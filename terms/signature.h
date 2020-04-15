// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#ifndef MSAT_SIGNATURE_H_INCLUDED
#define MSAT_SIGNATURE_H_INCLUDED

#include "../terms/typeuniverse.h"
#include <unordered_map>
#include <string.h>

namespace msat {

/**
 * An element of a signature
 */
class Symbol {
private:
    friend class Signature;
    
    Symbol(size_t id, char *name, size_t arity, const DataType *tp);
    ///< private constructor. Symbols must be created inside a \a Signature

public:
    size_t get_id() const { return id_; }

    size_t get_arity() const { return arity_; }

    const char *get_name() const { return name_; }

    const DataType *get_type() const { return tp_; }

    const DataType *get_output_type() const;

    std::string to_str() const { return get_name(); }

private:
    size_t id_;
    char *name_; 

    size_t arity_;
    
    const DataType *tp_;
};


std::ostream &operator<<(std::ostream &out, const Symbol *s);


/**
 * A collection of symbols
 */
class Signature {
    
    struct CStr_eq {
        bool operator()(const char *s1, const char *s2) const
        {
            return strcmp(s1, s2) == 0;
        }
    };
    
    // typedefs
    typedef std::unordered_map<char *, Symbol *, std::hash<char *>, CStr_eq>
            SymbolTable;
    
public:
    
    Signature(TypeUniverse *universe);
    ///< constructor

    ~Signature();
    ///< destructor

    const Symbol *get_symbol(const std::string &name) const;
    const Symbol *get_symbol(const char *name) const;

    const Symbol *add_symbol(const std::string &name, const DataType *tp);
    const Symbol *add_symbol(const char *name, const DataType *tp);

    typedef SymbolTable::const_iterator iterator;
    typedef iterator const_iterator;
    iterator begin() const;
    iterator end() const;
    
private:
    TypeUniverse *universe_;
    SymbolTable symboltable_;
    size_t next_id_;
};


inline const Symbol *Signature::get_symbol(const std::string &name) const
{ return get_symbol(name.c_str()); }

inline
const Symbol *Signature::add_symbol(const std::string &name, const DataType *tp)
{ return add_symbol(name.c_str(), tp); }

} // namespace msat

#endif // MSAT_SIGNATURE_H_INCLUDED
