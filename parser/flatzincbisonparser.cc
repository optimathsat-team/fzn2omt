/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         msat_flatzinc_parser_parse
#define yylex           msat_flatzinc_parser_lex
#define yyerror         msat_flatzinc_parser_error
#define yydebug         msat_flatzinc_parser_debug
#define yynerrs         msat_flatzinc_parser_nerrs


/* Copy the first part of user declarations.  */
#line 11 "parser/flatzincbisonparser.yy" /* yacc.c:339  */


#include "../utils/strutils.h"
#include "../utils/xmalloc.h"
#include "../utils/numinterval.h"
#include "../utils/numintervalset.h"
#include "../utils/numflatzincdomain.h"
#include "../parser/flatzincparser.h"
#include "../parser/flatzincannotation.h"
#include "../parser/flatzincbisonparser.h"
#include "../parser/flatzincflexlexer.h"
#include "../utils/smartptr.h"
#include <iostream>
#include <limits.h>
#include <stdlib.h>


#define YYMAXDEPTH LONG_MAX
#define YYLTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_TRIVIAL 1

#define UNUSED(x) (void)(x)
using namespace std;
using namespace msat;

inline void msat_flatzinc_parser_error(YYLTYPE *yylloc, yyscan_t scanner,
                                         msat::FlatZincAbstractParser *parser,
                                         const char *s)
{
    parser->handle_error(s);
}

namespace {

#define MSAT_SFREE(s) (parser->get_str_alloc()->str_free(s))

int64_t parser_atoi(msat::FlatZincAbstractParser *parser,
        const char *str)
{
    assert(str);
    uint64_t ret = strtoull(str, NULL, 0);
    if (ERANGE == errno) {
        std::stringstream ss;
        ss << "integer literal '" << str
           << "' does not fit into 64 bits";
        parser->handle_error(ss.str().c_str());
    } else if (EINVAL == errno) {
        std::stringstream ss;
        ss << "syntax error at '" << str
           << "' expected scalar int";
        parser->handle_error(ss.str().c_str());
    }
    return ret;
}

inline Number number_from_str(const char *str);

} // namespace


#line 133 "parser/flatzincbisonparser.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "flatzincbisonparser.hh".  */
#ifndef YY_MSAT_FLATZINC_PARSER_PARSER_FLATZINCBISONPARSER_HH_INCLUDED
# define YY_MSAT_FLATZINC_PARSER_PARSER_FLATZINCBISONPARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int msat_flatzinc_parser_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_PREDICATE = 258,
    TK_VAR = 259,
    TK_BOOL = 260,
    TK_FLOAT = 261,
    TK_INT = 262,
    TK_ARRAY = 263,
    TK_SET = 264,
    TK_OF = 265,
    TK_TRUE = 266,
    TK_FALSE = 267,
    TK_CONSTRAINT = 268,
    TK_SOLVE = 269,
    TK_MINIMIZE = 270,
    TK_MAXIMIZE = 271,
    TK_SATISFY = 272,
    TK_DOTDOT = 273,
    TK_COLONCOLON = 274,
    TK_EOF = 275,
    TK_ARRAY_BOOL_AND = 276,
    TK_ARRAY_BOOL_ELEMENT = 277,
    TK_ARRAY_BOOL_OR = 278,
    TK_ARRAY_BOOL_XOR = 279,
    TK_ARRAY_FLOAT_ELEMENT = 280,
    TK_ARRAY_INT_ELEMENT = 281,
    TK_ARRAY_SET_ELEMENT = 282,
    TK_ARRAY_VAR_BOOL_ELEMENT = 283,
    TK_ARRAY_VAR_FLOAT_ELEMENT = 284,
    TK_ARRAY_VAR_INT_ELEMENT = 285,
    TK_ARRAY_VAR_SET_ELEMENT = 286,
    TK_BOOL2INT = 287,
    TK_BOOL_AND = 288,
    TK_BOOL_CLAUSE = 289,
    TK_BOOL_EQ = 290,
    TK_BOOL_EQ_REIF = 291,
    TK_BOOL_LE = 292,
    TK_BOOL_LE_REIF = 293,
    TK_BOOL_LIN_EQ = 294,
    TK_BOOL_LIN_LE = 295,
    TK_BOOL_LT = 296,
    TK_BOOL_LT_REIF = 297,
    TK_BOOL_NOT = 298,
    TK_BOOL_OR = 299,
    TK_BOOL_XOR = 300,
    TK_FLOAT_ABS = 301,
    TK_FLOAT_DIV = 302,
    TK_FLOAT_ACOS = 303,
    TK_FLOAT_ASIN = 304,
    TK_FLOAT_ATAN = 305,
    TK_FLOAT_COS = 306,
    TK_FLOAT_COSH = 307,
    TK_FLOAT_EXP = 308,
    TK_FLOAT_LN = 309,
    TK_FLOAT_LOG10 = 310,
    TK_FLOAT_LOG2 = 311,
    TK_FLOAT_SQRT = 312,
    TK_FLOAT_SIN = 313,
    TK_FLOAT_SINH = 314,
    TK_FLOAT_TAN = 315,
    TK_FLOAT_TANH = 316,
    TK_FLOAT_EQ = 317,
    TK_FLOAT_EQ_REIF = 318,
    TK_FLOAT_LE = 319,
    TK_FLOAT_LE_REIF = 320,
    TK_FLOAT_LIN_EQ = 321,
    TK_FLOAT_LIN_EQ_REIF = 322,
    TK_FLOAT_LIN_LE = 323,
    TK_FLOAT_LIN_LE_REIF = 324,
    TK_FLOAT_LIN_LT = 325,
    TK_FLOAT_LIN_LT_REIF = 326,
    TK_FLOAT_LIN_NE = 327,
    TK_FLOAT_LIN_NE_REIF = 328,
    TK_FLOAT_LT = 329,
    TK_FLOAT_LT_REIF = 330,
    TK_FLOAT_MAX = 331,
    TK_FLOAT_MIN = 332,
    TK_FLOAT_NE = 333,
    TK_FLOAT_NE_REIF = 334,
    TK_FLOAT_PLUS = 335,
    TK_FLOAT_TIMES = 336,
    TK_INT_ABS = 337,
    TK_INT_DIV = 338,
    TK_INT_EQ = 339,
    TK_INT_EQ_REIF = 340,
    TK_INT_LE = 341,
    TK_INT_LE_REIF = 342,
    TK_INT_LIN_EQ = 343,
    TK_INT_LIN_EQ_REIF = 344,
    TK_INT_LIN_LE = 345,
    TK_INT_LIN_LE_REIF = 346,
    TK_INT_LIN_NE = 347,
    TK_INT_LIN_NE_REIF = 348,
    TK_INT_LT = 349,
    TK_INT_LT_REIF = 350,
    TK_INT_MAX = 351,
    TK_INT_MIN = 352,
    TK_INT_MOD = 353,
    TK_INT_NE = 354,
    TK_INT_NE_REIF = 355,
    TK_INT_PLUS = 356,
    TK_INT_TIMES = 357,
    TK_INT2FLOAT = 358,
    TK_SET_CARD = 359,
    TK_SET_DIFF = 360,
    TK_SET_EQ = 361,
    TK_SET_EQ_REIF = 362,
    TK_SET_IN = 363,
    TK_SET_IN_REIF = 364,
    TK_SET_INTERSECT = 365,
    TK_SET_LE = 366,
    TK_SET_LT = 367,
    TK_SET_NE = 368,
    TK_SET_NE_REIF = 369,
    TK_SET_SUBSET = 370,
    TK_SET_SUBSET_REIF = 371,
    TK_SET_SYMDIFF = 372,
    TK_SET_UNION = 373,
    TK_ALLDIFFERENT_EXCEPT_0 = 374,
    TK_ALL_DIFFERENT_INT = 375,
    TK_ALL_DIFFERENT_SET = 376,
    TK_ALL_DISJOINT = 377,
    TK_DISJOINT = 378,
    TK_DISJUNCTIVE = 379,
    TK_DISJUNCTIVE_STRICT = 380,
    TK_ALL_EQUAL_INT = 381,
    TK_ALL_EQUAL_SET = 382,
    TK_AMONG = 383,
    TK_MAXIMUM_FLOAT = 384,
    TK_MAXIMUM_INT = 385,
    TK_MINIMUM_FLOAT = 386,
    TK_MINIMUM_INT = 387,
    TK_ARRAY_FLOAT_MAXIMUM = 388,
    TK_ARRAY_INT_MAXIMUM = 389,
    TK_ARRAY_FLOAT_MINIMUM = 390,
    TK_ARRAY_INT_MINIMUM = 391,
    TK_MAXIMUM_ARG_INT = 392,
    TK_MAXIMUM_ARG_FLOAT = 393,
    TK_MINIMUM_ARG_INT = 394,
    TK_MINIMUM_ARG_FLOAT = 395,
    TK_AT_LEAST_INT = 396,
    TK_AT_LEAST_SET = 397,
    TK_EXACTLY_INT = 398,
    TK_EXACTLY_SET = 399,
    TK_AT_MOST_INT = 400,
    TK_AT_MOST_SET = 401,
    TK_ATMOST1 = 402,
    TK_BIN_PACKING_CAPA = 403,
    TK_BIN_PACKING_LOAD = 404,
    TK_BIN_PACKING = 405,
    TK_ELEMENT_BOOL = 406,
    TK_ELEMENT_FLOAT = 407,
    TK_ELEMENT_INT = 408,
    TK_ELEMENT_SET = 409,
    TK_COMPARISON_REL_ARRAY = 410,
    TK_COUNT_EQ = 411,
    TK_COUNT_GEQ = 412,
    TK_COUNT_GT = 413,
    TK_COUNT_LEQ = 414,
    TK_COUNT_LT = 415,
    TK_COUNT_NEQ = 416,
    TK_DECREASING_BOOL = 417,
    TK_DECREASING_FLOAT = 418,
    TK_DECREASING_INT = 419,
    TK_DECREASING_SET = 420,
    TK_INCREASING_BOOL = 421,
    TK_INCREASING_FLOAT = 422,
    TK_INCREASING_INT = 423,
    TK_INCREASING_SET = 424,
    TK_DIFFN = 425,
    TK_DIFFN_NONSTRICT = 426,
    TK_DIFFN_NONOVERLAP_K = 427,
    TK_DIFFN_NONSTRICT_NONOVERLAP_K = 428,
    TK_DISTRIBUTE = 429,
    TK_GEOST_NONOVERLAP_K = 430,
    TK_GLOBAL_CARDINALITY = 431,
    TK_GLOBAL_CARDINALITY_CLOSED = 432,
    TK_GLOBAL_CARDINALITY_LOW_UP = 433,
    TK_GLOBAL_CARDINALITY_LOW_UP_CLOSED = 434,
    TK_INT_SET_CHANNEL = 435,
    TK_INVERSE = 436,
    TK_INVERSE_SET = 437,
    TK_LINK_SET_TO_BOOLEANS = 438,
    TK_MEMBER_BOOL = 439,
    TK_MEMBER_FLOAT = 440,
    TK_MEMBER_INT = 441,
    TK_MEMBER_SET = 442,
    TK_NVALUE = 443,
    TK_RANGE = 444,
    TK_BOOL_CLAUSE_REIF = 445,
    TK_FLOAT_IN = 446,
    TK_FLOAT_DOM = 447,
    TK_ROOTS = 448,
    TK_SUM_PRED = 449,
    TK_SYMMETRIC_ALL_DIFFERENT = 450,
    TK_VALUE_PRECEDE_INT = 451,
    TK_VALUE_PRECEDE_SET = 452,
    TK_OUTPUT_VAR = 453,
    TK_OUTPUT_ARRAY = 454,
    IDENT = 455,
    UNDERSCORE_IDENT = 456,
    STRING_LITERAL = 457,
    INT_LITERAL = 458,
    FLOAT_LITERAL = 459
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 83 "parser/flatzincbisonparser.yy" /* yacc.c:355  */

    char *string;
    const msat::Term_ *term;
    std::vector<msat::Number> *numlist;
    std::vector<int64_t> *intlist;
    msat::NumFlatZincDomain *domain;
    msat::FznNode *node;
    msat::FlatZincAnnotation *annotation;

#line 388 "parser/flatzincbisonparser.cc" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int msat_flatzinc_parser_parse (yyscan_t scanner, msat::FlatZincAbstractParser *parser);

