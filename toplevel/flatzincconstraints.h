// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCCONSTRAINTS_H_INCLUDED
#define FLATZINCCONSTRAINTS_H_INCLUDED

#include "../api/environment.h"
#include "../toplevel/cmdline.h"
#include "../terms/termmanager.h"
#include "../parser/flatzincparser.h"
#include "../toplevel/flatzincinterface.h"
#include "../toplevel/flatzincbank.h"

namespace msat {

namespace opt {

class FlatZincInterface;
class FlatZincBank;
class OptEnvironment;

class FlatZincConstraints {
public:
    FlatZincConstraints(FlatZincInterface *parser, Environment *env,
                        CmdLine *cmdline, FlatZincBank *bank);
    ///< constructor

    virtual ~FlatZincConstraints();
    ///< destructor

    Term array_bool_and(TermList &as, Term r);
    Term array_element(Term b, TermList &as, Term c);
    Term array_bool_or(TermList &as, Term r);
    Term array_bool_xor(TermList &as);

    Term bool2int(Term a, Term b);
    Term bool_clause(TermList &as, TermList &bs);
    Term bool_eq(Term a, Term b);
    Term bool_eq_reif(Term a, Term b, Term r);
    Term bool_le(Term a, Term b);
    Term bool_le_reif(Term a, Term b, Term c);
    Term bool_lin_eq(TermList &as, TermList &bs, Term c);
    Term bool_lin_le(TermList &as, TermList &bs, Term c);
    Term bool_lt(Term a, Term b);
    Term bool_lt_reif(Term a, Term b, Term r);
    Term bool_not(Term a, Term b);
    Term bool_xor(Term a, Term b, Term r);

    Term float_abs(Term a, Term b);
    Term float_div(Term a, Term b, Term c);
    Term float_acos(Term a, Term b);
    Term float_asin(Term a, Term b);
    Term float_atan(Term a, Term b);
    Term float_cos(Term a, Term b);
    Term float_cosh(Term a, Term b);
    Term float_exp(Term a, Term b);
    Term float_ln(Term a, Term b);
    Term float_log10(Term a, Term b);
    Term float_log2(Term a, Term b);
    Term float_sqrt(Term a, Term b);
    Term float_sin(Term a, Term b);
    Term float_sinh(Term a, Term b);
    Term float_tan(Term a, Term b);
    Term float_tanh(Term a, Term b);
    Term float_eq(Term a, Term b);
    Term float_eq_reif(Term a, Term b, Term r);
    Term float_le(Term a, Term b);
    Term float_le_reif(Term a, Term b, Term r);
    Term float_lin_eq(TermList &as, TermList &bs, Term c);
    Term float_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r);
    Term float_lin_le(TermList &as, TermList &bs, Term c);
    Term float_lin_le_reif(TermList &as, TermList &bs, Term c, Term r);
    Term float_lin_lt(TermList &as, TermList &bs, Term c);
    Term float_lin_lt_reif(TermList &as, TermList &bs, Term c, Term r);
    Term float_lin_ne(TermList &as, TermList &bs, Term c);
    Term float_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r);
    Term float_lt(Term a, Term b);
    Term float_lt_reif(Term a, Term b, Term r);
    Term float_max(Term a, Term b, Term c);
    Term float_min(Term a, Term b, Term c);
    Term float_ne(Term a, Term b);
    Term float_ne_reif(Term a, Term b, Term r);
    Term float_plus(Term a, Term b, Term c);
    Term float_times(Term a, Term b, Term c);

