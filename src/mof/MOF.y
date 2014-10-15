%{

#include <cassert>
#include "MOF_Types.h"
#include "REF_Parser.h"

extern int MOF_lex();

static void MOF_trace(const char* str);

%}

%union
{
    MOF_char16 char_value;
    struct MOF_String_Literal
    {
        char* raw;
        char* escaped;
    }
    string_literal;
    char* string_value;
    MOF_sint64 int_value;
    int bool_value;
    double real_value;
    MOF_mask flavor;
    MOF_mask scope;

    class MOF_Class_Decl* class_decl;
    class MOF_Qualifier_Decl* qual_decl;
    class MOF_Class_Decl* struct_decl;
    class MOF_Feature* feature;
    class MOF_Literal* literal;
    class MOF_Instance_Decl* inst_decl;
    class MOF_Property* prop;
    class MOF_Property_Decl* prop_decl;
    class MOF_Qualifier* qual;
    class MOF_Reference_Decl* ref_decl;
    class MOF_Parameter* param;
    class MOF_Method_Decl* method_decl;
    class MOF_Object_Reference* obj_ref;

    struct _ref_init
    {
      char* alias;
      class MOF_Object_Reference* obj_ref;
    }
    ref_init;

    struct _decl_init
    {
        int array_index;
        class MOF_Literal* initializer;
    }
    decl_init;
}

%start start

%token TOK_ALIAS_IDENT
%token TOK_ANY
%token TOK_AS
%token TOK_ASSOCIATION
%token TOK_BOOLEAN
%token TOK_CHAR16
%token TOK_CHAR_VALUE
%token TOK_CLASS
%token TOK_CLOSE_BRACE
%token TOK_CLOSE_BRACKET
%token TOK_CLOSE_PAREN
%token TOK_COLON
%token TOK_COMMA
%token TOK_DATETIME
%token TOK_DISABLEOVERRIDE
%token TOK_ENABLEOVERRIDE
%token TOK_EQUAL
%token TOK_FLAVOR
%token TOK_IDENT
%token TOK_INDICATION
%token TOK_INSTANCE
%token TOK_METHOD
%token TOK_NULL_VALUE
%token TOK_OF
%token TOK_OPEN_BRACE
%token TOK_OPEN_BRACKET
%token TOK_OPEN_PAREN
%token TOK_PARAMETER
%token TOK_PRAGMA
%token TOK_PROPERTY
%token TOK_QUALIFIER
%token TOK_REAL32
%token TOK_REAL64
%token TOK_REAL_VALUE
%token TOK_REF
%token TOK_REFERENCE
%token TOK_RESTRICTED
%token TOK_SCHEMA
%token TOK_SCOPE
%token TOK_SEMICOLON
%token TOK_SINT16
%token TOK_SINT32
%token TOK_SINT64
%token TOK_SINT8
%token TOK_STRING
%token TOK_STRING_VALUE
%token TOK_TOSUBCLASS
%token TOK_TRANSLATABLE
%token TOK_BOOL_VALUE
%token TOK_INT_VALUE
%token TOK_UINT16
%token TOK_UINT32
%token TOK_UINT64
%token TOK_UINT8
%token TOK_STRING

