// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.


#include "../toplevel/flatzincbank.h"
#include "../api/optenvironment.h"
#include<math.h>
#include<limits>
#include<sstream>
using namespace std;

namespace msat {

namespace opt {

FlatZincBank::FlatZincBank(FlatZincInterface *parser, Environment *env,
                           CmdLine *cmdline):
        parser_(parser), env_(env), optenv_(NULL), cmdline_(cmdline)
{
    mgr_ = env_->get_term_manager();
    assert(mgr_);
    true_ = mgr_->make_true();
    false_ = mgr_->make_false();
    one_ = mgr_->make_number(1);
    zero_ = mgr_->make_number(0);
    optenv_ = dynamic_cast<opt::OptEnvironment*>(env);

    bool2int_[true_] = one_;
    bool2int_[false_] = zero_;
    int2bool_[one_] = true_;
    int2bool_[zero_] = false_;

    int2float_[one_] = one_;
    int2float_[zero_] = zero_;
    float2int_[one_] = one_;
    float2int_[zero_] = zero_;
}

FlatZincBank::~FlatZincBank()
{
    parser_ = NULL;
    env_ = NULL;
    optenv_ = NULL;
    cmdline_ = NULL;
    mgr_ = NULL;
    true_ = NULL;
    false_ = NULL;
    one_ = NULL;
    zero_ = NULL;

    scalar_decl_.clear();
    set_decl_.clear();
    set_list_decl_.clear();

    bool2int_.clear();
    int2bool_.clear();
    int2float_.clear();
    float2int_.clear();

    output_vars_.clear();
    output_arrays_.clear();
}

//-----------------------------------------------------------------------------
// bool, int, float support
//-----------------------------------------------------------------------------

void FlatZincBank::declare_par(
        NumFlatZincDomainSharedPtr dom,
        const char *ident,
        Term expr)
{
    assert(dom && ident && expr);

    do_type_check(dom, ident, expr);

    std::string id(ident);

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("identifier '")
            << id << "' is already declared and/or defined elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    Term cs = make_bounds_constraint(dom, expr);
    assert(cs);
    const Symbol *s = cs->get_symbol();

    if (mgr_->is_false(s)) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
    }
    assert(mgr_->is_true(s));

    scalar_decl_[id] = FlatZincScalarSharedPtr(new FlatZincScalar(false, expr, dom));
}

void FlatZincBank::declare_var(
        NumFlatZincDomainSharedPtr dom,
        const char *ident,
        Term expr)
{
    assert(dom && ident);
    do_type_check(dom, ident, expr);
    std::string id(ident);

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("identifier '")
            << id << "' is already declared and/or defined elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    if (!expr) {
        const Symbol *s = mgr_->make_symbol(ident, get_datatype(dom));
        expr = mgr_->make_constant(s);
    }
    Term cs = make_bounds_constraint(dom, expr);
    assert(cs);
    const Symbol *s = cs->get_symbol();

    if (mgr_->is_false(s)) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
    }

    if (!mgr_->is_true(s)) {
        env_->assert_formula(cs);
    }


    scalar_decl_[id] = FlatZincScalarSharedPtr(new FlatZincScalar(true, expr, dom));
}

void FlatZincBank::declare_array_par(
        size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, TermListSharedPtr terms)
{
    assert(dom && ident && terms);

    do_type_check(dom, ident, terms);

    std::string id(ident);

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("identifier '")
            << id << "' is already declared and/or defined elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    if (len != terms->size()) {
        parser_->raise(ParserInterface::error("array '")
            << id << "' has size " << len << ", but was assigned " << terms->size(),
            FlatZincInterface::GENERIC_ERROR);
    }

    if (dom->is_empty()) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
    }

    if (!dom->is_unbounded()) {
        for (size_t i = 1; i <= len; ++i) {
            Term expr = (*terms)[i-1];
            assert(expr);

            Term cs = make_bounds_constraint(dom, expr);
            assert(cs);
            const Symbol *s = cs->get_symbol();

            if (mgr_->is_false(s)) {
                parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                    << "model inconsistency detected before search");
            }
            assert(mgr_->is_true(s));
        }
    }

    scalar_decl_[id] = FlatZincScalarSharedPtr(new FlatZincScalar(false, terms, dom));
}

