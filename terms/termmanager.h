// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#ifndef MSAT_TERMMANAGER_H_INCLUDED
#define MSAT_TERMMANAGER_H_INCLUDED

#include "../terms/typeuniverse.h"
#include "../terms/signature.h"
#include "../terms/term.h"
#include "../utils/numbers.h"
#include <unordered_set>
#include<utility>
#include <unordered_map>
#include <iostream>


namespace msat {

class TermManager {
public:
    static const char INTERNAL_SYMBOLS_NAMESPACE = '.';
    static const char VARIABLE_SYMBOLS_NAMESPACE = '\'';
    static const char MODEL_SYMBOLS_NAMESPACE = '@';
    
    TermManager();
    ///< constructor

    virtual ~TermManager();
    ///< destructor

    ///< printer
    void declare_var_print(const Symbol *expr);

    /// new functions
    const DataType *make_simple_type(const std::string &name);

    // methods to retrieve standard types
    const DataType *get_bool_type() const;
    const DataType *get_rational_type() const;
    const DataType *get_integer_type() const;
    
    // methods to check for standard types
    bool is_bool_type(const DataType *tp) const;
    bool is_rational_type(const DataType *tp) const;
    bool is_integer_type(const DataType *tp) const;
    bool is_array_type(const DataType *tp,
                       const DataType **out_indextp=NULL,
                       const DataType **out_elemtp=NULL) const;

    bool is_subtype(const DataType *subtp, const DataType *supertp) const;

    // methods to retrieve standard symbols
    const Symbol *get_true() const;
    const Symbol *get_false() const;
    const Symbol *get_and() const;
    const Symbol *get_or() const;
    const Symbol *get_not() const;
    const Symbol *get_iff() const;

    const Symbol *get_rational_plus() const;
    const Symbol *get_rational_times() const;
    const Symbol *get_rational_leq() const;
    const Symbol *get_divide() const;

    const Symbol *get_integer_plus() const;
    const Symbol *get_integer_times() const;
    const Symbol *get_integer_leq() const;
    const Symbol *get_floor() const;

    const Symbol *get_pi() const;
    const Symbol *get_exp() const;
    const Symbol *get_sin() const;
    const Symbol *get_log() const;
    
    const Symbol *get_symbol(const std::string &name) const;

    // methods to check for standard symbols
    bool is_true(const Symbol *s) const;
    bool is_false(const Symbol *s) const;
    bool is_and(const Symbol *s) const;
    bool is_or(const Symbol *s) const;
    bool is_not(const Symbol *s) const;
    bool is_iff(const Symbol *s) const;

    bool is_equality(const Symbol *s, const DataType **out_argtp=NULL) const;
    bool is_int_modular_congruence(const Symbol *s, Number *out_mod=NULL) const;
    
    bool is_leq(const Symbol *s, const DataType **out_argtp=NULL) const;

    bool is_plus(const Symbol *s, const DataType **out_argtp=NULL) const;
    bool is_times(const Symbol *s, const DataType **out_argtp=NULL) const;
    bool is_divide(const Symbol *s) const;
    bool is_floor(const Symbol *s) const;

    bool is_number(const Symbol *s, Number *out_numval=NULL) const;

    bool is_constant(const Symbol *s) const;

    bool is_variable(const Symbol *s) const;
    
    bool is_atom(Term term) const;
    bool is_literal(Term term) const;

    // symbol creation methods
    const Symbol *make_symbol(const std::string &name, const DataType *tp);
    const Symbol *make_unique_symbol(const std::string &prefix,
                                     const DataType *tp);

    const Symbol *make_term_ite_symbol(const DataType *argtype);
    const Symbol *make_int_modular_congruence_symbol(const Number &modulus);

    // term creation methods
    Term make_true();
    Term make_false();
    Term make_and(Term t1, Term t2);
    Term make_or(Term t1, Term t2);
    Term make_not(Term t);
    Term make_iff(Term t1, Term t2);

