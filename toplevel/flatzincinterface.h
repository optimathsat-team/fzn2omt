// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCINTERFACE_H_INCLUDED
#define FLATZINCINTERFACE_H_INCLUDED

#include "../api/environment.h"
#include "../toplevel/cmdline.h"
#include "../toplevel/toplevelinterface.h"
#include "../api/optenvironment.h"
#include "../parser/flatzincparser.h"
#include "../toplevel/flatzincbank.h"
#include "../toplevel/flatzincconstraints.h"
#include "../utils/ciowrap.h"
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

namespace msat { namespace opt {

class FlatZincBank;
class FlatZincConstraints;

class FlatZincInterface: public ToplevelInterface,
                            public FlatZincAbstractParser {
public:
    MSAT_DECLARE_EXCEPTION(early_unsat)
    FlatZincInterface(Configuration *config, CmdLine *cmdline, bool bv);
    ///< constructor

    ~FlatZincInterface();
    ///< destructor

    /// TopLevel Interface
    void main_loop(std::istream &source);

    /// methods for FlatZinc 1.6

    void print_response();
    void reset_response();
    void handle_error(const char *msg);

    ///< FlatZinc Declarations
    ///< bool, int, float
    void declare_par(NumFlatZincDomainSharedPtr dom,
                     const char *ident, Term expr);
    void declare_var(NumFlatZincDomainSharedPtr dom,
                     const char *ident, Term expr);
    void declare_array_par(size_t len, NumFlatZincDomainSharedPtr dom,
                           const char *ident, TermListSharedPtr terms);
    void declare_array_var(size_t len, NumFlatZincDomainSharedPtr dom,
                           const char *ident, TermListSharedPtr terms);
    ///< set
    void declare_par_set(NumFlatZincDomainSharedPtr dom, const char *ident,
                         FznSetSharedPtr iset);
    void declare_var_set(NumFlatZincDomainSharedPtr dom, const char *ident,
                         FznSetSharedPtr iset);
    void declare_array_par_set(size_t len, NumFlatZincDomainSharedPtr dom,
                               const char *ident, FznSetListSharedPtr isets);
    void declare_array_var_set(size_t len, NumFlatZincDomainSharedPtr dom,
                               const char *ident, FznSetListSharedPtr isets);

    void annotate_decl(const char *ident, FlatZincAnnotation &ann);

    ///< FlatZinc Expressions
    ///< bool, int, float
    Term get_true();
    Term get_false();
    Term get_int_number(const char *value);
    Term get_float_number(const char *value);
    Term get_var_literal(bool var, FznType t, const char *ident);
    Term get_var_literal(bool var, FznType t, const char *ident,
                         size_t index);
    TermListSharedPtr get_array_var_literal(bool var, FznType t,
                                            const char *ident);
    ///< set
    FznSetSharedPtr get_set_literals(const char *ident);
    FznSetSharedPtr get_set_literals(const char *ident, size_t index);
    FznSetListSharedPtr get_array_set_literals(const char *ident);

    ///< FlatZinc Solve
    void push_objective(FlatZincAbstractParser::SolveType type, Term expr);

    ///< FlatZinc Constraints
    void array_bool_and(TermList &as, Term r);
    void array_bool_element(Term b, TermList &as, Term c);
    void array_bool_or(TermList &as, Term r);
    void array_bool_xor(TermList &as);
    void array_float_element(Term b, TermList &as, Term c);
    void array_int_element(Term b, TermList &as, Term c);
    void array_var_bool_element(Term b, TermList &as, Term c);
    void array_var_float_element(Term b, TermList &as, Term c);
    void array_var_int_element(Term b, TermList &as, Term c);
    void bool2int(Term a, Term b);
    void bool_and(Term a, Term b, Term r);
    void bool_clause(TermList &as, TermList &bs);
    void bool_eq(Term a, Term b);
    void bool_eq_reif(Term a, Term b, Term r);
    void bool_le(Term a, Term b);
    void bool_le_reif(Term a, Term b, Term r);
    void bool_lin_eq(TermList &as, TermList &bs, Term c);
    void bool_lin_le(TermList &as, TermList &bs, Term c);
    void bool_lt(Term a, Term b);
    void bool_lt_reif(Term a, Term b, Term r);
    void bool_not(Term a, Term b);
    void bool_or(Term a, Term b, Term r);
    void bool_xor(Term a, Term b, Term r);
    void float_abs(Term a, Term b);
    void float_div(Term a, Term b, Term c);
    void float_acos(Term a, Term b);
    void float_asin(Term a, Term b);
    void float_atan(Term a, Term b);
    void float_cos(Term a, Term b);
    void float_cosh(Term a, Term b);
    void float_exp(Term a, Term b);
    void float_ln(Term a, Term b);
    void float_log10(Term a, Term b);
    void float_log2(Term a, Term b);
    void float_sqrt(Term a, Term b);
    void float_sin(Term a, Term b);
    void float_sinh(Term a, Term b);
    void float_tan(Term a, Term b);
    void float_tanh(Term a, Term b);
    void float_eq(Term a, Term b);
    void float_eq_reif(Term a, Term b, Term r);
    void float_le(Term a, Term b);
    void float_le_reif(Term a, Term b, Term r);
    void float_lin_eq(TermList &as, TermList &bs, Term c);
    void float_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r);
    void float_lin_le(TermList &as, TermList &bs, Term c);
    void float_lin_le_reif(TermList &as, TermList &bs, Term c, Term r);
    void float_lin_lt(TermList &as, TermList &bs, Term c);
    void float_lin_lt_reif(TermList &as, TermList &bs, Term c, Term r);
    void float_lin_ne(TermList &as, TermList &bs, Term c);
    void float_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r);
    void float_lt(Term a, Term b);
    void float_lt_reif(Term a, Term b, Term r);
    void float_max(Term a, Term b, Term c);
    void float_min(Term a, Term b, Term c);
    void float_ne(Term a, Term b);
    void float_ne_reif(Term a, Term b, Term r);
    void float_plus(Term a, Term b, Term c);
    void float_times(Term a, Term b, Term c);
    void int_abs(Term a, Term b);
    void int_div(Term a, Term b, Term c);
    void int_eq(Term a, Term b);
    void int_eq_reif(Term a, Term b, Term r);
    void int_le(Term a, Term b);
    void int_le_reif(Term a, Term b, Term r);
    void int_lin_eq(TermList &as, TermList &bs, Term c);
    void int_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r);
    void int_lin_le(TermList &as, TermList &bs, Term c);
    void int_lin_le_reif(TermList &as, TermList &bs, Term c, Term r);
    void int_lin_ne(TermList &as, TermList &bs, Term c);
    void int_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r);
    void int_lt(Term a, Term b);
    void int_lt_reif(Term a, Term b, Term r);
    void int_max(Term a, Term b, Term c);
    void int_min(Term a, Term b, Term c);
    void int_mod(Term a, Term b, Term c);
    void int_ne(Term a, Term b);
    void int_ne_reif(Term a, Term b, Term r);
    void int_plus(Term a, Term b, Term c);
    void int_times(Term a, Term b, Term c);
    void int2float(Term a, Term b);
    void array_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c);
    void array_var_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c);
    void set_card(FznSetSharedPtr a, Term b);
    void set_diff(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);
    void set_eq(FznSetSharedPtr a, FznSetSharedPtr b);
    void set_eq_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r);
    void set_in(Term a, FznSetSharedPtr b);
    void set_in_reif(Term a, FznSetSharedPtr b, Term r);
    void set_intersect(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);
    void set_le(FznSetSharedPtr a, FznSetSharedPtr b);
    void set_lt(FznSetSharedPtr a, FznSetSharedPtr b);
    void set_ne(FznSetSharedPtr a, FznSetSharedPtr b);
    void set_ne_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r);
    void set_subset(FznSetSharedPtr a, FznSetSharedPtr b);
    void set_subset_reif(FznSetSharedPtr a, FznSetSharedPtr b, Term r);
    void set_symdiff(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);
    void set_union(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c);

    ///< FlatZinc Global Constraints

    void all_different(TermList &as);
    void all_different_except_0(TermList &as);
    void all_different(FznSetListSharedPtr as);

    void disjoint(FznSetSharedPtr s1, FznSetSharedPtr s2);
    void all_disjoint(FznSetListSharedPtr as);

    void disjunctive(TermList &s, TermList &d);
    void disjunctive_strict(TermList &s, TermList &d);

	void all_equal(TermList &x);
	void all_equal(FznSetListSharedPtr as);

    void among(Term n, TermList &x, FznSetSharedPtr v);

    void array_max(Term m, TermList &x);
    void array_min(Term m, TermList &x);

    void maximum_arg(TermList &x, Term i, const NumInterval &xdom);
    void minimum_arg(TermList &x, Term i, const NumInterval &xdom);

    void at_least_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v);
    void exactly_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v);
    void at_most_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v);
    void at_most_1(FznSetListSharedPtr as);

	void bin_packing(Term c, TermList &bin, TermList &w);
	void bin_packing_capa(TermList &c, TermList &bin,
                          TermList &w, const NumInterval &cdom);
	void bin_packing_load(TermList &load, TermList &bin,
                          TermList &w, const NumInterval &loaddom);

    virtual void element(Term i, TermList &x,
                         Term y, NumInterval &xdom);
    virtual void element(Term i, FznSetListSharedPtr x,
                         FznSetSharedPtr y, NumInterval &xdom);

    void comparison_rel_array(TermList &rels, Term rel);

    void count_eq(Term n, TermList &x, Term v);
    void count_geq(Term n, TermList &x, Term v);
    void count_gt(Term n, TermList &x, Term v);
    void count_leq(Term n, TermList &x, Term v);
    void count_lt(Term n, TermList &x, Term v);
    void count_neq(Term n, TermList &x, Term v);

    void decreasing(TermList &x);
    void decreasing(FznSetListSharedPtr x);
    void increasing(TermList &x);
    void increasing(FznSetListSharedPtr x);

    void diffn(TermList &x, TermList &y, TermList &dx, TermList &dy);
    void diffn_nonstrict(TermList &x, TermList &y, TermList &dx, TermList &dy);
    void diffn_nonoverlap_k(TermList &x1, TermList &w1, TermList &x2, TermList &w2);
    void diffn_nonstrict_nonoverlap_k(TermList &x1, TermList &w1,
                                      TermList &x2, TermList &w2);

    void distribute(TermList &card, TermList &value, TermList &base);

    void geost_nonoverlap_k(TermList &x1, TermList &w1,
                            TermList &x2, TermList &w2);

    void global_cardinality(TermList &x, TermList &cover,
                            TermList &costs);
    void global_cardinality_closed(TermList &x, TermList &cover,
                            TermList &costs);
    void global_cardinality_low_up(TermList &x, TermList &cover,
                            TermList &lbound, TermList &ubound);
    void global_cardinality_low_up_closed(TermList &x, TermList &cover,
                            TermList &lbound, TermList &ubound);

    void int_set_channel(TermList &x, FznSetListSharedPtr y,
                         const NumInterval &xdom, const NumInterval &ydom);

    void inverse(TermList &f, TermList &invf,
                 const NumInterval &fdom, const NumInterval &invfdom);
    void inverse_set(FznSetListSharedPtr f, FznSetListSharedPtr invf,
                     const NumInterval &fdom, const NumInterval &invfdom);

    void link_set_to_booleans(FznSetSharedPtr s, TermList &b,
                              const NumInterval &bdom);

    void member(TermList &x, Term y);
    void member(FznSetListSharedPtr x, FznSetSharedPtr y);

    void nvalue(Term n, TermList &x);

    void range(TermList &x, FznSetSharedPtr s,
               FznSetSharedPtr t, const NumInterval &xdom);

    void bool_clause_reif(TermList &as, TermList &bs, Term b);

    void float_in(Term x, Term a, Term b);
    void float_dom(Term x, TermList &as, Term a, Term b);

    void roots(TermList &x, FznSetSharedPtr s,
               FznSetSharedPtr t, const NumInterval &xdom);

    void sum_pred(Term i, FznSetListSharedPtr sets, TermList &cs,
                  Term s, const NumInterval &csdom, const NumInterval &setsdom);

    void symmetric_all_different(TermList &x, const NumInterval &xdom);

    void value_precede(Term s, Term t, TermList &x);
    void value_precede(Term s, Term t, FznSetListSharedPtr x);

