// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "circuit.h"
#include<assert.h>

namespace msat {

namespace opt {

Circuit::Circuit(OptEnvironment *env, Term s, Term w)
    : env_(env), sum_(s), weight_(w)
{
    assert(env_);
    assert(sum_);
    assert(weight_);
    mgr_ = env_->get_term_manager();
    assert(mgr_);
    zero_ = env_->make_number(0);
    Term t = env_->make_leq(zero_, weight_);
    assert(t);
    positive_weight_ = env_->is_true(t);
}

Circuit::~Circuit()
{
    // nothing to do
}


//-----------------------------------------------------------------------------
// Protected Interface
//-----------------------------------------------------------------------------

Term Circuit::make_circuit_bounded(size_t size)
{
    if (0 == size) {
        return mgr_->make_equal(sum_, zero_);
    }

    Term prod = mgr_->make_times(weight_,
                mgr_->make_number(size));
    assert(prod);
    if (positive_weight_) {
        return mgr_->make_and(
               mgr_->make_leq(zero_, sum_),
               mgr_->make_leq(sum_, prod));
    } else {
        return mgr_->make_and(
               mgr_->make_leq(prod, sum_),
               mgr_->make_leq(sum_, zero_));
    }
}


} /*** namespace msat::opt ***/
} /*** namespace msat ***/