%type <bool_value> TOK_BOOLEAN
%type <bool_value> TOK_BOOL_VALUE
%type <char_value> TOK_CHAR_VALUE
%type <class_decl> class_decl
%type <class_decl> class_head
%type <feature> class_body
%type <feature> feature
%type <feature> feature_list
%type <decl_init> prop_decl_array_init
%type <decl_init> prop_decl_body
%type <decl_init> prop_decl_scalar_init
%type <decl_init> qual_decl_array_init 
%type <decl_init> qual_decl_init
%type <decl_init> qual_decl_scalar_init
%type <flavor> flavor 
%type <flavor> flavor_list
%type <flavor> qual_decl_flavor 
%type <flavor> qual_flavor 
%type <flavor> qual_flavor_list
%type <prop> inst_body
%type <inst_decl> inst_decl
%type <inst_decl> inst_head
%type <int_value> array_index
%type <int_value> data_type
%type <int_value> param_body; 
%type <int_value> TOK_CHAR16
%type <int_value> TOK_DATETIME
%type <int_value> TOK_INT_VALUE
%type <int_value> TOK_REAL32
%type <int_value> TOK_REAL64
%type <int_value> TOK_SINT16
%type <int_value> TOK_SINT32
%type <int_value> TOK_SINT64
%type <int_value> TOK_SINT8
%type <int_value> TOK_STRING
%type <int_value> TOK_UINT16
%type <int_value> TOK_UINT32
%type <int_value> TOK_UINT64
%type <int_value> TOK_UINT8
%type <literal> array_init
%type <literal> init
%type <literal> literal; 
%type <literal> qual_param;
%type <literal> scalar_init_list
%type <literal> TOK_NULL_VALUE
%type <method_decl> method_decl
%type <method_decl> method_head
%type <param> method_body
%type <param> param
%type <param> param_data_type
%type <param> param_head
%type <param> param_list
%type <prop_decl> prop_decl
%type <prop_decl> prop_decl_head
%type <prop> prop
%type <prop> prop_body
%type <prop> prop_list
%type <qual> qual
%type <qual> qual_list
%type <qual> qual_list_body
%type <real_value> TOK_REAL_VALUE
%type <ref_decl> ref_decl;
%type <ref_decl> ref_head;
%type <ref_init> ref_body;
%type <ref_init> ref_init;
%type <scope> qual_decl_scope
%type <scope> scope
%type <scope> scope_list
%type <string_value> class_alias
%type <string_value> inst_alias
%type <string_literal> string_literal
%type <string_value> name
%type <obj_ref> obj_ref; 
%type <string_value> object_ref;
%type <string_value> super_class_name
%type <string_value> pragma_name
%type <string_literal> pragma_param
%type <string_value> TOK_ALIAS_IDENT
%type <string_value> TOK_IDENT
%type <string_value> TOK_SCHEMA
%type <string_literal> TOK_STRING_VALUE
%type <string_value> TOK_ASSOCIATION
%type <string_value> TOK_INDICATION
%type <string_value> TOK_REFERENCE
%type <qual_decl> qual_decl_body
%type <qual_decl> qual_decl

%%

/*
**==============================================================================
**
** MOF_specification:
**
**==============================================================================
*/

start
    : MOF_specification
    {
        /* printf("start rule reached\n"); */
    }

MOF_specification 
    : /* empty */
    {
        MOF_trace("MOF_specification:1");
    }
    | MOF_productions
    {
        MOF_trace("MOF_specification:2");
    }
    ;

MOF_productions 
    : MOF_production
    {
        MOF_trace("MOF_productions:1");
    }
    | MOF_productions MOF_production
    {
        MOF_trace("MOF_productions:2");
    }
    ;

MOF_production 
    : compiler_directive
    {
        MOF_trace("MOF_production:1");
        // MOF_warning_printf("pragma ignored");
    }
    | class_decl
    {
        MOF_trace("MOF_production:3");
        MOF_Class_Decl::handle($1);
    }
    | qual_decl
    {
        MOF_trace("MOF_production:4");
        MOF_Qualifier_Decl::handle($1);
    }
    | inst_decl
    {
        MOF_trace("MOF_production:5");
        MOF_Instance_Decl::handle($1);
    }
    ;

/*
**==============================================================================
**
** compiler_directive:
**
**==============================================================================
*/

compiler_directive 
    : TOK_PRAGMA pragma_name TOK_OPEN_PAREN pragma_param TOK_CLOSE_PAREN
    {
        MOF_Pragma::handle($2, $4.raw);
    }
    ;

pragma_name
    : TOK_IDENT
    {
        $$ = $1;
    }
    ;

pragma_param
    : string_literal
    {
        $$ = $1;
    }
    ;

/*
**==============================================================================
**
** name:
**
**     This production represents legal names for qualifiers, properties,
**     methods, params, references. Note that it is legal to have a
**     qualifier named "indication" and a property named "reference", or
**     a param called "source". This at first may seem odd.
**
**==============================================================================
*/

name 
    : TOK_IDENT 
    {
        MOF_trace("name:1");
        /* heap string */
        $$ = $1;
    }
    | TOK_SCHEMA
    {
        MOF_trace("name:2");
        $$ = strdup($1);
        MOF_ASSERT($$ != NULL);
    }
    | TOK_ASSOCIATION
    {
        MOF_trace("name:3");
        $$ = strdup($1);
        MOF_ASSERT($$ != NULL);
    }
    | TOK_INDICATION
    {
        MOF_trace("name:4");
        $$ = strdup($1);
        MOF_ASSERT($$ != NULL);
    }
    | TOK_REFERENCE
    {
        MOF_trace("name:5");
        $$ = strdup($1);
        MOF_ASSERT($$ != NULL);
    }
    ;

