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
base_type_list = ['int8', 'short', 'long', 'long long', 'uint8', 'unsigned short', 'unsigned long', 'unsigned long long',
                  'octet', 'float', 'double','long double', 'boolean', 'char', 'unsigned char', 'wchar', 'string', 'wstring']
base_type_dict = {}
array_type_list = []
seq_type_list = []
enum_type_dict = {}
preproc_directive= {'idl_lst': []}

def get_other_module_member_nativeFQNameInModule(module_name_list):
    for module_member in constructMapList:
        if module_member['modulesName'] != []:
            typeCodeFQName_list = module_member['typeCodeFQName'].split("::")
            if set(module_name_list).issubset(set(typeCodeFQName_list)):
                return module_member['nativeFQNameInModule']

    return "_".join(module_name_list)


def get_str_size_name(member_dict, constructMapList):
    member_dict["sizeIsStr"] = 'false'
    member_dict["SizeValue"] = member_dict['strSize']
    for node in constructMapList:
        if node["constructKind"] == 'const':
            if node['name'] == member_dict['strSize']:
                member_dict["SizeValue"] = node['value']
                member_dict['strSize'] = node['nativeFQNameInModule']
                member_dict["sizeIsStr"] = 'true'
        if node["constructKind"] == 'enum':
            for member in node['memberFieldMapList']:
                if member['name'] == member_dict['strSize']:
                    member_dict["SizeValue"] = member['value']
                    member_dict["sizeIsStr"] = 'true'

    return  member_dict

def get_array_size_name(member_dict, constructMapList):
    member_dict["sizeIsStr"] = 'false'
    member_dict["SizeValue"] = member_dict["arrayTotalSize"]
    for node in constructMapList:
        if node["constructKind"] == 'const':
            if node['name'] == member_dict["arrayTotalSize"] or node['nativeFQNameInModule'] == member_dict["arrayTotalSize"]:
                member_dict["SizeValue"] = node['value']
                member_dict["arrayTotalSize"] = node['nativeFQNameInModule']
                member_dict["dimensionList"] = f'[{member_dict["arrayTotalSize"]}]'
                member_dict["sizeIsStr"] = 'true'
        if node["constructKind"] == 'enum':
            for member in node['memberFieldMapList']:
                if member['name'] ==member_dict["arrayTotalSize"]:
                    member_dict["SizeValue"] = member['value']
                    member_dict["sizeIsStr"] = 'true'

    return  member_dict

def get_sequence_size_name(member_dict, constructMapList):
    member_dict["sizeIsStr"] = 'false'
    member_dict["SizeValue"] = member_dict["arrayTotalSize"]
    for node in constructMapList:
        if node["constructKind"] == 'const':
            if node['name'] == member_dict["arrayTotalSize"]:
                member_dict["arrayTotalSize"] = node['nativeFQNameInModule']
                member_dict["seqSize"] = node['nativeFQNameInModule']
                member_dict["seqSizeRealValue"] = node['value']
                member_dict["SizeValue"]  =  node['value']
                member_dict["sizeIsStr"] = 'true'

        if node["constructKind"] == 'enum':
            for member in node['memberFieldMapList']:
                if member['name'] ==member_dict["arrayTotalSize"]:
                    member_dict["arrayTotalSize"] = member['name']
                    member_dict["seqSize"] = member['name']
                    member_dict["seqSizeRealValue"] = member['value']
                    member_dict["SizeValue"] = member['value']
                    member_dict["sizeIsStr"] = 'true'

    return  member_dict
