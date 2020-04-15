// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef NUMFLATZINCDOMAIN_H_INCLUDED
#define NUMFLATZINCDOMAIN_H_INCLUDED

#include "../utils/numbers.h"
#include "../utils/smartptr.h"
#include "../utils/flatzincdomain.h"
#include<vector>

namespace msat {

template class FlatZincDomain<Number>;

typedef FlatZincDomain<Number> NumFlatZincDomain;
typedef std::vector<NumFlatZincDomain> NumFlatZincDomainList;

typedef SharedPtr<FlatZincDomain<Number> > NumFlatZincDomainSharedPtr;
typedef std::vector<NumFlatZincDomainSharedPtr> NumFlatZincDomainSharedPtrList;

} // namespace msat

#endif