/*
**==============================================================================
**
** qual_decl:
**
**==============================================================================
*/

qual_decl
    : TOK_QUALIFIER qual_decl_body TOK_SEMICOLON
    {
        MOF_trace("qual_decl:1");
        $$ = $2;
    }
    ;

qual_decl_body 
    : name TOK_COLON data_type qual_decl_init qual_decl_scope qual_decl_flavor
    {
        MOF_trace("qual_decl_body:1");
        $$ = new MOF_Qualifier_Decl();
        MOF_ASSERT($$ != NULL);
        $$->name = $1;
        $$->data_type = (int)$3;
        $$->array_index = $4.array_index;
        $$->initializer = $4.initializer;
        $$->scope = $5;
        $$->flavor = MOF_Flavor::fixup($6, true);
    }
    ;

qual_decl_init 
    : qual_decl_array_init
    {
        MOF_trace("qual_decl_init:1");
        $$ = $1;
    }
    | qual_decl_scalar_init
    {
        MOF_trace("qual_decl_init:2");
        $$ = $1;
    }
    ;

qual_decl_array_init 
    : array_index TOK_EQUAL array_init
    {
        MOF_trace("qual_decl_array_init:1");
        $$.array_index = (int)$1;
        $$.initializer = $3;
    }
    | array_index
    {
        MOF_trace("qual_decl_array_init:2");
        $$.array_index = (int)$1;
        $$.initializer = NULL;
    }
    ;

qual_decl_scalar_init 
    : TOK_EQUAL literal
    {
        MOF_trace("qual_decl_scalar_init:1");
        $$.array_index = 0;
        $$.initializer = $2;
    }
    | /* empty */
    {
        MOF_trace("qual_decl_scalar_init:2");
        $$.array_index = 0;
        $$.initializer = NULL;
    }
    ;

qual_decl_scope 
    : TOK_COMMA TOK_SCOPE TOK_OPEN_PAREN scope_list TOK_CLOSE_PAREN
    {
        MOF_trace("qual_decl_scope:1");
        $$ = $4;
    }
    ;

scope_list 
    : scope
    {
        MOF_trace("scope_list:1");
        $$ = $1;
    }
    | scope_list TOK_COMMA scope
    {
        MOF_trace("scope_list:2");
        $$ |= $3;
    }
    ;

scope 
    : TOK_SCHEMA
    {
        MOF_trace("scope:1");
        $$ = MOF_SCOPE_SCHEMA;
    }
    | TOK_CLASS
    {
        MOF_trace("scope:2");
        $$ = MOF_SCOPE_CLASS;
    }
    | TOK_ASSOCIATION
    {
        MOF_trace("scope:3");
        $$ = MOF_SCOPE_ASSOCIATION;
    }
    | TOK_INDICATION
    {
        MOF_trace("scope:4");
        $$ = MOF_SCOPE_INDICATION;
    }
    | TOK_PROPERTY
    {
        MOF_trace("scope:5");
        $$ = MOF_SCOPE_PROPERTY;
    }
    | TOK_REFERENCE
    {
        MOF_trace("scope:6");
        $$ = MOF_SCOPE_REFERENCE;
    }
    | TOK_METHOD
    {
        MOF_trace("scope:7");
        $$ = MOF_SCOPE_METHOD;
    }
    | TOK_PARAMETER
    {
        MOF_trace("scope:8");
        $$ = MOF_SCOPE_PARAMETER;
    }
    | TOK_ANY
    {
        MOF_trace("scope:9");
        $$ = MOF_SCOPE_ANY;
    }
    ;

qual_decl_flavor 
    : TOK_COMMA TOK_FLAVOR TOK_OPEN_PAREN flavor_list TOK_CLOSE_PAREN
    {
        MOF_trace("qual_decl_flavor:1");
        $$ = $4;
    }
    | /* empty */
    {
        MOF_trace("qual_decl_flavor:2");
        $$ = 0;
    }
    ;

