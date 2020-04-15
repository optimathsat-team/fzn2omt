// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCBANK_H_INCLUDED
#define FLATZINCBANK_H_INCLUDED

#include "../api/environment.h"
#include "../toplevel/cmdline.h"
#include "../toplevel/flatzincinterface.h"
#include <unordered_set>
#include <unordered_map>

namespace msat {

namespace opt {

class OptEnvironment;
class FlatZincInterface;

class FlatZincScalar {
public:
    FlatZincScalar(bool is_var, Term value,
                   NumFlatZincDomainSharedPtr domain) :
    is_array_(false), is_var_(is_var), type_(domain->type()), value_(value),
    values_(NULL), domain_(domain) { };

    FlatZincScalar(bool is_var, TermListSharedPtr values,
                   NumFlatZincDomainSharedPtr domain) :
    is_array_(true), is_var_(is_var), type_(domain->type()), value_(NULL),
    values_(values), domain_(domain) { };

    bool is_array_;
    bool is_var_;
    FznType type_;
    Term value_;
    TermListSharedPtr values_;
    NumFlatZincDomainSharedPtr domain_;
};


class FlatZincBank {
public:
    FlatZincBank(FlatZincInterface *parser, Environment *env,
                 CmdLine *cmdline);
    virtual ~FlatZincBank();

    ///< printer functions
    void declare_var_print(Term expr, Term cs);

    ///< bool, int, float support

    void declare_par(NumFlatZincDomainSharedPtr dom, const char *ident, Term expr);
    void declare_var(NumFlatZincDomainSharedPtr dom, const char *ident, Term expr);
    void declare_array_par(size_t len, NumFlatZincDomainSharedPtr dom,
                           const char *ident, TermListSharedPtr terms);
    void declare_array_var(size_t len, NumFlatZincDomainSharedPtr dom,
                           const char *ident, TermListSharedPtr terms);
    Term get_true();
    Term get_false();
    Term get_int_number(const char *value);
    Term get_float_number(const char *value);
    Term get_var_literal(bool var, FznType t, const char *ident);
    Term get_var_literal(bool var, FznType t, const char *ident,
                         size_t index);
    TermListSharedPtr get_array_var_literal(bool var, FznType t,
                                            const char *ident);

    ///< set support

    void declare_par_set(NumFlatZincDomainSharedPtr dom, const char *ident, FznSetSharedPtr iset);
    void declare_var_set(NumFlatZincDomainSharedPtr dom, const char *ident, FznSetSharedPtr iset);
    void declare_array_par_set(size_t len, NumFlatZincDomainSharedPtr dom,
                               const char *ident, FznSetListSharedPtr isets);
    void declare_array_var_set(size_t len, NumFlatZincDomainSharedPtr dom,
                               const char *ident, FznSetListSharedPtr isets);
    FznSetSharedPtr get_set_literals(const char *ident);
    FznSetSharedPtr get_set_literals(const char *ident, size_t index);
    FznSetListSharedPtr get_array_set_literals(const char *ident);
    ///< NOTE: FlatZincBank retains the ownership of these pointers

    void annotate_decl(const char *ident, FlatZincAnnotation &ann);

    ///< conversions support
    void bool2int(Term a, Term b);
    void int2float(Term a, Term b);

    bool is_pseudoboolean(Term a, Term &out);

    //void print_model(std::ostream *out, ModelStore *ms) const;
    Term make_model_block_clause() const;

    size_t get_required_bv_bits(TermList &as, Term &lower, Term &upper, bool &positive_domain) const;

    bool get_var_bounds(Term t, Number &lower, Number &upper) const;

    Term make_private_term(const DataType *type) const;
    Term make_private_term(const std::string &str, size_t idx,
                           const DataType *type) const;
    Term make_private_term(const std::string &str, Number idx,
                           const DataType *type) const;
    Term make_private_pbsum(TermList &clauses, Term weight) const;
    Term make_private_pbsum(TermList &clauses, TermList &weights) const;

private:
    std::string get_string_var_literal(bool var, FznType t) const;
    void print_flatzinc_term(std::ostream *out, Term term) const;
    const DataType *get_bv_datatype(NumFlatZincDomainSharedPtr &dom) const;
    const DataType *get_datatype(NumFlatZincDomainSharedPtr &dom) const;
    const DataType *get_datatype(FznType type) const;
    bool is_already_declared(std::string &id);
    inline void do_type_check(NumFlatZincDomainSharedPtr &dom, const char *ident, Term expr) const;
    inline void do_type_check(NumFlatZincDomainSharedPtr &dom, const char *ident, TermListSharedPtr exprs) const;
    inline bool is_compatible_type(FznType type, Term t) const;
    Term get_zero_one_substitution(Term a, bool pre_phase);
    Term make_bounds_constraint(NumFlatZincDomainSharedPtr &dom, Term var);
    Term make_la_bounds_constraint(NumFlatZincDomainSharedPtr &dom, Term var);
    Term make_sbv_bounds_constraint(NumFlatZincDomainSharedPtr &dom, Term var);

    FlatZincInterface *parser_;
    Environment *env_;
    opt::OptEnvironment *optenv_;
    CmdLine *cmdline_;
    TermManager *mgr_;
    Term true_;
    Term false_;
    Term one_;
    Term zero_;

    typedef SharedPtr<FlatZincScalar> FlatZincScalarSharedPtr;
    typedef std::unordered_map<std::string, FlatZincScalarSharedPtr > FznScalarDeclMap;
    FznScalarDeclMap scalar_decl_;

    typedef std::unordered_map<std::string, FznSetSharedPtr> FznSetDeclMap;
    typedef std::unordered_map<std::string, FznSetListSharedPtr> FznSetListDeclMap;
    FznSetDeclMap set_decl_;
    FznSetListDeclMap set_list_decl_;

    TermMap bool2int_;
    TermMap int2bool_;
    TermMap int2float_;
    TermMap float2int_;

    ///< output vars support
    typedef std::vector<std::string> OutputVarList;
    typedef std::pair<std::string, std::vector<int64_t> > OutputArray;
    typedef std::vector<OutputArray> OutputArrayList;

    OutputVarList output_vars_;
    OutputArrayList output_arrays_;
};

}} // namespace msat

#endif
