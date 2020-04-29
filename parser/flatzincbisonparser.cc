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
    TK_INT_LIN_LT = 347,
    TK_INT_LIN_LT_REIF = 348,
    TK_INT_LIN_NE = 349,
    TK_INT_LIN_NE_REIF = 350,
    TK_INT_LT = 351,
    TK_INT_LT_REIF = 352,
    TK_INT_MAX = 353,
    TK_INT_MIN = 354,
    TK_INT_MOD = 355,
    TK_INT_NE = 356,
    TK_INT_NE_REIF = 357,
    TK_INT_PLUS = 358,
    TK_INT_TIMES = 359,
    TK_INT2FLOAT = 360,
    TK_SET_CARD = 361,
    TK_SET_DIFF = 362,
    TK_SET_EQ = 363,
    TK_SET_EQ_REIF = 364,
    TK_SET_IN = 365,
    TK_SET_IN_REIF = 366,
    TK_SET_INTERSECT = 367,
    TK_SET_LE = 368,
    TK_SET_LT = 369,
    TK_SET_NE = 370,
    TK_SET_NE_REIF = 371,
    TK_SET_SUBSET = 372,
    TK_SET_SUBSET_REIF = 373,
    TK_SET_SYMDIFF = 374,
    TK_SET_UNION = 375,
    TK_ALLDIFFERENT_EXCEPT_0 = 376,
    TK_ALL_DIFFERENT_INT = 377,
    TK_ALL_DIFFERENT_SET = 378,
    TK_ALL_DISJOINT = 379,
    TK_DISJOINT = 380,
    TK_DISJUNCTIVE = 381,
    TK_DISJUNCTIVE_STRICT = 382,
    TK_ALL_EQUAL_INT = 383,
    TK_ALL_EQUAL_SET = 384,
    TK_AMONG = 385,
    TK_MAXIMUM_FLOAT = 386,
    TK_MAXIMUM_INT = 387,
    TK_MINIMUM_FLOAT = 388,
    TK_MINIMUM_INT = 389,
    TK_ARRAY_FLOAT_MAXIMUM = 390,
    TK_ARRAY_INT_MAXIMUM = 391,
    TK_ARRAY_FLOAT_MINIMUM = 392,
    TK_ARRAY_INT_MINIMUM = 393,
    TK_MAXIMUM_ARG_INT = 394,
    TK_MAXIMUM_ARG_FLOAT = 395,
    TK_MINIMUM_ARG_INT = 396,
    TK_MINIMUM_ARG_FLOAT = 397,
    TK_AT_LEAST_INT = 398,
    TK_AT_LEAST_SET = 399,
    TK_EXACTLY_INT = 400,
    TK_EXACTLY_SET = 401,
    TK_AT_MOST_INT = 402,
    TK_AT_MOST_SET = 403,
    TK_ATMOST1 = 404,
    TK_BIN_PACKING_CAPA = 405,
    TK_BIN_PACKING_LOAD = 406,
    TK_BIN_PACKING = 407,
    TK_ELEMENT_BOOL = 408,
    TK_ELEMENT_FLOAT = 409,
    TK_ELEMENT_INT = 410,
    TK_ELEMENT_SET = 411,
    TK_COMPARISON_REL_ARRAY = 412,
    TK_COUNT_EQ = 413,
    TK_COUNT_GEQ = 414,
    TK_COUNT_GT = 415,
    TK_COUNT_LEQ = 416,
    TK_COUNT_LT = 417,
    TK_COUNT_NEQ = 418,
    TK_DECREASING_BOOL = 419,
    TK_DECREASING_FLOAT = 420,
    TK_DECREASING_INT = 421,
    TK_DECREASING_SET = 422,
    TK_INCREASING_BOOL = 423,
    TK_INCREASING_FLOAT = 424,
    TK_INCREASING_INT = 425,
    TK_INCREASING_SET = 426,
    TK_DIFFN = 427,
    TK_DIFFN_NONSTRICT = 428,
    TK_DIFFN_NONOVERLAP_K = 429,
    TK_DIFFN_NONSTRICT_NONOVERLAP_K = 430,
    TK_DISTRIBUTE = 431,
    TK_GEOST_NONOVERLAP_K = 432,
    TK_GLOBAL_CARDINALITY = 433,
    TK_GLOBAL_CARDINALITY_CLOSED = 434,
    TK_GLOBAL_CARDINALITY_LOW_UP = 435,
    TK_GLOBAL_CARDINALITY_LOW_UP_CLOSED = 436,
    TK_INT_SET_CHANNEL = 437,
    TK_INVERSE = 438,
    TK_INVERSE_SET = 439,
    TK_LINK_SET_TO_BOOLEANS = 440,
    TK_MEMBER_BOOL = 441,
    TK_MEMBER_FLOAT = 442,
    TK_MEMBER_INT = 443,
    TK_MEMBER_SET = 444,
    TK_NVALUE = 445,
    TK_RANGE = 446,
    TK_BOOL_CLAUSE_REIF = 447,
    TK_FLOAT_IN = 448,
    TK_FLOAT_DOM = 449,
    TK_ROOTS = 450,
    TK_SUM_PRED = 451,
    TK_SYMMETRIC_ALL_DIFFERENT = 452,
    TK_VALUE_PRECEDE_INT = 453,
    TK_VALUE_PRECEDE_SET = 454,
    TK_OUTPUT_VAR = 455,
    TK_OUTPUT_ARRAY = 456,
    IDENT = 457,
    UNDERSCORE_IDENT = 458,
    STRING_LITERAL = 459,
    INT_LITERAL = 460,
    FLOAT_LITERAL = 461
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

#line 390 "parser/flatzincbisonparser.cc" /* yacc.c:355  */
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

