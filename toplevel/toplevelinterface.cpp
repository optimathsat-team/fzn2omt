// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#include "../toplevel/toplevelinterface.h"
#include "../api/optenvironment.h"
#include <iomanip>

namespace msat {

ToplevelInterfaceImpl::ToplevelInterfaceImpl(Configuration *config):
    config_(config), env_(NULL),
    starttime_(0), endtime_(0)
{

}


ToplevelInterfaceImpl::~ToplevelInterfaceImpl()
{

}

} // namespace msat