void FlatZincBank::declare_array_var(
        size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, TermListSharedPtr terms)
{
    assert(dom && ident);

    do_type_check(dom, ident, terms);
    
    std::string id(ident);

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("identifier '")
            << id << "' is already declared and/or defined elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    if (terms && len != terms->size()) {
        parser_->raise(ParserInterface::error("array '")
            << id << "' has size " << len << ", but was assigned " << terms->size(),
            FlatZincInterface::GENERIC_ERROR);
    }

    if (dom->is_empty()) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
        return;
    }

    bool is_bounded = !dom->is_unbounded();

    if (!terms) {
        terms.reset(new TermList());
        for (size_t i = 1; i <= len; ++i) {
            Term expr = make_private_term(id, i, get_datatype(dom));
            terms->push_back(expr);
        }
    }

    if (is_bounded) {
        for (size_t i = 1; i <= len; ++i) {
            Term expr = (*terms)[i-1];
            assert(expr);

            if (is_bounded) {
                Term cs = make_bounds_constraint(dom, expr);
                assert(cs);
                const Symbol *s = cs->get_symbol();

                if (mgr_->is_false(s)) {
                    parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                        << "model inconsistency detected before search");
                }

                if (!mgr_->is_true(s)) {
                    env_->assert_formula(cs);
                }
            }
        }
    }

    scalar_decl_[id] = FlatZincScalarSharedPtr(new FlatZincScalar(true, terms, dom));
}

Term FlatZincBank::get_true()
{
     return true_;
}

Term FlatZincBank::get_false()
{
     return false_;
}

Term FlatZincBank::get_int_number(const char *value)
{
    assert(value);

    Term ret;
    Number n = QNumber::from_str(value);
    ret = mgr_->make_number(n);
    return ret;
}

Term FlatZincBank::get_float_number(const char *value)
{
    assert(value);
    Term ret;
    Number n = QNumber::from_str(value);
    ret = mgr_->make_number(n);
    return ret;
}

Term FlatZincBank::get_var_literal(
        bool var, FznType t, const char *ident)
{
    assert(ident);
    std::string id(ident);

    FznScalarDeclMap::iterator it = scalar_decl_.find(id);
    if (it != scalar_decl_.end()) {
        FlatZincScalarSharedPtr &decl = it->second;
        if (t & decl->type_) {
            assert(!decl->is_array_);
            if (var || !decl->is_var_) {
                return decl->value_;
            } // else: error: id is declared as var, but par requested
        } // else: error: id is of the wrong type
    } // else: error: id not declared or of set type

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("unexpected '")
                << id << "' where '" << get_string_var_literal(var, t)
                << "' was required",
                FlatZincInterface::TYPE_INST_ERROR);
    } else {
        parser_->raise(ParserInterface::error("'")
             << id << "' undeclared",
             FlatZincInterface::SYMBOL_ERROR);
    }
    return NULL;
}

Term FlatZincBank::get_var_literal(
        bool var, FznType t,
        const char *ident, size_t index)
{
    assert(ident);
    std::string id(ident);
    TermListSharedPtr terms = get_array_var_literal(var, t, ident);

    if (terms) {
        size_t len = terms->size();
        if (index < 1 || index > len) {
            parser_->raise(ParserInterface::error("array index out of range: ")
                << index,
                FlatZincInterface::GENERIC_ERROR);
        }
        return (*terms)[index-1];
    }
    return NULL;
}

TermListSharedPtr FlatZincBank::get_array_var_literal(
    bool var, FznType t, const char *ident)
{
    assert(ident);
    assert(t != FZN_NUMERIC);
    std::string id(ident);   

    FznScalarDeclMap::iterator it = scalar_decl_.find(id);
    if (it != scalar_decl_.end()) {
        FlatZincScalarSharedPtr &decl = it->second;
        if (t & decl->type_) {
            assert(decl->is_array_);
            if (var || !decl->is_var_) {
                return decl->values_;
            } // else: error: id is declared as var, but par requested
        } // else: error: id is of the wrong type
    } // else: error: id not declared or of set type

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("unexpected '")
                << id << "' where an array of '" << get_string_var_literal(var, t)
                << "' was required",
                FlatZincInterface::TYPE_INST_ERROR);
    } else {
        parser_->raise(ParserInterface::error("'")
             << id << "' undeclared",
             FlatZincInterface::SYMBOL_ERROR);
    }
    return TermListSharedPtr();
}

