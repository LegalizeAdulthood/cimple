%{

#include "MOF_Config.h"
#include "MOF_Literal.h"
#include "MOF_Object_Reference.h"
#include "REF_Parser.h"
#include "REF_Yacc.h"
#include "MOF_Yacc.h"

extern int REF_lex();
static void REF_trace(const char* str);
extern void REF_error(const char* message);

%}

%union
{
    MOF_char16 char_value;
    char* string_value;
    MOF_sint64 int_value;
    int bool_value;
    double real_value;

    class MOF_Literal* literal;
    class MOF_Key_Value_Pair* key_val_pair;
    class MOF_Object_Reference* obj_ref;
}

%start start

%token REF_TOK_NULL_VALUE
%token REF_TOK_INT_VALUE
%token REF_TOK_BOOL_VALUE
%token REF_TOK_REAL_VALUE
%token REF_TOK_STRING_VALUE
%token REF_TOK_CHAR_VALUE
%token REF_TOK_BOOL_VALUE
%token REF_TOK_IDENT
%token REF_TOK_COMMA
%token REF_TOK_COLON
%token REF_TOK_EQUAL
%token REF_TOK_DOT
%token REF_TOK_OPEN_BRACE
%token REF_TOK_CLOSE_BRACE

%type <int_value> REF_TOK_INT_VALUE
%type <real_value> REF_TOK_REAL_VALUE
%type <string_value> REF_TOK_STRING_VALUE
%type <char_value> REF_TOK_CHAR_VALUE
%type <bool_value> REF_TOK_BOOL_VALUE
%type <string_value> REF_TOK_IDENT
%type <literal> value
%type <literal> value_list
%type <literal> value_array
%type <key_val_pair> key_val_pair
%type <key_val_pair> key_val_pair_list
%type <obj_ref> model_path
%type <string_value> multi_string

%%

start
    : model_path
    {
	REF_trace("start:1");
	ref_obj_ref = $1;
    }

model_path
    : REF_TOK_IDENT REF_TOK_DOT key_val_pair_list
    {
	REF_trace("model_path:1");
	$$ = new MOF_Object_Reference();
	MOF_ASSERT($$ != NULL);
	$$->class_name = $1;
	$$->pairs = $3;
    }
    | REF_TOK_IDENT
    {
	REF_trace("model_path:2");
	$$ = new MOF_Object_Reference();
	MOF_ASSERT($$ != NULL);
	$$->class_name = $1;
	$$->pairs = NULL;
    }
    ;

key_val_pair_list
    : key_val_pair
    {
	REF_trace("key_val_pair_list:1");
	$$ = $1;
    }
    | key_val_pair_list REF_TOK_COMMA key_val_pair
    {
	REF_trace("key_val_pair_list:2");
	$1->append($3);
	$$ = $1;
    }
    ;

key_val_pair
    : REF_TOK_IDENT REF_TOK_EQUAL value
    {
	REF_trace("key_val_pair:2");

	$$ = new MOF_Key_Value_Pair();
	MOF_ASSERT($$ != NULL);
	$$->key = $1;
	$$->value = $3;
	$$->is_array = false;
    }
    | REF_TOK_IDENT REF_TOK_EQUAL value_array
    {
	REF_trace("key_val_pair:2");

	$$ = new MOF_Key_Value_Pair();
	MOF_ASSERT($$ != NULL);
	$$->key = $1;
	$$->value = $3;
	$$->is_array = true;
    }
    ;

value_array 
    : REF_TOK_OPEN_BRACE value_list REF_TOK_CLOSE_BRACE
    {
	REF_trace("value_array:1");
	$$ = $2;
    }
    ;

value_list 
    : value
    {
	REF_trace("value_list:1");
	$$ = $1;
    }
    | value_list REF_TOK_COMMA value
    {
	REF_trace("value_list:2");
	$1->append($3);
	$$ = $1;
    }
    ;
    
value
    : REF_TOK_INT_VALUE
    {
	REF_trace("literal:1");
	$$ = new MOF_Literal();
	MOF_ASSERT($$ != NULL);
	$$->value_type = TOK_INT_VALUE;
	$$->int_value = $1;
    }
    | REF_TOK_REAL_VALUE
    {
	REF_trace("literal:2");
	$$ = new MOF_Literal();
	MOF_ASSERT($$ != NULL);
	$$->value_type = TOK_REAL_VALUE;
	$$->real_value = $1;
    }
    | REF_TOK_CHAR_VALUE
    {
	REF_trace("literal:3");
	$$ = new MOF_Literal();
	MOF_ASSERT($$ != NULL);
	$$->value_type = TOK_CHAR_VALUE;
	$$->char_value = $1;
    }
    | REF_TOK_BOOL_VALUE
    {
	REF_trace("literal:4");
	$$ = new MOF_Literal();
	MOF_ASSERT($$ != NULL);
	$$->value_type = TOK_BOOL_VALUE;
	$$->bool_value = $1 ? true : false;
    }
    | multi_string
    {
	REF_trace("literal:6");
	$$ = new MOF_Literal();
	MOF_ASSERT($$ != NULL);
	$$->value_type = TOK_STRING_VALUE;
	$$->string_value = $1;
    }
    | REF_TOK_NULL_VALUE
    {
	REF_trace("literal:5");
	$$ = new MOF_Literal();
	MOF_ASSERT($$ != NULL);
	$$->value_type = TOK_NULL_VALUE;
    }
    ;                              

multi_string 
    : REF_TOK_STRING_VALUE
    {
	REF_trace("multi_string:1");
	$$ = $1;
    }
    | multi_string REF_TOK_STRING_VALUE
    {
	size_t n1 = strlen($1);
	size_t n2 = strlen($2);

	REF_trace("multi_string:2");

	$$ = (char*)realloc($1, n1 + n2 + 16);
	MOF_ASSERT($$ != NULL);

	strcat($$, $2);
	free($2);
    }
    ;

%%

static void REF_trace(const char* str)
{
#if 0
    printf("REF_trace(): \"%s\"\n", str);
#endif
}