flavor_list 
    : flavor
    {
        MOF_trace("flavor_list:1");
        $$ = $1;
    }
    | flavor_list TOK_COMMA flavor
    {
        MOF_trace("flavor_list:2");
        $$ = $1;
        $$ |= $3;
    }
    ;

flavor 
    : TOK_ENABLEOVERRIDE
    {
        MOF_trace("flavor:1");
        $$ = MOF_FLAVOR_ENABLEOVERRIDE;
    }
    | TOK_DISABLEOVERRIDE
    {
        MOF_trace("flavor:2");
        $$ = MOF_FLAVOR_DISABLEOVERRIDE;
    }
    | TOK_RESTRICTED
    {
        MOF_trace("flavor:3");
        $$ = MOF_FLAVOR_RESTRICTED;
    }
    | TOK_TOSUBCLASS
    {
        MOF_trace("flavor:4");
        $$ = MOF_FLAVOR_TOSUBCLASS;
    }
    | TOK_TRANSLATABLE
    {
        MOF_trace("flavor:5");
        $$ = MOF_FLAVOR_TRANSLATABLE;
    }
    ;

/*
**==============================================================================
**
** qual_list:
**
**==============================================================================
*/

qual_list 
    : TOK_OPEN_BRACKET qual_list_body TOK_CLOSE_BRACKET
    {
        $$ = $2;
        MOF_trace("qual_list:1");
    }
    ;

qual_list_body 
    : qual 
    {
        MOF_trace("qual_list_body:1");
        $1->validate();
        $$ = $1;
    }
    | qual_list_body TOK_COMMA qual
    {
        MOF_trace("qual_list_body:2");
        $3->validate();
        $1->append($3);
        $$ = $1;
    }
    ;

qual 
    : name qual_param qual_flavor
    {
        MOF_trace("qual:1");
        $$ = new MOF_Qualifier();
        MOF_ASSERT($$ != NULL);
        $$->name = $1;
        $$->params = $2;
        $$->flavor = MOF_Flavor::fixup($3, false);
    }
    ;

qual_param 
    : TOK_OPEN_PAREN literal TOK_CLOSE_PAREN
    {
        MOF_trace("qual_param:1");
        $$ = $2;
    }
    | array_init
    {
        MOF_trace("qual_param:2");
        $$ = $1;
    }
    | /* empty */
    {
        MOF_trace("qual_param:3");
        $$ = NULL;
    }
    ;

qual_flavor 
    : TOK_COLON qual_flavor_list
    {
        MOF_trace("qual_flavor:1");
        $$ = $2;
    }
    | /* empty */
    {
        MOF_trace("qual_flavor:2");
        $$ = 0;
    }
    ;

qual_flavor_list 
    : flavor
    {
        MOF_trace("qual_flavor_list:1");
        $$ = $1;
    }
    | qual_flavor_list flavor
    {
        MOF_trace("qual_flavor_list:2");
        $$ = $1;
        $$ |= $2;
    }
    ;

/*
**==============================================================================
**
** class_decl:
**
**     ATTN: The specification grammar provides a class alias (so it can be
**     used as a reference-initializer). But there is no other mention of this
**     in the standard. Have class aliases fallen out of the standard?
**
**==============================================================================
*/

class_decl 
    : class_head class_body TOK_SEMICOLON
    {
        MOF_trace("class_decl:1");
        $$ = $1;
        $$->qualifiers = NULL;
        $$->features = $2;
    }
    | qual_list class_head class_body TOK_SEMICOLON
    {
        MOF_trace("class_decl:2");
        $$ = $2;
        $$->qualifiers = $1;
        $$->features = $3;
    }
    ;

class_head 
    : TOK_CLASS TOK_IDENT class_alias super_class_name
    {
        MOF_trace("class_head:1");
        $$ = new MOF_Class_Decl();
        MOF_ASSERT($$ != NULL);
        $$->name = $2;
        $$->alias = $3;
        $$->super_class_name = $4;
    }
    ;

class_body 
    : TOK_OPEN_BRACE feature_list TOK_CLOSE_BRACE
    {
        MOF_trace("class_body:1");
        $$ = $2;
    }
    ;

