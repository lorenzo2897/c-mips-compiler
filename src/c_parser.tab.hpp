/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TVOID = 258,
     TLONG = 259,
     TSHORT = 260,
     TCHAR = 261,
     TINT = 262,
     TFLOAT = 263,
     TDOUBLE = 264,
     UNSIGNED = 265,
     SIGNED = 266,
     AUTO = 267,
     CONST = 268,
     EXTERN = 269,
     REGISTER = 270,
     STATIC = 271,
     VOLATILE = 272,
     STRUCT = 273,
     TYPEDEF = 274,
     UNION = 275,
     ENUM = 276,
     IF = 277,
     ELSE = 278,
     WHILE = 279,
     DO = 280,
     FOR = 281,
     GOTO = 282,
     BREAK = 283,
     CONTINUE = 284,
     RETURN = 285,
     SWITCH = 286,
     CASE = 287,
     DEFAULT = 288,
     SIZEOF = 289,
     ARROW = 290,
     ELLIPSIS = 291,
     OPENBRACE = 292,
     CLOSEBRACE = 293,
     INCREMENT = 294,
     DECREMENT = 295,
     LOGICALAND = 296,
     LOGICALOR = 297,
     SHIFTLEFT = 298,
     SHIFTRIGHT = 299,
     ASSIGN = 300,
     ASSIGNPLUS = 301,
     ASSIGNMINUS = 302,
     ASSIGNSTAR = 303,
     ASSIGNSLASH = 304,
     ASSIGNMODULO = 305,
     ASSIGNAMPERSAND = 306,
     ASSIGNPIPE = 307,
     ASSIGNCARET = 308,
     ASSIGNLEFTSHIFT = 309,
     ASSIGNRIGHTSHIFT = 310,
     LESSTHAN = 311,
     GREATERTHAN = 312,
     EQUALS = 313,
     NOTEQUALS = 314,
     LESSOREQUAL = 315,
     MOREOREQUAL = 316,
     OCTINT = 317,
     DECINT = 318,
     HEXINT = 319,
     FLOATINGPOINT = 320,
     FLOATINGDOUBLE = 321,
     CHARLITERAL = 322,
     STRINGLITERAL = 323,
     IDENTIFIER = 324
   };
#endif
/* Tokens.  */
#define TVOID 258
#define TLONG 259
#define TSHORT 260
#define TCHAR 261
#define TINT 262
#define TFLOAT 263
#define TDOUBLE 264
#define UNSIGNED 265
#define SIGNED 266
#define AUTO 267
#define CONST 268
#define EXTERN 269
#define REGISTER 270
#define STATIC 271
#define VOLATILE 272
#define STRUCT 273
#define TYPEDEF 274
#define UNION 275
#define ENUM 276
#define IF 277
#define ELSE 278
#define WHILE 279
#define DO 280
#define FOR 281
#define GOTO 282
#define BREAK 283
#define CONTINUE 284
#define RETURN 285
#define SWITCH 286
#define CASE 287
#define DEFAULT 288
#define SIZEOF 289
#define ARROW 290
#define ELLIPSIS 291
#define OPENBRACE 292
#define CLOSEBRACE 293
#define INCREMENT 294
#define DECREMENT 295
#define LOGICALAND 296
#define LOGICALOR 297
#define SHIFTLEFT 298
#define SHIFTRIGHT 299
#define ASSIGN 300
#define ASSIGNPLUS 301
#define ASSIGNMINUS 302
#define ASSIGNSTAR 303
#define ASSIGNSLASH 304
#define ASSIGNMODULO 305
#define ASSIGNAMPERSAND 306
#define ASSIGNPIPE 307
#define ASSIGNCARET 308
#define ASSIGNLEFTSHIFT 309
#define ASSIGNRIGHTSHIFT 310
#define LESSTHAN 311
#define GREATERTHAN 312
#define EQUALS 313
#define NOTEQUALS 314
#define LESSOREQUAL 315
#define MOREOREQUAL 316
#define OCTINT 317
#define DECINT 318
#define HEXINT 319
#define FLOATINGPOINT 320
#define FLOATINGDOUBLE 321
#define CHARLITERAL 322
#define STRINGLITERAL 323
#define IDENTIFIER 324




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 47 "src/c_parser.y"
{
  char* s;
  char c;
  unsigned int i;
  float f;
  double d;
  std::vector<std::string>* strvector;
  std::vector<Expression*>* expvector;
  Node* ast_node;
}
/* Line 1529 of yacc.c.  */
#line 198 "src/c_parser.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

