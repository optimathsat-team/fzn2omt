// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.


#include "../utils/exception.h"
#include "../utils/flatzincset.h"
#include "../parser/flatzincparser.h"

namespace msat {

//-----------------------------------------------------------------------------
// Init/Deinit
//-----------------------------------------------------------------------------

FlatZincSet::FlatZincSet(bool is_literal):
    is_literal_(is_literal),
    id_(""),
    values_(),
    domain_(FZN_INT)
{

}

//-----------------------------------------------------------------------------
// Accessors Methods
//-----------------------------------------------------------------------------

bool FlatZincSet::set_ident(std::string &id)
{
    if (id_ == "") {
        id_ = id;
        return true;
    }
    return false;
}

const std::string& FlatZincSet::get_ident() const
{
    if (id_ == "") {
        throw (Exception("set element has no identifier"));
    }
    return id_;
}

bool FlatZincSet::is_set_literal() const
{
    return is_literal_;
}

void FlatZincSet::add_set_elements(const NumInterval &ival)
{
    assert(is_literal_);
    values_.add(ival);
}

bool FlatZincSet::contains(Number val) const
{
    assert(is_literal_);
    if (values_.set_in(val)) {
        return true;
    } else {
        return false;
    }
}

bool FlatZincSet::domain_contains(Number val) const
{
    if (is_literal_) return contains(val);

    if (domain_.contains(val)) {
        return true;
    } else {
        return false;
    }
}

bool FlatZincSet::apply_domain_restriction(const NumFlatZincDomain &dom)
{
    if (!dom.is_unbounded()) {
        const NumIntervalSet &dset = dom.domain_values();

        if (is_literal_) {
            NumIntervalSet v_m_d = values_.set_diff(dset);
            if (!v_m_d.is_empty()) {
                return false;
            }
        }
        domain_.apply_domain_restriction(dom);
    }
    return true;
}

const NumIntervalSet &FlatZincSet::get_domain() const
{
    if (is_literal_) {
        return values_;
    } else {
        if (domain_.is_unbounded()) {
            throw (Exception("set element is not finite"));
        } else {
            return domain_.domain_values();
        }
    }
}

} // namespace msat