#line 420 "parser/flatzincbisonparser.cc" /* yacc.c:358  */

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
#define YYLAST   2629

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  217
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  507
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1902

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   461

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
     208,   209,     2,     2,   214,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   210,   207,
       2,   211,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   212,     2,   213,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   215,     2,   216,     2,     2,     2,     2,
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
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   363,   363,   367,   371,   375,   379,   386,   387,   388,
     389,   393,   394,   398,   409,   413,   420,   421,   422,   423,
     432,   440,   448,   456,   470,   489,   506,   523,   547,   553,
     560,   567,   573,   580,   586,   593,   606,   623,   640,   657,
     674,   691,   708,   725,   748,   755,   769,   776,   781,   786,
     791,   796,   801,   806,   811,   816,   821,   825,   829,   835,
     839,   843,   847,   851,   857,   863,   867,   871,   875,   879,
     883,   887,   891,   895,   899,   903,   907,   911,   915,   919,
     923,   927,   931,   935,   939,   943,   947,   951,   955,   959,
     963,   969,   975,   981,   987,   993,   999,  1005,  1011,  1015,
    1019,  1023,  1027,  1031,  1035,  1039,  1043,  1047,  1051,  1055,
    1059,  1063,  1067,  1073,  1079,  1085,  1091,  1097,  1103,  1107,
    1111,  1115,  1119,  1123,  1127,  1131,  1135,  1139,  1143,  1149,
    1155,  1159,  1166,  1172,  1178,  1183,  1188,  1195,  1201,  1207,
    1213,  1219,  1225,  1231,  1238,  1245,  1248,  1258,  1266,  1269,
    1275,  1278,  1284,  1288,  1299,  1300,  1304,  1305,  1306,  1307,
    1308,  1309,  1310,  1311,  1312,  1319,  1320,  1324,  1325,  1326,
    1327,  1328,  1329,  1330,  1331,  1339,  1346,  1350,  1358,  1366,
    1372,  1381,  1385,  1404,  1405,  1406,  1407,  1413,  1423,  1424,
    1425,  1426,  1432,  1442,  1446,  1456,  1460,  1466,  1475,  1479,
    1487,  1492,  1501,  1505,  1511,  1520,  1524,  1532,  1537,  1550,
    1551,  1552,  1553,  1560,  1570,  1571,  1572,  1573,  1580,  1590,
    1602,  1606,  1612,  1621,  1625,  1633,  1638,  1647,  1651,  1657,
    1666,  1670,  1678,  1683,  1696,  1697,  1698,  1699,  1706,  1716,
    1717,  1718,  1719,  1726,  1736,  1748,  1752,  1758,  1767,  1771,
    1779,  1784,  1793,  1797,  1803,  1812,  1816,  1824,  1829,  1842,
    1843,  1844,  1845,  1846,  1853,  1867,  1871,  1881,  1889,  1897,
    1903,  1912,  1918,  1926,  1933,  1937,  1943,  1952,  1958,  1966,
    1977,  1980,  1986,  1989,  1992,  1996,  2000,  2004,  2007,  2010,
    2015,  2018,  2021,  2026,  2031,  2035,  2039,  2050,  2055,  2061,
    2066,  2072,  2078,  2086,  2095,  2105,  2106,  2107,  2108,  2109,
    2113,  2114,  2115,  2119,  2127,  2128,  2129,  2130,  2131,  2132,
    2133,  2134,  2135,  2136,  2137,  2138,  2139,  2140,  2141,  2142,
    2143,  2144,  2145,  2146,  2147,  2148,  2149,  2150,  2151,  2152,
    2153,  2154,  2155,  2156,  2157,  2158,  2159,  2160,  2161,  2162,
    2169,  2174,  2179,  2187,  2193,  2201,  2207,  2216,  2221,  2229,
    2238,  2243,  2251,  2256,  2264,  2269,  2277,  2282,  2291,  2303,
    2319,  2331,  2346,  2351,  2360,  2365,  2374,  2379,  2385,  2393,
    2407,  2421,  2430,  2441,  2452,  2463,  2478,  2486,  2491,  2496,
    2501,  2506,  2511,  2519,  2524,  2529,  2534,  2542,  2547,  2552,
    2557,  2565,  2573,  2581,  2589,  2601,  2611,  2623,  2630,  2637,
    2645,  2656,  2679,  2700,  2724,  2741,  2746,  2751,  2756,  2765,
    2773,  2791,  2800,  2804,  2813,  2831,  2854,  2869,  2874,  2882,
    2883,  2884,  2885,  2886,  2887,  2888,  2889,  2890,  2891,  2892,
    2893,  2894,  2895,  2896,  2897,  2898,  2899,  2900,  2901,  2902,
    2903,  2904,  2905,  2906,  2907,  2908,  2909,  2910,  2911,  2912,
    2913,  2914,  2915,  2916,  2917,  2918,  2919,  2920,  2921,  2922,
    2923,  2924,  2925,  2926,  2927,  2928,  2929,  2930,  2931,  2932,
    2933,  2934,  2935,  2936,  2937,  2938,  2939,  2940,  2941,  2942,
    2943,  2944,  2945,  2946,  2947,  2948,  2949,  2950,  2951,  2952,
    2953,  2954,  2955,  2956,  2957,  2958,  2959,  2960
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
  "\"int_lin_le\"", "\"int_lin_le_reif\"", "\"int_lin_lt\"",
  "\"int_lin_lt_reif\"", "\"int_lin_ne\"", "\"int_lin_ne_reif\"",
  "\"int_lt\"", "\"int_lt_reif\"", "\"int_max\"", "\"int_min\"",
  "\"int_mod\"", "\"int_ne\"", "\"int_ne_reif\"", "\"int_plus\"",
  "\"int_times\"", "\"int2float\"", "\"set_card\"", "\"set_diff\"",
  "\"set_eq\"", "\"set_eq_reif\"", "\"set_in\"", "\"set_in_reif\"",
  "\"set_intersect\"", "\"set_le\"", "\"set_lt\"", "\"set_ne\"",
  "\"set_ne_reif\"", "\"set_subset\"", "\"set_subset_reif\"",
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
     455,   456,   457,   458,   459,   460,   461,    59,    40,    41,
      58,    61,    91,    93,    44,   123,   125
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
      88,  1679,    26, -1087, -1087, -1087,  -178,    29,  2427, -1087,
      39,    42,  -164,    44,   117,    58, -1087,  -133,  -130, -1087,
   -1087, -1087, -1087,  -119,  -117,  -100,   -95,   -87, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087,   -80,   -72,   111,
     -53,   -49,   -46,   -62,    15,   -39,   -35,   -29,   -26,   -13,
     -11,     8,    14,    19,    21,    25,    27,    45,    81,   106,
     119,   140,   178,   180,   183,   187,   192,   194,   196,   198,
     205,   207,   210,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   230,   239,   240,   241,   242,   243,   245,   246,
     247,   248,   249,   252,   253,   254,   255,   256,   258,   259,
     260,   262,   263,   264,   265,   266,   267,   269,   275,   278,
     279,   281,   282,   286,   288,   289,   290,   291,   292,   294,
     295,   296,   297,   298,   299,   300,   303,   307,   309,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   328,   330,   331,   335,   338,   339,   340,   341,   342,
     343,   344,   348,   351,   353,   354,   355,   356,   363,   365,
     366,   367,   369,   370,   372,   374,   375,   376,   377,   378,
     379,   380,   381,   382,   384,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   396,   398,   407,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   430,   431,   432,   433,   434,   435,   437,   438,
     439,   440,   441,   442,   443,   444,   450,   451,   452,   453,
     457,   459,   460, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087,   159,   -59,    18,    -4,    63, -1087,    58,    97,   122,
     100,   100,   471, -1087,   -52,   -52,   -52,    62,    62,    15,
     -52,   -52,   -52,   519,   173,  -153,    71,  -153,  -153,    71,
      71,    71,    71,    71,    71,    71,    36,    36,  -153,    36,
      36,    36,    36,  -139,  -139,    36,    36,    36,    36,    36,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
     -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,    69,    69,
      69,    69,    69,    69,    69,    69,    71,    71,    71,    71,
      71,    71,  -139,  -139,  -139,  -139,  -139,  -139,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,   -68,   -68,
     -68,   -68,    71,    71,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,    16,    16,    40,    40,   -68,    16,    16,
      16,    40,    71,    69,    71,    69,    71,    69,    71,    69,
      71,    16,   110,    16,   110,   191,   191,   191,   191,   191,
     191,    40,  -139,    16,   191,    71,    71,    71,    71,    16,
      16,    16,    16,    16,    16,    16,  -153,   110,    16,    40,
    -153,   110,    16,    40,    16,    16,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    40,   -68,  -153,   110,
      16,    40,    71,    16,  -153,    69,    69,    16,    71,    16,
     191,   191,   364,   553,   -12,   -12, -1087,  -102, -1087,   455,
   -1087, -1087, -1087,  -164, -1087,   466, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087,   464,   467,   468,    80,   465,   670,   472,
     473,   475,   480,   484,   486,   487,   488,   489,   491,   232,
     -52, -1087, -1087,    34,   490, -1087,   470,   493, -1087,   492,
   -1087,   494,   498,   495,   496,   504,   507,   508,   513,   514,
   -1087, -1087,   500,   517,   516, -1087,   518,   520,   522,   527,
     528,   529, -1087, -1087,   -89,   530, -1087,   531,   537,   538,
     539,   540,   541,   521,   544, -1087,   543, -1087,   545,   546,
     547,   548,   549,   550,   551,   552,   554,   555,   557,   558,
     559,   560,   561,   562,   563,   564,   565, -1087, -1087,   -64,
     566, -1087,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   607,
     608,   680,   616,   609,   611,   612,   613,   615,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   628, -1087, -1087,
     -47,   634, -1087,   635, -1087, -1087,   -68,   636,   637,   633,
     638,   645,   639,   640,   646,   647,   648,   649,   650,   660,
     661,   662,   663,   664, -1087, -1087,   -43,   665, -1087,   667,
     668,   671,   672,   673, -1087,   674,   675,   676,   677,   678,
     641,   679,   681,   682,   683,   684,   688,   689,   699,   700,
     701,   702,   703,   705,   706,   642,   685,   712,   716,   717,
     718,   719,   720,   721,   722,   723,   724,   725,   726,   734,
     735,   736,   737,   738,   739,   740,   741,   742,   743,   744,
     745,   746,   747,   748,   749,   750,   751,   752,   754,   756,
     757, -1087, -1087,   -67,   761, -1087,   867, -1087,   329,   276,
     765,   762,   763,   766, -1087, -1087, -1087, -1087, -1087,   769,
     771,   229, -1087, -1087,   911,   911,   121,   191,   105,   693,
     770,   772,   773,    35,    15, -1087,    62,   556,   729,   730,
   -1087,   -52,    36,    71,    69,   768,   774, -1087, -1087,    46,
      36,   728,   781,   175,    36, -1087,   -31,  -139,    40,  -153,
     110,    16,    40,   782,   783,    71,    36,  -153,    36,    36,
      36,    36, -1087, -1087,    78,  -153,  -153,    36,    36,    36,
      36,    36,   784,   785,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,   779,   780, -1087, -1087, -1087,    96,
     110,   110,   110,   110,   110,   110,   110,   110,    69,    69,
      69,    69,    69,    69,    69,    69,    71,    71,    71,    71,
      71,    71,    16,    16,    16,    16,    16,    16,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    69,   788,   789,
     790, -1087,  -197,    71,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68, -1087, -1087,
     123, -1087, -1087, -1087,   148, -1087, -1087,   -68,    16,    16,
   -1087, -1087,    16,   110,   110,   110,    16,   110,    16,   110,
      16,    71, -1087, -1087,   150,    71,    71,    71,   791,   792,
      16,    40,    16,    40,    16,    40, -1087,    16,    16,    16,
    -153,   110,    16,    40,    71,    71,    71,    71,    71,    71,
      71, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,    16,
      16,    16,    16,    16,  -139,  -139,  -139,  -139,  -139,    40,
      16,    40,  -153,    36,    69,    71,   -68,    16,   -68,  -153,
     105,   -31,   -68,    40,   793,   191,   191,   364,   794,   795,
     796, -1087,   797, -1087,   786, -1087,   364,   798,   799,   800,
     364, -1087,   142,   801,   802, -1087, -1087, -1087, -1087,    15,
     732,   803,   804, -1087,   868,   805,   806, -1087, -1087, -1087,
   -1087,   808, -1087, -1087, -1087,   997,   -68, -1087,    36,   811,
     812,   813, -1087, -1087,   214,   807, -1087,   815,   814,   816,
     817,   818,   819,   820,   821,   823,   824,   829,   825,   831,
     832,   828,   834,   830, -1087,   191,   833,   836,   837,   838,
     839,   840,   841,   843,   844,   842,   845,   849,   851,   852,
     853,   854,   855,   856,   857,   859,   860,   861,   862,   863,
     864,   865,   866,   869,   870,   810,   822, -1087,   105,   871,
     872,   873,   874,   875,   876,   877,   878,   884,   880,   881,
     882,   890,   886,   887,   888,   894,   891,   895,   892,   898,
     896,   897,   900,   901,   902,   903,   905,   899,   906,   907,
     908,   909,   915,   912,   913,   914,   916,   917,   921, -1087,
     848, -1087,   920,   932,   926,   933,   939,   936,   937,   943,
     944,   953,   949,   955,   951,   952,   954, -1087,    71, -1087,
     -68,   958,   960,   961,   963,   969,   970,   972,   973,   974,
     975,   976,   978,   979, -1087,    69,   980,   981,   983,   977,
     985,   986,   987,   988,   990,   991,   993,   996,   998,  1000,
    1003,  1004,  1005,  1006,  1002,  1007,  1008,  1009,  1010,  1011,
    1013,  1015,  1017,  1018,  1019,  1020,  1021,  1023,  1031,  1032,
    1033,  1034,  1035,  1036,  1039,  1045,  1048,  1049,  1050,  1051,
    1052,  1053,  1055,  1056,  1058,  1059,   999,  1060,  1061,  1068,
    1065,  1066, -1087, -1087, -1087, -1087,  1067,  1070,   904,  1073,
   -1087,   984,  1054,   994,  1079,   835, -1087, -1087, -1087,  1080,
    1001,   827,   -68,    75, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087,   168,    36, -1087,    69,    71,   -68,    36,    69,    71,
     -68, -1087, -1087, -1087,    36, -1087, -1087,    36, -1087,    36,
   -1087,    71,   191, -1087,    36, -1087,    36,    36, -1087, -1087,
   -1087,    69, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087,    36, -1087,    36,
    1074,  1076, -1087,   105,   105,   105,   105,   105,   105,   105,
     105, -1087,    36,    69,    69, -1087,    36,    69,    69, -1087,
      71, -1087,    36, -1087,    36,   191,   191,   191,   191,   191,
     191, -1087,    36,    71,    71,    71, -1087,    36,    71,    71,
   -1087, -1087, -1087, -1087, -1087,   -68, -1087,    36, -1087,    36,
     -68, -1087, -1087, -1087,    36, -1087,    36,   -68,   -68, -1087,
   -1087, -1087, -1087, -1087,   -68, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087,  1085, -1087,  1086,  1087,  1092, -1087, -1087,
     191,   -68,   191,   -68,   191,   -68,  -139,  -139,  -139,    36,
      69,    71,   -68, -1087,    71,    71,    71,    71,    71,    71,
      16,    16,    16,    16,    16,    16,    16,    16,  -139,  -139,
    1094,  1095,  1101,  1103, -1087, -1087, -1087, -1087, -1087,   -68,
      36,   105,   105,   -68,  -139,  1104,    16,    40, -1087, -1087,
   -1087, -1087, -1087,  1063,   184, -1087, -1087,  1098,   364,  1099,
    1100,   910, -1087,   113, -1087, -1087,   120,  1072,  1105,  1106,
    1108, -1087,   121,  1102,  1110,  1111,  1112,  1113,  1114,  1115,
    1116,  1117,  1118,  1120,  1124,  1125,  1128,  1129,  1130,  1131,
    1132,  1133, -1087, -1087,  1134,  1135,  1136,  1137,  1138,  1139,
    1141,  1140,  1143,  1146,  1147,  1149,  1153,  1154,  1155,  1156,
    1157,  1158,  1159,  1160,  1161,  1162,  1163,  1165,  1167,  1169,
    1170,  1171,  1172,  1173,  1174,  1175,  1176,  1177,  1178,  1180,
    1188,  1190,  1191,  1246,  1247,  1296,  1326,  1192,  1193,  1194,
    1195,  1196,  1197,  1198,  1199,  1200,  1201,  1202,  1207,  1208,
    1205,  1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,  1226,
    1232,  1228,  1234,  1235,  1231,  1233,  1328,  1330,  1350,  1352,
    1255,  1237,  1239,  1256,  1257,  1259,  1265,  1266,  1267,  1203,
    1276,   904,  1206,  1277, -1087, -1087, -1087,   206,  1179,  1278,
   -1087, -1087, -1087,  1362,  1279,  1280,  1281,    15,   -52,   -52,
     -52, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087,    36, -1087,    36, -1087,    36, -1087,    36, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,    36,
   -1087,    36, -1087,    36, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
    1227,  1282,  1287,  1289, -1087, -1087, -1087, -1087, -1087, -1087,
    1290,  1291, -1087,  1292,  1293,  1294,  1295, -1087, -1087, -1087,
   -1087, -1087, -1087,    16,    16,    16,    16, -1087,  -139, -1087,
   -1087,  -139,  -139,  1297,  1298,  1301,  1304,  1306, -1087, -1087,
     105,  1308,    71, -1087, -1087, -1087, -1087, -1087, -1087,  1389,
     195, -1087,  1400, -1087, -1087, -1087,    15,  1229,    15,   -52,
     -52,   -52,  1305,  1303,  1307,  1309,  1310,  1312,  1313,  1314,
    1315,  1316,  1317,  1318,  1319,  1320,  1321,  1415,  1498,  1499,
    1513,  1515,  1517,  1331,  1333,  1337,  1339,  1340,  1341,  1342,
    1323,  1325,  1338,  1344,  1536,  1346,  1538,  1343,  1354,  1355,
    1356,    15, -1087, -1087,  1353,  1357,  1358,  1359,   -52,   175,
    -139,   -31, -1087, -1087, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087, -1087, -1087,  1360,  1361,  1366,  1367,  1368,  1369, -1087,
   -1087, -1087, -1087, -1087, -1087, -1087,  1370,  1371,  1372, -1087,
    1373, -1087,  1374,  1375, -1087, -1087,  1549, -1087,   -52,  -153,
      16,   110,  1376, -1087, -1087, -1087,  1377,  1379,  1380,  1381,
    1382,  1383,  1563,  1564,  1565,  1384,  1387,  1566,  1392,  1388,
   -1087, -1087, -1087,    40, -1087, -1087, -1087, -1087, -1087, -1087,
    1393,  1395,  1396, -1087, -1087,  1397, -1087,    40, -1087,  1394,
    1398,  1399,  1390, -1087, -1087, -1087, -1087,  1401,  1567,  1404,
    1402, -1087
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
   -1087, -1087,    79,    -3, -1087, -1087, -1087, -1087, -1087, -1087,
   -1087,  -336, -1087, -1087,    23, -1087, -1087,   -44,  -341, -1087,
   -1087, -1087,     2,    -2,   536,     4, -1086,  -121,  -811,  -801,
   -1087, -1087,  -356, -1087, -1087,  -146,   -63,  -214,  -371, -1087,
   -1087,  -306, -1087, -1087,  -756,  1069,  -459,  -377, -1087, -1087,
    -461, -1087, -1087,   474,   692, -1087,  -438, -1087,  -778, -1087,
    1062, -1087,  1322, -1087,  -538, -1087, -1087, -1087, -1087, -1087,
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
     555,   337,   597,   730,   566,   567,   568,  1190,   708,  1191,
    1052,  1054,     5,   713,   642,   643,   644,   645,   646,   647,
     648,     3,     4,     5,   113,   109,   756,   338,   339,   114,
     760,   334,  1073,   740,   336,   590,   591,   590,   591,   571,
     572,   663,   664,   665,   666,   667,   668,   332,   778,   573,
     333,   758,  1068,   602,   603,   762,   556,     3,     4,     5,
     557,   558,     9,   604,   340,   805,   805,   341,   775,  1506,
       3,     4,     5,   780,  1507,     3,     4,     5,   342,   819,
     343,     1,     2,     3,     4,     5,     6,     7,   808,   809,
     810,     8,     9,     1,     2,     3,     4,     5,     6,     7,
     344,   741,   354,   731,   732,   345,   578,  1627,     3,     4,
       5,   349,  1628,   346,   862,     3,     4,     5,   347,  1633,
       8,     9,   590,   591,   679,   680,   348,   681,   894,   895,
     755,  1047,   615,   353,   759,  1048,   541,   682,   703,   896,
     551,   552,   710,   711,   712,   576,   577,   350,   578,   613,
     614,   351,   777,   615,   352,   723,   958,   729,   783,   355,
     982,   637,   638,   356,   534,   535,   536,   742,   537,   357,
     898,   639,   358,   748,   749,   750,   751,   752,   753,   754,
     802,   803,   757,   578,   615,   359,   761,   360,   763,   764,
     765,   766,   767,   768,   769,   770,   771,   772,   773,   774,
     543,     3,     4,     5,   779,  1752,   361,   782,   698,   699,
      10,   786,   362,   788,   542,   590,   591,   363,   700,   364,
      12,    10,    11,   365,   836,   366,   592,   593,   592,   593,
    1074,    12,   704,   705,   534,   535,   596,   837,   598,   599,
     600,   601,   706,   367,   608,   609,   610,   611,   612,  1087,
    1088,   734,   734,   734,   734,   734,   734,    10,    11,  1279,
     734,   613,   614,   576,   577,   615,   578,    12,  1285,   544,
      10,    11,  1289,  1066,  1272,    10,    11,   791,   792,   368,
      12,  1114,  1115,    10,    11,    12,   583,   584,   585,   586,
     587,   588,   589,    12,   546,    10,    11,   894,   895,  1147,
    1148,   615,   724,   725,   369,    12,   734,   734,    10,    11,
     804,   804,   726,  1063,  1064,    10,    11,   370,    12,   547,
     735,   736,   737,   738,   739,    12,  1207,  1208,   743,   550,
     791,   792,  1290,  1291,  1292,   562,   562,   565,   371,   561,
     561,   563,   563,   657,   658,   659,   660,   661,   662,   898,
     545,  1209,  1210,  1224,  1225,   669,   670,   671,   672,   673,
     674,   675,   676,   677,   678,   791,   792,  1092,  1093,   687,
     688,  1511,  1512,   570,   789,   790,   372,  1094,   373,  1102,
     734,   374,  1362,   731,   732,   375,   578,  1620,  1621,   714,
     376,   716,   377,   718,   378,   720,   379,   722,  1799,  1800,
    1100,    10,    11,   380,  1104,   381,  1063,  1064,   382,   548,
     549,    12,   744,   745,   746,   747,  1641,  1309,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   835,   392,  1149,
    1150,  1151,  1152,  1153,  1154,  1155,  1156,   393,   394,   395,
     396,   397,   838,   398,   399,   400,   401,   402,   863,   781,
     403,   404,   405,   406,   407,   787,   408,   409,   410,  1098,
     411,   412,   413,   414,   415,   416,  1099,   417,   793,   794,
     795,   796,   797,   418,     8,  1077,   419,   420,   798,   421,
     422,   799,  1053,  1101,   423,  1081,   424,   425,   426,   427,
     428,  1109,   429,   430,   431,   432,   433,   434,   435,  1116,
    1117,   436,  1215,  1216,  1217,   437,  1219,   438,  1221,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   793,   794,   795,   796,   797,   451,   569,   452,   453,
    1241,   798,  1051,   454,   799,  1103,   455,   456,   457,   458,
     459,   460,   461,  1232,   821,  1234,   462,  1236,   820,   463,
     822,   464,   465,   466,   467,  1243,   793,   794,   795,   796,
     797,   468,   537,   469,   470,   471,   798,   472,   473,   799,
     474,   898,   475,   476,   477,   478,   479,   480,   481,   482,
     483,  1261,   484,  1263,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   734,   494,  1275,   495,  1534,  1535,  1536,
    1537,  1538,  1539,  1540,  1541,   496,  1171,  1172,  1173,  1174,
    1175,  1176,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   959,   512,   513,
     514,   515,   516,   517,  1240,   518,   519,   520,   521,   522,
     523,   524,   525,  1256,  1257,  1258,  1259,  1260,   526,   527,
     528,   529,  1212,  1213,  1273,   530,  1214,   531,   532,   811,
    1218,  1067,  1220,   813,  1222,   816,  1264,   823,   817,   818,
     824,   825,   841,  1271,  1231,   827,  1233,   826,  1235,   898,
     828,  1237,  1238,  1239,   829,   830,  1242,   831,   940,   832,
     833,  1066,   834,  1069,   840,   842,   843,   845,   844,   846,
     847,  1082,   853,  1251,  1252,  1253,  1254,  1255,   848,  1089,
    1623,   849,   850,  1097,  1262,  1612,  1613,   851,   852,   854,
     855,  1269,   856,   872,   857,  1108,   858,  1110,  1111,  1112,
    1113,   859,   860,   861,   865,   866,  1118,  1119,  1120,  1121,
    1122,   867,   868,   869,   870,   871,   873,   874,  1078,   875,
     876,   877,   878,   879,   880,   881,   882,  1061,   883,   884,
    1083,   885,   886,   887,   888,   889,   890,   891,   892,   893,
     900,   901,   902,   903,   904,   905,   906,   907,   908,   909,
     910,   911,  1107,   912,   913,   914,   915,   916,   917,   918,
     919,   920,   921,   922,   923,   924,   925,   926,   927,   928,
     929,   930,   931,   932,   933,   934,   935,   936,   937,   938,
     939,   941,  1076,   943,   562,   944,   945,   946,   561,   947,
     563,   734,   734,   948,   949,   950,   951,   952,   953,   954,
     955,   956,   957,   961,   962,   965,   966,   967,   970,   971,
     996,  1011,   968,  1165,  1166,  1167,  1168,  1169,  1170,   969,
     972,   973,   974,   975,   976,  1177,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,  1185,   977,   978,   979,   980,   981,   985,
    1192,   986,   987,   988,   989,  1050,  1299,   990,   991,   992,
     993,   994,   995,   997,  1012,   998,   999,  1000,  1001,  1277,
    1278,   734,  1002,  1003,   898,   898,   898,   898,   898,   898,
     898,   898,  1265,  1004,  1005,  1006,  1007,  1008,  1223,  1009,
    1010,  1013,  1226,  1227,  1228,  1014,  1015,  1016,  1017,  1018,
    1062,  1079,  1080,  1090,  1296,  1019,  1020,  1021,  1022,  1023,
    1024,  1244,  1245,  1246,  1247,  1248,  1249,  1250,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,
    1037,  1038,  1039,  1040,  1041,  1042,  1043,  1305,  1044,  1330,
    1045,  1046,  1267,  1049,  1055,  1057,  1056,  1059,  1058,  1060,
    1070,  1085,  1071,  1072,  1795,  1086,  1091,  1105,  1106,  1123,
    1124,  1145,  1146,  1187,  1188,  1189,  1229,  1230,  1276,  1280,
    1281,  1282,  1284,  1286,  1287,  1297,  1298,  1303,  1853,   807,
    1283,  1503,  1288,  1293,  1294,  1360,  1301,  1485,  1300,  1302,
    1306,  1312,   898,   898,  1313,  1307,  1308,  1361,  1314,  1504,
    1315,  1316,  1317,  1318,  1319,  1320,  1321,  1322,  1323,  1324,
    1325,  1326,  1327,  1328,  1329,  1501,  1333,  1331,  1335,  1618,
    1332,  1340,  1334,  1403,  1336,  1337,  1338,  1339,  1342,  1341,
    1343,  1344,  1345,  1346,  1347,  1348,  1349,  1295,  1350,  1351,
    1352,  1353,  1354,  1355,  1356,  1583,  1584,  1585,  1358,   812,
    1357,  1619,  1637,  1748,  1359,  1363,  1364,  1365,  1366,  1367,
    1368,  1369,  1370,  1371,  1372,  1373,  1374,  1604,  1605,  1375,
    1376,  1377,  1378,  1379,  1381,  1380,  1382,  1383,  1391,  1493,
    1384,  1385,  1626,  1615,  1386,  1387,  1388,  1389,   734,  1390,
    1392,  1393,  1394,  1395,  1396,  1400,  1397,  1398,  1399,  1404,
    1401,   684,   685,   686,  1402,  1406,   689,   690,   691,   692,
     693,   694,   695,   696,   697,  1419,  1405,  1407,  1408,   709,
    1409,  1410,  1411,  1412,  1596,  1597,  1598,  1599,  1600,  1601,
    1602,  1603,  1413,  1414,  1415,  1416,  1417,  1421,  1418,  1422,
    1423,   734,   734,   734,   734,   734,   734,  1424,  1425,  1426,
    1617,  1427,  1428,  1429,  1430,  1431,  1525,  1432,     0,  1756,
    1438,  1513,  1497,  1433,  1435,  1436,  1517,  1437,  1439,  1499,
    1440,  1441,  1442,  1521,  1443,  1444,  1522,  1445,  1523,   776,
    1446,  1453,  1447,  1526,  1448,  1527,  1528,  1449,  1450,  1451,
    1452,  1454,  1455,  1456,  1457,  1458,   734,  1459,   734,  1460,
     734,  1461,  1462,  1463,  1464,  1465,  1530,  1466,  1531,  1551,
    1552,  1553,  1554,  1555,  1556,  1467,  1468,  1469,  1470,  1471,
    1472,  1542,  1515,  1473,  1474,  1545,  1519,  1475,  1476,  1477,
    1478,  1549,  1498,  1550,  1700,  1701,  1479,  1480,  1524,  1481,
    1482,  1557,  1483,  1484,  1486,  1487,  1561,  1488,  1489,  1490,
    1491,   898,  1496,  1492,  1500,  1502,  1565,  1532,  1566,  1533,
    1573,  1574,  1575,  1568,  1577,  1569,  1579,  1576,  1581,  1606,
    1607,  1509,  1763,  1764,  1765,  1508,  1608,  1510,  1609,  1616,
    1622,  1642,  1624,  1625,  1702,  1638,  1639,  1548,  1640,  1643,
    1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1586,  1652,
    1558,  1559,  1560,  1653,  1654,  1562,  1563,  1655,  1656,  1657,
    1658,  1659,  1660,  1661,  1703,  1663,  1733,  1665,  1734,  1662,
    1667,  1664,  1669,  1666,  1668,  1670,  1671,  1787,  1672,  1611,
    1788,  1789,  1673,  1674,  1675,  1676,  1677,  1678,  1735,  1680,
    1736,  1682,  1758,  1679,  1684,  1681,  1685,  1683,  1686,  1687,
    1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1588,  1696,
    1872,  1590,  1591,  1592,  1593,  1594,  1595,  1697,   963,  1698,
    1699,  1704,  1705,  1706,  1707,  1708,  1709,  1798,  1746,  1712,
    1801,  1749,  1710,  1711,  1717,  1713,  1714,  1783,  1784,  1785,
    1786,  1715,  1716,  1805,  1806,  1807,  1718,  1719,  1720,  1721,
    1722,  1803,  1773,  1823,  1855,  1888,  1723,  1724,  1725,  1854,
    1726,  1727,  1728,  1729,  1730,  1731,  1738,  1732,  1739,  1893,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   627,
     628,   629,   630,   631,   632,   633,   634,   635,   636,  1737,
    1740,  1741,  1852,  1742,  1743,  1744,  1745,   649,   650,   651,
     652,   653,   654,   655,   656,  1747,  1751,  1774,  1757,  1759,
    1760,  1761,  1775,  1870,  1776,  1777,  1778,  1779,  1780,  1781,
    1782,  1631,  1790,  1791,  1635,  1630,  1792,  1632,  1634,  1793,
    1636,  1794,  1869,  1796,  1809,  1808,  1824,  1825,  1810,  1812,
    1811,  1813,  1814,  1815,  1816,  1817,  1818,  1819,  1820,  1821,
    1822,  1826,   715,  1827,   717,  1828,   719,  1836,   721,  1837,
    1829,  1766,  1830,  1767,  1871,  1768,  1831,  1769,  1832,  1833,
    1834,  1835,  1838,  1839,  1840,  1841,  1842,  1843,  1770,  1844,
    1771,  1846,  1772,  1848,  1845,  1856,  1857,  1868,  1849,  1850,
    1851,  1858,  1859,  1860,  1861,  1862,  1863,  1864,  1865,  1866,
    1867,  1880,  1881,  1882,  1885,  1899,  1874,  1873,  1875,  1876,
    1877,  1878,  1879,  1883,   784,   785,  1884,  1886,  1889,  1887,
    1890,  1891,  1892,  1894,  1897,     0,  1898,  1895,  1896,  1900,
       0,  1901,     0,     0,   815,   533,     0,     0,     0,     0,
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
       0,     0,  1543,  1544,     0,     0,  1546,  1547,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,  1587,
       0,   186,   187,   188,   189,   190,   191,   192,   193,   194,
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
     346,    14,   368,   474,   350,   351,   352,   214,   456,   216,
     798,   799,     7,   461,   401,   402,   403,   404,   405,   406,
     407,     5,     6,     7,   212,     9,   497,    14,    15,    10,
     501,   205,     7,   481,     0,    11,    12,    11,    12,   202,
     203,   422,   423,   424,   425,   426,   427,    18,   519,   212,
      18,   499,   818,   202,   203,   503,     4,     5,     6,     7,
       8,     9,    14,   212,   207,   534,   535,   207,   516,     4,
       5,     6,     7,   521,     9,     5,     6,     7,   207,     9,
     207,     3,     4,     5,     6,     7,     8,     9,   200,   201,
     202,    13,    14,     3,     4,     5,     6,     7,     8,     9,
     210,   482,   114,   202,   203,   210,   205,     4,     5,     6,
       7,    10,     9,   210,   213,     5,     6,     7,   208,     9,
      13,    14,    11,    12,   202,   203,   208,   205,   202,   203,
     496,   208,   206,   205,   500,   212,   205,   215,   454,   213,
     202,   203,   458,   459,   460,   202,   203,   210,   205,   202,
     203,   210,   518,   206,   210,   471,   213,   473,   524,   208,
     213,   202,   203,   208,    15,    16,    17,   483,    19,   208,
     639,   212,   208,   489,   490,   491,   492,   493,   494,   495,
     202,   203,   498,   205,   206,   208,   502,   208,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     214,     5,     6,     7,   520,     9,   208,   523,   202,   203,
     205,   527,   208,   529,   206,    11,    12,   208,   212,   208,
     215,   205,   206,   208,   570,   208,   202,   203,   202,   203,
     205,   215,   202,   203,    15,    16,   367,   213,   369,   370,
     371,   372,   212,   208,   375,   376,   377,   378,   379,   213,
     214,   475,   476,   477,   478,   479,   480,   205,   206,  1047,
     484,   202,   203,   202,   203,   206,   205,   215,  1056,   216,
     205,   206,  1060,  1094,  1040,   205,   206,    11,    12,   208,
     215,   213,   214,   205,   206,   215,   359,   360,   361,   362,
     363,   364,   365,   215,   207,   205,   206,   202,   203,   213,
     214,   206,   202,   203,   208,   215,   530,   531,   205,   206,
     534,   535,   212,   202,   203,   205,   206,   208,   215,   207,
     476,   477,   478,   479,   480,   215,   213,   214,   484,   342,
      11,    12,   200,   201,   202,   347,   348,   349,   208,   347,
     348,   347,   348,   416,   417,   418,   419,   420,   421,   818,
     337,   213,   214,   213,   214,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,    11,    12,   202,   203,   442,
     443,   213,   214,   210,   530,   531,   208,   212,   208,   850,
     604,   208,  1148,   202,   203,   208,   205,   213,   214,   462,
     208,   464,   208,   466,   208,   468,   208,   470,   213,   214,
     848,   205,   206,   208,   852,   208,   202,   203,   208,   340,
     341,   215,   485,   486,   487,   488,  1512,   213,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   205,   208,   900,
     901,   902,   903,   904,   905,   906,   907,   208,   208,   208,
     208,   208,   573,   208,   208,   208,   208,   208,   604,   522,
     208,   208,   208,   208,   208,   528,   208,   208,   208,   846,
     208,   208,   208,   208,   208,   208,   847,   208,   202,   203,
     204,   205,   206,   208,    13,   826,   208,   208,   212,   208,
     208,   215,   216,   849,   208,   831,   208,   208,   208,   208,
     208,   857,   208,   208,   208,   208,   208,   208,   208,   865,
     866,   208,   973,   974,   975,   208,   977,   208,   979,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   202,   203,   204,   205,   206,   208,    18,   208,   208,
    1001,   212,   213,   208,   215,   851,   208,   208,   208,   208,
     208,   208,   208,   991,   556,   993,   208,   995,   556,   208,
     556,   208,   208,   208,   208,  1003,   202,   203,   204,   205,
     206,   208,    19,   208,   208,   208,   212,   208,   208,   215,
     208,  1040,   208,   208,   208,   208,   208,   208,   208,   208,
     208,  1029,   208,  1031,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   817,   208,  1043,   208,  1363,  1364,  1365,
    1366,  1367,  1368,  1369,  1370,   208,   922,   923,   924,   925,
     926,   927,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   700,   208,   208,
     208,   208,   208,   208,  1000,   208,   208,   208,   208,   208,
     208,   208,   208,  1024,  1025,  1026,  1027,  1028,   208,   208,
     208,   208,   968,   969,  1041,   208,   972,   208,   208,   214,
     976,   817,   978,   207,   980,   211,  1032,   212,   211,   211,
      10,   209,   212,  1039,   990,   210,   992,   214,   994,  1148,
     210,   997,   998,   999,   210,   209,  1002,   210,    18,   211,
     211,  1512,   211,    10,   214,   212,   214,   209,   214,   214,
     214,   832,   212,  1019,  1020,  1021,  1022,  1023,   214,   840,
    1498,   214,   214,   844,  1030,  1481,  1482,   214,   214,   212,
     214,  1037,   214,   212,   214,   856,   214,   858,   859,   860,
     861,   214,   214,   214,   214,   214,   867,   868,   869,   870,
     871,   214,   214,   214,   214,   214,   212,   214,   202,   214,
     214,   214,   214,   214,   214,   214,   214,   811,   214,   214,
     833,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   855,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   212,
     212,   205,   824,   214,   826,   214,   214,   214,   826,   214,
     826,  1045,  1046,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   209,   209,   209,   209,   214,   209,   209,
     209,   209,   214,   916,   917,   918,   919,   920,   921,   214,
     214,   214,   214,   214,   214,   928,   929,   930,   931,   932,
     933,   934,   935,   936,   214,   214,   214,   214,   214,   214,
     943,   214,   214,   212,   212,    18,    18,   214,   214,   214,
     214,   214,   214,   214,   209,   214,   214,   214,   214,  1045,
    1046,  1115,   214,   214,  1363,  1364,  1365,  1366,  1367,  1368,
    1369,  1370,  1033,   214,   214,   214,   214,   214,   981,   214,
     214,   209,   985,   986,   987,   209,   209,   209,   209,   209,
      19,   202,   202,   205,   202,   214,   214,   214,   214,   214,
     214,  1004,  1005,  1006,  1007,  1008,  1009,  1010,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,  1088,   214,  1115,
     214,   214,  1035,   212,   209,   212,   214,   208,   212,   208,
     210,   213,   210,   210,  1740,   211,   205,   205,   205,   205,
     205,   212,   212,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   216,   205,   205,   202,   202,    10,  1809,   535,
     213,    10,   212,   212,   212,   205,   210,    18,   213,   211,
     209,   214,  1481,  1482,   209,   213,   213,   205,   214,   202,
     214,   214,   214,   214,   214,   214,   213,   213,   209,   214,
     209,   209,   214,   209,   214,   210,   209,   214,   209,  1487,
     214,   209,   214,   205,   214,   214,   213,   213,   209,   214,
     209,   209,   209,   209,   209,   209,   209,  1069,   209,   209,
     209,   209,   209,   209,   209,  1446,  1447,  1448,   209,   543,
     214,    18,    10,  1621,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   209,   214,   214,   214,  1468,  1469,   209,
     214,   214,   214,   209,   209,   214,   214,   209,   209,   205,
     214,   214,   202,  1484,   214,   214,   214,   214,  1332,   214,
     214,   214,   214,   214,   209,   209,   214,   214,   214,   209,
     213,   439,   440,   441,   213,   209,   444,   445,   446,   447,
     448,   449,   450,   451,   452,  1208,   214,   214,   209,   457,
     214,   214,   209,   209,  1460,  1461,  1462,  1463,  1464,  1465,
    1466,  1467,   209,   214,   209,   214,   214,   209,   214,   209,
     209,  1385,  1386,  1387,  1388,  1389,  1390,   214,   209,   209,
    1486,   209,   209,   209,   209,   209,  1332,   209,    -1,    10,
     213,  1312,   208,   214,   214,   214,  1317,   214,   213,   205,
     214,   214,   214,  1324,   214,   214,  1327,   214,  1329,   517,
     214,   209,   214,  1334,   214,  1336,  1337,   214,   214,   214,
     214,   214,   214,   214,   214,   214,  1440,   214,  1442,   214,
    1444,   214,   214,   214,   214,   214,  1357,   214,  1359,  1385,
    1386,  1387,  1388,  1389,  1390,   214,   214,   214,   214,   214,
     214,  1372,  1315,   214,   209,  1376,  1319,   209,   209,   209,
     209,  1382,   208,  1384,    18,    18,   214,   214,  1331,   214,
     214,  1392,   214,   214,   214,   214,  1397,   209,   213,   213,
     213,  1740,   209,   213,   205,   205,  1407,   213,  1409,   213,
     205,   205,   205,  1414,  1440,  1416,  1442,   205,  1444,   205,
     205,  1303,  1638,  1639,  1640,  1303,   205,  1303,   205,   205,
     212,   209,   213,   213,    18,   210,   210,  1380,   210,   209,
     209,   209,   209,   209,   209,   209,   209,   209,  1449,   209,
    1393,  1394,  1395,   209,   209,  1398,  1399,   209,   209,   209,
     209,   209,   209,   209,    18,   209,    18,   209,    18,   214,
     209,   214,   209,   214,   214,   209,   209,  1728,   209,  1480,
    1731,  1732,   209,   209,   209,   209,   209,   209,    18,   209,
      18,   209,    10,   214,   209,   214,   209,   214,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,  1451,   209,
    1851,  1454,  1455,  1456,  1457,  1458,  1459,   209,   706,   209,
     209,   209,   209,   209,   209,   209,   209,    18,   205,   209,
      10,   205,   214,   214,   209,   214,   214,  1723,  1724,  1725,
    1726,   214,   214,  1759,  1760,  1761,   209,   209,   209,   209,
     209,   202,   205,    18,  1811,  1873,   214,   214,   214,  1810,
     214,   209,   214,   209,   209,   214,   209,   214,   209,  1887,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   394,   395,   396,   397,   398,   399,   214,
     214,   214,  1808,   214,   209,   209,   209,   408,   409,   410,
     411,   412,   413,   414,   415,   209,   209,   205,   210,   210,
     210,   210,   205,  1849,   205,   205,   205,   205,   205,   205,
     205,  1503,   205,   205,  1506,  1503,   205,  1503,  1506,   205,
    1506,   205,  1848,   205,   211,   210,    18,    18,   211,   209,
     211,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,    18,   463,    18,   465,    18,   467,   214,   469,   214,
     209,  1662,   209,  1664,  1850,  1666,   209,  1668,   209,   209,
     209,   209,   214,   209,    18,   209,    18,   214,  1679,   205,
    1681,   205,  1683,   210,   209,   205,   205,    18,   211,   211,
     211,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,    18,    18,    18,    18,    18,   209,   211,   209,   209,
     209,   209,   209,   209,   525,   526,   209,   205,   205,   211,
     205,   205,   205,   209,   214,    -1,   205,   209,   209,   205,
      -1,   209,    -1,    -1,   552,   293,    -1,    -1,    -1,    -1,
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
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,    -1,
      -1,   202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,  1373,  1374,    -1,    -1,  1377,  1378,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,  1450,
      -1,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,    -1,    -1,   202
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    13,    14,
     205,   206,   215,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   229,   231,   239,   240,   242,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   202,   319,     9,
     239,   240,   242,   212,    10,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   202,   230,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   279,    18,    18,   205,   241,     0,   220,   231,   231,
     207,   207,   207,   207,   210,   210,   210,   208,   208,    10,
     210,   210,   210,   205,   240,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   208,   279,    15,    16,    17,    19,   232,   233,
     234,   205,   206,   214,   216,   231,   207,   207,   219,   219,
     220,   202,   203,   228,   228,   228,     4,     8,     9,   235,
     236,   239,   240,   242,   235,   240,   228,   228,   228,    18,
     210,   202,   203,   212,   249,   250,   202,   203,   205,   253,
     254,   249,   249,   253,   253,   253,   253,   253,   253,   253,
      11,    12,   202,   203,   244,   245,   244,   249,   244,   244,
     244,   244,   202,   203,   212,   255,   256,   255,   244,   244,
     244,   244,   244,   202,   203,   206,   262,   263,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   202,   203,   212,
     264,   265,   264,   264,   264,   264,   264,   264,   264,   262,
     262,   262,   262,   262,   262,   262,   262,   253,   253,   253,
     253,   253,   253,   255,   255,   255,   255,   255,   255,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   202,
     203,   205,   215,   271,   271,   271,   271,   253,   253,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   202,   203,
     212,   258,   259,   258,   202,   203,   212,   273,   273,   271,
     258,   258,   258,   273,   253,   262,   253,   262,   253,   262,
     253,   262,   253,   258,   202,   203,   212,   267,   268,   258,
     267,   202,   203,   252,   254,   252,   252,   252,   252,   252,
     273,   255,   258,   252,   253,   253,   253,   253,   258,   258,
     258,   258,   258,   258,   258,   249,   267,   258,   273,   249,
     267,   258,   273,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   273,   271,   249,   267,   258,
     273,   253,   258,   249,   262,   262,   258,   253,   258,   252,
     252,    11,    12,   202,   203,   204,   205,   206,   212,   215,
     275,   276,   202,   203,   254,   263,   270,   270,   200,   201,
     202,   214,   241,   207,   277,   277,   211,   211,   211,     9,
     239,   240,   242,   212,    10,   209,   214,   210,   210,   210,
     209,   210,   211,   211,   211,   205,   228,   213,   244,   251,
     214,   212,   212,   214,   214,   209,   214,   214,   214,   214,
     214,   214,   214,   212,   212,   214,   214,   214,   214,   214,
     214,   214,   213,   252,   257,   214,   214,   214,   214,   214,
     214,   214,   212,   212,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   202,   203,   213,   261,   263,   266,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   212,   212,
      18,   205,   272,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   213,   253,
     260,   209,   209,   271,   274,   209,   209,   214,   214,   214,
     209,   209,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   213,   262,   269,   214,   214,   214,   212,   212,
     214,   214,   214,   214,   214,   214,   209,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   209,   209,   209,   209,   209,   209,   209,   209,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   208,   212,   212,
      18,   213,   275,   216,   275,   209,   214,   212,   212,   208,
     208,   234,    19,   202,   203,   243,   245,   252,   261,    10,
     210,   210,   210,     7,   205,   237,   240,   235,   202,   202,
     202,   228,   244,   253,   262,   213,   211,   213,   214,   244,
     205,   205,   202,   203,   212,   246,   247,   244,   264,   255,
     273,   249,   267,   258,   273,   205,   205,   253,   244,   249,
     244,   244,   244,   244,   213,   214,   249,   249,   244,   244,
     244,   244,   244,   205,   205,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   212,   212,   213,   214,   267,
     267,   267,   267,   267,   267,   267,   267,   262,   262,   262,
     262,   262,   262,   262,   262,   253,   253,   253,   253,   253,
     253,   258,   258,   258,   258,   258,   258,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   262,   205,   205,   205,
     214,   216,   253,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   213,   214,   213,
     214,   271,   258,   258,   258,   267,   267,   267,   258,   267,
     258,   267,   258,   253,   213,   214,   253,   253,   253,   205,
     205,   258,   273,   258,   273,   258,   273,   258,   258,   258,
     249,   267,   258,   273,   253,   253,   253,   253,   253,   253,
     253,   258,   258,   258,   258,   258,   255,   255,   255,   255,
     255,   273,   258,   273,   249,   244,   262,   253,   271,   258,
     271,   249,   261,   264,   271,   273,   205,   252,   252,   275,
     205,   205,   205,   213,   216,   275,   205,   205,   212,   275,
     200,   201,   202,   212,   212,   240,   202,   202,   202,    18,
     213,   210,   211,    10,   271,   244,   209,   213,   213,   213,
     243,   248,   214,   209,   214,   214,   214,   214,   214,   214,
     214,   213,   213,   209,   214,   209,   209,   214,   209,   214,
     252,   214,   214,   209,   214,   209,   214,   214,   213,   213,
     209,   214,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   214,   209,   214,
     205,   205,   261,   214,   214,   214,   214,   214,   214,   214,
     214,   209,   214,   214,   214,   209,   214,   214,   214,   209,
     214,   209,   214,   209,   214,   214,   214,   214,   214,   214,
     214,   209,   214,   214,   214,   214,   209,   214,   214,   214,
     209,   213,   213,   205,   209,   214,   209,   214,   209,   214,
     214,   209,   209,   209,   214,   209,   214,   214,   214,   253,
     271,   209,   209,   209,   214,   209,   209,   209,   209,   209,
     209,   209,   209,   214,   262,   214,   214,   214,   213,   213,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   209,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   209,   209,   209,   209,   209,   214,
     214,   214,   214,   214,   214,    18,   214,   214,   209,   213,
     213,   213,   213,   205,   280,   281,   209,   208,   208,   205,
     205,   210,   205,    10,   202,   271,     4,     9,   239,   240,
     242,   213,   214,   244,   262,   253,   271,   244,   262,   253,
     271,   244,   244,   244,   253,   252,   244,   244,   244,   262,
     244,   244,   213,   213,   261,   261,   261,   261,   261,   261,
     261,   261,   244,   262,   262,   244,   262,   262,   253,   244,
     244,   252,   252,   252,   252,   252,   252,   244,   253,   253,
     253,   244,   253,   253,   271,   244,   244,   271,   244,   244,
     271,   271,   271,   205,   205,   205,   205,   252,   271,   252,
     271,   252,   271,   255,   255,   255,   244,   262,   253,   271,
     253,   253,   253,   253,   253,   253,   258,   258,   258,   258,
     258,   258,   258,   258,   255,   255,   205,   205,   205,   205,
     271,   244,   261,   261,   271,   255,   205,   258,   273,    18,
     213,   214,   212,   275,   213,   213,   202,     4,     9,   238,
     239,   240,   242,     9,   239,   240,   242,    10,   210,   210,
     210,   243,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   214,   209,   214,   209,   214,   209,   214,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   214,
     209,   214,   209,   214,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
      18,    18,    18,    18,   209,   209,   209,   209,   209,   209,
     214,   214,   209,   214,   214,   214,   214,   209,   209,   209,
     209,   209,   209,   214,   214,   214,   214,   209,   214,   209,
     209,   214,   214,    18,    18,    18,    18,   214,   209,   209,
     214,   214,   214,   209,   209,   209,   205,   209,   281,   205,
     278,   209,     9,   239,   240,   242,    10,   210,    10,   210,
     210,   210,   240,   228,   228,   228,   244,   244,   244,   244,
     244,   244,   244,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   258,   258,   258,   258,   255,   255,   255,
     205,   205,   205,   205,   205,   261,   205,   253,    18,   213,
     214,    10,   240,   202,   240,   228,   228,   228,   210,   211,
     211,   211,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,    18,    18,    18,    18,    18,    18,   209,
     209,   209,   209,   209,   209,   209,   214,   214,   214,   209,
      18,   209,    18,   214,   205,   209,   205,   240,   210,   211,
     211,   211,   228,   246,   255,   264,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,    18,   228,
     249,   258,   267,   211,   209,   209,   209,   209,   209,   209,
      18,    18,    18,   209,   209,    18,   205,   211,   273,   205,
     205,   205,   205,   273,   209,   209,   209,   214,   205,    18,
     205,   209
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   217,   218,   218,   218,   218,   218,   219,   219,   219,
     219,   220,   220,   221,   222,   222,   223,   223,   223,   223,
     224,   224,   224,   224,   225,   225,   225,   225,   226,   226,
     226,   226,   226,   226,   226,   226,   227,   227,   227,   227,
     227,   227,   227,   227,   228,   228,   229,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   231,   232,   232,
     233,   233,   234,   234,   235,   235,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   237,   237,   238,   238,   238,
     238,   238,   238,   238,   238,   239,   240,   240,   240,   241,
     241,   242,   242,   243,   243,   243,   243,   243,   244,   244,
     244,   244,   244,   245,   245,   246,   246,   246,   247,   247,
     248,   248,   249,   249,   249,   250,   250,   251,   251,   252,
     252,   252,   252,   252,   253,   253,   253,   253,   253,   254,
     255,   255,   255,   256,   256,   257,   257,   258,   258,   258,
     259,   259,   260,   260,   261,   261,   261,   261,   261,   262,
     262,   262,   262,   262,   263,   264,   264,   264,   265,   265,
     266,   266,   267,   267,   267,   268,   268,   269,   269,   270,
     270,   270,   270,   270,   270,   271,   271,   271,   271,   271,
     271,   272,   272,   272,   273,   273,   273,   274,   274,   274,
     275,   275,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   277,   277,   277,
     277,   277,   278,   278,   278,   279,   279,   279,   279,   279,
     280,   280,   280,   281,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     283,   283,   283,   284,   284,   285,   285,   286,   286,   287,
     288,   288,   289,   289,   290,   290,   291,   291,   292,   292,
     293,   293,   294,   294,   295,   295,   296,   296,   296,   297,
     297,   297,   298,   298,   298,   298,   299,   300,   300,   300,
     300,   300,   300,   301,   301,   301,   301,   302,   302,   302,
     302,   303,   303,   303,   303,   304,   305,   306,   306,   306,
     306,   307,   308,   308,   309,   310,   310,   310,   310,   311,
     312,   313,   314,   314,   315,   316,   317,   318,   318,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   319
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
          case 202: /* IDENT  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2720 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 203: /* UNDERSCORE_IDENT  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2726 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 204: /* STRING_LITERAL  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2732 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 205: /* INT_LITERAL  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2738 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 206: /* FLOAT_LITERAL  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2744 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 228: /* ident_anns  */
