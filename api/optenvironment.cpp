// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../api/optenvironment.h"
#include "../terms/termmanager.h"
#include "pbmanager.h"


using namespace std;
namespace msat {
namespace opt {

OptEnvironment::OptEnvironment(Configuration *config)
    : Environment(config, false)
{

}

OptEnvironment::OptEnvironment(Configuration *config, TermManager *mgr)
    : Environment(config, mgr)
{

}

OptEnvironment::~OptEnvironment()
{

}

void OptEnvironment::assert_formula(Term formula)
{
    Environment::assert_formula(formula);
}

bool OptEnvironment::has_compatible_type(
        const DataType *dt, Term t) const
{
    bool ret = true;
    if (t) {
        const DataType *other = t->get_type();
        assert(other);
        ret = mgr_->is_subtype(dt, other)
              || mgr_->is_subtype(other, dt);
    }
    return ret;
}

bool OptEnvironment::is_constant_value(Term t) const
{
    bool ret = true;
    if (t) {
        ret = mgr_->is_number(t->get_symbol(), NULL);
    }
    return ret;
}

OptSearch *OptEnvironment::make_minimize(
        Term term, Term lower, Term upper,
        const std::string &id, bool bvsigned, bool strict)
{
    std::cout<<"(minimize "<<term->get_symbol()->get_name();
    if(lower)
        std::cout<<" :lower "<<lower->get_symbol()->get_name();
    if(upper)
        std::cout<<" :upper "<<upper->get_symbol()->get_name();
    std::cout<<")"<<std::endl;
    
    return NULL;
}

OptSearch *OptEnvironment::make_maximize(
        Term term, Term lower, Term upper,
        const std::string &id, bool bvsigned, bool strict)
{
    
    assert(term);
        std::cout<<"(maximize "<<term->get_symbol()->get_name();
    if(lower)
        std::cout<<" :lower "<<lower->get_symbol()->get_name();
    if(upper)
        std::cout<<" :upper "<<upper->get_symbol()->get_name();
    std::cout<<")"<<std::endl;

    return NULL;
    
}

Term OptEnvironment::make_circuit(
        TermList &clauses,
        TermList &weights,
        Term id){
    PBManager sum(mgr_, this, id);

    if (clauses.size() != weights.size()) {
        throw Exception("there must be the same number of clauses and weights");
    }
    for (size_t i = 0; i < clauses.size(); i++) {
        sum.assert_soft_formula(clauses[i], weights[i]);
    }
    
    Term ret = NULL;
    bool ok = sum.has_pending_push(ret);
    assert(ok);

    return ret;
}

void OptEnvironment::assert_optsearch(OptSearch *ptr)
{
    // Nothing to do
}


} // namespace opt
} // namespace msat
