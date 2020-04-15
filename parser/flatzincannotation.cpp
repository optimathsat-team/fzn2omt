// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../parser/flatzincannotation.h"

namespace msat {

//-----------------------------------------------------------------------------
// FlatZincAnnotation Methods
//-----------------------------------------------------------------------------

FlatZincAnnotation::FlatZincAnnotation():
    output_var_(false), output_array_(false)
{
    // nothing to do
}

FlatZincAnnotation::~FlatZincAnnotation()
{
    // nothing to do
}

bool FlatZincAnnotation::is_output_var()
{
    return output_var_;
}

bool FlatZincAnnotation::is_output_array(std::vector<int64_t> &out)
{
    if (output_array_) {
        out = oa_shape_;
    }
    return output_array_;
}

void FlatZincAnnotation::set_output_var()
{
    output_var_ = true;
}

void FlatZincAnnotation::set_output_array(std::vector<int64_t> &in)
{
    oa_shape_.swap(in);
    output_array_ = true;
}

} // namespace msat