    Term make_constant(const Symbol *symb);

    Term make_equal(Term t1, Term t2);
    Term make_term_ite(Term c, Term t, Term e);
    
    Term make_number(const Number &num);
    Term make_number(int num) { return make_number(Number(num)); }
    Term make_leq(Term t1, Term t2);
    Term make_plus(Term t1, Term t2);
    Term make_times(Term t1, Term t2);
    Term make_divide(Term t1, Term t2);
    Term make_int_modular_congruence(const Number &modulus, Term t1, Term t2);
    Term make_floor(Term t);

    Term make_term(const Symbol *symb);
    
    Term make_term(const Symbol *symb, std::vector<Term> children);

    Term do_make_term(const Symbol *symb, const TermList &args);

protected:
    void typecheck(const Symbol *symb, const TermList &args);
    void typecheck(Term term, const DataType *tp,
                   const char *where) const;

private:

    struct DataType_eq {
        bool operator()(const DataType *t1, const DataType *t2) const
        {
            return t1 == t2;
        }
    };
    
    struct DataType_hash {
        size_t operator()(const DataType *tp) const
        {
            return tp->hash();
        }
    };

    struct Term_eq {
        bool operator()(Term t1, Term t2) const;
    };

    /**
     * Hash function for terms in the termbank
     */ 
    struct Term_hash {
        size_t operator()(Term t) const;
    };

    static const char INTERPRETED_SYMBOLS_NAMESPACE = '`';
    
    void initialize_standard_signature();

    Term make_bin(const Symbol *symb, Term t1, Term t2,
                         const char *where);

    typedef std::unordered_set<DataType *, DataType_hash, DataType_eq> TypeStore;
    typedef std::unordered_set<Term_ *, Term_hash, Term_eq> TermStore;

    const Symbol *add_interpreted_symbol(const std::string name, const DataType *tp);

    TypeUniverse *universe_;
    Signature *sig_;
    TypeStore type_store_;
    TermStore term_store_;

    const DataType *boolean_;
    const DataType *rational_;
    const DataType *integer_;

    const Symbol *true_;
    const Symbol *false_;
    const Symbol *and_;
    const Symbol *or_;
    const Symbol *not_;
    const Symbol *iff_;

    const Symbol *eq_rat_;
    const Symbol *leq_rat_;
    const Symbol *plus_rat_;
    const Symbol *times_rat_;
    const Symbol *divide_;

    const Symbol *eq_int_;
    const Symbol *leq_int_;
    const Symbol *plus_int_;
    const Symbol *times_int_;
    const Symbol *floor_;

    Term true_term_;
    Term false_term_;
    TermList children_buf_;

    size_t next_term_id_;
    unsigned int next_variable_idx_;
    size_t next_simple_type_id_;
    std::vector<int> t1;
    
