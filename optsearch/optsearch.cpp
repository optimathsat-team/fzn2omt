// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "optimathsat/optsearch/optsearch.h"
#include "mathsat/api/environment.h"
#include "mathsat/dpll/dpllsolver.h"
#include "optimathsat/api/optenvironment.h"
#include<iomanip>
#include<sstream>

namespace msat {
namespace opt {

//-----------------------------------------------------------------------------
// OptSearch
//-----------------------------------------------------------------------------

OptSearch::OptSearch(Environment *env, const Objective *obj)
    : model_(NULL), env_(env), optenv_(NULL), config_(env_->get_config()),
      mgr_(env_->get_term_manager()), printer_(mgr_, &(config_->printer)),
      obj_(obj), model_handler_(NULL), refcount_(1)
{
    assert(env_);
    assert(obj_);
    optenv_ = static_cast<OptEnvironment*>(env_);
    init();
}

OptSearch::~OptSearch()
{
    assert(refcount_ <= 0);

    if (obj_) delete obj_;
    if (model_) model_->unref();
}

void OptSearch::init()
{
    config_ = env_->get_config();
    assert(config_);
    mgr_ = env_->get_term_manager();
    assert(mgr_);

    printer_ = SmtLib2TermPrinter(mgr_, &(config_->printer));

    status_ = UNKNOWN;
    step_ = LINEAR_STEP;
    strategy_ = (OptSearch::search_strategy) config_->dpll.search_strategy();
    candidate_stored_ = false;
    verbose_ = config_->dpll.print_partial_sol();
    partial_ = config_->dpll.stop_at_first_solution();
    started_ = false;

    stats_.reset(dpll_);

    consec_pivotings_ = 0;
    forced_linear_ = (LINEAR == strategy_)
                     || (Number(1) == config_->dpll.bint());

    assert((LINEAR == strategy_)
           || (BINARY == strategy_)
           || (ADAPTIVE == strategy_));

    reset_model();
}

void OptSearch::reset()
{
    init();
}


//-----------------------------------------------------------------------------
// Search Handling
//-----------------------------------------------------------------------------

bool OptSearch::search_should_start() const
{
    return !started_ && (UNKNOWN == status_);
}

bool OptSearch::search_had_some_progress() const
{
    return (SAT_PARTIAL == status_)
           || (SAT_OPTIMAL == status_)
           || (UNSAT == status_)
           || (SAT_APPROX == status_);
}

bool OptSearch::search_was_sat() const
{
    return (SAT_PARTIAL == status_)
           || (SAT_OPTIMAL == status_)
           || (SAT_APPROX == status_);
}

bool OptSearch::search_should_continue() const
{
    return started_ &&
           ((UNKNOWN == status_)
           || (SAT_PARTIAL == status_
               && !partial_));
}


//-----------------------------------------------------------------------------
// Search Step Handling
//-----------------------------------------------------------------------------

void OptSearch::do_search_start()
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);
    assert(SAT_PARTIAL != status_);

    stats_.search_start();
    started_ = true;
}

OptSearch::search_step OptSearch::search_propose_next_step() const
{
    bool linear = false;

    switch (strategy_) {
    case LINEAR:
        linear = true;
        break;
    case BINARY:
                    /* other reasons */
        linear = forced_linear_
                    /* T-specific requirements */
                || search_must_use_linear()
                    /* first step linear requirement */
                || (config_->dpll.first_step_linear()
                    && !stats_.has_sat_linear_step());
        break;
    case ADAPTIVE:
                    /* other reasons */
        linear = forced_linear_
                    /* T-specific requirements */
              || search_must_use_linear()
                    /* no linear step yet */
              || !stats_.has_sat_linear_step();

        if (!linear && stats_.has_sat_binary_step()) {
            linear = search_adaptive_heuristic_use_linear();
        }
        break;
    default:
        assert(false);
    }

    if (linear) {
        return LINEAR_STEP;
    } else {
        return BINARY_STEP;
    }
}

