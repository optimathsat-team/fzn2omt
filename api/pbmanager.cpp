// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../terms/termmanager.h"
#include "../api/environment.h"
#include "circuit.h"
#include "pbmanager.h"
#include "cardconstr.h"
#include <iostream>

namespace msat {
namespace opt {

PBManager::PBManager(TermManager *mgr, OptEnvironment *opt, Term id){
    mgr_ = mgr;
    env_ = opt;
    zero_ = mgr_->make_number(Number(0));
    tid_ = id;
    lower_ = zero_;
    upper_ = zero_;
}

PBManager::~PBManager(){}

Circuit* PBManager::new_circuit(Term weight)
{
    static uint64_t counter;
    std::stringstream ss;
    ss << TermManager::INTERNAL_SYMBOLS_NAMESPACE
       << "pb_circ_" << counter++;
    const Symbol *s = mgr_->make_unique_symbol(ss.str(),
                                               weight->get_type());
    assert(s);
    Term var = mgr_->make_constant(s);
    assert(var);

    Circuit *ret = NULL;
    ret = new CardConstr(env_, var, weight);
 
    assert(ret);

    if (!pbsum_) {
        pbsum_ = var;
    } else {
        pbsum_ = var;
    }

    return ret;
}

void PBManager::do_push_soft_clause(const SoftClause &c){
    if (!mgr_->is_true(c.first->get_symbol())) {
        if (mgr_->is_false(c.first->get_symbol())) {
            lower_ = mgr_->make_plus(lower_, c.second);
            upper_ = mgr_->make_plus(upper_, c.second);
            assert(mgr_->is_number(lower_->get_symbol(), NULL));
            assert(mgr_->is_number(upper_->get_symbol(), NULL));
        } else {
            if (is_positive_weight(c.second)) {
                upper_ = mgr_->make_plus(upper_, c.second);
                assert(mgr_->is_number(upper_->get_symbol(), NULL));
            } else {
                lower_ = mgr_->make_plus(lower_, c.second);
                assert(mgr_->is_number(lower_->get_symbol(), NULL));
            }
        }
        stack_.push_back(c);
    }

    if (!mgr_->is_true(c.first->get_symbol())) {
        CircuitsMap::iterator it = map_.find(c.second);
        Circuit *ptr = NULL;
        if (it == map_.end()) {
            map_[c.second] = CircuitList();
            ptr = new_circuit(c.second);
            map_[c.second].push_back(ptr);
        } else {
            ptr = map_[c.second].back();
        }
        assert(ptr);
        /* circuit counts number of falsified clauses */
        ptr->push_clause(mgr_->make_not(c.first));
    }
}

bool PBManager::is_zero_weight(Term w)
{
    Term t = mgr_->make_equal(w, zero_);
    return mgr_->is_true(t->get_symbol());
}

bool PBManager::is_negative_weight(Term w)
{
    Term t = mgr_->make_not(
             mgr_->make_leq(zero_, w));
    return mgr_->is_true(t->get_symbol());
}

bool PBManager::is_positive_weight(Term w)
{
    Term t = mgr_->make_leq(zero_, w);
    return mgr_->is_true(t->get_symbol());
}

bool PBManager::do_assert_soft_formula(
        Term c, Term w, Term &b_i,
        Term &nb_i, Term &w_i, Term &enc)
{
    assert(c);
    assert(w);

    if (is_zero_weight(w) || mgr_->is_true(c->get_symbol())) {
        /* important! */
        return false;
    }

    static size_t counter;
    std::stringstream ss;
    ss << TermManager::INTERNAL_SYMBOLS_NAMESPACE
       << "pb_w_" << counter++;
    const Symbol *s = mgr_->make_unique_symbol(ss.str(),
                                               w->get_type());
    assert(s);

    w_i = mgr_->make_constant(s);
    b_i = NULL;
    nb_i = NULL;
    enc = NULL;

    if (mgr_->is_false(c->get_symbol()) || c->get_arity() == 0) {
        b_i = c;
        nb_i = mgr_->make_not(b_i);

        enc = mgr_->make_true();
    } else {
        ss.str(std::string());
        ss << TermManager::INTERNAL_SYMBOLS_NAMESPACE
           << "pb_b_" << counter;
        s = mgr_->make_unique_symbol(ss.str(), mgr_->get_bool_type());
        assert(s);
        b_i = mgr_->make_constant(s);
        nb_i = mgr_->make_not(b_i);

        /* b_i -> c */
        enc = mgr_->make_or(nb_i, c);
    }
    assert(b_i);
    assert(nb_i);
    assert(enc);

    do_push_soft_clause(SoftClause(b_i, w)); /* b_i: important! */

    return true;
}

void PBManager::assert_soft_formula(
        Term c, Term w)
{
    Term b_i, nb_i, w_i, enc;
    bool ok = do_assert_soft_formula(c, w, b_i, nb_i, w_i, enc);

    /**
     * NOTE(PT): do_push_soft_clause(...) already called by
     *           do_assert_soft_formula(...), so there is nothing
     *           to do here;
     */

    if (!ok) {
        return;
    }

    assert(enc);
    //env_->assert_formula(enc);
}

bool PBManager::has_pending_push(Term &cs)
{
    if (pbsum_) {
        assert(tid_);
        cs = mgr_->make_equal(tid_, pbsum_);
        for (CircuitsMap::iterator it = map_.begin(),
                iend = map_.end(); it != iend; ++it) {
            CircuitList &list = (*it).second;
            for (CircuitList::iterator jt = list.begin(),
                    jend = list.end(); jt != jend; ++jt) {
                Circuit *ptr = *jt;
                Term tmp = NULL;
                if (ptr->has_pending_push(tmp)) {
                    cs = mgr_->make_and(cs, tmp);
                }
            }
        }
        //env_->assert_formula(cs);
        /**
         * NOTE(PT): equation 13 in paper "On Optimization
         *  Modulo Theories, MaxSMT and Sorting Networks"
         *  cannot be used here, becaue weights can be
         *  negative. Rectifying negative weights into
         *  positive weights would also not work because
         *  implications would not be automatically
         *  activated during dpll search.
         */
        return true;
    } else {
        cs = mgr_->make_equal(tid_, zero_);
        return true;
    }
}

}
}