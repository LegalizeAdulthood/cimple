TOP = ../..
include $(TOP)/mak/config.mak

STATIC_LIBRARY = cimplemof

INCLUDES += -I.

DEFINES += -DMOF_INTERNAL

LEX_AND_YACC_SOURCES = \
    MOF_Yacc.cpp \
    MOF_Lex.cpp \
    REF_Yacc.cpp \
    REF_Lex.cpp

SOURCES = \
    $(LEX_AND_YACC_SOURCES) \
    MOF_Buffer.cpp \
    MOF_Class_Decl.cpp \
    MOF_Data_Type.cpp \
    MOF_Element.cpp \
    MOF_Error.cpp \
    MOF_Feature.cpp \
    MOF_Feature_Info.cpp \
    MOF_Flavor.cpp \
    MOF_Indent.cpp \
    MOF_Instance_Decl.cpp \
    MOF_Key_Value_Pair.cpp \
    MOF_Lex_Utils.cpp \
    MOF_Literal.cpp \
    MOF_Method_Decl.cpp \
    MOF_Named_Element.cpp \
    MOF_Object_Reference.cpp \
    MOF_Options.cpp \
    MOF_Parameter.cpp \
    MOF_Parser.cpp \
    MOF_Pragma.cpp \
    MOF_Property.cpp \
    MOF_Property_Decl.cpp \
    MOF_Qualified_Element.cpp \
    MOF_Qualifier.cpp \
    MOF_Qualifier_Decl.cpp \
    MOF_Qualifier_Info.cpp \
    MOF_Reference_Decl.cpp \
    MOF_String.cpp \
    REF_Parser.cpp

include $(TOP)/mak/rules.mak

## Turn this flag to 1 to execute generate of Yacc and Lex
GEN=0
ifeq ($(GEN),1)

MOF_Yacc.cpp : MOF.y
	bison -d -p MOF_ -o MOF_Yacc.cpp MOF.y
	mv MOF_Yacc.hpp MOF_Yacc.h

MOF_Lex.cpp : MOF.l
	flex -PMOF_ -oMOF_Lex.cpp MOF.l

REF_Yacc.cpp : REF.y
	bison -d -p REF_ -o REF_Yacc.cpp REF.y
	mv REF_Yacc.hpp REF_Yacc.h

REF_Lex.cpp : REF.l
	flex -PREF_ -oREF_Lex.cpp REF.l

CLEAN += \
    REF_Yacc.h \
    REF_Yacc.cpp \
    REF_Lex.cpp \
    MOF_Yacc.h \
    MOF_Yacc.cpp \
    MOF_Lex.cpp

endif
