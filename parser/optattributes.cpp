// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../parser/optattributes.h"

namespace msat {
namespace opt {

//-----------------------------------------------------------------------------
// OptAttributes
//-----------------------------------------------------------------------------

OptAttributes::OptAttributes()
    : lower_(NULL), upper_(NULL), weight_(NULL),
      id_(""), signed_(false)
{
    // nothing to do
}

void OptAttributes::reset()
{
    lower_ = NULL;
    upper_ = NULL;
    weight_ = NULL;
    id_ = "";
    signed_ = false;
}

//-----------------------------------------------------------------------------
// Setters
//-----------------------------------------------------------------------------

void OptAttributes::set_lower(Term v)
{
    lower_ = v;
}

void OptAttributes::set_upper(Term v)
{
    upper_ = v;
}

void OptAttributes::set_weight(Term v)
{
    weight_ = v;
}

void OptAttributes::set_id(std::string v)
{
    id_ = v;
}

void OptAttributes::set_signed(bool v)
{
    signed_ = v;
}


//-----------------------------------------------------------------------------
// Getters
//-----------------------------------------------------------------------------

Term OptAttributes::get_lower() const
{
    return lower_;
}

Term OptAttributes::get_upper() const
{
    return upper_;
}

Term OptAttributes::get_weight() const
{
    return weight_;
}

std::string OptAttributes::get_id() const
{
    return id_;
}

bool OptAttributes::get_signed() const
{
    return signed_;
}


} /*** namespace msat::opt ***/
} /*** namespace msat ***/

