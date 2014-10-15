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
     TOK_ALIAS_IDENT = 258,
     TOK_ANY = 259,
     TOK_AS = 260,
     TOK_ASSOCIATION = 261,
     TOK_BOOLEAN = 262,
     TOK_CHAR16 = 263,
     TOK_CHAR_VALUE = 264,
     TOK_CLASS = 265,
     TOK_CLOSE_BRACE = 266,
     TOK_CLOSE_BRACKET = 267,
     TOK_CLOSE_PAREN = 268,
     TOK_COLON = 269,
     TOK_COMMA = 270,
     TOK_DATETIME = 271,
     TOK_DISABLEOVERRIDE = 272,
     TOK_ENABLEOVERRIDE = 273,
     TOK_EQUAL = 274,
     TOK_FLAVOR = 275,
     TOK_IDENT = 276,
     TOK_INDICATION = 277,
     TOK_INSTANCE = 278,
     TOK_METHOD = 279,
     TOK_NULL_VALUE = 280,
     TOK_OF = 281,
     TOK_OPEN_BRACE = 282,
     TOK_OPEN_BRACKET = 283,
     TOK_OPEN_PAREN = 284,
     TOK_PARAMETER = 285,
     TOK_PRAGMA = 286,
     TOK_PROPERTY = 287,
     TOK_QUALIFIER = 288,
     TOK_REAL32 = 289,
     TOK_REAL64 = 290,
     TOK_REAL_VALUE = 291,
     TOK_REF = 292,
     TOK_REFERENCE = 293,
     TOK_RESTRICTED = 294,
     TOK_SCHEMA = 295,
     TOK_SCOPE = 296,
     TOK_SEMICOLON = 297,
     TOK_SINT16 = 298,
     TOK_SINT32 = 299,
     TOK_SINT64 = 300,
     TOK_SINT8 = 301,
     TOK_STRING = 302,
     TOK_STRING_VALUE = 303,
     TOK_TOSUBCLASS = 304,
     TOK_TRANSLATABLE = 305,
     TOK_BOOL_VALUE = 306,
     TOK_INT_VALUE = 307,
     TOK_UINT16 = 308,
     TOK_UINT32 = 309,
     TOK_UINT64 = 310,
     TOK_UINT8 = 311
   };
#endif
#define TOK_ALIAS_IDENT 258
#define TOK_ANY 259
#define TOK_AS 260
#define TOK_ASSOCIATION 261
#define TOK_BOOLEAN 262
#define TOK_CHAR16 263
#define TOK_CHAR_VALUE 264
#define TOK_CLASS 265
#define TOK_CLOSE_BRACE 266
#define TOK_CLOSE_BRACKET 267
#define TOK_CLOSE_PAREN 268
#define TOK_COLON 269
#define TOK_COMMA 270
#define TOK_DATETIME 271
#define TOK_DISABLEOVERRIDE 272
#define TOK_ENABLEOVERRIDE 273
#define TOK_EQUAL 274
#define TOK_FLAVOR 275
#define TOK_IDENT 276
#define TOK_INDICATION 277
#define TOK_INSTANCE 278
#define TOK_METHOD 279
#define TOK_NULL_VALUE 280
#define TOK_OF 281
#define TOK_OPEN_BRACE 282
#define TOK_OPEN_BRACKET 283
#define TOK_OPEN_PAREN 284
#define TOK_PARAMETER 285
#define TOK_PRAGMA 286
#define TOK_PROPERTY 287
#define TOK_QUALIFIER 288
#define TOK_REAL32 289
#define TOK_REAL64 290
#define TOK_REAL_VALUE 291
#define TOK_REF 292
#define TOK_REFERENCE 293
#define TOK_RESTRICTED 294
#define TOK_SCHEMA 295
#define TOK_SCOPE 296
#define TOK_SEMICOLON 297
#define TOK_SINT16 298
#define TOK_SINT32 299
#define TOK_SINT64 300
#define TOK_SINT8 301
#define TOK_STRING 302
#define TOK_STRING_VALUE 303
#define TOK_TOSUBCLASS 304
#define TOK_TRANSLATABLE 305
#define TOK_BOOL_VALUE 306
#define TOK_INT_VALUE 307
#define TOK_UINT16 308
#define TOK_UINT32 309
#define TOK_UINT64 310
#define TOK_UINT8 311




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 14 "MOF.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 1318 of yacc.c.  */
#line 193 "MOF_Yacc.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE MOF_lval;