std::string FlatZincBank::get_string_var_literal(
        bool var, FznType t) const
{
    std::stringstream ss;
    ss << (var ? "var_" : "par_");
    switch (t) {
    case FZN_BOOL:
        ss << "bool";
        break;
    case FZN_INT:
        ss << "int";
        break;
    case FZN_FLOAT:
        ss << "float";
        break;
    default:
        assert(false);
    }
    return ss.str();
}

//-----------------------------------------------------------------------------
// set support
//-----------------------------------------------------------------------------

void FlatZincBank::declare_par_set(
        NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetSharedPtr iset)
{
    assert(dom && ident && iset);

    std::string id(ident);
    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("set '")
            << id << "' declared and/or defined as a variable elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    if (!dom->is_unbounded()) {
        parser_->raise(ParserInterface::error("")
            << "the `set of int' parameter `" << id
            << "' has elements that have a\n constrained type-inst, "
            << "but FlatZinc does not allow `set of int' parameters\n "
            << "whose elements have a constrained type-inst.",
            FlatZincInterface::TYPE_INST_ERROR);
    }

    // NOTE:
    // - no need to restrict domain, because `dom' is unbounded
    // - 'id' is left unassigned, so bool variables associated
    //   to set literal are only declared if needed

    set_decl_[id] = iset;
}

void FlatZincBank::declare_var_set(
        NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetSharedPtr iset)
{
    assert(dom && ident);
    
    std::string id(ident);
    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("set '")
            << id << "' declared and/or defined as a set elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    if (dom->is_unbounded() && !iset) {
        parser_->raise(ParserInterface::error("set '")
            << id << "' is not finite",
            FlatZincInterface::TYPE_INST_ERROR);
    }

    if (!iset) {
        iset = FznSetSharedPtr(new FlatZincSet(false));
    }
    set_decl_[id] = iset;

    if (!iset->apply_domain_restriction(*dom)) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "this assignment value is out of range");
    }

    if (!iset->is_set_literal() && iset->set_ident(id)) {
        Term ret = NULL;
        const NumIntervalSet &set = iset->get_domain();
        for (NumIntervalSet::value_iterator it = set.value_begin(),
                end = set.value_end(); it != end; ++it) {
            Term bpar = make_private_term(id, *it, mgr_->get_bool_type());
            if (iset->is_set_literal()) {
                ret = (ret ? mgr_->make_and(ret, bpar) : bpar);
            }
        }
        if (ret) {
            env_->assert_formula(ret);
        }
    }
}

void FlatZincBank::declare_array_par_set(
        size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetListSharedPtr isets)
{
    assert(dom && ident && isets);

    std::string id(ident);

    if (len != isets->size()) {
        parser_->raise(ParserInterface::error("array of sets '")
            << id << "' has size " << len << ", but was assigned " << isets->size(),
            FlatZincInterface::GENERIC_ERROR);
    }

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("set '")
            << id << "' declared and/or defined as a variable elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    if (!dom->is_unbounded()) {
        parser_->raise(ParserInterface::error("")
            << "the `array[int] of set of int' parameter `" << id
            << "' has elements\n that have a constrained type-inst, "
            << "but FlatZinc does not allow\n `array[int] of set of int' "
            << "parameters whose elements have a constrained\n type-inst.",
            FlatZincInterface::TYPE_INST_ERROR);
    }

    // NOTE:
    // - no need to restrict domain, because `dom' is unbounded
    // - 'id' is left unassigned, so bool variables associated
    //   to set literal are only declared if needed

    set_list_decl_[id] = isets;
}

