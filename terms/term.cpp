// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#include "../terms/term.h"
#include <sstream>
#include<iostream>

namespace msat {

Term_::Term_(size_t id, const Symbol *symb):
    id_(id), symb_(symb)
{
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
}

std::string Term_::to_str() const
{
    return term_name_;
}

} // namespace msat
