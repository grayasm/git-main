/* A Bison parser, made from grampar.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	TOK_INTEGER	257
# define	TOK_NAME	258
# define	TOK_STRING	259
# define	TOK_LIT_CODE	260
# define	TOK_LBRACE	261
# define	TOK_RBRACE	262
# define	TOK_COLON	263
# define	TOK_SEMICOLON	264
# define	TOK_ARROW	265
# define	TOK_LPAREN	266
# define	TOK_RPAREN	267
# define	TOK_COMMA	268
# define	TOK_TERMINALS	269
# define	TOK_TOKEN	270
# define	TOK_NONTERM	271
# define	TOK_FUN	272
# define	TOK_VERBATIM	273
# define	TOK_IMPL_VERBATIM	274
# define	TOK_PRECEDENCE	275
# define	TOK_OPTION	276
# define	TOK_EXPECT	277
# define	TOK_CONTEXT_CLASS	278
# define	TOK_SUBSETS	279
# define	TOK_DELETE	280
# define	TOK_REPLACE	281
# define	TOK_FORBID_NEXT	282

#line 6 "grampar.y"


#include "grampar.h"        // yylex, etc.
#include "gramast.ast.gen.h"// grammar syntax AST definition
#include "gramlex.h"        // GrammarLexer
#include "owner.h"          // Owner

#include <stdlib.h>         // malloc, free
#include <iostream.h>       // cout

// enable debugging the parser
#ifndef NDEBUG
  #define YYDEBUG 1
#endif

// name of extra parameter to yylex
#define YYLEX_PARAM parseParam

// make it call my yylex
#define yylex(lv, param) grampar_yylex(lv, param)

// Bison calls yyerror(msg) on error; we need the extra
// parameter too, so the macro shoehorns it in there
#define yyerror(msg) grampar_yyerror(msg, YYPARSE_PARAM)

// rename the externally-visible parsing routine to make it
// specific to this instance, so multiple bison-generated
// parsers can coexist
#define yyparse grampar_yyparse


// grab the parameter
#define PARAM ((ParseParams*)parseParam)

// return a locstring for 'str' with no location information
#define noloc(str)                                                    \
  new LocString(SL_UNKNOWN,      /* unknown location */               \
                PARAM->lexer.strtable.add(str))
                
// locstring for NULL, with no location
#define nolocNULL()                                                   \
  new LocString(SL_UNKNOWN, NULL)

// return a locstring with same location info as something else
// (passed as a pointer to a SourceLocation)
#define sameloc(otherLoc, str)                                        \
  new LocString(otherLoc->loc, PARAM->lexer.strtable.add(str))

// interpret the word into an associativity kind specification
AssocKind whichKind(LocString * /*owner*/ kind);


