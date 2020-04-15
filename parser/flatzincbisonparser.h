// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.


#ifndef FLATZINCBISONPARSER_H_INCLUDED
#define FLATZINCBISONPARSER_H_INCLUDED

#include "../utils/smartptr.h"
#include "../parser/flatzincannotation.h"
#include "../utils/flatzincset.h"

typedef void *yyscan_t;

namespace msat {

class FlatZincAbstractParser;

typedef SharedPtr<TermList> TermListSharedPtr;
typedef SharedPtr<FlatZincSet> FznSetSharedPtr;
typedef std::vector<FznSetSharedPtr> FznSetList;
typedef SharedPtr<FznSetList> FznSetListSharedPtr;

struct FznNode {
    TermListSharedPtr termlist_;
    FznSetSharedPtr set_;
    FznSetListSharedPtr set_list_;
};

} // namespace


#include "../parser/flatzincbisonparser.hh"

#endif