void OptSearch::do_search_step_start(search_step ss)
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);

    step_ = ss;

    switch(step_) {
    case LINEAR_STEP:
        stats_.linear_step();
        break;
    case BINARY_STEP:
        stats_.binary_step();
        break;
    default:
        assert(false);
    }
}

void OptSearch::do_search_get_progress_atom() const
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);
}

void OptSearch::do_search_step_unsat_pivot()
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);
    assert(BINARY_STEP == step_);

    consec_pivotings_++;
}

void OptSearch::do_search_step_unsat()
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);

    stats_.search_end();

    if (SAT_PARTIAL == status_) {
        status_ = SAT_OPTIMAL;
    } else {
        status_ = UNSAT;
    }

    if (verbose_) {
        log_search_terminated();
    }
}

void OptSearch::do_search_step_sat()
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);

    if (UNKNOWN == status_) {
        stats_.search_is_sat(true);
        status_ = SAT_PARTIAL;
    } else {
        stats_.search_is_sat(false);
    }

    switch(step_) {
    case LINEAR_STEP:
        stats_.linear_step_sat();
        break;
    case BINARY_STEP:
        stats_.binary_step_sat();
        break;
    default:
        assert(false);
    }

    consec_pivotings_ = 0;
}

void OptSearch::do_check_termination()
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);

    if (SAT_PARTIAL == status_
            && has_reached_goal()) {

        stats_.search_end();

        if (abs_threshold_condition()
                || tol_threshold_condition()) {
            status_ = SAT_APPROX;
        } else {
            status_ = SAT_OPTIMAL;
        }

        if (verbose_) {
            log_search_terminated();
        }
    }
}


//-----------------------------------------------------------------------------
// Getters
//-----------------------------------------------------------------------------

const Objective *OptSearch::get_objective() const
{
    return obj_;
}


//-----------------------------------------------------------------------------
// TheoryManager
//-----------------------------------------------------------------------------

void OptSearch::candidate_optimum_store()
{
    assert(UNSAT != status_);
    assert(SAT_OPTIMAL != status_);
    assert(SAT_APPROX != status_);
    assert(!candidate_stored_);
    candidate_stored_ = true;
}

bool OptSearch::candidate_optimum_valid() const
{
    return candidate_stored_;
}

void OptSearch::candidate_optimum_discard()
{
    assert(candidate_stored_);
    candidate_stored_ = false;
}


//-----------------------------------------------------------------------------
// OptiMathSAT C-API
//-----------------------------------------------------------------------------

std::string OptSearch::to_z3_str()
{
    std::ostringstream ss;
    std::string value = "";
    std::string descr = "";
    bool range = false;
    switch (status_) {
    case UNKNOWN:       /* no search / error / timeout */
        value = "unknown";
        descr = "";
        range = true;
        break;
    case SAT_PARTIAL:   /* error / no optimization / timeout */
        value = value_to_z3_str(OPTIMUM);
        descr = "partial search";
        range = true;
        break;
    case SAT_APPROX:    /* termination condition */
        value = value_to_z3_str(OPTIMUM);
        if (abs_threshold_condition()) {
            descr = "interval threshold";
        } else if (tol_threshold_condition()) {
            descr = "tolerance threshold";
        } else {
            assert(false);
        }
        range = true;
        break;
    case SAT_OPTIMAL:   /* certified optimum */
        value = value_to_z3_str(OPTIMUM);
        descr = "";
        break;
    case UNSAT:         /* unsat */
        value = "unsat";
        descr = "";
        break;
    default:
        assert(false);
    }

    ss << " (";
    printer_.print_atom(ss, obj_->get_obj_function());
    ss << " " << value << ")";

    if ("" != descr) {
        ss << ", " << descr;
    }
    if (range) {
        ss << ", range: "
           << interval_to_str(FINAL);
    }

    ss << "\n";

    return ss.str();
}