#line 343 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { MSAT_SFREE(((*yyvaluep).string)); }
#line 2750 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 239: /* bool_ti_expr_tail  */
#line 344 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).domain); }
#line 2756 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 240: /* int_ti_expr_tail  */
#line 344 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).domain); }
#line 2762 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 241: /* num_literals  */
#line 345 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).numlist); }
#line 2768 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 242: /* float_ti_expr_tail  */
#line 344 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).domain); }
#line 2774 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 246: /* array_par_bool_expr  */
#line 346 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2780 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 247: /* array_par_bool_literal  */
#line 346 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2786 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 248: /* array_par_bool_elements  */
#line 346 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2792 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 249: /* array_var_bool_expr  */
#line 347 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2798 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 250: /* array_var_bool_literal  */
#line 347 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2804 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 251: /* array_var_bool_elements  */
#line 347 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2810 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 255: /* array_par_int_expr  */
#line 348 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2816 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 256: /* array_par_int_literal  */
#line 348 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2822 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 257: /* array_par_int_elements  */
#line 348 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2828 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 258: /* array_var_int_expr  */
#line 349 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2834 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 259: /* array_var_int_literal  */
#line 349 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2840 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 260: /* array_var_int_elements  */
#line 349 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2846 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 264: /* array_par_float_expr  */
#line 350 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2852 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 265: /* array_par_float_literal  */
#line 350 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2858 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 266: /* array_par_float_elements  */
#line 350 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2864 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 267: /* array_var_float_expr  */
#line 351 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2870 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 268: /* array_var_float_literal  */
#line 351 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2876 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 269: /* array_var_float_elements  */
#line 351 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2882 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 271: /* set_literal  */
#line 353 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2888 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 272: /* set_elements  */
#line 353 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2894 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 273: /* set_array_literal  */
#line 353 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2900 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 274: /* set_array_elements  */
#line 353 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).node); }
#line 2906 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 277: /* annotations  */
#line 352 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).annotation); }
#line 2912 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
        break;

    case 278: /* shape_list  */
