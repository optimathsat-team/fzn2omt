// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "cardconstr.h"
#include<assert.h>
#include<sstream>

namespace msat {

namespace opt {

CardConstr::CardConstr(OptEnvironment *env, Term s, Term w)
    : Circuit(env, s, w), enc_(NULL)
{
    counter = 0;
    // nothing to do
}

CardConstr::~CardConstr()
{
    // nothing to do
}


//-----------------------------------------------------------------------------
// Public Interface
//-----------------------------------------------------------------------------

size_t CardConstr::size() const
{
    return clauses_.size();
}

bool CardConstr::is_empty() const
{
    return (0 == clauses_.size());
}

void CardConstr::push_clause(
        Term cl)
{
    assert(mgr_->is_subtype(cl->get_type(), mgr_->get_bool_type()));
    clauses_.push_back(cl);
    enc_ = NULL;
}

void CardConstr::pop_clause()
{
    assert(clauses_.size() > 0);
    clauses_.pop_back();
    enc_ = NULL;
}

bool CardConstr::has_pending_push(
        Term &cs)
{
    if (clauses_.size() > 0) {
        if (!enc_) {
            TermList pins;
            enc_ = make_circuit_bounded(clauses_.size());
            sorting_network(clauses_, pins, enc_);
            circuit_connector(pins, enc_);
        }
        cs = enc_;
        return true;
    } else {
        return false;
    }
}

//-----------------------------------------------------------------------------
// Private Help Functions
//-----------------------------------------------------------------------------

inline TermList get_odd(const TermList &list) {
    TermList ret = TermList();
    ret.reserve((list.size() / 2) + 1);
    for (size_t i = 0; i < list.size(); ++i) {
        if (i % 2 == 0) { // inverted! see nlln_maxsmt.py
            ret.push_back(list[i]);
        }
    }
    return ret;
}

inline TermList get_even(const TermList &list) {
    TermList ret = TermList();
    ret.reserve((list.size() / 2));
    for (size_t i = 0; i < list.size(); ++i) {
        if (i % 2 == 1) { // inverted! see nlln_maxsmt.py
            ret.push_back(list[i]);
        }
    }
    return ret;
}

void CardConstr::sorting_network(
        const TermList &x,
        TermList& out, Term &f)
{
    size_t xl = x.size();
    if (1 == xl) {
        out = x;
    } else if (2 == xl) {
        TermList x_1(x.begin(),   x.begin()+1);
        TermList x_2(x.begin()+1, x.begin()+2);
        merge_network(x_1, x_2, out, f);
    } else {
        size_t l = xl / 2;
        TermList l1(x.begin(), x.begin()+l);
        TermList l2(x.begin()+l, x.begin()+xl);
        TermList out1;
        TermList out2;
        sorting_network(l1, out1, f);
        sorting_network(l2, out2, f);
        merge_network(out1, out2, out, f);
    }
}

void CardConstr::merge_network(
        const TermList &x_1, const TermList &x_2,
        TermList &out, Term &f)
{
    size_t l_1 = x_1.size();
    size_t l_2 = x_2.size();
    if (1 == l_1 && l_1 == l_2) {
        two_comparator(x_1[0], x_2[0], out, f);
    } else if (0 == l_1) {
        out = x_2;
    } else if (0 == l_2) {
        merge_network(x_2, x_1, out, f);
    } else if ((l_1 % 2 == 1) && (l_2 % 2 == 0)) {
        merge_network(x_2, x_1, out, f);
    } else {
        TermList odd1(get_odd(x_1));
        TermList odd2(get_odd(x_2));
        TermList even1(get_even(x_1));
        TermList even2(get_even(x_2));
        TermList out1;
        TermList out2;
        merge_network(odd1, odd2, out1, f);
        merge_network(even1, even2, out2, f);
        out.push_back(out1[0]);
        size_t ol = out1.size();
        size_t el = out2.size();
        size_t m = (((ol-1) < el) ? (ol-1) : el);
        for (size_t i = 0; i < m; ++i) {
            Term out3;
            two_comparator(out2[i], out1[i+1], out, f);
        }
        if ((l_1 % 2 == 0) && (l_2 % 2 == 0)) {
            out.push_back(out2.back());
        } else if ((l_1 % 2 == 1) && (l_2 % 2 == 1)) {
            out.push_back(out1.back());
        }
    }
}

void CardConstr::two_comparator(
        Term x_1, Term x_2,
        TermList &out, Term &f)
{
    static uint64_t counter;
    std::stringstream ss1, ss2;
    ss1 << TermManager::INTERNAL_SYMBOLS_NAMESPACE
        << "cc_y_1_" << counter;
    ss2 << TermManager::INTERNAL_SYMBOLS_NAMESPACE
        << "cc_y_2_" << counter++;
    const Symbol *s1 = mgr_->make_unique_symbol(ss1.str(),
                                                mgr_->get_bool_type());
    const Symbol *s2 = mgr_->make_unique_symbol(ss2.str(),
                                                mgr_->get_bool_type());
    assert(s1);
    assert(s2);
    Term y_1 = mgr_->make_constant(s1);
    Term y_2 = mgr_->make_constant(s2);
    Term t = mgr_->make_and(mgr_->make_or(mgr_->make_not(x_1), y_1),
             mgr_->make_and(mgr_->make_or(mgr_->make_not(x_2), y_1),
             mgr_->make_and(mgr_->make_or(mgr_->make_not(mgr_->make_and(x_1, x_2)), y_2),
             mgr_->make_and(mgr_->make_or(x_1, mgr_->make_not(y_2)),
             mgr_->make_and(mgr_->make_or(x_2, mgr_->make_not(y_2)),
                            mgr_->make_or(mgr_->make_or(x_1, x_2),
                                          mgr_->make_not(y_1)))))));
    f = mgr_->make_and(f, t);
    out.push_back(y_1);
    out.push_back(y_2);
}

void CardConstr::circuit_connector(
        const TermList &pins, Term &f)
{
    for (size_t i = 0; i < pins.size(); i++) {
        Term ub = mgr_->make_times(weight_,
                  mgr_->make_number(i));
        Term lb = mgr_->make_times(weight_,
                  mgr_->make_number(i + 1));
        assert(ub);
        assert(lb);
        Term cs1 = NULL;
        Term cs2 = NULL;
        if (positive_weight_) {
            cs1 = mgr_->make_leq(lb, sum_);
            cs2 = mgr_->make_leq(sum_, ub);
        } else {
            cs1 = mgr_->make_leq(sum_, lb);
            cs2 = mgr_->make_leq(ub, sum_);
        }
        assert(cs1);
        assert(cs2);
        Term impl1 = mgr_->make_or(mgr_->make_not(pins[i]), cs1);
        Term impl2 = mgr_->make_or(pins[i], cs2);
        Term mutex = mgr_->make_or(mgr_->make_not(cs1),
                                   mgr_->make_not(cs2));
        assert(impl1);
        assert(impl2);
        assert(mutex);
        f = mgr_->make_and(f, impl1);
        f = mgr_->make_and(f, impl2);
        f = mgr_->make_and(f, mutex);

        if (i > 0) {
            Term t = mgr_->make_or(mgr_->make_not(pins[i]),
                                   pins[i-1]); // pin[i] -> pin[i-1]
            assert(t);
            f = mgr_->make_and(f, t);
        }
    }
}


} /*** namespace msat::opt ***/
} /*** namespace msat ***/


