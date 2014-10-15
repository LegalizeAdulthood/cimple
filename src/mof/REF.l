%{

#include "MOF_Config.h"
#include "MOF_Lex_Utils.h"
#include "MOF_String.h"
#include "REF_Parser.h"
#include "REF_Yacc.h"

extern void REF_error(const char* message);

#define YY_NEVER_INTERACTIVE 1

#define YY_INPUT(BUFFER, RESULT, MAX_SIZE) \
    { \
	if (ref_input_first == ref_input_last) \
	    RESULT = YY_NULL; \
	else \
	{ \
	    BUFFER[0] = *ref_input_first++; \
	    RESULT = 1; \
	} \
    }

%}

BINARY_DIGIT            [01]
POS_DECIMAL_DIGIT       [1-9]
DECIMAL_DIGIT           [0-9]
OCTAL_DIGIT             [0-7]
HEX_DIGIT               [0-9A-Fa-f]
IDENT_CHAR              [A-Za-z_]
BLANK                   [ \t\n]

%%

[nN][uU][lL][lL] {
    return REF_TOK_NULL_VALUE;
}

[tT][rR][uU][eE] {
    REF_lval.bool_value = 1;
    return REF_TOK_BOOL_VALUE;
}

[fF][aA][lL][sS][eE] {
    REF_lval.bool_value = 0;
    return REF_TOK_BOOL_VALUE;
}

[-+]?{BINARY_DIGIT}+[bB] {

    char* end = NULL;
    REF_lval.int_value = strtoll(yytext, &end, 2);

    if (end == NULL || (*end != 'b' && *end != 'B'))
	REF_error("conversion error (1)");

    return REF_TOK_INT_VALUE;
}

[-+]?0{OCTAL_DIGIT}+ {

    char* end = NULL;
    REF_lval.int_value = strtoll(yytext, &end, 8);

    if (end == NULL || *end != '\0')
	REF_error("conversion error (2)");

    return REF_TOK_INT_VALUE;
}

[-+]?{POS_DECIMAL_DIGIT}{DECIMAL_DIGIT}* {

    char* end = NULL;
    REF_lval.int_value = strtoll(yytext, &end, 10);

    if (end == NULL || *end != '\0')
	REF_error("conversion error (3)");

    return REF_TOK_INT_VALUE;
}

[+-]?0 {
    REF_lval.int_value = 0;
    return REF_TOK_INT_VALUE;
}

[-+]?0[xX]{HEX_DIGIT}+ {

    char* end = NULL;
    REF_lval.int_value = strtoll(yytext, &end, 16);

    if (end == NULL || *end != '\0')
	REF_error("conversion error (4)");

    return REF_TOK_INT_VALUE;
}

[-+]?{DECIMAL_DIGIT}*\.{DECIMAL_DIGIT}+([eE][+-]?{DECIMAL_DIGIT}+)? {

    char* end = NULL;
    REF_lval.real_value = strtod((char*)yytext, &end);

    if (end == NULL || *end != '\0')
	REF_error("conversion error (5)");

    return REF_TOK_REAL_VALUE;
}

\" {
    MOF_read_string(
        yyinput, 
        REF_error, 
        (char**)0,
        &REF_lval.string_value);
    return REF_TOK_STRING_VALUE;
}

\'[^\']\' {
    REF_lval.char_value = yytext[1];
    return REF_TOK_CHAR_VALUE;
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

    REF_lval.char_value = ch;
    return REF_TOK_CHAR_VALUE;
}

\'\\[xX]{HEX_DIGIT}+\' {

    if (MOF_asc7_to_char16(&yytext[1], &REF_lval.char_value) == 0)
	REF_error("bad hex character literal");

    return REF_TOK_CHAR_VALUE;
}

{IDENT_CHAR}({IDENT_CHAR}|{DECIMAL_DIGIT})* {

    if ((REF_lval.string_value = strdup(yytext)) == NULL)
	REF_error("out of memory");
    
    return REF_TOK_IDENT;
}

\{ {
    return REF_TOK_OPEN_BRACE;
}

\} {
    return REF_TOK_CLOSE_BRACE;
}

\, {
    return REF_TOK_COMMA;
}

\: {
    return REF_TOK_COLON;
}

\. {
    return REF_TOK_DOT;
}

\= {
    return REF_TOK_EQUAL;
}

{BLANK}+ {
    ref_line_num += MOF_count_char(yytext, yyleng, '\n');
}

. {
    REF_error("syntax error");
    yyterminate();
}

%%

int REF_wrap()
{
    /* No more files to process */
    return 1;
}

void _REF_lex_suppress_unput_unused()
{
    unput('a');
}