#endif /* !YY_MSAT_FLATZINC_PARSER_PARSER_FLATZINCBISONPARSER_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 418 "parser/flatzincbisonparser.cc" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  336
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2699

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  215
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  507
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1902

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   459

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     206,   207,     2,     2,   212,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   208,   205,
       2,   209,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   210,     2,   211,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   213,     2,   214,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   361,   361,   365,   369,   373,   377,   384,   385,   386,
     387,   391,   392,   396,   407,   411,   418,   419,   420,   421,
     430,   438,   446,   454,   468,   487,   504,   521,   545,   551,
     558,   565,   571,   578,   584,   591,   604,   621,   638,   655,
     672,   689,   706,   723,   746,   753,   767,   774,   779,   784,
     789,   794,   799,   804,   809,   814,   819,   823,   827,   833,
     837,   841,   845,   849,   855,   861,   865,   869,   873,   877,
     881,   885,   889,   893,   897,   901,   905,   909,   913,   917,
     921,   925,   929,   933,   937,   941,   945,   949,   953,   957,
     961,   967,   973,   979,   985,   991,   997,  1003,  1009,  1013,
    1017,  1021,  1025,  1029,  1033,  1037,  1041,  1045,  1049,  1053,
    1057,  1061,  1065,  1071,  1077,  1083,  1089,  1095,  1101,  1105,
    1109,  1113,  1117,  1121,  1125,  1129,  1133,  1137,  1141,  1147,
    1153,  1157,  1164,  1170,  1176,  1181,  1186,  1193,  1199,  1205,
    1211,  1217,  1223,  1229,  1236,  1243,  1246,  1256,  1264,  1267,
    1273,  1276,  1282,  1286,  1297,  1298,  1302,  1303,  1304,  1305,
    1306,  1307,  1308,  1309,  1310,  1317,  1318,  1322,  1323,  1324,
    1325,  1326,  1327,  1328,  1329,  1337,  1344,  1348,  1356,  1364,
    1370,  1379,  1383,  1402,  1403,  1404,  1405,  1411,  1421,  1422,
    1423,  1424,  1430,  1440,  1444,  1454,  1458,  1464,  1473,  1477,
    1485,  1490,  1499,  1503,  1509,  1518,  1522,  1530,  1535,  1548,
    1549,  1550,  1551,  1558,  1568,  1569,  1570,  1571,  1578,  1588,
    1600,  1604,  1610,  1619,  1623,  1631,  1636,  1645,  1649,  1655,
    1664,  1668,  1676,  1681,  1694,  1695,  1696,  1697,  1704,  1714,
    1715,  1716,  1717,  1724,  1734,  1746,  1750,  1756,  1765,  1769,
    1777,  1782,  1791,  1795,  1801,  1810,  1814,  1822,  1827,  1840,
    1841,  1842,  1843,  1844,  1851,  1865,  1869,  1879,  1887,  1895,
    1901,  1910,  1916,  1924,  1931,  1935,  1941,  1950,  1956,  1964,
    1975,  1978,  1984,  1987,  1990,  1994,  1998,  2002,  2005,  2008,
    2013,  2016,  2019,  2024,  2029,  2033,  2037,  2048,  2053,  2059,
    2064,  2070,  2076,  2084,  2093,  2103,  2104,  2105,  2106,  2107,
    2111,  2112,  2113,  2117,  2125,  2126,  2127,  2128,  2129,  2130,
    2131,  2132,  2133,  2134,  2135,  2136,  2137,  2138,  2139,  2140,
    2141,  2142,  2143,  2144,  2145,  2146,  2147,  2148,  2149,  2150,
    2151,  2152,  2153,  2154,  2155,  2156,  2157,  2158,  2159,  2160,
    2167,  2172,  2177,  2185,  2191,  2199,  2205,  2214,  2219,  2227,
    2236,  2241,  2249,  2254,  2262,  2267,  2275,  2280,  2289,  2301,
    2317,  2329,  2344,  2349,  2358,  2363,  2372,  2377,  2383,  2391,
    2405,  2419,  2428,  2439,  2450,  2461,  2476,  2484,  2489,  2494,
    2499,  2504,  2509,  2517,  2522,  2527,  2532,  2540,  2545,  2550,
    2555,  2563,  2571,  2579,  2587,  2599,  2609,  2621,  2628,  2635,
    2643,  2654,  2677,  2698,  2722,  2739,  2744,  2749,  2754,  2763,
    2771,  2789,  2798,  2802,  2811,  2829,  2852,  2867,  2872,  2880,
    2881,  2882,  2883,  2884,  2885,  2886,  2887,  2888,  2889,  2890,
    2891,  2892,  2893,  2894,  2895,  2896,  2897,  2898,  2899,  2900,
    2901,  2902,  2903,  2904,  2905,  2906,  2907,  2908,  2909,  2910,
    2911,  2912,  2913,  2914,  2915,  2916,  2917,  2918,  2919,  2920,
    2921,  2922,  2923,  2924,  2925,  2926,  2927,  2928,  2929,  2930,
    2931,  2932,  2933,  2934,  2935,  2936,  2937,  2938,  2939,  2940,
    2941,  2942,  2943,  2944,  2945,  2946,  2947,  2948,  2949,  2950,
    2951,  2952,  2953,  2954,  2955,  2956,  2957,  2958
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"predicate\"", "\"var\"", "\"bool\"",
  "\"float\"", "\"int\"", "\"array\"", "\"set\"", "\"of\"", "\"true\"",
  "\"false\"", "\"constraint\"", "\"solve\"", "\"minimize\"",
  "\"maximize\"", "\"satisfy\"", "\"..\"", "\"::\"", "TK_EOF",
  "\"array_bool_and\"", "\"array_bool_element\"", "\"array_bool_or\"",
  "\"array_bool_xor\"", "\"array_float_element\"", "\"array_int_element\"",
  "\"array_set_element\"", "\"array_var_bool_element\"",
  "\"array_var_float_element\"", "\"array_var_int_element\"",
  "\"array_var_set_element\"", "\"bool2int\"", "\"bool_and\"",
  "\"bool_clause\"", "\"bool_eq\"", "\"bool_eq_reif\"", "\"bool_le\"",
  "\"bool_le_reif\"", "\"bool_lin_eq\"", "\"bool_lin_le\"", "\"bool_lt\"",
  "\"bool_lt_reif\"", "\"bool_not\"", "\"bool_or\"", "\"bool_xor\"",
  "\"float_abs\"", "\"float_div\"", "\"float_acos\"", "\"float_asin\"",
  "\"float_atan\"", "\"float_cos\"", "\"float_cosh\"", "\"float_exp\"",
  "\"float_ln\"", "\"float_log10\"", "\"float_log2\"", "\"float_sqrt\"",
  "\"float_sin\"", "\"float_sinh\"", "\"float_tan\"", "\"float_tanh\"",
  "\"float_eq\"", "\"float_reif\"", "\"float_le\"", "\"float_le_reif\"",
  "\"float_lin_eq\"", "\"float_lin_eq_reif\"", "\"float_lin_le\"",
  "\"float_lin_le_reif\"", "\"float_lin_lt\"", "\"float_lin_lt_reif\"",
  "\"float_lin_ne\"", "\"float_lin_ne_reif\"", "\"float_lt\"",
  "\"float_lt_reif\"", "\"float_max\"", "\"float_min\"", "\"float_ne\"",
  "\"float_ne_reif\"", "\"float_plus\"", "\"float_times\"", "\"int_abs\"",
  "\"int_div\"", "\"int_eq\"", "\"int_eq_reif\"", "\"int_le\"",
  "\"int_le_reif\"", "\"int_lin_eq\"", "\"int_lin_eq_reif\"",
  "\"int_lin_le\"", "\"int_lin_le_reif\"", "\"int_lin_ne\"",
  "\"int_lin_ne_reif\"", "\"int_lt\"", "\"int_lt_reif\"", "\"int_max\"",
  "\"int_min\"", "\"int_mod\"", "\"int_ne\"", "\"int_ne_reif\"",
  "\"int_plus\"", "\"int_times\"", "\"int2float\"", "\"set_card\"",
  "\"set_diff\"", "\"set_eq\"", "\"set_eq_reif\"", "\"set_in\"",
  "\"set_in_reif\"", "\"set_intersect\"", "\"set_le\"", "\"set_lt\"",
  "\"set_ne\"", "\"set_ne_reif\"", "\"set_subset\"", "\"set_subset_reif\"",
  "\"set_symdiff\"", "\"set_union\"",
  "\"optimathsat_alldifferent_except_0\"",
  "\"optimathsat_all_different_int\"", "\"optimathsat_all_different_set\"",
  "\"optimathsat_all_disjoint\"", "\"optimathsat_disjoint\"",
  "\"optimathsat_disjunctive\"", "\"optimathsat_disjunctive_strict\"",
  "\"optimathsat_all_equal_int\"", "\"optimathsat_all_equal_set\"",
  "\"optimathsat_among\"", "\"optimathsat_maximum_float\"",
  "\"optimathsat_maximum_int\"", "\"optimathsat_minimum_float\"",
  "\"optimathsat_minimum_int\"", "\"optimathsat_array_float_maximum\"",
  "\"optimathsat_array_int_maximum\"",
  "\"optimathsat_array_float_minimum\"",
  "\"optimathsat_array_int_minimum\"", "\"optimathsat_maximum_arg_int\"",
  "\"optimathsat_maximum_arg_float\"", "\"optimathsat_minimum_arg_int\"",
  "\"optimathsat_minimum_arg_float\"", "\"optimathsat_at_least_int\"",
  "\"optimathsat_at_least_set\"", "\"optimathsat_exactly_int\"",
  "\"optimathsat_exactly_set\"", "\"optimathsat_at_most_int\"",
  "\"optimathsat_at_most_set\"", "\"optimathsat_at_most1\"",
  "\"optimathsat_bin_packing_capa\"", "\"optimathsat_bin_packing_load\"",
  "\"optimathsat_bin_packing\"", "\"optimathsat_element_bool\"",
  "\"optimathsat_element_float\"", "\"optimathsat_element_int\"",
  "\"optimathsat_element_set\"", "\"optimathsat_comparison_rel_array\"",
  "\"optimathsat_count_eq\"", "\"optimathsat_count_geq\"",
  "\"optimathsat_count_gt\"", "\"optimathsat_count_leq\"",
  "\"optimathsat_count_lt\"", "\"optimathsat_count_neq\"",
  "\"optimathsat_decreasing_bool\"", "\"optimathsat_decreasing_float\"",
  "\"optimathsat_decreasing_int\"", "\"optimathsat_decreasing_set\"",
  "\"optimathsat_increasing_bool\"", "\"optimathsat_increasing_float\"",
  "\"optimathsat_increasing_int\"", "\"optimathsat_increasing_set\"",
  "\"optimathsat_diffn\"", "\"optimathsat_diffn_nonstrict\"",
  "\"optimathsat_diffn_nonoverlap_k\"",
  "\"optimathsat_diffn_nonstrict_nonoverlap_k\"",
  "\"optimathsat_distribute\"", "\"optimathsat_geost_nonoverlap_k\"",
  "\"optimathsat_global_cardinality\"",
  "\"optimathsat_global_cardinality_closed\"",
  "\"optimathsat_global_cardinality_low_up\"",
  "\"optimathsat_global_cardinality_low_up_closed\"",
  "\"optimathsat_int_set_channel\"", "\"optimathsat_inverse\"",
  "\"optimathsat_inverse_set\"", "\"optimathsat_link_set_to_booleans\"",
  "\"optimathsat_member_bool\"", "\"optimathsat_member_float\"",
  "\"optimathsat_member_int\"", "\"optimathsat_member_set\"",
  "\"optimathsat_nvalue\"", "\"optimathsat_range\"",
  "\"optimathsat_bool_clause_reif\"", "\"optimathsat_float_in\"",
  "\"optimathsat_float_dom\"", "\"optimathsat_roots\"",
  "\"optimathsat_sum_pred\"", "\"optimathsat_symmetric_all_different\"",
  "\"optimathsat_value_precede_int\"", "\"optimathsat_value_precede_set\"",
  "\"output_var\"", "\"output_array\"", "IDENT", "UNDERSCORE_IDENT",
  "STRING_LITERAL", "INT_LITERAL", "FLOAT_LITERAL", "';'", "'('", "')'",
  "':'", "'='", "'['", "']'", "','", "'{'", "'}'", "$accept",
  "whole_model", "declarations", "constraints", "error_state",
  "pred_decl_item", "decl_item", "par_decl_item", "array_par_decl_item",
  "var_decl_item", "array_var_decl_item", "ident_anns", "constraint_item",
  "constraint_elem", "solve_item", "solve_kind", "objectives", "objective",
  "pred_decl_args", "pred_decl_arg", "pred_arg_array_index",
  "pred_arg_array_tail", "bool_ti_expr_tail", "int_ti_expr_tail",
  "num_literals", "float_ti_expr_tail", "par_bool_expr", "var_bool_expr",
  "bool_literal", "array_par_bool_expr", "array_par_bool_literal",
  "array_par_bool_elements", "array_var_bool_expr",
  "array_var_bool_literal", "array_var_bool_elements", "par_int_expr",
  "var_int_expr", "int_literal", "array_par_int_expr",
  "array_par_int_literal", "array_par_int_elements", "array_var_int_expr",
  "array_var_int_literal", "array_var_int_elements", "par_float_expr",
  "var_float_expr", "float_literal", "array_par_float_expr",
  "array_par_float_literal", "array_par_float_elements",
  "array_var_float_expr", "array_var_float_literal",
  "array_var_float_elements", "var_num_expr", "set_literal",
  "set_elements", "set_array_literal", "set_array_elements",
  "ignored_exprs", "ignored_expr", "annotations", "shape_list",
  "ignored_annotations", "ignored_shape_list", "ignored_shape",
  "global_constraints", "all_different", "disjoint", "disjunctive",
  "all_equal", "among", "maximum", "minimum", "maximum_array",
  "minimum_array", "maximum_arg", "minimum_arg", "at_least", "exactly",
  "at_most", "bin_packing", "element", "comparison_rel_array", "count",
  "decreasing", "increasing", "diffn", "distribute", "geost",
  "global_cardinality", "int_set_channel", "inverse",
  "link_set_to_booleans", "member", "nvalue", "range", "bool_clause_reif",
  "float_dom", "roots", "sum_pred", "symmetric_all_different",
  "value_precede", "global_ident", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,    59,    40,    41,    58,    61,
      91,    93,    44,   123,   125
};
# endif

