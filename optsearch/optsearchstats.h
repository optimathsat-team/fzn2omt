// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef OPTSEARCHSTATS_H_INCLUDED
#define OPTSEARCHSTATS_H_INCLUDED

namespace msat {

namespace opt {

class OptSearchStats {
public:
    OptSearchStats();
    virtual ~OptSearchStats();

    void reset(/*DpllSolver *dpll*/);

    bool has_sat_linear_step() const;
    bool has_sat_binary_step() const;

    /*** setters ***/
    void search_start();
    void search_is_sat(bool first);
    void search_end();
    void linear_step();
    void binary_step();
    void linear_step_sat();
    void binary_step_sat();

    /*** getters ***/
    size_t get_search_steps() const;
    size_t get_bin_search_steps() const;
    size_t get_lin_search_steps() const;

    size_t get_sat_search_steps() const;
    size_t get_sat_bin_search_steps() const;
    size_t get_sat_lin_search_steps() const;

    uint64_t get_restarts() const;
    uint64_t get_decisions() const;
    uint64_t get_random_decisions() const;
    uint64_t get_propagations() const;
    uint64_t get_theory_propagations() const;
    uint64_t get_watch_visits() const;
    uint64_t get_binary_watch_visits() const;
    uint64_t get_conflicts() const;
    uint64_t get_theory_conflicts() const;

    uint64_t get_delta_restarts() const;
    uint64_t get_delta_decisions() const;
    uint64_t get_delta_random_decisions() const;
    uint64_t get_delta_propagations() const;
    uint64_t get_delta_theory_propagations() const;
    uint64_t get_delta_watch_visits() const;
    uint64_t get_delta_binary_watch_visits() const;
    uint64_t get_delta_conflicts() const;
    uint64_t get_delta_theory_conflicts() const;

    double get_time_since_start() const;
    double get_time_global() const;
    double get_time_sat() const;
    double get_time_optimization() const;
    double get_time_certification() const;

    double get_mb_memory() const;

private:
    double start_time_;
    double first_sol_time_;
    double optimization_time_;
    double certification_time_;
    ///< time take up by optimization
    size_t search_steps_;
    size_t bin_search_steps_;
    size_t lin_search_steps_;
    size_t sat_bin_search_steps_;
    size_t sat_lin_search_steps_;
    ///< # of mixed binary/linear optimization steps
    size_t memory_;

}; /*** OptSearchStats ***/

} /*** namespace msat::opt ***/
} /*** namespace msat ***/

#endif
