/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 83 "parser/flatzincbisonparser.yy" /* yacc.c:1909  */

    char *string;
    const msat::Term_ *term;
    std::vector<msat::Number> *numlist;
    std::vector<int64_t> *intlist;
    msat::NumFlatZincDomain *domain;
    msat::FznNode *node;
    msat::FlatZincAnnotation *annotation;

#line 269 "parser/flatzincbisonparser.hh" /* yacc.c:1909  */
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