std::string OptSearch::to_str(char c)
{
    std::ostringstream ss;
    std::string header;
    std::string objfun;

    switch (obj_->get_goal()) {
    case Objective::MINIMIZE: header = "MINIMIZATION"; break;
    case Objective::MAXIMIZE: header = "MAXIMIZATION"; break;
    default: assert(false);
    }

    printer_.print_atom(ss, obj_->get_obj_function());
    objfun = ss.str();

    ss.str("");
    ss.clear();

    ss << c << c << c << " " << header << " STATS " << c << c << c << "\n"
       << c << " objective:      " << objfun << "\n"
       << c << " interval:     " << interval_to_str(INITIAL) << "\n"
       << c << "\n";

    switch (status_) {
    case UNKNOWN:       /* no search / error / timeout */
        ss << c << " Timeout reached!\n"
           << c << " Latest range: "
           << interval_to_str(FINAL) << "\n"
           << c << " No optimum found so far!\n";
        break;
    case SAT_PARTIAL:   /* error / no optimization / timeout */
        ss << c << " Timeout reached!\n"
           << c << " Latest range: "
           << interval_to_str(FINAL) << "\n"
           << c << " Approximated "
           << (value_is_strict(OPTIMUM) ? "strict"
                                        : "non-strict")
           << " optimum found!\n"
           << c << " Optimum: " << value_to_str(OPTIMUM) << "\n";
        break;
    case SAT_APPROX:    /* termination condition */
        if (abs_threshold_condition()) {
            ss << c << " Minimum range reached: |ub-lb| < "
               << config_->dpll.termination().to_str() << "!\n";
        } else if (tol_threshold_condition()) {
            ss << c << " Minimum range reached: "
               << "|(ub-lb)/(ub_init-lb_init)| < "
               << config_->dpll.tolerance().to_str() << "!\n";
        } else {
            assert(false);
        }
        ss << c << " Latest range: "
           << interval_to_str(FINAL) << "\n"
           << c << " Approximated "
           << (value_is_strict(OPTIMUM) ? "strict"
                                        : "non-strict")
           << " optimum found!\n"
           << c << " Optimum: " << value_to_str(OPTIMUM) << "\n";
        break;
    case SAT_OPTIMAL:   /* certified optimum */
        ss << c << " Search terminated!\n"
           << c << " Exact "
           << (value_is_strict(OPTIMUM) ? "strict"
                                        : "non-strict")
           << " optimum found!\n"
           << c << " Optimum: " << value_to_str(OPTIMUM) << "\n";
        break;
    case UNSAT:         /* unsat */
        ss << c << " Search terminated!\n"
           << c << " No solution.\n";
        break;
    default:
        assert(false);
    }

    ss << c << " Search steps: " << stats_.get_search_steps()
                    << " (sat: " << stats_.get_sat_search_steps() << ")\n"
       << c << "  - binary: " << stats_.get_bin_search_steps()
                 << " (sat: " << stats_.get_sat_bin_search_steps() << ")\n"
       << c << "  - linear: " << stats_.get_lin_search_steps()
                 << " (sat: " << stats_.get_sat_lin_search_steps() << ")\n";

    ss << c << " Restarts: " << stats_.get_delta_restarts()
       << " [session: "  << stats_.get_restarts()
       << "]\n"
       << c << " Decisions: " << stats_.get_delta_decisions()
       << " (" << stats_.get_delta_random_decisions() << " random)"
       << " [session: " << stats_.get_decisions()
       << " (" << stats_.get_random_decisions() << " random)"
       << "]\n"
       << c << " Propagations: " << stats_.get_delta_propagations()
       << " (" << stats_.get_delta_theory_propagations() << " theory)"
       << " [session: " << stats_.get_propagations()
       << " (" << stats_.get_theory_propagations() << " theory)"
       << "]\n"
       << c << " Watched clauses visited: " << stats_.get_delta_watch_visits()
       << " (" << stats_.get_delta_binary_watch_visits() << " binary)"
       << " [session: " << stats_.get_watch_visits()
       << " (" << stats_.get_binary_watch_visits() << " binary)"
       << "]\n"
       << c << " Conflicts: " << stats_.get_delta_conflicts()
       << " (" << stats_.get_delta_theory_conflicts() << " theory)"
       << " [session: " << stats_.get_conflicts()
       << " (" << stats_.get_theory_conflicts() << " theory)"
       << "]\n";

    ss << c << " Error:\n"
       << c << "  - absolute: " << value_to_str(FINAL_ERROR) << "\n"
       << c << "  - relative: " << value_to_str(FINAL_TOLERANCE) << "\n";

    ss << std::setprecision(3) << std::fixed;

    ss << c << " Total time: "        << stats_.get_time_global() << " s\n"
       << c << "  - first solution: " << stats_.get_time_sat() << " s\n"
       << c << "  - optimization: "   << stats_.get_time_optimization() << " s\n"
       << c << "  - certification: "  << stats_.get_time_certification() << " s\n";

    ss << c << " Memory used: " << stats_.get_mb_memory() << " MB\n";

    return ss.str();
}