void FlatZincBank::declare_array_var_set(
        size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetListSharedPtr isets)
{
    assert(dom && ident);

    std::string id(ident);

    if (isets && len != isets->size()) {
        parser_->raise(ParserInterface::error("array of sets '")
            << id << "' has size " << len << ", but was assigned " << isets->size(),
            FlatZincInterface::GENERIC_ERROR);
    }

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("variable '")
            << id << "' declared and/or defined as a variable elsewhere",
            FlatZincInterface::SYMBOL_ERROR);
    }

    if (dom->is_unbounded() && !isets) {
        parser_->raise(ParserInterface::error("sets '")
           << id << "' are not finite",
           FlatZincInterface::TYPE_INST_ERROR);
    }

    bool fresh_isets = false;
    if (!isets) {
        isets = FznSetListSharedPtr(new FznSetList());
        fresh_isets = true;

        if (dom->is_unbounded()) {
            parser_->raise(ParserInterface::error("set `")
                << id << "' element type is not finite",
                FlatZincInterface::TYPE_INST_ERROR);
        }
    }

    set_list_decl_[id] = isets;

    Term ret = NULL;
    for (size_t i = 1; i <= len; ++i) {
        std::stringstream ss;
        ss << ":" << ident << ":" << i;
        std::string id(ss.str());

        FznSetSharedPtr iset;
        if (fresh_isets) {
            iset = FznSetSharedPtr(new FlatZincSet(false));
            isets->push_back(iset);
        } else {
            iset = (*isets)[i-1];
        }

        if (!iset->apply_domain_restriction(*dom)) {
            parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                << "element " << i-1 << " of array of sets '" << id
                << "' is out of range");
        }

        if (!iset->is_set_literal() && iset->set_ident(id)) {
            const NumIntervalSet &set = iset->get_domain();
            for (NumIntervalSet::value_iterator it = set.value_begin(),
                    end = set.value_end(); it != end; ++it) {
                Term bpar = make_private_term(id, *it, mgr_->get_bool_type());

                if (iset->is_set_literal()) {
                    ret = (ret ? mgr_->make_and(ret, bpar) : bpar);
                }
            }
        }
    }

    if (ret) {
        env_->assert_formula(ret);
    }
}

FznSetSharedPtr FlatZincBank::get_set_literals(const char *ident)
{
    assert(ident);
    std::string id(ident);

    FznSetDeclMap::iterator it = set_decl_.find(id);
    if (it != set_decl_.end()) {
        return it->second;
    }

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("unexpected '")
                << id << "' where set was required",
                FlatZincInterface::TYPE_INST_ERROR);
    } else {
        parser_->raise(ParserInterface::error("'")
             << id << "' undeclared",
             FlatZincInterface::SYMBOL_ERROR);
    }
    return FznSetSharedPtr();
}

FznSetSharedPtr FlatZincBank::get_set_literals(const char *ident, size_t index)
{
    assert(ident);
    std::string id(ident);

    FznSetListDeclMap::iterator it = set_list_decl_.find(id);
    if (it != set_list_decl_.end()) {
        size_t len = it->second->size();
        if (index < 1 || index > len) {
            parser_->raise(ParserInterface::error("array index out of range: ")
                << index,
                FlatZincInterface::GENERIC_ERROR);
        }
        return (*(it->second))[index-1];
    }

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("unexpected '")
                << id << "' where array of sets was required",
                FlatZincInterface::TYPE_INST_ERROR);
    } else {
        parser_->raise(ParserInterface::error("'")
             << id << "' undeclared",
             FlatZincInterface::SYMBOL_ERROR);
    }
    return FznSetSharedPtr();
}

FznSetListSharedPtr FlatZincBank::get_array_set_literals(const char *ident)
{
    assert(ident);
    std::string id(ident);

    FznSetListDeclMap::iterator it = set_list_decl_.find(id);
    if (it != set_list_decl_.end()) {
        return it->second;
    }

    if (is_already_declared(id)) {
        parser_->raise(ParserInterface::error("unexpected '")
                << id << "' where array of sets was required",
                FlatZincInterface::TYPE_INST_ERROR);
    } else {
        parser_->raise(ParserInterface::error("'")
             << id << "' undeclared",
             FlatZincInterface::SYMBOL_ERROR);
    }
    return FznSetListSharedPtr();
}

//-----------------------------------------------------------------------------
// other functionality
//-----------------------------------------------------------------------------

void FlatZincBank::annotate_decl(const char *ident, FlatZincAnnotation &ann)
{
    
    std::string id(ident);
    std::vector<int64_t> shape;
    if (ann.is_output_var()) {
        output_vars_.push_back(id);
    }
    if (ann.is_output_array(shape)) {
        output_arrays_.push_back(OutputArray(id, shape));
    }
}

void FlatZincBank::bool2int(Term a, Term b)
{
    bool2int_[a] = b;
    int2bool_[b] = a;
}

void FlatZincBank::int2float(Term a, Term b)
{
    int2float_[a] = b;
    float2int_[b] = a;
}

