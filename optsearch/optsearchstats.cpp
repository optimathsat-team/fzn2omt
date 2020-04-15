// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../optsearch/optsearchstats.h"
#include "../utils/rusage.h"

namespace msat {
namespace opt {

//-----------------------------------------------------------------------------
// OptSearchStats
//-----------------------------------------------------------------------------

OptSearchStats::OptSearchStats()
    : start_time_(0.0), first_sol_time_(0.0),
      optimization_time_(0.0), certification_time_(0.0),
      search_steps_(0), bin_search_steps_(0), lin_search_steps_(0),
      sat_bin_search_steps_(0), sat_lin_search_steps_(0),
      memory_(0)/*, dpll_(NULL)*/
{
    memset(&start_, 0, sizeof(start_));
    memset(&end_, 0, sizeof(end_));
}

OptSearchStats::~OptSearchStats()
{
    /// nothing to do
}

void OptSearchStats::reset()
{
    memset(&start_, 0, sizeof(start_));
    memset(&end_, 0, sizeof(end_));
    start_time_ = 0.0;
    first_sol_time_ = 0.0;
    optimization_time_ = 0.0;
    certification_time_ = 0.0;
    search_steps_ = 0;
    bin_search_steps_ = 0;
    lin_search_steps_ = 0;
    sat_bin_search_steps_ = 0;
    sat_lin_search_steps_ = 0;
    memory_ = 0;
}

bool OptSearchStats::has_sat_linear_step() const
{
    return sat_lin_search_steps_ > 0;
}

bool OptSearchStats::has_sat_binary_step() const
{
    return sat_bin_search_steps_ > 0;
}


//-----------------------------------------------------------------------------
// Setters
//-----------------------------------------------------------------------------

void OptSearchStats::search_start()
{

}

void OptSearchStats::search_is_sat(bool first)
{
    double delta_time = msat::get_cpu_time_sec()
                        - start_time_;
    if (first) {
        first_sol_time_ = delta_time;
    } else {
        optimization_time_ = delta_time
                             - first_sol_time_;
    }
    // NOTE: needed for partial/timed optimization
}

void OptSearchStats::search_end()
{
    double delta_time = msat::get_cpu_time_sec()
                        - start_time_;
    certification_time_ = delta_time
                          - optimization_time_
                          - first_sol_time_;
    memory_ = get_mem_used_bytes();
}

void OptSearchStats::linear_step()
{
    lin_search_steps_++;
    search_steps_++;
}

void OptSearchStats::binary_step()
{
    bin_search_steps_++;
    search_steps_++;
}

void OptSearchStats::linear_step_sat()
{
    sat_lin_search_steps_++;
}

void OptSearchStats::binary_step_sat()
{
    sat_bin_search_steps_++;
}


//-----------------------------------------------------------------------------
// Getters
//-----------------------------------------------------------------------------

size_t OptSearchStats::get_search_steps() const
{
    return search_steps_;
}

size_t OptSearchStats::get_bin_search_steps() const
{
    return bin_search_steps_;
}

size_t OptSearchStats::get_lin_search_steps() const
{
    return lin_search_steps_;
}

size_t OptSearchStats::get_sat_search_steps() const
{
    return sat_bin_search_steps_
           + sat_lin_search_steps_;
}

size_t OptSearchStats::get_sat_bin_search_steps() const
{
    return sat_bin_search_steps_;
}

size_t OptSearchStats::get_sat_lin_search_steps() const
{
    return sat_lin_search_steps_;
}

uint64_t OptSearchStats::get_restarts() const
{
    return end_.restarts;
}

uint64_t OptSearchStats::get_decisions() const
{
    return end_.decisions;
}

uint64_t OptSearchStats::get_random_decisions() const
{
    return end_.random_decisions;
}

uint64_t OptSearchStats::get_propagations() const
{
    return end_.propagations;
}

uint64_t OptSearchStats::get_theory_propagations() const
{
    return end_.theory_propagations;
}

uint64_t OptSearchStats::get_watch_visits() const
{
    return end_.watch_visits;
}

uint64_t OptSearchStats::get_binary_watch_visits() const
{
    return end_.binary_watch_visits;
}

uint64_t OptSearchStats::get_conflicts() const
{
    return end_.conflicts;
}

uint64_t OptSearchStats::get_theory_conflicts() const
{
    return end_.theory_conflicts;
}

uint64_t OptSearchStats::get_delta_restarts() const
{
    return end_.restarts
           - start_.restarts;
}

uint64_t OptSearchStats::get_delta_decisions() const
{
    return end_.decisions
           - start_.decisions;
}

uint64_t OptSearchStats::get_delta_random_decisions() const
{
    return end_.random_decisions
           - start_.random_decisions;
}

uint64_t OptSearchStats::get_delta_propagations() const
{
    return end_.propagations
           - start_.propagations;
}

uint64_t OptSearchStats::get_delta_theory_propagations() const
{
    return end_.theory_propagations
           - start_.theory_propagations;
}

uint64_t OptSearchStats::get_delta_watch_visits() const
{
    return end_.watch_visits
           - start_.watch_visits;
}

uint64_t OptSearchStats::get_delta_binary_watch_visits() const
{
    return end_.binary_watch_visits
           - start_.binary_watch_visits;
}

uint64_t OptSearchStats::get_delta_conflicts() const
{
    return end_.conflicts
           - start_.conflicts;
}

uint64_t OptSearchStats::get_delta_theory_conflicts() const
{
    return end_.theory_conflicts
           - start_.theory_conflicts;
}

double OptSearchStats::get_time_since_start() const
{
    return msat::get_cpu_time_sec()
           - start_time_;
}

double OptSearchStats::get_time_global() const
{
    return first_sol_time_
           + optimization_time_
           + certification_time_;
}

double OptSearchStats::get_time_sat() const
{
    return first_sol_time_;
}

double OptSearchStats::get_time_optimization() const
{
    return optimization_time_;
}

double OptSearchStats::get_time_certification() const
{
    return certification_time_;
}

double OptSearchStats::get_mb_memory() const
{
    return double(memory_)/1048576.0;
}

} /*** namespace msat::opt ***/
} /*** namespace msat ***/