#line 105 "grampar.y"
#ifndef YYSTYPE
typedef union YYSTYPE {
  int num;
  LocString *str;
  SourceLoc loc;

  ASTList<TopForm> *topFormList;
  TopForm *topForm;

  ASTList<TermDecl> *termDecls;
  TermDecl *termDecl;
  ASTList<TermType> *termTypes;
  TermType *termType;
  ASTList<PrecSpec> *precSpecs;

  ASTList<SpecFunc> *specFuncs;
  SpecFunc *specFunc;
  ASTList<LocString> *stringList;

  ASTList<ProdDecl> *prodDecls;
  ProdDecl *prodDecl;
  ASTList<RHSElt> *rhsList;
  RHSElt *rhsElt;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		106
#define	YYFLAG		-32768
#define	YYNTBASE	29

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 282 ? yytranslate[x] : 56)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,     8,    10,    12,    14,    16,
      20,    23,    26,    30,    35,    42,    43,    46,    51,    57,
      59,    60,    61,    64,    69,    76,    77,    82,    83,    89,
      90,    93,    95,    97,    98,   101,   108,   109,   111,   113,
     117,   122,   131,   132,   135,   139,   144,   149,   151,   153,
     154,   157,   159,   163,   165,   169,   174,   179,   180
};
static const short yyrhs[] =
{
      30,     0,     0,    30,    31,     0,    32,     0,    33,     0,
      34,     0,    35,     0,    49,     0,    24,     6,    10,     0,
      19,     6,     0,    20,     6,     0,    22,     4,    10,     0,
      22,     4,     3,    10,     0,    15,     7,    36,    39,    41,
       8,     0,     0,    36,    37,     0,     3,     9,     4,    10,
       0,     3,     9,     4,     5,    10,     0,     6,     0,     0,
       0,    39,    40,     0,    16,    38,     4,    10,     0,    16,
      38,     4,     7,    45,     8,     0,     0,    21,     7,    42,
       8,     0,     0,    42,     4,     3,    43,    10,     0,     0,
      43,    44,     0,     4,     0,     5,     0,     0,    45,    46,
       0,    18,     4,    12,    47,    13,     6,     0,     0,    48,
       0,     4,     0,    48,    14,     4,     0,    17,    38,     4,
      51,     0,    17,    38,     4,     7,    45,    50,    55,     8,
       0,     0,    50,    51,     0,    11,    53,    52,     0,    27,
      11,    53,    52,     0,    26,    11,    53,    10,     0,     6,
       0,    10,     0,     0,    53,    54,     0,     4,     0,     4,
       9,     4,     0,     5,     0,     4,     9,     5,     0,    21,
      12,    44,    13,     0,    28,    12,    44,    13,     0,     0,
      25,    48,    10,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   162,   167,   168,   172,   173,   174,   175,   176,   180,
     185,   186,   191,   192,   203,   208,   209,   217,   219,   224,
     225,   229,   230,   234,   236,   241,   242,   246,   248,   253,
     254,   258,   259,   265,   266,   270,   275,   276,   280,   281,
     292,   295,   300,   301,   305,   306,   307,   311,   312,   316,
     317,   326,   327,   328,   329,   330,   331,   335,   336
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "TOK_INTEGER", "TOK_NAME", "TOK_STRING", 
  "TOK_LIT_CODE", "\"{\"", "\"}\"", "\":\"", "\";\"", "\"->\"", "\"(\"", 
  "\")\"", "\",\"", "\"terminals\"", "\"token\"", "\"nonterm\"", 
  "\"fun\"", "\"verbatim\"", "\"impl_verbatim\"", "\"precedence\"", 
  "\"option\"", "\"expect\"", "\"context_class\"", "\"subsets\"", 
  "\"delete\"", "\"replace\"", "\"forbid_next\"", "StartSymbol", 
  "TopFormList", "TopForm", "ContextClass", "Verbatim", "Option", 
  "Terminals", "TermDecls", "TerminalDecl", "Type", "TermTypes", 
  "TermType", "Precedence", "PrecSpecs", "NameOrStringList", 
  "NameOrString", "SpecFuncs", "SpecFunc", "FormalsOpt", "Formals", 
  "Nonterminal", "Productions", "Production", "Action", "RHS", "RHSElt", 
  "Subsets", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    29,    30,    30,    31,    31,    31,    31,    31,    32,
      33,    33,    34,    34,    35,    36,    36,    37,    37,    38,
      38,    39,    39,    40,    40,    41,    41,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    54,    54,    54,    55,    55
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     1,     1,     1,     1,     1,     3,
       2,     2,     3,     4,     6,     0,     2,     4,     5,     1,
       0,     0,     2,     4,     6,     0,     4,     0,     5,     0,
       2,     1,     1,     0,     2,     6,     0,     1,     1,     3,
       4,     8,     0,     2,     3,     4,     4,     1,     1,     0,
       2,     1,     3,     1,     3,     4,     4,     0,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       2,     1,     0,    20,     0,     0,     0,     0,     3,     4,
       5,     6,     7,     8,    15,    19,     0,    10,    11,     0,
       0,    21,     0,     0,    12,     9,     0,    16,    25,    33,
      49,     0,     0,    40,    13,     0,    20,     0,    22,     0,
      42,     0,    49,    49,     0,     0,    27,    14,     0,    34,
      57,    51,    53,    47,    48,     0,     0,    44,    50,     0,
       0,     0,    17,     0,     0,     0,     0,    43,     0,     0,
       0,     0,    46,    45,    18,    33,    23,     0,    26,    36,
      38,     0,    41,    52,    54,    31,    32,     0,     0,     0,
      29,     0,    37,    58,     0,    55,    56,    24,     0,     0,
      39,    28,    30,    35,     0,     0,     0
};

