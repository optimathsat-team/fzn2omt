// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Bison parser for FlatZinc 1.6
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

%{

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

%}

%locations
%pure-parser
%name-prefix="msat_flatzinc_parser_"
%debug
%verbose
%define parse.error verbose

%parse-param { yyscan_t scanner }
%parse-param { msat::FlatZincAbstractParser *parser }
%lex-param   { yyscan_t scanner }

%union {
    char *string;
    const msat::Term_ *term;
    std::vector<msat::Number> *numlist;
    std::vector<int64_t> *intlist;
    msat::NumFlatZincDomain *domain;
    msat::FznNode *node;
    msat::FlatZincAnnotation *annotation;
};

%token-table

%token TK_PREDICATE     "predicate"
%token TK_VAR           "var"
%token TK_BOOL          "bool"
%token TK_FLOAT         "float"
%token TK_INT           "int"
%token TK_ARRAY         "array"
%token TK_SET           "set"
%token TK_OF            "of"
%token TK_TRUE          "true"
%token TK_FALSE         "false"
%token TK_CONSTRAINT    "constraint"
%token TK_SOLVE         "solve"
%token TK_MINIMIZE      "minimize"
%token TK_MAXIMIZE      "maximize"
%token TK_SATISFY       "satisfy"
%token TK_DOTDOT        ".."
%token TK_COLONCOLON    "::"
%token TK_EOF

%token TK_ARRAY_BOOL_AND          "array_bool_and"
%token TK_ARRAY_BOOL_ELEMENT      "array_bool_element"
%token TK_ARRAY_BOOL_OR           "array_bool_or"
%token TK_ARRAY_BOOL_XOR          "array_bool_xor"
%token TK_ARRAY_FLOAT_ELEMENT     "array_float_element"
%token TK_ARRAY_INT_ELEMENT       "array_int_element"
%token TK_ARRAY_SET_ELEMENT       "array_set_element"
%token TK_ARRAY_VAR_BOOL_ELEMENT  "array_var_bool_element"
%token TK_ARRAY_VAR_FLOAT_ELEMENT "array_var_float_element"
%token TK_ARRAY_VAR_INT_ELEMENT   "array_var_int_element"
%token TK_ARRAY_VAR_SET_ELEMENT   "array_var_set_element"
%token TK_BOOL2INT                "bool2int"
%token TK_BOOL_AND                "bool_and"
%token TK_BOOL_CLAUSE             "bool_clause"
%token TK_BOOL_EQ                 "bool_eq"
%token TK_BOOL_EQ_REIF            "bool_eq_reif"
%token TK_BOOL_LE                 "bool_le"
%token TK_BOOL_LE_REIF            "bool_le_reif"
%token TK_BOOL_LIN_EQ             "bool_lin_eq"
%token TK_BOOL_LIN_LE             "bool_lin_le"
%token TK_BOOL_LT                 "bool_lt"
%token TK_BOOL_LT_REIF            "bool_lt_reif"
%token TK_BOOL_NOT                "bool_not"
%token TK_BOOL_OR                 "bool_or"
%token TK_BOOL_XOR                "bool_xor"
%token TK_FLOAT_ABS               "float_abs"
%token TK_FLOAT_DIV               "float_div"
%token TK_FLOAT_ACOS              "float_acos"
%token TK_FLOAT_ASIN              "float_asin"
%token TK_FLOAT_ATAN              "float_atan"
%token TK_FLOAT_COS               "float_cos"
%token TK_FLOAT_COSH              "float_cosh"
%token TK_FLOAT_EXP               "float_exp"
%token TK_FLOAT_LN                "float_ln"
%token TK_FLOAT_LOG10             "float_log10"
%token TK_FLOAT_LOG2              "float_log2"
%token TK_FLOAT_SQRT              "float_sqrt"
%token TK_FLOAT_SIN               "float_sin"
%token TK_FLOAT_SINH              "float_sinh"
%token TK_FLOAT_TAN               "float_tan"
%token TK_FLOAT_TANH              "float_tanh"
%token TK_FLOAT_EQ                "float_eq"
%token TK_FLOAT_EQ_REIF           "float_reif"
%token TK_FLOAT_LE                "float_le"
%token TK_FLOAT_LE_REIF           "float_le_reif"
%token TK_FLOAT_LIN_EQ            "float_lin_eq"
%token TK_FLOAT_LIN_EQ_REIF       "float_lin_eq_reif"
%token TK_FLOAT_LIN_LE            "float_lin_le"
%token TK_FLOAT_LIN_LE_REIF       "float_lin_le_reif"
%token TK_FLOAT_LIN_LT            "float_lin_lt"
%token TK_FLOAT_LIN_LT_REIF       "float_lin_lt_reif"
%token TK_FLOAT_LIN_NE            "float_lin_ne"
%token TK_FLOAT_LIN_NE_REIF       "float_lin_ne_reif"
%token TK_FLOAT_LT                "float_lt"
%token TK_FLOAT_LT_REIF           "float_lt_reif"
%token TK_FLOAT_MAX               "float_max"
%token TK_FLOAT_MIN               "float_min"
%token TK_FLOAT_NE                "float_ne"
%token TK_FLOAT_NE_REIF           "float_ne_reif"
%token TK_FLOAT_PLUS              "float_plus"
%token TK_FLOAT_TIMES             "float_times"
%token TK_INT_ABS                 "int_abs"
%token TK_INT_DIV                 "int_div"
%token TK_INT_EQ                  "int_eq"
%token TK_INT_EQ_REIF             "int_eq_reif"
%token TK_INT_LE                  "int_le"
%token TK_INT_LE_REIF             "int_le_reif"
%token TK_INT_LIN_EQ              "int_lin_eq"
%token TK_INT_LIN_EQ_REIF         "int_lin_eq_reif"
%token TK_INT_LIN_LE              "int_lin_le"
%token TK_INT_LIN_LE_REIF         "int_lin_le_reif"
%token TK_INT_LIN_NE              "int_lin_ne"
%token TK_INT_LIN_NE_REIF         "int_lin_ne_reif"
%token TK_INT_LT                  "int_lt"
%token TK_INT_LT_REIF             "int_lt_reif"
%token TK_INT_MAX                 "int_max"
%token TK_INT_MIN                 "int_min"
%token TK_INT_MOD                 "int_mod"
%token TK_INT_NE                  "int_ne"
%token TK_INT_NE_REIF             "int_ne_reif"
%token TK_INT_PLUS                "int_plus"
%token TK_INT_TIMES               "int_times"
%token TK_INT2FLOAT               "int2float"
%token TK_SET_CARD                "set_card"
%token TK_SET_DIFF                "set_diff"
%token TK_SET_EQ                  "set_eq"
%token TK_SET_EQ_REIF             "set_eq_reif"
%token TK_SET_IN                  "set_in"
%token TK_SET_IN_REIF             "set_in_reif"
%token TK_SET_INTERSECT           "set_intersect"
%token TK_SET_LE                  "set_le"
%token TK_SET_LT                  "set_lt"
%token TK_SET_NE                  "set_ne"
%token TK_SET_NE_REIF             "set_ne_reif"
%token TK_SET_SUBSET              "set_subset"
%token TK_SET_SUBSET_REIF         "set_subset_reif"
%token TK_SET_SYMDIFF             "set_symdiff"
%token TK_SET_UNION               "set_union"