#line 345 "parser/flatzincbisonparser.yy" /* yacc.c:1257  */
      { delete ((*yyvaluep).intlist); }
#line 2918 "parser/flatzincbisonparser.cc" /* yacc.c:1257  */
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
#line 364 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3214 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 368 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3222 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 372 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3230 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 376 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYACCEPT;
  }
#line 3238 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 380 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYERROR;
  }
#line 3246 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 398 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    YYERROR;
  }
#line 3254 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 410 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
  }
#line 3262 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 414 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    // nothing to do
  }
#line 3270 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 420 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3276 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 421 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3282 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 422 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3288 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 423 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 3294 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 433 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    if ((yyvsp[0].term)) {
        parser->declare_par(dom, (yyvsp[-2].string), (yyvsp[0].term));
    }
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3306 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 441 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    if ((yyvsp[0].term)) {
        parser->declare_par(dom, (yyvsp[-2].string), (yyvsp[0].term));
    }
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3318 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 449 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    if ((yyvsp[0].term)) {
        parser->declare_par(dom, (yyvsp[-2].string), (yyvsp[0].term));
    }
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3330 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 457 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_par_set(dom, (yyvsp[-2].string), (yyvsp[0].node)->set_);
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3341 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 471 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3364 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 490 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3385 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 507 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3406 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 524 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3427 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 548 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var(dom, (yyvsp[-2].string), (yyvsp[0].term));
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3437 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 554 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //cout<<"integer";
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var(dom, (yyvsp[-2].string), (yyvsp[0].term));
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3448 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 561 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //cout<<"integer var2\n";
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var(dom, (yyvsp[-2].string), (yyvsp[0].term));
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 3459 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 568 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var(dom, (yyvsp[0].string), NULL);
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3469 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 574 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //cout<<"integer var\n";
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var(dom, (yyvsp[0].string), NULL);
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3480 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 581 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var(dom, (yyvsp[0].string), NULL);
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3490 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 587 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-4].domain));
    parser->declare_var_set(dom, (yyvsp[-2].string), (yyvsp[0].node)->set_);
    MSAT_SFREE((yyvsp[-2].string));
    delete (yyvsp[0].node);
  }
