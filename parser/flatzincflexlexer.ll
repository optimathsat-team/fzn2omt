/* -*- C++ -*-
 *
 * $MATHSAT5_LICENSE_BANNER_HERE$
 *
 * Author: Patrick Trentin <patrick.trentin@unitn.it>
 *
 * This file is part of OptiMathSAT.
 */

%top{
#include "../msatconfig.h"
#include <stdint.h>
#ifdef MSAT_MSVC
extern "C" int isatty(int);
#  define YY_NO_UNISTD_H 1
#endif
}

%{
//.                  { ParserInterface::error err("unrecognized text: "); err << yytext; throw err; }
#include "../parser/parserinterface.h"
#include "../utils/strutils.h"

using namespace msat;

#include "../parser/flatzincbisonparser.h"

#define MSAT_GET_INFO(s) static_cast<ParserInterface::istream_info *>(msat_flatzinc_parser_get_extra(s))

#define YY_INPUT(buf,result,maxsize)                                    \
    {                                                                   \
         ParserInterface::istream_info *source = MSAT_GET_INFO(yyscanner); \
         result = ParserInterface::flex_get_input(source->stream, buf, maxsize); \
    }

#define MSAT_SDUP(result,s,n)  \
    do { \
        ParserInterface::istream_info *source = MSAT_GET_INFO(yyscanner); \
        result = source->alloc->str_dup(s, n);                            \
    } while (0)

#define yyterminate() \
    do { \
        ParserInterface::istream_info *source = MSAT_GET_INFO(yyscanner); \
        source->done = true; \
        return YY_NULL; \
    } while (0)

%}

%option reentrant
%option bison-bridge
%option bison-locations
%option noyywrap
%option prefix="msat_flatzinc_parser_"
%option stack
%option yylineno

/* Regular expressions for attributed tokens. */
IDENT              [A-Za-z][A-Za-z0-9_]*
UNDERSCORE_IDENT   _*[A-Za-z][A-Za-z0-9_]*
STRING_LITERAL     \"[^"\n]*\"
INT_LITERAL        -?[0-9]+|-?0x[0-9A-Fa-f]+|-?0o[0-7]+
FLOAT_LITERAL      -?[0-9]+\.[0-9]+|-?[0-9]+\.[0-9]+[Ee][-+]?[0-9]+|-?[0-9]+[Ee][-+]?[0-9]+

%%
\n                        { ; }
\r                        { ; }
[ \t]                     { ; }
%.*                       { ; }

"predicate"               { return TK_PREDICATE; }
"var"                     { return TK_VAR; }
"bool"                    { return TK_BOOL; }
"float"                   { return TK_FLOAT; }
"int"                     { return TK_INT; }
"array"                   { return TK_ARRAY; }
"set"                     { return TK_SET; }
"of"                      { return TK_OF; }
"true"                    { return TK_TRUE; }
"false"                   { return TK_FALSE; }
"constraint"              { return TK_CONSTRAINT; }
"solve"                   { return TK_SOLVE; }
"minimize"                { return TK_MINIMIZE; }
"maximize"                { return TK_MAXIMIZE; }
"satisfy"                 { return TK_SATISFY; }

