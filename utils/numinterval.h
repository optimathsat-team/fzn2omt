// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef NUMINTERVAL_H_INCLUDED
#define NUMINTERVAL_H_INCLUDED

#include "../utils/numbers.h"
#include "../utils/interval.h"

namespace msat {

template class Interval<Number>;

typedef Interval<Number> NumInterval;

} // namespace msat
#endif
