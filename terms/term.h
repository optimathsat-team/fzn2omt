// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#ifndef MSAT_TERM_H_INCLUDED
#define MSAT_TERM_H_INCLUDED

#include "../terms/signature.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <ostream>

namespace msat {

/**
 * Datastructure for representing a Term
 */

enum TYPECLASS{
    BASE_TERM,
    VALUE_SET,
    BOUNDED_TERM
};

class Term_ {
private:
    friend class TermManager;
    Term_(size_t id, const Symbol *symb);

public:
	size_t get_id() const; 

    const Symbol *get_symbol() const;

    const DataType *get_type() const;

    size_t get_term_class() const;

    size_t get_arity() const;

    void set_term_class(size_t t);

    void add_child(const Term_ *t);

    int get_children_number() const;

    const Term_ *get_child(size_t idx) const;

    std::string to_str() const;

private:
    size_t id_; 
    size_t class_term_;
    const Symbol *symb_; 
    std::string term_name_;
    
    std::vector<const Term_ *> children_; 

};

typedef Term_ const *Term;

Term const term_Undef = NULL;

inline size_t Term_::get_id() const { return id_; }

inline const Symbol *Term_::get_symbol() const { return symb_; }

inline const DataType *Term_::get_type() const { return symb_->get_output_type();}

inline int Term_::get_children_number() const { return children_.size(); }

inline size_t Term_::get_arity() const { return 0; }

inline const Term_ *Term_::get_child(size_t idx) const { return children_[idx]; }


}// namespace msat

namespace msat {

typedef std::vector<Term> TermList;
typedef std::unordered_set<Term> TermSet;
typedef std::unordered_map<Term, Term> TermMap;

}

#endif // MSAT_TERM_H_INCLUDED