class_alias 
    : TOK_AS TOK_ALIAS_IDENT 
    {
        MOF_trace("class_alias:1");
        $$ = $2;
    }
    | /* empty */
    {
        MOF_trace("class_alias:2");
        $$ = NULL;
    }
    ;

super_class_name 
    : TOK_COLON TOK_IDENT
    {
        MOF_trace("super_class_name:1");
        $$ = $2;
    }
    | /* empty */
    {
        MOF_trace("super_class_name:2");
        $$ = NULL;
    }
    ;

feature_list 
    : /* empty */
    {
        MOF_trace("feature_list:1");
        $$ = NULL;
    }
    | feature_list feature
    {
        MOF_trace("feature_list:2");

        if ($1)
            $1->append($2);
        else
            $$ = $2;
    }
    ;

feature 
    : prop_decl
    {
        MOF_trace("feature:1");
        $$ = (MOF_Feature*)$1;
    }
    | ref_decl
    {
        MOF_trace("feature:2");
        $$ = (MOF_Feature*)$1;
    }
    | method_decl
    {
        MOF_trace("feature:3");
        $$ = (MOF_Feature*)$1;
    }
    ;

/*
**==============================================================================
**
** prop_decl:
**
**==============================================================================
*/

prop_decl 
    : prop_decl_head prop_decl_body TOK_SEMICOLON
    {
        MOF_trace("prop_decl:1");
        $$ = $1;
        $$->array_index = $2.array_index;
        $$->initializer = $2.initializer;
    }
    | qual_list prop_decl_head prop_decl_body TOK_SEMICOLON
    {
        MOF_trace("prop_decl:2");
        $1->validate_list(MOF_SCOPE_PROPERTY);
        $$ = $2;
        $$->qualifiers = $1;
        $$->array_index = $3.array_index;
        $$->initializer = $3.initializer;
    }
    ;

prop_decl_head 
    : data_type name
    {
        MOF_trace("prop_decl_head:1");
        $$ = new MOF_Property_Decl();
        MOF_ASSERT($$ != NULL);
        $$->type = MOF_FEATURE_PROP;
        $$->name = $2;
        $$->data_type = (int)$1;
    }
    ;

prop_decl_body 
    : prop_decl_array_init
    {
        MOF_trace("prop_decl_body:1");
        $$ = $1;
    }
    | prop_decl_scalar_init
    {
        MOF_trace("prop_decl_body:2");
        $$ = $1;
    }
    ;

prop_decl_array_init 
    : array_index TOK_EQUAL array_init
    {
        MOF_trace("prop_decl_array_init:1");
        $$.array_index = (int)$1;
        $$.initializer = $3;
    }
    | array_index
    {
        MOF_trace("prop_decl_array_init:2");
        $$.array_index = (int)$1;
        $$.initializer = NULL;
    }
    ;

prop_decl_scalar_init 
    : TOK_EQUAL literal
    {
        MOF_trace("prop_decl_scalar_init:1");
        $$.array_index = 0;
        $$.initializer = $2;
    }
    | /* empty */
    {
        MOF_trace("prop_decl_scalar_init:2");
        $$.array_index = 0;
        $$.initializer = NULL;
    }
    ;

/*
**==============================================================================
**
** ref_decl:
**
**==============================================================================
*/

ref_decl 
    : ref_head ref_body TOK_SEMICOLON
    {
        MOF_trace("ref_decl:1");
        $$ = $1;

        $$->alias = $2.alias;
        $$->obj_ref = $2.obj_ref;
        $$->qualifiers = NULL;
    }
    | qual_list ref_head ref_body TOK_SEMICOLON
    {
        MOF_trace("ref_decl:2");
        $1->validate_list(MOF_SCOPE_REFERENCE);
        $$ = $2;
        $$->qualifiers = $1;
        $$->alias = $3.alias;
        $$->obj_ref = $3.obj_ref;
    }
    ;

ref_head 
    : object_ref name
    {
        MOF_trace("ref_head:1");
        $$ = new MOF_Reference_Decl();
        MOF_ASSERT($$ != NULL);
        $$->class_name = $1;
        $$->type = MOF_FEATURE_REF;
        $$->name = $2;
    }

ref_body 
    : TOK_EQUAL ref_init
    {
        MOF_trace("ref_body:1");
        $$ = $2;
    }
    | /* empty */
    {
        MOF_trace("ref_body:2");
        $$.alias = NULL;
        $$.obj_ref = NULL;
    }
    ;

