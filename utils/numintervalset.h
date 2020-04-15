// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef NUMINTERVALSET_H_INCLUDED
#define NUMINTERVALSET_H_INCLUDED

#include "../utils/numbers.h"
#include "../utils/intervalset.h"

namespace msat {

template class IntervalSet<Number>;

typedef IntervalSet<Number> NumIntervalSet;

} // namespace msat
#endif
