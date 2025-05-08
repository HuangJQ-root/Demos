# Copyright (c) 2025 Li Auto Inc. and its affiliates
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import re
from antlr4 import *
from resources.gen.IDL_GrammarLexer import *
from resources.gen.IDL_GrammarParser import *
from resources.gen.IDL_GrammarVisitor import *
from resources.gen.IDL_GrammarListener import *

constructMapList = []
base_type_list = ["boolean", "char", "int8", "uint8", "short", "unsignedshort", "long", "unsignedlong", "longlong", \
                  "unsignedlonglong", "float", "double", "longdouble", "string"]

class MemberListener(IDL_GrammarListener):
    node = {}
    memberFieldMapList = []
    member_dict = {}
    modules_name = []
    id = 0
    tmp_ordinal = 0
    annotationSign = ""
    annotationName = ""

    rpc_dict = {}
    RPC_LIST = []
    FuncMember_dict = {}
    FuncMember_list = []
    ParamIn = []
    ParamOut = []
    ParamInout = []

    def fill_name_field(self):
        if self.modules_name:
            self.node["nativeFQNameInModule"] = "_".join(self.modules_name) + "_" + self.node["name"]
        else:
            self.node["nativeFQNameInModule"] = self.node["name"]

    def enterDefinition(self, ctx: IDL_GrammarParser.SpecificationContext):
        self.node.clear()
        self.memberFieldMapList.clear()
        self.member_dict.clear()
        self.modules_name.clear()

    def enterModule_dcl(self, ctx:IDL_GrammarParser.Module_dclContext):
        self.node.clear()
        self.modules_name.append(ctx.identifier().ID().getText())

    def exitModule_dcl(self, ctx:IDL_GrammarParser.Module_dclContext):
        self.node.clear()
        self.modules_name.pop()

    def enterConstr_type_dcl(self, ctx: IDL_GrammarParser.Constr_type_dclContext):
        self.node["modulesName"] = self.modules_name.copy()

    def exitTypedef_dcl(self, ctx:IDL_GrammarParser.Typedef_dclContext):
        self.node["memberCount"] = 1

    def exitConstr_type_dcl(self, ctx: IDL_GrammarParser.Constr_type_dclContext):
        self.node["memberFieldMapList"] = self.memberFieldMapList.copy()

        constructMapList.append(self.node.copy())
        self.node.clear()
        self.memberFieldMapList.clear()
        self.member_dict.clear()
        self.id = 0

    def enterStruct_def(self, ctx: IDL_GrammarParser.Struct_defContext):
        self.node["constructKind"] = "struct"
        self.node["name"] = ctx.identifier().getText()
        self.fill_name_field()

    def exitStruct_def(self, ctx: IDL_GrammarParser.Struct_defContext):
        self.node["memberCount"] = self.id

    def enterMember(self, ctx: IDL_GrammarParser.MemberContext):
        self.member_dict["id"] = self.id
        self.member_dict["name"] = ctx.declarators().getText()
        self.member_dict["typeKind"] = "builtin"

    def exitMember(self, ctx: IDL_GrammarParser.MemberContext):
        self.id += 1
        if ctx.type_spec().getText() not in base_type_list:
            self.node["hasNonBasicMember"] = "true"
            self.member_dict["typeName"] = ctx.type_spec().getText()
            self.member_dict["typeKind"] = "user"
            self.member_dict["nativeTypeFQName"] = \
            "_".join(self.node['modulesName']) + '_' + self.member_dict["typeName"] \
            if self.node['modulesName'] else self.member_dict["typeName"]
        self.memberFieldMapList.append(self.member_dict.copy())
        self.member_dict.clear()

    # ------------------------------------------RPC----------------------------------------------------------
    def exitSpecification(self, ctx:IDL_GrammarParser.SpecificationContext):
        if self.RPC_LIST:
            constructMapList.append(self.RPC_LIST.copy())
            self.RPC_LIST.clear()

    def enterInterface_body(self, ctx:IDL_GrammarParser.Interface_bodyContext):
        self.FuncMember_list.clear()
        self.id = 0

    def exitInterface_body(self, ctx:IDL_GrammarParser.Interface_bodyContext):
        self.rpc_dict['FuncMember'] = self.FuncMember_list.copy()

    def exitInterface_def(self, ctx:IDL_GrammarParser.Interface_defContext):
        self.RPC_LIST.append(self.rpc_dict.copy())
        self.rpc_dict.clear()

    def enterInterface_header(self, ctx:IDL_GrammarParser.Interface_headerContext):
        self.rpc_dict['ModuleName'] = "_".join(self.modules_name) if self.modules_name else ""
        self.rpc_dict['InterfaceName'] = ctx.identifier().getText()

    def enterOp_dcl(self, ctx:IDL_GrammarParser.Op_dclContext):
        self.FuncMember_dict['FuncName'] = ctx.identifier().getText()
        if ctx.operation_type_spec().getText() == "void":
            self.FuncMember_dict['ReturnType'] = "void"

    def exitOp_dcl(self, ctx:IDL_GrammarParser.Op_dclContext):
        self.FuncMember_list.append(self.FuncMember_dict.copy())
        self.FuncMember_dict.clear()

    def enterParameter_dcls(self, ctx:IDL_GrammarParser.Parameter_dclsContext):
        self.FuncMember_dict['id'] = self.id
        self.ParamIn.clear()
        self.ParamOut.clear()
        self.ParamInout.clear()

    def exitParameter_dcls(self, ctx:IDL_GrammarParser.Parameter_dclsContext):
        self.id += 1
        self.FuncMember_dict['ParamIn'] = self.ParamIn.copy()
        self.FuncMember_dict['ParamOut'] = self.ParamOut.copy()
        self.FuncMember_dict['ParamInout'] = self.ParamInout.copy()

    def enterParam_dcl(self, ctx:IDL_GrammarParser.Param_dclContext):
        self.member_dict['ParamAttr'] = ctx.param_attribute().getText() if ctx.param_attribute() else "in"
        self.member_dict['ParamValue'] =ctx.simple_declarator().getText()
        if ctx.type_spec():
            self.member_dict['isbase'] = "false"
            self.modules_name.append(ctx.type_spec().getText())
            self.member_dict['ParamType'] = "_".join(self.modules_name)
            self.modules_name.pop()
            self.member_dict['elementSerializeMethod'] = self.member_dict['ParamType'] + "_serialize_rpc_topic"
            self.member_dict['elementDeserializeMethod'] = self.member_dict['ParamType'] + "_deserialize_rpc_topic"
            self.member_dict['mvbsTypeName'] = self.member_dict['ParamType']
            self.member_dict['typeName'] = ctx.type_spec().getText()

    def exitParam_dcl(self, ctx: IDL_GrammarParser.Param_dclContext):
        if self.member_dict['ParamAttr'] == "in":
            self.ParamIn.append(self.member_dict.copy())
        elif self.member_dict['ParamAttr'] == "out":
            self.ParamOut.append(self.member_dict.copy())
        elif self.member_dict['ParamAttr'] == "inout":
            self.member_dict['ParamValue']= self.member_dict['ParamValue'] + "_in"
            self.ParamIn.append(self.member_dict.copy())

            self.member_dict['ParamValue'] = self.member_dict['ParamValue'].split('_in')[0] + "_out"
            self.ParamOut.append(self.member_dict.copy())

        self.member_dict.clear()

    # -------------------------------------------------------------------------------------------------------
    def enterSigned_octet_int(self, ctx: IDL_GrammarParser.Signed_octet_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "int8_t"
        self.member_dict["typeName"] = "int8"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int8_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int8_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "int8_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_int8_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_int8_t"
        else:
            self.member_dict['ParamType'] = "int8_t"

    def enterSigned_short_int(self, ctx: IDL_GrammarParser.Signed_short_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "int16_t"
        self.member_dict["typeName"] = "short"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int16_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int16_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "int16_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_int16_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_int16_t"
        else:
            self.member_dict['ParamType'] = "int16_t"


    def enterSigned_long_int(self, ctx: IDL_GrammarParser.Signed_long_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "int32_t"
        self.member_dict["typeName"] = "long"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int32_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int32_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "int32_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_int32_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_int32_t"
        else:
            self.member_dict['ParamType'] = "int32_t"

    def enterSigned_longlong_int(self, ctx: IDL_GrammarParser.Signed_longlong_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "int64_t"
        self.member_dict["typeName"] = "long long"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int64_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int64_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "int64_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_int64_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_int64_t"
        else:
            self.member_dict['ParamType'] = "int64_t"

    def enterUnsigned_octet_int(self, ctx: IDL_GrammarParser.Unsigned_octet_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "uint8_t"
        self.member_dict["typeName"] = "uint8"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint8_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint8_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "uint8_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_uint8_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_uint8_t"
        else:
            self.member_dict['ParamType'] = "uint8_t"

    def enterUnsigned_short_int(self, ctx: IDL_GrammarParser.Unsigned_short_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "uint16_t"
        self.member_dict["typeName"] = "unsigned short"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint16_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint16_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "uint16_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_uint16_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_uint16_t"
        else:
            self.member_dict['ParamType'] = "uint16_t"

    def enterUnsigned_long_int(self, ctx: IDL_GrammarParser.Unsigned_long_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "uint32_t"
        self.member_dict["typeName"] = "unsigned long"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint32_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint32_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "uint32_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_uint32_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_uint32_t"
        else:
            self.member_dict['ParamType'] = "uint32_t"

    def enterUnsigned_longlong_int(self, ctx: IDL_GrammarParser.Unsigned_longlong_intContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "uint64_t"
        self.member_dict["typeName"] = "unsigned long long"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint64_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint64_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "uint64_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_uint64_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_uint64_t"
        else:
            self.member_dict['ParamType'] = "uint64_t"

    def enterOctet_type(self, ctx: IDL_GrammarParser.Octet_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "uint8_t"
        self.member_dict["typeName"] = "octet"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint8_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint8_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "uint8_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_uint8_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_uint8_t"
        else:
            self.member_dict['ParamType'] = "uint8_t"

    def enterFloat_type(self, ctx: IDL_GrammarParser.Float_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "float"
        self.member_dict["typeName"] = "float"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_float"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_float"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "float"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_float"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_float"
        else:
            self.member_dict['ParamType'] = "float"

    def enterDouble_type(self, ctx: IDL_GrammarParser.Double_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "double"
        self.member_dict["typeName"] = "double"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_double"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_double"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "double"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_double"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_double"
        else:
            self.member_dict['ParamType'] = "double"

    def enterLong_double_type(self, ctx: IDL_GrammarParser.Long_double_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "double"
        self.member_dict["typeName"] = "double"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_double"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_double"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "double"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_double"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_double"
        else:
            self.member_dict['ParamType'] = "double"

    def enterBoolean_type(self, ctx: IDL_GrammarParser.Boolean_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "uint8_t"
        self.member_dict["typeName"] = "boolean"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint8_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint8_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "uint8_t"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_uint8_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_uint8_t"
        else:
            self.member_dict['ParamType'] = "uint8_t"

    def enterChar_type(self, ctx: IDL_GrammarParser.Char_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "unsigned char"
        self.member_dict["typeName"] = "unsigned char"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_char"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_char"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "char"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_char"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_char"
        else:
            self.member_dict['ParamType'] = "char"

    def enterWide_char_type(self, ctx: IDL_GrammarParser.Wide_char_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "uint32_t"
        self.member_dict["typeName"] = "wchar"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint32_t"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint32_t"
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "wchar"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_uint32_t"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_uint32_t"
        else:
            self.member_dict['ParamType'] = "wchar"

    def enterString_type(self, ctx: IDL_GrammarParser.String_typeContext):
        self.member_dict['isbase'] = "true"
        self.member_dict["mvbsTypeName"] = "char *"
        self.member_dict["typeName"] = "string"
        self.member_dict['elementSerializeMethod'] = "mcdr_serialize_string"
        self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_string"
        self.member_dict['strSize'] = int(ctx.positive_int_const().getText()) if ctx.positive_int_const() else 255
        if 'ReturnType' not in self.FuncMember_dict.keys():
            self.FuncMember_dict['ReturnType'] = "char"
            self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_string"
            self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_string"
        else:
            self.member_dict['ParamType'] = "char"
            # self.member_dict['ParamNewValue'] = ctx.parentCtx.parentCtx.simple_declarator().getText() + "[" + str(self.member_dict['Length']) + "]"

    # def enterWide_string_type(self, ctx: IDL_GrammarParser.Wide_string_typeContext):
    #     self.member_dict['isbase'] = "true"
    #     self.member_dict["mvbsTypeName"] = "wchar *"
    #     self.member_dict["typeName"] = "wstring"
    #     self.member_dict['elementSerializeMethod'] = "mcdr_serialize_string"
    #     self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_string"
    #     self.member_dict['strSize'] = int(ctx.positive_int_const().getText()) if ctx.positive_int_const() else 127
    #     if 'ReturnType' not in self.FuncMember_dict.keys():
    #         self.FuncMember_dict['ReturnType'] = "wchar"
    #         self.FuncMember_dict['returnSerializeMethod'] = "mcdr_serialize_string"
    #         self.FuncMember_dict['returnDeserializeMethod'] = "mcdr_deserialize_string"
    #     else:
    #         self.member_dict['ParamType'] = "wchar"
    #         self.member_dict['ParamNewValue'] = ctx.simple_declarator().getText() + "[" + str(self.member_dict['Length']) + "]"