//-----------------------------------------------------------------------------
// Logging
//-----------------------------------------------------------------------------

void OptSearch::log_search_start()
{
    (*log_) << loglevel(0) << flushlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") := " << obj_fun()
            << endlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") - "
            << "search start: "
            << interval_to_str(FINAL) // accounts for maxsmt updates
            << endlog;
}

void OptSearch::log_search_step_start()
{
    std::string step = "";
    size_t nsteps = 0;

    switch (step_) {
    case LINEAR_STEP:
        step = "linear";
        nsteps = stats_.get_lin_search_steps();
        break;
    case BINARY_STEP:
        step = "binary";
        nsteps = stats_.get_bin_search_steps();
        break;
    default:
        assert(false);
    }

    (*log_) << loglevel(0) << flushlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") - "
            << step << " step: " << nsteps
            << endlog;
}

void OptSearch::log_search_step_learn_pivot(Term piv)
{
    assert(piv);
    std::ostringstream ss;
    printer_.print_atom(ss, piv);

    (*log_) << loglevel(0) << flushlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") - "
            << "pivot: "
            << ss.str() << endlog;
}

void OptSearch::log_search_step_unsat()
{
    switch (obj_->get_goal()) {
    case Objective::MINIMIZE:
        log_update_lower_bound();
        break;
    case Objective::MAXIMIZE:
        log_update_upper_bound();
        break;
    default:
        assert(false);
    }
}

void OptSearch::log_search_step_sat()
{
    (*log_) << loglevel(0) << flushlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") - "
            << " new: "
            << value_to_str(OPTIMUM)
            << endlog;
}

void OptSearch::log_search_terminated()
{
    std::string status;
    switch (status_) {
    case UNKNOWN:
        status = "unknown";
        break;
    case SAT_PARTIAL:
        status = "sat_partial";
        break;
    case SAT_APPROX:
        status = "sat_approx";
        break;
    case SAT_OPTIMAL:
        status = "sat_optimal";
        break;
    case UNSAT:
        status = "unsat";
        break;
    default:
        assert(false);
    }

    (*log_) << loglevel(0) << flushlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") - "
            << "search end: " << status
            << endlog;
}

void OptSearch::log_update_lower_bound()
{
    (*log_) << loglevel(0) << flushlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") - "
            << " update lower: "
            << interval_to_str(FINAL)
            << endlog;
}

void OptSearch::log_update_upper_bound()
{
    (*log_) << loglevel(0) << flushlog;
    (*log_) << loglevel(0)
            << "# obj(" << label() << ") - "
            << " update upper: "
            << interval_to_str(FINAL)
            << endlog;
}

//-----------------------------------------------------------------------------
// Print Help Functions
//-----------------------------------------------------------------------------

std::string OptSearch::interval_to_z3_str(int_code c)
{
    api_code lower = (INITIAL == c ? INITIAL_LOWER
                                   : FINAL_LOWER);
    api_code upper = (INITIAL == c ? INITIAL_UPPER
                                   : FINAL_UPPER);
    std::ostringstream ss;
    ss << "[ "
       << value_to_z3_str(lower) << ", "
       << value_to_z3_str(upper) << " ]";
    return ss.str();
}

