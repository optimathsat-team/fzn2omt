// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Configurable parameters of MathSAT
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_CONFIGURATION_H_INCLUDED
#define MSAT_CONFIGURATION_H_INCLUDED

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-04-21 (p.t.): moved Optimization configuration here
/*
#include "mathsat/utils/numbers.h"
#include "mathsat/theorysolver/la/latypes.h"
#include "mathsat/theorysolver/la/deltanumber.h"
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include <string>
#include <vector>
*/


#define MSAT_CONFIG_PARAM(tp, name)                         \
    private:                                                \
        tp name ## _;                                       \
    public:                                                 \
        const tp &name () const { return name ## _; }       \
        void set_ ## name (const tp &val) { name ## _ = val; }

/*
#define MSAT_INHERIT_PARAM(tp, name)                        \
    public:                                                 \
        const tp &name() const { return parent_->name(); }
*/

#define MSAT_LINK_PARAM(source, tp, name)                   \
    public:                                                 \
        const tp &name() const { return source.name(); }

#define MSAT_LINK_LOC_PARAM(source, tp, loc_name, name)     \
    public:                                                 \
        const tp &loc_name() const { return source.name(); }

namespace msat {

/**
 * The Configuration for the whole solver
 */
class Configuration {
    MSAT_CONFIG_PARAM(unsigned int, verbosity);
    ///< the verbosity level
    /*
    MSAT_CONFIG_PARAM(bool, proof_generation);
    ///< if true, proof generation is turned on

    MSAT_CONFIG_PARAM(bool, interpolation);
    ///< if true, interpolation is turned on

    MSAT_CONFIG_PARAM(bool, model_generation);
    ///< if true, model computation is turned on

    MSAT_CONFIG_PARAM(bool, bool_model_generation);
    ///< restricted form of model computation, working only for Booleans

    MSAT_CONFIG_PARAM(bool, allow_bool_function_args);
    ///< if true, allow to create terms with Boolean arguments
    ///< WARNING: the solver doesn't support them, use only if you know
    ///< what you are doing


    enum {
        UNSAT_CORE_OFF,
        UNSAT_CORE_PROOF,
        UNSAT_CORE_EXTERNAL,
        UNSAT_CORE_ASSUMPTIONS
    };
    MSAT_CONFIG_PARAM(int, unsat_core_generation);
    ///< unsat core generation mode

    MSAT_CONFIG_PARAM(bool, shallow_incrementality);

    MSAT_CONFIG_PARAM(int, random_seed);
    */
    ///< seed for random number generators

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-04-22 (p.t.): moved here global optimization settings
    
    /*
    MSAT_CONFIG_PARAM(bool, no_optimization);
    ///< true iff optimization procedure should return current value of cost

    enum {
        MAXSMT_ENC_BASIC = 0,
        MAXSMT_ENC_WITH_CUTS = 1,
        MAXSMT_ENC_WITH_LE = 2,
        MAXSMT_ENC_WITH_IMPL = 4,
        MAXSMT_ENC_BIDIRECTIONAL = 8,
        MAXSMT_PREF_BRANCHING = 16,
        //NOTE(PT): the following is deprecated, as it
        // is always done now.
        MAXSMT_BOUNDS_AUTO = 32,
        
        MAXSMT_ENC_ALTERNATIVE = 64
    };

    MSAT_CONFIG_PARAM(int, maxsmt_encoding);
    ///< determines which encoding is used for soft constraints

    enum {
        CARDCONSTR_ENC_SIMPLE = 0,
        CARDCONSTR_ENC_N_TIMES_N = 1,
        CARDCONSTR_ENC_N_LOG_LOG_N = 2
    };

    MSAT_CONFIG_PARAM(int, card_constr_encoding);
    ///< determines which encoding is used for cardinality constraints

    enum {
        MAXSMT_OMT_ENCODING = 0,
        MAXSMT_MAXRES = 1,
        MAXSMT_EXTERNAL = 2
    };

    MSAT_CONFIG_PARAM(int, maxsmt_engine);

    MSAT_CONFIG_PARAM(int, circuit_limit);
    ///< limits the size of maxsmt circuits

    enum {
        LEX_UNIFIED_ENGINE = 0,
        LEX_ITERATED_ENGINE = 1
    };

    MSAT_CONFIG_PARAM(int, lex_engine);
    ///< sets the Lexicographic Optimization engine

    enum {
        PARETO_GIA_ENGINE = 0,
        PARETO_LEX_ENGINE = 1
    };

    MSAT_CONFIG_PARAM(int, par_engine);
    ///< sets the Pareto engine to be used

    enum {
        PARETO_INCREMENTAL = 0,
        PARETO_CALLBACK    = 1
    };

    MSAT_CONFIG_PARAM(int, par_mode);
    ///< controls the behaviour of pareto-engine when
    ///< a 'check-sat' command is issued

    MSAT_CONFIG_PARAM(bool, par_print_model);
    ///< if TRUE, when a pareto model is found the complete model
    ///< is printed on standard output. Otherwise, only the
    ///< value of optimal objectives are printed out

    MSAT_CONFIG_PARAM(bool, print_objectives);
    ///< if TRUE, the value of objective functions is printed
    ///< by default without the new 'get-objectives' directive
    ///< NOTE: this was introduced for retro-compatibility
    MSAT_CONFIG_PARAM(bool, old_output_format);
    ///< if TRUE, OptiMathSAT prints output in the old format
    ///< instead of the new z3-like one.
    ///< NOTE: the old output is deprecated and it will
    ///<    eventually be removed from OptiMathSAT
    */
    /**
     *
     */
    /*
    class MaxDpll {
        MSAT_CONFIG_PARAM(bool, share_learnt_clauses);

        MaxDpll(Configuration *parent);

    private:
        friend class Configuration;
        Configuration *parent_;
    };
    */

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    /*
    struct Debug {
        enum {
            API_CALL_TRACE_OFF,
            API_CALL_TRACE_SMTLIB2,
            API_CALL_TRACE_C,
            API_CALL_TRACE_SMTLIB2_SCOPED
        };
        MSAT_CONFIG_PARAM(int, api_call_trace);
        ///< if not zero, all Environment API calls will be logged in the
        ///< selected format
        
        MSAT_CONFIG_PARAM(std::string, api_call_trace_filename);
        ///< name of the output file for logging API calls

        MSAT_CONFIG_PARAM(bool, api_call_trace_dump_config);
        ///< if true, include a dump of the current config in the API trace

        MSAT_CONFIG_PARAM(bool, dump_theory_lemmas);
        ///< if true, dump all theory lemmas generated during search

        MSAT_CONFIG_PARAM(std::vector<std::string>, log_sections);
        ///< list of enabled logging sections. If empty, consider all sections
        ///< By default, only the DPLL section is enabled

        MSAT_CONFIG_PARAM(bool, solver_enabled);
        ///< if false, the solver will be turned off. Can be useful in
        ///< combination with api_call_trace for creating traces of commands
        ///< without actually executing them

        MSAT_CONFIG_PARAM(bool, term_simplifications);
        ///< if false, turn off term simplifications

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2016-05-31 (p.t.): moved here global optimization settings
        MSAT_CONFIG_PARAM(bool, expand_soft);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    };
    */
    /**
     * Configurable parameters for the preprocessor
     */
    /*
    class Preprocessor {
        MSAT_CONFIG_PARAM(bool, toplevel_propagation);
        ///< controls the initial propagation of toplevel information

        MSAT_CONFIG_PARAM(int, toplevel_propagation_limit);
        ///< limit on the number of iterations in toplevel propagation (0
        ///< means unlimited)

        enum {
            SIMPLIFICATION_OFF = 0,
            SIMPLIFICATION_ITE = 1,
            SIMPLIFICATION_BV = 2,
            SIMPLIFICATION_ARRAY = 4,
            SIMPLIFICATION_GLOBAL = 8,
            SIMPLIFICATION_ARITH = 16
        };
        MSAT_CONFIG_PARAM(int, simplification);
        ///< bit-mask of the simplification options enabled

        MSAT_CONFIG_PARAM(bool, free_input_propagation);
        ///< controls whether or not we use free input propagation

        MSAT_CONFIG_PARAM(bool, ite_minimization);
        ///< controls whether or not we use ite minimization

        MSAT_CONFIG_PARAM(int, ite_minimization_call_limit);
        ///< set a limit for the ite minimization (in terms of recursive calls).

        MSAT_CONFIG_PARAM(bool, interpolation_ite_elimination);
        ///< if true, remove term-ITEs from interpolants

        MSAT_CONFIG_PARAM(bool, partial_nnf_conversion);
        ///< if true, apply (partial) NNF conversion before toplevel propagation

        MSAT_CONFIG_PARAM(bool, full_cnf_conversion);
        ///< if true, apply CNF conversion also to (sub)formulas already in CNF

        MSAT_INHERIT_PARAM(bool, proof_generation);
        MSAT_INHERIT_PARAM(bool, interpolation);
        MSAT_INHERIT_PARAM(bool, model_generation);
        
        Preprocessor(Configuration *parent);

    private:
        friend class Configuration;
        Configuration *parent_;
    };
    */
    /**
     * Configurable parameters for the DPLL engine
     */
    /*
    class Dpll {
    public:
        MSAT_CONFIG_PARAM(double, var_decay);
        ///< inverse of the variable activity decay factor

        MSAT_CONFIG_PARAM(double, clause_decay);
        ///< Inverse of the clause activity decay factor

        MSAT_CONFIG_PARAM(double, branching_random_frequency);
        ///< The frequency with which the decision heuristic tries to choose a
        ///< random variable

        enum {
            RESTART_GEOMETRIC,
            RESTART_LUBY,
            RESTART_LUBY_AGILITY,
            RESTART_GLUCOSE
        };
        MSAT_CONFIG_PARAM(int, restart_strategy);
        ///< The restart strategy used

        MSAT_CONFIG_PARAM(int, restart_initial);
        ///< The initial restart limit

        MSAT_CONFIG_PARAM(double, restart_geometric_factor);
        ///< The factor with which the restart limit is multiplied in each
        ///< restart (for the RESTART_GEOMETRIC strategy)

        MSAT_CONFIG_PARAM(double, restart_agility_flip_factor);
        MSAT_CONFIG_PARAM(double, restart_agility_upper_bound);
        MSAT_CONFIG_PARAM(double, restart_agility_lower_bound);
        
        MSAT_CONFIG_PARAM(double, tlemmas_activity_factor);
        ///< the multiplicative factor to use for scaling the activity of
        ///< theory lemmas when reducing the clause database. This can be used
        ///< to make the solver prefer T-lemmas over other learnt clauses when
        ///< deciding which clauses to keep
    
        MSAT_CONFIG_PARAM(bool, expensive_ccmin);
        ///< Controls conflict clause minimization

        MSAT_CONFIG_PARAM(bool, remove_satisfied);
        ///< If false, do not remove satisfied original clauses in simplify()

        MSAT_CONFIG_PARAM(bool, store_tlemmas);
        ///< if true, store all the T-lemmas generated during search

        enum {
            PHASE_FALSE = 0,
            PHASE_TRUE = 1,
            PHASE_INVERSE_POLARITY = 2
        };
        MSAT_CONFIG_PARAM(int, branching_initial_phase);
        ///< controls the phase used the first time a variable is selected
        ///< for branching

        enum {
            PHASE_CACHE_OFF = 0,
            PHASE_CACHE_PARTIAL = 1,
            PHASE_CACHE_FULL = 2
        };
        MSAT_CONFIG_PARAM(int, branching_cache_phase);
        ///< controls the phase caching mode for branching

        MSAT_CONFIG_PARAM(bool, branching_random_invalidate_phase_cache);
        ///< if true, random branches invalidate the phase cache of the
        ///< selected variables

        MSAT_CONFIG_PARAM(bool, branching_random_ignore_polarity);
        ///< if true, use random polarity when performing random branches

        MSAT_CONFIG_PARAM(bool, ghost_filtering);

        MSAT_CONFIG_PARAM(bool, minimize_model);
        ///< if true, try to minimize the final Boolean model (default: false)

        MSAT_CONFIG_PARAM(bool, allsat_minimize_model);
        ///< if true, try to minimize the model before calling the allsat hook

        MSAT_CONFIG_PARAM(bool, pop_btpoint_reset_var_order);
        ///< if true (default), reset variable ordering when popping a
        ///< user-visible backtracking point

        MSAT_CONFIG_PARAM(bool, glucose_var_activity);
        MSAT_CONFIG_PARAM(bool, glucose_learnt_minimization);

        enum {
            INTERPOLATION_MCMILLAN = 0,
            INTERPOLATION_SYMMETRIC = 1,
            INTERPOLATION_MCMILLAN_PRIME = 2
        };
        MSAT_CONFIG_PARAM(int, interpolation_mode);

        MSAT_CONFIG_PARAM(bool, proof_simplification);

        MSAT_CONFIG_PARAM(bool, allsat_allow_duplicates);

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-04-22 (p.t.): moved here global optimization settings

        enum {
           LINEAR = 0,
           BINARY = 1,
           ADAPTIVE = 2,
        };

        MSAT_CONFIG_PARAM(int, search_strategy);
        ///< search strategy (from 0 to 2)

        MSAT_CONFIG_PARAM(bool, learn_cost_implication);
        ///< learn chain of costs found so far for each cost variable

        MSAT_CONFIG_PARAM(bool, print_partial_sol);
        ///< true if intermediate solutions must be printed during the search

        MSAT_CONFIG_PARAM(bool, first_step_linear);
        ///< true if the dpll optimization must start with linear search

        MSAT_CONFIG_PARAM(unsigned int, mixbin_steps);
        ///< number of binary search steps before each linear serch step

        MSAT_CONFIG_PARAM(float, bint_fl);
        MSAT_CONFIG_PARAM(QNumber, bint);
        ///< parameter t used to divide the range [lb_, ub_[ to place the pivot

        MSAT_CONFIG_PARAM(QNumber, termination);
        ///< tolerance used for terminating the search (@LA(Q) optimization)

        MSAT_CONFIG_PARAM(QNumber, tolerance);
        ///< tolerance used to approximate the optimal solution (@LA(Q) optimization)

        MSAT_CONFIG_PARAM(bool, stop_at_first_solution);
        ///< true iff optimization search should stop at the first solution found (if any)

        MSAT_CONFIG_PARAM(bool, use_soft_timeout);
        ///< true iff optimization should not be interrupted by a timeout before at least
        ///< one solution has been found for all objective functions on the stack
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        MSAT_INHERIT_PARAM(bool, proof_generation);
        MSAT_INHERIT_PARAM(bool, interpolation);
        MSAT_INHERIT_PARAM(bool, model_generation);
        MSAT_INHERIT_PARAM(int, random_seed);
        MSAT_INHERIT_PARAM(int, unsat_core_generation);

        struct Preprocessor {
            enum {
                OFF = 0,
                PREPROCESSING = 1,
                INPROCESSING = 2
            };
            MSAT_CONFIG_PARAM(int, mode);
            ///< The preprocessing strategy used

            MSAT_CONFIG_PARAM(int, clause_size_limit);
            ///< The maximum size of created simplified clauses

            MSAT_CONFIG_PARAM(int, subsumption_size_limit);
            ///< The maximum size of created simplified clauses

            MSAT_CONFIG_PARAM(int, elimination_grow_limit);
            ///< The nr of clause we allow the DB to increase
            ///< when eliminating a variable

            MSAT_CONFIG_PARAM(int, elimination_phase);
            ///< In an incremental setting set how often we do
            ///< variable elimination, 1 means every check
            ///< 2 means every other check etc.

            MSAT_CONFIG_PARAM(bool, elimination_recent_vars_only);
            ///< In an incremental setting we only try the elimination
            ///< of newly pushed variables.

            MSAT_CONFIG_PARAM(bool, try_reelimination);
            ///< In an incremental setting, if true we try the reelimination
            ///< of reintroduced variables.

        public:
            Preprocessor(Configuration::Dpll *parent);

        private:
            friend class Configuration;
            Configuration::Dpll *parent_;
        };

    public:
        Dpll(Configuration *parent);
        void copy_to(Configuration::Dpll *dest);
        Preprocessor preprocessor; ///< the configuration object for the DPLL
                                   ///< preprocessor

    private:
        friend class Configuration;
        Configuration *parent_;
    };*/

    /**
     * Configurable parameters for the T-solvers
     */
    /*
    class Theory {
    public:
        enum {
            INTERFACE_EQ_POLICY_LAZY = 0,
            INTERFACE_EQ_POLICY_EAGER = 1,
            INTERFACE_EQ_POLICY_INTERESTING = 2,
            INTERFACE_EQ_POLICY_OFF = 3
        };
        MSAT_CONFIG_PARAM(int, interface_eq_policy);
        ///< policy for the generation of interface equalities

        MSAT_CONFIG_PARAM(bool, pairwise_interface_eq);
        ///< if true, filter-out interface equalities that do not occur in the
        ///< same position as arguments of the same UF (default is true)

        MSAT_CONFIG_PARAM(bool, eq_propagation);
        ///< if false, disable equality propagation among T-solvers (default
        ///< is true)

        MSAT_CONFIG_PARAM(bool, pure_literal_filtering);
        ///< if true, enable pure literal filtering

        MSAT_CONFIG_PARAM(int, interface_eq_batch_size);
        ///< max number of interface equalities to generate in a single batch
        ///< (0: unlimited)
    */
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-04-22 (p.t.): moved here DPLL common optimization search settings

        //MSAT_INHERIT_PARAM(bool, no_optimization);
        ///< true iff optimization procedure should return current value of cost

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        /**
         * Configurable parameters for the EUF solver
         */
        /*
        class Euf {
            MSAT_CONFIG_PARAM(bool, enabled);
            
            MSAT_CONFIG_PARAM(bool, handle_all_atoms);
            ///< if true, the EUF solver will handle all atoms, not just
            ///< uninterpreted predicates and equalities

            enum {
                DYN_ACK_OFF = 0,
                DYN_ACK_TOP = 1,
                DYN_ACK_ALL = 2
            };
            MSAT_CONFIG_PARAM(int, dyn_ack);
            ///< if not zero, enable dynamic Ackermann expansion
            ///< DYN_ACK_TOP means that only toplevel congruences will be
            ///< considered, DYN_ACK_ALL means that all congruences will be
            ///< considered

            MSAT_CONFIG_PARAM(unsigned int, dyn_ack_threshold);
            ///< threshold for activating dynamic Ackermann expansion

            MSAT_CONFIG_PARAM(unsigned int, dyn_ack_limit);
            ///< limit on the number of dynamic Ackermann lemmas generated

            MSAT_INHERIT_PARAM(bool, proof_generation);
            MSAT_INHERIT_PARAM(bool, interpolation);
            MSAT_INHERIT_PARAM(bool, model_generation);
            MSAT_INHERIT_PARAM(int, random_seed);

        public:
            Euf(Configuration::Theory *parent);

        private:
            friend class Configuration;
            Configuration::Theory *parent_;
        };
        */
        /**
         * Configurable parameters for the LA solver
         */
        /*
        class La {
            MSAT_CONFIG_PARAM(bool, enabled);
            
            MSAT_CONFIG_PARAM(unsigned int, lazy_expl_threshold);
            ///< threshold for generating lazy explanations for implied literals

            MSAT_CONFIG_PARAM(bool, split_rat_eq);
            ///< if false, don't split rational equalities and handle
            ///< disequalities directly.

            MSAT_CONFIG_PARAM(bool, delay_alien);
            ///< if true, delay "alien" atoms and interface equalities
            ///< (default: false)

            MSAT_CONFIG_PARAM(int, pivoting_greedy_threshold);
            ///< the threshold for switching to the Bland's rule for pivoting
            ///< in the Simplex (default: 0, which means use a value
            ///< proportional to the number of problem vars)

            enum {
                INTERPOLATION_SINGLE_SUMMARY = 0,
                INTERPOLATION_MULTIPLE_SUMMARIES = 1,
                INTERPOLATION_SINGLE_B_SUMMARY = 2
            };
            MSAT_CONFIG_PARAM(int, interpolation_mode);
            ///< controls the kind of LA interpolants generated. With
            ///< INTERPOLATION_SINGLE_SUMMARY, all the A-contraints are added
            ///< together, whereas with INTERPOLATION_MULTIPLE_SUMMARIES only
            ///< the minimal number of summations necessary to eliminate A-local
            ///< variables are performed

            MSAT_CONFIG_PARAM(bool, interpolation_laz_use_floor);
            ///< if true, allow floor functions in interpolants in LA(Z)

            MSAT_CONFIG_PARAM(bool, pure_equality_filtering);
            ///< if true, filter purely-positive negated equalities regardless
            ///< of the setting of pure_literal_filtering

            MSAT_CONFIG_PARAM(bool, detect_euf_fragment);
            ///< if true, detect problems that can be solved by EUF only, and
            ///< avoid calling the Simplex. Warning: the EUF solver must be
            ///< enabled, otherwise unsound results are returned

            MSAT_CONFIG_PARAM(bool, deduction_enabled);
            ///< if false, disable theory deduction

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-04-22 (p.t.): moved here DPLL common optimization search settings

            MSAT_CONFIG_PARAM(int, epsilon);
            ///< set the tolerance of the strict minimum cost;
            ///< if <c,k> and k>0, then the model value is c+k*delta
            ///< wiht delta <= 10^(-epsilon)

            MSAT_CONFIG_PARAM(int, infinite_exp);
            MSAT_CONFIG_PARAM(la::DNumber, infinite);
            ///< Infinite Value 10^I

            MSAT_CONFIG_PARAM(bool, lia_and_lra);
            ///< true if theor is LIA+LRA

            MSAT_CONFIG_PARAM(bool, optimize_iff_lra_sat);
            ///< check whether (< cost_var latest_cost_val) & tableau are SAT prior to
            ///< any minimization attempt (dual for maximization)

            MSAT_CONFIG_PARAM(bool, lra_check_and_optimize);
            ///< iff true, perform additional optimization steps at the end of check-sat
            ///< routine

            enum {
                LAZ_STRATEGY_BB_ONLY_SAT = 1,
                LAZ_STRATEGY_RECURSIVE_WITH_MIN = 2,
            };

            MSAT_CONFIG_PARAM(int, laz_opt_mode);
            ///< states which technique should the LA(Z)-Solver use to return a result
            ///< when `optimize()` is called.

            MSAT_INHERIT_PARAM(bool, no_optimization);
            ///< true iff optimization procedure should return current value of cost
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


            MSAT_CONFIG_PARAM(bool, laz_equality_elimination);
            ///< if true, enable the equality elimination step for LA(Z)
            ///< (default: true)

            MSAT_CONFIG_PARAM(bool, laz_internal_branch_and_bound);
            ///< if true, enable the internal branch and bound for LA(Z)
            ///< (default: true)

            MSAT_CONFIG_PARAM(int, laz_internal_branch_and_bound_limit);
            ///< limit on internal branch and bound case splits. 0 means
            ///< unlimited, and 1 means a value proportional to the number of
            ///< variables in the problem (default: 1)

            enum {
                LAZ_CUTS_FROM_PROOFS_OFF = 0,
                LAZ_CUTS_FROM_PROOFS_INTERNAL = 1,
                LAZ_CUTS_FROM_PROOFS_EXTERNAL = 2,
                LAZ_CUTS_FROM_PROOFS_EXTERNAL_EQ = 3
            };
            MSAT_CONFIG_PARAM(int, laz_cuts_from_proofs_mode);
            ///< controls the use of the "cuts from proofs" algorithm for
            ///< extended branch and bound lemmas. With
            ///< LAZ_CUTS_FROM_PROOFS_OFF, cuts from proofs are not used. With
            ///< LAZ_CUTS_FROM_PROOFS_INTERNAL, they are used both in the
            ///< internal and in the external branch and bound, whereas with
            ///< LAZ_CUTS_FROM_PROOFS_EXTERNAL they are used only in the
            ///< external branch and bound with splitting on-demand (default:
            ///< LAZ_CUTS_FROM_PROOFS_EXTERNAL).

            MSAT_CONFIG_PARAM(bool, laz_enabled);
            ///< if false, the LA(Z) solver will be disabled

            MSAT_CONFIG_PARAM(bool, laz_unit_cube_test);
            ///< if false, disable the unit cube test technique of Bromberger
            ///< and Weidenbach

            MSAT_INHERIT_PARAM(bool, proof_generation);
            MSAT_INHERIT_PARAM(bool, interpolation);
            MSAT_INHERIT_PARAM(bool, model_generation);
            MSAT_INHERIT_PARAM(int, random_seed);
            MSAT_INHERIT_PARAM(bool, pure_literal_filtering);
    */
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2016-11-14 (p.t.): DL Solver

            /**
             * Configurable parameters for the DL solver
             */
        /*
            MSAT_CONFIG_PARAM(bool, dl_enabled);

            enum {
                DL_INTERPOLATION_NONE = 0,
                DL_INTERPOLATION_SHORT = 1,
                DL_INTERPOLATION_LONG = 2
            };
            MSAT_CONFIG_PARAM(int, dl_interpolation_mode);

            MSAT_CONFIG_PARAM(float, dl_similarity_threshold);

            MSAT_CONFIG_PARAM(bool, dl_filter_tlemmas);

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        public:
            La(Configuration::Theory *parent);

        private:
            friend class Configuration;            
            Configuration::Theory *parent_;
        };
    */
        /**
         * Configurable parameters for the ARR solver
         */
        /*
        class Arr {
            MSAT_CONFIG_PARAM(bool, enabled);

            enum {
                NORMAL,
                LOD
            };
            MSAT_CONFIG_PARAM(int, mode);
            ///< which kind of solver to use
            
            MSAT_CONFIG_PARAM(bool, lazy_lemmas);
            MSAT_CONFIG_PARAM(int,  max_ext_lemmas);
            MSAT_CONFIG_PARAM(bool, enable_ext_polarity);
            MSAT_CONFIG_PARAM(bool, enable_ext_arg);
            MSAT_CONFIG_PARAM(bool, enable_witness);

            MSAT_INHERIT_PARAM(bool, proof_generation);
            MSAT_INHERIT_PARAM(bool, interpolation);
            MSAT_INHERIT_PARAM(bool, model_generation);
            MSAT_INHERIT_PARAM(int, random_seed);

            MSAT_LINK_LOC_PARAM(parent_->euf, bool, euf_enabled, enabled);

        public:
            Arr(Configuration::Theory *parent);

        private:
            friend class Configuration;
            Configuration::Theory *parent_;
        };


        class Bv {
            MSAT_CONFIG_PARAM(bool, enabled);
            MSAT_CONFIG_PARAM(bool, delay_propagated_eqs);
            ///< if true, equalities propagated by the EUF solver will be
            ///< given lower priority than other literals when checking
            ///< satisfiability (default: false)

            MSAT_CONFIG_PARAM(bool, eager);
            ///< if true, use eager BV solver (i.e. bit-blasting to the main
            ///< DPLL)

            enum {
                BIT_BLAST_DIRECT_CNF = 0,
                BIT_BLAST_AIG_TSEITIN = 1,
                BIT_BLAST_AIG_LS = 2
            };
            MSAT_CONFIG_PARAM(int, bit_blast_mode);
            ///< controls the way in which BV constraints are bit-blasted

            enum {
                INTERPOLATION_EQ_LIA = 0,
                INTERPOLATION_LIA = 1,
                INTERPOLATION_BIT = 2,
                INTERPOLATION_LIA_EQ = 3,
                INTERPOLATION_EQ = 4
            };
            MSAT_CONFIG_PARAM(int, interpolation_mode);
            ///< controls the kind of BV interpolants generated.
            ///< With INTERPOLATION_EQ_LIA (default), first we try to compute
            ///< interpolants by inlining equalities, and then by encoding into
            ///< LA(Z).
            ///< With INTERPOLATION_LIA, we only try encoding into LA(Z).
            ///< With INTERPOLATION_BIT, we extract interpolants from
            ///< bit-level proofs.
            ///< With INTERPOLATION_LIA_EQ, we first try encoding into LA(Z),
            ///< then try inlining equalities, and then bit-blasting.
            ///< With INTERPOLATION_EQ, we only try inlining equalities and
            ///< then bit-blasting

            enum {
                DIV_BY_ZERO_HW = 0,
                DIV_BY_ZERO_UF = 1
            };
            MSAT_CONFIG_PARAM(int, div_by_zero_mode);
            ///< controls the semantics used for division (and remainder) by
            ///< zero. DIV_BY_ZERO_HW uses the semantics commonly implemented
            ///< by hardware dividers, i.e. (bvudiv a 0) returns INT_MAX and
            ///< (bvurem a 0) returns a. DIV_BY_ZERO_UF uses an uninterpreted
            ///< function to leave the result unspecified (this is the
            ///< semantics mandated by SMT-LIB)

            MSAT_CONFIG_PARAM(bool, proof_simplification);

            MSAT_INHERIT_PARAM(bool, proof_generation);

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2017-12-15 (p.t.):
            MSAT_CONFIG_PARAM(bool, polarity);
            ///< if true, the solver sets the initial polarity of any BV goal
            MSAT_CONFIG_PARAM(bool, branch_preference);
            ///< if true, the solver prefers branching on th BV objective

            enum {
                BITVECTOR_OMT = 0,
                BITVECTOR_OBVWA = 1,
                BITVECTOR_OBVBS = 2,
            };

            MSAT_CONFIG_PARAM(int, opt_engine);
            ///< selects the optimization engine to be used with BitVector
            ///< objectives

            MSAT_INHERIT_PARAM(bool, model_generation);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        public:
            Bv(Configuration::Theory *parent);

            Configuration::Dpll lazydpll;
            ///< the configuration object for the internal DPLL solver used in
            ///< lazy mode

        private:
            friend class Configuration;
            Configuration::Theory *parent_;
        };
        */
        /*
        class Fp {
            MSAT_CONFIG_PARAM(bool, enabled);
            enum {
                BIT_BLAST_LAZY,
                BIT_BLAST_EAGER,
                ACDCL
            };
            MSAT_CONFIG_PARAM(int, mode);
            MSAT_CONFIG_PARAM(bool, bv_combination_enabled);

            enum {
                ACDCL_CONFLICT_TRIVIAL,
                ACDCL_CONFLICT_GENERALIZE_LIGHT,
                ACDCL_CONFLICT_GENERALIZE,
                ACDCL_CONFLICT_GENERALIZE_FULL
            };
            MSAT_CONFIG_PARAM(int, acdcl_conflict_generalization);

            enum {
                INTERPOLATION_ACDCL_MCMILLAN = 0,
                INTERPOLATION_EQ_ACDCL_MCMILLAN = 1,
                INTERPOLATION_ACDCL_SYMMETRIC = 2,
                INTERPOLATION_EQ_ACDCL_SYMMETRIC = 3,
                INTERPOLATION_ACDCL_MCMILLAN_PRIME = 4,
                INTERPOLATION_EQ_ACDCL_MCMILLAN_PRIME = 5
            };
            MSAT_CONFIG_PARAM(int, interpolation_mode);

            MSAT_CONFIG_PARAM(int, acdcl_single_propagation_limit);
            MSAT_CONFIG_PARAM(int, acdcl_single_generalization_limit);
            MSAT_CONFIG_PARAM(bool, acdcl_generalization_fair);

            enum {
                MINMAX_ZERO_TOTAL_ORDER = 0,
                MINMAX_ZERO_POSITIVE = 1,
                MINMAX_ZERO_FIRST = 2,
                MINMAX_ZERO_SECOND = 3,
                MINMAX_ZERO_UF = 4
            };
            MSAT_CONFIG_PARAM(int, minmax_zero_mode);
            ///< controls the semantics used for fp.min and fp.max when one
            ///< arg is +0 and the other is -0. MINMAX_ZERO_TOTAL_ORDER
            ///< returns -0 for fp.min and +0 for fp.max. MINMAX_ZERO_POSITIVE
            ///< always returns +0. MINMAX_ZERO_FIRST always returns the first
            ///< argument. MINMAX_ZERO_SECOND always returns the second
            ///< argument. MINMAX_ZERO_UF uses an uninterpreted function to
            ///< leave the result unspecified, i.e. either +0 or -0 (this is
            ///< the semantics mandated by SMT-LIB)
            
            MSAT_INHERIT_PARAM(bool, proof_generation);

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2017-01-27 (p.t.):
            MSAT_CONFIG_PARAM(bool, polarity);
            ///< if true, the solver sets the initial polarity of any FP goal
            MSAT_CONFIG_PARAM(bool, branch_preference);
            ///< if true, the solver prefers branching on the FP objective
            MSAT_CONFIG_PARAM(bool, safe_bits_only);
            ///< if true, both previous options only affect those bits
            ///< that are safe to work on

            enum {
                FLOATINGPOINT_OMT = 0,
                FLOATINGPOINT_OFPBS = 1,
                FLOATINGPOINT_OFPBLS = 2,
            };

            MSAT_CONFIG_PARAM(int, opt_engine);
            ///< selects the optimization engine to be used with FloatingPoint
            ///< objectives

            MSAT_INHERIT_PARAM(bool, model_generation);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

            
        public:
            Fp(Configuration::Theory *parent);

            Configuration::Theory::Bv lazybv;
            ///< the configuration object for the internal BV solver

        private:
            friend class Configuration;
            Configuration::Theory *parent_;
        };
        */
        /*
        class Na {
            MSAT_CONFIG_PARAM(bool, enabled);
            MSAT_CONFIG_PARAM(bool, permanent_lemmas);
            MSAT_CONFIG_PARAM(bool, eager_lemmas);
            MSAT_CONFIG_PARAM(bool, enable_tangent_lemmas_frontier);
            MSAT_CONFIG_PARAM(int, tangent_lemmas_rat_approx);
            MSAT_CONFIG_PARAM(int, tangent_lemmas_limit);
            MSAT_CONFIG_PARAM(bool, tangent_lemmas_enabled);
            MSAT_CONFIG_PARAM(bool, sat_check_enabled);
            MSAT_CONFIG_PARAM(bool, bound_lemmas_enabled);
            MSAT_CONFIG_PARAM(bool, nta_enabled);
            MSAT_CONFIG_PARAM(int, nta_rat_approx);
            MSAT_CONFIG_PARAM(int, nta_rat_approx_limit);
            enum {
                NTA_SAT_OFF,
                NTA_SAT_LINEAR,
                NTA_SAT_NONLINEAR
            };
            MSAT_CONFIG_PARAM(int, nta_sat_mode);
            MSAT_CONFIG_PARAM(bool, nta_eager);

            MSAT_INHERIT_PARAM(bool, proof_generation);
        public:
            Na(Configuration::Theory *parent);
        private:
            friend class Configuration;
            Configuration::Theory *parent_;
        };
        
        MSAT_INHERIT_PARAM(bool, proof_generation);
        MSAT_INHERIT_PARAM(bool, interpolation);
        MSAT_INHERIT_PARAM(bool, model_generation);
        MSAT_INHERIT_PARAM(int, random_seed);
        MSAT_LINK_PARAM(parent_->debug, bool, dump_theory_lemmas);
        
    private:
        friend class Configuration;
        friend class Configuration::Theory::Bv; // for accessing parent_ in
                                                // creating lazydpll
        Configuration *parent_;

    public:
        Theory(Configuration *parent);

        Euf euf; ///< the configuration object for the EUF solver
        La la; ///< the configuration object for the LA solver
        Arr arr; ///< the configuration object for the Arr solver
        Bv bv; ///< the configuration object for the BV solver
        Fp fp; ///< the configuration object for the FP solver
        Na na; ///< the configuration object for the NA solver
    };
    */
    /*
    struct Printer {
        enum {
            BV_NUMBER_DECIMAL,
            BV_NUMBER_BINARY,
            BV_NUMBER_HEX
        };
        MSAT_CONFIG_PARAM(int, bv_number_format);
        ///< sets the output format for printing bv numbers

        enum {
            FP_NUMBER_BV_DECIMAL,
            FP_NUMBER_BV_BINARY,
            FP_NUMBER_FLOATING
        };
        MSAT_CONFIG_PARAM(int, fp_number_format);
        ///< sets the output format for printing fp numbers

        MSAT_CONFIG_PARAM(std::string, defines_prefix);
        ///< custom prefix for defines/let bindings

        MSAT_CONFIG_PARAM(bool, model_as_formula);
        ///< if true, (get-model) will print a formula instead of a list of
        ///< assignments

        Printer();
    };
    */

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-05-07 (p.t.): moved here global optimization settings
    /*
    class Optimization {
    public:
        enum {
            CONCURRENT = 1,
            SEQUENTIAL = 2
        };
        MSAT_CONFIG_PARAM(int, job_type);
        ///< states how optimization variable is chosen at each round:
        ///< - CONCURRENT: devote each round to a different variable that is not
        ///<   yet optimised
        ///< - SEQUENTIAL: change optimisation variable only when its optimal
        ///<   value has been found

        enum {
            OPTIMIZATION_BOX_PRIORITY,
            OPTIMIZATION_LEX_PRIORITY,
            OPTIMIZATION_PAR_PRIORITY
        };

        MSAT_CONFIG_PARAM(int, priority);
        ///< true iff we are currently trying to optimize multiple objectives at once

        Optimization(Configuration *parent);
    private:
        Configuration* parent_;
    };
    */
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


    Configuration();
    /*
    Debug debug; ///< the debugging options
    Preprocessor preprocessor; ///< the config object for the preprocessor
    Dpll dpll; ///< the config object for the DPLL engine
    Theory theory; ///< the config object for the T-solvers
    Printer printer; ///< the config object for the printer
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-05-07 (p.t.): moved here global optimization settings
    Optimization optimization;
    MaxDpll maxdpll; ///< the config object for lemma lifting algorithm
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
    */

    bool model_generation();
    void copy_to(Configuration *dest);
    

private:
    // also the assignment operator should be considered private!
    // we don't declare it private because we want it to be auto-generated, so
    // that we avoid repeating the config params over and over
   // Configuration(const Configuration &other);
};

inline bool model_generation(){
    return true;
}

} // namespace msat

#undef MSAT_INHERIT_PARAM
#undef MSAT_CONFIG_PARAM

#endif // MSAT_CONFIGURATION_H_INCLUDED