static const short yydefgoto[] =
{
     104,     1,     8,     9,    10,    11,    12,    21,    27,    16,
      28,    38,    39,    64,    98,    87,    40,    49,    91,    81,
      13,    50,    33,    57,    41,    58,    68
};

static const short yypact[] =
{
  -32768,    21,     1,    26,    31,    33,    48,    49,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    52,-32768,-32768,    10,
      47,    55,     4,    50,-32768,-32768,    53,-32768,    -7,-32768,
  -32768,    54,    56,-32768,-32768,    57,    26,    59,-32768,    51,
      45,    -3,-32768,-32768,     7,    60,-32768,-32768,    64,-32768,
       8,    61,-32768,-32768,-32768,    62,    63,-32768,-32768,     0,
      -3,    66,-32768,    37,    18,    65,    67,-32768,    70,    44,
      46,    46,-32768,-32768,-32768,-32768,-32768,    69,-32768,    67,
  -32768,    32,-32768,-32768,-32768,-32768,-32768,    68,    71,    -2,
  -32768,    72,    73,-32768,    75,-32768,-32768,-32768,    19,    74,
  -32768,-32768,-32768,-32768,    82,    83,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    58,
  -32768,-32768,-32768,-32768,-32768,   -71,    -6,-32768,-32768,     9,
  -32768,-32768,    23,    29,    11,-32768,-32768
};


#define	YYLAST		94


static const short yytable[] =
{
      88,    51,    52,    53,    51,    52,    97,    54,    14,    36,
      72,    29,    61,    23,    37,    30,    48,    62,    55,    30,
      24,    55,    77,    85,    86,    56,    78,   102,    56,   101,
      31,    32,    15,    66,    31,    32,     2,    17,     3,    18,
       4,     5,    93,     6,    75,     7,    94,    76,    83,    84,
      85,    86,    19,    59,    60,    20,    22,    25,    26,    47,
      34,    44,    35,    48,    63,    42,    46,    43,    65,    89,
      69,    80,    90,    67,    70,    71,    74,    79,    82,   100,
     103,    95,   105,   106,    96,    99,     0,    94,    92,    73,
       0,     0,     0,     0,    45
};