#define YYPACT_NINF -1087

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1087)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      82,  1681,    26, -1087, -1087, -1087,  -188,    24,  2499, -1087,
      32,    39,  -161,    77,    46,    89, -1087,   -86,   -70, -1087,
   -1087, -1087, -1087,   -58,   -36,   -71,   -50,   -34, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087,   -30,   -13,   185,
     -11,     8,    14,     9,    12,    18,    20,    27,    41,    65,
      69,    85,   101,   103,   106,   116,   117,   123,   175,   176,
     177,   180,   181,   182,   189,   190,   191,   192,   194,   196,
     198,   200,   205,   206,   207,   209,   212,   214,   215,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     241,   242,   243,   244,   245,   247,   248,   249,   250,   251,
     254,   255,   256,   257,   258,   260,   261,   262,   266,   268,
     269,   271,   272,   273,   275,   276,   277,   278,   282,   284,
     285,   286,   288,   291,   292,   293,   294,   296,   297,   298,
     299,   300,   301,   302,   305,   309,   311,   313,   314,   315,
     316,   317,   318,   324,   326,   327,   328,   330,   331,   335,
     336,   337,   338,   340,   341,   342,   343,   344,   345,   346,
     350,   353,   355,   356,   357,   358,   365,   367,   368,   369,
     372,   374,   381,   383,   384,   388,   390,   391,   392,   393,
     394,   395,   396,   398,   400,   409,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   432,   433,   434,   435,   436,   437,   439,   440,   441,
     442,   443,   444,   445,   446,   452,   453,   454,   455,   459,
     461,   462,   463, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087,   156,    15,    83,    33,    22, -1087,    89,    47,   143,
      64,    64,   378, -1087,  -108,  -108,  -108,    40,    40,    12,
    -108,  -108,  -108,   471,   265,   -87,    37,   -87,   -87,    37,
      37,    37,    37,    37,    37,    37,   110,   110,   -87,   110,
     110,   110,   110,   -76,   -76,   110,   110,   110,   110,   110,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,    37,    37,    37,    37,
      37,    37,   -76,   -76,   -76,   -76,   -76,   -76,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,  -119,  -119,
    -119,  -119,    37,    37,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,   -55,   -55,   -51,   -51,  -119,   -55,   -55,
     -55,   -51,    37,   -10,    37,   -10,    37,   -10,    37,   -10,
      37,   -55,   -44,   -55,   -44,   105,   105,   105,   105,   105,
     105,   -51,   -76,   -55,   105,    37,    37,    37,    37,   -55,
     -55,   -55,   -55,   -55,   -55,   -55,   -87,   -44,   -55,   -51,
     -87,   -44,   -55,   -51,   -55,   -55,   -55,   -55,   -55,   -55,
     -55,   -55,   -55,   -55,   -55,   -55,   -51,  -119,   -87,   -44,
     -55,   -51,    37,   -55,   -87,   -10,   -10,   -55,    37,   -55,
     105,   105,   382,   512,   -22,   -22, -1087,    81, -1087,   360,
   -1087, -1087, -1087,  -161, -1087,   468, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087,   379,   466,   469,   122,   467,   669,   473,
     470,   477,   479,   482,   474,   486,   488,   489,   490,   492,
    -108, -1087, -1087,   208,   491, -1087,   494,   495, -1087,   496,
   -1087,   497,   493,   498,   500,   506,   509,   510,   515,   516,
   -1087, -1087,   519,   520,   521, -1087,   522,   524,   529,   530,
     531,   532, -1087, -1087,  -137,   533, -1087,   539,   540,   541,
     542,   543,   544,   547,   548, -1087,   549, -1087,   550,   551,
     552,   553,   554,   555,   556,   557,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569, -1087, -1087,  -103,
     570, -1087,   571,   572,   573,   574,   575,   576,   577,   578,
     579,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   599,
     600,   601,   602,   603,   604,   605,   606,   607,   608,   611,
     613,   684,   503,   614,   615,   617,   621,   622,   623,   624,
     625,   626,   627,   628,   629,   630,   631,   632, -1087, -1087,
    -101,   525, -1087,   618, -1087, -1087,  -119,   638,   639,   635,
     636,   637,   643,   644,   640,   647,   648,   649,   650,   651,
     652,   662,   663,   664, -1087, -1087,   -68,   665, -1087,   666,
     667,   671,   672,   673, -1087,   674,   675,   676,   677,   678,
     685,   679,   681,   682,   683,   686,   690,   691,   701,   702,
     703,   704,   705,   707,   708,   689,   714,   718,   719,   720,
     721,   722,   723,   724,   725,   726,   727,   728,   736,   737,
     738,   739,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   756,   758,   759,
     761, -1087, -1087,   -80,   687, -1087,   865, -1087,   366,   325,
     767,   763,   766,   768, -1087, -1087, -1087, -1087, -1087,   501,
     729,   148, -1087, -1087,   912,   912,   127,   105,    31,   874,
     769,   771,   772,    10,    12, -1087,    40,   732,   733,   734,
   -1087,  -108,   110,    37,   -10,   770,   773, -1087, -1087,  -132,
     110,   780,   782,   -40,   110, -1087,   -59,   -76,   -51,   -87,
     -44,   -55,   -51,   783,   784,    37,   110,   -87,   110,   110,
     110,   110, -1087, -1087,    -1,   -87,   -87,   110,   110,   110,
     110,   110,   785,   786,   -10,   -10,   -10,   -10,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,   -10,
     -10,   -10,   -10,   -10,   781,   787, -1087, -1087, -1087,    30,
     -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,   -10,    37,    37,    37,    37,
      37,    37,   -55,   -55,   -55,   -55,   -55,   -55,    37,    37,
      37,    37,    37,    37,    37,    37,    37,   -10,   789,   790,
     791, -1087,  -173,    37,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119, -1087, -1087,
      48, -1087, -1087, -1087,   107, -1087, -1087,  -119,   -55,   -55,
   -1087, -1087,   -55,   -44,   -44,   -44,   -55,   -44,   -55,   -44,
     -55,    37, -1087, -1087,   132,    37,    37,    37,   792,   793,
     -55,   -51,   -55,   -51,   -55,   -51, -1087,   -55,   -55,   -55,
     -87,   -44,   -55,   -51,    37,    37,    37,    37,    37,    37,
      37, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,   -55,
     -55,   -55,   -55,   -55,   -76,   -76,   -76,   -76,   -76,   -51,
     -55,   -51,   -87,   110,   -10,    37,  -119,   -55,  -119,   -87,
      31,   -59,  -119,   -51,   795,   105,   105,   382,   796,   797,
     798, -1087,   779, -1087,   545, -1087,   382,   799,   800,   794,
     382, -1087,   142,   801,   802, -1087, -1087, -1087, -1087,    12,
     805,   806,   807, -1087,   990,   803,   808, -1087, -1087, -1087,
   -1087,   804, -1087, -1087, -1087,   999,  -119, -1087,   110,   810,
     809,   813, -1087, -1087,   216,   814, -1087,   811,   815,   816,
     817,   818,   819,   820,   821,   823,   824,   812,   825,   829,
     831,   827,   833,   830, -1087,   105,   832,   834,   836,   835,
     838,   839,   840,   837,   842,   843,   844,   847,   848,   850,
     851,   852,   853,   854,   855,   856,   857,   858,   859,   861,
     862,   863,   860,   864,   866,   822,   870, -1087,    31,   867,
     868,   869,   871,   872,   873,   875,   876,   879,   877,   878,
     880,   884,   881,   882,   883,   889,   887,   893,   890,   894,
     891,   892,   895,   896,   897,   898,   899,   905,   902,   903,
     904,   907,   910,   908,   909,   911,   915,   913,   914, -1087,
     923, -1087,   920,   916,   922,   918,   927,   934,   935,   928,
     941,   943,   939,   945,   950,   951,   952, -1087,    37, -1087,
    -119,   946,   958,   959,   955,   961,   962,   963,   970,   971,
     972,   974,   975,   973, -1087,   -10,   976,   977,   978,   981,
     982,   983,   985,   986,   987,   988,   989,   992,   993,   995,
     998,  1000,  1002,  1005,   980,  1006,  1007,  1008,  1009,  1010,
    1011,  1012,  1013,  1015,  1017,  1019,  1020,  1021,  1022,  1023,
    1025,  1033,  1034,  1035,  1036,  1004,  1042,  1043,  1046,  1047,
    1045,  1048,  1050,  1052,  1053,  1054,   997,  1055,  1057,  1051,
     991,  1059, -1087, -1087, -1087, -1087,  1061,  1062,  1056,  1067,
   -1087,   900,  1071,  1072,  1075,  1074, -1087, -1087, -1087,  1076,
    1031,   984,  -119,   100, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087,   150,   110, -1087,   -10,    37,  -119,   110,   -10,    37,
    -119, -1087, -1087, -1087,   110, -1087, -1087,   110, -1087,   110,
   -1087,    37,   105, -1087,   110, -1087,   110,   110, -1087, -1087,
   -1087,   -10, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087,   110, -1087,   110,
    1073,  1078, -1087,    31,    31,    31,    31,    31,    31,    31,
      31, -1087,   110,   -10,   -10, -1087,   110,   -10,   -10, -1087,
      37, -1087,   110, -1087,   110,   105,   105,   105,   105,   105,
     105, -1087,   110,    37,    37,    37, -1087,   110,    37,    37,
   -1087, -1087, -1087, -1087, -1087,  -119, -1087,   110, -1087,   110,
    -119, -1087, -1087, -1087,   110, -1087,   110,  -119,  -119, -1087,
   -1087, -1087, -1087, -1087,  -119, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087,  1077, -1087,  1080,  1082,  1084, -1087, -1087,
     105,  -119,   105,  -119,   105,  -119,   -76,   -76,   -76,   110,
     -10,    37,  -119, -1087,    37,    37,    37,    37,    37,    37,
     -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -76,   -76,
    1087,  1088,  1089,  1094, -1087, -1087, -1087, -1087, -1087,  -119,
     110,    31,    31,  -119,   -76,  1096,   -55,   -51, -1087, -1087,
   -1087, -1087, -1087,  1003,   152, -1087, -1087,  1090,   382,  1095,
    1097,   994, -1087,   111, -1087, -1087,   267,  1064,  1101,  1102,
    1103, -1087,   127,  1105,  1106,  1107,  1108,  1109,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,  1122,  1126,
    1127,  1130, -1087, -1087,  1131,  1128,  1132,  1129,  1135,  1133,
    1136,  1134,  1137,  1140,  1141,  1142,  1143,  1144,  1145,  1146,
    1147,  1148,  1150,  1149,  1151,  1157,  1153,  1159,  1160,  1161,
    1162,  1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,
    1172,  1173,  1174,  1340,  1364,  1365,  1366,  1178,  1179,  1180,
    1182,  1190,  1192,  1188,  1189,  1195,  1191,  1193,  1194,  1196,
    1197,  1200,  1202,  1203,  1204,  1205,  1201,  1209,  1210,  1214,
    1207,  1215,  1208,  1221,  1217,  1218,  1398,  1413,  1414,  1415,
    1224,  1230,  1231,  1228,  1229,  1232,  1235,  1236,  1238,  1243,
    1240,  1056,  1245,  1262, -1087, -1087, -1087,   283,  1460,  1263,
   -1087, -1087, -1087,  1463,  1266,  1267,  1268,    12,  -108,  -108,
    -108, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087,   110, -1087,   110, -1087,   110, -1087,   110, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,   110,
   -1087,   110, -1087,   110, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
    1282,  1283,  1284,  1285, -1087, -1087, -1087, -1087, -1087, -1087,
    1286,  1287, -1087,  1288,  1289,  1291,  1292, -1087, -1087, -1087,
   -1087, -1087, -1087,   -55,   -55,   -55,   -55, -1087,   -76, -1087,
   -1087,   -76,   -76,  1293,  1294,  1295,  1296,  1297, -1087, -1087,
      31,  1299,    37, -1087, -1087, -1087, -1087, -1087, -1087,  1485,
     164, -1087,  1496, -1087, -1087, -1087,    12,  1309,    12,  -108,
    -108,  -108,  1303,  1304,  1305,  1306,  1310,  1311,  1312,  1313,
    1314,  1315,  1316,  1317,  1318,  1319,  1320,  1498,  1510,  1511,
    1512,  1513,  1515,  1328,  1330,  1332,  1333,  1335,  1339,  1341,
    1337,  1338,  1342,  1344,  1534,  1346,  1537,  1345,  1353,  1352,
    1358,    12, -1087, -1087,  1355,  1356,  1357,  1359,  -108,   -40,
     -76,   -59, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087,  1361,  1367,  1368,  1369,  1370,  1371, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087,  1372,  1373,  1374, -1087,
    1375, -1087,  1376,  1377, -1087, -1087,  1549, -1087,  -108,   -87,
     -55,   -44,  1360, -1087, -1087, -1087,  1378,  1379,  1380,  1381,
    1382,  1383,  1563,  1564,  1565,  1384,  1385,  1566,  1390,  1387,
   -1087, -1087, -1087,   -51, -1087, -1087, -1087, -1087, -1087, -1087,
    1394,  1395,  1396, -1087, -1087,  1397, -1087,   -51, -1087,  1399,
    1400,  1401,  1389, -1087, -1087, -1087, -1087,  1402,  1584,  1406,
    1403, -1087
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      13,     0,     0,   175,   181,   176,     0,     0,     0,   309,
       0,     0,     0,     0,     0,     0,     6,     0,     0,    16,
      17,    18,    19,     0,     0,     0,     0,     0,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   309,   145,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   341,   340,   342,   343,   344,   345,   346,   347,   348,
     349,     0,     0,     0,   180,     0,     1,     0,     0,     0,
       9,    10,    12,     5,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,     0,     0,   148,     0,   147,   149,
     151,   177,   182,     0,   178,     0,     3,     4,     7,     8,
      11,   301,   301,     0,     0,     0,     0,     0,     0,     0,
     155,     0,     0,     0,     0,     0,    31,    32,    33,     0,
       0,   203,   204,     0,     0,   202,   215,   216,   219,     0,
     214,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     194,   193,   189,   190,     0,   188,     0,     0,     0,     0,
       0,     0,   221,   222,     0,     0,   220,     0,     0,     0,
       0,     0,     0,   240,   241,   244,     0,   239,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   246,   247,     0,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   269,
     270,     0,   273,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   228,   229,
       0,     0,   227,     0,   275,   276,   279,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   253,   254,     0,     0,   252,     0,
       0,   210,   211,     0,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   283,   282,   294,   295,   286,   284,   285,     0,     0,
       0,   281,   261,   262,   259,   260,   152,   153,   305,     0,
     307,     0,   179,     2,    44,    45,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,     0,     0,     0,     0,
      15,     0,     0,     0,     0,     0,     0,   206,   208,     0,
       0,     0,     0,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   224,   226,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   235,   236,   249,   251,   234,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   272,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   231,   233,
       0,   350,   351,   278,     0,   352,   354,     0,     0,     0,
     357,   358,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   256,   258,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   393,   394,   395,   396,   397,   398,   399,   400,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   291,     0,   288,     0,   146,     0,     0,     0,     0,
       0,   150,     0,   184,   185,    20,   183,    21,    22,     0,
       0,     0,     0,   165,     0,     0,     0,   154,   156,   157,
     158,    35,    28,    29,    30,     0,     0,   205,     0,     0,
       0,     0,   196,   197,     0,     0,   195,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   223,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   248,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   266,
       0,   265,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   230,     0,   274,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   255,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   289,   290,   287,   280,     0,     0,   312,     0,
     297,     0,   299,     0,     0,     0,   159,   160,   161,     0,
       0,     0,     0,     0,    23,   207,    47,   217,   218,   199,
     201,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,   191,   192,    56,     0,    58,    59,     0,    61,     0,
     225,     0,     0,    65,     0,    67,     0,     0,   242,   243,
      70,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,     0,    88,     0,
       0,     0,   250,     0,     0,     0,     0,     0,     0,     0,
       0,    98,     0,     0,     0,   102,     0,     0,     0,   106,
       0,   108,     0,   110,     0,     0,     0,     0,     0,     0,
       0,   118,     0,     0,     0,     0,   123,     0,     0,     0,
     127,   267,   268,   271,   130,     0,   132,     0,   134,     0,
       0,   137,   138,   139,     0,   141,     0,     0,     0,   232,
     277,   353,   355,   356,     0,   360,   361,   362,   363,   364,
     365,   366,   367,     0,   257,     0,     0,     0,   212,   213,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   386,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   415,   416,   417,   418,   419,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   296,   292,
     293,   263,   264,     0,     0,   311,   308,     0,     0,     0,
       0,     0,   166,     0,   162,    34,     0,     0,     0,     0,
       0,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   237,   238,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   304,     0,   186,   187,   163,     0,     0,     0,
     167,   168,   169,     0,     0,     0,     0,     0,     0,     0,
       0,   200,    50,    51,    52,   128,    53,    54,    55,   129,
      57,    60,    62,    63,    64,    66,    68,    69,    71,    87,
      89,    90,     0,    92,     0,    94,     0,    96,     0,    99,
     100,   101,   103,   104,   105,   107,   109,   111,   112,     0,
     114,     0,   116,     0,   119,   120,   121,   122,   124,   125,
     126,   131,   133,   135,   136,   140,   142,   143,   144,   359,
       0,     0,     0,     0,   372,   373,   374,   375,   376,   377,
       0,     0,   381,     0,     0,     0,     0,   387,   388,   389,
     390,   391,   392,     0,     0,     0,     0,   405,     0,   407,
     408,     0,     0,     0,     0,     0,     0,     0,   421,   422,
       0,     0,     0,   426,   427,   428,   313,   306,   310,     0,
       0,   300,     0,   170,   171,   172,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,   164,     0,    39,    40,    41,     0,     0,
       0,     0,    91,    93,    95,    97,   113,   115,   117,   368,
     369,   370,   371,     0,     0,     0,     0,     0,     0,   401,
     402,   403,   404,   406,   409,   410,     0,     0,     0,   414,
       0,   423,     0,     0,   303,   298,     0,   174,     0,     0,
       0,     0,     0,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
      36,    37,    38,     0,   379,   380,   382,   383,   384,   385,
       0,     0,     0,   420,   424,     0,   302,     0,    27,     0,
       0,     0,     0,    42,   411,   412,   413,     0,     0,     0,
       0,   425
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1087, -1087,   -47,    -3, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087,  -336, -1087, -1087,    23, -1087, -1087,   199,  -341, -1087,
   -1087, -1087,     2,    -2,   217,     4, -1086,  -121,  -811,  -727,
   -1087, -1087,  -356, -1087, -1087,  -146,   -63,  -214,  -371, -1087,
   -1087,  -306, -1087, -1087,  -756,  1069,  -459,  -377, -1087, -1087,
    -461, -1087, -1087,  1068,   692, -1087,  -438, -1087,  -778, -1087,
    1060, -1087,  1321, -1087,  -516, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,   553,    23,   293,    24,   538,   539,   540,   559,   560,
    1075,  1629,    25,    26,   335,    27,  1065,   594,   595,  1095,
    1096,  1311,   574,   575,   839,   733,   579,   580,   605,   606,
     864,   701,   702,   960,   897,   616,   617,   640,   641,   899,
     727,   728,   984,   806,   683,   942,   707,   964,   800,   801,
     814,  1750,   331,  1494,  1495,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   108
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     111,   581,   582,   607,   110,  1066,   112,   564,  1310,   554,
     555,   337,   597,   730,   566,   567,   568,  1073,   708,     5,
    1052,  1054,   113,   713,   642,   643,   644,   645,   646,   647,
     648,     3,     4,     5,   114,   109,   756,   338,   339,  1190,
     760,  1191,   334,   740,   556,     3,     4,     5,   557,   558,
     332,   663,   664,   665,   666,   667,   668,   333,   778,     8,
       9,   758,  1068,   731,   732,   762,   578,     1,     2,     3,
       4,     5,     6,     7,   862,   805,   805,   336,   775,  1087,
    1088,   679,   680,   780,   681,     1,     2,     3,     4,     5,
       6,     7,   551,   552,   682,     8,     9,   894,   895,   576,
     577,   615,   578,     9,  1506,     3,     4,     5,   896,  1507,
     958,   741,   354,   571,   572,  1627,     3,     4,     5,   340,
    1628,   590,   591,   573,   602,   603,  1047,     3,     4,     5,
    1048,   819,   613,   614,   604,   341,   615,   344,   590,   591,
     755,   637,   638,   982,   759,   698,   699,   342,   703,   704,
     705,   639,   710,   711,   712,   700,   724,   725,   345,   706,
    1092,  1093,   777,   534,   535,   723,   726,   729,   783,   343,
    1094,   534,   535,   536,   346,   537,   347,   742,   802,   803,
     898,   578,   615,   748,   749,   750,   751,   752,   753,   754,
     613,   614,   757,   348,   615,   349,   761,   350,   763,   764,
     765,   766,   767,   768,   769,   770,   771,   772,   773,   774,
    1114,  1115,   353,  1074,   779,    10,   351,   782,   541,   590,
     591,   786,   352,   788,   355,    12,   356,   590,   591,    10,
      11,   894,   895,   357,   836,   615,   544,   576,   577,    12,
     578,  1147,  1148,    10,    11,   543,   596,   358,   598,   599,
     600,   601,   546,    12,   608,   609,   610,   611,   612,  1207,
    1208,   734,   734,   734,   734,   734,   734,    10,    11,  1279,
     734,   359,     3,     4,     5,   360,  1633,    12,  1285,   808,
     809,   810,  1289,  1066,  1272,    10,    11,   542,     3,     4,
       5,   361,  1752,   548,   549,    12,   583,   584,   585,   586,
     587,   588,   589,    10,    11,   731,   732,   362,   578,   363,
     592,   593,   364,    12,    10,    11,   734,   734,  1209,  1210,
     804,   804,   365,   366,    12,    10,    11,  1063,  1064,   367,
     735,   736,   737,   738,   739,    12,   791,   792,   743,   550,
    1290,  1291,  1292,  1224,  1225,   562,   562,   565,   547,   561,
     561,   563,   563,   657,   658,   659,   660,   661,   662,   898,
     545,  1511,  1512,  1620,  1621,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,  1799,  1800,   791,   792,   687,
     688,   368,   369,   370,   789,   790,   371,   372,   373,  1102,
     734,     8,  1362,   791,   792,   374,   375,   376,   377,   714,
     378,   716,   379,   718,   380,   720,   381,   722,   592,   593,
    1100,   382,   383,   384,  1104,   385,  1063,  1064,   386,   837,
     387,   388,   744,   745,   746,   747,  1641,  1309,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,  1149,
    1150,  1151,  1152,  1153,  1154,  1155,  1156,   400,   401,   402,
     403,   404,   838,   405,   406,   407,   408,   409,   863,   781,
     410,   411,   412,   413,   414,   787,   415,   416,   417,  1098,
      10,    11,   418,   570,   419,   420,  1099,   421,   422,   423,
      12,   424,   425,   426,   427,  1077,    10,    11,   428,   569,
     429,   430,   431,  1101,   432,  1081,    12,   433,   434,   435,
     436,  1109,   437,   438,   439,   440,   441,   442,   443,  1116,
    1117,   444,  1215,  1216,  1217,   445,  1219,   446,  1221,   447,
     448,   449,   450,   451,   452,   793,   794,   795,   796,   797,
     453,   537,   454,   455,   456,   798,   457,   458,   799,  1053,
    1241,   459,   460,   461,   462,  1103,   463,   464,   465,   466,
     467,   468,   469,  1232,   821,  1234,   470,  1236,   820,   471,
     822,   472,   473,   474,   475,  1243,   793,   794,   795,   796,
     797,   476,   811,   477,   478,   479,   798,  1051,   480,   799,
     481,   898,   793,   794,   795,   796,   797,   482,   816,   483,
     484,  1261,   798,  1263,   485,   799,   486,   487,   488,   489,
     490,   491,   492,   734,   493,  1275,   494,  1534,  1535,  1536,
    1537,  1538,  1539,  1540,  1541,   495,  1171,  1172,  1173,  1174,
    1175,  1176,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   959,   511,   512,
     513,   514,   515,   516,  1240,   517,   518,   519,   520,   521,
     522,   523,   524,  1256,  1257,  1258,  1259,  1260,   525,   526,
     527,   528,  1212,  1213,  1273,   529,  1214,   530,   531,   532,
    1218,  1067,  1220,   813,  1222,   817,  1264,   823,   818,   824,
     825,   830,   826,  1271,  1231,   827,  1233,   828,  1235,   898,
     829,  1237,  1238,  1239,   831,   835,  1242,   832,   833,   834,
     845,  1066,   940,   840,   841,   842,   941,  1059,   843,   844,
     846,  1082,   847,  1251,  1252,  1253,  1254,  1255,   848,  1089,
    1623,   849,   850,  1097,  1262,  1612,  1613,   851,   852,   853,
     854,  1269,   961,   855,   856,  1108,   857,  1110,  1111,  1112,
    1113,   858,   859,   860,   861,   865,  1118,  1119,  1120,  1121,
    1122,   866,   867,   868,   869,   870,   871,   872,   873,  1284,
     812,   874,   875,   876,   877,   878,   879,   880,   881,   882,
    1083,   883,   884,   885,   886,   887,   888,   889,   890,   891,
     892,   893,   900,   901,   902,   903,   904,   905,   906,   907,
     908,   909,  1107,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   929,   930,   931,   932,   933,   934,   935,   936,
     937,   938,  1076,   939,   562,   962,   943,   944,   561,   945,
     563,   734,   734,   946,   947,   948,   949,   950,   951,   952,
     953,   954,   955,   956,   957,   965,   966,   967,   968,   969,
     970,   971,   972,  1165,  1166,  1167,  1168,  1169,  1170,   973,
     974,   975,   976,   977,   978,  1177,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,  1185,   979,   980,   981,   985,   986,   987,
    1192,   988,   989,  1050,  1069,   990,   991,   992,   993,   994,
     995,   997,   996,   998,   999,  1000,  1011,  1049,  1001,  1277,
    1278,   734,  1002,  1003,   898,   898,   898,   898,   898,   898,
     898,   898,  1265,  1004,  1005,  1006,  1007,  1008,  1223,  1009,
    1010,  1012,  1226,  1227,  1228,  1013,  1014,  1015,  1016,  1017,
    1018,  1062,  1078,  1079,  1080,  1060,  1019,  1020,  1021,  1022,
    1023,  1244,  1245,  1246,  1247,  1248,  1249,  1250,  1024,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,
    1036,  1037,  1038,  1039,  1040,  1041,  1042,  1305,  1043,  1330,
    1044,  1045,  1267,  1046,  1055,  1056,  1057,  1070,  1058,  1071,
    1072,  1085,  1086,  1090,  1795,  1091,  1105,  1106,  1123,  1124,
    1283,  1145,  1187,  1188,  1189,  1229,  1230,  1146,  1276,  1280,
    1281,  1282,  1286,  1287,  1288,  1296,  1297,  1298,  1299,  1303,
    1061,  1293,  1294,  1302,  1300,  1485,  1301,  1306,  1313,  1323,
    1307,  1619,   898,   898,  1308,  1360,  1312,  1314,  1315,  1316,
    1317,  1318,  1319,  1320,  1321,  1322,  1325,  1324,  1326,  1327,
    1328,  1503,  1329,  1333,  1331,  1335,  1332,  1334,  1338,  1618,
    1340,  1336,  1337,  1339,  1342,  1343,  1341,  1344,  1345,  1346,
    1347,  1348,  1349,  1350,  1351,  1352,  1353,  1295,  1354,  1355,
    1356,  1358,  1357,  1361,  1637,  1583,  1584,  1585,  1359,  1363,
    1364,  1365,  1853,  1366,  1367,  1368,  1371,  1369,  1370,  1372,
    1373,  1375,  1374,  1376,  1377,  1378,  1379,  1604,  1605,  1380,
    1381,  1383,  1382,  1384,  1385,  1748,  1497,  1386,  1387,  1388,
    1389,  1390,  1391,  1615,  1392,  1393,  1394,  1396,   734,  1395,
    1397,  1398,  1400,  1399,  1401,  1402,  1403,  1404,  1405,  1406,
    1407,   684,   685,   686,  1408,  1411,   689,   690,   691,   692,
     693,   694,   695,   696,   697,  1419,  1409,  1410,  1412,   709,
    1413,  1414,  1415,  1421,  1596,  1597,  1598,  1599,  1600,  1601,
    1602,  1603,  1416,  1417,  1418,  1422,  1423,  1424,  1425,  1426,
    1427,   734,   734,   734,   734,   734,   734,  1428,  1429,  1430,
    1617,  1431,  1432,     0,  1504,  1433,  1525,  1453,  1435,  1436,
    1437,  1513,  1438,  1439,  1626,  1440,  1517,  1441,  1442,  1443,
    1444,  1445,  1489,  1521,  1446,  1447,  1522,  1448,  1523,   776,
    1449,  1474,  1450,  1526,  1451,  1527,  1528,  1452,  1454,  1455,
    1456,  1457,  1458,  1459,  1460,  1461,   734,  1462,   734,  1463,
     734,  1464,  1465,  1466,  1467,  1468,  1530,  1469,  1531,  1551,
    1552,  1553,  1554,  1555,  1556,  1470,  1471,  1472,  1473,  1475,
    1476,  1542,  1515,  1477,  1478,  1545,  1519,  1479,  1488,  1493,
    1480,  1549,  1481,  1550,  1482,  1483,  1484,  1486,  1524,  1487,
    1490,  1557,  1491,  1492,  1496,  1499,  1561,  1498,  1500,  1502,
    1573,   898,  1501,  1574,  1532,  1575,  1565,  1576,  1566,  1533,
    1606,  1607,  1608,  1568,  1577,  1569,  1579,  1609,  1581,  1616,
    1622,  1509,  1763,  1764,  1765,  1508,  1624,  1510,  1625,  1638,
    1639,  1640,  1642,  1643,  1644,  1645,  1646,  1548,  1647,  1648,
    1649,  1650,  1651,  1652,  1653,  1654,  1655,  1656,  1586,  1657,
    1558,  1559,  1560,  1658,  1659,  1562,  1563,  1660,  1661,  1663,
    1662,  1664,  1665,  1667,  1669,  1666,  1668,  1670,  1671,  1672,
    1673,  1674,  1675,  1676,  1677,  1678,  1680,  1787,  1700,  1611,
    1788,  1789,  1679,  1681,  1682,  1683,  1684,  1685,  1686,  1687,
    1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,
    1698,  1699,  1701,  1702,  1703,  1704,  1705,  1706,  1588,  1707,
    1872,  1590,  1591,  1592,  1593,  1594,  1595,  1708,   963,  1709,
    1710,  1711,  1712,  1713,  1717,  1714,  1715,  1718,  1716,  1719,
    1720,  1721,  1722,  1723,  1727,  1729,  1733,  1783,  1784,  1785,
    1786,  1724,  1725,  1805,  1806,  1807,  1726,  1728,  1730,  1731,
    1732,  1734,  1735,  1736,  1855,  1888,  1737,  1738,  1739,  1854,
    1740,  1741,  1743,  1744,  1742,  1745,  1746,  1747,  1749,  1893,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   633,   634,   635,   636,  1751,
    1756,  1757,  1852,  1758,  1759,  1760,  1761,   649,   650,   651,
     652,   653,   654,   655,   656,  1773,  1774,  1775,  1776,  1777,
    1778,  1779,  1780,  1870,  1781,  1782,  1790,  1791,  1792,  1793,
    1794,  1631,  1796,  1798,  1635,  1630,  1801,  1632,  1634,  1803,
    1636,  1808,  1869,  1809,  1810,  1811,  1823,  1812,  1813,  1814,
    1815,  1816,  1817,  1818,  1819,  1820,  1821,  1822,  1824,  1825,
    1826,  1827,   715,  1828,   717,  1829,   719,  1830,   721,  1831,
    1832,  1766,  1833,  1767,  1871,  1768,  1834,  1769,  1835,  1836,
    1837,  1839,  1840,  1841,  1838,  1842,  1844,  1843,  1770,  1845,
    1771,  1846,  1772,  1848,  1856,  1849,  1850,  1868,  1851,  1873,
    1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,  1865,  1866,
    1867,  1880,  1881,  1882,  1885,  1874,  1875,  1876,  1877,  1878,
    1879,  1883,  1884,  1886,   784,   785,  1887,  1889,  1890,  1891,
    1892,  1897,  1899,   807,     0,  1898,  1894,  1895,  1896,  1900,
    1901,     0,   815,     0,   533,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1754,     0,     0,     0,  1753,
       0,  1755,     0,     0,     0,  1762,  1193,  1194,  1195,  1196,
    1197,  1198,  1199,  1200,  1201,  1202,  1203,  1204,  1205,  1206,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1211,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1797,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1268,     0,
    1270,     0,     0,     0,  1274,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1802,     0,  1804,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1304,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   983,     0,     0,     0,  1847,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,     0,
       0,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1420,  1084,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1125,  1126,  1127,  1128,  1129,  1130,  1131,
    1132,  1133,  1134,  1135,  1136,  1137,  1138,  1139,  1140,  1141,
    1142,  1143,  1144,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1157,  1158,  1159,
    1160,  1161,  1162,  1163,  1164,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1505,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1186,     0,  1516,     0,
       0,     0,  1520,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1564,     0,     0,
       0,     0,  1567,  1266,     0,     0,     0,     0,     0,  1570,
    1571,     0,     0,     0,     0,     0,  1572,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1578,     0,  1580,     0,  1582,     0,     0,
       0,     0,     0,     0,  1589,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1610,     0,     0,     0,  1614,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1434,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1514,     0,     0,     0,  1518,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1529,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1543,  1544,     0,     0,  1546,  1547,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1587,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,     0,     0,   292
};

