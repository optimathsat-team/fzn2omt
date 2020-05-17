// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef OPTENVIRONMENT_H_INCLUDED
#define OPTENVIRONMENT_H_INCLUDED

#include "../api/environment.h"
#include "../optsearch/optsearch.h"

namespace msat { namespace opt {

class FlatZincInterface;
class FlatZincBank;


/**
 * An Environment is the interface that MathSAT provides to the external world
 */
class OptEnvironment : public Environment {
public:
    OptEnvironment(Configuration *config);
    ///< constructor

    OptEnvironment(Configuration *config, TermManager *mgr);

    virtual ~OptEnvironment();
    ///< destructor

    virtual void assert_formula(Term term);
    ///< asserts the given formula

    ///----------------------------------------------------------------------
    /// Optimization Interface
    ///----------------------------------------------------------------------
    bool has_compatible_type(const DataType *dt, Term t) const;

    bool is_constant_value(Term t) const;

    virtual OptSearch *make_minimize(Term term, Term lower, Term upper,
                       const std::string &id="", bool bvsigned=false,
                       bool strict=true);
    ///< create the objective 'min(term)' with optional
    ///< optimization internal [lower, upper) and id
    virtual OptSearch *make_maximize(Term term, Term lower, Term upper,
                       const std::string &id="", bool bvsigned=false,
                       bool strict=true);
    ///< create the objective 'min(-1 * term)' with optional
    ///< optimization intervl [-upper, -lower) and id

    virtual void assert_optsearch(OptSearch *ptr);

    Term make_circuit(TermList &clauses, TermList &weights, Term id);
    bool is_zero_weight(Term w);
    bool do_assert_soft_formula(Term c, Term w, Term &b_i,Term &nb_i, Term &w_i, Term &enc);

    bool bv_;
    int language_;
protected:
    friend class FlatZincInterface;
    friend class FlatZincBank;
};

} // namespace opt
} // namespace msat

#endif // OPTENVIRONMENT_H_INCLUDED

