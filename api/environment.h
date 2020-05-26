// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#ifndef MSAT_ENVIRONMENT_H_INCLUDED
#define MSAT_ENVIRONMENT_H_INCLUDED

#include "../terms/termmanager.h"
#include "../configuration.h"

namespace msat {

class Environment {
public:
    void assert_formula_ric(Term formula, bool last, bool isreal);
    void assert_formula(Term term);

    Environment(Configuration *config, bool api_trace = true);

    Environment(Configuration *config, TermManager *mgr, bool api_trace = true);
    
    virtual ~Environment();

    const DataType *get_bool_type();
    const DataType *get_rational_type();
    const DataType *get_integer_type();

    ///----------------------------------------------------------------------
    /// Term creation
    ///----------------------------------------------------------------------

    Term make_true();
    Term make_false();
    Term make_iff(Term t1, Term t2);
    Term make_or(Term t1, Term t2);
    Term make_and(Term t1, Term t2);
    Term make_not(Term t);
    Term make_equal(Term t1, Term t2);
    Term make_eq(Term t1, Term t2);
    Term make_leq(Term t1, Term t2);
    Term make_plus(Term t1, Term t2);
    Term make_times(Term t1, Term t2);
    Term make_divide(Term t1, Term t2);
    Term make_number(const Number &n);
    Term make_number(int n);
    Term make_floor(Term t);
    Term make_term_ite(Term c, Term tt, Term te);
    Term make_constant(const Symbol *var);
    
    bool is_true(Term t);
    bool is_false(Term t);
    bool is_boolean_constant(Term t);
    bool is_atom(Term t);
    bool is_number(Term t, Number *out=NULL);
    bool is_and(Term t);
    bool is_or(Term t);
    bool is_not(Term t);
    bool is_iff(Term t);
    bool is_constant(Term t);
    bool is_equal(Term t);
    bool is_equality(Term t, const DataType **out_tp=NULL);
    bool is_leq(Term t);
    bool is_plus(Term t);
    bool is_times(Term t);
    bool is_divide(Term t);
    bool is_floor(Term t);

    enum status {
        UNKNOWN = -1,
        UNSAT = 0,
        SAT = 1
    };

    enum OMT_languages{
        OPTIMATHSAT = 0,
        Z3 = 1,
        CVC4 = 2,
        BCLT = 3
    };

    TermManager *get_term_manager() { return mgr_; }

protected:
    Configuration config_;
    ///< the configuration of this environment

    TermManager *mgr_;
    ///< the term manager

    bool owns_mgr_;
    status last_check_status_;
    bool bv_;
    int language_;
    ///< true if this environment is the owner of the TermManager
};

//-----------------------------------------------------------------------------
// Implementation of inline methods
//-----------------------------------------------------------------------------

inline const DataType *Environment::get_bool_type()
{ return mgr_->get_bool_type(); }

inline const DataType *Environment::get_rational_type()
{ return mgr_->get_rational_type(); }

inline const DataType *Environment::get_integer_type()
{ return mgr_->get_integer_type(); }

inline Term Environment::make_true() { return mgr_->make_true(); }

inline Term Environment::make_false() { return mgr_->make_false(); }

inline Term Environment::make_iff(Term t1, Term t2)
{ return mgr_->make_iff(t1, t2); }

inline Term Environment::make_or(Term t1, Term t2)
{ return mgr_->make_or(t1, t2); }

inline Term Environment::make_and(Term t1, Term t2)
{ return mgr_->make_and(t1, t2); }

inline Term Environment::make_not(Term t)
{ return mgr_->make_not(t); }

inline Term Environment::make_equal(Term t1, Term t2)
{ return mgr_->make_equal(t1, t2); }

inline Term Environment::make_eq(Term t1, Term t2)
{
    if (mgr_->is_bool_type(t1->get_type())) {
        return make_iff(t1, t2);
    } else {
        return make_equal(t1, t2);
    }
}

inline Term Environment::make_leq(Term t1, Term t2)
{ return mgr_->make_leq(t1, t2); }

inline Term Environment::make_plus(Term t1, Term t2)
{ return mgr_->make_plus(t1, t2); }

inline Term Environment::make_times(Term t1, Term t2)
{ return mgr_->make_times(t1, t2); }

inline Term Environment::make_divide(Term t1, Term t2)
{ return mgr_->make_divide(t1, t2); }

inline Term Environment::make_floor(Term t) { return mgr_->make_floor(t); }

inline Term Environment::make_number(const Number &n)
{ return mgr_->make_number(n); }

inline Term Environment::make_number(int n)
{ return mgr_->make_number(n); }

inline Term Environment::make_term_ite(Term c, Term tt, Term te)
{ return mgr_->make_term_ite(c, tt, te); }

inline Term Environment::make_constant(const Symbol *var)
{ return mgr_->make_constant(var); }

inline bool Environment::is_true(Term t)
{ return mgr_->is_true(t->get_symbol()); }

inline bool Environment::is_false(Term t)
{ return mgr_->is_false(t->get_symbol()); }

inline bool Environment::is_boolean_constant(Term t)
{
    return mgr_->is_constant(t->get_symbol()) &&
        mgr_->is_bool_type(t->get_type());
}

inline bool Environment::is_atom(Term t)
{ return mgr_->is_atom(t); }

inline bool Environment::is_number(Term t, Number *out)
{ return mgr_->is_number(t->get_symbol(), out); }

inline bool Environment::is_and(Term t)
{ return mgr_->is_and(t->get_symbol()); }

inline bool Environment::is_or(Term t)
{ return mgr_->is_or(t->get_symbol()); }

inline bool Environment::is_not(Term t)
{ return mgr_->is_not(t->get_symbol()); }

inline bool Environment::is_iff(Term t)
{ return mgr_->is_iff(t->get_symbol()); }

inline bool Environment::is_constant(Term t)
{ return mgr_->is_constant(t->get_symbol()); }

inline bool Environment::is_equal(Term t)
{ return is_equality(t); }

inline bool Environment::is_equality(Term t, const DataType **out_tp)
{ return mgr_->is_equality(t->get_symbol(), out_tp); }

inline bool Environment::is_leq(Term t)
{ return mgr_->is_leq(t->get_symbol()); }

inline bool Environment::is_plus(Term t)
{ return mgr_->is_plus(t->get_symbol()); }

inline bool Environment::is_times(Term t)
{ return mgr_->is_times(t->get_symbol()); }

inline bool Environment::is_divide(Term t)
{ return mgr_->is_divide(t->get_symbol()); }

inline bool Environment::is_floor(Term t)
{ return mgr_->is_floor(t->get_symbol()); }

} // namespace msat

#endif // MSAT_ENVIRONMENT_H_INCLUDED