%token TK_ALLDIFFERENT_EXCEPT_0             "optimathsat_alldifferent_except_0"
%token TK_ALL_DIFFERENT_INT                 "optimathsat_all_different_int"
%token TK_ALL_DIFFERENT_SET                 "optimathsat_all_different_set"
%token TK_ALL_DISJOINT                      "optimathsat_all_disjoint"
%token TK_DISJOINT                          "optimathsat_disjoint"
%token TK_DISJUNCTIVE                       "optimathsat_disjunctive"
%token TK_DISJUNCTIVE_STRICT                "optimathsat_disjunctive_strict"
%token TK_ALL_EQUAL_INT                     "optimathsat_all_equal_int"
%token TK_ALL_EQUAL_SET                     "optimathsat_all_equal_set"
%token TK_AMONG                             "optimathsat_among"
%token TK_MAXIMUM_FLOAT                     "optimathsat_maximum_float"           // MiniZinc 1.6
%token TK_MAXIMUM_INT                       "optimathsat_maximum_int"             // MiniZinc 1.6
%token TK_MINIMUM_FLOAT                     "optimathsat_minimum_float"           // MiniZinc 1.6
%token TK_MINIMUM_INT                       "optimathsat_minimum_int"             // MiniZinc 1.6
%token TK_ARRAY_FLOAT_MAXIMUM               "optimathsat_array_float_maximum"     // MiniZinc 2.1.5
%token TK_ARRAY_INT_MAXIMUM                 "optimathsat_array_int_maximum"       // MiniZinc 2.1.5
%token TK_ARRAY_FLOAT_MINIMUM               "optimathsat_array_float_minimum"     // Minizinc 2.1.5
%token TK_ARRAY_INT_MINIMUM                 "optimathsat_array_int_minimum"       // MiniZinc 2.1.5
%token TK_MAXIMUM_ARG_INT                   "optimathsat_maximum_arg_int"
%token TK_MAXIMUM_ARG_FLOAT                 "optimathsat_maximum_arg_float"
%token TK_MINIMUM_ARG_INT                   "optimathsat_minimum_arg_int"
%token TK_MINIMUM_ARG_FLOAT                 "optimathsat_minimum_arg_float"
%token TK_AT_LEAST_INT                      "optimathsat_at_least_int"
%token TK_AT_LEAST_SET                      "optimathsat_at_least_set"
%token TK_EXACTLY_INT                       "optimathsat_exactly_int"
%token TK_EXACTLY_SET                       "optimathsat_exactly_set"
%token TK_AT_MOST_INT                       "optimathsat_at_most_int"
%token TK_AT_MOST_SET                       "optimathsat_at_most_set"
%token TK_ATMOST1                           "optimathsat_at_most1"
%token TK_BIN_PACKING_CAPA                  "optimathsat_bin_packing_capa"
%token TK_BIN_PACKING_LOAD                  "optimathsat_bin_packing_load"
%token TK_BIN_PACKING                       "optimathsat_bin_packing"
%token TK_ELEMENT_BOOL                      "optimathsat_element_bool"
%token TK_ELEMENT_FLOAT                     "optimathsat_element_float"
%token TK_ELEMENT_INT                       "optimathsat_element_int"
%token TK_ELEMENT_SET                       "optimathsat_element_set"
%token TK_COMPARISON_REL_ARRAY              "optimathsat_comparison_rel_array"
%token TK_COUNT_EQ                          "optimathsat_count_eq"
%token TK_COUNT_GEQ                         "optimathsat_count_geq"
%token TK_COUNT_GT                          "optimathsat_count_gt"
%token TK_COUNT_LEQ                         "optimathsat_count_leq"
%token TK_COUNT_LT                          "optimathsat_count_lt"
%token TK_COUNT_NEQ                         "optimathsat_count_neq"
%token TK_DECREASING_BOOL                   "optimathsat_decreasing_bool"
%token TK_DECREASING_FLOAT                  "optimathsat_decreasing_float"
%token TK_DECREASING_INT                    "optimathsat_decreasing_int"
%token TK_DECREASING_SET                    "optimathsat_decreasing_set"
%token TK_INCREASING_BOOL                   "optimathsat_increasing_bool"
%token TK_INCREASING_FLOAT                  "optimathsat_increasing_float"
%token TK_INCREASING_INT                    "optimathsat_increasing_int"
%token TK_INCREASING_SET                    "optimathsat_increasing_set"
%token TK_DIFFN                             "optimathsat_diffn"
%token TK_DIFFN_NONSTRICT                   "optimathsat_diffn_nonstrict"
%token TK_DIFFN_NONOVERLAP_K                "optimathsat_diffn_nonoverlap_k"
%token TK_DIFFN_NONSTRICT_NONOVERLAP_K      "optimathsat_diffn_nonstrict_nonoverlap_k"
%token TK_DISTRIBUTE                        "optimathsat_distribute"
%token TK_GEOST_NONOVERLAP_K                "optimathsat_geost_nonoverlap_k"
%token TK_GLOBAL_CARDINALITY                "optimathsat_global_cardinality"
%token TK_GLOBAL_CARDINALITY_CLOSED         "optimathsat_global_cardinality_closed"
%token TK_GLOBAL_CARDINALITY_LOW_UP         "optimathsat_global_cardinality_low_up"
%token TK_GLOBAL_CARDINALITY_LOW_UP_CLOSED  "optimathsat_global_cardinality_low_up_closed"
%token TK_INT_SET_CHANNEL                   "optimathsat_int_set_channel"
%token TK_INVERSE                           "optimathsat_inverse"
%token TK_INVERSE_SET                       "optimathsat_inverse_set"
%token TK_LINK_SET_TO_BOOLEANS              "optimathsat_link_set_to_booleans"
%token TK_MEMBER_BOOL                       "optimathsat_member_bool"
%token TK_MEMBER_FLOAT                      "optimathsat_member_float"
%token TK_MEMBER_INT                        "optimathsat_member_int"
%token TK_MEMBER_SET                        "optimathsat_member_set"
%token TK_NVALUE                            "optimathsat_nvalue"
%token TK_RANGE                             "optimathsat_range"
%token TK_BOOL_CLAUSE_REIF                  "optimathsat_bool_clause_reif"
%token TK_FLOAT_IN                          "optimathsat_float_in"
%token TK_FLOAT_DOM                         "optimathsat_float_dom"
%token TK_ROOTS                             "optimathsat_roots"
%token TK_SUM_PRED                          "optimathsat_sum_pred"
%token TK_SYMMETRIC_ALL_DIFFERENT           "optimathsat_symmetric_all_different"
%token TK_VALUE_PRECEDE_INT                 "optimathsat_value_precede_int"
%token TK_VALUE_PRECEDE_SET                 "optimathsat_value_precede_set"

%token TK_OUTPUT_VAR              "output_var"
%token TK_OUTPUT_ARRAY            "output_array"

%token <string> IDENT
%token <string> UNDERSCORE_IDENT
%token <string> STRING_LITERAL
%token <string> INT_LITERAL
%token <string> FLOAT_LITERAL
%type <string> ident_anns
%type <domain> bool_ti_expr_tail
%type <domain> int_ti_expr_tail
%type <domain> float_ti_expr_tail
%type <term> bool_literal
%type <term> par_bool_expr
%type <term> var_bool_expr
%type <term> int_literal
%type <term> par_int_expr
%type <term> var_int_expr
%type <term> float_literal
%type <term> par_float_expr
%type <term> var_float_expr
%type <term> var_num_expr
%type <node> array_par_bool_expr
%type <node> array_par_bool_literal
%type <node> array_par_bool_elements
%type <node> array_var_bool_expr
%type <node> array_var_bool_literal
%type <node> array_var_bool_elements
%type <node> array_par_int_expr
%type <node> array_par_int_literal
%type <node> array_par_int_elements
%type <node> array_var_int_expr
%type <node> array_var_int_literal
%type <node> array_var_int_elements
%type <node> array_par_float_expr
%type <node> array_par_float_literal
%type <node> array_par_float_elements
%type <node> array_var_float_expr
%type <node> array_var_float_literal
%type <node> array_var_float_elements
%type <node> set_literal
%type <node> set_elements
%type <node> set_array_literal
%type <node> set_array_elements
%type <intlist> shape_list
%type <numlist> num_literals
%type <annotation> annotations

%destructor { MSAT_SFREE($$); } IDENT UNDERSCORE_IDENT STRING_LITERAL INT_LITERAL FLOAT_LITERAL ident_anns
%destructor { delete $$; } bool_ti_expr_tail int_ti_expr_tail float_ti_expr_tail
%destructor { delete $$; } shape_list num_literals;
%destructor { delete $$; } array_par_bool_expr array_par_bool_literal array_par_bool_elements
%destructor { delete $$; } array_var_bool_expr array_var_bool_literal array_var_bool_elements
%destructor { delete $$; } array_par_int_expr array_par_int_literal array_par_int_elements
%destructor { delete $$; } array_var_int_expr array_var_int_literal array_var_int_elements
%destructor { delete $$; } array_par_float_expr array_par_float_literal array_par_float_elements
%destructor { delete $$; } array_var_float_expr array_var_float_literal array_var_float_elements
%destructor { delete $$; } annotations;
%destructor { delete $$; } set_literal set_elements set_array_literal set_array_elements;

%start whole_model
%%

//---------------------------------------------------------------------------
// Whole-File Parsing
//---------------------------------------------------------------------------

whole_model :
  declarations constraints solve_item ';'
  {
    YYACCEPT;
  }
| declarations solve_item ';'
  {
    YYACCEPT;
  }
| constraints solve_item ';'
  {
    YYACCEPT;
  }
| solve_item ';'
  {
    YYACCEPT;
  }
| error_state
  {
    YYERROR;
  }
;

declarations :
  pred_decl_item ';' declarations
| decl_item ';' declarations
| pred_decl_item ';'
| decl_item ';'
;

constraints :
  constraint_item ';' constraints
| constraint_item ';'
;

error_state :
  {
    YYERROR;
  }
;


//---------------------------------------------------------------------------
// Items
//---------------------------------------------------------------------------

pred_decl_item :
  TK_PREDICATE IDENT '(' pred_decl_args ')'
  {
    MSAT_SFREE($2);
  }
| TK_PREDICATE global_ident '(' pred_decl_args ')'
  {
    // nothing to do
  }
;

decl_item :
  par_decl_item { }
| array_par_decl_item { }
| var_decl_item { }
| array_var_decl_item { }
;


    //---------------------------------------------------------------------------
    // SIMPLE PAR
    //---------------------------------------------------------------------------

par_decl_item :
  bool_ti_expr_tail ':' ident_anns '=' par_bool_expr
  {
    NumFlatZincDomainSharedPtr dom($1);
    if ($5) {
        parser->declare_par(dom, $3, $5);
    }
    MSAT_SFREE($3);
  }
| int_ti_expr_tail ':' ident_anns '=' par_int_expr
  {
    NumFlatZincDomainSharedPtr dom($1);
    if ($5) {
        parser->declare_par(dom, $3, $5);
    }
    MSAT_SFREE($3);
  }
| float_ti_expr_tail ':' ident_anns '=' par_float_expr
  {
    NumFlatZincDomainSharedPtr dom($1);
    if ($5) {
        parser->declare_par(dom, $3, $5);
    }
    MSAT_SFREE($3);
  }
| TK_SET TK_OF int_ti_expr_tail ':' ident_anns '=' set_literal
  {
    NumFlatZincDomainSharedPtr dom($3);
    parser->declare_par_set(dom, $5, $7->set_);
    MSAT_SFREE($5);
    delete $7;
  }
;

    //---------------------------------------------------------------------------
    // ARRAY PAR
    //---------------------------------------------------------------------------

