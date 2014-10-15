%{

#include <string.h>
#include "MOF_Types.h"
#include "MOF_Parser.h"
#include "MOF_Yacc.h"
#include "MOF_Lex_Utils.h"

#define YY_NEVER_INTERACTIVE 1

/*
 * These are created and pushed on a stack when include pragmas are
 * encountered. And popped when the included file EOF is encountered.
 */
struct MOF_State
{
    char* file_name;
    int line_num;
    char* current_dir;
    YY_BUFFER_STATE buffer_state;
};

#define MAX_STATE_STACK_SIZE 10
static MOF_State state_stack[MAX_STATE_STACK_SIZE];
static size_t state_stack_size = 0;

extern int pop_include_file();

%}

/*
**------------------------------------------------------------------------------
**
** From CIM specification: Appendix A ("case insentive keywords").
**
**------------------------------------------------------------------------------
*/

ANY [aA][nN][yY]
AS [aA][sS]
ASSOCIATION [aA][sS][sS][oO][cC][iI][aA][tT][iI][oO][nN]
CLASS [cC][lL][aA][sS][sS]
DISABLEOVERRIDE [dD][iI][sS][aA][bB][lL][eE][oO][vV][eE][rR][rR][iI][dD][eE]
DT_BOOL [bB][oO][oO][lL][eE][aA][nN]
DT_CHAR16 [cC][hH][aA][rR]16
DT_DATETIME [dD][aA][tT][eE][tT][iI][mM][eE]
DT_REAL32 [rR][eE][aA][lL]32
DT_REAL64 [rR][eE][aA][lL]64
DT_SINT16 [sS][iI][nN][tT]16
DT_SINT32 [sS][iI][nN][tT]32
DT_SINT64 [sS][iI][nN][tT]64
DT_SINT8 [sS][iI][nN][tT]8
DT_STR [sS][tT][rR][iI][nN][gG] 
DT_UINT16 [uU][iI][nN][tT]16
DT_UINT32 [uU][iI][nN][tT]32
DT_UINT64 [uU][iI][nN][tT]64
DT_UINT8 [uU][iI][nN][tT]8
ENABLEOVERRIDE [eE][nN][aA][bB][lL][eE][oO][vV][eE][rR][rR][iI][dD][eE]
FALSE [fF][aA][lL][sS][eE]
FLAVOR [fF][lL][aA][vV][oO][rR]
INDICATION [iI][nN][dD][iI][cC][aA][tT][iI][oO][nN]
INSTANCE [iI][nN][sS][tT][aA][nN][cC][eE]
METHOD [mM][eE][tT][hH][oO][dD]
NULL [nN][uU][lL][lL]
OF [oO][fF]
PARAMETER [pP][aA][rR][aA][mM][eE][tT][eE][rR]
PRAGMA \#[Pp][Rr][Aa][Gg][Mm][Aa]
PROPERTY [pP][rR][oO][pP][eE][rR][tT][yY]
QUALIFIER [qQ][uU][aA][lL][iI][fF][iI][eE][rR]
REFERENCE [rR][eE][fF][eE][rR][eE][nN][cC][eE]
REF [rR][eE][fF]
RESTRICTED [rR][eE][sS][tT][rR][iI][cC][tT][eE][dD]
SCHEMA [sS][cC][hH][eE][mM][aA]
SCOPE [sS][cC][oO][pP][eE]
TOSUBCLASS [tT][oO][sS][uU][bB][cC][lL][aA][sS][sS]
TRANSLATABLE [tT][rR][aA][nN][sS][lL][aA][tT][aA][bB][lL][eE]
TRUE [tT][rR][uU][eE]

/*
**------------------------------------------------------------------------------
**
** Convenient definitions:
**
**------------------------------------------------------------------------------
*/