    Term int_abs(Term a, Term b);
    Term int_div(Term a, Term b, Term c);
    Term int_eq(Term a, Term b);
    Term int_eq_reif(Term a, Term b, Term r);
    Term int_le(Term a, Term b);
    Term int_le_reif(Term a, Term b, Term r);
    Term int_lin_eq(TermList &as, TermList &bs, Term c);
    Term int_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r);
    Term int_lin_le(TermList &as, TermList &bs, Term c);
    Term int_lin_le_reif(TermList &as, TermList &bs, Term c, Term r);
    Term int_lin_lt(TermList &as, TermList &bs, Term c);
    Term int_lin_lt_reif(TermList &as, TermList &bs, Term c, Term r);
    Term int_lin_ne(TermList &as, TermList &bs, Term c);
    Term int_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r);
    Term int_lt(Term a, Term b);
    Term int_lt_reif(Term a, Term b, Term r);
    Term int_max(Term a, Term b, Term c);
    Term int_min(Term a, Term b, Term c);
    Term int_mod(Term a, Term b, Term c);
    Term int_ne(Term a, Term b);
    Term int_ne_reif(Term a, Term b, Term r);
    Term int_plus(Term a, Term b, Term c);
    Term int_times(Term a, Term b, Term c);
    Term int2float(Term a, Term b);

    Term array_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c);
    Term set_card(FznSetSharedPtr a, Term b);
    Term set_diff(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);
    Term set_eq(FznSetSharedPtr a, FznSetSharedPtr b);
    Term set_eq_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r);
    Term set_in(Term a, FznSetSharedPtr b, bool internal=false);
    Term set_in_reif(Term a, FznSetSharedPtr b, Term r);
    Term set_intersect(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);
    Term set_le(FznSetSharedPtr a, FznSetSharedPtr b);
    Term set_lt(FznSetSharedPtr a, FznSetSharedPtr b);
    Term set_ne(FznSetSharedPtr a, FznSetSharedPtr b, bool internal=false);
    Term set_ne_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r);
    Term set_subseteq(FznSetSharedPtr a, FznSetSharedPtr b);
    Term set_subseteq_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r);
    Term set_subsetneq(FznSetSharedPtr a, FznSetSharedPtr b);
    Term set_subsetneq_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r);
    Term set_symdiff(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);
    Term set_union(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);

    ///< FlatZinc Global Constraints

    virtual Term all_different(TermList &as) = 0;
    virtual Term all_different_except_0(TermList &as) = 0;
    virtual Term all_different(FznSetListSharedPtr as) = 0;

    virtual Term disjoint(FznSetSharedPtr s1, FznSetSharedPtr s2) = 0;
    virtual Term all_disjoint(FznSetListSharedPtr as) = 0;

    virtual Term disjunctive(TermList &s, TermList &d) = 0;
    virtual Term disjunctive_strict(TermList &s, TermList &d) = 0;

    virtual Term all_equal(TermList &x) = 0;
    virtual Term all_equal(FznSetListSharedPtr x) = 0;

    virtual Term among(Term n, TermList &x, FznSetSharedPtr v) = 0;

    virtual Term array_max(Term m, TermList &x) = 0;
    virtual Term array_min(Term m, TermList &x) = 0;

    virtual Term maximum_arg(TermList &x, Term i, const NumInterval &xdom) = 0;
    virtual Term minimum_arg(TermList &x, Term i, const NumInterval &xdom) = 0;

    virtual Term at_least_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v) = 0;
    virtual Term exactly_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v) = 0;
    virtual Term at_most_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v) = 0;
    virtual Term at_most_1(FznSetListSharedPtr s) = 0;

    virtual Term bin_packing(Term c, TermList &bin, TermList &w) = 0;
    virtual Term bin_packing_capa(TermList &c, TermList &bin,
                                  TermList &w, const NumInterval &cdom) = 0;
    virtual Term bin_packing_load(TermList &load, TermList &bin,
                                  TermList &w, const NumInterval &loaddom) = 0;

    virtual Term element(Term i, TermList &x,
                         Term y, NumInterval &xdom) = 0;
    virtual Term element(Term i, FznSetListSharedPtr x,
                         FznSetSharedPtr y, NumInterval &xdom) = 0;

    virtual Term comparison_rel_array(TermList &rels, Term rel) = 0;

    virtual Term count_eq(Term n, TermList &x, Term v) = 0;
    virtual Term count_geq(Term n, TermList &x, Term v) = 0;
    virtual Term count_gt(Term n, TermList &x, Term v) = 0;
    virtual Term count_leq(Term n, TermList &x, Term v) = 0;
    virtual Term count_lt(Term n, TermList &x, Term v) = 0;
    virtual Term count_neq(Term n, TermList &x, Term v) = 0;

    virtual Term decreasing(TermList &x) = 0;
    virtual Term decreasing(FznSetListSharedPtr x) = 0;
    virtual Term increasing(TermList &x) = 0;
    virtual Term increasing(FznSetListSharedPtr x) = 0;

    virtual Term diffn(TermList &x, TermList &y, TermList &dx, TermList &dy) = 0;
    virtual Term diffn_nonstrict(TermList &x, TermList &y, TermList &dx, TermList &dy) = 0;
    virtual Term diffn_nonoverlap_k(TermList &x1, TermList &w1, TermList &x2, TermList &w2) = 0;
    virtual Term diffn_nonstrict_nonoverlap_k(TermList &x1, TermList &w1,
                                              TermList &x2, TermList &w2) = 0;

    virtual Term distribute(TermList &card, TermList &value, TermList &base) = 0;

    virtual Term geost_nonoverlap_k(TermList &x1, TermList &w1,
                                    TermList &x2, TermList &w2) = 0;

    virtual Term global_cardinality(TermList &x, TermList &cover,
                                    TermList &costs) = 0;
    virtual Term global_cardinality_closed(TermList &x, TermList &cover,
                                    TermList &costs) = 0;
    virtual Term global_cardinality_low_up(TermList &x, TermList &cover,
                                    TermList &lbound, TermList &ubound) = 0;
    virtual Term global_cardinality_low_up_closed(TermList &x, TermList &cover,
                                    TermList &lbound, TermList &ubound) = 0;

    virtual Term int_set_channel(TermList &x, FznSetListSharedPtr y,
                         const NumInterval &xdom, const NumInterval &ydom) = 0;

    virtual Term inverse(TermList &f, TermList &invf,
                         const NumInterval &fdom, const NumInterval &invfdom) = 0;
    virtual Term inverse_set(FznSetListSharedPtr f, FznSetListSharedPtr invf,
                             const NumInterval &fdom, const NumInterval &invfdom) = 0;

    virtual Term link_set_to_booleans(FznSetSharedPtr s, TermList &b,
                                      const NumInterval &bdom) = 0;

    virtual Term member(TermList &x, Term y) = 0;
    virtual Term member(FznSetListSharedPtr x, FznSetSharedPtr y) = 0;

    virtual Term nvalue(Term n, TermList &x) = 0;

    virtual Term range(TermList &x, FznSetSharedPtr s,
                       FznSetSharedPtr t, const NumInterval &xdom) = 0;

    virtual Term bool_clause_reif(TermList &as, TermList &bs, Term b) = 0;

    virtual Term float_in(Term x, Term a, Term b) = 0;
    virtual Term float_dom(Term x, TermList &as, Term a, Term b) = 0;

    virtual Term roots(TermList &x, FznSetSharedPtr s,
                       FznSetSharedPtr t, const NumInterval &xdom) = 0;

    virtual Term sum_pred(Term i, FznSetListSharedPtr sets, TermList &cs,
                          Term s, const NumInterval &csdom, const NumInterval &setsdom) = 0;

    virtual Term symmetric_all_different(TermList &x, const NumInterval &xdom) = 0;

    virtual Term value_precede(Term s, Term t, TermList &x) = 0;
    virtual Term value_precede(Term s, Term t, FznSetListSharedPtr x) = 0;