    int smtlib_index_;
};

inline
const Symbol *TermManager::add_interpreted_symbol(const std::string name,
                                                  const DataType *tp)
{
    const Symbol *ret = sig_->add_symbol(name, tp);
    return ret;
}

inline const DataType *TermManager::get_bool_type() const { return boolean_; }
inline const DataType *TermManager::get_rational_type() const
{ return rational_; }
inline const DataType *TermManager::get_integer_type() const
{ return integer_; }

inline bool TermManager::is_bool_type(const DataType *tp) const
{ return tp == get_bool_type(); }
inline bool TermManager::is_rational_type(const DataType *tp) const
{ return tp == get_rational_type(); }
inline bool TermManager::is_integer_type(const DataType *tp) const
{ return tp == get_integer_type(); }


inline const Symbol *TermManager::get_true() const { return true_; }
inline const Symbol *TermManager::get_false() const { return false_; }
inline const Symbol *TermManager::get_and() const { return and_; }
inline const Symbol *TermManager::get_or() const { return or_; }
inline const Symbol *TermManager::get_not() const { return not_; }
inline const Symbol *TermManager::get_iff() const { return iff_; }

inline const Symbol *TermManager::get_symbol(const std::string &name) const
{ return sig_->get_symbol(name); }

inline const Symbol *TermManager::get_rational_plus() const
{ return plus_rat_; }
inline const Symbol *TermManager::get_rational_times() const
{ return times_rat_; }
inline const Symbol *TermManager::get_divide() const { return divide_; }
inline const Symbol *TermManager::get_rational_leq() const { return leq_rat_; }

inline const Symbol *TermManager::get_integer_plus() const
{ return plus_int_; }
inline const Symbol *TermManager::get_integer_times() const
{ return times_int_; }
inline const Symbol *TermManager::get_integer_leq() const { return leq_int_; }
inline const Symbol *TermManager::get_floor() const { return floor_; }

inline bool TermManager::is_true(const Symbol *s) const
{ 
    const Symbol *t = get_true();
    return s->get_name() == t->get_name() && s->get_type() == t->get_type();
}
inline bool TermManager::is_false(const Symbol *s) const
{ 
    const Symbol *t = get_false();
    return s->get_name() == t->get_name() && s->get_type() == t->get_type();
     }
inline bool TermManager::is_and(const Symbol *s) const
{ return s == get_and(); }
inline bool TermManager::is_or(const Symbol *s) const
{ return s == get_or(); }
inline bool TermManager::is_not(const Symbol *s) const
{ return s == get_not(); }
inline bool TermManager::is_iff(const Symbol *s) const
{ return s == get_iff(); }

inline bool TermManager::is_leq(const Symbol *s,
                                const DataType **out_argtp) const
{
    if (s == leq_rat_) {
        if (out_argtp) *out_argtp = get_rational_type();
        return true;
    } else if (s == leq_int_) {
        if (out_argtp) *out_argtp = get_integer_type();
        return true;
    } else {
        return false;
    }
}

inline bool TermManager::is_plus(const Symbol *s,
                                 const DataType **out_argtp) const
{
    if (s == plus_rat_) {
        if (out_argtp) *out_argtp = get_rational_type();
        return true;
    } else if (s == plus_int_) {
        if (out_argtp) *out_argtp = get_integer_type();
        return true;
    } else {
        return false;
    }
}

inline bool TermManager::is_times(const Symbol *s,
                                  const DataType **out_argtp) const
{
    if (s == times_rat_) {
        if (out_argtp) *out_argtp = get_rational_type();
        return true;
    } else if (s == times_int_) {
        if (out_argtp) *out_argtp = get_integer_type();
        return true;
    } else {
        return false;
    }
}

inline bool TermManager::is_divide(const Symbol *s) const
{ return s == divide_; }

inline bool TermManager::is_floor(const Symbol *s) const { return s == floor_; }

inline bool TermManager::is_equality(const Symbol *s,
                                     const DataType **out_argtp) const
{
    return false;
}


inline bool TermManager::is_number(const Symbol *s, Number *out_numval) const
{
    std::string name = s->get_name();
    //std::cout<<"is number "<<name<<std::endl;
    bool real = false;
    for (int i=0; i<name.length(); i++)
    {
        if(name[i] == '/' && !real){
            real = true;
        }
        else if (isdigit(name[i])){
            // DO NOTHING
        }
        else{
            return false;
        }
    }
    return true;
}


inline bool TermManager::is_atom(Term term) const
{
    return false;
}


inline bool TermManager::is_literal(Term term) const
{
    return false;
}

inline Term TermManager::make_term(const Symbol *symb)
{
    std::vector<Term> empty_vec;
    return make_term(symb, empty_vec);
}

inline Term TermManager::make_true() { return true_term_; }
inline Term TermManager::make_false() { return false_term_; }

} // namespace msat

#endif // MSAT_TERMMANAGER_H_INCLUDED
