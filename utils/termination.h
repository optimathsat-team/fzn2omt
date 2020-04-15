// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// TerminationTest class, for supporting user-provided termination criteria
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_TERMINATION_H_INCLUDED
#define MSAT_TERMINATION_H_INCLUDED

#include "../utils/exception.h"

namespace msat {

class TerminationTest {
public:
    MSAT_DECLARE_EXCEPTION(terminated)

    TerminationTest() {}
    virtual ~TerminationTest() {}

    inline virtual void operator()() const throw(terminated) {}
};

} // namespace msat

#endif // MSAT_TERMINATION_H_INCLUDED