#line 3501 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 594 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    NumFlatZincDomainSharedPtr dom((yyvsp[-2].domain));
    parser->declare_var_set(dom, (yyvsp[0].string), FznSetSharedPtr());
    MSAT_SFREE((yyvsp[0].string));
  }
#line 3511 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 607 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3532 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 624 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3553 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 641 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3574 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 658 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3595 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 675 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3616 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 692 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3637 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 709 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3658 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 726 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 3678 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 749 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->annotate_decl((yyvsp[-1].string), *(yyvsp[0].annotation));
    delete (yyvsp[0].annotation);
    (yyval.string) = (yyvsp[-1].string);
    // MSAT_SFREE: postponed
  }
#line 3689 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 756 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->annotate_decl((yyvsp[-1].string), *(yyvsp[0].annotation));
    delete (yyvsp[0].annotation);
    (yyval.string) = (yyvsp[-1].string);
    // MSAT_SFREE: postponed
  }
#line 3700 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 770 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {

  }
#line 3708 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 777 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_and(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3717 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 782 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_or(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3726 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 787 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_xor(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 3735 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 792 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_bool_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3744 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 797 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_float_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3753 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 802 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_int_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3762 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 807 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_bool_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3771 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 812 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_float_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3780 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 817 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_int_element((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 3789 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 822 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool2int((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3797 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 826 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_and((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3805 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 830 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_clause(*((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 3815 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 836 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_eq((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3823 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 840 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_eq_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3831 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 844 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_le((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3839 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 848 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_le_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3847 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 852 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lin_eq(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 3857 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 858 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lin_le(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 3867 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 864 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3875 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 868 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_lt_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3883 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 872 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_not((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3891 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 876 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_or((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3899 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 880 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_xor((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3907 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 884 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_abs((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3915 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 888 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_div((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3923 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 892 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_acos((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3931 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 896 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_asin((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3939 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 900 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_atan((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3947 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 904 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_cos((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3955 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 908 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_cosh((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3963 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 912 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_exp((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3971 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 916 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_ln((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3979 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 920 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_log10((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3987 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 924 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_log2((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 3995 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 928 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_sqrt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4003 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 932 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_sin((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4011 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 936 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_sinh((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4019 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 940 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_tan((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4027 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 944 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_tanh((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4035 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 948 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_eq((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4043 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 952 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_eq_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4051 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 956 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_le((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4059 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 960 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_le_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4067 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 964 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_eq(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4077 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 970 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_eq_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4087 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 976 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_le(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4097 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 982 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_le_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4107 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 988 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_lt(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4117 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 994 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_lt_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4127 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 1000 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_ne(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4137 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 1006 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lin_ne_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4147 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 1012 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4155 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 1016 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_lt_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4163 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 1020 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_max((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4171 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 1024 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_min((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4179 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 1028 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_ne((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4187 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 1032 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_ne_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4195 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 1036 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_plus((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4203 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 1040 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_times((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4211 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 1044 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_abs((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4219 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 1048 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_div((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4227 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 1052 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_eq((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4235 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 1056 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_eq_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4243 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 1060 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_le((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4251 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 1064 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_le_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4259 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 1068 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_eq(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4269 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 1074 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_eq_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4279 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 1080 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_le(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4289 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 1086 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_le_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4299 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 1092 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_ne(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4309 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 1098 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lin_ne_reif(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
  }
