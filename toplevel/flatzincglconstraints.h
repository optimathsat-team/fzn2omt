// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCGLCONSTRAINTS_H_INCLUDED
#define FLATZINCGLCONSTRAINTS_H_INCLUDED

#include "../toplevel/flatzincconstraints.h"
#include <unordered_map>
#include <unordered_set>

namespace msat {
namespace opt {

class FlatZincGlConstraints : public FlatZincConstraints {
public:
    FlatZincGlConstraints(FlatZincInterface *parser, Environment *env,
                          CmdLine *cmdline, FlatZincBank *bank);
    ///< constructor

    virtual ~FlatZincGlConstraints();
    ///< destructor

    Term all_different(TermList &as);
    Term all_different_except_0(TermList &as);
    Term all_different(FznSetListSharedPtr as);

    Term disjoint(FznSetSharedPtr s1, FznSetSharedPtr s2);
    Term all_disjoint(FznSetListSharedPtr as);

    Term disjunctive(TermList &s, TermList &d);
    Term disjunctive_strict(TermList &s, TermList &d);

    Term all_equal(TermList &x);
    Term all_equal(FznSetListSharedPtr x);

    Term among(Term n, TermList &x, FznSetSharedPtr v);

    Term array_max(Term m, TermList &x);
    Term array_min(Term m, TermList &x);

    Term maximum_arg(TermList &x, Term i, const NumInterval &xdom);
    Term minimum_arg(TermList &x, Term i, const NumInterval &xdom);

    Term at_least_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v);
    Term exactly_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v);
    Term at_most_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v);
    Term at_most_1(FznSetListSharedPtr s);

	Term bin_packing(Term c, TermList &bin, TermList &w);
	Term bin_packing_capa(TermList &c, TermList &bin,
                          TermList &w, const NumInterval &cdom);
	Term bin_packing_load(TermList &load, TermList &bin,
                          TermList &w, const NumInterval &loaddom);

    Term element(Term i, TermList &x,
                 Term y, NumInterval &xdom);
    Term element(Term i, FznSetListSharedPtr x,
                 FznSetSharedPtr y, NumInterval &xdom);

    Term comparison_rel_array(TermList &rels, Term rel);

    Term count_eq(Term n, TermList &x, Term c);
    Term count_geq(Term n, TermList &x, Term v);
    Term count_gt(Term n, TermList &x, Term c);
    Term count_leq(Term n, TermList &x, Term v);
    Term count_lt(Term n, TermList &x, Term c);
    Term count_neq(Term n, TermList &x, Term c);

    Term decreasing(TermList &x);
    Term decreasing(FznSetListSharedPtr x);
    Term increasing(TermList &x);
    Term increasing(FznSetListSharedPtr x);

    Term diffn(TermList &x, TermList &y, TermList &dx, TermList &dy);
    Term diffn_nonstrict(TermList &x, TermList &y, TermList &dx, TermList &dy);
    Term diffn_nonoverlap_k(TermList &x1, TermList &w1, TermList &x2, TermList &w2);
    Term diffn_nonstrict_nonoverlap_k(TermList &x1, TermList &w1,
                                      TermList &x2, TermList &w2);

    Term distribute(TermList &card, TermList &value, TermList &base);

    Term geost_nonoverlap_k(TermList &x1, TermList &w1,
                            TermList &x2, TermList &w2);

    Term global_cardinality(TermList &x, TermList &cover,
                            TermList &counts);
    Term global_cardinality_closed(TermList &x, TermList &cover,
                            TermList &counts);
    Term global_cardinality_low_up(TermList &x, TermList &cover,
                            TermList &lbound, TermList &ubound);
    Term global_cardinality_low_up_closed(TermList &x, TermList &cover,
                            TermList &lbound, TermList &ubound);

    Term int_set_channel(TermList &x, FznSetListSharedPtr y,
                         const NumInterval &xdom, const NumInterval &ydom);

    Term inverse(TermList &f, TermList &invf,
                 const NumInterval &fdom, const NumInterval &invfdom);
    Term inverse_set(FznSetListSharedPtr f, FznSetListSharedPtr invf,
                     const NumInterval &fdom, const NumInterval &invfdom);

    Term link_set_to_booleans(FznSetSharedPtr s, TermList &b,
                              const NumInterval &bdom);

    Term member(TermList &x, Term y);
    Term member(FznSetListSharedPtr x, FznSetSharedPtr y);

    Term nvalue(Term n, TermList &x);

    Term range(TermList &x, FznSetSharedPtr s,
               FznSetSharedPtr t, const NumInterval &xdom);

    Term bool_clause_reif(TermList &as, TermList &bs, Term b);

    Term float_in(Term x, Term a, Term b);
    Term float_dom(Term x, TermList &as, Term a, Term b);

    Term roots(TermList &x, FznSetSharedPtr s,
               FznSetSharedPtr t, const NumInterval &xdom);

    Term sum_pred(Term i, FznSetListSharedPtr sets, TermList &cs,
                  Term s, const NumInterval &csdom, const NumInterval &setsdom);

    Term symmetric_all_different(TermList &x, const NumInterval &xdom);

    Term value_precede(Term s, Term t, TermList &x);
    Term value_precede(Term s, Term t, FznSetListSharedPtr x);

protected:
    Term make_count(TermList &x, Term v);
    Term make_count(FznSetListSharedPtr x, FznSetSharedPtr v);

};

}} // namespace

#endif // FLATZINCGLCONSTRAINTS_H_INCLUDED
