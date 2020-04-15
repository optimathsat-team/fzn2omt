// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCPARSER_H_INCLUDED
#define FLATZINCPARSER_H_INCLUDED

#include "../terms/term.h"
#include "../utils/numbers.h"
#include "../parser/parserinterface.h"
#include "../utils/numinterval.h"
#include "../utils/numintervalset.h"
#include "../utils/numflatzincdomain.h"
#include "../utils/flatzincset.h"
#include "../parser/flatzincannotation.h"
#include "../parser/flatzincbisonparser.h"
#include<vector>

namespace msat {

//-----------------------------------------------------------------------------
// Interface for FlatZinc parsers
//-----------------------------------------------------------------------------
class FlatZincAbstractParser {
public:
    virtual ~FlatZincAbstractParser() {};

    virtual void handle_error(const char *msg) = 0;
    ParserInterface::str_alloc *get_str_alloc() { return &stralloc_; }

    ///< FlatZinc Variable Declaration
    ///< bool, int, float
    virtual void declare_par(NumFlatZincDomainSharedPtr dom,
                         const char *ident, Term expr) = 0;
    virtual void declare_var(NumFlatZincDomainSharedPtr dom,
                         const char *ident, Term expr) = 0;
    virtual void declare_array_par(size_t len, NumFlatZincDomainSharedPtr dom,
                         const char *ident, TermListSharedPtr terms) = 0;
    virtual void declare_array_var(size_t len, NumFlatZincDomainSharedPtr dom,
                         const char *ident, TermListSharedPtr terms) = 0;
    ///< set
    virtual void declare_par_set(NumFlatZincDomainSharedPtr dom,
                         const char *ident, FznSetSharedPtr iset) = 0;
    virtual void declare_var_set(NumFlatZincDomainSharedPtr dom,
                         const char *ident, FznSetSharedPtr iset) = 0;
    virtual void declare_array_par_set(size_t len, NumFlatZincDomainSharedPtr dom,
                         const char *ident, FznSetListSharedPtr isets) = 0;
    virtual void declare_array_var_set(size_t len, NumFlatZincDomainSharedPtr dom,
                         const char *ident, FznSetListSharedPtr isets) = 0;

    virtual void annotate_decl(const char *ident, FlatZincAnnotation &ann) = 0;

    ///< FlatZinc Expressions
    ///< bool, int, float
    virtual Term get_true() = 0;
    virtual Term get_false() = 0;
    virtual Term get_int_number(const char *value) = 0;
    virtual Term get_float_number(const char *value) = 0;
    virtual Term get_var_literal(bool var, FznType t, const char *ident) = 0;
    virtual Term get_var_literal(bool var, FznType t, const char *ident,
                                 size_t index) = 0;
    virtual TermListSharedPtr get_array_var_literal(bool var, FznType t,
                                                    const char *ident) = 0;
    ///< set
    virtual FznSetSharedPtr get_set_literals(const char *ident) = 0;
    virtual FznSetSharedPtr get_set_literals(const char *ident, size_t index) = 0;
    virtual FznSetListSharedPtr get_array_set_literals(const char *ident) = 0;

    ///< FlatZinc Solve
    typedef enum {
        SATISFY,
        MINIMIZE,
        MAXIMIZE
    } SolveType;
    virtual void push_objective(FlatZincAbstractParser::SolveType type, Term expr) = 0;
    //virtual void check_sat() = 0;

    ///< FlatZinc Constraints
    virtual void array_bool_and(TermList &as, Term r) = 0;
    virtual void array_bool_element(Term b, TermList &as, Term c) = 0;
    virtual void array_bool_or(TermList &as, Term r) = 0;
    virtual void array_bool_xor(TermList &as) = 0;
    virtual void array_float_element(Term b, TermList &as, Term c) = 0;
    virtual void array_int_element(Term b, TermList &as, Term c) = 0;
    virtual void array_var_bool_element(Term b, TermList &as, Term c) = 0;
    virtual void array_var_float_element(Term b, TermList &as, Term c) = 0;
    virtual void array_var_int_element(Term b, TermList &as, Term c) = 0;

