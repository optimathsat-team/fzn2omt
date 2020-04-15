// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED

#include "../api/optenvironment.h"
#include<string>

namespace msat {

namespace opt {


/**
 * A Circuit envelopes a Pseudo-Boolean sum of terms,
 * all of which have the same weight.
 */
class Circuit {
public:
    Circuit(OptEnvironment *env, Term s, Term w);
    ///< constructor

    virtual ~Circuit();
    ///< destructor

    ///----------------------------------------------------------------------
    /// Functionality
    ///----------------------------------------------------------------------

    virtual size_t size() const = 0;
    virtual bool is_empty() const = 0;

    virtual void push_clause(Term cl) = 0;
    virtual void pop_clause() = 0;

    virtual bool has_pending_push(Term &cs) = 0;

protected:
    Term make_circuit_bounded(size_t size);

    OptEnvironment *env_;
    TermManager *mgr_;
    Term sum_;
    Term weight_;
    Term zero_;
    bool positive_weight_;
};


}} // namespace msat::opt

#endif
