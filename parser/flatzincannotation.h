// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCANNOTATION_H_INCLUDED
#define FLATZINCANNOTATION_H_INCLUDED

#include<inttypes.h>
#include<vector>

namespace msat {

//-----------------------------------------------------------------------------
// FlatZincAnnotation Class
//-----------------------------------------------------------------------------

class FlatZincAnnotation {
public:
    FlatZincAnnotation();
    virtual ~FlatZincAnnotation();

    bool is_output_var();
    bool is_output_array(std::vector<int64_t> &out);

    void set_output_var();
    void set_output_array(std::vector<int64_t> &in);

private:
    bool output_var_;
    bool output_array_;
    std::vector<int64_t> oa_shape_;
};

} // namespace msat

#endif