protected:
    bool are_compatible_types(Term t1, Term t2) const;
    bool is_float(Term t) const;
    bool is_int(Term t) const;
    bool is_bool(Term t) const;

    Term make_ite(Term a, Term b, Term c);
    Term make_times(Term a, Term b);
    Term make_linearized_times(Term a, Term b, Term c);
    Term do_make_linearized_times(Term a, Term b, Number &a_lower, Number &a_upper, Term c);
    Term make_bool_lin(TermList &as, TermList &bs, Term c);
    Term make_float_lin(TermList &as, TermList &bs, Term c);
    Term make_int_lin(TermList &as, TermList &bs, Term c);
    Term make_sum(TermList &terms);

    Term set_make_and_true(const NumIntervalSet &set, FznSetSharedPtr a) const;
    Term set_make_and_false(const NumIntervalSet &set, FznSetSharedPtr a) const;
    Term set_make_or_true(const NumIntervalSet &set, FznSetSharedPtr a) const;
    Term set_make_or_false(const NumIntervalSet &set, FznSetSharedPtr a) const;
    Term set_make_imply(const NumIntervalSet &st, FznSetSharedPtr a, FznSetSharedPtr b) const;
    Term set_make_equal(const NumIntervalSet &st, FznSetSharedPtr a, FznSetSharedPtr b);
    Term set_make_el(FznSetSharedPtr a, Number val) const;
    Term set_make_not_el(FznSetSharedPtr a, Number val) const;
    Term get_max_rear_set_els(FznSetSharedPtr b, Number i);
    Term set_le_lt_base(FznSetSharedPtr a, FznSetSharedPtr b, Term fValReif, bool fStrict);

    FlatZincInterface *parser_;
    Environment *env_;
    opt::OptEnvironment *optenv_;
    CmdLine *cmdline_;
    TermManager *mgr_;
    FlatZincBank *bank_;

    Term one_;
    Term zero_;
    Term true_;
    Term false_;
};

}} // namespace

#endif // FLATZINCCONSTRAINTS_H_INCLUDED