ref_init 
    : TOK_ALIAS_IDENT
    {
        MOF_trace("ref_init:1");

        /*
         * Create object reference for this alias (or at least try to):
         */

        $$.alias = NULL;
        $$.obj_ref = MOF_Instance_Decl::alias_to_obj_ref($1);
    }
    | obj_ref 
    {
        MOF_trace("ref_init:2");
        $$.alias = NULL;
        $$.obj_ref = $1;
    }
    ; 

/*
**==============================================================================
**
** method_decl:
**
**==============================================================================
*/

method_decl 
    : method_head method_body TOK_SEMICOLON
    {
        MOF_trace("method_decl:1");
        $$ = $1;
        $$->qualifiers = NULL;
        $$->parameters = $2;
    }
    | qual_list method_head method_body TOK_SEMICOLON
    {
        MOF_trace("method_decl:2");
        $1->validate_list(MOF_SCOPE_METHOD);
        $$ = $2;
        $$->qualifiers = $1;
        $$->parameters = $3;
    }
    ;

method_head 
    : data_type name
    {
        MOF_trace("method_head:1");
        $$ = new MOF_Method_Decl();
        MOF_ASSERT($$ != NULL);
        $$->type = MOF_FEATURE_METHOD;
        $$->name = $2;
        $$->data_type = (int)$1;
    }
    ;

method_body 
    : TOK_OPEN_PAREN param_list TOK_CLOSE_PAREN
    {
        MOF_trace("method_body:1");
        $$ = $2;
    }
    | TOK_OPEN_PAREN TOK_CLOSE_PAREN
    {
        MOF_trace("method_body:2");
        $$ = NULL;
    }
    ;

param_list 
    : param
    {
        MOF_trace("param_list:1");
        $$ = $1;
    }
    | param_list TOK_COMMA param
    {
        MOF_trace("param_list:2");
        $$ = $1;
        $$->append($3);
    }
    ;                    

/*
**==============================================================================
**
** param:
**
**==============================================================================
*/

param 
    : param_head param_body
    {
        MOF_trace("param:1");
        $$ = $1;
        $$->array_index = (int)$2;
    }
    | qual_list param_head param_body
    {
        MOF_trace("param:2");
        $1->validate_list(MOF_SCOPE_PARAMETER);
        $$ = $2;
        $$->qualifiers = $1;
        $$->array_index = (int)$3;
    }
    ;

param_head 
    : param_data_type name
    {
        MOF_trace("param_head:1");
        $$ = $1;
        $$->name = $2;
    }
    ;

param_body 
    : array_index
    {
        MOF_trace("param_body:1");
        $$ = $1;
    }
    | /* empty */
    {
        MOF_trace("param_body:2");
        /* It's not an array at all */
        $$ = 0;
    }
    ;

param_data_type 
    : data_type
    {
        MOF_trace("param_data_type:1");
        $$ = new MOF_Parameter();
        $$->data_type = (int)$1;
        $$->ref_name = NULL;
    }
    | object_ref
    {
        MOF_trace("param_data_type:2");
        $$ = new MOF_Parameter();
        $$->data_type = TOK_REF;
        $$->ref_name = $1;
    }
    ;

/*
**==============================================================================
**
** param:
**
**==============================================================================
*/

inst_decl 
    : inst_head inst_body TOK_SEMICOLON
    {
        MOF_trace("inst_decl:1");
        $$ = $1;
        $$->qualifiers = NULL;
        $$->properties = $2;
    }
    | qual_list inst_head inst_body TOK_SEMICOLON
    {
        MOF_trace("inst_decl:2");
        $1->validate_list(MOF_SCOPE_CLASS);
        $$ = $2;
        $$->qualifiers = $1;
        $$->properties = $3;
    }
    ;

inst_head 
    : TOK_INSTANCE TOK_OF TOK_IDENT inst_alias
    {
        MOF_trace("inst_head:1");
        $$ = new MOF_Instance_Decl();
        MOF_ASSERT($$ != NULL);
        $$->class_name = $3;
        $$->alias = $4;
    }
    ;

inst_body 
    : TOK_OPEN_BRACE prop_list TOK_CLOSE_BRACE
    {
        MOF_trace("inst_body:1");
        $$ = $2;
    }
    ;

