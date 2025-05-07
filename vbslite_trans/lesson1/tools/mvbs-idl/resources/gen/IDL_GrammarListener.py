# Generated from IDL_Grammar.g4 by ANTLR 4.13.0
# antlr4 (v4.13.0)
# 	- Project: https://github.com/antlr/antlr4
# 	- License: BSD
# 	- Copyright (c) 2012-2022 The ANTLR Project


# Full license texts:
# - BSD License: See LICENSE-ANTLR

from antlr4 import *
if "." in __name__:
    from .IDL_GrammarParser import IDL_GrammarParser
else:
    from IDL_GrammarParser import IDL_GrammarParser

# This class defines a complete listener for a parse tree produced by IDL_GrammarParser.
class IDL_GrammarListener(ParseTreeListener):

    # Enter a parse tree produced by IDL_GrammarParser#specification.
    def enterSpecification(self, ctx:IDL_GrammarParser.SpecificationContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#specification.
    def exitSpecification(self, ctx:IDL_GrammarParser.SpecificationContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#definition.
    def enterDefinition(self, ctx:IDL_GrammarParser.DefinitionContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#definition.
    def exitDefinition(self, ctx:IDL_GrammarParser.DefinitionContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#module_dcl.
    def enterModule_dcl(self, ctx:IDL_GrammarParser.Module_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#module_dcl.
    def exitModule_dcl(self, ctx:IDL_GrammarParser.Module_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#module_contents.
    def enterModule_contents(self, ctx:IDL_GrammarParser.Module_contentsContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#module_contents.
    def exitModule_contents(self, ctx:IDL_GrammarParser.Module_contentsContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#module_content.
    def enterModule_content(self, ctx:IDL_GrammarParser.Module_contentContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#module_content.
    def exitModule_content(self, ctx:IDL_GrammarParser.Module_contentContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_dcl.
    def enterInterface_dcl(self, ctx:IDL_GrammarParser.Interface_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_dcl.
    def exitInterface_dcl(self, ctx:IDL_GrammarParser.Interface_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_forward_dcl.
    def enterInterface_forward_dcl(self, ctx:IDL_GrammarParser.Interface_forward_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_forward_dcl.
    def exitInterface_forward_dcl(self, ctx:IDL_GrammarParser.Interface_forward_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_def.
    def enterInterface_def(self, ctx:IDL_GrammarParser.Interface_defContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_def.
    def exitInterface_def(self, ctx:IDL_GrammarParser.Interface_defContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_header.
    def enterInterface_header(self, ctx:IDL_GrammarParser.Interface_headerContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_header.
    def exitInterface_header(self, ctx:IDL_GrammarParser.Interface_headerContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_kind.
    def enterInterface_kind(self, ctx:IDL_GrammarParser.Interface_kindContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_kind.
    def exitInterface_kind(self, ctx:IDL_GrammarParser.Interface_kindContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_inheritance_spec.
    def enterInterface_inheritance_spec(self, ctx:IDL_GrammarParser.Interface_inheritance_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_inheritance_spec.
    def exitInterface_inheritance_spec(self, ctx:IDL_GrammarParser.Interface_inheritance_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_body.
    def enterInterface_body(self, ctx:IDL_GrammarParser.Interface_bodyContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_body.
    def exitInterface_body(self, ctx:IDL_GrammarParser.Interface_bodyContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#export_dcl.
    def enterExport_dcl(self, ctx:IDL_GrammarParser.Export_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#export_dcl.
    def exitExport_dcl(self, ctx:IDL_GrammarParser.Export_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#interface_name.
    def enterInterface_name(self, ctx:IDL_GrammarParser.Interface_nameContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#interface_name.
    def exitInterface_name(self, ctx:IDL_GrammarParser.Interface_nameContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#scoped_name.
    def enterScoped_name(self, ctx:IDL_GrammarParser.Scoped_nameContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#scoped_name.
    def exitScoped_name(self, ctx:IDL_GrammarParser.Scoped_nameContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#annotated_scoped_name.
    def enterAnnotated_scoped_name(self, ctx:IDL_GrammarParser.Annotated_scoped_nameContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#annotated_scoped_name.
    def exitAnnotated_scoped_name(self, ctx:IDL_GrammarParser.Annotated_scoped_nameContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#initialization_parameter_declaration.
    def enterInitialization_parameter_declaration(self, ctx:IDL_GrammarParser.Initialization_parameter_declarationContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#initialization_parameter_declaration.
    def exitInitialization_parameter_declaration(self, ctx:IDL_GrammarParser.Initialization_parameter_declarationContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#const_dcl.
    def enterConst_dcl(self, ctx:IDL_GrammarParser.Const_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#const_dcl.
    def exitConst_dcl(self, ctx:IDL_GrammarParser.Const_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#const_type.
    def enterConst_type(self, ctx:IDL_GrammarParser.Const_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#const_type.
    def exitConst_type(self, ctx:IDL_GrammarParser.Const_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#const_expr.
    def enterConst_expr(self, ctx:IDL_GrammarParser.Const_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#const_expr.
    def exitConst_expr(self, ctx:IDL_GrammarParser.Const_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#or_expr.
    def enterOr_expr(self, ctx:IDL_GrammarParser.Or_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#or_expr.
    def exitOr_expr(self, ctx:IDL_GrammarParser.Or_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#xor_expr.
    def enterXor_expr(self, ctx:IDL_GrammarParser.Xor_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#xor_expr.
    def exitXor_expr(self, ctx:IDL_GrammarParser.Xor_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#and_expr.
    def enterAnd_expr(self, ctx:IDL_GrammarParser.And_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#and_expr.
    def exitAnd_expr(self, ctx:IDL_GrammarParser.And_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#shift_expr.
    def enterShift_expr(self, ctx:IDL_GrammarParser.Shift_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#shift_expr.
    def exitShift_expr(self, ctx:IDL_GrammarParser.Shift_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#add_expr.
    def enterAdd_expr(self, ctx:IDL_GrammarParser.Add_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#add_expr.
    def exitAdd_expr(self, ctx:IDL_GrammarParser.Add_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#mult_expr.
    def enterMult_expr(self, ctx:IDL_GrammarParser.Mult_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#mult_expr.
    def exitMult_expr(self, ctx:IDL_GrammarParser.Mult_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#unary_expr.
    def enterUnary_expr(self, ctx:IDL_GrammarParser.Unary_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#unary_expr.
    def exitUnary_expr(self, ctx:IDL_GrammarParser.Unary_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#primary_expr.
    def enterPrimary_expr(self, ctx:IDL_GrammarParser.Primary_exprContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#primary_expr.
    def exitPrimary_expr(self, ctx:IDL_GrammarParser.Primary_exprContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#unary_operator.
    def enterUnary_operator(self, ctx:IDL_GrammarParser.Unary_operatorContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#unary_operator.
    def exitUnary_operator(self, ctx:IDL_GrammarParser.Unary_operatorContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#literal.
    def enterLiteral(self, ctx:IDL_GrammarParser.LiteralContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#literal.
    def exitLiteral(self, ctx:IDL_GrammarParser.LiteralContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#type_dcl.
    def enterType_dcl(self, ctx:IDL_GrammarParser.Type_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#type_dcl.
    def exitType_dcl(self, ctx:IDL_GrammarParser.Type_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#typedef_dcl.
    def enterTypedef_dcl(self, ctx:IDL_GrammarParser.Typedef_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#typedef_dcl.
    def exitTypedef_dcl(self, ctx:IDL_GrammarParser.Typedef_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#constr_type_dcl.
    def enterConstr_type_dcl(self, ctx:IDL_GrammarParser.Constr_type_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#constr_type_dcl.
    def exitConstr_type_dcl(self, ctx:IDL_GrammarParser.Constr_type_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#type_declarator.
    def enterType_declarator(self, ctx:IDL_GrammarParser.Type_declaratorContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#type_declarator.
    def exitType_declarator(self, ctx:IDL_GrammarParser.Type_declaratorContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#type_spec.
    def enterType_spec(self, ctx:IDL_GrammarParser.Type_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#type_spec.
    def exitType_spec(self, ctx:IDL_GrammarParser.Type_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#simple_type_spec.
    def enterSimple_type_spec(self, ctx:IDL_GrammarParser.Simple_type_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#simple_type_spec.
    def exitSimple_type_spec(self, ctx:IDL_GrammarParser.Simple_type_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#base_type_spec.
    def enterBase_type_spec(self, ctx:IDL_GrammarParser.Base_type_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#base_type_spec.
    def exitBase_type_spec(self, ctx:IDL_GrammarParser.Base_type_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#template_type_spec.
    def enterTemplate_type_spec(self, ctx:IDL_GrammarParser.Template_type_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#template_type_spec.
    def exitTemplate_type_spec(self, ctx:IDL_GrammarParser.Template_type_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#declarators.
    def enterDeclarators(self, ctx:IDL_GrammarParser.DeclaratorsContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#declarators.
    def exitDeclarators(self, ctx:IDL_GrammarParser.DeclaratorsContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#declarator.
    def enterDeclarator(self, ctx:IDL_GrammarParser.DeclaratorContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#declarator.
    def exitDeclarator(self, ctx:IDL_GrammarParser.DeclaratorContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#simple_declarator.
    def enterSimple_declarator(self, ctx:IDL_GrammarParser.Simple_declaratorContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#simple_declarator.
    def exitSimple_declarator(self, ctx:IDL_GrammarParser.Simple_declaratorContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#complex_declarator.
    def enterComplex_declarator(self, ctx:IDL_GrammarParser.Complex_declaratorContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#complex_declarator.
    def exitComplex_declarator(self, ctx:IDL_GrammarParser.Complex_declaratorContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#floating_pt_type.
    def enterFloating_pt_type(self, ctx:IDL_GrammarParser.Floating_pt_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#floating_pt_type.
    def exitFloating_pt_type(self, ctx:IDL_GrammarParser.Floating_pt_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#float_type.
    def enterFloat_type(self, ctx:IDL_GrammarParser.Float_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#float_type.
    def exitFloat_type(self, ctx:IDL_GrammarParser.Float_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#double_type.
    def enterDouble_type(self, ctx:IDL_GrammarParser.Double_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#double_type.
    def exitDouble_type(self, ctx:IDL_GrammarParser.Double_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#long_double_type.
    def enterLong_double_type(self, ctx:IDL_GrammarParser.Long_double_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#long_double_type.
    def exitLong_double_type(self, ctx:IDL_GrammarParser.Long_double_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#integer_type.
    def enterInteger_type(self, ctx:IDL_GrammarParser.Integer_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#integer_type.
    def exitInteger_type(self, ctx:IDL_GrammarParser.Integer_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#signed_int.
    def enterSigned_int(self, ctx:IDL_GrammarParser.Signed_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#signed_int.
    def exitSigned_int(self, ctx:IDL_GrammarParser.Signed_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#signed_octet_int.
    def enterSigned_octet_int(self, ctx:IDL_GrammarParser.Signed_octet_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#signed_octet_int.
    def exitSigned_octet_int(self, ctx:IDL_GrammarParser.Signed_octet_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#signed_short_int.
    def enterSigned_short_int(self, ctx:IDL_GrammarParser.Signed_short_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#signed_short_int.
    def exitSigned_short_int(self, ctx:IDL_GrammarParser.Signed_short_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#signed_long_int.
    def enterSigned_long_int(self, ctx:IDL_GrammarParser.Signed_long_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#signed_long_int.
    def exitSigned_long_int(self, ctx:IDL_GrammarParser.Signed_long_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#signed_longlong_int.
    def enterSigned_longlong_int(self, ctx:IDL_GrammarParser.Signed_longlong_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#signed_longlong_int.
    def exitSigned_longlong_int(self, ctx:IDL_GrammarParser.Signed_longlong_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#unsigned_int.
    def enterUnsigned_int(self, ctx:IDL_GrammarParser.Unsigned_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#unsigned_int.
    def exitUnsigned_int(self, ctx:IDL_GrammarParser.Unsigned_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#unsigned_octet_int.
    def enterUnsigned_octet_int(self, ctx:IDL_GrammarParser.Unsigned_octet_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#unsigned_octet_int.
    def exitUnsigned_octet_int(self, ctx:IDL_GrammarParser.Unsigned_octet_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#unsigned_short_int.
    def enterUnsigned_short_int(self, ctx:IDL_GrammarParser.Unsigned_short_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#unsigned_short_int.
    def exitUnsigned_short_int(self, ctx:IDL_GrammarParser.Unsigned_short_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#unsigned_long_int.
    def enterUnsigned_long_int(self, ctx:IDL_GrammarParser.Unsigned_long_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#unsigned_long_int.
    def exitUnsigned_long_int(self, ctx:IDL_GrammarParser.Unsigned_long_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#unsigned_longlong_int.
    def enterUnsigned_longlong_int(self, ctx:IDL_GrammarParser.Unsigned_longlong_intContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#unsigned_longlong_int.
    def exitUnsigned_longlong_int(self, ctx:IDL_GrammarParser.Unsigned_longlong_intContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#char_type.
    def enterChar_type(self, ctx:IDL_GrammarParser.Char_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#char_type.
    def exitChar_type(self, ctx:IDL_GrammarParser.Char_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#wide_char_type.
    def enterWide_char_type(self, ctx:IDL_GrammarParser.Wide_char_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#wide_char_type.
    def exitWide_char_type(self, ctx:IDL_GrammarParser.Wide_char_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#boolean_type.
    def enterBoolean_type(self, ctx:IDL_GrammarParser.Boolean_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#boolean_type.
    def exitBoolean_type(self, ctx:IDL_GrammarParser.Boolean_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#octet_type.
    def enterOctet_type(self, ctx:IDL_GrammarParser.Octet_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#octet_type.
    def exitOctet_type(self, ctx:IDL_GrammarParser.Octet_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#annotation.
    def enterAnnotation(self, ctx:IDL_GrammarParser.AnnotationContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#annotation.
    def exitAnnotation(self, ctx:IDL_GrammarParser.AnnotationContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#annotation_appl.
    def enterAnnotation_appl(self, ctx:IDL_GrammarParser.Annotation_applContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#annotation_appl.
    def exitAnnotation_appl(self, ctx:IDL_GrammarParser.Annotation_applContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#annotation_appl_params.
    def enterAnnotation_appl_params(self, ctx:IDL_GrammarParser.Annotation_appl_paramsContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#annotation_appl_params.
    def exitAnnotation_appl_params(self, ctx:IDL_GrammarParser.Annotation_appl_paramsContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#annotation_appl_param.
    def enterAnnotation_appl_param(self, ctx:IDL_GrammarParser.Annotation_appl_paramContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#annotation_appl_param.
    def exitAnnotation_appl_param(self, ctx:IDL_GrammarParser.Annotation_appl_paramContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#struct_dcl.
    def enterStruct_dcl(self, ctx:IDL_GrammarParser.Struct_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#struct_dcl.
    def exitStruct_dcl(self, ctx:IDL_GrammarParser.Struct_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#struct_def.
    def enterStruct_def(self, ctx:IDL_GrammarParser.Struct_defContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#struct_def.
    def exitStruct_def(self, ctx:IDL_GrammarParser.Struct_defContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#struct_forward_dcl.
    def enterStruct_forward_dcl(self, ctx:IDL_GrammarParser.Struct_forward_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#struct_forward_dcl.
    def exitStruct_forward_dcl(self, ctx:IDL_GrammarParser.Struct_forward_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#member_list.
    def enterMember_list(self, ctx:IDL_GrammarParser.Member_listContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#member_list.
    def exitMember_list(self, ctx:IDL_GrammarParser.Member_listContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#member.
    def enterMember(self, ctx:IDL_GrammarParser.MemberContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#member.
    def exitMember(self, ctx:IDL_GrammarParser.MemberContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#union_dcl.
    def enterUnion_dcl(self, ctx:IDL_GrammarParser.Union_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#union_dcl.
    def exitUnion_dcl(self, ctx:IDL_GrammarParser.Union_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#union_def.
    def enterUnion_def(self, ctx:IDL_GrammarParser.Union_defContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#union_def.
    def exitUnion_def(self, ctx:IDL_GrammarParser.Union_defContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#union_forward_dcl.
    def enterUnion_forward_dcl(self, ctx:IDL_GrammarParser.Union_forward_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#union_forward_dcl.
    def exitUnion_forward_dcl(self, ctx:IDL_GrammarParser.Union_forward_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#switch_type_spec.
    def enterSwitch_type_spec(self, ctx:IDL_GrammarParser.Switch_type_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#switch_type_spec.
    def exitSwitch_type_spec(self, ctx:IDL_GrammarParser.Switch_type_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#switch_body.
    def enterSwitch_body(self, ctx:IDL_GrammarParser.Switch_bodyContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#switch_body.
    def exitSwitch_body(self, ctx:IDL_GrammarParser.Switch_bodyContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#case.
    def enterCase(self, ctx:IDL_GrammarParser.CaseContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#case.
    def exitCase(self, ctx:IDL_GrammarParser.CaseContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#case_label.
    def enterCase_label(self, ctx:IDL_GrammarParser.Case_labelContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#case_label.
    def exitCase_label(self, ctx:IDL_GrammarParser.Case_labelContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#element_spec.
    def enterElement_spec(self, ctx:IDL_GrammarParser.Element_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#element_spec.
    def exitElement_spec(self, ctx:IDL_GrammarParser.Element_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#enum_dcl.
    def enterEnum_dcl(self, ctx:IDL_GrammarParser.Enum_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#enum_dcl.
    def exitEnum_dcl(self, ctx:IDL_GrammarParser.Enum_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#enumerator_list.
    def enterEnumerator_list(self, ctx:IDL_GrammarParser.Enumerator_listContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#enumerator_list.
    def exitEnumerator_list(self, ctx:IDL_GrammarParser.Enumerator_listContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#enumerator.
    def enterEnumerator(self, ctx:IDL_GrammarParser.EnumeratorContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#enumerator.
    def exitEnumerator(self, ctx:IDL_GrammarParser.EnumeratorContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#string_type.
    def enterString_type(self, ctx:IDL_GrammarParser.String_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#string_type.
    def exitString_type(self, ctx:IDL_GrammarParser.String_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#positive_int_const.
    def enterPositive_int_const(self, ctx:IDL_GrammarParser.Positive_int_constContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#positive_int_const.
    def exitPositive_int_const(self, ctx:IDL_GrammarParser.Positive_int_constContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#sequence_type.
    def enterSequence_type(self, ctx:IDL_GrammarParser.Sequence_typeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#sequence_type.
    def exitSequence_type(self, ctx:IDL_GrammarParser.Sequence_typeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#array_declarator.
    def enterArray_declarator(self, ctx:IDL_GrammarParser.Array_declaratorContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#array_declarator.
    def exitArray_declarator(self, ctx:IDL_GrammarParser.Array_declaratorContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#fixed_array_size.
    def enterFixed_array_size(self, ctx:IDL_GrammarParser.Fixed_array_sizeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#fixed_array_size.
    def exitFixed_array_size(self, ctx:IDL_GrammarParser.Fixed_array_sizeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#op_dcl.
    def enterOp_dcl(self, ctx:IDL_GrammarParser.Op_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#op_dcl.
    def exitOp_dcl(self, ctx:IDL_GrammarParser.Op_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#operation_type_spec.
    def enterOperation_type_spec(self, ctx:IDL_GrammarParser.Operation_type_specContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#operation_type_spec.
    def exitOperation_type_spec(self, ctx:IDL_GrammarParser.Operation_type_specContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#parameter_dcls.
    def enterParameter_dcls(self, ctx:IDL_GrammarParser.Parameter_dclsContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#parameter_dcls.
    def exitParameter_dcls(self, ctx:IDL_GrammarParser.Parameter_dclsContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#param_dcl.
    def enterParam_dcl(self, ctx:IDL_GrammarParser.Param_dclContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#param_dcl.
    def exitParam_dcl(self, ctx:IDL_GrammarParser.Param_dclContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#param_attribute.
    def enterParam_attribute(self, ctx:IDL_GrammarParser.Param_attributeContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#param_attribute.
    def exitParam_attribute(self, ctx:IDL_GrammarParser.Param_attributeContext):
        pass


    # Enter a parse tree produced by IDL_GrammarParser#identifier.
    def enterIdentifier(self, ctx:IDL_GrammarParser.IdentifierContext):
        pass

    # Exit a parse tree produced by IDL_GrammarParser#identifier.
    def exitIdentifier(self, ctx:IDL_GrammarParser.IdentifierContext):
        pass



del IDL_GrammarParser
