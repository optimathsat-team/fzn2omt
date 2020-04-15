// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCSET_H_INCLUDED
#define FLATZINCSET_H_INCLUDED

#include "../utils/numinterval.h"
#include "../utils/numintervalset.h"
#include "../utils/numflatzincdomain.h"
#include<vector>
#include<inttypes.h>

namespace msat {

class FlatZincSet;
typedef std::vector<FlatZincSet*> FlatZincSetList;

//-----------------------------------------------------------------------------
// FlatZincSet Class
//-----------------------------------------------------------------------------

class FlatZincSet {
public:
    FlatZincSet(bool is_literal);

    bool set_ident(std::string &id);
    ///< if the set has no identifier set, it stores it and returns TRUE
    ///< otherwise the identifier is not set and it returns FALSE
    const std::string& get_ident() const;
    ///< returns the identifier of the set, if any

    bool is_set_literal() const;
    ///< returns TRUE iff this is a set literal
    void add_set_elements(const NumInterval &ival);
    ///< adds elements to the set, the set must be a literal set
    ///< NOTE: it is assumed that any literal value is added to the set
    ///< before any domain restriction is applied.
    bool contains(Number val) const;
    ///< returns true if set literal contains val
    bool domain_contains(Number val) const;
    ///< returns true if set domain/literal contains val

    bool apply_domain_restriction(const NumFlatZincDomain &dom);
    ///< restricts the domain of the set with the domain interval
    ///< passed as argument. The function returns FALSE if this
    ///< is a set literal and the domain restriction is incompatible
    ///< with its set of literal values
    const NumIntervalSet &get_domain() const;
    ///< returns the domain of the set; if the set is a set literal
    ///< the literal set of values is returned instead

private:
    bool is_literal_;
    std::string id_;
    NumIntervalSet values_;
    NumFlatZincDomain domain_;
};

} // namespace msat

#endif