    virtual void bool2int(Term a, Term b) = 0;
    virtual void bool_and(Term a, Term b, Term r) = 0;
    virtual void bool_clause(TermList &as, TermList &bs) = 0;
    virtual void bool_eq(Term a, Term b) = 0;
    virtual void bool_eq_reif(Term a, Term b, Term r) = 0;
    virtual void bool_le(Term a, Term b) = 0;
    virtual void bool_le_reif(Term a, Term b, Term r) = 0;
    virtual void bool_lin_eq(TermList &as, TermList &bs, Term c) = 0;
    virtual void bool_lin_le(TermList &as, TermList &bs, Term c) = 0;
    virtual void bool_lt(Term a, Term b) = 0;
    virtual void bool_lt_reif(Term a, Term b, Term r) = 0;
    virtual void bool_not(Term a, Term b) = 0;
    virtual void bool_or(Term a, Term b, Term r) = 0;
    virtual void bool_xor(Term a, Term b, Term r) = 0;

    virtual void float_abs(Term a, Term b) = 0;
    virtual void float_div(Term a, Term b, Term c) = 0;
    virtual void float_acos(Term a, Term b) = 0;
    virtual void float_asin(Term a, Term b) = 0;
    virtual void float_atan(Term a, Term b) = 0;
    virtual void float_cos(Term a, Term b) = 0;
    virtual void float_cosh(Term a, Term b) = 0;
    virtual void float_exp(Term a, Term b) = 0;
    virtual void float_ln(Term a, Term b) = 0;
    virtual void float_log10(Term a, Term b) = 0;
    virtual void float_log2(Term a, Term b) = 0;
    virtual void float_sqrt(Term a, Term b) = 0;
    virtual void float_sin(Term a, Term b) = 0;
    virtual void float_sinh(Term a, Term b) = 0;
    virtual void float_tan(Term a, Term b) = 0;
    virtual void float_tanh(Term a, Term b) = 0;
    virtual void float_eq(Term a, Term b) = 0;
    virtual void float_eq_reif(Term a, Term b, Term r) = 0;
    virtual void float_le(Term a, Term b) = 0;
    virtual void float_le_reif(Term a, Term b, Term r) = 0;
    virtual void float_lin_eq(TermList &as, TermList &bs, Term c) = 0;
    virtual void float_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r) = 0;
    virtual void float_lin_le(TermList &as, TermList &bs, Term c) = 0;
    virtual void float_lin_le_reif(TermList &as, TermList &bs, Term c, Term r) = 0;
    virtual void float_lin_lt(TermList &as, TermList &bs, Term c) = 0;
    virtual void float_lin_lt_reif(TermList &as, TermList &bs, Term c, Term r) = 0;
    virtual void float_lin_ne(TermList &as, TermList &bs, Term c) = 0;
    virtual void float_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r) = 0;
    virtual void float_lt(Term a, Term b) = 0;
    virtual void float_lt_reif(Term a, Term b, Term r) = 0;
    virtual void float_max(Term a, Term b, Term c) = 0;
    virtual void float_min(Term a, Term b, Term c) = 0;
    virtual void float_ne(Term a, Term b) = 0;
    virtual void float_ne_reif(Term a, Term b, Term r) = 0;
    virtual void float_plus(Term a, Term b, Term c) = 0;
    virtual void float_times(Term a, Term b, Term c) = 0;

    virtual void int_abs(Term a, Term b) = 0;
    virtual void int_div(Term a, Term b, Term c) = 0;
    virtual void int_eq(Term a, Term b) = 0;
    virtual void int_eq_reif(Term a, Term b, Term r) = 0;
    virtual void int_le(Term a, Term b) = 0;
    virtual void int_le_reif(Term a, Term b, Term r) = 0;
    virtual void int_lin_eq(TermList &as, TermList &bs, Term c) = 0;
    virtual void int_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r) = 0;
    virtual void int_lin_le(TermList &as, TermList &bs, Term c) = 0;
    virtual void int_lin_le_reif(TermList &as, TermList &bs, Term c, Term r) = 0;
    virtual void int_lin_ne(TermList &as, TermList &bs, Term c) = 0;
    virtual void int_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r) = 0;
    virtual void int_lt(Term a, Term b) = 0;
    virtual void int_lt_reif(Term a, Term b, Term r) = 0;
    virtual void int_max(Term a, Term b, Term c) = 0;
    virtual void int_min(Term a, Term b, Term c) = 0;
    virtual void int_mod(Term a, Term b, Term c) = 0;
    virtual void int_ne(Term a, Term b) = 0;
    virtual void int_ne_reif(Term a, Term b, Term r) = 0;
    virtual void int_plus(Term a, Term b, Term c) = 0;
    virtual void int_times(Term a, Term b, Term c) = 0;
    virtual void int2float(Term a, Term b) = 0;

    virtual void array_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c) = 0;
    virtual void array_var_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c) = 0;
    virtual void set_card(FznSetSharedPtr a, Term b) = 0;
    virtual void set_diff(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c) = 0;
    virtual void set_eq(FznSetSharedPtr a, FznSetSharedPtr b) = 0;
    virtual void set_eq_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r) = 0;
    virtual void set_in(Term a, FznSetSharedPtr b) = 0;
    virtual void set_in_reif(Term a, FznSetSharedPtr b, Term r) = 0;
    virtual void set_intersect(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c) = 0;
    virtual void set_le(FznSetSharedPtr a, FznSetSharedPtr b) = 0;
    virtual void set_lt(FznSetSharedPtr a, FznSetSharedPtr b) = 0;
    virtual void set_ne(FznSetSharedPtr a, FznSetSharedPtr b) = 0;
    virtual void set_ne_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r) = 0;
    virtual void set_subset(FznSetSharedPtr a, FznSetSharedPtr b) = 0;
    virtual void set_subset_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r) = 0;
    virtual void set_symdiff(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c) = 0;
    virtual void set_union(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c) = 0;

    ///< FlatZinc Global Constraints

    virtual void all_different(TermList &as) = 0;
    virtual void all_different_except_0(TermList &as) = 0;
    virtual void all_different(FznSetListSharedPtr as) = 0;

    virtual void disjoint(FznSetSharedPtr s1, FznSetSharedPtr s2) = 0;
    virtual void all_disjoint(FznSetListSharedPtr as) = 0;

    virtual void disjunctive(TermList &s, TermList &d) = 0;
    virtual void disjunctive_strict(TermList &s, TermList &d) = 0;

    virtual void all_equal(TermList &x) = 0;
    virtual void all_equal(FznSetListSharedPtr x) = 0;

    virtual void among(Term n, TermList &x, FznSetSharedPtr v) = 0;

    virtual void array_max(Term m, TermList &x) = 0;
    virtual void array_min(Term m, TermList &x) = 0;

    virtual void maximum_arg(TermList &x, Term i, const NumInterval &xdom) = 0;
    virtual void minimum_arg(TermList &x, Term i, const NumInterval &xdom) = 0;

    virtual void at_least_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v) = 0;
    virtual void exactly_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v) = 0;
    virtual void at_most_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v) = 0;
    virtual void at_most_1(FznSetListSharedPtr s) = 0;

    virtual void bin_packing(Term c, TermList &bin, TermList &w) = 0;
    virtual void bin_packing_capa(TermList &c, TermList &bin,
                                  TermList &w, const NumInterval &cdom) = 0;
    virtual void bin_packing_load(TermList &load, TermList &bin,
                                  TermList &w, const NumInterval &loaddom) = 0;

    virtual void element(Term i, TermList &x,
                         Term y, NumInterval &xdom) = 0;
    virtual void element(Term i, FznSetListSharedPtr x,
                         FznSetSharedPtr y, NumInterval &xdom) = 0;

    virtual void comparison_rel_array(TermList &rels, Term rel) = 0;

    virtual void count_eq(Term n, TermList &x, Term v) = 0;
    virtual void count_geq(Term n, TermList &x, Term v) = 0;
    virtual void count_gt(Term n, TermList &x, Term v) = 0;
    virtual void count_leq(Term n, TermList &x, Term v) = 0;
    virtual void count_lt(Term n, TermList &x, Term v) = 0;
    virtual void count_neq(Term n, TermList &x, Term v) = 0;

    virtual void decreasing(TermList &x) = 0;
    virtual void decreasing(FznSetListSharedPtr x) = 0;
    virtual void increasing(TermList &x) = 0;
    virtual void increasing(FznSetListSharedPtr x) = 0;

    virtual void diffn(TermList &x, TermList &y, TermList &dx, TermList &dy) = 0;
    virtual void diffn_nonstrict(TermList &x, TermList &y, TermList &dx, TermList &dy) = 0;
    virtual void diffn_nonoverlap_k(TermList &x1, TermList &w1, TermList &x2, TermList &w2) = 0;
    virtual void diffn_nonstrict_nonoverlap_k(TermList &x1, TermList &w1,
                                              TermList &x2, TermList &w2) = 0;

    virtual void distribute(TermList &card, TermList &value, TermList &base) = 0;

    virtual void geost_nonoverlap_k(TermList &x1, TermList &w1,
                                    TermList &x2, TermList &w2) = 0;

    virtual void global_cardinality(TermList &x, TermList &cover,
                                    TermList &counts) = 0;
    virtual void global_cardinality_closed(TermList &x, TermList &cover,
                                    TermList &counts) = 0;
    virtual void global_cardinality_low_up(TermList &x, TermList &cover,
                                    TermList &lbound, TermList &ubound) = 0;
    virtual void global_cardinality_low_up_closed(TermList &x, TermList &cover,
                                    TermList &lbound, TermList &ubound) = 0;

    virtual void int_set_channel(TermList &x, FznSetListSharedPtr y,
                                 const NumInterval &xdom, const NumInterval &ydom) = 0;

    virtual void inverse(TermList &f, TermList &invf,
                         const NumInterval &fdom, const NumInterval &invfdom) = 0;
    virtual void inverse_set(FznSetListSharedPtr f, FznSetListSharedPtr invf,
                             const NumInterval &fdom, const NumInterval &invfdom) = 0;

    virtual void link_set_to_booleans(FznSetSharedPtr s, TermList &b,
                                      const NumInterval &bdom) = 0;

    virtual void member(TermList &x, Term y) = 0;
    virtual void member(FznSetListSharedPtr x, FznSetSharedPtr y) = 0;

    virtual void nvalue(Term n, TermList &x) = 0;

    virtual void range(TermList &x, FznSetSharedPtr s,
                       FznSetSharedPtr t, const NumInterval &xdom) = 0;

    virtual void bool_clause_reif(TermList &as, TermList &bs, Term b) = 0;

    virtual void float_in(Term x, Term a, Term b) = 0;
    virtual void float_dom(Term x, TermList &as, Term a, Term b) = 0;

    virtual void roots(TermList &x, FznSetSharedPtr s,
                       FznSetSharedPtr t, const NumInterval &xdom) = 0;

    virtual void sum_pred(Term i, FznSetListSharedPtr sets, TermList &cs,
                          Term s, const NumInterval &csdom, const NumInterval &setsdom) = 0;

    virtual void symmetric_all_different(TermList &x, const NumInterval &xdom) = 0;

    virtual void value_precede(Term s, Term t, TermList &x) = 0;
    virtual void value_precede(Term s, Term t, FznSetListSharedPtr x) = 0;

protected:
    ParserInterface::str_alloc stralloc_;
};

} // namespace

#endif
