// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#include "../terms/term.h"
#include <sstream>
#include<iostream>
#include<string.h>

namespace msat {

Term_::Term_(size_t id, const Symbol *symb):
    id_(id), symb_(symb)
{
    class_term_ = 25;
    term_name_ = symb->get_name();
    
}

size_t Term_::get_term_class() const{ 
    return class_term_;
}

void Term_::set_term_class(size_t t){ 
    class_term_ = t;
}

void Term_::add_child(const Term_ *t){
    children_.push_back(t);

    if(term_name_.compare("bvmul") == 0){
        class_term_ = std::max(class_term_, t->get_term_class() * 2);
    }else if(term_name_.compare("bvadd") == 0){
        class_term_ = std::max(class_term_, t->get_term_class() + 1);
    }else if(term_name_.compare("bvsub") == 0){
        class_term_ = std::max(class_term_, t->get_term_class() + 1);
    }else{
        class_term_ = std::max(class_term_, t->get_term_class());
    }
}

std::string Term_::to_str() const
{
    return term_name_;
}

} // namespace msat