static const short yycheck[] =
{
      71,     4,     5,     6,     4,     5,     8,    10,     7,    16,
      10,     7,     5,     3,    21,    11,    18,    10,    21,    11,
      10,    21,     4,     4,     5,    28,     8,    98,    28,    10,
      26,    27,     6,    25,    26,    27,    15,     6,    17,     6,
      19,    20,    10,    22,     7,    24,    14,    10,     4,     5,
       4,     5,     4,    42,    43,     6,     4,    10,     3,     8,
      10,     4,     9,    18,     4,    11,     7,    11,     4,    75,
       9,     4,     3,    50,    12,    12,    10,    12,     8,     4,
       6,    13,     0,     0,    13,    13,    -1,    14,    79,    60,
      -1,    -1,    -1,    -1,    36
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 163 "grampar.y"
{ ((ParseParams*)parseParam)->treeTop = new GrammarAST(yyvsp[0].topFormList); yyval.num=0; ;
    break;}
case 2:
#line 167 "grampar.y"
{ yyval.topFormList = new ASTList<TopForm>; ;
    break;}
case 3:
#line 168 "grampar.y"
{ (yyval.topFormList=yyvsp[-1].topFormList)->append(yyvsp[0].topForm); ;
    break;}
case 4:
#line 172 "grampar.y"
{ yyval.topForm = yyvsp[0].topForm; ;
    break;}
case 5:
#line 173 "grampar.y"
{ yyval.topForm = yyvsp[0].topForm; ;
    break;}
case 6:
#line 174 "grampar.y"
{ yyval.topForm = yyvsp[0].topForm; ;
    break;}
case 7:
#line 175 "grampar.y"
{ yyval.topForm = yyvsp[0].topForm; ;
    break;}
case 8:
#line 176 "grampar.y"
{ yyval.topForm = yyvsp[0].topForm; ;
    break;}
case 9:
#line 181 "grampar.y"
{ yyval.topForm = new TF_context(yyvsp[-1].str); ;
    break;}
case 10:
#line 185 "grampar.y"
{ yyval.topForm = new TF_verbatim(false, yyvsp[0].str); ;
    break;}
case 11:
#line 186 "grampar.y"
{ yyval.topForm = new TF_verbatim(true, yyvsp[0].str); ;
    break;}
case 12:
#line 191 "grampar.y"
{ yyval.topForm = new TF_option(yyvsp[-1].str, 1); ;
    break;}
case 13:
#line 192 "grampar.y"
{ yyval.topForm = new TF_option(yyvsp[-2].str, yyvsp[-1].num); ;
    break;}
case 14:
#line 204 "grampar.y"
{ yyval.topForm = new TF_terminals(yyvsp[-3].termDecls, yyvsp[-2].termTypes, yyvsp[-1].precSpecs); ;
    break;}
case 15:
#line 208 "grampar.y"
{ yyval.termDecls = new ASTList<TermDecl>; ;
    break;}
case 16:
#line 209 "grampar.y"
{ (yyval.termDecls=yyvsp[-1].termDecls)->append(yyvsp[0].termDecl); ;
    break;}
case 17:
#line 218 "grampar.y"
{ yyval.termDecl = new TermDecl(yyvsp[-3].num, yyvsp[-1].str, sameloc(yyvsp[-1].str, "")); ;
    break;}
case 18:
#line 220 "grampar.y"
{ yyval.termDecl = new TermDecl(yyvsp[-4].num, yyvsp[-2].str, yyvsp[-1].str); ;
    break;}
case 19:
#line 224 "grampar.y"
{ yyval.str = yyvsp[0].str; ;
    break;}
case 20:
#line 225 "grampar.y"
{ yyval.str = nolocNULL(); ;
    break;}
case 21:
#line 229 "grampar.y"
{ yyval.termTypes = new ASTList<TermType>; ;
    break;}
case 22:
#line 230 "grampar.y"
{ (yyval.termTypes=yyvsp[-1].termTypes)->append(yyvsp[0].termType); ;
    break;}
case 23:
#line 235 "grampar.y"
{ yyval.termType = new TermType(yyvsp[-1].str, yyvsp[-2].str, new ASTList<SpecFunc>); ;
    break;}
case 24:
#line 237 "grampar.y"
{ yyval.termType = new TermType(yyvsp[-3].str, yyvsp[-4].str, yyvsp[-1].specFuncs); ;
    break;}
case 25:
#line 241 "grampar.y"
{ yyval.precSpecs = new ASTList<PrecSpec>; ;
    break;}
case 26:
#line 242 "grampar.y"
{ yyval.precSpecs = yyvsp[-1].precSpecs; ;
    break;}
case 27:
#line 247 "grampar.y"
{ yyval.precSpecs = new ASTList<PrecSpec>; ;
    break;}
case 28:
#line 249 "grampar.y"
{ (yyval.precSpecs=yyvsp[-4].precSpecs)->append(new PrecSpec(whichKind(yyvsp[-3].str), yyvsp[-2].num, yyvsp[-1].stringList)); ;
    break;}
case 29:
#line 253 "grampar.y"
{ yyval.stringList = new ASTList<LocString>; ;
    break;}
case 30:
#line 254 "grampar.y"
{ (yyval.stringList=yyvsp[-1].stringList)->append(yyvsp[0].str); ;
    break;}
case 31:
#line 258 "grampar.y"
{ yyval.str = yyvsp[0].str; ;
    break;}
case 32:
#line 259 "grampar.y"
{ yyval.str = yyvsp[0].str; ;
    break;}
case 33:
#line 265 "grampar.y"
{ yyval.specFuncs = new ASTList<SpecFunc>; ;
    break;}
case 34:
#line 266 "grampar.y"
{ (yyval.specFuncs=yyvsp[-1].specFuncs)->append(yyvsp[0].specFunc); ;
    break;}
case 35:
#line 271 "grampar.y"
{ yyval.specFunc = new SpecFunc(yyvsp[-4].str, yyvsp[-2].stringList, yyvsp[0].str); ;
    break;}
case 36:
#line 275 "grampar.y"
{ yyval.stringList = new ASTList<LocString>; ;
    break;}
case 37:
#line 276 "grampar.y"
{ yyval.stringList = yyvsp[0].stringList; ;
    break;}
case 38:
#line 280 "grampar.y"
{ yyval.stringList = new ASTList<LocString>(yyvsp[0].str); ;
    break;}
case 39:
#line 281 "grampar.y"
{ (yyval.stringList=yyvsp[-2].stringList)->append(yyvsp[0].str); ;
    break;}
case 40:
#line 293 "grampar.y"
{ yyval.topForm = new TF_nonterm(yyvsp[-1].str, yyvsp[-2].str, new ASTList<SpecFunc>,
                                     new ASTList<ProdDecl>(yyvsp[0].prodDecl), NULL); ;
    break;}
case 41:
#line 296 "grampar.y"
{ yyval.topForm = new TF_nonterm(yyvsp[-5].str, yyvsp[-6].str, yyvsp[-3].specFuncs, yyvsp[-2].prodDecls, yyvsp[-1].stringList); ;
    break;}
case 42:
#line 300 "grampar.y"
{ yyval.prodDecls = new ASTList<ProdDecl>; ;
    break;}
case 43:
#line 301 "grampar.y"
{ (yyval.prodDecls=yyvsp[-1].prodDecls)->append(yyvsp[0].prodDecl); ;
    break;}
case 44:
#line 305 "grampar.y"
{ yyval.prodDecl = new ProdDecl(yyvsp[-2].loc, PDK_NEW, yyvsp[-1].rhsList, yyvsp[0].str); ;
    break;}
case 45:
#line 306 "grampar.y"
{ yyval.prodDecl = new ProdDecl(yyvsp[-2].loc, PDK_REPLACE,yyvsp[-1].rhsList, yyvsp[0].str); ;
    break;}
case 46:
#line 307 "grampar.y"
{ yyval.prodDecl = new ProdDecl(yyvsp[-2].loc, PDK_DELETE, yyvsp[-1].rhsList, nolocNULL()); ;
    break;}
case 47:
#line 311 "grampar.y"
{ yyval.str = yyvsp[0].str; ;
    break;}
case 48:
#line 312 "grampar.y"
{ yyval.str = nolocNULL(); ;
    break;}
case 49:
#line 316 "grampar.y"
{ yyval.rhsList = new ASTList<RHSElt>; ;
    break;}
case 50:
#line 317 "grampar.y"
{ (yyval.rhsList=yyvsp[-1].rhsList)->append(yyvsp[0].rhsElt); ;
    break;}
case 51:
#line 326 "grampar.y"
{ yyval.rhsElt = new RH_name(sameloc(yyvsp[0].str, ""), yyvsp[0].str); ;
    break;}
case 52:
#line 327 "grampar.y"
{ yyval.rhsElt = new RH_name(yyvsp[-2].str, yyvsp[0].str); ;
    break;}
case 53:
#line 328 "grampar.y"
{ yyval.rhsElt = new RH_string(sameloc(yyvsp[0].str, ""), yyvsp[0].str); ;
    break;}
case 54:
#line 329 "grampar.y"
{ yyval.rhsElt = new RH_string(yyvsp[-2].str, yyvsp[0].str); ;
    break;}
case 55:
#line 330 "grampar.y"
{ yyval.rhsElt = new RH_prec(yyvsp[-1].str); ;
    break;}
case 56:
#line 331 "grampar.y"
{ yyval.rhsElt = new RH_forbid(yyvsp[-1].str); ;
    break;}
case 57:
#line 335 "grampar.y"
{ yyval.stringList = NULL; ;
    break;}
case 58:
#line 336 "grampar.y"
{ yyval.stringList = yyvsp[-1].stringList; ;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 340 "grampar.y"

/* ------------------ extra C code ------------------ */
AssocKind whichKind(LocString * /*owner*/ kind)
{ 
  // delete 'kind' however we exit
  Owner<LocString> killer(kind);
  
  #define CHECK(syntax, value)   \
    if (kind->equals(syntax)) {  \
      return value;              \
    }
  CHECK("left", AK_LEFT);
  CHECK("right", AK_RIGHT);
  CHECK("nonassoc", AK_NONASSOC);
  CHECK("prec", AK_NEVERASSOC);
  CHECK("assoc_split", AK_SPLIT);
  #undef CHECK

  xbase(stringc << kind->locString()
                << ": invalid associativity kind: " << *kind);
}
