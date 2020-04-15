// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Defines the Exception class, the root of all exceptions raised by MathSAT
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#include "../utils/exception.h"
#include <iostream>
#include <assert.h>

namespace msat {

#ifndef NDEBUG
volatile sig_atomic_t exceptions_dump_and_raise_assertion = false;
#endif

void Exception::dump_msg_and_raise_assertion() throw()
{
#ifndef NDEBUG
    if (exceptions_dump_and_raise_assertion) {
        std::cerr << "MathSAT EXCEPTION: " << what() << std::endl;
        assert(false);
    }
#endif
}

} // namespace msat