static const yytype_int16 yycheck[] =
{
       2,   357,   358,   374,     2,   816,     2,   348,  1094,   345,
     346,    14,   368,   474,   350,   351,   352,     7,   456,     7,
     798,   799,   210,   461,   401,   402,   403,   404,   405,   406,
     407,     5,     6,     7,    10,     9,   497,    14,    15,   212,
     501,   214,   203,   481,     4,     5,     6,     7,     8,     9,
      18,   422,   423,   424,   425,   426,   427,    18,   519,    13,
      14,   499,   818,   200,   201,   503,   203,     3,     4,     5,
       6,     7,     8,     9,   211,   534,   535,     0,   516,   211,
     212,   200,   201,   521,   203,     3,     4,     5,     6,     7,
       8,     9,   200,   201,   213,    13,    14,   200,   201,   200,
     201,   204,   203,    14,     4,     5,     6,     7,   211,     9,
     211,   482,   114,   200,   201,     4,     5,     6,     7,   205,
       9,    11,    12,   210,   200,   201,   206,     5,     6,     7,
     210,     9,   200,   201,   210,   205,   204,   208,    11,    12,
     496,   200,   201,   211,   500,   200,   201,   205,   454,   200,
     201,   210,   458,   459,   460,   210,   200,   201,   208,   210,
     200,   201,   518,    15,    16,   471,   210,   473,   524,   205,
     210,    15,    16,    17,   208,    19,   206,   483,   200,   201,
     639,   203,   204,   489,   490,   491,   492,   493,   494,   495,
     200,   201,   498,   206,   204,    10,   502,   208,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     211,   212,   203,   203,   520,   203,   208,   523,   203,    11,
      12,   527,   208,   529,   206,   213,   206,    11,    12,   203,
     204,   200,   201,   206,   570,   204,   214,   200,   201,   213,
     203,   211,   212,   203,   204,   212,   367,   206,   369,   370,
     371,   372,   205,   213,   375,   376,   377,   378,   379,   211,
     212,   475,   476,   477,   478,   479,   480,   203,   204,  1047,
     484,   206,     5,     6,     7,   206,     9,   213,  1056,   198,
     199,   200,  1060,  1094,  1040,   203,   204,   204,     5,     6,
       7,   206,     9,   340,   341,   213,   359,   360,   361,   362,
     363,   364,   365,   203,   204,   200,   201,   206,   203,   206,
     200,   201,   206,   213,   203,   204,   530,   531,   211,   212,
     534,   535,   206,   206,   213,   203,   204,   200,   201,   206,
     476,   477,   478,   479,   480,   213,    11,    12,   484,   342,
     198,   199,   200,   211,   212,   347,   348,   349,   205,   347,
     348,   347,   348,   416,   417,   418,   419,   420,   421,   818,
     337,   211,   212,   211,   212,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   211,   212,    11,    12,   442,
     443,   206,   206,   206,   530,   531,   206,   206,   206,   850,
     604,    13,  1148,    11,    12,   206,   206,   206,   206,   462,
     206,   464,   206,   466,   206,   468,   206,   470,   200,   201,
     848,   206,   206,   206,   852,   206,   200,   201,   206,   211,
     206,   206,   485,   486,   487,   488,  1512,   211,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   900,
     901,   902,   903,   904,   905,   906,   907,   206,   206,   206,
     206,   206,   573,   206,   206,   206,   206,   206,   604,   522,
     206,   206,   206,   206,   206,   528,   206,   206,   206,   846,
     203,   204,   206,   208,   206,   206,   847,   206,   206,   206,
     213,   206,   206,   206,   206,   826,   203,   204,   206,    18,
     206,   206,   206,   849,   206,   831,   213,   206,   206,   206,
     206,   857,   206,   206,   206,   206,   206,   206,   206,   865,
     866,   206,   973,   974,   975,   206,   977,   206,   979,   206,
     206,   206,   206,   206,   206,   200,   201,   202,   203,   204,
     206,    19,   206,   206,   206,   210,   206,   206,   213,   214,
    1001,   206,   206,   206,   206,   851,   206,   206,   206,   206,
     206,   206,   206,   991,   556,   993,   206,   995,   556,   206,
     556,   206,   206,   206,   206,  1003,   200,   201,   202,   203,
     204,   206,   212,   206,   206,   206,   210,   211,   206,   213,
     206,  1040,   200,   201,   202,   203,   204,   206,   209,   206,
     206,  1029,   210,  1031,   206,   213,   206,   206,   206,   206,
     206,   206,   206,   817,   206,  1043,   206,  1363,  1364,  1365,
    1366,  1367,  1368,  1369,  1370,   206,   922,   923,   924,   925,
     926,   927,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   700,   206,   206,
     206,   206,   206,   206,  1000,   206,   206,   206,   206,   206,
     206,   206,   206,  1024,  1025,  1026,  1027,  1028,   206,   206,
     206,   206,   968,   969,  1041,   206,   972,   206,   206,   206,
     976,   817,   978,   205,   980,   209,  1032,   210,   209,    10,
     207,   207,   212,  1039,   990,   208,   992,   208,   994,  1148,
     208,   997,   998,   999,   208,   203,  1002,   209,   209,   209,
     207,  1512,    18,   212,   210,   210,   203,   206,   212,   212,
     212,   832,   212,  1019,  1020,  1021,  1022,  1023,   212,   840,
    1498,   212,   212,   844,  1030,  1481,  1482,   212,   212,   210,
     210,  1037,   207,   212,   212,   856,   212,   858,   859,   860,
     861,   212,   212,   212,   212,   212,   867,   868,   869,   870,
     871,   212,   212,   212,   212,   212,   212,   210,   210,   214,
     543,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     833,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   855,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   210,   824,   210,   826,   207,   212,   212,   826,   212,
     826,  1045,  1046,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   207,   207,   212,   212,   212,
     207,   207,   212,   916,   917,   918,   919,   920,   921,   212,
     212,   212,   212,   212,   212,   928,   929,   930,   931,   932,
     933,   934,   935,   936,   212,   212,   212,   212,   212,   212,
     943,   210,   210,    18,    10,   212,   212,   212,   212,   212,
     212,   212,   207,   212,   212,   212,   207,   210,   212,  1045,
    1046,  1115,   212,   212,  1363,  1364,  1365,  1366,  1367,  1368,
    1369,  1370,  1033,   212,   212,   212,   212,   212,   981,   212,
     212,   207,   985,   986,   987,   207,   207,   207,   207,   207,
     207,    19,   200,   200,   200,   206,   212,   212,   212,   212,
     212,  1004,  1005,  1006,  1007,  1008,  1009,  1010,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,  1088,   212,  1115,
     212,   212,  1035,   212,   207,   212,   210,   208,   210,   208,
     208,   211,   209,   203,  1740,   203,   203,   203,   203,   203,
     211,   210,   203,   203,   203,   203,   203,   210,   203,   203,
     203,   203,   203,   203,   210,   200,   200,   200,    18,    10,
     811,   210,   210,   209,   211,    18,   208,   207,   207,   207,
     211,    18,  1481,  1482,   211,   203,   212,   212,   212,   212,
     212,   212,   212,   212,   211,   211,   207,   212,   207,   212,
     207,    10,   212,   207,   212,   207,   212,   212,   211,  1487,
     207,   212,   212,   211,   207,   207,   212,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,  1069,   207,   207,
     207,   207,   212,   203,    10,  1446,  1447,  1448,   212,   212,
     212,   212,  1809,   212,   212,   212,   207,   212,   212,   212,
     212,   207,   212,   212,   212,   212,   207,  1468,  1469,   212,
     207,   207,   212,   212,   212,  1621,   206,   212,   212,   212,
     212,   212,   207,  1484,   212,   212,   212,   207,  1332,   212,
     212,   212,   207,   212,   211,   211,   203,   207,   212,   207,
     212,   439,   440,   441,   207,   207,   444,   445,   446,   447,
     448,   449,   450,   451,   452,  1208,   212,   212,   207,   457,
     207,   212,   207,   207,  1460,  1461,  1462,  1463,  1464,  1465,
    1466,  1467,   212,   212,   212,   207,   207,   212,   207,   207,
     207,  1385,  1386,  1387,  1388,  1389,  1390,   207,   207,   207,
    1486,   207,   207,    -1,   200,   212,  1332,   207,   212,   212,
     212,  1312,   211,   211,   200,   212,  1317,   212,   212,   212,
     212,   212,   211,  1324,   212,   212,  1327,   212,  1329,   517,
     212,   207,   212,  1334,   212,  1336,  1337,   212,   212,   212,
     212,   212,   212,   212,   212,   212,  1440,   212,  1442,   212,
    1444,   212,   212,   212,   212,   212,  1357,   212,  1359,  1385,
    1386,  1387,  1388,  1389,  1390,   212,   212,   212,   212,   207,
     207,  1372,  1315,   207,   207,  1376,  1319,   212,   207,   203,
     212,  1382,   212,  1384,   212,   212,   212,   212,  1331,   212,
     211,  1392,   211,   211,   207,   203,  1397,   206,   203,   203,
     203,  1740,   208,   203,   211,   203,  1407,   203,  1409,   211,
     203,   203,   203,  1414,  1440,  1416,  1442,   203,  1444,   203,
     210,  1303,  1638,  1639,  1640,  1303,   211,  1303,   211,   208,
     208,   208,   207,   207,   207,   207,   207,  1380,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,  1449,   207,
    1393,  1394,  1395,   207,   207,  1398,  1399,   207,   207,   207,
     212,   212,   207,   207,   207,   212,   212,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,  1728,    18,  1480,
    1731,  1732,   212,   212,   207,   212,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,    18,    18,    18,   207,   207,   207,  1451,   207,
    1851,  1454,  1455,  1456,  1457,  1458,  1459,   207,   706,   207,
     212,   212,   207,   212,   207,   212,   212,   207,   212,   207,
     207,   207,   207,   212,   207,   207,    18,  1723,  1724,  1725,
    1726,   212,   212,  1759,  1760,  1761,   212,   212,   207,   212,
     212,    18,    18,    18,  1811,  1873,   212,   207,   207,  1810,
     212,   212,   207,   207,   212,   207,   203,   207,   203,  1887,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   207,
      10,   208,  1808,    10,   208,   208,   208,   408,   409,   410,
     411,   412,   413,   414,   415,   203,   203,   203,   203,   203,
     203,   203,   203,  1849,   203,   203,   203,   203,   203,   203,
     203,  1503,   203,    18,  1506,  1503,    10,  1503,  1506,   200,
    1506,   208,  1848,   209,   209,   209,    18,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,    18,    18,
      18,    18,   463,    18,   465,   207,   467,   207,   469,   207,
     207,  1662,   207,  1664,  1850,  1666,   207,  1668,   207,   212,
     212,   207,    18,   207,   212,    18,   203,   212,  1679,   207,
    1681,   203,  1683,   208,   203,   209,   209,    18,   209,   209,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,    18,    18,    18,    18,   207,   207,   207,   207,   207,
     207,   207,   207,   203,   525,   526,   209,   203,   203,   203,
     203,   212,    18,   535,    -1,   203,   207,   207,   207,   203,
     207,    -1,   552,    -1,   293,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1627,    -1,    -1,    -1,  1627,
      -1,  1627,    -1,    -1,    -1,  1637,   944,   945,   946,   947,
     948,   949,   950,   951,   952,   953,   954,   955,   956,   957,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   967,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1742,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1036,    -1,
    1038,    -1,    -1,    -1,  1042,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1756,    -1,  1758,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1086,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   726,    -1,    -1,    -1,  1801,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,    -1,
      -1,   200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1210,   834,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   874,   875,   876,   877,   878,   879,   880,
     881,   882,   883,   884,   885,   886,   887,   888,   889,   890,
     891,   892,   893,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   908,   909,   910,
     911,   912,   913,   914,   915,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1302,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   937,    -1,  1316,    -1,
      -1,    -1,  1320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1405,    -1,    -1,
      -1,    -1,  1410,  1034,    -1,    -1,    -1,    -1,    -1,  1417,
    1418,    -1,    -1,    -1,    -1,    -1,  1424,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1441,    -1,  1443,    -1,  1445,    -1,    -1,
      -1,    -1,    -1,    -1,  1452,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1479,    -1,    -1,    -1,  1483,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1225,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1314,    -1,    -1,    -1,  1318,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1341,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1373,  1374,    -1,    -1,  1377,  1378,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1450,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,    -1,    -1,   200
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    13,    14,
     203,   204,   213,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   227,   229,   237,   238,   240,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   200,   317,     9,
     237,   238,   240,   210,    10,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   200,   228,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   277,    18,    18,   203,   239,     0,   218,   229,   229,
     205,   205,   205,   205,   208,   208,   208,   206,   206,    10,
     208,   208,   208,   203,   238,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   277,    15,    16,    17,    19,   230,   231,
     232,   203,   204,   212,   214,   229,   205,   205,   217,   217,
     218,   200,   201,   226,   226,   226,     4,     8,     9,   233,
     234,   237,   238,   240,   233,   238,   226,   226,   226,    18,
     208,   200,   201,   210,   247,   248,   200,   201,   203,   251,
     252,   247,   247,   251,   251,   251,   251,   251,   251,   251,
      11,    12,   200,   201,   242,   243,   242,   247,   242,   242,
     242,   242,   200,   201,   210,   253,   254,   253,   242,   242,
     242,   242,   242,   200,   201,   204,   260,   261,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   200,   201,   210,
     262,   263,   262,   262,   262,   262,   262,   262,   262,   260,
     260,   260,   260,   260,   260,   260,   260,   251,   251,   251,
     251,   251,   251,   253,   253,   253,   253,   253,   253,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   200,
     201,   203,   213,   269,   269,   269,   269,   251,   251,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   200,   201,
     210,   256,   257,   256,   200,   201,   210,   271,   271,   269,
     256,   256,   256,   271,   251,   260,   251,   260,   251,   260,
     251,   260,   251,   256,   200,   201,   210,   265,   266,   256,
     265,   200,   201,   250,   252,   250,   250,   250,   250,   250,
     271,   253,   256,   250,   251,   251,   251,   251,   256,   256,
     256,   256,   256,   256,   256,   247,   265,   256,   271,   247,
     265,   256,   271,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   271,   269,   247,   265,   256,
     271,   251,   256,   247,   260,   260,   256,   251,   256,   250,
     250,    11,    12,   200,   201,   202,   203,   204,   210,   213,
     273,   274,   200,   201,   252,   261,   268,   268,   198,   199,
     200,   212,   239,   205,   275,   275,   209,   209,   209,     9,
     237,   238,   240,   210,    10,   207,   212,   208,   208,   208,
     207,   208,   209,   209,   209,   203,   226,   211,   242,   249,
     212,   210,   210,   212,   212,   207,   212,   212,   212,   212,
     212,   212,   212,   210,   210,   212,   212,   212,   212,   212,
     212,   212,   211,   250,   255,   212,   212,   212,   212,   212,
     212,   212,   210,   210,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   200,   201,   211,   259,   261,   264,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   210,   210,
      18,   203,   270,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   211,   251,
     258,   207,   207,   269,   272,   207,   207,   212,   212,   212,
     207,   207,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   211,   260,   267,   212,   212,   212,   210,   210,
     212,   212,   212,   212,   212,   212,   207,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   207,   207,   207,   207,   207,   207,   207,   207,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   206,   210,   210,
      18,   211,   273,   214,   273,   207,   212,   210,   210,   206,
     206,   232,    19,   200,   201,   241,   243,   250,   259,    10,
     208,   208,   208,     7,   203,   235,   238,   233,   200,   200,
     200,   226,   242,   251,   260,   211,   209,   211,   212,   242,
     203,   203,   200,   201,   210,   244,   245,   242,   262,   253,
     271,   247,   265,   256,   271,   203,   203,   251,   242,   247,
     242,   242,   242,   242,   211,   212,   247,   247,   242,   242,
     242,   242,   242,   203,   203,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   210,   210,   211,   212,   265,
     265,   265,   265,   265,   265,   265,   265,   260,   260,   260,
     260,   260,   260,   260,   260,   251,   251,   251,   251,   251,
     251,   256,   256,   256,   256,   256,   256,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   260,   203,   203,   203,
     212,   214,   251,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   211,   212,   211,
     212,   269,   256,   256,   256,   265,   265,   265,   256,   265,
     256,   265,   256,   251,   211,   212,   251,   251,   251,   203,
     203,   256,   271,   256,   271,   256,   271,   256,   256,   256,
     247,   265,   256,   271,   251,   251,   251,   251,   251,   251,
     251,   256,   256,   256,   256,   256,   253,   253,   253,   253,
     253,   271,   256,   271,   247,   242,   260,   251,   269,   256,
     269,   247,   259,   262,   269,   271,   203,   250,   250,   273,
     203,   203,   203,   211,   214,   273,   203,   203,   210,   273,
     198,   199,   200,   210,   210,   238,   200,   200,   200,    18,
     211,   208,   209,    10,   269,   242,   207,   211,   211,   211,
     241,   246,   212,   207,   212,   212,   212,   212,   212,   212,
     212,   211,   211,   207,   212,   207,   207,   212,   207,   212,
     250,   212,   212,   207,   212,   207,   212,   212,   211,   211,
     207,   212,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   212,   207,   212,
     203,   203,   259,   212,   212,   212,   212,   212,   212,   212,
     212,   207,   212,   212,   212,   207,   212,   212,   212,   207,
     212,   207,   212,   207,   212,   212,   212,   212,   212,   212,
     212,   207,   212,   212,   212,   212,   207,   212,   212,   212,
     207,   211,   211,   203,   207,   212,   207,   212,   207,   212,
     212,   207,   207,   207,   212,   207,   212,   212,   212,   251,
     269,   207,   207,   207,   212,   207,   207,   207,   207,   207,
     207,   207,   207,   212,   260,   212,   212,   212,   211,   211,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   207,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   207,   207,   207,   207,   207,   212,
     212,   212,   212,   212,   212,    18,   212,   212,   207,   211,
     211,   211,   211,   203,   278,   279,   207,   206,   206,   203,
     203,   208,   203,    10,   200,   269,     4,     9,   237,   238,
     240,   211,   212,   242,   260,   251,   269,   242,   260,   251,
     269,   242,   242,   242,   251,   250,   242,   242,   242,   260,
     242,   242,   211,   211,   259,   259,   259,   259,   259,   259,
     259,   259,   242,   260,   260,   242,   260,   260,   251,   242,
     242,   250,   250,   250,   250,   250,   250,   242,   251,   251,
     251,   242,   251,   251,   269,   242,   242,   269,   242,   242,
     269,   269,   269,   203,   203,   203,   203,   250,   269,   250,
     269,   250,   269,   253,   253,   253,   242,   260,   251,   269,
     251,   251,   251,   251,   251,   251,   256,   256,   256,   256,
     256,   256,   256,   256,   253,   253,   203,   203,   203,   203,
     269,   242,   259,   259,   269,   253,   203,   256,   271,    18,
     211,   212,   210,   273,   211,   211,   200,     4,     9,   236,
     237,   238,   240,     9,   237,   238,   240,    10,   208,   208,
     208,   241,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   212,   207,   212,   207,   212,   207,   212,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   212,
     207,   212,   207,   212,   207,   207,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   207,
      18,    18,    18,    18,   207,   207,   207,   207,   207,   207,
     212,   212,   207,   212,   212,   212,   212,   207,   207,   207,
     207,   207,   207,   212,   212,   212,   212,   207,   212,   207,
     207,   212,   212,    18,    18,    18,    18,   212,   207,   207,
     212,   212,   212,   207,   207,   207,   203,   207,   279,   203,
     276,   207,     9,   237,   238,   240,    10,   208,    10,   208,
     208,   208,   238,   226,   226,   226,   242,   242,   242,   242,
     242,   242,   242,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   256,   256,   256,   256,   253,   253,   253,
     203,   203,   203,   203,   203,   259,   203,   251,    18,   211,
     212,    10,   238,   200,   238,   226,   226,   226,   208,   209,
     209,   209,   207,   207,   207,   207,   207,   207,   207,   207,
     207,   207,   207,    18,    18,    18,    18,    18,    18,   207,
     207,   207,   207,   207,   207,   207,   212,   212,   212,   207,
      18,   207,    18,   212,   203,   207,   203,   238,   208,   209,
     209,   209,   226,   244,   253,   262,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,    18,   226,
     247,   256,   265,   209,   207,   207,   207,   207,   207,   207,
      18,    18,    18,   207,   207,    18,   203,   209,   271,   203,
     203,   203,   203,   271,   207,   207,   207,   212,   203,    18,
     203,   207
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   215,   216,   216,   216,   216,   216,   217,   217,   217,
     217,   218,   218,   219,   220,   220,   221,   221,   221,   221,
     222,   222,   222,   222,   223,   223,   223,   223,   224,   224,
     224,   224,   224,   224,   224,   224,   225,   225,   225,   225,
     225,   225,   225,   225,   226,   226,   227,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   229,   230,   230,
     231,   231,   232,   232,   233,   233,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   235,   235,   236,   236,   236,
     236,   236,   236,   236,   236,   237,   238,   238,   238,   239,
     239,   240,   240,   241,   241,   241,   241,   241,   242,   242,
     242,   242,   242,   243,   243,   244,   244,   244,   245,   245,
     246,   246,   247,   247,   247,   248,   248,   249,   249,   250,
     250,   250,   250,   250,   251,   251,   251,   251,   251,   252,
     253,   253,   253,   254,   254,   255,   255,   256,   256,   256,
     257,   257,   258,   258,   259,   259,   259,   259,   259,   260,
     260,   260,   260,   260,   261,   262,   262,   262,   263,   263,
     264,   264,   265,   265,   265,   266,   266,   267,   267,   268,
     268,   268,   268,   268,   268,   269,   269,   269,   269,   269,
     269,   270,   270,   270,   271,   271,   271,   272,   272,   272,
     273,   273,   274,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   274,   274,   275,   275,   275,
     275,   275,   276,   276,   276,   277,   277,   277,   277,   277,
     278,   278,   278,   279,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     281,   281,   281,   282,   282,   283,   283,   284,   284,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   290,   290,
     291,   291,   292,   292,   293,   293,   294,   294,   294,   295,
     295,   295,   296,   296,   296,   296,   297,   298,   298,   298,
     298,   298,   298,   299,   299,   299,   299,   300,   300,   300,
     300,   301,   301,   301,   301,   302,   303,   304,   304,   304,
     304,   305,   306,   306,   307,   308,   308,   308,   308,   309,
     310,   311,   312,   312,   313,   314,   315,   316,   316,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     3,     2,     1,     3,     3,     2,
       2,     3,     2,     0,     5,     5,     1,     1,     1,     1,
       5,     5,     5,     7,    12,    12,    12,    14,     6,     6,
       6,     4,     4,     4,     8,     6,    13,    13,    13,    11,
      11,    11,    15,    13,     2,     2,     3,     6,     6,     4,
       8,     8,     8,     8,     8,     8,     6,     8,     6,     6,
       8,     6,     8,     8,     8,     6,     8,     6,     8,     8,
       6,     8,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     8,     6,     8,
       8,    10,     8,    10,     8,    10,     8,    10,     6,     8,
       8,     8,     6,     8,     8,     8,     6,     8,     6,     8,
       6,     8,     8,    10,     8,    10,     8,    10,     6,     8,
       8,     8,     8,     6,     8,     8,     8,     6,     8,     8,
       6,     8,     6,     8,     6,     8,     8,     6,     6,     6,
       8,     6,     8,     8,     8,     1,     4,     3,     1,     1,
       3,     1,     2,     2,     3,     1,     3,     3,     3,     4,
       4,     4,     5,     6,     8,     1,     3,     1,     1,     1,
       2,     2,     2,     3,     4,     1,     1,     3,     3,     3,
       1,     1,     3,     1,     1,     1,     4,     4,     1,     1,
       1,     4,     4,     1,     1,     1,     1,     1,     3,     2,
       3,     1,     1,     1,     1,     3,     2,     3,     1,     1,
       1,     1,     4,     4,     1,     1,     1,     4,     4,     1,
       1,     1,     1,     3,     2,     3,     1,     1,     1,     1,
       3,     2,     3,     1,     1,     1,     1,     4,     4,     1,
       1,     1,     4,     4,     1,     1,     1,     1,     3,     2,
       3,     1,     1,     1,     1,     3,     2,     3,     1,     1,
       1,     1,     1,     4,     4,     3,     3,     4,     4,     1,
       1,     3,     1,     0,     3,     1,     1,     3,     1,     0,
       3,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       3,     2,     4,     4,     1,     1,     4,     3,     8,     3,
       6,     0,     5,     3,     0,     3,     8,     3,     6,     0,
       3,     1,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     6,     4,     6,     6,     4,     4,     8,
       6,     6,     6,     6,     6,     6,     6,     6,    10,    10,
      10,    10,     8,     8,     8,     8,     8,     8,     4,    12,
      12,     8,    12,    12,    12,    12,     6,     8,     8,     8,
       8,     8,     8,     4,     4,     4,     4,     4,     4,     4,
       4,    10,    10,    10,    10,     8,    10,     8,     8,    10,
      10,    14,    14,    14,    10,     6,     6,     6,     6,     6,
      12,     8,     8,    10,    12,    18,     8,     8,     8,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, scanner, parser, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, scanner, parser); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, msat::FlatZincAbstractParser *parser)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (parser);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, msat::FlatZincAbstractParser *parser)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, parser);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, yyscan_t scanner, msat::FlatZincAbstractParser *parser)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , scanner, parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, parser); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, msat::FlatZincAbstractParser *parser)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (parser);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 200: /* IDENT  */