bool FlatZincBank:: is_pseudoboolean(Term a, Term &out)
{
    return false;
}

void FlatZincBank::print_flatzinc_term(std::ostream *out, Term term) const
{
    const DataType *dt = term->get_type();
    size_t width;
    if (mgr_->is_bool_type(dt)) {
        if (mgr_->is_true(term->get_symbol())) {
            *out << "true";
        } else {
            *out << "false";
        }
    } else if (mgr_->is_integer_type(dt)) {
        Number n;
        mgr_->is_number(term->get_symbol(), &n); // value trusted
        *out << n.to_str();
    } else if (mgr_->is_rational_type(dt)) {
        Number n;
        mgr_->is_number(term->get_symbol(), &n); // value trusted
        *out << n.to_str();
    }
}

inline size_t compute_required_bits(Number &v)
{
    long lv = 0;
    bool ret = v.to_int(lv);
    // Assumption should be valid for FlatZinc Problems
    // if broken, logarithm has to be computed manually
    assert(ret);
    if (lv == 0) {
        return 1;
    } else {
        return (size_t) ceil(log2((lv < 0 ? - lv : lv) + 1)) + 1;
    }
}

size_t FlatZincBank::get_required_bv_bits(TermList &as, Term &lower, Term &upper, bool &positive_domain) const
{
    // assumption: as contains integer values / variables

    bool first = true;
    Number min;
    Number max;

    for (TermList::const_iterator it = as.begin(), iend = as.end();
            it != iend; ++it) {
        Term t = *it;
        Number v;
        bool is_number = mgr_->is_number(t->get_symbol(), &v);
        if (is_number) {
            if (v < min || first) {
                min = v;
            }
            if (v > max || first) {
                max = v;
            }
        } else {
            Number nlower;
            Number nupper;
            bool has_bounds = get_var_bounds(t, nlower, nupper);
            if (has_bounds) {
                if (nlower < min || first) {
                    min = nlower;
                }
                if (nupper > max || first) {
                    max = nupper;
                }
            } else {
                // assumes 32 bit domain for flatzinc INTS
                // warning: this might actually be a bad idea performance-wise
                // so it might be better to return width equal 0
                // and use integer encoding
                min = Number(std::numeric_limits<int32_t>::min());
                max = Number(std::numeric_limits<int32_t>::max());
                break;
            }
        }
        first = false;
    }

    size_t min_bits = compute_required_bits(min);
    size_t max_bits = compute_required_bits(max);
    size_t ret = (min_bits > max_bits ? min_bits : max_bits);
    if (min >= Number(0) && max >= Number(0) && ret > 1) {
        ret -= 1;
        positive_domain = true;
    } else {
        positive_domain = false;
    }
    lower = mgr_->make_number(min);
    upper = mgr_->make_number(max);

    return ret;
}

bool FlatZincBank::get_var_bounds(Term t, Number &lower, Number &upper) const
{
    assert(t);
    assert(!mgr_->is_bool_type(t->get_type()));

    // is it a constant value?
    Number v;
    bool res = mgr_->is_number(t->get_symbol(), &v);
    if (res) {
        lower = v;
        upper = v;
        return true;
    }
    
    std::string id(t->to_str());

    // is it a private variable name?
    if (id[0] == TermManager::INTERNAL_SYMBOLS_NAMESPACE) {
        std::vector<std::string> els;
        std::istringstream is(id);
        std::string s;
        while (std::getline(is, s, TermManager::INTERNAL_SYMBOLS_NAMESPACE)) {
            if (s != "") {
                els.push_back(s);
            }
        }
        if (els.size() > 1) {
            id = els[1]; // array / set
        } else {
            id = els[0]; // other
        }
    }

    FznScalarDeclMap::const_iterator it = scalar_decl_.find(id);
    if (it != scalar_decl_.end()) {
        NumFlatZincDomainSharedPtr dom = it->second->domain_;
        if (!dom->is_unbounded()) {
            lower = dom->lower();
            upper = dom->upper();
            return true;
        }
    }

    return false;
}

Term FlatZincBank::make_private_term(
        const DataType *tp) const
{
    assert(tp);

    std::stringstream ss;
    ss << TermManager::INTERNAL_SYMBOLS_NAMESPACE
       << "pvt_fzn_t";
    const Symbol *s = mgr_->make_unique_symbol(ss.str(), tp);
    assert(s);

    Term ret = mgr_->make_constant(s);
    assert(ret);
    return ret;
}