inst_alias 
    : TOK_AS TOK_ALIAS_IDENT
    {
        MOF_trace("inst_alias:1");
        $$ = $2;
    }
    | /* empty */
    {
        MOF_trace("inst_alias:2");
        $$ = NULL;
    }
    ;

/*
**==============================================================================
**
** prop_list:
**
**==============================================================================
*/

prop_list 
    : prop
    {
        MOF_trace("prop_list:1");
        $$ = $1;
    }
    | prop_list prop
    {
        MOF_trace("prop_list:2");
        $1->append($2);
        $$ = $1;
    }
    ;

prop 
    : prop_body
    {
        MOF_trace("prop:1");
        $$ = $1;
        $$->qualifiers = NULL;
    }
    | qual_list prop_body
    {
        MOF_trace("prop:2");
        $1->validate_list(MOF_SCOPE_PROPERTY);
        $$ = $2;
        $$->qualifiers = $1;
    }
    ;

prop_body 
    : TOK_IDENT TOK_EQUAL init TOK_SEMICOLON
    {
        MOF_trace("prop_body:1");

        $$ = new MOF_Property();
        MOF_ASSERT($$ != NULL);
        $$->name = $1;
        $$->initializer = $3;
    }
    | TOK_IDENT TOK_EQUAL TOK_ALIAS_IDENT TOK_SEMICOLON
    {
        MOF_trace("prop_body:2");

        $$ = new MOF_Property();
        MOF_ASSERT($$ != NULL);
        $$->name = $1;
        $$->initializer = NULL;
        $$->alias = $3;
    }
    ;

/*
**==============================================================================
**
** object_ref:
**
**==============================================================================
*/

object_ref 
    : TOK_IDENT TOK_REF
    {
        MOF_trace("object_ref:1");
        $$ = $1;
    }
    ;

obj_ref 
    : string_literal
    {
        MOF_trace("obj_ref:1");

        if (REF_parse($1.escaped, &$$) != 0)
        {
            MOF_error_printf("malformed object reference: \"%s\": %s", 
                $1.escaped, ref_error_message);
        }

        {
            char* p = MOF_Object_Reference::normalize($1.escaped);
            MOF_ASSERT(p != NULL);
            free(p);
        }

        free($1.escaped);
        free($1.raw);
        $$->validate();
        $$->normalize();
        /* MOF_obj_ref_print(stdout, $$); */
    }
    ;

/*
**==============================================================================
**
** array_index:
**
**==============================================================================
*/

array_index 
    : TOK_OPEN_BRACKET TOK_CLOSE_BRACKET
    {
        MOF_trace("array_index:1");
        /* It's a varying length array (VLA) */
        $$ = -1;
    }
    | TOK_OPEN_BRACKET TOK_INT_VALUE TOK_CLOSE_BRACKET
    {
        MOF_trace("array_index:2");

        /* subscript must be positive */

        if ($2 <= 0)
            MOF_error("array subscript must be a positive number");

        $$ = $2;
    }
    ;

/*
**==============================================================================
**
** data_type:
**
**==============================================================================
*/

data_type 
    : TOK_UINT8
    {
        MOF_trace("data_type:1");
        $$ = TOK_UINT8;
    }
    | TOK_SINT8
    {
        MOF_trace("data_type:2");
        $$ = TOK_SINT8;
    }
    | TOK_UINT16
    {
        MOF_trace("data_type:3");
        $$ = TOK_UINT16;
    }
    | TOK_SINT16
    {
        MOF_trace("data_type:4");
        $$ = TOK_SINT16;
    }
    | TOK_UINT32
    {
        MOF_trace("data_type:5");
        $$ = TOK_UINT32;
    }
    | TOK_SINT32
    {
        MOF_trace("data_type:6");
        $$ = TOK_SINT32;
    }
    | TOK_UINT64
    {
        MOF_trace("data_type:7");
        $$ = TOK_UINT64;
    }
    | TOK_SINT64
    {
        MOF_trace("data_type:8");
        $$ = TOK_SINT64;
    }
    | TOK_REAL32
    {
        MOF_trace("data_type:9");
        $$ = TOK_REAL32;
    }
    | TOK_REAL64
    {
        MOF_trace("data_type:10");
        $$ = TOK_REAL64;
    }
    | TOK_CHAR16
    {
        MOF_trace("data_type:11");
        $$ = TOK_CHAR16;
    }
    | TOK_STRING
    {
        MOF_trace("data_type:12");
        $$ = TOK_STRING;
    }
    | TOK_BOOLEAN
    {
        MOF_trace("data_type:13");
        $$ = TOK_BOOLEAN;
    }
    | TOK_DATETIME
    {
        MOF_trace("data_type:14");
        $$ = TOK_DATETIME;
    }
    ;