std::string OptSearch::interval_to_str(int_code c)
{
    api_code lower = (INITIAL == c ? INITIAL_LOWER
                                   : FINAL_LOWER);
    api_code upper = (INITIAL == c ? INITIAL_UPPER
                                   : FINAL_UPPER);
    std::ostringstream ss;
    ss << "[ "
       << value_to_str(lower) << ", "
       << value_to_str(upper) << " ]";
    return ss.str();
}

std::string OptSearch::label()
{
    std::ostringstream ss;
    printer_.print_atom(ss, obj_->get_obj_var());
    return ss.str();
}

std::string OptSearch::obj_fun()
{
    std::ostringstream ss;
    printer_.print_atom(ss, obj_->get_obj_function());
    return ss.str();
}


//-----------------------------------------------------------------------------
// Model Handling
//-----------------------------------------------------------------------------

ModelStore *OptSearch::get_model()
{
    return model_;
}

void OptSearch::reset_model()
{
    if (model_) {
        model_->unref();
        model_ = NULL;
    }
}

void OptSearch::store_model()
{
    reset_model();
    model_ = optenv_->build_model_store();

    if (model_ && model_handler_) {
        (*model_handler_)(this);
    }
}

void OptSearch::set_partial_model_handler(
        OptModelFoundHook *hook)
{
    model_handler_ = hook;
}

//-----------------------------------------------------------------------------
// Common Constraints
//-----------------------------------------------------------------------------

Term OptSearch::make_and_defs(
        TermManager *mgr,
        optsearch_iterator begin,
        optsearch_iterator end)
{
    assert(mgr);
    Term ret = mgr->make_true();
    for (optsearch_iterator it = begin; it != end; ++it) {
        OptSearch *opt = *it;
        /* all objectives, including those already optimized */
        const Objective *obj = opt->get_objective();
        assert(obj);
        ret = mgr->make_and(ret, obj->get_cost_var_proxy());
    }
    return ret;
}

Term OptSearch::make_and_bounds(
        TermManager *mgr,
        optsearch_iterator begin,
        optsearch_iterator end)
{
    assert(mgr);
    Term ret = mgr->make_true();
    for (optsearch_iterator it = begin; it != end; ++it) {
        OptSearch *opt = *it;
        /* all objectives, including those already optimized */
        const Objective *obj = opt->get_objective();
        assert(obj);
        ret = mgr->make_and(ret, obj->get_bounds_proxy());
    }
    return ret;
}

Term OptSearch::make_codependent_costs(
        TermManager *mgr,
        optsearch_iterator begin,
        optsearch_iterator end)
{
    assert(mgr);
    Term ret = mgr->make_true();
    for (optsearch_iterator it = begin; it != end; ++it) {
        OptSearch *opt = *it;
        /* all objectives, including those already optimized */
        const Objective *obj = opt->get_objective();
        assert(obj);
        ret = mgr->make_and(ret, obj->get_incr_proxy());
    }
    return ret;
}

Term OptSearch::make_independent_costs(
        TermManager *mgr,
        optsearch_iterator begin,
        optsearch_iterator end)
{
    assert(mgr);
    if ((end - begin) == 0) {
        /* no obj */
        return mgr->make_true();
    }
    Term ret = mgr->make_false();
    for (optsearch_iterator it = begin; it != end; ++it) {
        OptSearch *opt = *it;
        /* all objectives, including those already optimized */
        const Objective *obj = opt->get_objective();
        assert(obj);
        ret = mgr->make_or(ret, obj->get_incr_proxy());
    }
    return ret;
}

void OptSearch::reset(
        optsearch_iterator begin,
        optsearch_iterator end)
{
    for (optsearch_iterator it = begin; it != end; ++it) {
        OptSearch *opt = *it;
        opt->reset();
    }
}

void OptSearch::set_partial_model_handler(
        OptModelFoundHook *hook,
        optsearch_iterator begin,
        optsearch_iterator end)
{
    for (optsearch_iterator it = begin; it != end; ++it) {
        OptSearch *opt = *it;
        opt->set_partial_model_handler(hook);
    }
}

} /*** namespace msat::opt ***/
} /*** namespace msat ***/