Term FlatZincBank::make_private_term(
        const std::string &str,
        size_t idx,
        const DataType *tp) const
{
    assert(tp);

    std::stringstream ss;
    ss << TermManager::INTERNAL_SYMBOLS_NAMESPACE << "pvt_fzn"
       << TermManager::INTERNAL_SYMBOLS_NAMESPACE << str
       << TermManager::INTERNAL_SYMBOLS_NAMESPACE << idx;
    const Symbol *s = mgr_->make_symbol(ss.str(), tp);
    assert(s);

    Term ret = mgr_->make_constant(s);
    assert(ret);
    return ret;
}

Term FlatZincBank::make_private_term(
        const std::string &str,
        Number idx,
        const DataType *tp) const
{
    assert(tp);

    std::stringstream ss;
    ss << TermManager::INTERNAL_SYMBOLS_NAMESPACE << "pvt_fzn"
       << TermManager::INTERNAL_SYMBOLS_NAMESPACE << str
       << TermManager::INTERNAL_SYMBOLS_NAMESPACE << idx.to_str();
    const Symbol *s = mgr_->make_symbol(ss.str(), tp);
    assert(s);

    Term ret = mgr_->make_constant(s);
    assert(ret);
    return ret;
}

Term FlatZincBank::make_private_pbsum(
        TermList &clauses,
        Term weight) const
{
    TermList tmp;
    for (size_t i = 0; i < clauses.size(); i++) {
        tmp.push_back(weight);
    }
    return make_private_pbsum(clauses, tmp);
}

Term FlatZincBank::make_private_pbsum(
        TermList &clauses,
        TermList &weights) const
{
    static uint64_t counter;
    std::stringstream ss;
    ss << TermManager::INTERNAL_SYMBOLS_NAMESPACE
       << "pvt_fzn_pbsum_"<<counter++;
    const Symbol *s = mgr_->make_unique_symbol(ss.str(),
                                               mgr_->get_rational_type());
    assert(s);
    Term ret = mgr_->make_constant(s);
    assert(ret);

    Term enc = optenv_->make_circuit(clauses, weights, ret);
    assert(enc);
    env_->assert_formula(enc);
    return ret;
}

//-----------------------------------------------------------------------------
// private functionality
//-----------------------------------------------------------------------------

const DataType *FlatZincBank::get_bv_datatype(NumFlatZincDomainSharedPtr &dom) const
{
    /*assert(cmdline_->fzn_bv_integers());
    // FIXME: here you can always force width of 25 (or configurable)
    //        instead of trying to dynamically compute the right size
    //        this would help because you no longer need to extend BV
    //        around, though you might have more bits than needed on some problems
    if (dom->is_unbounded()) {
        return mgr_->get_bv_type(25);  // 25: -10.000.000..10.000.000 default MiniZinc domain
                                       // TODO(PT): this should be a configurable option
    } else {
        Number low = dom->lower();
        Number upp = dom->upper();
        size_t s = get_sbv_size(low, upp);
        return mgr_->get_bv_type(s);
    }*/
}

const DataType *FlatZincBank::get_datatype(NumFlatZincDomainSharedPtr &dom) const
{
    assert(dom);
    FznType type = dom->type();
    switch(type) {
    case FZN_BOOL:
        return mgr_->get_bool_type();
    case FZN_INT:
        return mgr_->get_integer_type();
    case FZN_FLOAT:
        return mgr_->get_rational_type();
    default:
        return NULL;
    }
}

const DataType *FlatZincBank::get_datatype(FznType type) const
{
    switch(type) {
    case FZN_BOOL:
        return mgr_->get_bool_type();
    case FZN_INT:
        return mgr_->get_integer_type();
    case FZN_FLOAT:
        return mgr_->get_rational_type();
    default:
        return NULL;
    }
}

void FlatZincBank::do_type_check(NumFlatZincDomainSharedPtr &dom, const char *ident, Term expr) const
{
    assert(dom && ident);
    if (expr) {
        FznType type = dom->type();
        if (!is_compatible_type(type, expr)) {
            std::stringstream ss;
            ss << "initialisation of value for `" << ident
               << "'has invalid type-inst:\n\texpected `";
            switch(type) {
            case FZN_BOOL:
                ss << "bool";
                break;
            case FZN_INT:
                ss << "int";
                break;
            case FZN_FLOAT:
                ss << "float";
                break;
            default:
                ss << "unknown";
            }
            ss << "'";
            parser_->raise(ParserInterface::error(ss.str()),
                FlatZincInterface::TYPE_INST_ERROR);
        }
    }
}