/*
**==============================================================================
**
** init:
**
**==============================================================================
*/

init 
    : literal
    {
        MOF_trace("init:1");
        $$ = $1;
    }
    | array_init
    {
        MOF_trace("init:2");
        $$ = $1;
    }
    ;

array_init 
    : TOK_OPEN_BRACE scalar_init_list TOK_CLOSE_BRACE
    {
        MOF_trace("array_init:1");
        $$ = $2;
    }
    ;

scalar_init_list 
    : literal
    {
        MOF_trace("scalar_init_list:1");
        $$ = $1;
    }
    | scalar_init_list TOK_COMMA literal
    {
        MOF_trace("scalar_init_list:2");
        $1->append($3);
        $$ = $1;
    }
    ;
    
/*
**==============================================================================
**
** literal:
**
**==============================================================================
*/

literal 
    : TOK_INT_VALUE
    {
        MOF_trace("literal:1");
        $$ = new MOF_Literal();
        MOF_ASSERT($$ != NULL);
        $$->value_type = TOK_INT_VALUE;
        $$->int_value = $1;
    }
    | TOK_REAL_VALUE
    {
        MOF_trace("literal:2");
        $$ = new MOF_Literal();
        MOF_ASSERT($$ != NULL);
        $$->value_type = TOK_REAL_VALUE;
        $$->real_value = $1;
    }
    | TOK_CHAR_VALUE
    {
        MOF_trace("literal:3");
        $$ = new MOF_Literal();
        MOF_ASSERT($$ != NULL);
        $$->value_type = TOK_CHAR_VALUE;
        $$->char_value = $1;
    }
    | TOK_BOOL_VALUE
    {
        MOF_trace("literal:4");
        $$ = new MOF_Literal();
        MOF_ASSERT($$ != NULL);
        $$->value_type = TOK_BOOL_VALUE;
        $$->bool_value = $1 ? true : false;
    }
    | string_literal
    {
        MOF_trace("literal:6");
        $$ = new MOF_Literal();
        MOF_ASSERT($$ != NULL);
        $$->value_type = TOK_STRING_VALUE;
        $$->string_value = $1.escaped;
        free($1.raw);
    }
    | TOK_NULL_VALUE
    {
        MOF_trace("literal:5");
        $$ = new MOF_Literal();
        MOF_ASSERT($$ != NULL);
        $$->value_type = TOK_NULL_VALUE;
    }
    ;                              

/*
**==============================================================================
**
** string_literal:
**
**==============================================================================
*/

string_literal 
    : TOK_STRING_VALUE
    {
        MOF_trace("string_literal:1");
        $$ = $1;
    }
    | string_literal TOK_STRING_VALUE
    {
        /* Raw case */
        {
            size_t n1 = strlen($1.raw);
            size_t n2 = strlen($2.raw);

            MOF_trace("string_literal:2");

            $$.raw = (char*)realloc($1.raw, n1 + n2 + 16);
            MOF_ASSERT($$.raw != NULL);

            strcat($$.raw, $2.raw);
            free($2.raw);
        }

        /* Escaped case */
        {
            size_t n1 = strlen($1.escaped);
            size_t n2 = strlen($2.escaped);

            MOF_trace("string_literal:2");

            $$.escaped = (char*)realloc($1.escaped, n1 + n2 + 16);
            MOF_ASSERT($$.escaped != NULL);

            strcat($$.escaped, $2.escaped);
            free($2.escaped);
        }
    }
    ;

%%

/*
**==============================================================================
**
** MOF_trace():  Ouputs statements for detailed debug of yacc progress
**
**==============================================================================
*/

static void MOF_trace(const char* str)
{
#if MOF_DEBUG_MODE
    printf("MOF_trace(): \"%s\"\n", str);
#endif
}