array_par_decl_item :
  TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF bool_ti_expr_tail ':' ident_anns '=' array_par_bool_expr
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    FznType v;

    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($8);
    parser->declare_array_par(len, dom, $10, $12->termlist_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($10);
    delete $12;
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF int_ti_expr_tail ':' ident_anns '=' array_par_int_expr
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($8);
    parser->declare_array_par(len, dom, $10, $12->termlist_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($10);
    delete $12;
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF float_ti_expr_tail ':' ident_anns '=' array_par_float_expr
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($8);
    parser->declare_array_par(len, dom, $10, $12->termlist_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($10);
    delete $12;
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_SET TK_OF int_ti_expr_tail ':' ident_anns '=' set_array_literal
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($10);
    parser->declare_array_par_set(len, dom, $12, $14->set_list_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($12);
    delete $14;
  }
;

    //---------------------------------------------------------------------------
    // SIMPLE VAR
    //---------------------------------------------------------------------------

var_decl_item :
  TK_VAR    bool_ti_expr_tail ':' ident_anns '=' var_bool_expr
  {
    NumFlatZincDomainSharedPtr dom($2);
    parser->declare_var(dom, $4, $6);
    MSAT_SFREE($4);
  }
| TK_VAR    int_ti_expr_tail ':' ident_anns '=' var_int_expr
  {
    //cout<<"integer";
    NumFlatZincDomainSharedPtr dom($2);
    parser->declare_var(dom, $4, $6);
    MSAT_SFREE($4);
  }
| TK_VAR    float_ti_expr_tail ':' ident_anns '=' var_float_expr
  {
    //cout<<"integer var2\n";
    NumFlatZincDomainSharedPtr dom($2);
    parser->declare_var(dom, $4, $6);
    MSAT_SFREE($4);
  }
| TK_VAR    bool_ti_expr_tail ':' ident_anns
  {
    NumFlatZincDomainSharedPtr dom($2);
    parser->declare_var(dom, $4, NULL);
    MSAT_SFREE($4);
  }
| TK_VAR    int_ti_expr_tail ':' ident_anns
  {
    //cout<<"integer var\n";
    NumFlatZincDomainSharedPtr dom($2);
    parser->declare_var(dom, $4, NULL);
    MSAT_SFREE($4);
  }
| TK_VAR    float_ti_expr_tail ':' ident_anns
  {
    NumFlatZincDomainSharedPtr dom($2);
    parser->declare_var(dom, $4, NULL);
    MSAT_SFREE($4);
  }
| TK_VAR TK_SET TK_OF int_ti_expr_tail ':' ident_anns '=' set_literal
  {
    NumFlatZincDomainSharedPtr dom($4);
    parser->declare_var_set(dom, $6, $8->set_);
    MSAT_SFREE($6);
    delete $8;
  }
| TK_VAR TK_SET TK_OF int_ti_expr_tail ':' ident_anns
  {
    NumFlatZincDomainSharedPtr dom($4);
    parser->declare_var_set(dom, $6, FznSetSharedPtr());
    MSAT_SFREE($6);
  }
;

    //---------------------------------------------------------------------------
    // ARRAY VAR
    //---------------------------------------------------------------------------

array_var_decl_item :
  TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR bool_ti_expr_tail ':' ident_anns '=' array_var_bool_expr
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($9);
    parser->declare_array_var(len, dom, $11, $13->termlist_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($11);
    delete $13;
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR int_ti_expr_tail ':' ident_anns '=' array_var_int_expr
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($9);
    parser->declare_array_var(len, dom, $11, $13->termlist_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($11);
    delete $13;
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR float_ti_expr_tail ':' ident_anns '=' array_var_float_expr
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($9);
    parser->declare_array_var(len, dom, $11, $13->termlist_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($11);
    delete $13;
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR bool_ti_expr_tail ':' ident_anns
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($9);
    TermListSharedPtr terms(NULL);
    parser->declare_array_var(len, dom, $11, terms);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($11);
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR int_ti_expr_tail ':' ident_anns
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($9);
    TermListSharedPtr terms(NULL);
    parser->declare_array_var(len, dom, $11, terms);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($11);
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR float_ti_expr_tail ':' ident_anns
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($9);
    TermListSharedPtr terms(NULL);
    parser->declare_array_var(len, dom, $11, terms);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($11);
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR TK_SET TK_OF int_ti_expr_tail ':' ident_anns '=' set_array_literal
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($11);
    parser->declare_array_var_set(len, dom, $13, $15->set_list_);
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($13);
    delete $15;
  }
| TK_ARRAY '[' INT_LITERAL TK_DOTDOT INT_LITERAL ']' TK_OF TK_VAR TK_SET TK_OF int_ti_expr_tail ':' ident_anns
  {
    size_t one = parser_atoi(parser, $3);
    if (one != 1) {
        std::stringstream ss;
        ss << "syntax error at `" << one
           << "' expected `1' after `['";
        parser->handle_error(ss.str().c_str());
    }
    size_t len = parser_atoi(parser, $5);
    NumFlatZincDomainSharedPtr dom($11);
    parser->declare_array_var_set(len, dom, $13, FznSetListSharedPtr());
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    MSAT_SFREE($13);
  }
;

    //---------------------------------------------------------------------------
    // IDENTIFIER + ANNOTATIONS (DECLARATION)
    //---------------------------------------------------------------------------

ident_anns :
  IDENT annotations
  {
    parser->annotate_decl($1, *$2);
    delete $2;
    $$ = $1;
    // MSAT_SFREE: postponed
  }
| UNDERSCORE_IDENT annotations
  {
    parser->annotate_decl($1, *$2);
    delete $2;
    $$ = $1;
    // MSAT_SFREE: postponed
  }
;

    //---------------------------------------------------------------------------
    // GLOBAL CONSTRAINTS
    //---------------------------------------------------------------------------

constraint_item :
  TK_CONSTRAINT constraint_elem ignored_annotations
  {

  }
;

constraint_elem :
  TK_ARRAY_BOOL_AND '(' array_var_bool_expr ',' var_bool_expr ')'
  {
    parser->array_bool_and(*($3->termlist_), $5);
    delete $3;
  }
| TK_ARRAY_BOOL_OR '(' array_var_bool_expr ',' var_bool_expr ')'
  {
    parser->array_bool_or(*($3->termlist_), $5);
    delete $3;
  }
| TK_ARRAY_BOOL_XOR '(' array_var_bool_expr ')'
  {
    parser->array_bool_xor(*($3->termlist_));
    delete $3;
  }
| TK_ARRAY_BOOL_ELEMENT '(' var_int_expr ',' array_par_bool_expr ',' var_bool_expr ')'
  {
    parser->array_bool_element($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_ARRAY_FLOAT_ELEMENT '(' var_int_expr ',' array_par_float_expr ',' var_float_expr ')'
  {
    parser->array_float_element($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_ARRAY_INT_ELEMENT '(' var_int_expr ',' array_par_int_expr ',' var_int_expr ')'
  {
    parser->array_int_element($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_ARRAY_VAR_BOOL_ELEMENT '(' var_int_expr ',' array_var_bool_expr ',' var_bool_expr ')'
  {
    parser->array_var_bool_element($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_ARRAY_VAR_FLOAT_ELEMENT '(' var_int_expr ',' array_var_float_expr ',' var_float_expr ')'
  {
    parser->array_var_float_element($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_ARRAY_VAR_INT_ELEMENT '(' var_int_expr ',' array_var_int_expr ',' var_int_expr ')'
  {
    parser->array_var_int_element($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_BOOL2INT '(' var_bool_expr ',' var_int_expr ')'
  {
    parser->bool2int($3, $5);
  }
| TK_BOOL_AND '(' var_bool_expr ',' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_and($3, $5, $7);
  }
| TK_BOOL_CLAUSE '(' array_var_bool_expr ',' array_var_bool_expr ')'
  {
    parser->bool_clause(*($3->termlist_), *($5->termlist_));
    delete $3;
    delete $5;
  }
| TK_BOOL_EQ '(' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_eq($3, $5);
  }
| TK_BOOL_EQ_REIF '(' var_bool_expr ',' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_eq_reif($3, $5, $7);
  }
| TK_BOOL_LE '(' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_le($3, $5);
  }
| TK_BOOL_LE_REIF '(' var_bool_expr ',' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_le_reif($3, $5, $7);
  }
| TK_BOOL_LIN_EQ '(' array_par_int_expr ',' array_var_bool_expr ',' var_int_expr ')'
  {
    parser->bool_lin_eq(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_BOOL_LIN_LE '(' array_par_int_expr ',' array_var_bool_expr ',' par_int_expr ')'
  {
    parser->bool_lin_le(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_BOOL_LT '(' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_lt($3, $5);
  }
| TK_BOOL_LT_REIF '(' var_bool_expr ',' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_lt_reif($3, $5, $7);
  }
| TK_BOOL_NOT '(' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_not($3, $5);
  }
| TK_BOOL_OR '(' var_bool_expr ',' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_or($3, $5, $7);
  }
| TK_BOOL_XOR '(' var_bool_expr ',' var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_xor($3, $5, $7);
  }
| TK_FLOAT_ABS '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_abs($3, $5);
  }
| TK_FLOAT_DIV '(' var_float_expr ',' var_float_expr ',' var_float_expr ')'
  {
    parser->float_div($3, $5, $7);
  }
| TK_FLOAT_ACOS '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_acos($3, $5);
  }
| TK_FLOAT_ASIN '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_asin($3, $5);
  }
| TK_FLOAT_ATAN '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_atan($3, $5);
  }
| TK_FLOAT_COS '(' var_float_expr ',' var_float_expr')'
  {
    parser->float_cos($3, $5);
  }
| TK_FLOAT_COSH '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_cosh($3, $5);
  }
| TK_FLOAT_EXP '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_exp($3, $5);
  }
| TK_FLOAT_LN '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_ln($3, $5);
  }
| TK_FLOAT_LOG10 '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_log10($3, $5);
  }
| TK_FLOAT_LOG2 '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_log2($3, $5);
  }
| TK_FLOAT_SQRT '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_sqrt($3, $5);
  }
| TK_FLOAT_SIN '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_sin($3, $5);
  }
| TK_FLOAT_SINH '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_sinh($3, $5);
  }
| TK_FLOAT_TAN '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_tan($3, $5);
  }
| TK_FLOAT_TANH '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_tanh($3, $5);
  }
| TK_FLOAT_EQ '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_eq($3, $5);
  }
| TK_FLOAT_EQ_REIF '(' var_float_expr ',' var_float_expr ',' var_bool_expr ')'
  {
    parser->float_eq_reif($3, $5, $7);
  }
| TK_FLOAT_LE '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_le($3, $5);
  }
| TK_FLOAT_LE_REIF '(' var_float_expr ',' var_float_expr ',' var_bool_expr ')'
  {
    parser->float_le_reif($3, $5, $7);
  }
