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

# This class defines a complete generic visitor for a parse tree produced by IDL_GrammarParser.

class IDL_GrammarVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by IDL_GrammarParser#specification.
    def visitSpecification(self, ctx:IDL_GrammarParser.SpecificationContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#definition.
    def visitDefinition(self, ctx:IDL_GrammarParser.DefinitionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#module_dcl.
    def visitModule_dcl(self, ctx:IDL_GrammarParser.Module_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#module_contents.
    def visitModule_contents(self, ctx:IDL_GrammarParser.Module_contentsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#module_content.
    def visitModule_content(self, ctx:IDL_GrammarParser.Module_contentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_dcl.
    def visitInterface_dcl(self, ctx:IDL_GrammarParser.Interface_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_forward_dcl.
    def visitInterface_forward_dcl(self, ctx:IDL_GrammarParser.Interface_forward_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_def.
    def visitInterface_def(self, ctx:IDL_GrammarParser.Interface_defContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_header.
    def visitInterface_header(self, ctx:IDL_GrammarParser.Interface_headerContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_kind.
    def visitInterface_kind(self, ctx:IDL_GrammarParser.Interface_kindContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_inheritance_spec.
    def visitInterface_inheritance_spec(self, ctx:IDL_GrammarParser.Interface_inheritance_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_body.
    def visitInterface_body(self, ctx:IDL_GrammarParser.Interface_bodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#export_dcl.
    def visitExport_dcl(self, ctx:IDL_GrammarParser.Export_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#interface_name.
    def visitInterface_name(self, ctx:IDL_GrammarParser.Interface_nameContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#scoped_name.
    def visitScoped_name(self, ctx:IDL_GrammarParser.Scoped_nameContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#annotated_scoped_name.
    def visitAnnotated_scoped_name(self, ctx:IDL_GrammarParser.Annotated_scoped_nameContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#initialization_parameter_declaration.
    def visitInitialization_parameter_declaration(self, ctx:IDL_GrammarParser.Initialization_parameter_declarationContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#const_dcl.
    def visitConst_dcl(self, ctx:IDL_GrammarParser.Const_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#const_type.
    def visitConst_type(self, ctx:IDL_GrammarParser.Const_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#const_expr.
    def visitConst_expr(self, ctx:IDL_GrammarParser.Const_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#or_expr.
    def visitOr_expr(self, ctx:IDL_GrammarParser.Or_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#xor_expr.
    def visitXor_expr(self, ctx:IDL_GrammarParser.Xor_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#and_expr.
    def visitAnd_expr(self, ctx:IDL_GrammarParser.And_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#shift_expr.
    def visitShift_expr(self, ctx:IDL_GrammarParser.Shift_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#add_expr.
    def visitAdd_expr(self, ctx:IDL_GrammarParser.Add_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#mult_expr.
    def visitMult_expr(self, ctx:IDL_GrammarParser.Mult_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#unary_expr.
    def visitUnary_expr(self, ctx:IDL_GrammarParser.Unary_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#primary_expr.
    def visitPrimary_expr(self, ctx:IDL_GrammarParser.Primary_exprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#unary_operator.
    def visitUnary_operator(self, ctx:IDL_GrammarParser.Unary_operatorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#literal.
    def visitLiteral(self, ctx:IDL_GrammarParser.LiteralContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#type_dcl.
    def visitType_dcl(self, ctx:IDL_GrammarParser.Type_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#typedef_dcl.
    def visitTypedef_dcl(self, ctx:IDL_GrammarParser.Typedef_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#constr_type_dcl.
    def visitConstr_type_dcl(self, ctx:IDL_GrammarParser.Constr_type_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#type_declarator.
    def visitType_declarator(self, ctx:IDL_GrammarParser.Type_declaratorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#type_spec.
    def visitType_spec(self, ctx:IDL_GrammarParser.Type_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#simple_type_spec.
    def visitSimple_type_spec(self, ctx:IDL_GrammarParser.Simple_type_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#base_type_spec.
    def visitBase_type_spec(self, ctx:IDL_GrammarParser.Base_type_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#template_type_spec.
    def visitTemplate_type_spec(self, ctx:IDL_GrammarParser.Template_type_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#declarators.
    def visitDeclarators(self, ctx:IDL_GrammarParser.DeclaratorsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#declarator.
    def visitDeclarator(self, ctx:IDL_GrammarParser.DeclaratorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#simple_declarator.
    def visitSimple_declarator(self, ctx:IDL_GrammarParser.Simple_declaratorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#complex_declarator.
    def visitComplex_declarator(self, ctx:IDL_GrammarParser.Complex_declaratorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#floating_pt_type.
    def visitFloating_pt_type(self, ctx:IDL_GrammarParser.Floating_pt_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#float_type.
    def visitFloat_type(self, ctx:IDL_GrammarParser.Float_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#double_type.
    def visitDouble_type(self, ctx:IDL_GrammarParser.Double_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#long_double_type.
    def visitLong_double_type(self, ctx:IDL_GrammarParser.Long_double_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#integer_type.
    def visitInteger_type(self, ctx:IDL_GrammarParser.Integer_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#signed_int.
    def visitSigned_int(self, ctx:IDL_GrammarParser.Signed_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#signed_octet_int.
    def visitSigned_octet_int(self, ctx:IDL_GrammarParser.Signed_octet_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#signed_short_int.
    def visitSigned_short_int(self, ctx:IDL_GrammarParser.Signed_short_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#signed_long_int.
    def visitSigned_long_int(self, ctx:IDL_GrammarParser.Signed_long_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#signed_longlong_int.
    def visitSigned_longlong_int(self, ctx:IDL_GrammarParser.Signed_longlong_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#unsigned_int.
    def visitUnsigned_int(self, ctx:IDL_GrammarParser.Unsigned_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#unsigned_octet_int.
    def visitUnsigned_octet_int(self, ctx:IDL_GrammarParser.Unsigned_octet_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#unsigned_short_int.
    def visitUnsigned_short_int(self, ctx:IDL_GrammarParser.Unsigned_short_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#unsigned_long_int.
    def visitUnsigned_long_int(self, ctx:IDL_GrammarParser.Unsigned_long_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#unsigned_longlong_int.
    def visitUnsigned_longlong_int(self, ctx:IDL_GrammarParser.Unsigned_longlong_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#char_type.
    def visitChar_type(self, ctx:IDL_GrammarParser.Char_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#wide_char_type.
    def visitWide_char_type(self, ctx:IDL_GrammarParser.Wide_char_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#boolean_type.
    def visitBoolean_type(self, ctx:IDL_GrammarParser.Boolean_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#octet_type.
    def visitOctet_type(self, ctx:IDL_GrammarParser.Octet_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#annotation.
    def visitAnnotation(self, ctx:IDL_GrammarParser.AnnotationContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#annotation_appl.
    def visitAnnotation_appl(self, ctx:IDL_GrammarParser.Annotation_applContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#annotation_appl_params.
    def visitAnnotation_appl_params(self, ctx:IDL_GrammarParser.Annotation_appl_paramsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#annotation_appl_param.
    def visitAnnotation_appl_param(self, ctx:IDL_GrammarParser.Annotation_appl_paramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#struct_dcl.
    def visitStruct_dcl(self, ctx:IDL_GrammarParser.Struct_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#struct_def.
    def visitStruct_def(self, ctx:IDL_GrammarParser.Struct_defContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#struct_forward_dcl.
    def visitStruct_forward_dcl(self, ctx:IDL_GrammarParser.Struct_forward_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#member_list.
    def visitMember_list(self, ctx:IDL_GrammarParser.Member_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#member.
    def visitMember(self, ctx:IDL_GrammarParser.MemberContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#union_dcl.
    def visitUnion_dcl(self, ctx:IDL_GrammarParser.Union_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#union_def.
    def visitUnion_def(self, ctx:IDL_GrammarParser.Union_defContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#union_forward_dcl.
    def visitUnion_forward_dcl(self, ctx:IDL_GrammarParser.Union_forward_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#switch_type_spec.
    def visitSwitch_type_spec(self, ctx:IDL_GrammarParser.Switch_type_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#switch_body.
    def visitSwitch_body(self, ctx:IDL_GrammarParser.Switch_bodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#case.
    def visitCase(self, ctx:IDL_GrammarParser.CaseContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#case_label.
    def visitCase_label(self, ctx:IDL_GrammarParser.Case_labelContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#element_spec.
    def visitElement_spec(self, ctx:IDL_GrammarParser.Element_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#enum_dcl.
    def visitEnum_dcl(self, ctx:IDL_GrammarParser.Enum_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#enumerator_list.
    def visitEnumerator_list(self, ctx:IDL_GrammarParser.Enumerator_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#enumerator.
    def visitEnumerator(self, ctx:IDL_GrammarParser.EnumeratorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#string_type.
    def visitString_type(self, ctx:IDL_GrammarParser.String_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#positive_int_const.
    def visitPositive_int_const(self, ctx:IDL_GrammarParser.Positive_int_constContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#sequence_type.
    def visitSequence_type(self, ctx:IDL_GrammarParser.Sequence_typeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#array_declarator.
    def visitArray_declarator(self, ctx:IDL_GrammarParser.Array_declaratorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#fixed_array_size.
    def visitFixed_array_size(self, ctx:IDL_GrammarParser.Fixed_array_sizeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#op_dcl.
    def visitOp_dcl(self, ctx:IDL_GrammarParser.Op_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#operation_type_spec.
    def visitOperation_type_spec(self, ctx:IDL_GrammarParser.Operation_type_specContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#parameter_dcls.
    def visitParameter_dcls(self, ctx:IDL_GrammarParser.Parameter_dclsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#param_dcl.
    def visitParam_dcl(self, ctx:IDL_GrammarParser.Param_dclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#param_attribute.
    def visitParam_attribute(self, ctx:IDL_GrammarParser.Param_attributeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by IDL_GrammarParser#identifier.
    def visitIdentifier(self, ctx:IDL_GrammarParser.IdentifierContext):
        return self.visitChildren(ctx)



del IDL_GrammarParser
