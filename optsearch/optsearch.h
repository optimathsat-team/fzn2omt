// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef OPTSEARCH_H_INCLUDED
#define OPTSEARCH_H_INCLUDED

#include "../terms/term.h"
#include "../terms/termmanager.h"
#include "../objectives/objective.h"
#include "../optsearch/optsearchstats.h"
#include<vector>

namespace msat {

class Environment;
class Configuration;

namespace opt {

class OptEnvironment;

class OptSearch {
public:
    typedef enum {
        UNKNOWN = 0,
        SAT_PARTIAL = 1,
        SAT_APPROX = 2,
        SAT_OPTIMAL = 3,
        UNSAT = 4
    } status;
    typedef enum {
        LINEAR_STEP = 0,
        BINARY_STEP = 1
    } search_step;
    typedef enum {
        LINEAR = 0,
        BINARY = 1,
        ADAPTIVE = 2,
    } search_strategy;

    OptSearch(Environment *env, const Objective *obj);
    ///< ownership of obj is acquired

    OptSearch *ref();
    void unref();
    size_t nrefs() const;

    virtual void reset();
    virtual void set_maxsmt_bounds(Term lower, Term upper) = 0;

    virtual bool search_should_start() const;
    ///< returns true if optimization search is not yet
    ///< started. It considers only the search status
    virtual bool search_had_some_progress() const;
    ///< returns true if optimization search has found
    ///< at least one solution (or is unsat). It considers
    ///< only the search status
    virtual bool search_was_sat() const;
    ///< returns true if optimization search has found
    ///< at least one solution (but not if it is unsat).
    ///< It considers only the search status
    virtual bool search_should_continue() const;
    ///< returns true if optimization search is not yet
    ///< concluded. It considers only the search status

    virtual bool theory_solver_enabled() const = 0;
    ///< returns true if the associated Theory Solver
    ///< is enabled.

    virtual void search_start() = 0;
    ///< marks the start of the optimization search on
    ///< this unit.
    search_step search_propose_next_step() const;
    ///< returns the proposed next search step based
    ///< on the state of this search unit
    //virtual Lit search_step_start(search_step ss) = 0;
    ///< starts a search step in this unit
    virtual bool search_get_progress_atom(Term &t, bool &negate,
                                          bool current = true) const = 0;
    ///< returns true if it could generate an atom to
    ///< force a progress in the optimization search
    virtual void search_step_unsat_pivot() = 0;
    ///< called when the pivot of this optsearch unit
    ///< is unsatisfiable
    virtual void search_step_unsat() = 0;
    ///< called when search space is unsatisfiable
    virtual void search_step_sat() = 0;
    ///< called when search space is satisfiable

    //virtual lbool get_pivot_value() const = 0;
    ///< returns the value of the current pivoting
    ///< branch variable, if any

    const Objective *get_objective() const;
    ///< returns a copy of the pointer to the objective

    virtual bool is_bounded() const = 0;
    ///< true if both lower and upper bounds are finite
    virtual bool is_lower_bounded() const = 0;
    ///< true if lower bound is finite
    virtual bool is_upper_bounded() const = 0;
    ///< true if upper bound is finite


    /*** TheoryManager ***/
    virtual void candidate_optimum_store(Term sol) = 0;
    virtual void candidate_optimum_store();
    virtual bool candidate_optimum_valid() const;
    virtual void candidate_optimum_discard();
    ///< TSolver may find an optimal solution, but it must
    ///< first be checked for theory combination compatibility
    ///< before being confirmed true


    /*** OptiMathSAT C-API ***/
    typedef enum {
        OPTIMUM = 0,
        INITIAL_LOWER = 1,
        INITIAL_UPPER = 2,
        FINAL_LOWER = 3,
        FINAL_UPPER = 4,
        FINAL_ERROR = 5,
        FINAL_TOLERANCE = 6
    } api_code;
    virtual bool value_is_unbounded(api_code code) const = 0;
    virtual bool value_is_minus_inf(api_code code) const = 0;
    virtual bool value_is_plus_inf(api_code code) const = 0;
    virtual bool value_is_strict(api_code code) const = 0;
    virtual int  value_get_epsilon(api_code code) const = 0;
    virtual Term value_to_term(api_code code,
                               Term inf = NULL,
                               Term eps = NULL) const = 0;
    virtual std::string value_to_z3_str(api_code code) = 0;
    virtual std::string value_to_str(api_code code) = 0;
    std::string to_z3_str();
    std::string to_str(char c = '#');
    status get_status() const { return status_; };

