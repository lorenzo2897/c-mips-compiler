/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "src/c_parser.y"

	#include <stdio.h>
	#include <string.h>

	#include <vector>
	#include <string>

	#include "ast/Node.hpp"
	#include "ast/ProgramRoot.hpp"
	#include "ast/Function.hpp"
	#include "ast/Scope.hpp"

	#include "ast/Statement.hpp"
	#include "ast/statements/CaseStatement.hpp"
	#include "ast/statements/CompoundStatement.hpp"
	#include "ast/statements/ExpressionStatement.hpp"
	#include "ast/statements/LabeledStatement.hpp"
	#include "ast/statements/SwitchStatement.hpp"
	#include "ast/statements/WhileStatement.hpp"
	#include "ast/statements/ForStatement.hpp"
	#include "ast/statements/ReturnStatement.hpp"
	#include "ast/statements/BreakStatement.hpp"
	#include "ast/statements/GotoStatement.hpp"
	#include "ast/statements/IfStatement.hpp"

	#include "ast/Expression.hpp"
	#include "ast/expressions/InitialiserList.hpp"
	#include "ast/expressions/AssignmentExpression.hpp"
	#include "ast/expressions/CastExpression.hpp"
	#include "ast/expressions/UnaryExpression.hpp"
	#include "ast/expressions/FunctionCall.hpp"
	#include "ast/expressions/ArrayAccess.hpp"
	#include "ast/expressions/MemberAccess.hpp"
	#include "ast/expressions/BinaryExpression.hpp"
	#include "ast/expressions/TernaryExpression.hpp"

	#include "ast/Variable.hpp"
	#include "ast/Value.hpp"

	//! This is to fix problems when generating C++
    int yylex(void);
    void yyerror(const char *);

    extern Node* ast_root;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 291 "src/c_parser.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 304 "src/c_parser.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1045

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  166
/* YYNRULES -- Number of states.  */
#define YYNSTATES  288

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,     2,     2,    50,    56,     2,
      39,    41,    48,    46,    36,    47,    35,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    38,
      90,    89,    91,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    57,     2,    59,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      37,    40,    44,    45,    51,    52,    54,    55,    60,    61,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    18,    25,    28,    30,
      33,    35,    37,    39,    41,    43,    45,    47,    49,    51,
      53,    55,    57,    59,    61,    63,    65,    68,    71,    75,
      77,    79,    83,    85,    89,    91,    94,    97,    99,   103,
     108,   110,   114,   116,   119,   122,   127,   133,   136,   141,
     144,   148,   152,   157,   161,   166,   168,   171,   173,   175,
     177,   179,   181,   183,   185,   187,   189,   191,   195,   200,
     204,   210,   216,   224,   231,   239,   248,   258,   261,   265,
     268,   271,   275,   281,   289,   291,   294,   296,   300,   302,
     306,   308,   310,   312,   314,   316,   318,   320,   322,   324,
     326,   328,   330,   336,   338,   342,   344,   348,   350,   354,
     356,   360,   362,   366,   368,   372,   376,   378,   382,   386,
     390,   394,   396,   400,   404,   406,   410,   414,   416,   420,
     424,   428,   430,   435,   441,   443,   446,   449,   452,   455,
     460,   466,   468,   470,   472,   474,   476,   478,   480,   483,
     486,   490,   495,   500,   504,   508,   510,   514,   516,   518,
     522,   524,   526,   528,   530,   532,   534
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    94,    -1,    93,    94,    -1,    95,    99,
      38,    -1,    95,   101,    39,    41,    38,    -1,    95,   101,
      39,   106,    41,    38,    -1,    95,   105,    -1,    96,    -1,
      95,    96,    -1,     3,    -1,     4,    -1,     5,    -1,     6,
      -1,     7,    -1,     8,    -1,     9,    -1,    11,    -1,    10,
      -1,    13,    -1,    17,    -1,    14,    -1,    16,    -1,    12,
      -1,    15,    -1,    98,    -1,    97,    98,    -1,    42,    43,
      -1,    42,   140,    43,    -1,    48,    -1,   100,    -1,    99,
      36,   100,    -1,   101,    -1,   101,    89,   102,    -1,    88,
      -1,    97,    88,    -1,    88,    97,    -1,   121,    -1,    44,
     103,    45,    -1,    44,   103,    36,    45,    -1,   104,    -1,
     103,    36,   104,    -1,   140,    -1,    46,   140,    -1,    47,
     140,    -1,   101,    39,    41,   107,    -1,   101,    39,   106,
      41,   107,    -1,    95,   101,    -1,   106,    36,    95,   101,
      -1,    44,    45,    -1,    44,   108,    45,    -1,    44,   109,
      45,    -1,    44,   108,   109,    45,    -1,    95,    99,    38,
      -1,   108,    95,    99,    38,    -1,   110,    -1,   109,   110,
      -1,   107,    -1,   111,    -1,   112,    -1,   113,    -1,   114,
      -1,   115,    -1,   116,    -1,   117,    -1,   118,    -1,   119,
      -1,    88,    63,   110,    -1,    32,   123,    63,   110,    -1,
      33,    63,   110,    -1,    31,    39,   120,    41,   110,    -1,
      24,    39,   120,    41,   110,    -1,    25,   110,    24,    39,
     120,    41,    38,    -1,    26,    39,   119,   119,    41,   110,
      -1,    26,    39,   119,   119,   120,    41,   110,    -1,    26,
      39,    95,    99,    38,   119,    41,   110,    -1,    26,    39,
      95,    99,    38,   119,   120,    41,   110,    -1,    30,    38,
      -1,    30,   120,    38,    -1,    29,    38,    -1,    28,    38,
      -1,    27,    88,    38,    -1,    22,    39,   120,    41,   110,
      -1,    22,    39,   120,    41,   110,    23,   110,    -1,    38,
      -1,   120,    38,    -1,   121,    -1,   120,    36,   121,    -1,
     123,    -1,   135,   122,   121,    -1,    89,    -1,    65,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,
      71,    -1,    72,    -1,    73,    -1,    74,    -1,   124,    -1,
     124,    62,   120,    63,   123,    -1,   125,    -1,   124,    55,
     125,    -1,   126,    -1,   125,    54,   126,    -1,   127,    -1,
     126,    57,   127,    -1,   128,    -1,   127,    58,   128,    -1,
     129,    -1,   128,    56,   129,    -1,   130,    -1,   129,    77,
     130,    -1,   129,    78,   130,    -1,   131,    -1,   130,    90,
     131,    -1,   130,    91,   131,    -1,   130,    79,   131,    -1,
     130,    80,   131,    -1,   132,    -1,   131,    60,   132,    -1,
     131,    61,   132,    -1,   133,    -1,   132,    46,   133,    -1,
     132,    47,   133,    -1,   134,    -1,   133,    50,   134,    -1,
     133,    49,   134,    -1,   133,    48,   134,    -1,   135,    -1,
      39,    96,    41,   134,    -1,    39,    96,    97,    41,   134,
      -1,   137,    -1,    51,   135,    -1,    52,   135,    -1,   136,
     134,    -1,    34,   135,    -1,    34,    39,    95,    41,    -1,
      34,    39,    95,    97,    41,    -1,    46,    -1,    47,    -1,
      56,    -1,    48,    -1,    59,    -1,    53,    -1,   139,    -1,
     137,    51,    -1,   137,    52,    -1,    88,    39,    41,    -1,
      88,    39,   138,    41,    -1,   137,    42,   120,    43,    -1,
     137,    35,    88,    -1,   137,    37,    88,    -1,   121,    -1,
     138,    36,   121,    -1,   140,    -1,    88,    -1,    39,   120,
      41,    -1,    82,    -1,    81,    -1,    83,    -1,    84,    -1,
      85,    -1,    86,    -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   106,   110,   117,   121,   125,   132,   136,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   155,   156,   158,   159,   160,
     162,   166,   170,   173,   178,   182,   187,   193,   194,   195,
     197,   201,   206,   207,   208,   210,   223,   240,   245,   251,
     252,   253,   254,   256,   268,   284,   295,   304,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   319,   320,   321,
     323,   325,   326,   328,   331,   334,   343,   353,   354,   356,
     357,   359,   361,   362,   367,   368,   370,   371,   384,   385,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   401,   402,   404,   405,   407,   408,   410,   411,   413,
     414,   416,   417,   419,   420,   421,   423,   424,   425,   426,
     427,   429,   430,   431,   433,   434,   435,   437,   438,   439,
     440,   442,   443,   446,   450,   451,   452,   453,   456,   457,
     461,   465,   466,   467,   468,   469,   470,   472,   473,   474,
     475,   476,   477,   478,   479,   481,   485,   489,   490,   491,
     493,   494,   495,   496,   497,   498,   499
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TVOID", "TLONG", "TSHORT", "TCHAR",
  "TINT", "TFLOAT", "TDOUBLE", "UNSIGNED", "SIGNED", "AUTO", "CONST",
  "EXTERN", "REGISTER", "STATIC", "VOLATILE", "STRUCT", "TYPEDEF", "UNION",
  "ENUM", "IF", "ELSE", "WHILE", "DO", "FOR", "GOTO", "BREAK", "CONTINUE",
  "RETURN", "SWITCH", "CASE", "DEFAULT", "SIZEOF", "'.'", "','", "ARROW",
  "';'", "'('", "ELLIPSIS", "')'", "'['", "']'", "OPENBRACE", "CLOSEBRACE",
  "'+'", "'-'", "'*'", "'/'", "'%'", "INCREMENT", "DECREMENT", "'!'",
  "LOGICALAND", "LOGICALOR", "'&'", "'|'", "'^'", "'~'", "SHIFTLEFT",
  "SHIFTRIGHT", "'?'", "':'", "ASSIGN", "ASSIGNPLUS", "ASSIGNMINUS",
  "ASSIGNSTAR", "ASSIGNSLASH", "ASSIGNMODULO", "ASSIGNAMPERSAND",
  "ASSIGNPIPE", "ASSIGNCARET", "ASSIGNLEFTSHIFT", "ASSIGNRIGHTSHIFT",
  "LESSTHAN", "GREATERTHAN", "EQUALS", "NOTEQUALS", "LESSOREQUAL",
  "MOREOREQUAL", "OCTINT", "DECINT", "HEXINT", "FLOATINGPOINT",
  "FLOATINGDOUBLE", "CHARLITERAL", "STRINGLITERAL", "IDENTIFIER", "'='",
  "'<'", "'>'", "$accept", "ProgramRoot", "TopLevelDeclaration",
  "DeclarationSpecifiers", "TypeSpecifier", "TypeSuffix", "Pointer",
  "DeclarationList", "Declaration", "Declarator", "Initialiser",
  "InitialiserList", "InitialiserListValue", "Function",
  "FunctionParameterList", "CompoundStatement", "InnerDeclarationBlock",
  "StatementBlock", "Statement", "LabeledStatement", "SwitchStatement",
  "WhileStatement", "ForStatement", "ReturnStatement", "BreakStatement",
  "GotoStatement", "IfStatement", "ExpressionStatement", "Expression",
  "AssignmentExpression", "AssignmentOperator", "TernaryExpression",
  "LogicalOrExpression", "LogicalAndExpression", "BitwiseOrExpression",
  "BitwiseXorExpression", "BitwiseAndExpression", "EqualityExpression",
  "ComparisonExpression", "ShiftExpression", "AdditiveExpression",
  "MultiplicativeExpression", "CastExpression", "UnaryExpression",
  "UnaryOperator", "PostfixExpression", "FunctionArgumentList",
  "AtomicExpression", "Value", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    46,    44,   290,    59,    40,
     291,    41,    91,    93,   292,   293,    43,    45,    42,    47,
      37,   294,   295,    33,   296,   297,    38,   124,    94,   126,
     298,   299,    63,    58,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,    61,
      60,    62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    94,    94,    94,    94,    95,    95,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    98,    98,    98,
      99,    99,   100,   100,   101,   101,   101,   102,   102,   102,
     103,   103,   104,   104,   104,   105,   105,   106,   106,   107,
     107,   107,   107,   108,   108,   109,   109,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   111,   111,   111,
     112,   113,   113,   114,   114,   114,   114,   115,   115,   116,
     116,   117,   118,   118,   119,   119,   120,   120,   121,   121,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   128,   129,   129,   129,   130,   130,   130,   130,
     130,   131,   131,   131,   132,   132,   132,   133,   133,   133,
     133,   134,   134,   134,   135,   135,   135,   135,   135,   135,
     135,   136,   136,   136,   136,   136,   136,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   139,   139,   139,
     140,   140,   140,   140,   140,   140,   140
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     5,     6,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     1,
       1,     3,     1,     3,     1,     2,     2,     1,     3,     4,
       1,     3,     1,     2,     2,     4,     5,     2,     4,     2,
       3,     3,     4,     3,     4,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     4,     3,
       5,     5,     7,     6,     7,     8,     9,     2,     3,     2,
       2,     3,     5,     7,     1,     2,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     4,     5,     1,     2,     2,     2,     2,     4,
       5,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     4,     4,     3,     3,     1,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    18,    17,
      23,    19,    21,    24,    22,    20,     0,     2,     0,     8,
       1,     3,     0,    29,    34,     9,     0,    25,     0,    30,
      32,     7,    27,   161,   160,   162,   163,   164,   165,   166,
       0,    36,    35,    26,     0,     4,     0,     0,    28,    31,
      32,     0,     0,     0,     0,     0,     0,   141,   142,   144,
       0,     0,   146,   143,   145,   158,    33,    37,    88,   101,
     103,   105,   107,   109,   111,   113,   116,   121,   124,   127,
     131,     0,   134,   147,   157,     5,     0,    45,    47,     0,
       0,     0,   138,     0,     0,    86,     0,     0,     0,    40,
      42,     0,   135,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    90,     0,   137,   131,     0,     0,
       0,   148,   149,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    84,    49,   158,     0,    57,     0,
       0,    55,    58,    59,    60,    61,    62,    63,    64,    65,
      66,     0,     0,     6,    46,     0,     0,     0,     0,   159,
      43,    44,     0,    38,   150,   155,     0,   104,     0,   106,
     108,   110,   112,   114,   115,   119,   120,   117,   118,   122,
     123,   125,   126,   130,   129,   128,    89,   153,   154,     0,
       0,     0,     0,     0,     0,    80,    79,    77,     0,     0,
       0,     0,     0,     0,    50,     0,     0,    51,    56,    85,
      48,   139,     0,   132,     0,    87,    39,    41,     0,   151,
       0,   152,     0,     0,     0,     0,     0,    81,    78,     0,
       0,    69,    67,    53,     0,    52,   140,   133,   156,   102,
       0,     0,     0,     0,     0,     0,    68,    54,    82,    71,
       0,     0,     0,     0,    70,     0,     0,     0,    73,     0,
      83,    72,     0,     0,    74,    75,     0,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    26,    27,    28,    29,    50,
      66,    98,    99,    31,    53,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,    95,
     135,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,   186,    83,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -188