| TK_FLOAT_LIN_EQ '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ')'
  {
    parser->float_lin_eq(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LIN_EQ_REIF '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ',' var_bool_expr ')'
  {
    parser->float_lin_eq_reif(*($3->termlist_), *($5->termlist_), $7, $9);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LIN_LE '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ')'
  {
    parser->float_lin_le(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LIN_LE_REIF '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ',' var_bool_expr')'
  {
    parser->float_lin_le_reif(*($3->termlist_), *($5->termlist_), $7, $9);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LIN_LT '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ')'
  {
    parser->float_lin_lt(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LIN_LT_REIF '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ',' var_bool_expr ')'
  {
    parser->float_lin_lt_reif(*($3->termlist_), *($5->termlist_), $7, $9);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LIN_NE '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ')'
  {
    parser->float_lin_ne(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LIN_NE_REIF '(' array_par_float_expr ',' array_var_float_expr ',' par_float_expr ',' var_bool_expr ')'
  {
    parser->float_lin_ne_reif(*($3->termlist_), *($5->termlist_), $7, $9);
    delete $3;
    delete $5;
  }
| TK_FLOAT_LT '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_lt($3, $5);
  }
| TK_FLOAT_LT_REIF '(' var_float_expr ',' var_float_expr ',' var_bool_expr ')'
  {
    parser->float_lt_reif($3, $5, $7);
  }
| TK_FLOAT_MAX '(' var_float_expr ',' var_float_expr ',' var_float_expr ')'
  {
    parser->float_max($3, $5, $7);
  }
| TK_FLOAT_MIN '(' var_float_expr ',' var_float_expr ',' var_float_expr ')'
  {
    parser->float_min($3, $5, $7);
  }
| TK_FLOAT_NE '(' var_float_expr ',' var_float_expr ')'
  {
    parser->float_ne($3, $5);
  }
| TK_FLOAT_NE_REIF '(' var_float_expr ',' var_float_expr ',' var_bool_expr ')'
  {
    parser->float_ne_reif($3, $5, $7);
  }
| TK_FLOAT_PLUS '(' var_float_expr ',' var_float_expr ',' var_float_expr ')'
  {
    parser->float_plus($3, $5, $7);
  }
| TK_FLOAT_TIMES '(' var_float_expr ',' var_float_expr ',' var_float_expr ')'
  {
    parser->float_times($3, $5, $7);
  }
| TK_INT_ABS '(' var_int_expr ',' var_int_expr ')'
  {
    parser->int_abs($3, $5);
  }
| TK_INT_DIV '(' var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->int_div($3, $5, $7);
  }
| TK_INT_EQ '(' var_int_expr ',' var_int_expr ')'
  {
    parser->int_eq($3, $5);
  }
| TK_INT_EQ_REIF '(' var_int_expr ',' var_int_expr ',' var_bool_expr ')'
  {
    parser->int_eq_reif($3, $5, $7);
  }
| TK_INT_LE '(' var_int_expr ',' var_int_expr ')'
  {
    parser->int_le($3, $5);
  }
| TK_INT_LE_REIF '(' var_int_expr ',' var_int_expr ',' var_bool_expr ')'
  {
    parser->int_le_reif($3, $5, $7);
  }
| TK_INT_LIN_EQ '(' array_par_int_expr ',' array_var_int_expr ',' par_int_expr ')'
  {
    parser->int_lin_eq(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_INT_LIN_EQ_REIF '(' array_par_int_expr ',' array_var_int_expr ',' par_int_expr ',' var_bool_expr ')'
  {
    parser->int_lin_eq_reif(*($3->termlist_), *($5->termlist_), $7, $9);
    delete $3;
    delete $5;
  }
| TK_INT_LIN_LE '(' array_par_int_expr ',' array_var_int_expr ',' par_int_expr ')'
  {
    parser->int_lin_le(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_INT_LIN_LE_REIF '(' array_par_int_expr ',' array_var_int_expr ',' par_int_expr ',' var_bool_expr ')'
  {
    parser->int_lin_le_reif(*($3->termlist_), *($5->termlist_), $7, $9);
    delete $3;
    delete $5;
  }
| TK_INT_LIN_NE '(' array_par_int_expr ',' array_var_int_expr ',' par_int_expr ')'
  {
    parser->int_lin_ne(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
| TK_INT_LIN_NE_REIF '(' array_par_int_expr ',' array_var_int_expr ',' par_int_expr ',' var_bool_expr ')'
  {
    parser->int_lin_ne_reif(*($3->termlist_), *($5->termlist_), $7, $9);
    delete $3;
    delete $5;
  }
| TK_INT_LT '(' var_int_expr ',' var_int_expr ')'
  {
    parser->int_lt($3, $5);
  }
| TK_INT_LT_REIF '(' var_int_expr ',' var_int_expr ',' var_bool_expr ')'
  {
    parser->int_lt_reif($3, $5, $7);
  }
| TK_INT_MAX '(' var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->int_max($3, $5, $7);
  }
| TK_INT_MIN '(' var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->int_min($3, $5, $7);
  }
| TK_INT_MOD '(' var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->int_mod($3, $5, $7);
  }
| TK_INT_NE '(' var_int_expr ',' var_int_expr ')'
  {
    parser->int_ne($3, $5);
  }
| TK_INT_NE_REIF '(' var_int_expr ',' var_int_expr ',' var_bool_expr ')'
  {
    parser->int_ne_reif($3, $5, $7);
  }
| TK_INT_PLUS '(' var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->int_plus($3, $5, $7);
  }
| TK_INT_TIMES '(' var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->int_times($3, $5, $7);
  }
| TK_INT2FLOAT '(' var_int_expr ',' var_float_expr ')'
  {
    parser->int2float($3, $5);
  }
| TK_ARRAY_SET_ELEMENT '(' var_int_expr ',' set_array_literal ',' set_literal ')'
  {
    parser->array_set_element($3, $5->set_list_, $7->set_);
    delete $5;
    delete $7;
  }
| TK_ARRAY_VAR_SET_ELEMENT '(' var_int_expr ',' set_array_literal ',' set_literal ')'
  {
    parser->array_var_set_element($3, $5->set_list_, $7->set_);
    delete $5;
    delete $7;
  }
| TK_SET_CARD '(' set_literal ',' var_int_expr ')'
  {
    parser->set_card($3->set_, $5);
  }
| TK_SET_DIFF '(' set_literal ',' set_literal ',' set_literal ')'
  {
    parser->set_diff($3->set_, $5->set_, $7->set_);
    delete $3;
    delete $5;
    delete $7;
  }
| TK_SET_EQ '(' set_literal ',' set_literal ')'
  {
    parser->set_eq($3->set_, $5->set_);
    delete $3;
    delete $5;
  }
| TK_SET_EQ_REIF '(' set_literal ',' set_literal ',' var_bool_expr ')'
  {
    parser->set_eq_reif($3->set_, $5->set_, $7);
    delete $3;
    delete $5;
  }
| TK_SET_IN '(' var_int_expr ',' set_literal ')'
  {
    parser->set_in($3, $5->set_);
    delete $5;
  }
| TK_SET_IN_REIF '(' var_int_expr ',' set_literal ',' var_bool_expr ')'
  {
    parser->set_in_reif($3, $5->set_, $7);
    delete $5;
  }
| TK_SET_INTERSECT '(' set_literal ',' set_literal ',' set_literal ')'
  {
    parser->set_intersect($3->set_, $5->set_, $7->set_);
    delete $3;
    delete $5;
    delete $7;
  }
| TK_SET_LE '(' set_literal ',' set_literal ')'
  {
    parser->set_le($3->set_, $5->set_);
    delete $3;
    delete $5;
  }
| TK_SET_LT '(' set_literal ',' set_literal ')'
  {
    parser->set_lt($3->set_, $5->set_);
    delete $3;
    delete $5;
  }
| TK_SET_NE '(' set_literal ',' set_literal ')'
  {
    parser->set_ne($3->set_, $5->set_);
    delete $3;
    delete $5;
  }
| TK_SET_NE_REIF '(' set_literal ',' set_literal ',' var_bool_expr ')'
  {
    parser->set_ne_reif($3->set_, $5->set_, $7);
    delete $3;
    delete $5;
  }
| TK_SET_SUBSET '(' set_literal ',' set_literal ')'
  {
    parser->set_subset($3->set_, $5->set_);
    delete $3;
    delete $5;
  }
| TK_SET_SUBSET_REIF '(' set_literal ',' set_literal ',' var_bool_expr ')'
  {
    parser->set_subset_reif($3->set_, $5->set_, $7);
    delete $3;
    delete $5;
  }
| TK_SET_SYMDIFF '(' set_literal ',' set_literal ',' set_literal ')'
  {
    parser->set_symdiff($3->set_, $5->set_, $7->set_);
    delete $3;
    delete $5;
    delete $7;
  }
| TK_SET_UNION '(' set_literal ',' set_literal ',' set_literal ')'
  {
    parser->set_union($3->set_, $5->set_, $7->set_);
    delete $3;
    delete $5;
    delete $7;
  }
| global_constraints
  {
  }
| IDENT '(' ignored_exprs ')'
  {
    std::stringstream ss;
    ss << "constraint '" << $1
       << "' is not supported.";
    parser->handle_error(ss.str().c_str());
  }
;

solve_item :
  TK_SOLVE ignored_annotations solve_kind
  {
    //std::cout<<"Solve maxiize\n";
    //parser->check_sat();
  }
;

solve_kind :
  TK_SATISFY
  {
  }
| objectives
  {
  }
;

objectives :
  objectives ',' objective
  {
  }
| objective
  {
  }
;

objective:
  TK_MINIMIZE var_num_expr
  {
    parser->push_objective(FlatZincAbstractParser::MINIMIZE, $2);
  }
| TK_MAXIMIZE var_num_expr
  {
    parser->push_objective(FlatZincAbstractParser::MAXIMIZE, $2);
  }
;

//---------------------------------------------------------------------------
// Predicate parameters: ignored
//---------------------------------------------------------------------------

pred_decl_args :
  pred_decl_arg ',' pred_decl_args { }
| pred_decl_arg { }
;

pred_decl_arg :
  bool_ti_expr_tail ':' IDENT  { delete $1; MSAT_SFREE($3); }
| int_ti_expr_tail ':' IDENT   { delete $1; MSAT_SFREE($3); }
| float_ti_expr_tail ':' IDENT { delete $1; MSAT_SFREE($3); }
| TK_VAR bool_ti_expr_tail ':' IDENT  { delete $2; MSAT_SFREE($4); }
| TK_VAR int_ti_expr_tail ':' IDENT   { delete $2; MSAT_SFREE($4); }
| TK_VAR float_ti_expr_tail ':' IDENT { delete $2; MSAT_SFREE($4); }
| TK_SET TK_OF int_ti_expr_tail ':' IDENT  { delete $3; MSAT_SFREE($5); }
| TK_VAR TK_SET TK_OF int_ti_expr_tail ':' IDENT { delete $4; MSAT_SFREE($6); }
| TK_ARRAY '[' pred_arg_array_index ']' TK_OF  pred_arg_array_tail ':' IDENT
  {
    MSAT_SFREE($8);
  }
;

pred_arg_array_index :
  TK_INT { }
| INT_LITERAL TK_DOTDOT INT_LITERAL { MSAT_SFREE($1); MSAT_SFREE($3); }
;

pred_arg_array_tail :
  bool_ti_expr_tail { delete $1; }
| int_ti_expr_tail { delete $1; }
| float_ti_expr_tail { delete $1; }
| TK_VAR bool_ti_expr_tail { delete $2; }
| TK_VAR int_ti_expr_tail { delete $2; }
| TK_VAR float_ti_expr_tail { delete $2; }
| TK_SET TK_OF int_ti_expr_tail { delete $3; }
| TK_VAR TK_SET TK_OF int_ti_expr_tail { delete $4; }
;

//---------------------------------------------------------------------------
// Type-Inst Expression Tails
//---------------------------------------------------------------------------

bool_ti_expr_tail :
  TK_BOOL
  {
    $$ = new NumFlatZincDomain(FZN_BOOL);
  }
;

int_ti_expr_tail :
  TK_INT
  {
    $$ = new NumFlatZincDomain(FZN_INT);
  }
| INT_LITERAL TK_DOTDOT INT_LITERAL
  {
    $$ = new NumFlatZincDomain(FZN_INT,
                               number_from_str($1),
                               number_from_str($3));
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| '{' num_literals '}'
  {
    $$ = new NumFlatZincDomain(FZN_INT, (*$2));
    delete $2;
  }
;

num_literals :
  INT_LITERAL ',' num_literals
  {
    $3->push_back(number_from_str($1));
    $$ = $3;
    MSAT_SFREE($1);
  }
| INT_LITERAL
  {
    $$ = new std::vector<Number>();
    $$->push_back(number_from_str($1));
    MSAT_SFREE($1);
  }
;

float_ti_expr_tail :
  TK_FLOAT
  {
    $$ = new NumFlatZincDomain(FZN_FLOAT);
  }
| FLOAT_LITERAL TK_DOTDOT FLOAT_LITERAL
  {
    $$ = new NumFlatZincDomain(FZN_FLOAT,
                               number_from_str($1),
                               number_from_str($3));
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

//---------------------------------------------------------------------------
// Term Expressions
//---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // TYPED EXPR: BOOL
    //---------------------------------------------------------------------------

par_bool_expr :
  bool_literal { $$ = $1; }
| IDENT { $$ = parser->get_var_literal(false, FZN_BOOL, $1); MSAT_SFREE($1); }
| UNDERSCORE_IDENT { $$ = parser->get_var_literal(false, FZN_BOOL, $1); MSAT_SFREE($1); }
| IDENT '[' INT_LITERAL ']' {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(false, FZN_BOOL, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(false, FZN_BOOL, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

var_bool_expr :
  bool_literal { $$ = $1; }
| IDENT { $$ = parser->get_var_literal(true, FZN_BOOL, $1); MSAT_SFREE($1); }
| UNDERSCORE_IDENT { $$ = parser->get_var_literal(true, FZN_BOOL, $1); MSAT_SFREE($1); }
| IDENT '[' INT_LITERAL ']' {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_BOOL, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_BOOL, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

bool_literal :
  TK_FALSE
  {
    $$ = parser->get_false();
  }
| TK_TRUE
  {
    $$ = parser->get_true();
  }

    //---------------------------------------------------------------------------
    // TYPED EXPR: ARRAY BOOL
    //---------------------------------------------------------------------------

array_par_bool_expr :
  array_par_bool_literal
  {
    $$ = $1;
  }
| IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(false, FZN_BOOL, $1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(false, FZN_BOOL, $1);
    MSAT_SFREE($1);
  }
;

array_par_bool_literal :
  '[' array_par_bool_elements ']'
  {
    $$ = $2;
  }
| '[' ']'
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
  }
;

array_par_bool_elements :
  array_par_bool_elements ',' par_bool_expr
  {
    $1->termlist_->push_back($3);
    $$ = $1;
  }
| par_bool_expr
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
    $$->termlist_->push_back($1);
  }
;

array_var_bool_expr :
  array_var_bool_literal
  {
    $$ = $1;
  }
| IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(true, FZN_BOOL, $1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(true, FZN_BOOL, $1);
    MSAT_SFREE($1);
  }
;

array_var_bool_literal :
  '[' array_var_bool_elements ']'
  {
    $$ = $2;
  }
| '[' ']'
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
  }
;

array_var_bool_elements :
  array_var_bool_elements ',' var_bool_expr
  {
    $1->termlist_->push_back($3);
    $$ = $1;
  }
| var_bool_expr
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
    $$->termlist_->push_back($1);
  }
;

    //---------------------------------------------------------------------------
    // TYPED EXPR: INT
    //---------------------------------------------------------------------------

par_int_expr :
  int_literal { $$ = $1; }
| IDENT { $$ = parser->get_var_literal(false, FZN_INT, $1); MSAT_SFREE($1); }
| UNDERSCORE_IDENT { $$ = parser->get_var_literal(false, FZN_INT, $1); MSAT_SFREE($1); }
| IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(false, FZN_INT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(false, FZN_INT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

var_int_expr :
  int_literal { $$ = $1; }
| IDENT { $$ = parser->get_var_literal(true, FZN_INT, $1); MSAT_SFREE($1); }
| UNDERSCORE_IDENT { $$ = parser->get_var_literal(true, FZN_INT, $1); MSAT_SFREE($1); }
| IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_INT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_INT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

int_literal :
  INT_LITERAL
  {
    $$ = parser->get_int_number($1);
    MSAT_SFREE($1);
  }
;

    //---------------------------------------------------------------------------
    // TYPED EXPR: ARRAY INT
    //---------------------------------------------------------------------------

array_par_int_expr :
  array_par_int_literal
  {
    $$ = $1;
  }
| IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(false, FZN_INT, $1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(false, FZN_INT, $1);
    MSAT_SFREE($1);
  }
;

array_par_int_literal :
  '[' array_par_int_elements ']'
  {
    $$ = $2;
  }
| '[' ']'
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
  }
;

array_par_int_elements :
  array_par_int_elements ',' par_int_expr
  {
    $1->termlist_->push_back($3);
    $$ = $1;
  }
| par_int_expr
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
    $$->termlist_->push_back($1);
  }
;

array_var_int_expr :
  array_var_int_literal
  {
    $$ = $1;
  }
| IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(true, FZN_INT, $1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(true, FZN_INT, $1);
    MSAT_SFREE($1);
  }
;

array_var_int_literal :
  '[' array_var_int_elements ']'
  {
    $$ = $2;
  }
| '[' ']'
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
  }
;

array_var_int_elements :
  array_var_int_elements ',' var_int_expr
  {
    $1->termlist_->push_back($3);
    $$ = $1;
  }
| var_int_expr
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
    $$->termlist_->push_back($1);
  }
;

    //---------------------------------------------------------------------------
    // TYPED EXPR: FLOAT
    //---------------------------------------------------------------------------

par_float_expr:
  float_literal { $$ = $1; }
| IDENT { $$ = parser->get_var_literal(false, FZN_FLOAT, $1); MSAT_SFREE($1); }
| UNDERSCORE_IDENT { $$ = parser->get_var_literal(false, FZN_FLOAT, $1); MSAT_SFREE($1); }
| IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(false, FZN_FLOAT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(false, FZN_FLOAT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

var_float_expr:
  float_literal { $$ = $1; }
| IDENT { $$ = parser->get_var_literal(true, FZN_FLOAT, $1); MSAT_SFREE($1); }
| UNDERSCORE_IDENT { $$ = parser->get_var_literal(true, FZN_FLOAT, $1); MSAT_SFREE($1); }
| IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_FLOAT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_FLOAT, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

float_literal :
  FLOAT_LITERAL
  {
    $$ = parser->get_float_number($1);
    MSAT_SFREE($1);
  }
;

    //---------------------------------------------------------------------------
    // TYPED EXPR: ARRAY FLOAT
    //---------------------------------------------------------------------------

array_par_float_expr :
  array_par_float_literal
  {
    $$ = $1;
  }
| IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(false, FZN_FLOAT, $1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(false, FZN_FLOAT, $1);
    MSAT_SFREE($1);
  }
;

array_par_float_literal :
  '[' array_par_float_elements ']'
  {
    $$ = $2;
  }
| '[' ']'
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
  }
;

array_par_float_elements :
  array_par_float_elements ',' par_float_expr
  {
    $1->termlist_->push_back($3);
    $$ = $1;
  }
| par_float_expr
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
    $$->termlist_->push_back($1);
  }
;

array_var_float_expr :
  array_var_float_literal
  {
    $$ = $1;
  }
| IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(true, FZN_FLOAT, $1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->termlist_ = parser->get_array_var_literal(true, FZN_FLOAT, $1);
    MSAT_SFREE($1);
  }
;

array_var_float_literal :
  '[' array_var_float_elements ']'
  {
    $$ = $2;
  }
| '[' ']'
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
  }
;

array_var_float_elements :
  array_var_float_elements ',' var_float_expr
  {
    $1->termlist_->push_back($3);
    $$ = $1;
  }
| var_float_expr
  {
    $$ = new FznNode();
    $$->termlist_.reset(new TermList());
    $$->termlist_->push_back($1);
  }
;

    //---------------------------------------------------------------------------
    // TYPED EXPR: NUMERIC
    //---------------------------------------------------------------------------

var_num_expr:
  int_literal { $$ = $1; }
| float_literal { $$ = $1; }
| IDENT { $$ = parser->get_var_literal(true, FZN_NUMERIC, $1); MSAT_SFREE($1); }
| UNDERSCORE_IDENT { $$ = parser->get_var_literal(true, FZN_NUMERIC, $1); MSAT_SFREE($1); }
| IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_NUMERIC, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = parser->get_var_literal(true, FZN_NUMERIC, $1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
;

//---------------------------------------------------------------------------
// Set Expressions
//---------------------------------------------------------------------------

set_literal:
  '{' set_elements '}'
  {
    $$ = $2;
  }
| INT_LITERAL TK_DOTDOT INT_LITERAL
  {
    $$ = new FznNode();
    FlatZincSet *set = new FlatZincSet(true);
    $$->set_.reset(set);
    set->add_set_elements(NumInterval(number_from_str($1),
                                      number_from_str($3)));
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
|  IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = new FznNode();
    $$->set_ = parser->get_set_literals($1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    size_t index = parser_atoi(parser, $3);
    $$ = new FznNode();
    $$->set_ = parser->get_set_literals($1, index);
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| IDENT
  {
    $$ = new FznNode();
    $$->set_ = parser->get_set_literals($1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->set_ = parser->get_set_literals($1);
    MSAT_SFREE($1);
  }
;

set_elements :
  set_elements ',' INT_LITERAL
  {
    $$ = $1;
    $$->set_->add_set_elements(NumInterval(number_from_str($3)));
    MSAT_SFREE($3);
  }
| INT_LITERAL
  {
    $$ = new FznNode();
    $$->set_.reset(new FlatZincSet(true));
    $$->set_->add_set_elements(NumInterval(number_from_str($1)));
    MSAT_SFREE($1);
  }
|
  {
    $$ = new FznNode();
    $$->set_.reset(new FlatZincSet(true));
  }
;

set_array_literal :
  '[' set_array_elements ']'
  {
    $$ = $2;
  }
| IDENT
  {
    $$ = new FznNode();
    $$->set_list_ = parser->get_array_set_literals($1);
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    $$ = new FznNode();
    $$->set_list_ = parser->get_array_set_literals($1);
    MSAT_SFREE($1);
  }
;

set_array_elements :
  set_array_elements ',' set_literal
  {
    $$ = $1;
    $$->set_list_->push_back($3->set_);
    delete $3;
  }
| set_literal
  {
    $$ = new FznNode();
    $$->set_list_.reset(new FznSetList());
    $$->set_list_->push_back($1->set_);
    delete $1;
  }
|
  {
    $$ = new FznNode();
    $$->set_list_.reset(new FznSetList());
  }
;

//---------------------------------------------------------------------------
// generic ignored_exprs: ignored
//---------------------------------------------------------------------------

ignored_exprs:
  ignored_expr ',' ignored_exprs
  {
  }
| ignored_expr
  {
  }
;

ignored_expr:
  TK_FALSE
  {
  }
| TK_TRUE
  {
  }
| INT_LITERAL
  {
    MSAT_SFREE($1);
  }
| FLOAT_LITERAL
  {
    MSAT_SFREE($1);
  }
| STRING_LITERAL
  {
    MSAT_SFREE($1);
  }
| '{' ignored_exprs '}'
  {
  }
| '{' '}'
  {
  }
| INT_LITERAL TK_DOTDOT INT_LITERAL
  {
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| '[' ignored_exprs ']'
  {
  }
| '[' ']'
  {
  }
| IDENT '[' INT_LITERAL ']'
  {
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| UNDERSCORE_IDENT '[' INT_LITERAL ']'
  {
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
| IDENT
  {
    MSAT_SFREE($1);
  }
| UNDERSCORE_IDENT
  {
    MSAT_SFREE($1);
  }
| IDENT '(' ignored_exprs ')'
  {
    MSAT_SFREE($1);
  }
;

//---------------------------------------------------------------------------
// Annotations
//---------------------------------------------------------------------------

annotations:
  annotations TK_COLONCOLON TK_OUTPUT_VAR
  {
    $1->set_output_var();
    $$ = $1;
  }
| annotations TK_COLONCOLON TK_OUTPUT_ARRAY '(' '[' shape_list ']' ')'
  {
    $1->set_output_array(*$6);
    $$ = $1;
    delete $6;
  }
| annotations TK_COLONCOLON IDENT
  {
    MSAT_SFREE($3);
    $$ = $1;
  }
| annotations TK_COLONCOLON IDENT '(' ignored_exprs ')'
  {
    MSAT_SFREE($3);
    $$ = $1;
  }
| /* empty */
  {
    $$ = new FlatZincAnnotation();
  }
;

shape_list :
  shape_list ',' INT_LITERAL TK_DOTDOT INT_LITERAL
  {
    $1->push_back(parser_atoi(parser,$3));
    $1->push_back(parser_atoi(parser,$5));
    MSAT_SFREE($3);
    MSAT_SFREE($5);
    $$ = $1;
  }
| INT_LITERAL TK_DOTDOT INT_LITERAL
  {
    $$ = new std::vector<int64_t>();
    $$->push_back(parser_atoi(parser,$1));
    $$->push_back(parser_atoi(parser,$3));
    MSAT_SFREE($1);
    MSAT_SFREE($3);
  }
|
  {
    $$ = new std::vector<int64_t>();
  }
;

//---------------------------------------------------------------------------
// Ignored Annotations
//---------------------------------------------------------------------------

ignored_annotations:
  ignored_annotations TK_COLONCOLON TK_OUTPUT_VAR { }
| ignored_annotations TK_COLONCOLON TK_OUTPUT_ARRAY '(' '[' ignored_shape_list ']' ')' { }
| ignored_annotations TK_COLONCOLON IDENT { MSAT_SFREE($3); }
| ignored_annotations TK_COLONCOLON IDENT '(' ignored_exprs ')' { MSAT_SFREE($3); }
| { }
;

ignored_shape_list :
  ignored_shape_list ',' ignored_shape { }
| ignored_shape { }
| { }
;

ignored_shape:
  INT_LITERAL TK_DOTDOT INT_LITERAL { MSAT_SFREE($1); MSAT_SFREE($3); }
;

//---------------------------------------------------------------------------
// Global Constraints
//---------------------------------------------------------------------------

global_constraints:
  all_different
| disjoint
| disjunctive
| all_equal
| among
| maximum
| minimum
| maximum_array
| minimum_array
| maximum_arg
| minimum_arg
| at_least
| exactly
| at_most
| bin_packing
| element
| comparison_rel_array
| count
| decreasing
| increasing
| diffn
| distribute
| geost
| global_cardinality
| int_set_channel
| inverse
| member
| link_set_to_booleans
| nvalue
| range
| bool_clause_reif
| float_dom
| roots
| sum_pred
| symmetric_all_different
| value_precede
  {
    // supported
  }
;

all_different:
  TK_ALLDIFFERENT_EXCEPT_0 '(' array_var_int_expr ')'
  {
    parser->all_different_except_0(*($3->termlist_));
    delete $3;
  }
| TK_ALL_DIFFERENT_INT '(' array_var_int_expr ')'
  {
    parser->all_different(*($3->termlist_));
    delete $3;
  }
| TK_ALL_DIFFERENT_SET '(' set_array_literal ')'
  {
    parser->all_different($3->set_list_);
    delete $3;
  }
;

disjoint:
  TK_DISJOINT '(' set_literal ',' set_literal ')'
  {
    parser->disjoint($3->set_, $5->set_);
    delete $3;
    delete $5;
  }
| TK_ALL_DISJOINT '(' set_array_literal ')'
  {
    parser->all_disjoint($3->set_list_);
    delete $3;
  }
;

disjunctive:
  TK_DISJUNCTIVE '(' array_var_int_expr ',' array_var_int_expr ')'
  {
    parser->disjunctive(*($3->termlist_), *($5->termlist_));
    delete $3;
    delete $5;
  }
| TK_DISJUNCTIVE_STRICT '(' array_var_int_expr ',' array_var_int_expr ')'
  {
    parser->disjunctive_strict(*($3->termlist_), *($5->termlist_));
    delete $3;
    delete $5;
  }
;

all_equal:
  TK_ALL_EQUAL_INT '(' array_var_int_expr ')'
  {
    parser->all_equal(*($3->termlist_));
    delete $3;
  }
| TK_ALL_EQUAL_SET '(' set_array_literal ')'
  {
    parser->all_equal($3->set_list_);
    delete $3;
  }
;

among:
  TK_AMONG '(' var_int_expr ',' array_var_int_expr ',' set_literal ')'
  {
    parser->among($3, *($5->termlist_), $7->set_);
    delete $5;
    delete $7;
  }
;

maximum:
  TK_MAXIMUM_FLOAT '(' var_float_expr ',' array_var_float_expr ')'
  {
    parser->array_max($3, *($5->termlist_));
    delete $5;
  }
| TK_MAXIMUM_INT '(' var_int_expr ',' array_var_float_expr ')'
  {
    parser->array_max($3, *($5->termlist_));
    delete $5;
  }
;

minimum:
  TK_MINIMUM_FLOAT '(' var_float_expr ',' array_var_float_expr ')'
  {
    parser->array_min($3, *($5->termlist_));
    delete $5;
  }
| TK_MINIMUM_INT '(' var_int_expr ',' array_var_int_expr ')'
  {
    parser->array_min($3, *($5->termlist_));
    delete $5;
  }
;

maximum_array:
  TK_ARRAY_FLOAT_MAXIMUM '(' var_float_expr ',' array_var_float_expr ')'
  {
    parser->array_max($3, *($5->termlist_));
    delete $5;
  }
| TK_ARRAY_INT_MAXIMUM '(' var_int_expr ',' array_var_int_expr ')'
  {
    parser->array_max($3, *($5->termlist_));
    delete $5;
  }
;

minimum_array:
  TK_ARRAY_FLOAT_MINIMUM '(' var_float_expr ',' array_var_float_expr ')'
  {
    parser->array_min($3, *($5->termlist_));
    delete $5;
  }
| TK_ARRAY_INT_MINIMUM '(' var_int_expr ',' array_var_int_expr ')'
  {
    parser->array_min($3, *($5->termlist_));
    delete $5;
  }
;

// TODO: bool version is listed in doc-2.3.1
maximum_arg:
  TK_MAXIMUM_ARG_INT '(' array_var_int_expr ',' var_int_expr
                     ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($7);
    Number end   = number_from_str($9);
    NumInterval x_ival(start, end);

    parser->maximum_arg(*($3->termlist_), $5, x_ival);
    delete $3;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
  }
| TK_MAXIMUM_ARG_FLOAT '(' array_var_float_expr ',' var_int_expr
                       ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($7);
    Number end   = number_from_str($9);
    NumInterval x_ival(start, end);

    parser->maximum_arg(*($3->termlist_), $5, x_ival);
    delete $3;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
  }
;

// TODO: bool version is listed in doc-2.3.1
minimum_arg:
  TK_MINIMUM_ARG_INT '(' array_var_int_expr ',' var_int_expr
                     ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($7);
    Number end   = number_from_str($9);
    NumInterval x_ival(start, end);

    parser->minimum_arg(*($3->termlist_), $5, x_ival);
    delete $3;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
  }
| TK_MINIMUM_ARG_FLOAT '(' array_var_float_expr ',' var_int_expr
                       ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($7);
    Number end   = number_from_str($9);
    NumInterval x_ival(start, end);

    parser->minimum_arg(*($3->termlist_), $5, x_ival);
    delete $3;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
  }
;

at_least:
  TK_AT_LEAST_INT '(' par_int_expr ',' array_var_int_expr ',' par_int_expr ')'
  {
    parser->count_geq($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_AT_LEAST_SET '(' par_int_expr ',' set_array_literal ',' set_literal ')'
  {
    parser->at_least_set($3, $5->set_list_, $7->set_);
    delete $5;
    delete $7;
  }
;

exactly:
  TK_EXACTLY_INT '(' par_int_expr ',' array_var_int_expr ',' par_int_expr ')'
  {
    parser->count_eq($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_EXACTLY_SET '(' par_int_expr ',' set_array_literal ',' set_literal ')'
  {
    parser->exactly_set($3, $5->set_list_, $7->set_);
    delete $5;
    delete $7;
  }
;

at_most:
  TK_AT_MOST_INT '(' par_int_expr ',' array_var_int_expr ',' par_int_expr ')'
  {
    parser->count_leq($3, *($5->termlist_), $7);
    delete $5;
  }
| TK_AT_MOST_SET '(' par_int_expr ',' set_array_literal ',' set_literal ')'
  {
    parser->at_least_set($3, $5->set_list_, $7->set_);
    delete $5;
    delete $7;
  }
| TK_ATMOST1 '(' set_array_literal ')'
  {
    parser->at_most_1($3->set_list_);
    delete $3;
  }
;

bin_packing:
  TK_BIN_PACKING_CAPA '(' array_par_int_expr ',' array_var_int_expr ',' array_par_int_expr
                      ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($9);
    Number end   = number_from_str($11);
    NumInterval c_ival(start, end);

    parser->bin_packing_capa(*($3->termlist_), *($5->termlist_), *($7->termlist_), c_ival);
    delete $3;
    delete $5;
    delete $7;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
| TK_BIN_PACKING_LOAD '(' array_var_int_expr ',' array_var_int_expr ',' array_par_int_expr
                      ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($9);
    Number end   = number_from_str($11);
    NumInterval load_ival(start, end);

    parser->bin_packing_load(*($3->termlist_), *($5->termlist_), *($7->termlist_), load_ival);
    delete $3;
    delete $5;
    delete $7;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
| TK_BIN_PACKING '(' par_int_expr ',' array_var_int_expr ',' array_par_int_expr ')'
  {
    parser->bin_packing($3, *($5->termlist_), *($7->termlist_));
    delete $5;
    delete $7;
  }
;

element:
  TK_ELEMENT_BOOL '(' var_int_expr ',' array_var_bool_expr ',' var_bool_expr
                  ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($9);
    Number end   = number_from_str($11);
    NumInterval x_ival(start, end);
    parser->element($3, *($5->termlist_), $7, x_ival);
    delete $5;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
| TK_ELEMENT_FLOAT '(' var_int_expr ',' array_var_float_expr ',' var_float_expr
                  ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($9);
    Number end   = number_from_str($11);
    NumInterval x_ival(start, end);
    parser->element($3, *($5->termlist_), $7, x_ival);
    delete $5;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
| TK_ELEMENT_INT '(' var_int_expr ',' array_var_int_expr ',' var_int_expr
                  ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($9);
    Number end   = number_from_str($11);
    NumInterval x_ival(start, end);
    parser->element($3, *($5->termlist_), $7, x_ival);
    delete $5;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
| TK_ELEMENT_SET '(' var_int_expr ',' set_array_literal ',' set_literal
                  ',' INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($9);
    Number end   = number_from_str($11);
    NumInterval x_ival(start, end);
    parser->element($3, $5->set_list_, $7->set_, x_ival);
    delete $5;
    delete $7;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
;

comparison_rel_array:
  TK_COMPARISON_REL_ARRAY '(' array_var_int_expr ',' var_int_expr ')'
  {
    parser->comparison_rel_array(*($3->termlist_), $5);
    delete $3;
  }
;

count:
  TK_COUNT_EQ '(' array_var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->count_eq($7, *($3->termlist_), $5);
    delete $3;
  }
| TK_COUNT_GEQ '(' array_var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->count_geq($7, *($3->termlist_), $5);
    delete $3;
  }
| TK_COUNT_GT '(' array_var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->count_gt($7, *($3->termlist_), $5);
    delete $3;
  }
| TK_COUNT_LEQ '(' array_var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->count_leq($7, *($3->termlist_), $5);
    delete $3;
  }
| TK_COUNT_LT '(' array_var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->count_lt($7, *($3->termlist_), $5);
    delete $3;
  }
| TK_COUNT_NEQ '(' array_var_int_expr ',' var_int_expr ',' var_int_expr ')'
  {
    parser->count_neq($7, *($3->termlist_), $5);
    delete $3;
  }
;

decreasing:
  TK_DECREASING_BOOL '(' array_var_bool_expr ')'
  {
    parser->decreasing(*($3->termlist_));
    delete $3;
  }
| TK_DECREASING_FLOAT '(' array_var_float_expr ')'
  {
    parser->decreasing(*($3->termlist_));
    delete $3;
  }
| TK_DECREASING_INT '(' array_var_int_expr ')'
  {
    parser->decreasing(*($3->termlist_));
    delete $3;
  }
| TK_DECREASING_SET '(' set_array_literal ')'
  {
    parser->decreasing($3->set_list_);
    delete $3;
  }
;

increasing:
  TK_INCREASING_BOOL '(' array_var_bool_expr ')'
  {
    parser->increasing(*($3->termlist_));
    delete $3;
  }
| TK_INCREASING_FLOAT '(' array_var_float_expr ')'
  {
    parser->increasing(*($3->termlist_));
    delete $3;
  }
| TK_INCREASING_INT '(' array_var_int_expr ')'
  {
    parser->increasing(*($3->termlist_));
    delete $3;
  }
| TK_INCREASING_SET '(' set_array_literal ')'
  {
    parser->increasing($3->set_list_);
    delete $3;
  }
;

diffn:
  TK_DIFFN '(' array_var_int_expr ',' array_var_int_expr ',' array_var_int_expr ',' array_var_int_expr ')'
  {
    parser->diffn(*($3->termlist_), *($5->termlist_), *($7->termlist_), *($9->termlist_));
    delete $3;
    delete $5;
    delete $7;
    delete $9;
  }
| TK_DIFFN_NONSTRICT '(' array_var_int_expr ',' array_var_int_expr ',' array_var_int_expr ',' array_var_int_expr ')'
  {
    parser->diffn_nonstrict(*($3->termlist_), *($5->termlist_), *($7->termlist_), *($9->termlist_));
    delete $3;
    delete $5;
    delete $7;
    delete $9;
  }
| TK_DIFFN_NONOVERLAP_K '(' array_var_int_expr ',' array_var_int_expr ',' array_var_int_expr ',' array_var_int_expr ')'
  {
    parser->diffn_nonoverlap_k(*($3->termlist_), *($5->termlist_), *($7->termlist_), *($9->termlist_));
    delete $3;
    delete $5;
    delete $7;
    delete $9;
  }
| TK_DIFFN_NONSTRICT_NONOVERLAP_K '(' array_var_int_expr ',' array_var_int_expr ','
                                      array_var_int_expr ',' array_var_int_expr ')'
  {
    parser->diffn_nonstrict_nonoverlap_k(*($3->termlist_), *($5->termlist_), *($7->termlist_), *($9->termlist_));
    delete $3;
    delete $5;
    delete $7;
    delete $9;
  }
;

distribute:
  TK_DISTRIBUTE '(' array_var_int_expr ',' array_var_int_expr ',' array_var_int_expr ')'
  {
    parser->distribute(*($3->termlist_), *($5->termlist_), *($7->termlist_));
    delete $3;
    delete $5;
    delete $7;
  }
;

geost:
  TK_GEOST_NONOVERLAP_K '(' array_var_int_expr ',' array_par_int_expr ','
                            array_var_int_expr ',' array_par_int_expr ')'
  {
    parser->geost_nonoverlap_k(*($3->termlist_), *($5->termlist_), *($7->termlist_), *($9->termlist_));
    delete $3;
    delete $5;
    delete $7;
    delete $9;
  }
;

global_cardinality:
 TK_GLOBAL_CARDINALITY '(' array_var_int_expr ',' array_par_int_expr ',' array_var_int_expr ')'
  {
    parser->global_cardinality(*($3->termlist_), *($5->termlist_), *($7->termlist_));
    delete $3;
    delete $5;
    delete $7;
  }
| TK_GLOBAL_CARDINALITY_CLOSED '(' array_var_int_expr ',' array_par_int_expr ',' array_var_int_expr ')'
  {
    parser->global_cardinality_closed(*($3->termlist_), *($5->termlist_), *($7->termlist_));
    delete $3;
    delete $5;
    delete $7;
  }
| TK_GLOBAL_CARDINALITY_LOW_UP '(' array_var_int_expr ',' array_par_int_expr ',' array_par_int_expr ',' array_par_int_expr ')'
  {
    parser->global_cardinality_low_up(*($3->termlist_), *($5->termlist_), *($7->termlist_), *($9->termlist_));
    delete $3;
    delete $5;
    delete $7;
    delete $9;
  }
| TK_GLOBAL_CARDINALITY_LOW_UP_CLOSED '(' array_var_int_expr ',' array_par_int_expr ',' array_par_int_expr ',' array_par_int_expr ')'
  {
    parser->global_cardinality_low_up_closed(*($3->termlist_), *($5->termlist_), *($7->termlist_), *($9->termlist_));
    delete $3;
    delete $5;
    delete $7;
    delete $9;
  }
;

int_set_channel:
  TK_INT_SET_CHANNEL '(' array_var_int_expr ',' set_array_literal ','
                         INT_LITERAL TK_DOTDOT INT_LITERAL ','
                         INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number xstart = number_from_str($7);
    Number xend   = number_from_str($9);
    Number ystart = number_from_str($11);
    Number yend   = number_from_str($13);

    NumInterval x_ival(xstart, xend);
    NumInterval y_ival(ystart, yend);

    parser->int_set_channel(*($3->termlist_), $5->set_list_, x_ival, y_ival);
    delete $3;
    delete $5;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
    MSAT_SFREE($11);
    MSAT_SFREE($13);
  }
;

inverse:
  TK_INVERSE '(' array_var_int_expr ',' array_var_int_expr ','
                 INT_LITERAL TK_DOTDOT INT_LITERAL ','
                 INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number fstart = number_from_str($7);
    Number fend   = number_from_str($9);
    Number invfstart = number_from_str($11);
    Number invfend   = number_from_str($13);

    NumInterval f_ival(fstart, fend);
    NumInterval invf_ival(invfstart, invfend);

    parser->inverse(*($3->termlist_), *($5->termlist_), f_ival, invf_ival);

    delete $3;
    delete $5;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
    MSAT_SFREE($11);
    MSAT_SFREE($13);
  }
| TK_INVERSE_SET '(' set_array_literal ',' set_array_literal ','
                 INT_LITERAL TK_DOTDOT INT_LITERAL ','
                 INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number fstart = number_from_str($7);
    Number fend   = number_from_str($9);
    Number invfstart = number_from_str($11);
    Number invfend   = number_from_str($13);

    NumInterval f_ival(fstart, fend);
    NumInterval invf_ival(invfstart, invfend);

    parser->inverse_set($3->set_list_, $5->set_list_,
                        f_ival, invf_ival);
    delete $3;
    delete $5;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
    MSAT_SFREE($11);
    MSAT_SFREE($13);
  }
;

link_set_to_booleans:
  TK_LINK_SET_TO_BOOLEANS '(' set_literal ',' array_var_bool_expr ','
                         INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number bstart = number_from_str($7);
    Number bend   = number_from_str($9);

    NumInterval b_ival(bstart, bend);

    parser->link_set_to_booleans($3->set_, *($5->termlist_), b_ival);
    delete $3;
    delete $5;
    MSAT_SFREE($7);
    MSAT_SFREE($9);
  }
;

member:
  TK_MEMBER_BOOL '(' array_var_bool_expr ',' var_bool_expr ')'
  {
    parser->member(*($3->termlist_), $5);
    delete $3;
  }
| TK_MEMBER_FLOAT '(' array_var_float_expr ',' var_float_expr ')'
  {
    parser->member(*($3->termlist_), $5);
    delete $3;
  }
| TK_MEMBER_INT '(' array_var_int_expr ',' var_int_expr ')'
  {
    parser->member(*($3->termlist_), $5);
    delete $3;
  }
| TK_MEMBER_SET '(' set_array_literal ',' set_literal ')'
  {
    parser->member($3->set_list_, $5->set_);
    delete $3;
    delete $5;
  }
;

nvalue:
  TK_NVALUE '(' var_int_expr ',' array_var_int_expr ')'
  {
    parser->nvalue($3, *($5->termlist_));
    delete $5;
  }
;

range:
  TK_RANGE '(' array_var_int_expr ',' set_literal ',' set_literal ','
               INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number xstart = number_from_str($9);
    Number xend   = number_from_str($11);

    NumInterval x_ival(xstart, xend);

    parser->range(*($3->termlist_), $5->set_, $7->set_, x_ival);
    delete $3;
    delete $5;
    delete $7;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
;

bool_clause_reif :
  TK_BOOL_CLAUSE_REIF '(' array_var_bool_expr ',' array_var_bool_expr ',' var_bool_expr ')'
  {
    parser->bool_clause_reif(*($3->termlist_), *($5->termlist_), $7);
    delete $3;
    delete $5;
  }
;

float_dom:
  TK_FLOAT_IN '(' var_float_expr ',' par_float_expr ',' par_float_expr ')'
  {
    parser->float_in($3, $5, $7);
  }
| TK_FLOAT_DOM '(' var_float_expr ',' array_par_float_expr ','
                   par_float_expr ',' par_float_expr ')'
  {
    parser->float_dom($3, *($5->termlist_), $7, $9);
    delete $5;
  }
;

roots:
  TK_ROOTS '(' array_var_int_expr ',' set_literal ',' set_literal ','
               INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number xstart = number_from_str($9);
    Number xend   = number_from_str($11);

    NumInterval x_ival(xstart, xend);

    parser->roots(*($3->termlist_), $5->set_, $7->set_, x_ival);
    delete $3;
    delete $5;
    delete $7;
    MSAT_SFREE($9);
    MSAT_SFREE($11);
  }