#line 4319 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 1104 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lt((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4327 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 1108 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_lt_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4335 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 1112 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_max((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4343 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 1116 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_min((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4351 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 1120 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_mod((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4359 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 1124 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_ne((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4367 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 1128 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_ne_reif((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4375 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 1132 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_plus((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4383 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 1136 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int_times((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4391 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 1140 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->int2float((yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 4399 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 1144 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_set_element((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4409 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 1150 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_var_set_element((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4419 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 1156 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_card((yyvsp[-3].node)->set_, (yyvsp[-1].term));
  }
#line 4427 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 1160 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_diff((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4438 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 1167 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_eq((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4448 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 1173 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_eq_reif((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4458 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 1179 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_in((yyvsp[-3].term), (yyvsp[-1].node)->set_);
    delete (yyvsp[-1].node);
  }
#line 4467 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 1184 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_in_reif((yyvsp[-5].term), (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 4476 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 1189 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_intersect((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4487 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 1196 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_le((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4497 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 1202 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_lt((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4507 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 1208 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_ne((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4517 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 1214 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_ne_reif((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4527 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 1220 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_subset((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4537 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 1226 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_subset_reif((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 4547 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 1232 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_symdiff((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4558 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 1239 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->set_union((yyvsp[-5].node)->set_, (yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 4569 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 1246 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4576 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 1249 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    std::stringstream ss;
    ss << "constraint '" << (yyvsp[-3].string)
       << "' is not supported.";
    parser->handle_error(ss.str().c_str());
  }