BINARY_VALUE [+-]?{BINARY_DIGIT}+[bB]
BINARY_DIGIT [01]
OCTAL_VALUE [+-]?0{OCTAL_DIGIT}+
OCTAL_DIGIT [0-7]
DECIMAL_VALUE [+-]?{POSITIVE_DECIMAL_DIGIT}{DECIMAL_DIGIT}*
DECIMAL_DIGIT [0-9]
POSITIVE_DECIMAL_DIGIT [1-9]
HEX_VALUE [+-]?0[xX]{HEX_DIGIT}+
HEX_DIGIT [A-Fa-f0-9]
REAL_VALUE [+-]?{DECIMAL_DIGIT}*\.{DECIMAL_DIGIT}+([eE][+-]?{DECIMAL_DIGIT}+)?
BLANK [ \t\n\r]
IDENT_CHAR [A-Za-z_]

/*
**------------------------------------------------------------------------------
**
** Rules:
**
**------------------------------------------------------------------------------
*/

%%

<<EOF>> {
    if (pop_include_file() == -1)
	yyterminate();
}

\/\* {

    int prev_ch = '\0';
    int ch;

    /* 
     * Skip remainder of comment.
     */

    while ((ch = yyinput()) != 0)
    {
	if (ch == '\n')
	    MOF_line_num++;
	else if (ch == '/' && prev_ch == '*')
	    break;
	
	prev_ch = ch;
    }

    /* 
     * Replace comment with space in case a comment 
     * was used as a separator.
     */

    unput(' ');
}

\/\/ {

    char c;

    /*
     * Skip remainder of line:
     */

    while ((c = yyinput()) !='\n' && c != 0)
	;

    MOF_line_num++;
}

{ANY} {
     return TOK_ANY; 
}

{AS} {
     return TOK_AS; 
}

{ASSOCIATION} {
     MOF_lval.string_value = yytext; 
     return TOK_ASSOCIATION; 
}

{CLASS} {
     return TOK_CLASS; 
}

{DISABLEOVERRIDE} {
     return TOK_DISABLEOVERRIDE; 
}

{DT_BOOL} {
     return TOK_BOOLEAN; 
}

{DT_CHAR16} {
     return TOK_CHAR16; 
}

{DT_DATETIME} {
     return TOK_DATETIME; 
}

{DT_REAL32} {
     return TOK_REAL32; 
}

{DT_REAL64} {
     return TOK_REAL64; 
}

{DT_SINT16} {
     return TOK_SINT16; 
}

{DT_SINT32} {
     return TOK_SINT32; 
}

{DT_SINT64} {
     return TOK_SINT64; 
}

{DT_SINT8} {
     return TOK_SINT8; 
}

{DT_STR} {
     return TOK_STRING; 
}

{DT_UINT16} {
     return TOK_UINT16; 
}

{DT_UINT32} {
     return TOK_UINT32; 
}

{DT_UINT64} {
     return TOK_UINT64; 
}

{DT_UINT8} {
     return TOK_UINT8; 
}

{ENABLEOVERRIDE} {
     return TOK_ENABLEOVERRIDE; 
}

{FALSE} {
     MOF_lval.bool_value = 0; 
     return TOK_BOOL_VALUE; 
}

{FLAVOR} {
     return TOK_FLAVOR; 
}

{INDICATION} {
     MOF_lval.string_value = yytext; 
     return TOK_INDICATION; 
}

{INSTANCE} {
     return TOK_INSTANCE; 
}

{METHOD} {
     return TOK_METHOD; 
}

{NULL} {
     return TOK_NULL_VALUE; 
}

{OF} {
     return TOK_OF; 
}

{PARAMETER} {
     return TOK_PARAMETER; 
}

{PRAGMA}{BLANK} {
     return TOK_PRAGMA; 
}

{PROPERTY} {
     return TOK_PROPERTY; 
}

{QUALIFIER} {
     return TOK_QUALIFIER; 
}

{REFERENCE} {
     MOF_lval.string_value = yytext; 
     return TOK_REFERENCE; 
}

{REF} {
     return TOK_REF; 
}

{RESTRICTED} {
     return TOK_RESTRICTED; 
}

{SCHEMA} {
     MOF_lval.string_value = yytext; 
     return TOK_SCHEMA; 
}