;

sum_pred:
  TK_SUM_PRED '(' var_int_expr ',' set_array_literal ',' array_par_int_expr ',' var_int_expr ','
                  INT_LITERAL TK_DOTDOT INT_LITERAL ','
                  INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number csstart = number_from_str($11);
    Number csend   = number_from_str($13);
    Number setsstart = number_from_str($15);
    Number setsend   = number_from_str($17);

    NumInterval cs_ival(csstart, csend);
    NumInterval sets_ival(setsstart, setsend);

    parser->sum_pred($3, $5->set_list_, *($7->termlist_), $9, cs_ival, sets_ival);
    delete $5;
    delete $7;
    MSAT_SFREE($11);
    MSAT_SFREE($13);
    MSAT_SFREE($15);
    MSAT_SFREE($17);
  }
;

symmetric_all_different:
  TK_SYMMETRIC_ALL_DIFFERENT '(' array_var_int_expr ','
                                 INT_LITERAL TK_DOTDOT INT_LITERAL ')'
  {
    Number start = number_from_str($5);
    Number end   = number_from_str($7);
    NumInterval x_ival(start, end);

    parser->symmetric_all_different(*($3->termlist_), x_ival);
    delete $3;
    MSAT_SFREE($5);
    MSAT_SFREE($7);
  }