private:
    MSAT_DECLARE_EXCEPTION(exiting)

    void print_model();
    void init_env();

    enum {
        GENERIC_ERROR,
        SYNTAX_ERROR,
        SYMBOL_ERROR,
        TYPE_INST_ERROR,
        EVALUATION_ERROR,
        EARLY_UNSAT_ERROR,
    };
    void raise(const std::exception &exc, size_t type = GENERIC_ERROR);
    void raise_early_unsat(const std::exception &exc);

    Configuration *cfg_;
    CmdLine *cmdline_;
    Environment *env_;
    OptEnvironment *optenv_;
    TermManager *mgr_;
    FlatZincBank *bank_;
    FlatZincConstraints *constraints_;
    OptSearchList objs_;
    std::ostream *outstream_;
    std::ostream *errstream_;
    std::string inputfile_;

    enum Response {
        SUCCESS,
        ERROR,
        UNSUPPORTED,
        STATUS,
        INFO,
        MODEL,
        UNSATCORE,
        INTERPOLANT,
        EARLY_UNSAT
    };
    Response response_;
    bool print_success_;
    bool print_model_;
    unsigned long timeout_;
    size_t memlimit_mb_;

    bool prefetch_phase_;
    std::string error_msg_;
    Environment::status status_;

    void *flex_scanner_;
    std::ofstream output;
    ///< the actual lexical scanner

    friend class FlatZincBank;
    friend class FlatZincConstraints;
    friend class FlatZincGlConstraints;
};

}} // namespace

#endif // FLATZINCINTERFACE_H_INCLUDED