#line 341 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2730 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 201: /* UNDERSCORE_IDENT  */
#line 341 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2736 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 202: /* STRING_LITERAL  */
#line 341 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2742 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 203: /* INT_LITERAL  */
#line 341 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2748 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 204: /* FLOAT_LITERAL  */
#line 341 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2754 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 226: /* ident_anns  */
#line 341 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2760 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 237: /* bool_ti_expr_tail  */
#line 342 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).domain); }
#line 2766 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 238: /* int_ti_expr_tail  */
#line 342 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).domain); }
#line 2772 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 239: /* num_literals  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).numlist); }
#line 2778 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 240: /* float_ti_expr_tail  */
#line 342 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).domain); }
#line 2784 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 244: /* array_par_bool_expr  */
#line 344 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2790 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 245: /* array_par_bool_literal  */
#line 344 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2796 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 246: /* array_par_bool_elements  */
#line 344 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2802 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 247: /* array_var_bool_expr  */
#line 345 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2808 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 248: /* array_var_bool_literal  */
#line 345 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2814 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 249: /* array_var_bool_elements  */
#line 345 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2820 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 253: /* array_par_int_expr  */
#line 346 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2826 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 254: /* array_par_int_literal  */
#line 346 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2832 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 255: /* array_par_int_elements  */
#line 346 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2838 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 256: /* array_var_int_expr  */
#line 347 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2844 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 257: /* array_var_int_literal  */
#line 347 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2850 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 258: /* array_var_int_elements  */
#line 347 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2856 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 262: /* array_par_float_expr  */
#line 348 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2862 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 263: /* array_par_float_literal  */
#line 348 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2868 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 264: /* array_par_float_elements  */
#line 348 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2874 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 265: /* array_var_float_expr  */
#line 349 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2880 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 266: /* array_var_float_literal  */
#line 349 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2886 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 267: /* array_var_float_elements  */
#line 349 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2892 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 269: /* set_literal  */
#line 351 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2898 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 270: /* set_elements  */
#line 351 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2904 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 271: /* set_array_literal  */
#line 351 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2910 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 272: /* set_array_elements  */
#line 351 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2916 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 275: /* annotations  */
#line 350 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).annotation); }
#line 2922 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 276: /* shape_list  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).intlist); }
#line 2928 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, msat::FlatZincAbstractParser *parser)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 362 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3224 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 366 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3232 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 370 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3240 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 374 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3248 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 378 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYERROR;
  }