#line 4587 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 1259 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    //std::cout<<"Solve maxiize\n";
    //parser->check_sat();
  }
#line 4596 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 1267 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4603 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 1270 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4610 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 1276 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4617 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 1279 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 4624 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 1285 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->push_objective(FlatZincAbstractParser::MINIMIZE, (yyvsp[0].term));
  }
#line 4632 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 1289 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->push_objective(FlatZincAbstractParser::MAXIMIZE, (yyvsp[0].term));
  }
#line 4640 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 1299 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 4646 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 1300 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 4652 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 1304 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4658 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 1305 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4664 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 1306 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4670 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 1307 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4676 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 1308 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4682 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 1309 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4688 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 1310 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4694 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 1311 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[-2].domain); MSAT_SFREE((yyvsp[0].string)); }
#line 4700 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 1313 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4708 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 1319 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 4714 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 1320 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[-2].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4720 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 1324 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4726 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 1325 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4732 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 1326 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4738 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 1327 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4744 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 1328 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4750 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 1329 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4756 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 1330 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4762 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 1331 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { delete (yyvsp[0].domain); }
#line 4768 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 1340 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_BOOL);
  }
#line 4776 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 1347 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_INT);
  }
#line 4784 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 1351 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_INT,
                               number_from_str((yyvsp[-2].string)),
                               number_from_str((yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4796 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 1359 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_INT, (*(yyvsp[-1].numlist)));
    delete (yyvsp[-1].numlist);
  }
#line 4805 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 1367 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[0].numlist)->push_back(number_from_str((yyvsp[-2].string)));
    (yyval.numlist) = (yyvsp[0].numlist);
    MSAT_SFREE((yyvsp[-2].string));
  }
#line 4815 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 1373 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.numlist) = new std::vector<Number>();
    (yyval.numlist)->push_back(number_from_str((yyvsp[0].string)));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4825 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 1382 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_FLOAT);
  }
#line 4833 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 1386 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.domain) = new NumFlatZincDomain(FZN_FLOAT,
                               number_from_str((yyvsp[-2].string)),
                               number_from_str((yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4845 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 1404 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 4851 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 1405 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4857 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 1406 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4863 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 1407 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4874 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 1414 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4885 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 1423 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 4891 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 1424 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4897 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 1425 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 4903 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 1426 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4914 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 1433 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_BOOL, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 4925 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 1443 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_false();
  }
#line 4933 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 1447 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_true();
  }
#line 4941 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 1457 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 4949 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 1461 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4959 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 1467 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 4969 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 1476 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 4977 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 199:
#line 1480 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 4986 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 200:
#line 1488 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 4995 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 201:
#line 1493 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5005 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 202:
#line 1502 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5013 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 203:
#line 1506 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5023 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 204:
#line 1512 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_BOOL, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5033 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 205:
#line 1521 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5041 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 206:
#line 1525 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5050 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 207:
#line 1533 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5059 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 208:
#line 1538 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5069 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 209:
#line 1550 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5075 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 210:
#line 1551 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5081 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 211:
#line 1552 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5087 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 212:
#line 1554 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5098 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 213:
#line 1561 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5109 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 214:
#line 1570 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5115 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 215:
#line 1571 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5121 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 216:
#line 1572 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5127 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 217:
#line 1574 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5138 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 218:
#line 1581 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_INT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5149 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 219:
#line 1591 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_int_number((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5158 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 220:
#line 1603 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5166 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 221:
#line 1607 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5176 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 222:
#line 1613 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5186 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 223:
#line 1622 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5194 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 224:
#line 1626 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5203 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 225:
#line 1634 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5212 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 226:
#line 1639 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5222 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 227:
#line 1648 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5230 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 228:
#line 1652 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5240 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 229:
#line 1658 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_INT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5250 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 230:
#line 1667 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5258 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 231:
#line 1671 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5267 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 232:
#line 1679 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5276 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 233:
#line 1684 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5286 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 234:
#line 1696 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5292 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 235:
#line 1697 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5298 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 236:
#line 1698 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5304 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 237:
#line 1700 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5315 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 238:
#line 1707 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(false, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5326 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 239:
#line 1716 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5332 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 240:
#line 1717 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5338 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 241:
#line 1718 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5344 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 242:
#line 1720 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5355 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 243:
#line 1727 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_FLOAT, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5366 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 244:
#line 1737 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.term) = parser->get_float_number((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5375 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 245:
#line 1749 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5383 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 246:
#line 1753 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5393 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 247:
#line 1759 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(false, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5403 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 248:
#line 1768 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5411 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 249:
#line 1772 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5420 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 250:
#line 1780 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5429 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 251:
#line 1785 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5439 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 252:
#line 1794 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[0].node);
  }
#line 5447 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 253:
#line 1798 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5457 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 254:
#line 1804 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_ = parser->get_array_var_literal(true, FZN_FLOAT, (yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5467 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 255:
#line 1813 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5475 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 256:
#line 1817 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
  }
#line 5484 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 257:
#line 1825 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].node)->termlist_->push_back((yyvsp[0].term));
    (yyval.node) = (yyvsp[-2].node);
  }
#line 5493 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 258:
#line 1830 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->termlist_.reset(new TermList());
    (yyval.node)->termlist_->push_back((yyvsp[0].term));
  }