"array_bool_and"          { return TK_ARRAY_BOOL_AND; }
"array_bool_element"      { return TK_ARRAY_BOOL_ELEMENT; }
"array_bool_or"           { return TK_ARRAY_BOOL_OR; }
"array_bool_xor"          { return TK_ARRAY_BOOL_XOR; }
"array_float_element"     { return TK_ARRAY_FLOAT_ELEMENT; }
"array_int_element"       { return TK_ARRAY_INT_ELEMENT; }
"array_set_element"       { return TK_ARRAY_SET_ELEMENT; }
"array_var_bool_element"  { return TK_ARRAY_VAR_BOOL_ELEMENT; }
"array_var_float_element" { return TK_ARRAY_VAR_FLOAT_ELEMENT; }
"array_var_int_element"   { return TK_ARRAY_VAR_INT_ELEMENT; }
"array_var_set_element"   { return TK_ARRAY_VAR_SET_ELEMENT; }
"bool2int"                { return TK_BOOL2INT; }
"bool_and"                { return TK_BOOL_AND; }
"bool_clause"             { return TK_BOOL_CLAUSE; }
"bool_eq"                 { return TK_BOOL_EQ; }
"bool_eq_reif"            { return TK_BOOL_EQ_REIF; }
"bool_le"                 { return TK_BOOL_LE; }
"bool_le_reif"            { return TK_BOOL_LE_REIF; }
"bool_lin_eq"             { return TK_BOOL_LIN_EQ; }
"bool_lin_le"             { return TK_BOOL_LIN_LE; }
"bool_lt"                 { return TK_BOOL_LT; }
"bool_lt_reif"            { return TK_BOOL_LT_REIF; }
"bool_not"                { return TK_BOOL_NOT; }
"bool_or"                 { return TK_BOOL_OR; }
"bool_xor"                { return TK_BOOL_XOR; }
"float_abs"               { return TK_FLOAT_ABS; }
"float_div"               { return TK_FLOAT_DIV; }
"float_acos"              { return TK_FLOAT_ACOS; }
"float_asin"              { return TK_FLOAT_ASIN; }
"float_atan"              { return TK_FLOAT_ATAN; }
"float_cos"               { return TK_FLOAT_COS; }
"float_cosh"              { return TK_FLOAT_COSH; }
"float_exp"               { return TK_FLOAT_EXP; }
"float_ln"                { return TK_FLOAT_LN; }
"float_log10"             { return TK_FLOAT_LOG10; }
"float_log2"              { return TK_FLOAT_LOG2; }
"float_sqrt"              { return TK_FLOAT_SQRT; }
"float_sin"               { return TK_FLOAT_SIN; }
"float_sinh"              { return TK_FLOAT_SINH; }
"float_tan"               { return TK_FLOAT_TAN; }
"float_tanh"              { return TK_FLOAT_TANH; }
"float_eq"                { return TK_FLOAT_EQ; }
"float_eq_reif"           { return TK_FLOAT_EQ_REIF; }
"float_le"                { return TK_FLOAT_LE; }
"float_le_reif"           { return TK_FLOAT_LE_REIF; }
"float_lin_eq"            { return TK_FLOAT_LIN_EQ; }
"float_lin_eq_reif"       { return TK_FLOAT_LIN_EQ_REIF; }
"float_lin_le"            { return TK_FLOAT_LIN_LE; }
"float_lin_le_reif"       { return TK_FLOAT_LIN_LE_REIF; }
"float_lin_lt"            { return TK_FLOAT_LIN_LT; }
"float_lin_lt_reif"       { return TK_FLOAT_LIN_LT_REIF; }
"float_lin_ne"            { return TK_FLOAT_LIN_NE; }
"float_lin_ne_reif"       { return TK_FLOAT_LIN_NE_REIF; }
"float_lt"                { return TK_FLOAT_LT; }
"float_lt_reif"           { return TK_FLOAT_LT_REIF; }
"float_max"               { return TK_FLOAT_MAX; }
"float_min"               { return TK_FLOAT_MIN; }
"float_ne"                { return TK_FLOAT_NE; }
"float_ne_reif"           { return TK_FLOAT_NE_REIF; }
"float_plus"              { return TK_FLOAT_PLUS; }
"float_times"             { return TK_FLOAT_TIMES; }
"int_abs"                 { return TK_INT_ABS; }
"int_div"                 { return TK_INT_DIV; }
"int_eq"                  { return TK_INT_EQ; }
"int_eq_reif"             { return TK_INT_EQ_REIF; }
"int_le"                  { return TK_INT_LE; }
"int_le_reif"             { return TK_INT_LE_REIF; }
"int_lin_eq"              { return TK_INT_LIN_EQ; }
"int_lin_eq_reif"         { return TK_INT_LIN_EQ_REIF; }
"int_lin_le"              { return TK_INT_LIN_LE; }
"int_lin_le_reif"         { return TK_INT_LIN_LE_REIF; }
"int_lin_ne"              { return TK_INT_LIN_NE; }
"int_lin_ne_reif"         { return TK_INT_LIN_NE_REIF; }
"int_lt"                  { return TK_INT_LT; }
"int_lt_reif"             { return TK_INT_LT_REIF; }
"int_max"                 { return TK_INT_MAX; }
"int_min"                 { return TK_INT_MIN; }
"int_mod"                 { return TK_INT_MOD; }
"int_ne"                  { return TK_INT_NE; }
"int_ne_reif"             { return TK_INT_NE_REIF; }
"int_plus"                { return TK_INT_PLUS; }
"int_times"               { return TK_INT_TIMES; }
"int2float"               { return TK_INT2FLOAT; }
"set_card"                { return TK_SET_CARD; }
"set_diff"                { return TK_SET_DIFF; }
"set_eq"                  { return TK_SET_EQ; }
"set_eq_reif"             { return TK_SET_EQ_REIF; }
"set_in"                  { return TK_SET_IN; }
"set_in_reif"             { return TK_SET_IN_REIF; }
"set_intersect"           { return TK_SET_INTERSECT; }
"set_le"                  { return TK_SET_LE; }
"set_lt"                  { return TK_SET_LT; }
"set_ne"                  { return TK_SET_NE; }
"set_ne_reif"             { return TK_SET_NE_REIF; }
"set_subset"              { return TK_SET_SUBSET; }
"set_subset_reif"         { return TK_SET_SUBSET_REIF; }
"set_symdiff"             { return TK_SET_SYMDIFF; }
"set_union"               { return TK_SET_UNION; }

