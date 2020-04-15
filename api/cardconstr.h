// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef CARDCONSTR_H_INCLUDED
#define CARDCONSTR_H_INCLUDED

#include "circuit.h"

namespace msat {

namespace opt {


/**
 * A CardConstr envelopes a Pseudo-Boolean sum of terms,
 * all of which have the same weight.
 */
class CardConstr : public Circuit {
public:
    CardConstr(OptEnvironment *env, Term s, Term w);
    ///< constructor

    virtual ~CardConstr();
    ///< destructor

    ///----------------------------------------------------------------------
    /// Functionality
    ///----------------------------------------------------------------------

    virtual size_t size() const;
    virtual bool is_empty() const;

    virtual void push_clause(Term cl);
    virtual void pop_clause();

    virtual bool has_pending_push(Term &cs);
    //virtual bool has_pending_assumptions(const TheoryLitList &assumptions);

private:
    void sorting_network(const TermList &x,
                         TermList &out, Term &f);
    void merge_network(const TermList &x_1, const TermList &x_2,
                       TermList &out, Term &f);
    void two_comparator(Term x_1, Term x_2,
                        TermList &out, Term &f);
    void circuit_connector(const TermList &pins, Term &f);

    TermList clauses_;
    Term enc_;
    size_t counter;
};

}} // namespace msat::opt

#endif
