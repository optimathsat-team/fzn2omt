// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#include "../api/environment.h"
#include <algorithm>
using namespace std;
namespace msat {

void print_list(const TermList & list) {
    for (TermList::const_iterator i = list.begin(),
             e = list.end(); i!=e; ++i) {
       std::cout << "  " << *i;
    }
    std::cout << std::endl;
}

Environment::Environment(Configuration *config, TermManager *mgr, bool api_trace):
    mgr_(mgr)
   {
   }

Environment::Environment(Configuration *config, bool api_trace):
    mgr_(new TermManager())
   {
   }

Environment::~Environment()
{
    
}

void Environment::assert_formula_ric(Term formula, bool last){
    int arity = formula->get_children_number();
    if(arity == 0){
        std::string name(formula->get_symbol()->get_name());
        std::replace(name.begin(), name.end(), ':', '_');
        std::cout<<name;
        if(!last)
            std::cout<<" ";
    }
    else{
        std::cout<<"(" << formula->get_symbol()->get_name()<<" ";
        for(int i=0; i<arity; i++){
            assert_formula_ric(formula->get_child(i), i == arity-1);
        }
        std::cout<<")";
    }
}

void Environment::assert_formula(Term formula)
{
    std::cout<<"(assert (" << formula->get_symbol()->get_name()<<" "; 
    int arity = formula->get_children_number();
    if(arity > 0){
        for(int i=0; i<arity; i++){
            assert_formula_ric(formula->get_child(i), i == arity-1);
        }
    }
    std::cout<<"))\n";
}

} // namespace msat