#line 5503 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 259:
#line 1842 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5509 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 260:
#line 1843 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = (yyvsp[0].term); }
#line 5515 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 261:
#line 1844 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5521 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 262:
#line 1845 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[0].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5527 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 263:
#line 1847 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5538 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 264:
#line 1854 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.term) = parser->get_var_literal(true, FZN_NUMERIC, (yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5549 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 265:
#line 1868 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5557 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 266:
#line 1872 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    FlatZincSet *set = new FlatZincSet(true);
    (yyval.node)->set_.reset(set);
    set->add_set_elements(NumInterval(number_from_str((yyvsp[-2].string)),
                                      number_from_str((yyvsp[0].string))));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5571 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 267:
#line 1882 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5583 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 268:
#line 1890 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    size_t index = parser_atoi(parser, (yyvsp[-1].string));
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[-3].string), index);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5595 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 269:
#line 1898 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5605 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 270:
#line 1904 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_ = parser->get_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5615 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 271:
#line 1913 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-2].node);
    (yyval.node)->set_->add_set_elements(NumInterval(number_from_str((yyvsp[0].string))));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5625 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 272:
#line 1919 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_.reset(new FlatZincSet(true));
    (yyval.node)->set_->add_set_elements(NumInterval(number_from_str((yyvsp[0].string))));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5636 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 273:
#line 1926 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_.reset(new FlatZincSet(true));
  }
#line 5645 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 274:
#line 1934 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 5653 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 275:
#line 1938 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_ = parser->get_array_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5663 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 276:
#line 1944 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_ = parser->get_array_set_literals((yyvsp[0].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5673 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 277:
#line 1953 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-2].node);
    (yyval.node)->set_list_->push_back((yyvsp[0].node)->set_);
    delete (yyvsp[0].node);
  }
#line 5683 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 278:
#line 1959 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_.reset(new FznSetList());
    (yyval.node)->set_list_->push_back((yyvsp[0].node)->set_);
    delete (yyvsp[0].node);
  }
#line 5694 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 279:
#line 1966 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.node) = new FznNode();
    (yyval.node)->set_list_.reset(new FznSetList());
  }
#line 5703 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 280:
#line 1978 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5710 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 281:
#line 1981 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5717 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 282:
#line 1987 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5724 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 283:
#line 1990 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5731 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 284:
#line 1993 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5739 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 285:
#line 1997 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5747 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 286:
#line 2001 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5755 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 287:
#line 2005 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5762 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 288:
#line 2008 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5769 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 289:
#line 2011 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5778 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 290:
#line 2016 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5785 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 291:
#line 2019 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
  }
#line 5792 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 292:
#line 2022 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5801 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 293:
#line 2027 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 5810 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 294:
#line 2032 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5818 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 295:
#line 2036 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5826 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 296:
#line 2040 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
  }
#line 5834 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 297:
#line 2051 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-2].annotation)->set_output_var();
    (yyval.annotation) = (yyvsp[-2].annotation);
  }
#line 5843 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 298:
#line 2056 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-7].annotation)->set_output_array(*(yyvsp[-2].intlist));
    (yyval.annotation) = (yyvsp[-7].annotation);
    delete (yyvsp[-2].intlist);
  }
#line 5853 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 299:
#line 2062 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[0].string));
    (yyval.annotation) = (yyvsp[-2].annotation);
  }
#line 5862 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 300:
#line 2067 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    MSAT_SFREE((yyvsp[-3].string));
    (yyval.annotation) = (yyvsp[-5].annotation);
  }
#line 5871 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 301:
#line 2072 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.annotation) = new FlatZincAnnotation();
  }
#line 5879 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 302:
#line 2079 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyvsp[-4].intlist)->push_back(parser_atoi(parser,(yyvsp[-2].string)));
    (yyvsp[-4].intlist)->push_back(parser_atoi(parser,(yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
    (yyval.intlist) = (yyvsp[-4].intlist);
  }
#line 5891 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 303:
#line 2087 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.intlist) = new std::vector<int64_t>();
    (yyval.intlist)->push_back(parser_atoi(parser,(yyvsp[-2].string)));
    (yyval.intlist)->push_back(parser_atoi(parser,(yyvsp[0].string)));
    MSAT_SFREE((yyvsp[-2].string));
    MSAT_SFREE((yyvsp[0].string));
  }
#line 5903 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 304:
#line 2095 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    (yyval.intlist) = new std::vector<int64_t>();
  }
#line 5911 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 305:
#line 2105 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5917 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 306:
#line 2106 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5923 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 307:
#line 2107 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[0].string)); }
#line 5929 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 308:
#line 2108 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[-3].string)); }
#line 5935 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 309:
#line 2109 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5941 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 310:
#line 2113 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5947 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 311:
#line 2114 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5953 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 312:
#line 2115 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { }
#line 5959 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 313:
#line 2119 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    { MSAT_SFREE((yyvsp[-2].string)); MSAT_SFREE((yyvsp[0].string)); }
#line 5965 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 349:
#line 2163 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    // supported
  }
#line 5973 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 350:
#line 2170 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_different_except_0(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 5982 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 351:
#line 2175 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_different(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 5991 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 352:
#line 2180 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_different((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6000 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 353:
#line 2188 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->disjoint((yyvsp[-3].node)->set_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6010 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 354:
#line 2194 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_disjoint((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6019 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 355:
#line 2202 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->disjunctive(*((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6029 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 356:
#line 2208 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->disjunctive_strict(*((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6039 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 357:
#line 2217 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_equal(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6048 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 358:
#line 2222 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->all_equal((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6057 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 359:
#line 2230 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->among((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6067 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 360:
#line 2239 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6076 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 361:
#line 2244 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6085 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 362:
#line 2252 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6094 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 363:
#line 2257 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6103 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 364:
#line 2265 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6112 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 365:
#line 2270 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_max((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6121 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 366:
#line 2278 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6130 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 367:
#line 2283 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->array_min((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6139 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 368:
#line 2293 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->maximum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6154 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 369:
#line 2305 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->maximum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6169 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 370:
#line 2321 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->minimum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6184 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 371:
#line 2333 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->minimum_arg(*((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6199 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 372:
#line 2347 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_geq((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6208 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 373:
#line 2352 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->at_least_set((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6218 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 374:
#line 2361 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_eq((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6227 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 375:
#line 2366 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->exactly_set((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6237 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 376:
#line 2375 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_leq((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6246 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 377:
#line 2380 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->at_least_set((yyvsp[-5].term), (yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6256 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 378:
#line 2386 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->at_most_1((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6265 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 379:
#line 2395 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6282 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 380:
#line 2409 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6299 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 381:
#line 2422 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bin_packing((yyvsp[-5].term), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6309 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 382:
#line 2432 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);
    parser->element((yyvsp[-9].term), *((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6323 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 383:
#line 2443 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);
    parser->element((yyvsp[-9].term), *((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6337 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 384:
#line 2454 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);
    parser->element((yyvsp[-9].term), *((yyvsp[-7].node)->termlist_), (yyvsp[-5].term), x_ival);
    delete (yyvsp[-7].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6351 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 385:
#line 2465 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6366 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 386:
#line 2479 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->comparison_rel_array(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6375 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 387:
#line 2487 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_eq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6384 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 388:
#line 2492 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_geq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6393 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 389:
#line 2497 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_gt((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6402 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 390:
#line 2502 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_leq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6411 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 391:
#line 2507 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_lt((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6420 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 392:
#line 2512 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->count_neq((yyvsp[-1].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term));
    delete (yyvsp[-5].node);
  }
#line 6429 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 393:
#line 2520 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6438 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 394:
#line 2525 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6447 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 395:
#line 2530 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6456 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 396:
#line 2535 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->decreasing((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6465 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 397:
#line 2543 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6474 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 398:
#line 2548 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6483 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 399:
#line 2553 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing(*((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6492 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 400:
#line 2558 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->increasing((yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6501 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 401:
#line 2566 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6513 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 402:
#line 2574 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn_nonstrict(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6525 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 403:
#line 2582 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn_nonoverlap_k(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6537 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 404:
#line 2591 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->diffn_nonstrict_nonoverlap_k(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6549 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 405:
#line 2602 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->distribute(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6560 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 406:
#line 2613 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->geost_nonoverlap_k(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6572 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 407:
#line 2624 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6583 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 408:
#line 2631 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality_closed(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6594 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 409:
#line 2638 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality_low_up(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6606 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 410:
#line 2646 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->global_cardinality_low_up_closed(*((yyvsp[-7].node)->termlist_), *((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-7].node);
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6618 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 411:
#line 2659 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6640 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 412:
#line 2682 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6663 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 413:
#line 2703 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6686 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 414:
#line 2726 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6703 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 415:
#line 2742 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6712 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 416:
#line 2747 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6721 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 417:
#line 2752 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member(*((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-3].node);
  }
#line 6730 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 418:
#line 2757 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->member((yyvsp[-3].node)->set_list_, (yyvsp[-1].node)->set_);
    delete (yyvsp[-3].node);
    delete (yyvsp[-1].node);
  }
#line 6740 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 419:
#line 2766 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->nvalue((yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6749 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 420:
#line 2775 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6767 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 421:
#line 2792 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->bool_clause_reif(*((yyvsp[-5].node)->termlist_), *((yyvsp[-3].node)->termlist_), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
    delete (yyvsp[-3].node);
  }
#line 6777 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 422:
#line 2801 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_in((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].term));
  }
#line 6785 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 423:
#line 2806 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->float_dom((yyvsp[-7].term), *((yyvsp[-5].node)->termlist_), (yyvsp[-3].term), (yyvsp[-1].term));
    delete (yyvsp[-5].node);
  }
#line 6794 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 424:
#line 2815 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6812 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 425:
#line 2834 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
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
#line 6834 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 426:
#line 2856 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    Number start = number_from_str((yyvsp[-3].string));
    Number end   = number_from_str((yyvsp[-1].string));
    NumInterval x_ival(start, end);

    parser->symmetric_all_different(*((yyvsp[-5].node)->termlist_), x_ival);
    delete (yyvsp[-5].node);
    MSAT_SFREE((yyvsp[-3].string));
    MSAT_SFREE((yyvsp[-1].string));
  }
#line 6849 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 427:
#line 2870 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->value_precede((yyvsp[-5].term), (yyvsp[-3].term), *((yyvsp[-1].node)->termlist_));
    delete (yyvsp[-1].node);
  }
#line 6858 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 428:
#line 2875 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {
    parser->value_precede((yyvsp[-5].term), (yyvsp[-3].term), (yyvsp[-1].node)->set_list_);
    delete (yyvsp[-1].node);
  }
#line 6867 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;

  case 507:
#line 2961 "parser/flatzincbisonparser.yy" /* yacc.c:1646  */
    {

  }
#line 6875 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
    break;


#line 6879 "parser/flatzincbisonparser.cc" /* yacc.c:1646  */
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
#line 2969 "parser/flatzincbisonparser.yy" /* yacc.c:1906  */


namespace {

inline Number number_from_str(const char *str)
{
    assert(str);
    return Number::from_str(str);
}

} // namespace
