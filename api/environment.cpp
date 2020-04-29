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
    config_ = config;
   }

Environment::Environment(Configuration *config, bool api_trace)
   {
    mgr_ = new TermManager(config->bv_);
    bv_ = config->bv_;
   }

Environment::~Environment()
{
    
}

void Environment::assert_formula_ric(Term formula, bool last, bool isreal){
    int arity = formula->get_children_number();
    std::string name(formula->get_symbol()->get_name());
    if(arity == 0){
        if(bv_ && formula->get_type() == mgr_->get_integer_type()){            
            std::replace(name.begin(), name.end(), ':', '_');
            std::string name2 = std::to_string(atoi(name.c_str()));
            if(name2.compare(name) == 0 && !isreal){
                std::cout<<"((_ to_bv 25)" <<name<<") ";
            }
            else{
                std::cout<<name;
            }
            if(!last)
                std::cout<<" ";
        }
        else{
            std::string name(formula->get_symbol()->get_name());
            std::replace(name.begin(), name.end(), ':', '_');
            std::cout<<name;
            if(!last)
                std::cout<<" ";
        }
        
    }
    else{
        if(bv_ && name.compare("-") == 0){
            std::cout<<"(bvneg"<<" ";
        }
        else{
            std::cout<<"(" << formula->get_symbol()->get_name()<<" ";
        }
        bool x = formula->get_type() == mgr_->get_rational_type();
        for(int i=0; i<arity; i++){
            assert_formula_ric(formula->get_child(i), i == arity-1,x);
        }
        std::cout<<")";
    }
}

void Environment::assert_formula(Term formula)
{
    std::cout<<"(assert ";
    assert_formula_ric(formula, true, false);
    std::cout<<")\n";
}

} // namespace msat
