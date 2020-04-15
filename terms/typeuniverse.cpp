// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#include "../terms/typeuniverse.h"
#include <sstream>
#include <assert.h>


namespace msat {

//-----------------------------------------------------------------------------
// DataType
//-----------------------------------------------------------------------------

const std::string &DataType::get_name() const
{
    if (!is_simple()) {
        throw TypeUniverse::error("Not a simple type!");
    }
    return name_;
}


const DataType *DataType::get_component(size_t idx) const
{
    return types_[idx];
}


size_t DataType::hash() const
{
    if (is_simple()) return id_;
    size_t ret = 0;
    for (size_t i = 0; i < types_.size(); ++i) {
        ret ^= types_[i]->hash() + (ret << 6) + (ret >> 2);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// TypeUniverse
//-----------------------------------------------------------------------------

TypeUniverse::TypeUniverse():
    store_(), subtypes_(), next_id_(2), application_(1, "->")
{
    // Nothing to do
}


TypeUniverse::~TypeUniverse()
{
    // Nothing to do
}

bool TypeUniverse::is_subtype(const DataType *s, const DataType *m) const
{
    if (s == m) {
        return true;
    }
    SubtypeMap::const_iterator i = subtypes_.find(s);
    if (i != subtypes_.end()) {
        return is_subtype(i->second, m);
    } else if (s->get_arity() > 0 && s->get_arity() == m->get_arity()) {
        for (size_t i = 0, sz = s->get_arity(); i < sz; ++i) {
            if (!is_subtype(s->get_component(i), m->get_component(i))) {
                return false;
            }
        }
        return true;
    }
    return false;
}

} // namespace msat