    /*** Search-Cuts Handling ***/
    virtual Term make_equal(Term val) const = 0;
    ///< return (= obj_var val)
    virtual Term make_worse_than(Term val) const = 0;
    ///< return (< val obj_var) when minimizing,
    ///< (< obj_var val) when maximizing
    virtual Term make_not_worse_than(Term val) const = 0;
    ///< return (<= obj_var val) when minimizing,
    ///< (<= val obj_var) when maximizing
    virtual Term make_better_than(Term val) const = 0;
    ///< return (< obj_var val) when minimizing,
    ///< (< val obj_var) when maximizing
    virtual Term make_not_better_than(Term val) const = 0;
    ///< return (<= val obj_var) when minimizing,
    ///< (<= obj_var val) when maximizing

    /*** Common Functions ***/
    static Term make_and_defs(TermManager *mgr,
                              std::vector<OptSearch *>::iterator begin,
                              std::vector<OptSearch *>::iterator end);
    ///< connects each cost function to its cost label
    static Term make_and_bounds(TermManager *mgr,
                                std::vector<OptSearch *>::iterator begin,
                                std::vector<OptSearch *>::iterator end);
    ///< gives a global scope to all bounds
    static Term make_codependent_costs(TermManager *mgr,
                                       std::vector<OptSearch *>::iterator begin,
                                       std::vector<OptSearch *>::iterator end);
    ///< improving the value of any objective cost_i
    ///< can restrict the feasible space of any other
    ///< goal cost_j
    static Term make_independent_costs(TermManager *mgr,
                                       std::vector<OptSearch *>::iterator begin,
                                       std::vector<OptSearch *>::iterator end);
    ///< improving the value of any objective cost_i
    ///< does not affect any other objective cost_j
    static void reset(std::vector<OptSearch *>::iterator begin,
                      std::vector<OptSearch *>::iterator end);
    ///< resets all objectives state so that a new
    ///< search can be started
    //static void set_partial_model_handler(OptModelFoundHook *hook,
    //                                      std::vector<OptSearch *>::iterator begin,
    //                                      std::vector<OptSearch *>::iterator end);
    ///< sets the partial model handler for each
    ///< optsearch unit

protected:
    virtual ~OptSearch();

    virtual bool has_solution() const = 0;
    virtual bool has_reached_goal() const = 0;
    virtual bool abs_threshold_condition() const
                { return false; };
    virtual bool tol_threshold_condition() const
                { return false; };

    virtual bool search_must_use_linear() const
                { return true; };
    ///< return true iff any T-specific condition
    ///< forces a linear step
    virtual bool search_adaptive_heuristic_use_linear() const
                { return true; };
    ///< return true iff adaptive heuristic
    ///< forces a linear step

    void reset_model();
    void store_model();
    ///< model handling

    void do_search_start();
    void do_search_step_start(search_step ss);
    void do_search_get_progress_atom() const;
    void do_search_step_unsat_pivot();
    void do_search_step_unsat();
    void do_search_step_sat();
    void do_check_termination();

    virtual void log_search_start();
    virtual void log_search_step_start();
    virtual void log_search_step_learn_pivot(Term piv);
    virtual void log_search_step_unsat();
    virtual void log_search_step_sat();
    virtual void log_search_terminated();
    virtual void log_update_lower_bound();
    virtual void log_update_upper_bound();

    status status_;
    search_step step_;
    search_strategy strategy_;
    size_t consec_pivotings_;
    bool verbose_;
    bool partial_;
    bool started_;

    Environment *env_;
    OptEnvironment *optenv_;
    Configuration *config_;
    TermManager *mgr_;
    const Objective *obj_;

private:
    void init();

    typedef enum {
        INITIAL,
        FINAL
    } int_code;
    std::string interval_to_z3_str(int_code c);
    std::string interval_to_str(int_code c);
    std::string label();
    std::string obj_fun();

    size_t stackid_;
    bool forced_linear_;
    bool candidate_stored_;
    OptSearchStats stats_;

    size_t refcount_;
}; /*** OptSearch ***/


//-----------------------------------------------------------------------------
// Compound types
//-----------------------------------------------------------------------------

typedef std::vector<OptSearch *> OptSearchList;
typedef OptSearchList::iterator optsearch_iterator;
typedef OptSearchList::reverse_iterator optsearch_reverse_iterator;


//-----------------------------------------------------------------------------
// Lifecycle management
//-----------------------------------------------------------------------------

inline OptSearch *OptSearch::ref()
{
    ++refcount_;
    return this;
}

inline void OptSearch::unref()
{
    assert(refcount_ > 0);
    --refcount_;
    if (!refcount_) {
        delete this;
    }
}

inline size_t OptSearch::nrefs() const { return refcount_; }

} /*** namespace msat::opt ***/
} /*** namespace msat ***/

#endif
