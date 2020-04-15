// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef OPTATTRIBUTES_H_INCLUDED
#define OPTATTRIBUTES_H_INCLUDED

#include "../terms/term.h"
#include<string>
#include<vector>

namespace msat {

namespace opt {

class OptAttributes {
public:
    OptAttributes();

    void reset();

    void set_lower(Term v);
    void set_upper(Term v);
    void set_weight(Term v);
    void set_id(std::string v);
    void set_signed(bool v);

    Term get_lower() const;
    Term get_upper() const;
    Term get_weight() const;
    std::string get_id() const;
    bool get_signed() const;

private:
    Term lower_;
    Term upper_;
    Term weight_;
    std::string id_;
    bool signed_;
};

} /*** namespace msat::opt ***/
} /*** namespace msat ***/

#endif