class MemberListener(IDL_GrammarListener):
    node = {}
    memberFieldMapList = []
    member_dict = {}
    modules_name = []
    id = 0
    tmp_ordinal = 0
    annotationSign = ""
    annotationName = ""

    def fill_name_field(self):
        if self.modules_name:
            self.node["nativeFQNameInModule"] = "_".join(self.modules_name) + "_" + self.node["name"]
            self.node["typeCodeFQName"] = "::".join(self.modules_name) + "::" + self.node["name"]
        else:
            self.node["nativeFQNameInModule"] = self.node["name"]
            self.node["typeCodeFQName"] = self.node["name"]

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
        if not self.node.get("extensibility"):
            self.node["extensibility"] = "EXTENSIBLE_EXTENSIBILITY"

    def enterTypedef_dcl(self, ctx:IDL_GrammarParser.Typedef_dclContext):
        self.node["constructKind"] = "alias"

    def exitTypedef_dcl(self, ctx:IDL_GrammarParser.Typedef_dclContext):
        self.node["memberCount"] = 1
        if "typedefsequence" in ctx.getText():
            self.node['isAliseofSequence'] = 'true'
            self.node["isBaseSequence"] = \
                "true" if self.member_dict["typeName"] in base_type_dict.values() else "false"
        if self.node["name"] in array_type_list:
            self.node["isAliasOfArray"] = "true"
            self.node["isBaseArray"] = \
                "true" if self.member_dict["typeName"] in base_type_dict.values() else "false"

    def exitConstr_type_dcl(self, ctx: IDL_GrammarParser.Type_dclContext):
        self.node["memberFieldMapList"] = self.memberFieldMapList.copy()
        constructMapList.append(self.node.copy())
        self.node.clear()
        self.memberFieldMapList.clear()
        self.member_dict.clear()
        self.id = 0

    def enterAnnotation_appl(self, ctx: IDL_GrammarParser.Annotation_applContext):
        self.annotationSign = "@"
        if ctx.getText() == '@mutable':
            self.node['extensibility'] = 'MUTABLE_EXTENSIBILITY'
        if ctx.getText() == '@compatible':
            self.node['extensibility'] = 'COMPATIBLE_EXTENSIBILITY'
        if ctx.getText() == '@key':
            self.member_dict['isKey'] = 'true'
            self.node["hasKey"] = 'true'
        if ctx.KW_DEFAULT():
            if ctx.KW_DEFAULT().getText() == 'default':
                self.member_dict['defaultvalue'] = ctx.annotation_appl_params().getText()

    def enterType_declarator(self, ctx: IDL_GrammarParser.Type_declaratorContext):
        self.node["name"] = ctx.declarators().declarator()[0].getText()
        self.fill_name_field()
        self.member_dict["id"] = self.id
        self.member_dict["name"] = ""
        self.member_dict["typeKind"] = "builtin"

        if self.node.get("modulesName"):
            if "sequence" in ctx.type_spec().getText():
                self.member_dict["typeName"] =  "_".join(
                    self.node.get("modulesName")) + "_" + ctx.declarators().getText()
                self.member_dict["seqname"] = "seq_data"
                seq_type_list.append(self.node["name"])
            else:
                self.member_dict["typeName"] = "_".join(
                    self.node.get("modulesName")) + "_" + ctx.type_spec().getText()
        else:
            if "sequence" in ctx.type_spec().getText():
                self.member_dict["typeName"] =   ctx.declarators().getText()
                self.member_dict["seqname"] = "seq_data"
                seq_type_list.append(self.node["name"])
            else:
                self.member_dict["typeName"] = ctx.type_spec().getText()

        self.member_dict["nativeTypeFQName"] = self.member_dict["typeName"]
        self.member_dict["typeKindResolved"] = "unused"

    def exitType_declarator(self, ctx: IDL_GrammarParser.Type_declaratorContext):
        self.id += 1
        if self.member_dict["typeKindResolved"] == "unused":
            self.member_dict["typeKind"] = "user"
        del self.member_dict["typeKindResolved"]
        self.memberFieldMapList.append(self.member_dict.copy())

    def enterArray_declarator(self, ctx: IDL_GrammarParser.Array_declaratorContext):
        if self.node["constructKind"] == "alias":
            self.node["name"] = ctx.identifier().getText()
            self.fill_name_field()
            array_type_list.append(self.node["name"])
        else:
            self.member_dict["name"] = ctx.identifier().getText()

        if "::" in ctx.fixed_array_size(0).positive_int_const().getText():
            module_name_list =  ctx.fixed_array_size(0).positive_int_const().getText().split("::")
            self.member_dict["arrayTotalSize"] = get_other_module_member_nativeFQNameInModule(module_name_list)
            self.member_dict["dimensionList"] = '[' + self.member_dict["arrayTotalSize"] + ']'
        else:
            self.member_dict["dimensionList"] = ctx.fixed_array_size(0).getText()
            self.member_dict["arrayTotalSize"] = ctx.fixed_array_size(0).positive_int_const().getText()
        self.member_dict = get_array_size_name(self.member_dict, constructMapList)

    def enterSequence_type(self, ctx:IDL_GrammarParser.Sequence_typeContext):
        self.member_dict["isSeq"] = 'true'
        if "::" in ctx.simple_type_spec().getText():
            module_name_list = ctx.simple_type_spec().getText().split("::")
            self.member_dict["typeName"] = get_other_module_member_nativeFQNameInModule(module_name_list)
        else:
            self.member_dict["typeName"] = ctx.simple_type_spec().getText()
        if ctx.positive_int_const():
            self.member_dict["seqSize"] = ctx.positive_int_const().getText()
            self.member_dict['seqSizeRealValue'] = self.member_dict["seqSize"]
            self.member_dict["isdefault"] = 'false'
        else:
            self.member_dict["seqSize"] = 100
            self.member_dict["isdefault"] = 'true'
        self.member_dict["arrayTotalSize"] =  self.member_dict["seqSize"]
        self.member_dict = get_sequence_size_name(self.member_dict, constructMapList)
        pass

    def exitSequence_type(self, ctx:IDL_GrammarParser.Sequence_typeContext):
        if self.member_dict["typeName"]  in base_type_list:
            self.member_dict['elementSeqSerializeMethod'] = "mcdr_serialize_sequence_"+self.member_dict["mvbsTypeName"]
            self.member_dict['elementSeqDeserializeMethod'] = "mcdr_deserialize_sequence_"+self.member_dict["mvbsTypeName"]
        else:
            self.member_dict['elementSeqSerializeMethod'] = "mcdr_serialize_"+self.member_dict["typeName"]
            self.member_dict['elementSeqDeserializeMethod'] = "mcdr_deserialize_"+self.member_dict["typeName"]
            pass

    def enterStruct_def(self, ctx: IDL_GrammarParser.Struct_defContext):
        self.node["constructKind"] = "struct"
        self.node["name"] = ctx.identifier().getText()
        self.fill_name_field()

    def exitStruct_def(self, ctx: IDL_GrammarParser.Struct_defContext):
        self.node["memberCount"] = self.id


    def enterUnion_def(self, ctx:IDL_GrammarParser.Union_defContext):
        self.node["constructKind"] = "union"
        self.node["name"] = ctx.identifier().getText()
        self.fill_name_field()

    def enterSwitch_type_spec(self, ctx:IDL_GrammarParser.Switch_type_specContext):
        nativeTypeFQName = ctx.getText()
        typeCodeFQNameInModule = ctx.getText()
        if nativeTypeFQName not in base_type_list:
            self.node["switchType"] = "user"
        else:
            self.node["switchType"] = "buildin"

        for node in constructMapList:
            if node['name'] == nativeTypeFQName:
                nativeTypeFQName = node['nativeFQNameInModule']
                typeCodeFQNameInModule = node['typeCodeFQName']

        self.node["nativeTypeFQName"] = nativeTypeFQName
        self.node["typeCodeFQNameInModule"] = typeCodeFQNameInModule


    def enterSwitch_body(self, ctx: IDL_GrammarParser.Switch_bodyContext):
        self.node['labelList'] = []

    def enterCase_label(self, ctx: IDL_GrammarParser.CaseContext):
        self.member_dict['label'] = ctx.const_expr().getText()
        self.node['labelList'].append(self.member_dict['label'])


    def enterElement_spec(self, ctx: IDL_GrammarParser.Element_specContext):
        self.member_dict["id"] = self.id
        self.member_dict["name"] = ctx.declarator().getText()
        self.member_dict["typeKind"] = "builtin"

    def exitElement_spec(self, ctx: IDL_GrammarParser.Element_specContext):
        self.id += 1
        self.memberFieldMapList.append(self.member_dict.copy())
        self.member_dict.clear()

    def exitUnion_def(self, ctx:IDL_GrammarParser.Union_defContext):
        self.node["memberCount"] = self.id

    def enterMember(self, ctx: IDL_GrammarParser.MemberContext):
        self.member_dict["id"] = self.id
        self.member_dict["name"] = ctx.declarators().getText()
        self.member_dict["typeKind"] = "builtin"
        if "::" in  ctx.type_spec().getText():
            module_name_list =  ctx.type_spec().getText().split("::")
            self.member_dict["typeName"] = get_other_module_member_nativeFQNameInModule(module_name_list)
        else:
            self.member_dict["typeName"] = ctx.type_spec().getText()


    def exitMember(self, ctx: IDL_GrammarParser.MemberContext):
        self.id += 1
        if self.member_dict["typeName"]  not in base_type_list:
            self.node["hasNonBasicMember"] = "true"
            self.member_dict["typeKind"] = "user"
            self.member_dict["nativeTypeFQName"] = self.member_dict["typeName"]
            for node in constructMapList:
                if node['name'] == self.member_dict["typeName"]:
                    self.member_dict["nativeTypeFQName"] = node['nativeFQNameInModule']

            self.member_dict["extensibility"] = "FINAL_EXTENSIBILITY"
            if self.member_dict["typeName"] in array_type_list:
                self.member_dict["isAlias"] = "true"
                self.member_dict["isAliasOfArray"] = "true"
                self.member_dict["nativeTypeFQName"] = \
                    "_".join(self.node['modulesName']) + '_' + self.member_dict["typeName"] \
                        if self.node['modulesName'] else self.member_dict["typeName"]
                for node in constructMapList:
                    if self.member_dict["nativeTypeFQName"] == node["nativeFQNameInModule"] and node["isAliasOfArray"] == "true" \
                           and "mvbsTypeName" in node["memberFieldMapList"][0] :
                        self.member_dict['Original_type'] = node["memberFieldMapList"][0]["realTypeName"]
                        self.member_dict['Original_count'] = node["memberFieldMapList"][0]["arrayTotalSize"]
            elif self.member_dict["typeName"] in seq_type_list:
                self.member_dict["isAlias"] = "true"
                self.member_dict["isAliseofSequence"] = "true"
                self.member_dict["nativeTypeFQName"] = \
                    "_".join(self.node['modulesName']) + '_' + self.member_dict["typeName"] \
                        if self.node['modulesName'] else self.member_dict["typeName"]
                for node in constructMapList:
                    if self.member_dict["nativeTypeFQName"] == node["nativeFQNameInModule"] and node["isAliseofSequence"] == "true" \
                           and "mvbsTypeName" in node["memberFieldMapList"][0] :
                        self.member_dict['Original_type'] = node["memberFieldMapList"][0]["realTypeName"]
                        self.member_dict['Original_count'] = node["memberFieldMapList"][0]["arrayTotalSize"]
            elif self.member_dict["typeName"] in enum_type_dict.keys():
                self.member_dict["isEnum"] = "true"
                self.member_dict["defaultEnumMemberName"] = enum_type_dict[self.member_dict["typeName"]][0]
                # self.member_dict["explicitDefaultValue"] = enum_type_dict[self.member_dict["typeName"]][1]
                self.member_dict["resolvedTypeEnum"] = "true"
        if "SeqTypeName" not in  self.member_dict and "nativeTypeFQName" in self.member_dict:
            self.member_dict["SeqTypeName"] = self.member_dict["nativeTypeFQName"] + "Seq"
        self.memberFieldMapList.append(self.member_dict.copy())
        self.member_dict.clear()

    def enterEnum_dcl(self, ctx: IDL_GrammarParser.Enum_dclContext):
        self.node["constructKind"] = "enum"
        self.node["name"] = ctx.identifier().getText()
        if ctx.enumerator_list().enumerator()[0].const_expr():
            self.node["explicitDefaultValue"] = ctx.enumerator_list().enumerator()[0].const_expr()[0].getText()
        else:
            self.node["explicitDefaultValue"] = 0
        self.fill_name_field()

    def exitEnum_dcl(self, ctx: IDL_GrammarParser.Enum_dclContext):
        self.node["memberCount"] = self.id

    def enterEnumerator(self, ctx: IDL_GrammarParser.EnumeratorContext):
        self.member_dict["typeKind"] = "enum"
        self.member_dict["name"] = ctx.declarator().getText()
        self.member_dict["nativeFQNameInModule"] = self.node['nativeFQNameInModule'] + "_" + self.member_dict["name"]
        self.member_dict["typeCodeFQName"] = self.node['typeCodeFQName'] + "::" + self.member_dict["name"]
        if ctx.const_expr():
            self.member_dict["ordinal"] = ctx.const_expr()[0].getText()
        else:
            self.member_dict["ordinal"] = 'NULL'
            self.member_dict["value"] = self.id
            if self.tmp_ordinal != 0:
                self.tmp_ordinal += 1
                self.member_dict["value"] = self.tmp_ordinal
        if self.node["name"] not in enum_type_dict.keys():
            enum_type_dict[self.node["name"]] = (self.member_dict["name"], self.member_dict["ordinal"])

    def exitEnumerator(self, ctx: IDL_GrammarParser.EnumeratorContext):
        self.id += 1
        self.memberFieldMapList.append(self.member_dict.copy())

    def enterConst_dcl(self, ctx: IDL_GrammarParser.Const_dclContext):
        self.node["constructKind"] = "const"
        self.node["modulesName"] = self.modules_name.copy()
        self.node["name"] = ctx.identifier().getText()
        self.node["typeName"] = ctx.const_type().getText()
        self.node["typeKind"] = "builtin"
        if self.node['modulesName']:
            self.member_dict['nativeFQNameInModule'] = "_".join(self.node['modulesName']) + "_" + self.node["name"]
            self.member_dict["typeCodeFQName"] = "::".join(self.modules_name) + "::" + self.node["name"]
        else:
            self.member_dict['nativeFQNameInModule'] = self.node["name"]
            self.member_dict['typeCodeFQName'] = self.node["name"]
        # typeName
        if ctx.const_type().string_type():
            self.node["typeName"] = "string"
        # elif ctx.const_type().wide_string_type():
        #     self.node["typeName"] = "wstring"
        else:
            self.node["typeName"] = ctx.const_type().getText()
        # value
        if self.node["typeName"] == "longlong":
            self.node["value"] = re.findall(r"\d+\.?\d*", ctx.const_expr().getText())[0] + "LL"
        elif self.node["typeName"] in ["unsignedlonglong"]:
            self.node["value"] = re.findall(r"\d+\.?\d*", ctx.const_expr().getText())[0] + "ULL"
        elif self.node["typeName"] in ["float"]:
            self.node["value"] = re.findall(r"\d+\.?\d*", ctx.const_expr().getText())[0] + "f"
        # elif self.node["typeName"] == "wstring":
            # ord_lst = [str(ord(x)) for x in ctx.const_expr().getText().replace("\"", "").replace("\'", "")]
            # ord_lst.append("0")
            # self.node["value"] = "{" + ",".join(ord_lst) + "}"
        else:
            self.node["value"] = ctx.const_expr().getText()

    def exitConst_dcl(self, ctx: IDL_GrammarParser.Const_dclContext):
        self.node["nativeTypeFQName"] = self.node["typeName"]
        if self.member_dict:
            constructMapList.append({**self.node, **self.member_dict})
            self.member_dict.clear()
        else:
            constructMapList.append(self.node.copy())
        self.node.clear()



    def enterSigned_octet_int(self, ctx: IDL_GrammarParser.Signed_octet_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "int8"
            self.member_dict['realTypeName'] = "int8"
            self.member_dict["mvbsTypeName"] = "int8_t"
            self.member_dict["SeqTypeName"] = "mvbs_int8_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int8_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int8_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_int8_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_int8_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "int8"

    def enterSigned_short_int(self, ctx: IDL_GrammarParser.Signed_short_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "short"
            self.member_dict['realTypeName'] = "short"
            self.member_dict["mvbsTypeName"] = "int16_t"
            self.member_dict["SeqTypeName"] = "mvbs_short_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int16_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int16_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_int16_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_int16_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "short"

    def enterSigned_long_int(self, ctx: IDL_GrammarParser.Signed_long_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "long"
            self.member_dict['realTypeName'] = "long"
            self.member_dict["mvbsTypeName"] = "int32_t"
            self.member_dict["SeqTypeName"] = "mvbs_long_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int32_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int32_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_int32_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_int32_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "long"

    def enterSigned_longlong_int(self, ctx: IDL_GrammarParser.Signed_longlong_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "long long"
            self.member_dict['realTypeName'] = "long long"
            self.member_dict["mvbsTypeName"] = "int64_t"
            self.member_dict["SeqTypeName"] = "mvbs_long_long_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_int64_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_int64_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_int64_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_int64_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "long long"

    def enterUnsigned_octet_int(self, ctx: IDL_GrammarParser.Unsigned_octet_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "uint8"
            self.member_dict['realTypeName'] = "uint8"
            self.member_dict["mvbsTypeName"] = "uint8_t"
            self.member_dict["SeqTypeName"] = "mvbs_uint8_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint8_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint8_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_uint8_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_uint8_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "uint8"

    def enterUnsigned_short_int(self, ctx: IDL_GrammarParser.Unsigned_short_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "unsigned short"
            self.member_dict['realTypeName'] = "unsigned short"
            self.member_dict["mvbsTypeName"] = "uint16_t"
            self.member_dict["SeqTypeName"] = "mvbs_unsigned_short_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint16_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint16_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_uint16_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_uint16_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "unsigned short"

    def enterUnsigned_long_int(self, ctx: IDL_GrammarParser.Unsigned_long_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "unsigned long"
            self.member_dict['realTypeName'] = "unsigned long"
            self.member_dict["mvbsTypeName"] = "uint32_t"
            self.member_dict["SeqTypeName"] = "mvbs_unsigned_long_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint32_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint32_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_uint32_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_uint32_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "unsigned long"

    def enterUnsigned_longlong_int(self, ctx: IDL_GrammarParser.Unsigned_longlong_intContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "unsigned long long"
            self.member_dict['realTypeName'] = "unsigned long long"
            self.member_dict["mvbsTypeName"] = "uint64_t"
            self.member_dict["SeqTypeName"] = "mvbs_unsigned_long_long_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint64_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint64_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_uint64_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_uint64_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "unsigned long long"

    def enterOctet_type(self, ctx: IDL_GrammarParser.Octet_typeContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "octet"
            self.member_dict['realTypeName'] = "uint8"
            self.member_dict["mvbsTypeName"] = "uint8_t"
            self.member_dict["SeqTypeName"] = "mvbs_uint8_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint8_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint8_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_uint8_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_uint8_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "octet"

    def enterFloat_type(self, ctx: IDL_GrammarParser.Float_typeContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "float"
            self.member_dict['realTypeName'] = "float"
            self.member_dict["mvbsTypeName"] = "float"
            self.member_dict["SeqTypeName"] = "mvbs_float_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_float"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_float"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_float"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_float"
            self.member_dict.setdefault('defaultvalue', '0.0f')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "float"

    def enterDouble_type(self, ctx: IDL_GrammarParser.Double_typeContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "double"
            self.member_dict['realTypeName'] = "double"
            self.member_dict["mvbsTypeName"] = "double"
            self.member_dict["SeqTypeName"] = "mvbs_double_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_double"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_double"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_double"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_double"
            self.member_dict.setdefault('defaultvalue', '0.0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "double"

    def enterLong_double_type(self, ctx: IDL_GrammarParser.Long_double_typeContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "double"
            self.member_dict['realTypeName'] = "double"
            self.member_dict["mvbsTypeName"] = "double"
            self.member_dict["SeqTypeName"] = "mvbs_long_double_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_double"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_double"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_double"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_double"
            self.member_dict.setdefault('defaultvalue', '0.0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "double"

    def enterBoolean_type(self, ctx: IDL_GrammarParser.Boolean_typeContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "boolean"
            self.member_dict['realTypeName'] = "boolean"
            self.member_dict["mvbsTypeName"] = "uint8_t"
            self.member_dict["SeqTypeName"] = "mvbs_boolean_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint8_t"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint8_t"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_uint8_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_uint8_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "boolean"

    def enterChar_type(self, ctx: IDL_GrammarParser.Char_typeContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "unsigned char"
            self.member_dict['realTypeName'] = "char"
            self.member_dict["mvbsTypeName"] = "unsigned char"
            self.member_dict["SeqTypeName"] = "mvbs_char_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_unsigned_char"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_unsigned_char"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_unsigned_char"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_unsigned_char"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "unsigned char"

    def enterWide_char_type(self, ctx: IDL_GrammarParser.Wide_char_typeContext):
        if self.node['constructKind'] != 'const':
            self.member_dict["typeName"] = "wchar"
            self.member_dict['realTypeName'] = "wchar"
            self.member_dict["mvbsTypeName"] = "uint32_t"
            self.member_dict["SeqTypeName"] = "mvbs_char_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_uint32"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_uint32"
            self.member_dict['elementArraySerializeMethod'] = "mcdr_serialize_array_uint32_t"
            self.member_dict['elementArrayDeserializeMethod'] = "mcdr_deserialize_array_uint32_t"
            self.member_dict.setdefault('defaultvalue', '0')
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "wchar"

    def enterString_type(self, ctx: IDL_GrammarParser.String_typeContext):
        if self.node['constructKind'] != 'const':
            self.node['memberHasString'] = 'true'
            self.member_dict["typeName"] = "string"
            self.member_dict['realTypeName'] = "string"
            self.member_dict["mvbsTypeName"] = "char *"
            self.member_dict["SeqTypeName"] = "mvbs_string_seq"
            self.member_dict['elementSerializeMethod'] = "mcdr_serialize_string"
            self.member_dict['elementDeserializeMethod'] = "mcdr_deserialize_string"

            if ctx.positive_int_const():
                self.member_dict["strSize"] = ctx.positive_int_const().getText()
                self.member_dict["isdefault"] = 'false'
            else:
                self.member_dict["strSize"] = 255
                self.member_dict["isdefault"] = 'true'
            self.member_dict = get_str_size_name(self.member_dict, constructMapList)
            self.member_dict.setdefault('defaultvalue', "")
            if ctx.getText() not in base_type_dict.keys():
                base_type_dict[ctx.getText()] = "string"