static const yytype_int16 yypact[] =
{
    1028,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  1013,  -188,   482,  -188,
    -188,  -188,   117,  -188,    60,  -188,    13,  -188,   -15,  -188,
      -7,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
     -31,    60,  -188,  -188,    55,  -188,   635,   134,  -188,  -188,
     -59,    41,   482,    83,   854,   425,   433,  -188,  -188,  -188,
     869,   869,  -188,  -188,  -188,    -6,  -188,  -188,  -188,   -35,
      36,    42,   -14,    -9,    44,    37,    -4,    88,   217,  -188,
     925,   924,    58,  -188,  -188,  -188,   225,  -188,  -188,  1028,
      85,   425,  -188,   -13,    97,  -188,   204,   204,   -23,  -188,
    -188,   924,  -188,  -188,   657,   924,   924,   924,   924,   924,
     924,   924,   924,   924,   924,   924,   924,   924,   924,   924,
     924,   924,   924,   924,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,   924,  -188,  -188,     6,    54,
     924,  -188,  -188,   113,   131,   641,   158,    61,   156,   175,
     712,   184,   924,   151,  -188,  -188,   -21,   482,  -188,   311,
     507,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,   110,   482,  -188,  -188,   568,   924,    63,   924,  -188,
    -188,  -188,   215,  -188,  -188,  -188,   100,    36,   -17,    42,
     -14,    -9,    44,    37,    37,    -4,    -4,    -4,    -4,    88,
      88,   217,   217,  -188,  -188,  -188,  -188,  -188,  -188,    -5,
     924,   924,   224,   368,   230,  -188,  -188,  -188,   139,   924,
     211,   641,   641,   173,  -188,   482,   574,  -188,  -188,  -188,
    -188,  -188,    72,  -188,   924,  -188,  -188,  -188,   924,  -188,
     924,  -188,   109,   133,   236,   482,   728,  -188,  -188,   135,
     641,  -188,  -188,  -188,   188,  -188,  -188,  -188,  -188,  -188,
     641,   641,   924,   244,   783,   641,  -188,  -188,   256,  -188,
     143,   728,   641,   147,  -188,   641,   245,   799,  -188,   641,
    -188,  -188,   641,   155,  -188,  -188,   641,  -188
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,  -188,   276,   -41,   -18,   -10,   -24,  -133,   249,   -11,
    -188,  -188,   112,  -188,  -188,   -47,  -188,   136,  -135,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -187,   -52,   -46,
    -188,  -144,  -188,   198,   197,   221,   196,   220,    51,   130,
      38,    86,   -70,   -45,  -188,  -188,  -188,  -188,   -16
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      25,    67,    43,    94,    87,    52,    40,    30,   220,    92,
     212,   136,    48,   182,    41,   102,   103,    43,   104,   178,
     105,    44,   183,    45,   223,   228,   246,   106,   176,    22,
      47,   178,    46,   104,    25,    23,   137,    93,   241,    94,
     100,    88,   222,   174,   109,   157,   240,   110,   172,    94,
     175,   203,   204,   205,   188,    22,   117,   118,   185,   264,
     137,    23,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,    85,
     180,   181,    47,   177,   277,    86,   251,   252,   209,   206,
     107,   228,   254,   138,   207,   139,   259,    22,   218,   108,
     140,    42,    22,    23,   234,    22,   233,   137,    23,   141,
     142,    23,   263,   256,    22,   266,   113,   114,   225,    89,
      23,   111,   112,   173,    90,   268,   269,   115,   116,    86,
     274,   137,   235,   178,   119,   120,   238,   278,   179,    25,
     280,   239,   208,    24,   284,   178,   178,   285,   229,   214,
     260,   287,   210,    43,    25,   199,   200,    25,   242,   243,
      32,   230,   193,   194,   257,   232,   100,   249,    54,   178,
     211,   178,   245,    55,   261,   178,   265,   248,    56,   178,
      57,    58,    59,   178,   276,    60,    61,    62,   279,   137,
      63,   178,   258,    64,   215,   137,   286,   213,    33,    34,
      35,    36,    37,    38,    39,   201,   202,    25,    43,    44,
     270,   253,   273,   216,   221,    33,    34,    35,    36,    37,
      38,    39,    65,   219,    44,   283,   267,    25,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   195,   196,   197,   198,   143,   244,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,    54,
     236,    96,    97,   154,    55,   121,   122,   123,   247,    86,
     155,    57,    58,    59,   250,   262,    60,    61,    62,   275,
      44,    63,   271,   281,    64,    33,    34,    35,    36,    37,
      38,    39,    21,    49,   237,   226,    33,    34,    35,    36,
      37,    38,    39,   187,   189,   191,    33,    34,    35,    36,
      37,    38,    39,   156,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,   190,
     192,     0,     0,   143,     0,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,    54,     0,     0,     0,   154,
      55,     0,     0,     0,     0,    86,   224,    57,    58,    59,
       0,     0,    60,    61,    62,     0,     0,    63,     0,     0,
      64,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,     0,
       0,     0,    33,    34,    35,    36,    37,    38,    39,   156,
       0,     0,    54,     0,     0,     0,   154,    55,     0,     0,
       0,     0,     0,     0,    57,    58,    59,     0,     0,    60,
      61,    62,     0,     0,    63,     0,     0,    64,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,    37,    38,    39,    65,     0,     0,    54,
       0,     0,     0,     0,    55,     0,     0,     0,     0,     0,
       0,    57,    58,    59,     0,     0,    60,    61,    62,    96,
      97,    63,     0,     0,    64,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       0,     0,     0,     0,     0,     0,    33,    34,    35,    36,
      37,    38,    39,    65,    33,    34,    35,    36,    37,    38,
      39,     0,     0,     0,    22,     0,     0,     0,     0,   143,
      23,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,    54,     0,     0,     0,   154,    55,     0,     0,     0,
       0,    86,   227,    57,    58,    59,     0,     0,    60,    61,
      62,     0,     0,    63,     0,     0,    64,     0,     0,     0,
      24,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,     0,     0,    33,    34,
      35,    36,    37,    38,    39,   156,   143,     0,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,    54,   231,
      22,     0,   154,    55,     0,     0,    23,     0,    86,   255,
      57,    58,    59,     0,     0,    60,    61,    62,     0,     0,
      63,     0,     0,    64,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,     0,     0,    33,    34,    35,    36,    37,
      38,    39,   156,   143,     0,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,    54,    51,     0,     0,   154,
      55,     0,     0,     0,     0,    86,     0,    57,    58,    59,
       0,    54,    60,    61,    62,     0,    55,    63,   184,     0,
      64,     0,     0,    57,    58,    59,     0,     0,    60,    61,
      62,     0,     0,    63,     0,     0,    64,     0,     0,     0,
       0,     0,    33,    34,    35,    36,    37,    38,    39,   156,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      35,    36,    37,    38,    39,    65,    54,     0,     0,     0,
     217,    55,     0,     0,     0,     0,     0,     0,    57,    58,
      59,     0,    54,    60,    61,    62,   154,    55,    63,     0,
       0,    64,     0,     0,    57,    58,    59,     0,     0,    60,
      61,    62,     0,     0,    63,     0,     0,    64,     0,     0,
       0,     0,     0,    33,    34,    35,    36,    37,    38,    39,
      65,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,    37,    38,    39,    65,    54,     0,     0,
       0,     0,    55,     0,   272,     0,     0,     0,     0,    57,
      58,    59,     0,    54,    60,    61,    62,     0,    55,    63,
     282,     0,    64,     0,     0,    57,    58,    59,     0,     0,
      60,    61,    62,     0,     0,    63,     0,     0,    64,     0,
       0,     0,     0,     0,    33,    34,    35,    36,    37,    38,
      39,    65,     0,     0,     0,     0,     0,     0,     0,     0,
      33,    34,    35,    36,    37,    38,    39,    65,    54,     0,
       0,     0,     0,    91,     0,     0,     0,     0,     0,     0,
      57,    58,    59,    54,     0,    60,    61,    62,   101,     0,
      63,     0,     0,    64,     0,    57,    58,    59,     0,     0,
      60,    61,    62,     0,     0,    63,     0,     0,    64,     0,
       0,     0,     0,     0,     0,    33,    34,    35,    36,    37,
      38,    39,    65,     0,     0,     0,     0,     0,     0,     0,
      33,    34,    35,    36,    37,    38,    39,    65,    54,     0,
       0,     0,     0,    55,     0,     0,     0,     0,     0,     0,
      57,    58,    59,     0,     0,    60,    61,    62,     0,     0,
      63,     0,     0,    64,     0,     0,     0,     0,     0,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,     0,    33,    34,    35,    36,    37,
      38,    39,    65,    20,   134,     0,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15
};