{SCOPE} {
     return TOK_SCOPE; 
}

{TOSUBCLASS} {
     return TOK_TOSUBCLASS; 
}

{TRANSLATABLE} {
     return TOK_TRANSLATABLE; 
}

{TRUE} {
     MOF_lval.bool_value = 1; 
     return TOK_BOOL_VALUE; 
}

{BINARY_VALUE} {

    char* end = NULL;

    MOF_lval.int_value = strtoll(yytext, &end, 2);

    if (end == NULL || (*end != 'b' && *end != 'B'))
	MOF_error("conversion error (1)");

    return TOK_INT_VALUE;
}

{OCTAL_VALUE} {

    char* end = NULL;
    MOF_lval.int_value = strtoll(yytext, &end, 8);

    if (end == NULL || *end != '\0')
	MOF_error("conversion error (2)");

    return TOK_INT_VALUE;
}

{DECIMAL_VALUE} {

    char* end = NULL;
    MOF_lval.int_value = strtoll(yytext, &end, 10);

    if (end == NULL || *end != '\0')
	MOF_error("conversion error (3)");

    return TOK_INT_VALUE;
}

[+-]?0 {
    MOF_lval.int_value = 0;
    return TOK_INT_VALUE;
}

{HEX_VALUE} {

    char* end = NULL;
    MOF_lval.int_value = strtoll(yytext, &end, 16);

    if (end == NULL || *end != '\0')
	MOF_error("conversion error (4)");

    return TOK_INT_VALUE;
}

{REAL_VALUE} {

    char* end = NULL;
    MOF_lval.real_value = strtod((char*)yytext, &end);

    if (end == NULL || *end != '\0')
	MOF_error("conversion error (5)");

    return TOK_REAL_VALUE;
}

\" {

    MOF_read_string(
        yyinput, 
        MOF_error, 
        &MOF_lval.string_literal.raw,
        &MOF_lval.string_literal.escaped);

    return TOK_STRING_VALUE;
}

\'[^\']\' {
    MOF_lval.char_value = yytext[1];
    return TOK_CHAR_VALUE;
}

\'\\[btnfr\"\'\\]\' {

    MOF_char16 ch;

    switch (yytext[2])
    {
	case 'b':
	    ch = '\b';
	    break;

	case 't':
	    ch = '\t';
	    break;

	case 'n':
	    ch = '\n';
	    break;

	case 'f':
	    ch = '\f';
	    break;

	case 'r':
	    ch = '\r';
	    break;

	case '"':
	case '\'':
	case '\\':
	    ch = yytext[2];

	default:
	    MOF_ASSERT(0);
    }

    MOF_lval.char_value = ch;
    return TOK_CHAR_VALUE;
}

\'\\[xX]{HEX_DIGIT}+\' {

    if (MOF_asc7_to_char16(&yytext[1], &MOF_lval.char_value) == 0)
	MOF_error("bad hex character literal");

    return TOK_CHAR_VALUE;
}

{IDENT_CHAR}({IDENT_CHAR}|{DECIMAL_DIGIT})* {

    if ((MOF_lval.string_value = strdup(yytext)) == NULL)
	MOF_error("out of memory");

    return TOK_IDENT;
}

\${IDENT_CHAR}({IDENT_CHAR}|{DECIMAL_DIGIT})* {

    if ((MOF_lval.string_value = strdup(yytext)) == NULL)
	MOF_error("out of memory");

    return TOK_ALIAS_IDENT;
}

\, {
    return TOK_COMMA;
}

\: {
    return TOK_COLON;
}

\; {
   return TOK_SEMICOLON;
}

\= {
    return TOK_EQUAL;
}

\{ {
    return TOK_OPEN_BRACE;
}

\} {
    return TOK_CLOSE_BRACE;
}

\[ {
    return TOK_OPEN_BRACKET;
}

\] {
    return TOK_CLOSE_BRACKET;
}

\( {
    return TOK_OPEN_PAREN;
}

\) {
    return TOK_CLOSE_PAREN;
}

