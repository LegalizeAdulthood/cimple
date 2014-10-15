/*NOCHKSRC*/
/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     REF_TOK_NULL_VALUE = 258,
     REF_TOK_INT_VALUE = 259,
     REF_TOK_BOOL_VALUE = 260,
     REF_TOK_REAL_VALUE = 261,
     REF_TOK_STRING_VALUE = 262,
     REF_TOK_CHAR_VALUE = 263,
     REF_TOK_IDENT = 264,
     REF_TOK_COMMA = 265,
     REF_TOK_COLON = 266,
     REF_TOK_EQUAL = 267,
     REF_TOK_DOT = 268,
     REF_TOK_OPEN_BRACE = 269,
     REF_TOK_CLOSE_BRACE = 270
   };
#endif
#define REF_TOK_NULL_VALUE 258
#define REF_TOK_INT_VALUE 259
#define REF_TOK_BOOL_VALUE 260
#define REF_TOK_REAL_VALUE 261
#define REF_TOK_STRING_VALUE 262
#define REF_TOK_CHAR_VALUE 263
#define REF_TOK_IDENT 264
#define REF_TOK_COMMA 265
#define REF_TOK_COLON 266
#define REF_TOK_EQUAL 267
#define REF_TOK_DOT 268
#define REF_TOK_OPEN_BRACE 269
#define REF_TOK_CLOSE_BRACE 270




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 17 "REF.y"
typedef union YYSTYPE {
    MOF_char16 char_value;
    char* string_value;
    MOF_sint64 int_value;
    int bool_value;
    double real_value;

    class MOF_Literal* literal;
    class MOF_Key_Value_Pair* key_val_pair;
    class MOF_Object_Reference* obj_ref;
} YYSTYPE;
/* Line 1318 of yacc.c.  */
#line 79 "REF_Yacc.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE REF_lval;