static const yytype_int16 yycheck[] =
{
      18,    47,    26,    55,    51,    46,    22,    18,   152,    54,
     145,    81,    43,    36,    24,    60,    61,    41,    39,    36,
      55,    36,    45,    38,   157,   160,   213,    62,    41,    42,
      89,    36,    39,    39,    52,    48,    81,    55,    43,    91,
      56,    52,    63,    90,    58,    86,    63,    56,    89,   101,
      91,   121,   122,   123,   106,    42,    60,    61,   104,   246,
     105,    48,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    38,
      96,    97,    89,    93,   271,    44,   221,   222,   140,   135,
      54,   226,   225,    35,    88,    37,   240,    42,   150,    57,
      42,    88,    42,    48,    41,    42,   176,   152,    48,    51,
      52,    48,   245,    41,    42,   250,    79,    80,   159,    36,
      48,    77,    78,    38,    41,   260,   261,    90,    91,    44,
     265,   176,   178,    36,    46,    47,    36,   272,    41,   157,
     275,    41,    88,    88,   279,    36,    36,   282,    38,    88,
      41,   286,    39,   177,   172,   117,   118,   175,   210,   211,
      43,   172,   111,   112,   234,   175,   182,   219,    34,    36,
      39,    36,   213,    39,    41,    36,    41,    38,    44,    36,
      46,    47,    48,    36,    41,    51,    52,    53,    41,   234,
      56,    36,   238,    59,    38,   240,    41,    39,    81,    82,
      83,    84,    85,    86,    87,   119,   120,   225,   232,    36,
     262,    38,   264,    38,    63,    81,    82,    83,    84,    85,
      86,    87,    88,    39,    36,   277,    38,   245,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,   113,   114,   115,   116,    22,    24,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      45,    46,    47,    38,    39,    48,    49,    50,    38,    44,
      45,    46,    47,    48,    63,    39,    51,    52,    53,    23,
      36,    56,    38,    38,    59,    81,    82,    83,    84,    85,
      86,    87,    16,    44,   182,   159,    81,    82,    83,    84,
      85,    86,    87,   105,   107,   109,    81,    82,    83,    84,
      85,    86,    87,    88,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,   108,
     110,    -1,    -1,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    38,
      39,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      -1,    -1,    51,    52,    53,    -1,    -1,    56,    -1,    -1,
      59,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      -1,    -1,    34,    -1,    -1,    -1,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    -1,    -1,    51,
      52,    53,    -1,    -1,    56,    -1,    -1,    59,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    -1,    -1,    51,    52,    53,    46,
      47,    56,    -1,    -1,    59,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    81,    82,    83,    84,    85,    86,
      87,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    22,
      48,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    38,    39,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    -1,    -1,    51,    52,
      53,    -1,    -1,    56,    -1,    -1,    59,    -1,    -1,    -1,
      88,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    22,    -1,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    41,
      42,    -1,    38,    39,    -1,    -1,    48,    -1,    44,    45,
      46,    47,    48,    -1,    -1,    51,    52,    53,    -1,    -1,
      56,    -1,    -1,    59,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    22,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    41,    -1,    -1,    38,
      39,    -1,    -1,    -1,    -1,    44,    -1,    46,    47,    48,
      -1,    34,    51,    52,    53,    -1,    39,    56,    41,    -1,
      59,    -1,    -1,    46,    47,    48,    -1,    -1,    51,    52,
      53,    -1,    -1,    56,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    34,    -1,    -1,    -1,
      38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    47,
      48,    -1,    34,    51,    52,    53,    38,    39,    56,    -1,
      -1,    59,    -1,    -1,    46,    47,    48,    -1,    -1,    51,
      52,    53,    -1,    -1,    56,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    34,    -1,    -1,
      -1,    -1,    39,    -1,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    -1,    34,    51,    52,    53,    -1,    39,    56,
      41,    -1,    59,    -1,    -1,    46,    47,    48,    -1,    -1,
      51,    52,    53,    -1,    -1,    56,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    34,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    34,    -1,    51,    52,    53,    39,    -1,
      56,    -1,    -1,    59,    -1,    46,    47,    48,    -1,    -1,
      51,    52,    53,    -1,    -1,    56,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    34,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    -1,    -1,    51,    52,    53,    -1,    -1,
      56,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,     0,    89,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    93,    94,    95,    96,
       0,    94,    42,    48,    88,    96,    97,    98,    99,   100,
     101,   105,    43,    81,    82,    83,    84,    85,    86,    87,
     140,    97,    88,    98,    36,    38,    39,    89,    43,   100,
     101,    41,    95,   106,    34,    39,    44,    46,    47,    48,
      51,    52,    53,    56,    59,    88,   102,   121,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   139,   140,    38,    44,   107,   101,    36,
      41,    39,   135,    96,   120,   121,    46,    47,   103,   104,
     140,    39,   135,   135,    39,    55,    62,    54,    57,    58,
      56,    77,    78,    79,    80,    90,    91,    60,    61,    46,
      47,    48,    49,    50,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    89,   122,   134,   135,    35,    37,
      42,    51,    52,    22,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    38,    45,    88,    95,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,    95,    38,   107,    95,    41,    97,    36,    41,
     140,   140,    36,    45,    41,   121,   138,   125,   120,   126,
     127,   128,   129,   130,   130,   131,   131,   131,   131,   132,
     132,   133,   133,   134,   134,   134,   121,    88,    88,   120,
      39,    39,   110,    39,    88,    38,    38,    38,   120,    39,
     123,    63,    63,    99,    45,    95,   109,    45,   110,    38,
     101,    41,    97,   134,    41,   121,    45,   104,    36,    41,
      63,    43,   120,   120,    24,    95,   119,    38,    38,   120,
      63,   110,   110,    38,    99,    45,    41,   134,   121,   123,
      41,    41,    39,    99,   119,    41,   110,    38,   110,   110,
     120,    38,    41,   120,   110,    23,    41,   119,   110,    41,
     110,    38,    41,   120,   110,   110,    41,   110
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 101 "src/c_parser.y"
    {
				(yyval.ast_node) = new ProgramRoot();
				ast_root = (yyval.ast_node);
				dynamic_cast<ProgramRoot*>(yyval.ast_node)->add((yyvsp[(1) - (1)].ast_node));
			;}
    break;

  case 3:
#line 106 "src/c_parser.y"
    {
				dynamic_cast<ProgramRoot*>(yyval.ast_node)->add((yyvsp[(2) - (2)].ast_node));
			;}
    break;

  case 4:
#line 110 "src/c_parser.y"
    {
						(yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);
						// add in the specifiers for each declaration in the list
						for(int i = 0; i < dynamic_cast<Scope*>(yyval.ast_node)->declarations.size(); i++) {
							dynamic_cast<Scope*>(yyval.ast_node)->declarations[i]->specifiers = *(yyvsp[(1) - (3)].strvector);
						}
					;}
    break;

  case 5:
#line 117 "src/c_parser.y"
    {
						// function declaration
						(yyval.ast_node) = NULL;
					;}
    break;

  case 6:
#line 121 "src/c_parser.y"
    {
						// function declaration
						(yyval.ast_node) = NULL;
					;}
    break;

  case 7:
#line 125 "src/c_parser.y"
    {
						// function definition
						(yyval.ast_node) = (yyvsp[(2) - (2)].ast_node);
						// add in the specifiers for the function type
						dynamic_cast<Function*>(yyval.ast_node)->specifiers = *(yyvsp[(1) - (2)].strvector);
					;}
    break;

  case 8:
#line 132 "src/c_parser.y"
    {
					  	  (yyval.strvector) = new std::vector<std::string>;
						  (yyval.strvector)->push_back((yyvsp[(1) - (1)].s));
					  ;}
    break;

  case 9:
#line 136 "src/c_parser.y"
    { (yyval.strvector)->push_back((yyvsp[(2) - (2)].s)); ;}
    break;

  case 10:
#line 138 "src/c_parser.y"
    { (yyval.s) = strdup("void"); ;}
    break;

  case 11:
#line 139 "src/c_parser.y"
    { (yyval.s) = strdup("long"); ;}
    break;

  case 12:
#line 140 "src/c_parser.y"
    { (yyval.s) = strdup("short"); ;}
    break;

  case 13:
#line 141 "src/c_parser.y"
    { (yyval.s) = strdup("char"); ;}
    break;

  case 14:
#line 142 "src/c_parser.y"
    { (yyval.s) = strdup("int"); ;}
    break;

  case 15:
#line 143 "src/c_parser.y"
    { (yyval.s) = strdup("float"); ;}
    break;

  case 16:
#line 144 "src/c_parser.y"
    { (yyval.s) = strdup("double"); ;}
    break;

  case 17:
#line 145 "src/c_parser.y"
    { (yyval.s) = strdup("signed"); ;}
    break;

  case 18:
#line 146 "src/c_parser.y"
    { (yyval.s) = strdup("unsigned"); ;}
    break;

  case 19:
#line 147 "src/c_parser.y"
    { (yyval.s) = strdup("const"); ;}
    break;

  case 20:
#line 148 "src/c_parser.y"
    { (yyval.s) = strdup("volatile"); ;}
    break;

  case 21:
#line 149 "src/c_parser.y"
    { (yyval.s) = strdup("extern"); ;}
    break;

  case 22:
#line 150 "src/c_parser.y"
    { (yyval.s) = strdup("static"); ;}
    break;

  case 23:
#line 151 "src/c_parser.y"
    { (yyval.s) = strdup("auto"); ;}
    break;

  case 24:
#line 152 "src/c_parser.y"
    { (yyval.s) = strdup("register"); ;}
    break;

  case 25:
#line 155 "src/c_parser.y"
    { (yyval.i) = 1; ;}
    break;

  case 26:
#line 156 "src/c_parser.y"
    { (yyval.i) += 1; ;}
    break;

  case 30:
#line 162 "src/c_parser.y"
    {
					(yyval.ast_node) = new Scope();
					dynamic_cast<Scope*>(yyval.ast_node)->declare(dynamic_cast<Declaration*>(yyvsp[(1) - (1)].ast_node));
				;}
    break;

  case 31:
#line 166 "src/c_parser.y"
    {
					dynamic_cast<Scope*>(yyval.ast_node)->declare(dynamic_cast<Declaration*>(yyvsp[(3) - (3)].ast_node));
				;}
    break;

  case 32:
#line 170 "src/c_parser.y"
    {
				(yyval.ast_node) = (yyvsp[(1) - (1)].ast_node);
			;}
    break;

  case 33:
#line 173 "src/c_parser.y"
    {
				(yyval.ast_node) = (yyvsp[(1) - (3)].ast_node);
				dynamic_cast<Declaration*>(yyval.ast_node)->initialiser = dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node);
			;}
    break;

  case 34:
#line 178 "src/c_parser.y"
    {
				(yyval.ast_node) = new Declaration();
				dynamic_cast<Declaration*>(yyval.ast_node)->identifier = (yyvsp[(1) - (1)].s);
			;}
    break;

  case 35:
#line 182 "src/c_parser.y"
    {
				(yyval.ast_node) = new Declaration();
				dynamic_cast<Declaration*>(yyval.ast_node)->pointer_depth = (yyvsp[(1) - (2)].i);
				dynamic_cast<Declaration*>(yyval.ast_node)->identifier = (yyvsp[(2) - (2)].s);
			;}
    break;

  case 36:
#line 187 "src/c_parser.y"
    {
				(yyval.ast_node) = new Declaration();
				dynamic_cast<Declaration*>(yyval.ast_node)->pointer_depth = (yyvsp[(2) - (2)].i);
				dynamic_cast<Declaration*>(yyval.ast_node)->identifier = (yyvsp[(1) - (2)].s);
			;}
    break;

  case 38:
#line 194 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); ;}
    break;

  case 39:
#line 195 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (4)].ast_node); ;}
    break;

  case 40:
#line 197 "src/c_parser.y"
    {
					(yyval.ast_node) = new InitialiserList();
					dynamic_cast<InitialiserList*>(yyval.ast_node)->add(dynamic_cast<Expression*>(yyvsp[(1) - (1)].ast_node));
				;}
    break;

  case 41:
#line 201 "src/c_parser.y"
    {
					(yyval.ast_node) = (yyvsp[(1) - (3)].ast_node);
					dynamic_cast<InitialiserList*>(yyval.ast_node)->add(dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node));
				;}
    break;

  case 43:
#line 207 "src/c_parser.y"
    { (yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(2) - (2)].ast_node), '+'); ;}
    break;

  case 44:
#line 208 "src/c_parser.y"
    { (yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(2) - (2)].ast_node), '-'); ;}
    break;

  case 45:
#line 210 "src/c_parser.y"
    {
				(yyval.ast_node) = new Function();

				// give the function a name
				dynamic_cast<Function*>(yyval.ast_node)->function_name = dynamic_cast<Declaration*>(yyvsp[(1) - (4)].ast_node)->identifier;

				// transfer the pointer depth
				dynamic_cast<Function*>(yyval.ast_node)->pointer_depth = dynamic_cast<Declaration*>(yyvsp[(1) - (4)].ast_node)->pointer_depth;

				// transfer the declarations and statements from the compound statement
				dynamic_cast<Function*>(yyval.ast_node)->merge_declarations(dynamic_cast<Scope*>(yyvsp[(4) - (4)].ast_node));
				dynamic_cast<Function*>(yyval.ast_node)->merge_statements(dynamic_cast<Scope*>(yyvsp[(4) - (4)].ast_node));
			;}
    break;

  case 46:
#line 223 "src/c_parser.y"
    {
				(yyval.ast_node) = new Function();

				// give the function a name
				dynamic_cast<Function*>(yyval.ast_node)->function_name = dynamic_cast<Declaration*>(yyvsp[(1) - (5)].ast_node)->identifier;

				// transfer the pointer depth
				dynamic_cast<Function*>(yyval.ast_node)->pointer_depth = dynamic_cast<Declaration*>(yyvsp[(1) - (5)].ast_node)->pointer_depth;

				// transfer the parameter list
				dynamic_cast<Function*>(yyval.ast_node)->merge_parameters(dynamic_cast<Scope*>(yyvsp[(3) - (5)].ast_node));

				// transfer the declarations and statements from the compound statement
				dynamic_cast<Function*>(yyval.ast_node)->merge_declarations(dynamic_cast<Scope*>(yyvsp[(5) - (5)].ast_node));
				dynamic_cast<Function*>(yyval.ast_node)->merge_statements(dynamic_cast<Scope*>(yyvsp[(5) - (5)].ast_node));
			;}
    break;

  case 47:
#line 240 "src/c_parser.y"
    {
							(yyval.ast_node) = new Scope();
							dynamic_cast<Declaration*>(yyvsp[(2) - (2)].ast_node)->specifiers = *(yyvsp[(1) - (2)].strvector);
							dynamic_cast<Scope*>(yyval.ast_node)->declare(dynamic_cast<Declaration*>(yyvsp[(2) - (2)].ast_node));
						;}
    break;

  case 48:
#line 245 "src/c_parser.y"
    {
							(yyval.ast_node) = (yyvsp[(1) - (4)].ast_node);
							dynamic_cast<Declaration*>(yyvsp[(4) - (4)].ast_node)->specifiers = *(yyvsp[(3) - (4)].strvector);
							dynamic_cast<Scope*>(yyval.ast_node)->declare(dynamic_cast<Declaration*>(yyvsp[(4) - (4)].ast_node));
						;}
    break;

  case 49:
#line 251 "src/c_parser.y"
    { (yyval.ast_node) = new Scope(); ;}
    break;

  case 50:
#line 252 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); ;}
    break;

  case 51:
#line 253 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); ;}
    break;

  case 52:
#line 254 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (4)].ast_node); dynamic_cast<Scope*>(yyval.ast_node)->merge_statements(dynamic_cast<Scope*>(yyvsp[(3) - (4)].ast_node)); ;}
    break;

  case 53:
#line 256 "src/c_parser.y"
    {
						  // get the list of declarations
						  Scope* d = dynamic_cast<Scope*>(yyvsp[(2) - (3)].ast_node);

						  // add in the specifiers for each declaration in the list
						  for(int i = 0; i < d->declarations.size(); i++) {
							  d->declarations[i]->specifiers = *(yyvsp[(1) - (3)].strvector);
						  }

						  // set the new declarationblock to be the declaration list
						  (yyval.ast_node) = d;
					  ;}
    break;

  case 54:
#line 268 "src/c_parser.y"
    {
  						  // get the list of declarations
  						  Scope* d = dynamic_cast<Scope*>(yyvsp[(3) - (4)].ast_node);

						  // set the specifiers for the new declarations
						  for(int i = 0; i < d->declarations.size(); i++) {
							  d->declarations[i]->specifiers = *(yyvsp[(2) - (4)].strvector);
						  }

						  // add the new declarations into the existing list
						  Scope* block = dynamic_cast<Scope*>(yyvsp[(1) - (4)].ast_node);
						  block->merge_declarations(d);

						  (yyval.ast_node) = (yyvsp[(1) - (4)].ast_node);
					  ;}
    break;

  case 55:
#line 284 "src/c_parser.y"
    {
					// get the statement
					Statement* statement = dynamic_cast<Statement*>(yyvsp[(1) - (1)].ast_node);

					// create a scope and add in the statement
					Scope* scope = new Scope();
					scope->add_statement(statement);

					// set the block to the new scope
					(yyval.ast_node) = scope;
				;}
    break;

  case 56:
#line 295 "src/c_parser.y"
    {
					// get the statement
					Statement* statement = dynamic_cast<Statement*>(yyvsp[(2) - (2)].ast_node);

					// add statement to existing scope
					dynamic_cast<Scope*>(yyvsp[(1) - (2)].ast_node)->add_statement(statement);
					(yyval.ast_node) = (yyvsp[(1) - (2)].ast_node);
				;}
    break;

  case 57:
#line 304 "src/c_parser.y"
    {
				// wrap the scope in a compound statement class
				(yyval.ast_node) = new CompoundStatement(dynamic_cast<Scope*>(yyvsp[(1) - (1)].ast_node));
			;}
    break;

  case 67:
#line 319 "src/c_parser.y"
    { (yyval.ast_node) = new LabeledStatement((yyvsp[(1) - (3)].s), dynamic_cast<Statement*>(yyvsp[(3) - (3)].ast_node)); ;}
    break;

  case 68:
#line 320 "src/c_parser.y"
    { (yyval.ast_node) = new CaseStatement(dynamic_cast<Expression*>(yyvsp[(2) - (4)].ast_node), dynamic_cast<Statement*>(yyvsp[(4) - (4)].ast_node)); ;}
    break;

  case 69:
#line 321 "src/c_parser.y"
    { (yyval.ast_node) = new CaseStatement(NULL, dynamic_cast<Statement*>(yyvsp[(3) - (3)].ast_node)); ;}
    break;

  case 70:
#line 323 "src/c_parser.y"
    { (yyval.ast_node) = new SwitchStatement(dynamic_cast<Expression*>(yyvsp[(3) - (5)].ast_node), dynamic_cast<Statement*>(yyvsp[(5) - (5)].ast_node)); ;}
    break;

  case 71:
#line 325 "src/c_parser.y"
    { (yyval.ast_node) = new WhileStatement(dynamic_cast<Expression*>(yyvsp[(3) - (5)].ast_node), dynamic_cast<Statement*>(yyvsp[(5) - (5)].ast_node), false); ;}
    break;

  case 72:
#line 326 "src/c_parser.y"
    { (yyval.ast_node) = new WhileStatement(dynamic_cast<Expression*>(yyvsp[(5) - (7)].ast_node), dynamic_cast<Statement*>(yyvsp[(2) - (7)].ast_node), true); ;}
    break;

  case 73:
#line 328 "src/c_parser.y"
    {
					(yyval.ast_node) = new ForStatement(dynamic_cast<ExpressionStatement*>(yyvsp[(3) - (6)].ast_node)->expression, dynamic_cast<ExpressionStatement*>(yyvsp[(4) - (6)].ast_node)->expression, NULL, dynamic_cast<Statement*>(yyvsp[(6) - (6)].ast_node));
				;}
    break;

  case 74:
#line 331 "src/c_parser.y"
    {
					(yyval.ast_node) = new ForStatement(dynamic_cast<ExpressionStatement*>(yyvsp[(3) - (7)].ast_node)->expression, dynamic_cast<ExpressionStatement*>(yyvsp[(4) - (7)].ast_node)->expression, dynamic_cast<Expression*>(yyvsp[(5) - (7)].ast_node), dynamic_cast<Statement*>(yyvsp[(7) - (7)].ast_node));
				;}
    break;

  case 75:
#line 334 "src/c_parser.y"
    {
					(yyval.ast_node) = new ForStatement(NULL, dynamic_cast<ExpressionStatement*>(yyvsp[(6) - (8)].ast_node)->expression, NULL, dynamic_cast<Statement*>(yyvsp[(8) - (8)].ast_node));
					Scope* s = dynamic_cast<Scope*>(yyvsp[(4) - (8)].ast_node);
					// add in the specifiers for each declaration in the list
					for(int i = 0; i < s->declarations.size(); i++) {
						s->declarations[i]->specifiers = *(yyvsp[(3) - (8)].strvector);
					}
					dynamic_cast<ForStatement*>(yyval.ast_node)->merge_declarations(s);
				;}
    break;

  case 76:
#line 343 "src/c_parser.y"
    {
					(yyval.ast_node) = new ForStatement(NULL, dynamic_cast<ExpressionStatement*>(yyvsp[(6) - (9)].ast_node)->expression, dynamic_cast<Expression*>(yyvsp[(7) - (9)].ast_node), dynamic_cast<Statement*>(yyvsp[(9) - (9)].ast_node));
					Scope* s = dynamic_cast<Scope*>(yyvsp[(4) - (9)].ast_node);
					// add in the specifiers for each declaration in the list
					for(int i = 0; i < s->declarations.size(); i++) {
						s->declarations[i]->specifiers = *(yyvsp[(3) - (9)].strvector);
					}
					dynamic_cast<ForStatement*>(yyval.ast_node)->merge_declarations(s);
				;}
    break;

  case 77:
#line 353 "src/c_parser.y"
    { (yyval.ast_node) = new ReturnStatement(); ;}
    break;

  case 78:
#line 354 "src/c_parser.y"
    { (yyval.ast_node) = new ReturnStatement(dynamic_cast<Expression*>(yyvsp[(2) - (3)].ast_node)); ;}
    break;

  case 79:
#line 356 "src/c_parser.y"
    { (yyval.ast_node) = new BreakStatement(true); ;}
    break;

  case 80:
#line 357 "src/c_parser.y"
    { (yyval.ast_node) = new BreakStatement(); ;}
    break;

  case 81:
#line 359 "src/c_parser.y"
    { (yyval.ast_node) = new GotoStatement((yyvsp[(2) - (3)].s)); ;}
    break;

  case 82:
#line 361 "src/c_parser.y"
    { (yyval.ast_node) = new IfStatement(dynamic_cast<Expression*>(yyvsp[(3) - (5)].ast_node), dynamic_cast<Statement*>(yyvsp[(5) - (5)].ast_node), NULL); ;}
    break;

  case 83:
#line 362 "src/c_parser.y"
    { (yyval.ast_node) = new IfStatement(dynamic_cast<Expression*>(yyvsp[(3) - (7)].ast_node), dynamic_cast<Statement*>(yyvsp[(5) - (7)].ast_node), dynamic_cast<Statement*>(yyvsp[(7) - (7)].ast_node)); ;}
    break;

  case 84:
#line 367 "src/c_parser.y"
    { (yyval.ast_node) = new ExpressionStatement(); ;}
    break;

  case 85:
#line 368 "src/c_parser.y"
    { (yyval.ast_node) = new ExpressionStatement(dynamic_cast<Expression*>(yyvsp[(1) - (2)].ast_node)); ;}
    break;

  case 86:
#line 370 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 87:
#line 371 "src/c_parser.y"
    {
				CompoundExpression* ce = dynamic_cast<CompoundExpression*>(yyvsp[(1) - (3)].ast_node);
				if(ce) {
					// add expression to compound expression
					(yyval.ast_node) = ce;
					ce->add_expression(dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node));
				} else {
					// create a compound expression and add in the new expression
					(yyval.ast_node) = new CompoundExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node));
					dynamic_cast<CompoundExpression*>(yyval.ast_node)->add_expression(dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node));
				}
			;}
    break;

  case 88:
#line 384 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 89:
#line 385 "src/c_parser.y"
    {
							(yyval.ast_node) = new AssignmentExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), (yyvsp[(2) - (3)].c));
						;}
    break;

  case 90:
#line 389 "src/c_parser.y"
    { (yyval.c) = '='; ;}
    break;

  case 91:
#line 390 "src/c_parser.y"
    { (yyval.c) = '+'; ;}
    break;

  case 92:
#line 391 "src/c_parser.y"
    { (yyval.c) = '-'; ;}
    break;

  case 93:
#line 392 "src/c_parser.y"
    { (yyval.c) = '*'; ;}
    break;

  case 94:
#line 393 "src/c_parser.y"
    { (yyval.c) = '/'; ;}
    break;

  case 95:
#line 394 "src/c_parser.y"
    { (yyval.c) = '%'; ;}
    break;

  case 96:
#line 395 "src/c_parser.y"
    { (yyval.c) = '&'; ;}
    break;

  case 97:
#line 396 "src/c_parser.y"
    { (yyval.c) = '|'; ;}
    break;

  case 98:
#line 397 "src/c_parser.y"
    { (yyval.c) = '^'; ;}
    break;

  case 99:
#line 398 "src/c_parser.y"
    { (yyval.c) = '<'; ;}
    break;

  case 100:
#line 399 "src/c_parser.y"
    { (yyval.c) = '>'; ;}
    break;

  case 102:
#line 402 "src/c_parser.y"
    { (yyval.ast_node) = new TernaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (5)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (5)].ast_node), dynamic_cast<Expression*>(yyvsp[(5) - (5)].ast_node)); ;}
    break;

  case 104:
#line 405 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_logicalor); ;}
    break;

  case 106:
#line 408 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_logicaland); ;}
    break;

  case 108:
#line 411 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_bitwiseor); ;}
    break;

  case 110:
#line 414 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_bitwisexor); ;}
    break;

  case 112:
#line 417 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_bitwiseand); ;}
    break;

  case 114:
#line 420 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_equals); ;}
    break;

  case 115:
#line 421 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_notequals); ;}
    break;

  case 117:
#line 424 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_lessthan); ;}
    break;

  case 118:
#line 425 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_morethan); ;}
    break;

  case 119:
#line 426 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_lessequal); ;}
    break;

  case 120:
#line 427 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_moreequal); ;}
    break;

  case 122:
#line 430 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_leftshift); ;}
    break;

  case 123:
#line 431 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_rightshift); ;}
    break;

  case 125:
#line 434 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_add); ;}
    break;

  case 126:
#line 435 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_subtract); ;}
    break;

  case 128:
#line 438 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_modulo); ;}
    break;

  case 129:
#line 439 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_divide); ;}
    break;

  case 130:
#line 440 "src/c_parser.y"
    { (yyval.ast_node) = new BinaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node), BinaryExpression::op_multiply); ;}
    break;

  case 131:
#line 442 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 132:
#line 443 "src/c_parser.y"
    {
					(yyval.ast_node) = new CastExpression((yyvsp[(2) - (4)].s), 0, dynamic_cast<Expression*>(yyvsp[(4) - (4)].ast_node));
				;}
    break;

  case 133:
#line 446 "src/c_parser.y"
    {
					(yyval.ast_node) = new CastExpression((yyvsp[(2) - (5)].s), (yyvsp[(3) - (5)].i), dynamic_cast<Expression*>(yyvsp[(5) - (5)].ast_node));
				;}
    break;

  case 135:
#line 451 "src/c_parser.y"
    { (yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(2) - (2)].ast_node), UnaryExpression::op_preincrement); ;}
    break;

  case 136:
#line 452 "src/c_parser.y"
    { (yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(2) - (2)].ast_node), UnaryExpression::op_predecrement); ;}
    break;

  case 137:
#line 453 "src/c_parser.y"
    {
					(yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(2) - (2)].ast_node), (yyvsp[(1) - (2)].c));
				;}
    break;

  case 138:
#line 456 "src/c_parser.y"
    { (yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(2) - (2)].ast_node), UnaryExpression::op_sizeof); ;}
    break;

  case 139:
#line 457 "src/c_parser.y"
    {
					std::vector<std::string>* specs = (yyvsp[(3) - (4)].strvector);
					(yyval.ast_node) = UnaryExpression::compute_sizeof_type(specs);
				;}
    break;

  case 140:
#line 461 "src/c_parser.y"
    {
					(yyval.ast_node) = new Value(4);
				;}
    break;

  case 141:
#line 465 "src/c_parser.y"
    { (yyval.c) = '+'; ;}
    break;

  case 142:
#line 466 "src/c_parser.y"
    { (yyval.c) = '-'; ;}
    break;

  case 143:
#line 467 "src/c_parser.y"
    { (yyval.c) = '&'; ;}
    break;

  case 144:
#line 468 "src/c_parser.y"
    { (yyval.c) = '*'; ;}
    break;

  case 145:
#line 469 "src/c_parser.y"
    { (yyval.c) = '~'; ;}
    break;

  case 146:
#line 470 "src/c_parser.y"
    { (yyval.c) = '!'; ;}
    break;

  case 148:
#line 473 "src/c_parser.y"
    { (yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (2)].ast_node), UnaryExpression::op_postincrement); ;}
    break;

  case 149:
#line 474 "src/c_parser.y"
    { (yyval.ast_node) = new UnaryExpression(dynamic_cast<Expression*>(yyvsp[(1) - (2)].ast_node), UnaryExpression::op_postdecrement); ;}
    break;

  case 150:
#line 475 "src/c_parser.y"
    { (yyval.ast_node) = new FunctionCall((yyvsp[(1) - (3)].s)); ;}
    break;

  case 151:
#line 476 "src/c_parser.y"
    { (yyval.ast_node) = new FunctionCall((yyvsp[(1) - (4)].s), *(yyvsp[(3) - (4)].expvector)); ;}
    break;

  case 152:
#line 477 "src/c_parser.y"
    { (yyval.ast_node) = new ArrayAccess(dynamic_cast<Expression*>(yyvsp[(1) - (4)].ast_node), dynamic_cast<Expression*>(yyvsp[(3) - (4)].ast_node)); ;}
    break;

  case 153:
#line 478 "src/c_parser.y"
    { (yyval.ast_node) = new MemberAccess(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].s), false); ;}
    break;

  case 154:
#line 479 "src/c_parser.y"
    { (yyval.ast_node) = new MemberAccess(dynamic_cast<Expression*>(yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].s), true); ;}
    break;

  case 155:
#line 481 "src/c_parser.y"
    {
							(yyval.expvector) = new std::vector<Expression*>;
							(yyval.expvector)->push_back(dynamic_cast<Expression*>(yyvsp[(1) - (1)].ast_node));
						;}
    break;

  case 156:
#line 485 "src/c_parser.y"
    {
							(yyval.expvector)->push_back(dynamic_cast<Expression*>(yyvsp[(3) - (3)].ast_node));
						;}
    break;

  case 157:
#line 489 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(1) - (1)].ast_node); ;}
    break;

  case 158:
#line 490 "src/c_parser.y"
    { (yyval.ast_node) = new Variable((yyvsp[(1) - (1)].s)); ;}
    break;

  case 159:
#line 491 "src/c_parser.y"
    { (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node); ;}
    break;

  case 160:
#line 493 "src/c_parser.y"
    { (yyval.ast_node) = new Value((yyvsp[(1) - (1)].i)); ;}
    break;

  case 161:
#line 494 "src/c_parser.y"
    { (yyval.ast_node) = new Value((yyvsp[(1) - (1)].i)); ;}
    break;

  case 162:
#line 495 "src/c_parser.y"
    { (yyval.ast_node) = new Value((yyvsp[(1) - (1)].i)); ;}
    break;

  case 163:
#line 496 "src/c_parser.y"
    { (yyval.ast_node) = new Value((yyvsp[(1) - (1)].f)); ;}
    break;

  case 164:
#line 497 "src/c_parser.y"
    { (yyval.ast_node) = new Value((yyvsp[(1) - (1)].d)); ;}
    break;

  case 165:
#line 498 "src/c_parser.y"
    { (yyval.ast_node) = new Value((yyvsp[(1) - (1)].c)); ;}
    break;

  case 166:
#line 499 "src/c_parser.y"
    { (yyval.ast_node) = new Value((yyvsp[(1) - (1)].s)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2815 "src/c_parser.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 501 "src/c_parser.y"