#line 3256 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 396 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYERROR;
  }
#line 3264 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 408 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
  }
#line 3272 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 412 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    // nothing to do
  }
#line 3280 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 418 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3286 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 419 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3292 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 420 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3298 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 421 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3304 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 431 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    if ((yyvsp[0].term)) {
        parser->declare_par(dom, (yyvsp[-2].string), (yyvsp[0].term));
    }
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3316 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 439 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    if ((yyvsp[0].term)) {
        parser->declare_par(dom, (yyvsp[-2].string), (yyvsp[0].term));
    }
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3328 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 447 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    if ((yyvsp[0].term)) {
        parser->declare_par(dom, (yyvsp[-2].string), (yyvsp[0].term));
    }
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3340 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 455 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_par_set(dom, (yyvsp[-2].string), (yyvsp[0].node)->set_);
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3351 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 469 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-9].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    FznType v;

    size_t len = parser_atoi(parser, (yyvsp[-7].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_par(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->termlist_);
    MSAT_SFREE((yyvsp[-9].string));
    MSAT_SFREE((yyvsp[-7].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3374 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 488 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-9].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-7].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_par(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->termlist_);
    MSAT_SFREE((yyvsp[-9].string));
    MSAT_SFREE((yyvsp[-7].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3395 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 505 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-9].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-7].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_par(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->termlist_);
    MSAT_SFREE((yyvsp[-9].string));
    MSAT_SFREE((yyvsp[-7].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3416 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 522 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-11].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-9].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_par_set(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->set_list_);
    MSAT_SFREE((yyvsp[-11].string));
    MSAT_SFREE((yyvsp[-9].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3437 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 546 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var(dom, (yyvsp[-2].string), (yyvsp[0].term));
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3447 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 552 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //cout<<"integer";
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var(dom, (yyvsp[-2].string), (yyvsp[0].term));
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3458 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 559 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //cout<<"integer var2\n";
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var(dom, (yyvsp[-2].string), (yyvsp[0].term));
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3469 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 566 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var(dom, (yyvsp[0].string), NULL);
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3479 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 572 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //cout<<"integer var\n";
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var(dom, (yyvsp[0].string), NULL);
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3490 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 579 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var(dom, (yyvsp[0].string), NULL);
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3500 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 585 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var_set(dom, (yyvsp[-2].string), (yyvsp[0].node)->set_);
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3511 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 592 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var_set(dom, (yyvsp[0].string), FznSetSharedPtr());
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3521 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 605 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-10].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-8].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_var(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->termlist_);
    MSAT_SFREE((yyvsp[-10].string));
    MSAT_SFREE((yyvsp[-8].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3542 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 622 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-10].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-8].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_var(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->termlist_);
    MSAT_SFREE((yyvsp[-10].string));
    MSAT_SFREE((yyvsp[-8].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3563 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 639 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-10].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-8].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_var(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->termlist_);
    MSAT_SFREE((yyvsp[-10].string));
    MSAT_SFREE((yyvsp[-8].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3584 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 656 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-8].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-6].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    TermListSharedPtr terms(NULL);
    parser->declare_array_var(len, dom, (yyvsp[0].string), terms);
    MSAT_SFREE((yyvsp[-8].string));
    MSAT_SFREE((yyvsp[-6].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3605 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 673 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-8].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-6].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    TermListSharedPtr terms(NULL);
    parser->declare_array_var(len, dom, (yyvsp[0].string), terms);
    MSAT_SFREE((yyvsp[-8].string));
    MSAT_SFREE((yyvsp[-6].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3626 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 690 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-8].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-6].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    TermListSharedPtr terms(NULL);
    parser->declare_array_var(len, dom, (yyvsp[0].string), terms);
    MSAT_SFREE((yyvsp[-8].string));
    MSAT_SFREE((yyvsp[-6].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3647 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 707 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-12].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-10].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_array_var_set(len, dom, (yyvsp[-2].string), (yyvsp[0].node)->set_list_);
    MSAT_SFREE((yyvsp[-12].string));
    MSAT_SFREE((yyvsp[-10].string));
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3668 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 724 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t one = parser_atoi(parser, (yyvsp[-10].string));
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, (yyvsp[-8].string));
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_array_var_set(len, dom, (yyvsp[0].string), FznSetListSharedPtr());
    MSAT_SFREE((yyvsp[-10].string));
    MSAT_SFREE((yyvsp[-8].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3688 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 747 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->annotate_decl((yyvsp[-1].string), *(yyvsp[0].annotation));
    delete (yyvsp[0].annotation);
    (yyval.string) = (yyvsp[-1].string);
    // MSAT_SFREE: postponed
  }
#line 3699 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 754 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->annotate_decl((yyvsp[-1].string), *(yyvsp[0].annotation));
    delete (yyvsp[0].annotation);
    (yyval.string) = (yyvsp[-1].string);
    // MSAT_SFREE: postponed
  }
#line 3710 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 768 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {

  }