void FlatZincBank::do_type_check(NumFlatZincDomainSharedPtr &dom, const char *ident, TermListSharedPtr exprs) const
{
    assert(dom && ident);
    if (exprs) {
        FznType type = dom->type();
        bool error = false;
        for (TermList::iterator it = exprs->begin(), end = exprs->end();
                it != end; ++it) {
            if (!is_compatible_type(type, *it)) {
                error = true;
                break;
            }
        }
        if (error) {
            std::stringstream ss;
            ss << "initialisation of value for `" << ident
               << "'has invalid type-inst:\n\texpected `";
            switch(type) {
            case FZN_BOOL:
                ss << "bool";
                break;
            case FZN_INT:
                ss << "int";
                break;
            case FZN_FLOAT:
                ss << "float";
                break;
            default:
                ss << "unknown";
            }
            ss << "'";
            parser_->raise(ParserInterface::error(ss.str()),
                FlatZincInterface::TYPE_INST_ERROR);
        }
    }
}

bool FlatZincBank::is_compatible_type(FznType type, Term t) const
{
    assert(t);
    const DataType *tp = t->get_type();
    if(!tp){
        std::cout<<"is_compatible_type Emtpy\n";
    }
    //std::cout<<"The type: "<<type<<std::endl;
    switch(type) {
    case FZN_BOOL:
        return mgr_->is_bool_type(tp);
    case FZN_INT:
        return mgr_->is_integer_type(tp);
    case FZN_FLOAT:
        return mgr_->is_rational_type(tp) || mgr_->is_integer_type(tp);
    default:
        return false;
    }
}

bool FlatZincBank::is_already_declared(std::string &id)
{
    return (scalar_decl_.find(id) != scalar_decl_.end())
           || (set_decl_.find(id) != set_decl_.end())
           || (set_list_decl_.find(id) != set_list_decl_.end());
}

//-----------------------------------------------------------------------------
// Bounds Declarations
//-----------------------------------------------------------------------------

Term FlatZincBank::make_bounds_constraint(
        NumFlatZincDomainSharedPtr &dom, Term var)
{
    assert(dom);
    assert(var);
    assert(dom->type() != FZN_NUMERIC);
    if (dom->type() == FZN_BOOL) {
        return true_;
    }
    assert(FZN_INT == dom->type()
           || FZN_FLOAT == dom->type());
    if (dom->is_unbounded()) {
        return true_;
    } else if (dom->is_empty()) {
        return false_;
    } else {
            return make_la_bounds_constraint(dom, var);
    }
}

Term FlatZincBank::make_la_bounds_constraint(
        NumFlatZincDomainSharedPtr &dom, Term var)
{
    Term ret = NULL;
    if (dom->is_single_valued()) {
        ret = mgr_->make_equal(var, mgr_->make_number(dom->lower()));
    } else {
        ret = mgr_->make_and(
              mgr_->make_leq(mgr_->make_number(dom->lower()), var),
              mgr_->make_leq(var, mgr_->make_number(dom->upper())));
    }
    
    if (dom->is_fragmented()) {
        Term tvalues = false_;
        const NumIntervalSet &set = dom->domain_values();

        TermList clauses;
        for (NumIntervalSet::subset_iterator it = set.subset_begin(),
                end = set.subset_end(); it != end; ++it) {
            Term sub = mgr_->make_and(
                       mgr_->make_leq(mgr_->make_number(it->lower()), var),
                       mgr_->make_leq(var, mgr_->make_number(it->upper())));
            tvalues = mgr_->make_or(tvalues, sub);
            clauses.push_back(mgr_->make_not(sub));
        }
        Term pbterm = make_private_pbsum(clauses, one_);
        ret = mgr_->make_and(ret, tvalues);
        ret = mgr_->make_and(ret, mgr_->make_leq(one_, pbterm));
        ret = mgr_->make_and(ret, mgr_->make_leq(pbterm, one_));
    }
    
    return ret;
}

}} // namespace msat::opt