{BLANK}+ {
    MOF_line_num += MOF_count_char(yytext, yyleng, '\n');
}

. {
    MOF_error("syntax error");
    yyterminate();
}

%%

int MOF_wrap()
{
    return 1;
}

static FILE* _find_and_open_included_file(
    const char* file_name,
    char** current_dir_out)
{
    *current_dir_out = NULL;

    const char* path = NULL;

    // Try to open file relative to the current file.

    if (MOF_current_dir)
    {
        char path[MOF_PATH_SIZE];
        size_t n = strlen(MOF_current_dir) + strlen(file_name) + 2;

        if (n > sizeof(path))
	    MOF_error("path would be too long");

        sprintf(path, "%s/%s", MOF_current_dir, file_name);
	FILE* stream = fopen(path, "rb");

	if (stream != NULL)
        {
            char* p = strrchr(path, '/');
            assert(p != NULL);

            char* current_dir = (char*)malloc(MOF_PATH_SIZE);
            *current_dir = '\0';
            strncat(current_dir, path, p - path);
            *current_dir_out = current_dir;

	    return stream;
        }
    }

    // Now search the MOF include path.

    for (size_t i = 0; i < MOF_num_include_paths; i++)
    {
        char path[MOF_PATH_SIZE];

        size_t n = strlen(MOF_include_paths[i]) + strlen(file_name) + 2;

        if (n > sizeof(path))
	    MOF_error("path would be too long");

        sprintf(path, "%s/%s", MOF_include_paths[i], file_name);
	FILE* stream = fopen(path, "rb");

	if (stream != NULL)
        {
            char* p = strrchr(path, '/');
            assert(p != NULL);

            char* current_dir = (char*)malloc(MOF_PATH_SIZE);
            *current_dir = '\0';
            strncat(current_dir, path, p - path);
            *current_dir_out = current_dir;

	    return stream;
        }
    }

    return NULL;
}

/*
 * Used to push (and save) the current parsing state and to define a new
 * one from the file_name parameter.
 */
void push_include_file(const char* file_name_)
{
    // Reverse slashes.

    char file_name[MOF_PATH_SIZE];

    *file_name = '\0';
    strncat(file_name, file_name_, sizeof(file_name) - 1);

    for (char* p = file_name; *p; p++)
    {
        if (*p == '\\')
            *p = '/';
    }

    // Save the old state:

    if (state_stack_size == MAX_STATE_STACK_SIZE)
    {
	MOF_error_printf("includes nested too deeply (greater than %d)",
	    MAX_STATE_STACK_SIZE);
    }

    MOF_State current_state = 
	{ MOF_file_name, MOF_line_num, MOF_current_dir, YY_CURRENT_BUFFER };

    state_stack[state_stack_size++] = current_state;

    // Open file.

    char* current_dir = NULL;
    FILE* stream = _find_and_open_included_file(file_name, &current_dir);

    if (stream == NULL)
	MOF_error_printf("failed to open included file: \"%s\"", file_name);

    // Create the new state:

    yy_switch_to_buffer(yy_create_buffer(stream, YY_BUF_SIZE));
    MOF_file_name = strdup(file_name);	
    MOF_line_num = 1;
    MOF_current_dir = current_dir;
}

int pop_include_file()
{
    /*
     * Pop the current include file off the state stack and restore the
     * pushed file.
     */

    if (state_stack_size > 0)
    {
	free(MOF_file_name);
	free(MOF_current_dir);
	fclose(YY_CURRENT_BUFFER->yy_input_file);

	yy_delete_buffer(YY_CURRENT_BUFFER);

	state_stack_size--;

	MOF_line_num = state_stack[state_stack_size].line_num;
	MOF_file_name = state_stack[state_stack_size].file_name;
	MOF_current_dir = state_stack[state_stack_size].current_dir;

	yy_switch_to_buffer(state_stack[state_stack_size].buffer_state);
	return 0;
    }

    /* 
     * Stack is empty:
     */

    return -1;
}