#line 3718 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 775 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_and(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3727 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 780 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_or(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3736 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 785 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_xor(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 3745 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 790 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3754 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 795 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_float_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3763 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 800 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_int_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3772 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 805 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_bool_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3781 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 810 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_float_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3790 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 815 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_int_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3799 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 820 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool2int((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3807 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 824 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_and((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3815 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 828 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_clause(*((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 3825 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 834 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_eq((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3833 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 838 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_eq_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3841 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 842 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_le((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3849 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 846 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_le_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3857 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 850 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lin_eq(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 3867 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 856 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lin_le(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 3877 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 862 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3885 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 866 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lt_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3893 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 870 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_not((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3901 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 874 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_or((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3909 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 878 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_xor((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3917 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 882 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_abs((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3925 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 886 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_div((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3933 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 890 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_acos((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3941 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 894 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_asin((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3949 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 898 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_atan((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3957 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 902 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_cos((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3965 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 906 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_cosh((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3973 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 910 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_exp((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3981 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 914 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_ln((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3989 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 918 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_log10((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3997 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 922 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_log2((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4005 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 926 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_sqrt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4013 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 930 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_sin((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4021 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 934 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_sinh((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4029 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 938 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_tan((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4037 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 942 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_tanh((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4045 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 946 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_eq((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4053 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 950 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_eq_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4061 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 954 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_le((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4069 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 958 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_le_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4077 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 962 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_eq(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4087 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 968 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_eq_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4097 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 974 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_le(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4107 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 980 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_le_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4117 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 986 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_lt(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4127 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 992 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_lt_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4137 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 998 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_ne(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4147 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 1004 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_ne_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4157 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 1010 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4165 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 1014 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lt_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4173 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 1018 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_max((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4181 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 1022 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_min((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4189 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 1026 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_ne((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4197 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 1030 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_ne_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4205 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 1034 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_plus((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4213 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 1038 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_times((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4221 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 1042 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_abs((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4229 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 1046 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_div((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4237 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 1050 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_eq((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4245 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 1054 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_eq_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4253 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 1058 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_le((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4261 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 1062 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_le_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4269 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 1066 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_eq(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4279 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 1072 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_eq_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4289 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 1078 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_le(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4299 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 1084 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_le_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4309 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 1090 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_ne(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4319 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 1096 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_ne_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4329 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 1102 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4337 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 1106 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lt_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4345 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 1110 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_max((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4353 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 1114 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_min((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4361 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 1118 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_mod((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4369 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 1122 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_ne((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4377 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 1126 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_ne_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4385 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 1130 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_plus((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4393 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 1134 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_times((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4401 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 1138 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int2float((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4409 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 1142 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_set_element((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4419 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 1148 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_set_element((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4429 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 1154 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_card((yyvsp[-3].node)->set_, (yyvsp[-1].term));
  }
#line 4437 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 1158 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_diff((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4448 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 1165 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_eq((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4458 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 1171 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_eq_reif((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4468 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 1177 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_in((yyvsp[-3].term), (yyvsp[-1].node)->set_);
    delete (yyvsp[-1].node);
  }
#line 4477 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 1182 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_in_reif((yyvsp[-5].term), (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 4486 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 1187 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_intersect((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4497 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 1194 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_le((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4507 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 1200 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_lt((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4517 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 1206 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_ne((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4527 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 1212 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_ne_reif((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4537 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 1218 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_subset((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4547 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 1224 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_subset_reif((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4557 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 1230 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_symdiff((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4568 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 1237 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_union((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4579 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 1244 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4586 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 1247 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    std::stringstream ss;
    ss << "constraint '" << (yyvsp[-3].string)
       << "' is not supported.";
    parser->handle_error(ss.str().c_str());
  }
#line 4597 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 1257 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //std::cout<<"Solve maxiize\n";
    //parser->check_sat();
  }
#line 4606 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 1265 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4613 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 1268 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4620 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 1274 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4627 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 1277 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4634 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 1283 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->push_objective(FlatZincAbstractParser::MINIMIZE, (yyvsp[0].term));
  }
#line 4642 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 1287 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->push_objective(FlatZincAbstractParser::MAXIMIZE, (yyvsp[0].term));
  }
#line 4650 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 1297 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 4656 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 1298 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 4662 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 1302 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4668 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 1303 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4674 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 1304 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4680 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 1305 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4686 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 1306 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4692 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 1307 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4698 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 1308 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4704 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 1309 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4710 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 1311 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4718 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 1317 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 4724 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 1318 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[-2].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4730 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 1322 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4736 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 1323 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4742 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 1324 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4748 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 1325 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4754 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 1326 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4760 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 1327 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4766 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 1328 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4772 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 1329 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4778 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 1338 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_BOOL);
  }
#line 4786 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 1345 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_INT);
  }
#line 4794 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 1349 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_INT,
                               number_from_str((yyvsp[-2].string)),
                               number_from_str((yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4806 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 1357 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_INT, (*(yyvsp[-1].numlist)));
    delete (yyvsp[-1].numlist);
  }
#line 4815 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 1365 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[0].numlist)->push_back(number_from_str((yyvsp[-2].string)));
    (yyval.numlist) = (yyvsp[0].numlist);
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 4825 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 1371 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.numlist) = new std::vector<Number>();
    (yyval.numlist)->push_back(number_from_str((yyvsp[0].string)));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4835 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 1380 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_FLOAT);
  }
#line 4843 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 1384 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_FLOAT,
                               number_from_str((yyvsp[-2].string)),
                               number_from_str((yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4855 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 1402 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 4861 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 1403 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4867 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 1404 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4873 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 1405 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4884 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 1412 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4895 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 1421 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 4901 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 1422 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4907 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 1423 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4913 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 1424 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4924 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 1431 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4935 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 1441 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_false();
  }
#line 4943 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 1445 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_true();
  }
