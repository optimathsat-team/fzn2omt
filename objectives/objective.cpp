// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../objectives/objective.h"

namespace msat {
namespace opt {

//-----------------------------------------------------------------------------
// Objective
//-----------------------------------------------------------------------------

Objective::Objective(Term obj, Objective::goal g, bool strict,
        Term cvar, Term cvar_proxy, Term bounds_proxy,
        Term incr_proxy, Term ass_constr, bool bounded_decl)
    : obj_(obj), goal_(g), strict_bound_(strict), cvar_(cvar),
      cvar_proxy_(cvar_proxy), bounds_proxy_(bounds_proxy),
      incr_proxy_(incr_proxy), ass_constr_(ass_constr),
      bounded_decl_(bounded_decl)
{
    // nothing to do
}

Objective::~Objective()
{
    /// nothing to do
}

} /*** namespace msat::opt ***/
} /*** namespace msat ***/