;

value_precede:
  TK_VALUE_PRECEDE_INT '(' par_int_expr ',' par_int_expr ',' array_var_int_expr ')'
  {
    parser->value_precede($3, $5, *($7->termlist_));
    delete $7;
  }
| TK_VALUE_PRECEDE_SET '(' par_int_expr ',' par_int_expr ',' set_array_literal ')'
  {
    parser->value_precede($3, $5, $7->set_list_);
    delete $7;
  }
;

global_ident :
  TK_ALLDIFFERENT_EXCEPT_0
| TK_ALL_DIFFERENT_INT
| TK_ALL_DIFFERENT_SET
| TK_ALL_DISJOINT
| TK_DISJOINT
| TK_DISJUNCTIVE
| TK_DISJUNCTIVE_STRICT
| TK_ALL_EQUAL_INT
| TK_ALL_EQUAL_SET
| TK_AMONG
| TK_MAXIMUM_FLOAT
| TK_MAXIMUM_INT
| TK_MINIMUM_FLOAT
| TK_MINIMUM_INT
| TK_ARRAY_FLOAT_MAXIMUM
| TK_ARRAY_INT_MAXIMUM
| TK_ARRAY_FLOAT_MINIMUM
| TK_ARRAY_INT_MINIMUM
| TK_MAXIMUM_ARG_INT
| TK_MAXIMUM_ARG_FLOAT
| TK_MINIMUM_ARG_INT
| TK_MINIMUM_ARG_FLOAT
| TK_AT_LEAST_INT
| TK_AT_LEAST_SET
| TK_EXACTLY_INT
| TK_EXACTLY_SET
| TK_AT_MOST_INT
| TK_AT_MOST_SET
| TK_ATMOST1
| TK_BIN_PACKING_CAPA
| TK_BIN_PACKING_LOAD
| TK_BIN_PACKING
| TK_ELEMENT_BOOL
| TK_ELEMENT_FLOAT
| TK_ELEMENT_INT
| TK_ELEMENT_SET
| TK_COMPARISON_REL_ARRAY
| TK_COUNT_EQ
| TK_COUNT_GEQ
| TK_COUNT_GT
| TK_COUNT_LEQ
| TK_COUNT_LT
| TK_COUNT_NEQ
| TK_DECREASING_BOOL
| TK_DECREASING_FLOAT
| TK_DECREASING_INT
| TK_DECREASING_SET
| TK_INCREASING_BOOL
| TK_INCREASING_FLOAT
| TK_INCREASING_INT
| TK_INCREASING_SET
| TK_DIFFN
| TK_DIFFN_NONSTRICT
| TK_DIFFN_NONOVERLAP_K
| TK_DIFFN_NONSTRICT_NONOVERLAP_K
| TK_DISTRIBUTE
| TK_GEOST_NONOVERLAP_K
| TK_GLOBAL_CARDINALITY
| TK_GLOBAL_CARDINALITY_CLOSED
| TK_GLOBAL_CARDINALITY_LOW_UP
| TK_GLOBAL_CARDINALITY_LOW_UP_CLOSED
| TK_INT_SET_CHANNEL
| TK_INVERSE
| TK_INVERSE_SET
| TK_LINK_SET_TO_BOOLEANS
| TK_MEMBER_BOOL
| TK_MEMBER_FLOAT
| TK_MEMBER_INT
| TK_MEMBER_SET
| TK_NVALUE
| TK_RANGE
| TK_BOOL_CLAUSE_REIF
| TK_FLOAT_IN
| TK_FLOAT_DOM
| TK_ROOTS
| TK_SUM_PRED
| TK_SYMMETRIC_ALL_DIFFERENT
| TK_VALUE_PRECEDE_INT
| TK_VALUE_PRECEDE_SET
  {

  }
;
//---------------------------------------------------------------------------
// Utils
//---------------------------------------------------------------------------

%%

namespace {

inline Number number_from_str(const char *str)
{
    assert(str);
    return Number::from_str(str);
}

} // namespace
