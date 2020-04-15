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

#include "configuration.h"
#include <iostream>
using namespace std;
namespace msat {

Configuration::Configuration()
    /*:
    debug(),
    preprocessor(this),
    dpll(this),
    theory(this),
    printer(),
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-05-07 (p.t.): moved here GLOBAL OPT configuration
    optimization(this),
    maxdpll(this)
    */
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
{
    /*
    set_verbosity(0);
    set_proof_generation(false);
    set_interpolation(false);
    set_model_generation(false);
    set_bool_model_generation(false);
    set_allow_bool_function_args(false);
    set_unsat_core_generation(UNSAT_CORE_OFF);
    debug.set_api_call_trace(Debug::API_CALL_TRACE_OFF);
    debug.set_api_call_trace_filename("");
    debug.set_api_call_trace_dump_config(true);
    debug.set_dump_theory_lemmas(false);
    debug.set_solver_enabled(true);
    debug.set_term_simplifications(true);
    std::vector<std::string> default_log_sections;
    default_log_sections.push_back("");
    debug.set_log_sections(default_log_sections);
    set_shallow_incrementality(false);
    set_random_seed(91648253);
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-05-07 (p.t.): moved here GLOBAL OPT configuration
    set_no_optimization(false);
    set_maxsmt_encoding(127);
    set_card_constr_encoding(2);
    set_maxsmt_engine(MAXSMT_OMT_ENCODING);
    set_circuit_limit(20);
    set_lex_engine(LEX_ITERATED_ENGINE);
    set_par_engine(PARETO_LEX_ENGINE);
    set_par_mode(PARETO_INCREMENTAL);
    set_par_print_model(true);
    set_print_objectives(false);
    set_old_output_format(false);
    debug.set_expand_soft(false);
    */
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}

/*
Configuration::Printer::Printer()
{
    set_bv_number_format(BV_NUMBER_DECIMAL);
    set_fp_number_format(FP_NUMBER_BV_BINARY);
    set_defines_prefix("");
    set_model_as_formula(false);
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2016-08-14 (p.t.): adding lemma lifting functionality
Configuration::MaxDpll::MaxDpll(Configuration *parent):
    parent_(parent)
{
    set_share_learnt_clauses(false);
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*/
void Configuration::copy_to(Configuration *dest)
{
    *dest = *this;
    //cout<<"copy_to\n";
}

/*)
Configuration::Preprocessor::Preprocessor(Configuration *parent):
    parent_(parent)
{
    set_toplevel_propagation(true);
    set_toplevel_propagation_limit(0);
    set_simplification(SIMPLIFICATION_ITE | SIMPLIFICATION_BV |
                       SIMPLIFICATION_ARRAY | SIMPLIFICATION_ARITH);
    set_free_input_propagation(false);
    set_ite_minimization(false);
    set_ite_minimization_call_limit(150000);
    set_interpolation_ite_elimination(false);
    set_partial_nnf_conversion(false);
    set_full_cnf_conversion(false);
}


Configuration::Dpll::Dpll(Configuration *parent):
    preprocessor(this),
    parent_(parent)
{
    set_var_decay(1 / 0.95);
    set_clause_decay(1 / 0.999);
    set_restart_strategy(RESTART_GEOMETRIC);
    set_restart_initial(200);
    set_restart_geometric_factor(1.5);
    set_restart_agility_lower_bound(0.15);
    set_restart_agility_upper_bound(0.20);
    set_restart_agility_flip_factor(0.9999);
    set_tlemmas_activity_factor(1.6);
    set_expensive_ccmin(true);
    set_remove_satisfied(true);
    set_store_tlemmas(false);
    set_branching_random_frequency(0.001);
    set_branching_initial_phase(PHASE_FALSE);
    set_branching_cache_phase(PHASE_CACHE_FULL);
    set_branching_random_invalidate_phase_cache(false);
    set_branching_random_ignore_polarity(true);
    set_ghost_filtering(false);
    set_minimize_model(false);
    set_allsat_minimize_model(false);
    set_pop_btpoint_reset_var_order(true);
    set_glucose_var_activity(false);
    set_glucose_learnt_minimization(false);
    set_interpolation_mode(INTERPOLATION_MCMILLAN);
    set_proof_simplification(false);
    set_allsat_allow_duplicates(false);

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-04-22 (p.t.): moved here DPLL configuration
    set_first_step_linear(true);
    set_mixbin_steps(1);
    set_search_strategy(Configuration::Dpll::LINEAR);
    set_learn_cost_implication(true);
    set_print_partial_sol(false);
    set_bint_fl(0.5);
    set_bint(QNumber(1, 2));
    set_termination(QNumber(0));
    set_tolerance(QNumber(0));
    set_stop_at_first_solution(false);
    set_use_soft_timeout(false);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}


void Configuration::Dpll::copy_to(Configuration::Dpll *dest)
{
    Configuration *p = dest->parent_;
    *dest = *this;
    dest->parent_ = p;
    dest->preprocessor.parent_ = dest;
}


Configuration::Dpll::Preprocessor::Preprocessor(Configuration::Dpll *parent):
    parent_(parent)
{
    set_mode(OFF);
    set_clause_size_limit(20);
    set_subsumption_size_limit(1000);
    set_elimination_grow_limit(0);
    set_elimination_recent_vars_only(false);
    set_try_reelimination(true);
    set_elimination_phase(1);
}


Configuration::Theory::Theory(Configuration *parent):
    parent_(parent),
    euf(this),
    la(this),
    arr(this),
    bv(this),
    fp(this),
    na(this)
{
    set_interface_eq_policy(INTERFACE_EQ_POLICY_INTERESTING);
    set_pairwise_interface_eq(true);
    set_interface_eq_batch_size(100);
    set_eq_propagation(true);
    set_pure_literal_filtering(false);
}


Configuration::Theory::Euf::Euf(Configuration::Theory *parent):
    parent_(parent)
{
    set_enabled(true);
    set_handle_all_atoms(false);
    set_dyn_ack(DYN_ACK_OFF);
    set_dyn_ack_threshold(1);
    set_dyn_ack_limit(1000);
}


Configuration::Theory::La::La(Configuration::Theory *parent):
    parent_(parent)
{
    set_enabled(true);
    set_lazy_expl_threshold(10);
    set_split_rat_eq(true);
    set_delay_alien(false);
    set_pivoting_greedy_threshold(0);
    set_interpolation_mode(INTERPOLATION_SINGLE_SUMMARY);
    set_interpolation_laz_use_floor(true);
    set_pure_equality_filtering(true);
    set_detect_euf_fragment(false);
    set_deduction_enabled(true);

    set_laz_equality_elimination(true);
    set_laz_internal_branch_and_bound(true);
    set_laz_internal_branch_and_bound_limit(1);
    set_laz_cuts_from_proofs_mode(LAZ_CUTS_FROM_PROOFS_EXTERNAL_EQ);
    set_laz_enabled(true);
    set_laz_unit_cube_test(true);
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2014-04-22 (p.t.): moved here LA(Q)/LA(Z) OPT configuration
    set_epsilon(6);
    set_infinite_exp(9);
    set_infinite(la::DNumber(QNumber(pow(10, infinite_exp()))*-1, 0));
    set_lia_and_lra(false);
    set_laz_opt_mode(LAZ_STRATEGY_BB_ONLY_SAT);
    set_optimize_iff_lra_sat(true);
    set_lra_check_and_optimize(false);
    set_dl_enabled(false);
    set_dl_interpolation_mode(DL_INTERPOLATION_SHORT|DL_INTERPOLATION_LONG);
    set_dl_similarity_threshold(0.5);
    set_dl_filter_tlemmas(false);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}

Configuration::Theory::Arr::Arr(Configuration::Theory *parent):
    parent_(parent)
{
    set_enabled(true);
    set_mode(NORMAL);
    set_lazy_lemmas(false);
    set_max_ext_lemmas(0);
    set_enable_ext_polarity(true);
    set_enable_ext_arg(true);
    set_enable_witness(true);
}


Configuration::Theory::Bv::Bv(Configuration::Theory *parent):
    lazydpll(parent->parent_),
    parent_(parent)
{
    set_enabled(true);
    set_delay_propagated_eqs(true);
    set_eager(true);
    set_bit_blast_mode(BIT_BLAST_AIG_TSEITIN);
    set_interpolation_mode(INTERPOLATION_EQ_LIA);
    lazydpll.set_branching_random_frequency(0);
    set_proof_simplification(false);
    set_div_by_zero_mode(DIV_BY_ZERO_HW);
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2017-12-27 (p.t.): moved here BV OPT configuration
    set_polarity(true);
    set_branch_preference(false);
    set_opt_engine(Configuration::Theory::Bv::BITVECTOR_OBVBS);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}

Configuration::Optimization::Optimization(Configuration *parent):
    parent_(parent)
{
    set_job_type(SEQUENTIAL);
    set_priority(Configuration::Optimization::OPTIMIZATION_BOX_PRIORITY);
}

Configuration::Theory::Fp::Fp(Configuration::Theory *parent):
    lazybv(parent),
    parent_(parent)
{
    set_enabled(true);
    set_mode(BIT_BLAST_EAGER);
    set_bv_combination_enabled(true);
    set_acdcl_conflict_generalization(ACDCL_CONFLICT_GENERALIZE);
    lazybv.set_bit_blast_mode(Configuration::Theory::Bv::BIT_BLAST_AIG_LS);
    lazybv.lazydpll.set_restart_strategy(Configuration::Dpll::RESTART_GLUCOSE);
    lazybv.lazydpll.set_glucose_var_activity(true);
    lazybv.lazydpll.set_glucose_learnt_minimization(true);
    lazybv.lazydpll.set_branching_cache_phase(
        Configuration::Dpll::PHASE_CACHE_PARTIAL);
    lazybv.lazydpll.set_branching_random_frequency(0.01);
    set_interpolation_mode(INTERPOLATION_ACDCL_MCMILLAN);
    set_acdcl_single_propagation_limit(0);
    set_acdcl_single_generalization_limit(0);
    set_acdcl_generalization_fair(true);
    set_minmax_zero_mode(MINMAX_ZERO_POSITIVE);
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2017-12-27 (p.t.): moved here FP OPT configuration
    set_polarity(true);
    set_branch_preference(false);
    set_safe_bits_only(true);
    set_opt_engine(Configuration::Theory::Fp::FLOATINGPOINT_OFPBS);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}


Configuration::Theory::Na::Na(Configuration::Theory *parent):
    parent_(parent)
{
    set_enabled(true);
    set_permanent_lemmas(true);
    set_eager_lemmas(false);
    set_enable_tangent_lemmas_frontier(true);
    set_tangent_lemmas_rat_approx(0);
    set_tangent_lemmas_limit(0);
    set_tangent_lemmas_enabled(true);
    set_sat_check_enabled(true);
    set_bound_lemmas_enabled(true);
    set_nta_enabled(true);
    set_nta_rat_approx(3);
    set_nta_rat_approx_limit(10);
    set_nta_sat_mode(Configuration::Theory::Na::NTA_SAT_LINEAR);
    set_nta_eager(true);
}
*/

} // namespace msat
