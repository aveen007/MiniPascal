/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     PROGRAM = 258,
     VAR = 259,
     REAL = 260,
     INTEGER = 261,
     FUNCTION = 262,
     PROCEDURE = 263,
     WHILE = 264,
     DO = 265,
     BEGINN = 266,
     END = 267,
     IF = 268,
     THEN = 269,
     ELSE = 270,
     ARRAY = 271,
     OF = 272,
     DIV = 273,
     NOT = 274,
     AND = 275,
     OR = 276,
     ALPHA = 277,
     ID = 278,
     INTNUM = 279,
     REALNUM = 280,
     NEQ = 281,
     TRUEE = 282,
     FALSEE = 283,
     BOOLEANN = 284,
     IFPREC = 285,
     Uoperator = 286
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define VAR 259
#define REAL 260
#define INTEGER 261
#define FUNCTION 262
#define PROCEDURE 263
#define WHILE 264
#define DO 265
#define BEGINN 266
#define END 267
#define IF 268
#define THEN 269
#define ELSE 270
#define ARRAY 271
#define OF 272
#define DIV 273
#define NOT 274
#define AND 275
#define OR 276
#define ALPHA 277
#define ID 278
#define INTNUM 279
#define REALNUM 280
#define NEQ 281
#define TRUEE 282
#define FALSEE 283
#define BOOLEANN 284
#define IFPREC 285
#define Uoperator 286




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