"optimathsat_alldifferent_except_0"             { return TK_ALLDIFFERENT_EXCEPT_0; }
"optimathsat_all_different_int"                 { return TK_ALL_DIFFERENT_INT; }
"optimathsat_all_different_set"                 { return TK_ALL_DIFFERENT_SET; }
"optimathsat_all_disjoint"                      { return TK_ALL_DISJOINT; }
"optimathsat_disjoint"                          { return TK_DISJOINT; }
"optimathsat_disjunctive"                       { return TK_DISJUNCTIVE; }
"optimathsat_disjunctive_strict"                { return TK_DISJUNCTIVE_STRICT; }
"optimathsat_all_equal_int"                     { return TK_ALL_EQUAL_INT; }
"optimathsat_all_equal_set"                     { return TK_ALL_EQUAL_SET; }
"optimathsat_among"                             { return TK_AMONG; }
"optimathsat_maximum_float"                     { return TK_MAXIMUM_FLOAT; }
"optimathsat_maximum_int"                       { return TK_MAXIMUM_INT; }
"optimathsat_minimum_float"                     { return TK_MINIMUM_FLOAT; }
"optimathsat_minimum_int"                       { return TK_MINIMUM_INT; }
"optimathsat_array_float_maximum"               { return TK_ARRAY_FLOAT_MAXIMUM; }
"optimathsat_array_int_maximum"                 { return TK_ARRAY_INT_MAXIMUM; }
"optimathsat_array_float_minimum"               { return TK_ARRAY_FLOAT_MINIMUM; }
"optimathsat_array_int_minimum"                 { return TK_ARRAY_INT_MINIMUM; }
"optimathsat_maximum_arg_int"                   { return TK_MAXIMUM_ARG_INT; }
"optimathsat_maximum_arg_float"                 { return TK_MAXIMUM_ARG_FLOAT; }
"optimathsat_minimum_arg_int"                   { return TK_MINIMUM_ARG_INT; }
"optimathsat_minimum_arg_float"                 { return TK_MINIMUM_ARG_FLOAT; }
"optimathsat_at_least_int"                      { return TK_AT_LEAST_INT; }
"optimathsat_at_least_set"                      { return TK_AT_LEAST_SET; }
"optimathsat_exactly_int"                       { return TK_EXACTLY_INT; }
"optimathsat_exactly_set"                       { return TK_EXACTLY_SET; }
"optimathsat_at_most_int"                       { return TK_AT_MOST_INT; }
"optimathsat_at_most_set"                       { return TK_AT_MOST_SET; }
"optimathsat_at most1"                          { return TK_ATMOST1; }
"optimathsat_bin_packing_capa"                  { return TK_BIN_PACKING_CAPA; }
"optimathsat_bin_packing_load"                  { return TK_BIN_PACKING_LOAD; }
"optimathsat_bin_packing"                       { return TK_BIN_PACKING; }
"optimathsat_element_bool"                      { return TK_ELEMENT_BOOL; }
"optimathsat_element_float"                     { return TK_ELEMENT_FLOAT; }
"optimathsat_element_int"                       { return TK_ELEMENT_INT; }
"optimathsat_element_set"                       { return TK_ELEMENT_SET; }
"optimathsat_comparison_rel_array"              { return TK_COMPARISON_REL_ARRAY; }
"optimathsat_count_eq"                          { return TK_COUNT_EQ; }
"optimathsat_count_geq"                         { return TK_COUNT_GEQ; }
"optimathsat_count_gt"                          { return TK_COUNT_GT; }
"optimathsat_count_leq"                         { return TK_COUNT_LEQ; }
"optimathsat_count_lt"                          { return TK_COUNT_LT; }
"optimathsat_count_neq"                         { return TK_COUNT_NEQ; }
"optimathsat_decreasing_bool"                   { return TK_DECREASING_BOOL; }
"optimathsat_decreasing_float"                  { return TK_DECREASING_FLOAT; }
"optimathsat_decreasing_int"                    { return TK_DECREASING_INT; }
"optimathsat_decreasing_set"                    { return TK_DECREASING_SET; }
"optimathsat_increasing_bool"                   { return TK_INCREASING_BOOL; }
"optimathsat_increasing_float"                  { return TK_INCREASING_FLOAT; }
"optimathsat_increasing_int"                    { return TK_INCREASING_INT; }
"optimathsat_increasing_set"                    { return TK_INCREASING_SET; }
"optimathsat_diffn"                             { return TK_DIFFN; }
"optimathsat_diffn_nonstrict"                   { return TK_DIFFN_NONSTRICT; }
"optimathsat_diffn_nonoverlap_k"                { return TK_DIFFN_NONOVERLAP_K; }
"optimathsat_diffn_nonstrict_nonoverlap_k"      { return TK_DIFFN_NONSTRICT_NONOVERLAP_K; }
"optimathsat_distribute"                        { return TK_DISTRIBUTE; }
"optimathsat_geost_nonoverlap_k"                { return TK_GEOST_NONOVERLAP_K; }
"optimathsat_global_cardinality"                { return TK_GLOBAL_CARDINALITY; }
"optimathsat_global_cardinality_closed"         { return TK_GLOBAL_CARDINALITY_CLOSED; }
"optimathsat_global_cardinality_low_up"         { return TK_GLOBAL_CARDINALITY_LOW_UP; }
"optimathsat_global_cardinality_low_up_closed"  { return TK_GLOBAL_CARDINALITY_LOW_UP_CLOSED; }
"optimathsat_int_set_channel"                   { return TK_INT_SET_CHANNEL; }
"optimathsat_inverse"                           { return TK_INVERSE; }
"optimathsat_inverse_set"                       { return TK_INVERSE_SET; }
"optimathsat_link_set_to_booleans"              { return TK_LINK_SET_TO_BOOLEANS; }
"optimathsat_member_bool"                       { return TK_MEMBER_BOOL; }
"optimathsat_member_float"                      { return TK_MEMBER_FLOAT; }
"optimathsat_member_int"                        { return TK_MEMBER_INT; }
"optimathsat_member_set"                        { return TK_MEMBER_SET; }
"optimathsat_nvalue"                            { return TK_NVALUE; }
"optimathsat_range"                             { return TK_RANGE; }
"optimathsat_bool_clause_reif"                  { return TK_BOOL_CLAUSE_REIF; }
"optimathsat_float_in"                          { return TK_FLOAT_IN; }
"optimathsat_float_dom"                         { return TK_FLOAT_DOM; }
"optimathsat_roots"                             { return TK_ROOTS; }
"optimathsat_sum_pred"                          { return TK_SUM_PRED; }
"optimathsat_symmetric_all_different"           { return TK_SYMMETRIC_ALL_DIFFERENT; }
"optimathsat_value_precede_int"                 { return TK_VALUE_PRECEDE_INT; }
"optimathsat_value_precede_set"                 { return TK_VALUE_PRECEDE_SET; }

"output_var"              { return TK_OUTPUT_VAR; }
"output_array"            { return TK_OUTPUT_ARRAY; }

\.\.                      { return TK_DOTDOT; }
::                        { return TK_COLONCOLON; }

{IDENT}                   { MSAT_SDUP(yylval->string, yytext, yyleng); return IDENT; }
{UNDERSCORE_IDENT}        { MSAT_SDUP(yylval->string, yytext, yyleng); return UNDERSCORE_IDENT; }
{STRING_LITERAL}          { MSAT_SDUP(yylval->string, yytext, yyleng); return STRING_LITERAL; }
{INT_LITERAL}             { MSAT_SDUP(yylval->string, yytext, yyleng); return INT_LITERAL; }
{FLOAT_LITERAL}           { MSAT_SDUP(yylval->string, yytext, yyleng); return FLOAT_LITERAL; }

.                         { return yytext[0]; }

%%