#line 4951 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 1455 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 4959 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 1459 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4969 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 1465 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4979 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 1474 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 4987 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 199:
#line 1478 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 4996 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 200:
#line 1486 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5005 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 201:
#line 1491 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5015 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 202:
#line 1500 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5023 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 203:
#line 1504 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5033 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 204:
#line 1510 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5043 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 205:
#line 1519 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5051 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 206:
#line 1523 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5060 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 207:
#line 1531 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5069 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 208:
#line 1536 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5079 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 209:
#line 1548 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5085 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 210:
#line 1549 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5091 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 211:
#line 1550 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5097 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 212:
#line 1552 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5108 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 213:
#line 1559 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5119 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 214:
#line 1568 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5125 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 215:
#line 1569 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5131 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 216:
#line 1570 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5137 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 217:
#line 1572 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5148 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 218:
#line 1579 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5159 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 219:
#line 1589 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_int_number((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5168 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 220:
#line 1601 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5176 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 221:
#line 1605 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5186 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 222:
#line 1611 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5196 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 223:
#line 1620 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5204 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 224:
#line 1624 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5213 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 225:
#line 1632 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5222 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 226:
#line 1637 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5232 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 227:
#line 1646 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5240 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 228:
#line 1650 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5250 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 229:
#line 1656 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5260 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 230:
#line 1665 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5268 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 231:
#line 1669 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5277 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 232:
#line 1677 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5286 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 233:
#line 1682 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5296 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 234:
#line 1694 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5302 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 235:
#line 1695 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5308 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 236:
#line 1696 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5314 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 237:
#line 1698 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5325 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 238:
#line 1705 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5336 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 239:
#line 1714 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5342 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 240:
#line 1715 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5348 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 241:
#line 1716 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5354 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 242:
#line 1718 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5365 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 243:
#line 1725 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5376 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 244:
#line 1735 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_float_number((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5385 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 245:
#line 1747 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5393 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 246:
#line 1751 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5403 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 247:
#line 1757 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5413 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 248:
#line 1766 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5421 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 249:
#line 1770 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5430 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 250:
#line 1778 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5439 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 251:
#line 1783 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5449 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 252:
#line 1792 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5457 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 253:
#line 1796 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5467 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 254:
#line 1802 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5477 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 255:
#line 1811 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5485 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 256:
#line 1815 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5494 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 257:
#line 1823 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5503 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 258:
#line 1828 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5513 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 259:
#line 1840 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5519 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 260:
#line 1841 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5525 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 261:
#line 1842 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5531 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 262:
#line 1843 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5537 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 263:
#line 1845 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5548 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 264:
#line 1852 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5559 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 265:
#line 1866 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5567 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 266:
#line 1870 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    FlatZincSet *set = new FlatZincSet(true);
    (yyval.node)->set_.reset(set);
    set->add_set_elements(NumInterval(number_from_str((yyvsp[-2].string)),
                                      number_from_str((yyvsp[0].string))));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5581 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 267:
#line 1880 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5593 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 268:
#line 1888 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5605 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 269:
#line 1896 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5615 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 270:
#line 1902 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5625 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 271:
#line 1911 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-2].node);
    (yyval.node)->set_->add_set_elements(NumInterval(number_from_str((yyvsp[0].string))));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5635 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 272:
#line 1917 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_.reset(new FlatZincSet(true));
    (yyval.node)->set_->add_set_elements(NumInterval(number_from_str((yyvsp[0].string))));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5646 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 273:
#line 1924 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_.reset(new FlatZincSet(true));
  }
#line 5655 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 274:
#line 1932 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5663 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 275:
#line 1936 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_ = parser->get_array_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5673 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 276:
#line 1942 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_ = parser->get_array_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5683 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 277:
#line 1951 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-2].node);
    (yyval.node)->set_list_->push_back((yyvsp[0].node)->set_);
    delete (yyvsp[0].node);
  }
#line 5693 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 278:
#line 1957 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_.reset(new FznSetList());
    (yyval.node)->set_list_->push_back((yyvsp[0].node)->set_);
    delete (yyvsp[0].node);
  }
#line 5704 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 279:
#line 1964 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_.reset(new FznSetList());
  }
#line 5713 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 280:
#line 1976 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5720 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 281:
#line 1979 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5727 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 282:
#line 1985 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5734 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 283:
#line 1988 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5741 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 284:
#line 1991 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5749 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 285:
#line 1995 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5757 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 286:
#line 1999 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5765 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 287:
#line 2003 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5772 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 288:
#line 2006 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5779 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 289:
#line 2009 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5788 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 290:
#line 2014 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5795 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 291:
#line 2017 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5802 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 292:
#line 2020 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5811 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 293:
#line 2025 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5820 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 294:
#line 2030 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5828 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 295:
#line 2034 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5836 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 296:
#line 2038 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
  }
#line 5844 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 297:
#line 2049 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].annotation)->set_output_var();
    (yyval.annotation) = (yyvsp[-2].annotation);
  }
#line 5853 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 298:
#line 2054 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-7].annotation)->set_output_array(*(yyvsp[-2].intlist));
    (yyval.annotation) = (yyvsp[-7].annotation);
    delete (yyvsp[-2].intlist);
  }
#line 5863 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 299:
#line 2060 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
    (yyval.annotation) = (yyvsp[-2].annotation);
  }
#line 5872 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 300:
#line 2065 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
    (yyval.annotation) = (yyvsp[-5].annotation);
  }
#line 5881 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 301:
#line 2070 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.annotation) = new FlatZincAnnotation();
  }
#line 5889 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 302:
#line 2077 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-4].intlist)->push_back(parser_atoi(parser,(yyvsp[-2].string)));
    (yyvsp[-4].intlist)->push_back(parser_atoi(parser,(yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
    (yyval.intlist) = (yyvsp[-4].intlist);
  }
#line 5901 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 303:
#line 2085 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.intlist) = new std::vector<int64_t>();
    (yyval.intlist)->push_back(parser_atoi(parser,(yyvsp[-2].string)));
    (yyval.intlist)->push_back(parser_atoi(parser,(yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5913 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 304:
#line 2093 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.intlist) = new std::vector<int64_t>();
  }
#line 5921 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 305:
#line 2103 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5927 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 306:
#line 2104 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5933 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 307:
#line 2105 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[0].string)); }
#line 5939 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 308:
#line 2106 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[-3].string)); }
#line 5945 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 309:
#line 2107 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5951 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 310:
#line 2111 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5957 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 311:
#line 2112 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5963 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 312:
#line 2113 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5969 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 313:
#line 2117 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[-2].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5975 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 349:
#line 2161 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    // supported
  }
#line 5983 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 350:
#line 2168 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_different_except_0(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 5992 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 351:
#line 2173 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_different(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6001 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 352:
#line 2178 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_different((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6010 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 353:
#line 2186 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->disjoint((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6020 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 354:
#line 2192 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_disjoint((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6029 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 355:
#line 2200 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->disjunctive(*((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6039 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 356:
#line 2206 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->disjunctive_strict(*((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6049 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 357:
#line 2215 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_equal(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6058 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 358:
#line 2220 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_equal((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6067 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 359:
#line 2228 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->among((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6077 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 360:
#line 2237 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6086 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 361:
#line 2242 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6095 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 362:
#line 2250 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6104 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 363:
#line 2255 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6113 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 364:
#line 2263 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6122 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 365:
#line 2268 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6131 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 366:
#line 2276 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6140 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 367:
#line 2281 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6149 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 368:
#line 2291 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->maximum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6164 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 369:
#line 2303 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->maximum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6179 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 370:
#line 2319 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->minimum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6194 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 371:
#line 2331 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->minimum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6209 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 372:
#line 2345 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_geq((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6218 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 373:
#line 2350 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->at_least_set((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6228 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 374:
#line 2359 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_eq((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6237 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 375:
#line 2364 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->exactly_set((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6247 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 376:
#line 2373 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_leq((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6256 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 377:
#line 2378 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->at_least_set((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6266 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 378:
#line 2384 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->at_most_1((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6275 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 379:
#line 2393 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval c_ival(start, end);

    parser->bin_packing_capa(*((yyvsp[-9].node)->termlist_), *((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), c_ival);
    delete (yyvsp[-9].node);
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6292 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 380:
#line 2407 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval load_ival(start, end);

    parser->bin_packing_load(*((yyvsp[-9].node)->termlist_), *((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), load_ival);
    delete (yyvsp[-9].node);
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6309 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 381:
#line 2420 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bin_packing((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6319 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 382:
#line 2430 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);
    parser->element((yyvsp[-9].term), *((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6333 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 383:
#line 2441 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);
    parser->element((yyvsp[-9].term), *((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6347 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 384:
#line 2452 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);
    parser->element((yyvsp[-9].term), *((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6361 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 385:
#line 2463 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);
    parser->element((yyvsp[-9].term), (yyvsp[-7].node)->set_list_, (yyvsp[-5].node)->set_, x_ival);
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6376 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 386:
#line 2477 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->comparison_rel_array(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6385 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 387:
#line 2485 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_eq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6394 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 388:
#line 2490 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_geq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6403 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 389:
#line 2495 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_gt((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6412 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 390:
#line 2500 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_leq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6421 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 391:
#line 2505 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_lt((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6430 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 392:
#line 2510 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_neq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6439 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 393:
#line 2518 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6448 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 394:
#line 2523 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6457 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 395:
#line 2528 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6466 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 396:
#line 2533 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6475 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 397:
#line 2541 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6484 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 398:
#line 2546 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6493 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 399:
#line 2551 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6502 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 400:
#line 2556 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6511 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 401:
#line 2564 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6523 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 402:
#line 2572 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn_nonstrict(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6535 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 403:
#line 2580 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn_nonoverlap_k(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6547 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 404:
#line 2589 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn_nonstrict_nonoverlap_k(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6559 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 405:
#line 2600 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->distribute(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6570 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 406:
#line 2611 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->geost_nonoverlap_k(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6582 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 407:
#line 2622 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6593 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 408:
#line 2629 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality_closed(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6604 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 409:
#line 2636 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality_low_up(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6616 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 410:
#line 2644 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality_low_up_closed(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6628 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 411:
#line 2657 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number xstart = number_from_str((yyvsp[-7].string));
    Number xend   = number_from_str((yyvsp[-5].string));
    Number ystart = number_from_str((yyvsp[-3].string));
    Number yend   = number_from_str((yyvsp[-1].string));

    NumInterval x_ival(xstart, xend);
    NumInterval y_ival(ystart, yend);

    parser->int_set_channel(*((yyvsp[-11].node)->termlist_), (yyvsp[-9].node)->set_list_, x_ival, y_ival);
    delete (yyvsp[-11].node);
    delete (yyvsp[-9].node);
    MSAT_SFREE((yyvsp[-7].string));
    MSAT_SFREE((yyvsp[-5].string));
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6650 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 412:
#line 2680 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number fstart = number_from_str((yyvsp[-7].string));
    Number fend   = number_from_str((yyvsp[-5].string));
    Number invfstart = number_from_str((yyvsp[-3].string));
    Number invfend   = number_from_str((yyvsp[-1].string));

    NumInterval f_ival(fstart, fend);
    NumInterval invf_ival(invfstart, invfend);

    parser->inverse(*((yyvsp[-11].node)->termlist_), *((yyvsp[-9].node)->termlist_), f_ival, invf_ival);

    delete (yyvsp[-11].node);
    delete (yyvsp[-9].node);
    MSAT_SFREE((yyvsp[-7].string));
    MSAT_SFREE((yyvsp[-5].string));
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6673 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 413:
#line 2701 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number fstart = number_from_str((yyvsp[-7].string));
    Number fend   = number_from_str((yyvsp[-5].string));
    Number invfstart = number_from_str((yyvsp[-3].string));
    Number invfend   = number_from_str((yyvsp[-1].string));

    NumInterval f_ival(fstart, fend);
    NumInterval invf_ival(invfstart, invfend);

    parser->inverse_set((yyvsp[-11].node)->set_list_, (yyvsp[-9].node)->set_list_,
                        f_ival, invf_ival);
    delete (yyvsp[-11].node);
    delete (yyvsp[-9].node);
    MSAT_SFREE((yyvsp[-7].string));
    MSAT_SFREE((yyvsp[-5].string));
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6696 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 414:
#line 2724 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number bstart = number_from_str((yyvsp[-3].string));
    Number bend   = number_from_str((yyvsp[-1].string));

    NumInterval b_ival(bstart, bend);

    parser->link_set_to_booleans((yyvsp[-7].node)->set_, *((yyvsp[-5].node)->termlist_), b_ival);
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6713 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 415:
#line 2740 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6722 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 416:
#line 2745 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6731 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 417:
#line 2750 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6740 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 418:
#line 2755 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member((yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6750 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 419:
#line 2764 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->nvalue((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6759 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 420:
#line 2773 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number xstart = number_from_str((yyvsp[-3].string));
    Number xend   = number_from_str((yyvsp[-1].string));

    NumInterval x_ival(xstart, xend);

    parser->range(*((yyvsp[-9].node)->termlist_), (yyvsp[-7].node)->set_, (yyvsp[-5].node)->set_, x_ival);
    delete (yyvsp[-9].node);
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6777 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 421:
#line 2790 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_clause_reif(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 6787 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 422:
#line 2799 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_in((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 6795 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 423:
#line 2804 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_dom((yyvsp[-7].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
  }
#line 6804 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 424:
#line 2813 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number xstart = number_from_str((yyvsp[-3].string));
    Number xend   = number_from_str((yyvsp[-1].string));

    NumInterval x_ival(xstart, xend);

    parser->roots(*((yyvsp[-9].node)->termlist_), (yyvsp[-7].node)->set_, (yyvsp[-5].node)->set_, x_ival);
    delete (yyvsp[-9].node);
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6822 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 425:
#line 2832 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number csstart = number_from_str((yyvsp[-7].string));
    Number csend   = number_from_str((yyvsp[-5].string));
    Number setsstart = number_from_str((yyvsp[-3].string));
    Number setsend   = number_from_str((yyvsp[-1].string));

    NumInterval cs_ival(csstart, csend);
    NumInterval sets_ival(setsstart, setsend);

    parser->sum_pred((yyvsp[-15].term), (yyvsp[-13].node)->set_list_, *((yyvsp[-11].node)->termlist_), (yyvsp[-9].term), cs_ival, sets_ival);
    delete (yyvsp[-13].node);
    delete (yyvsp[-11].node);
    MSAT_SFREE((yyvsp[-7].string));
    MSAT_SFREE((yyvsp[-5].string));
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6844 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 426:
#line 2854 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->symmetric_all_different(*((yyvsp[-5].node)->termlist_), x_ival);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6859 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 427:
#line 2868 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->value_precede((yyvsp[-5].term), (yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6868 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 428:
#line 2873 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->value_precede((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6877 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 507:
#line 2959 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {

  }
#line 6885 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;


#line 6889 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, scanner, parser, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, scanner, parser, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc, scanner, parser);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, scanner, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, parser);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, scanner, parser);
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
  return yyresult;
}
#line 2967 "parser/flatzincbisonparser.yy" /* yacc.c:1906  */


namespace {

inline Number number_from_str(const char *str)
{
    assert(str);
    return Number::from_str(str);
}

} // namespace
