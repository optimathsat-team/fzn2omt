// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#include "../terms/signature.h"
#include <assert.h>
#include <iostream>

using namespace std;

namespace msat {

//-----------------------------------------------------------------------------
// Symbol
//-----------------------------------------------------------------------------

Symbol::Symbol(size_t id, char *name, size_t arity, const DataType *tp):
    id_(id), name_(name), arity_(arity), tp_(tp)
{

}


const DataType *Symbol::get_output_type() const
{
    return tp_;
}


//-----------------------------------------------------------------------------
// Signature
//-----------------------------------------------------------------------------

Signature::Signature(TypeUniverse *universe):
    universe_(universe), next_id_(1)
{
}


Signature::~Signature()
{
    
}


const Symbol *Signature::get_symbol(const char *name) const
{
    SymbolTable::const_iterator i = symboltable_.find(const_cast<char *>(name));
    if (i == symboltable_.end())
        return NULL; 
    else
       return i->second;
}


const Symbol *Signature::add_symbol(const char *name, const DataType *tp)
{
    const Symbol *ret = NULL;
    char *symbol_name = new char[strlen(name)+1];
    strcpy(symbol_name, name);
    size_t arity = 0;
    Symbol *s = new Symbol(next_id_, symbol_name, 0, tp);
    symboltable_[symbol_name] = s;
    return s;
}

Signature::iterator Signature::begin() const
{
    return symboltable_.begin();
}


Signature::iterator Signature::end() const
{
    return symboltable_.end();
}

} // namespace msat
