// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../utils/exception.h"
#include "../utils/strutils.h"
#include "../utils/varsetter.h"
#include "../toplevel/flatzincinterface.h"
#include "../toplevel/flatzincglconstraints.h"
#include "../parser/flatzincbisonparser.h"
#include "../parser/flatzincflexlexer.h"
#include "../api/optenvironment.h"
#include "../utils/termination.h"
#include <iomanip>



using namespace std;

extern int msat_flatzinc_parser_parse(yyscan_t scanner, msat::FlatZincAbstractParser *parser);

namespace {

struct FlexScanner {
    yyscan_t scanner;
    msat::ParserInterface::istream_info info;
    msat::ParserInterface::str_alloc *alloc;

    FlexScanner(std::istream &source, msat::ParserInterface::str_alloc *a):
        alloc(a)
    {
        init(source);
    }
    ~FlexScanner() { msat_flatzinc_parser_lex_destroy(scanner); }

    void reset(std::istream &source)
    {
        msat_flatzinc_parser_lex_destroy(scanner);
        init(source);
    }

    bool eof() const { return info.done; }

private:
    void init(std::istream &source)
    {
        info = msat::ParserInterface::istream_info(&source, alloc);
        msat_flatzinc_parser_lex_init(&scanner);
        msat_flatzinc_parser_set_extra(&info, scanner);
    }
    FlexScanner &operator=(const FlexScanner &other);
    FlexScanner(const FlexScanner &);
};

} // namespace


namespace msat { namespace opt {

//-----------------------------------------------------------------------------
// Init/Deinit
//-----------------------------------------------------------------------------

FlatZincInterface::FlatZincInterface(Configuration *config, CmdLine *cmdline, bool bv):
    cmdline_(cmdline),
    cfg_(config),
    env_(NULL),
    optenv_(NULL),
    mgr_(NULL),
    bank_(NULL),
    constraints_(NULL),
    timeout_(0),
    memlimit_mb_(0),
    flex_scanner_(NULL)
{
    outstream_ = new file_ostream(stdout);
    errstream_ = new file_ostream(stderr);

    inputfile_ = cmdline_->get_input_file();
    if (inputfile_ == "") {
        inputfile_ = "line";
    }

    reset_response();
    print_success_ = false;
    print_model_ = true;

    // Note: model generation always enabled for FlatZinc
    //cfg_->set_model_generation(true);
    //cfg_->set_par_mode(Configuration::PARETO_CALLBACK);

    status_ = Environment::UNKNOWN;
}

FlatZincInterface::~FlatZincInterface()
{
    if (errstream_ != &(std::cerr) && errstream_ != &(std::cout)) {
        delete errstream_;
    }
    if (outstream_ != &(std::cout) && outstream_ != &(std::cerr)) {
        delete outstream_;
    }
    if (env_) delete env_;
    if (bank_) delete bank_;
    if (constraints_) delete constraints_;
    optenv_ = NULL;
    bank_ = NULL;
    constraints_ = NULL;
}

//-----------------------------------------------------------------------------
// TopLevel Interface
//-----------------------------------------------------------------------------

void FlatZincInterface::main_loop(std::istream &source)
{
    FlexScanner s(source, get_str_alloc());
    flex_scanner_ = s.scanner;
    reset_response();

    bool done = false;
    while (!done && !s.eof()) {
        try {
            msat_flatzinc_parser_parse(s.scanner, this);
            if (!s.eof()) {
                print_response();
                reset_response();
            } else if (prefetch_phase_ && (response_ == SUCCESS)) {
                source.clear();
                source.seekg(0);
                s.reset(source);
                prefetch_phase_ = false;
            }
        } catch (FlatZincInterface::exiting &) {
            print_response();
            done = true;
        } catch (FlatZincInterface::early_unsat &err) {
            response_ = EARLY_UNSAT;
            error_msg_ = err.get_msg();
            print_response();
            s.reset(source);
        } catch (ParserInterface::error &err) {
            response_ = ERROR;
            error_msg_ = err.get_msg();
            print_response();
            s.reset(source);
        } catch (Exception &err) { // internal mathsat exceptions
            response_ = ERROR;
            std::stringstream ss;
            if (flex_scanner_) {
                int lineno = msat_flatzinc_parser_get_lineno(flex_scanner_);
                ss << inputfile_ << ":" << lineno << ":\n";
            }
            ss << "\tmsat error: " << err.get_msg();
            error_msg_ = ss.str();
            print_response();
            s.reset(source);
        }
    }
    std::cout<<"(check-sat)\n(get-objectives)\n";
}

//-----------------------------------------------------------------------------
// FlatZinc Interface
//-----------------------------------------------------------------------------

void FlatZincInterface::print_response()
{
    switch (response_) {
    case SUCCESS: {
        if (print_success_) (*outstream_) << "success" << std::endl;
        print_model();
        break;
    }
    case ERROR: {
        (*errstream_) << error_msg_ << std::endl;
        break;
    }
    case UNSUPPORTED: {
        (*errstream_) << "unsupported" << std::endl;
        break;
    }
    case STATUS: {
        assert(env_);
        if (status_ == Environment::SAT) {
            if (print_model_) {
                print_model();
            }
        } else {
            (*outstream_) << (status_ == Environment::UNSAT
                              ? "=====UNSATISFIABLE====="
                              : "=====UNKNOWN=====")
                          << std::endl;
            print_model();
        }
        break;
    }
    case EARLY_UNSAT: {
        assert(status_ == Environment::UNSAT);
        (*outstream_) << "=====UNSATISFIABLE====="
                      << std::endl;
        (*outstream_) << error_msg_ << std::endl;
        break;
    }
    case INFO:
    case MODEL:
    case UNSATCORE:
    case INTERPOLANT:
    default:
        assert(false);
    }
}

void FlatZincInterface::reset_response()
{
    response_ = SUCCESS;
    error_msg_ = "";
}

void FlatZincInterface::handle_error(const char *msg)
{
    if (response_ != ERROR) {
        raise(Exception(msg));
    }
}

//-----------------------------------------------------------------------------
// FlatZinc Variable Declarations
//-----------------------------------------------------------------------------

void FlatZincInterface::declare_par(NumFlatZincDomainSharedPtr dom,
        const char *ident, Term expr)
{
    assert(dom && ident && expr);

    init_env();

    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_par(dom, ident, expr);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::declare_var(NumFlatZincDomainSharedPtr dom,
        const char *ident, Term expr)
{
    assert(dom && ident);
    init_env();
    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_var(dom, ident, expr);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::declare_array_par(
        size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, TermListSharedPtr terms)
{
    assert(dom && ident && terms);

    init_env();

    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_array_par(len, dom, ident, terms);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::declare_array_var(
        size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, TermListSharedPtr terms)
{
    assert(dom && ident);

    init_env();

    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_array_var(len, dom, ident, terms);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::declare_par_set(NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetSharedPtr set)
{
    assert(dom && ident && set);

    init_env();

    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_par_set(dom, ident, set);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::declare_var_set(NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetSharedPtr set)
{
    assert(dom && ident);

    init_env();

    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_var_set(dom, ident, set);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::declare_array_par_set(size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetListSharedPtr isets)
{
    assert(dom && ident && isets);

    init_env();

    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_array_par_set(len, dom, ident, isets);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::declare_array_var_set(size_t len, NumFlatZincDomainSharedPtr dom,
        const char *ident, FznSetListSharedPtr isets)
{
    assert(dom && ident);

    init_env();

    if (prefetch_phase_ && response_ != ERROR) {
        bank_->declare_array_var_set(len, dom, ident, isets);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::annotate_decl(const char *ident, FlatZincAnnotation &ann)
{

    assert(ident);
    
    init_env();
    if (prefetch_phase_ && response_ != ERROR) {
        bank_->annotate_decl(ident, ann);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// FlatZinc Expressions
//-----------------------------------------------------------------------------

Term FlatZincInterface::get_true()
{
    init_env();

    if (response_ != ERROR) {
        Term ret = bank_->get_true();
        response_ = SUCCESS;
        return ret;
    }
    return NULL;
}

Term FlatZincInterface::get_false()
{
    init_env();

    if (response_ != ERROR) {
        Term ret = bank_->get_false();
        response_ = SUCCESS;
        return ret;
    }
    return NULL;
}

Term FlatZincInterface::get_int_number(const char *value)
{
    assert(value);

    init_env();

    if (response_ != ERROR) {
        Term ret = bank_->get_int_number(value);
        response_ = SUCCESS;
        return ret;
    }
    return NULL;
}

Term FlatZincInterface::get_float_number(const char *value)
{
    assert(value);

    init_env();

    if (response_ != ERROR) {
        Term ret = bank_->get_float_number(value);
        response_ = SUCCESS;
        return ret;
    }
    return NULL;
}

Term FlatZincInterface::get_var_literal(
        bool var, FznType t, const char *ident)
{
    init_env();

    if (response_ != ERROR) {
        Term ret = bank_->get_var_literal(var, t, ident);
        response_ = SUCCESS;
        return ret;
    }
    return NULL;
}

Term FlatZincInterface::get_var_literal(
        bool var, FznType t,
        const char *ident, size_t index)
{
    init_env();

    if (response_ != ERROR) {
        Term ret = bank_->get_var_literal(var, t, ident, index);
        response_ = SUCCESS;
        return ret;
    }
    return NULL;
}

TermListSharedPtr FlatZincInterface::get_array_var_literal(
        bool var, FznType t, const char *ident)
{
    init_env();

    if (response_ != ERROR) {
        TermListSharedPtr ret = bank_->get_array_var_literal(var, t, ident);
        response_ = SUCCESS;
        return ret;
    }
    return TermListSharedPtr();
}

FznSetSharedPtr FlatZincInterface::get_set_literals(const char *ident)
{
    init_env();

    if (response_ != ERROR) {
        FznSetSharedPtr ret = bank_->get_set_literals(ident);
        response_ = SUCCESS;
        return ret;
    }
    return FznSetSharedPtr();
}

FznSetSharedPtr FlatZincInterface::get_set_literals(const char *ident, size_t index)
{
    init_env();

    if (response_ != ERROR) {
        FznSetSharedPtr ret = bank_->get_set_literals(ident, index);
        response_ = SUCCESS;
        return ret;
    }
    return FznSetSharedPtr();
}

FznSetListSharedPtr FlatZincInterface::get_array_set_literals(const char *ident)
{
    init_env();

    if (response_ != ERROR) {
        FznSetListSharedPtr ret = bank_->get_array_set_literals(ident);
        response_ = SUCCESS;
        return ret;
    }
    return FznSetListSharedPtr();
}

void FlatZincInterface::push_objective(FlatZincAbstractParser::SolveType type, Term expr)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {

        assert(expr);
        Term lower = NULL;
        Term upper = NULL;
        Number nlower;
        Number nupper;
        bool ret = bank_->get_var_bounds(expr, nlower, nupper);
        if (ret) {
            size_t width;
                lower = env_->make_number(nlower);
                upper = env_->make_number(nupper);
        }
        OptSearch *ptr = NULL;
        switch(type) {
        case FlatZincAbstractParser::MAXIMIZE:
            ptr = optenv_->make_maximize(expr, lower, upper, "", true, false);
            break;
        case FlatZincAbstractParser::MINIMIZE:
        default:
            ptr = optenv_->make_minimize(expr, lower, upper, "", true, false);
            break;
        }
        response_ = SUCCESS;
    }
}


//-----------------------------------------------------------------------------
// FlatZinc Constraints
//-----------------------------------------------------------------------------

void FlatZincInterface::array_bool_and(TermList &as, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_bool_and(as, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_bool_element(Term b, TermList &as, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_bool_or(TermList &as, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_bool_or(as, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    };
}

void FlatZincInterface::array_bool_xor(TermList &as)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) { // PTTODO: this could be done with sorting network
        Term ret = constraints_->array_bool_xor(as);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_float_element(Term b, TermList &as, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_int_element(Term b, TermList &as, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_var_bool_element(Term b, TermList &as, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_var_float_element(Term b, TermList &as, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_var_int_element(Term b, TermList &as, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool2int(Term a, Term b)
{
    init_env();

    if (response_ != ERROR) {
        if (prefetch_phase_) {
            bank_->bool2int(a, b);
        } else {
            Term ret = constraints_->bool2int(a, b);
            if (ret) {
                env_->assert_formula(ret);
            }
        }
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_and(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        TermList tmp;
        tmp.push_back(a);
        tmp.push_back(b);
        Term ret = constraints_->array_bool_and(tmp, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_clause(TermList &as, TermList &bs)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_clause(as, bs);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_eq(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_eq(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_eq_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_eq_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_le(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_le(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_le_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_le_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_lin_eq(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_lin_eq(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_lin_le(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_lin_le(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_lt(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_lt(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_lt_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_lt_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_not(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_not(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_or(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        TermList tmp;
        tmp.push_back(a);
        tmp.push_back(b);
        Term ret = constraints_->array_bool_or(tmp, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bool_xor(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_xor(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_abs(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_abs(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_div(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_div(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

// TODO: support these functions if A is a parametric value
void FlatZincInterface::float_acos(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_acos unsupported";
}

void FlatZincInterface::float_asin(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_asin unsupported";
}

void FlatZincInterface::float_atan(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_atan unsupported";
}

void FlatZincInterface::float_cos(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_cos unsupported";
}

void FlatZincInterface::float_cosh(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_cosh unsupported";
}

void FlatZincInterface::float_exp(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_exp unsupported";
}

void FlatZincInterface::float_ln(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_ln unsupported";
}

void FlatZincInterface::float_log2(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_log2 unsupported";
}

void FlatZincInterface::float_log10(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_log10 unsupported";
}

void FlatZincInterface::float_sqrt(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_sqrt unsupported";
}

void FlatZincInterface::float_sin(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_sin unsupported";
}

void FlatZincInterface::float_sinh(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_sinh unsupported";
}

void FlatZincInterface::float_tan(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_tan unsupported";
}

void FlatZincInterface::float_tanh(Term a, Term b)
{
    response_ = ERROR;
    error_msg_ = "float_tanh unsupported";
}

void FlatZincInterface::float_eq(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_eq(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_eq_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_eq_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_le(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_le(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_le_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_le_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_eq(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_eq(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_eq_reif(as, bs, c, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_le(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_le(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_le_reif(TermList &as, TermList &bs, Term c, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_le_reif(as, bs, c, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_lt(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_lt(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_lt_reif(TermList &as, TermList &bs, Term c, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_lt_reif(as, bs, c, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_ne(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_ne(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lin_ne_reif(as, bs, c, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lt(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lt(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_lt_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_lt_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_max(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_max(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_min(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_min(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_ne(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_ne(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_ne_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_ne_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_plus(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_plus(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_times(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_times(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_abs(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_abs(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_div(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_div(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_eq(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_eq(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_eq_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_eq_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_le(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_le(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_le_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_le_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lin_eq(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lin_eq(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lin_eq_reif(as, bs, c, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lin_le(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lin_le(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lin_le_reif(TermList &as, TermList &bs, Term c, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lin_le_reif(as, bs, c, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lin_ne(TermList &as, TermList &bs, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lin_ne(as, bs, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lin_ne_reif(as, bs, c, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lt(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lt(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_lt_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_lt_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_max(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_max(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_min(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_min(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_mod(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_mod(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_ne(Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_ne(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_ne_reif(Term a, Term b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_ne_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_plus(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_plus(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int_times(Term a, Term b, Term c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_times(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::int2float(Term a, Term b)
{
    init_env();

    if (response_ != ERROR) {
        if (prefetch_phase_) {
            bank_->int2float(a, b);
        } else {
            Term ret = constraints_->int2float(a, b);
            if (ret) {
                env_->assert_formula(ret);
            }
        }
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_set_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_var_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_set_element(b, as, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_card(FznSetSharedPtr a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_card(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_diff(FznSetSharedPtr a,
        FznSetSharedPtr b, FznSetSharedPtr c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_diff(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_eq(FznSetSharedPtr a, FznSetSharedPtr b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_eq(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_eq_reif(FznSetSharedPtr a,
        FznSetSharedPtr b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_eq_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_in(Term a, FznSetSharedPtr b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_in(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_in_reif(Term a,
        FznSetSharedPtr b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_in_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_intersect(FznSetSharedPtr a,
        FznSetSharedPtr b, FznSetSharedPtr c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_intersect(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_le(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_le(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_lt(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_lt(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_ne(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_ne(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_ne_reif(FznSetSharedPtr a,
        FznSetSharedPtr b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_ne_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_subset(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_subseteq(a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_subset_reif(FznSetSharedPtr a,
        FznSetSharedPtr b, Term r)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_subseteq_reif(a, b, r);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::set_symdiff(FznSetSharedPtr a,
        FznSetSharedPtr b, FznSetSharedPtr c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_symdiff(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}


void FlatZincInterface::set_union(FznSetSharedPtr a,
        FznSetSharedPtr b, FznSetSharedPtr c)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->set_union(a, b, c);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// all_different
//-----------------------------------------------------------------------------

void FlatZincInterface::all_different(TermList &as)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->all_different(as);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::all_different_except_0(TermList &as)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->all_different_except_0(as);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::all_different(FznSetListSharedPtr as)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->all_different(as);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// disjoint
//-----------------------------------------------------------------------------

void FlatZincInterface::disjoint(FznSetSharedPtr s1,
        FznSetSharedPtr s2)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->disjoint(s1, s2);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::all_disjoint(FznSetListSharedPtr as)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->all_disjoint(as);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// disjunctive
//-----------------------------------------------------------------------------

void FlatZincInterface::disjunctive(TermList &s,
        TermList &d)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->disjunctive(s, d);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::disjunctive_strict(
        TermList &s, TermList &d)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->disjunctive_strict(s, d);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// all_equal
//-----------------------------------------------------------------------------

void FlatZincInterface::all_equal(TermList &x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->all_equal(x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::all_equal(FznSetListSharedPtr x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->all_equal(x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// among
//-----------------------------------------------------------------------------

void FlatZincInterface::among(Term n, TermList &x, FznSetSharedPtr v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->among(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// array_max/min
//-----------------------------------------------------------------------------

void FlatZincInterface::array_max(Term m, TermList &x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_max(m, x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::array_min(Term m, TermList &x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->array_min(m, x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// maximum/minimum_arg
//-----------------------------------------------------------------------------

void FlatZincInterface::maximum_arg(TermList &x,
        Term i, const NumInterval &xdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->maximum_arg(x, i, xdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::minimum_arg(TermList &x,
        Term i, const NumInterval &xdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->minimum_arg(x, i, xdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// at_least/exactly/at_most
//-----------------------------------------------------------------------------

void FlatZincInterface::at_least_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->at_least_set(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::exactly_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->exactly_set(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::at_most_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->at_most_set(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::at_most_1(FznSetListSharedPtr x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->at_most_1(x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// bin_packing
//-----------------------------------------------------------------------------

void FlatZincInterface::bin_packing(Term c, TermList &bin, TermList &w)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bin_packing(c, bin, w);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bin_packing_capa(TermList &c, TermList &bin,
        TermList &w, const NumInterval &cdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bin_packing_capa(c, bin, w, cdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::bin_packing_load(TermList &load, TermList &bin,
        TermList &w, const NumInterval &loaddom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bin_packing_load(load, bin, w, loaddom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// element
//-----------------------------------------------------------------------------

void FlatZincInterface::element(Term i,
        TermList &x, Term y, NumInterval &xdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->element(i, x, y, xdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::element(Term i,
        FznSetListSharedPtr x, FznSetSharedPtr y,
        NumInterval &xdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->element(i, x, y, xdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// comparison_rel_array
//-----------------------------------------------------------------------------

void FlatZincInterface::comparison_rel_array(TermList &rels, Term rel)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->comparison_rel_array(rels, rel);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// count
//-----------------------------------------------------------------------------

void FlatZincInterface::count_eq(Term n, TermList &x, Term v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->count_eq(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::count_geq(Term n, TermList &x, Term v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->count_geq(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::count_gt(Term n, TermList &x, Term v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->count_gt(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::count_leq(Term n, TermList &x, Term v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->count_leq(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::count_lt(Term n, TermList &x, Term v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->count_lt(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::count_neq(Term n, TermList &x, Term v)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->count_neq(n, x, v);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// decreasing/increasing
//-----------------------------------------------------------------------------

void FlatZincInterface::decreasing(TermList &x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->decreasing(x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::decreasing(FznSetListSharedPtr x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->decreasing(x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::increasing(TermList &x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->increasing(x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::increasing(FznSetListSharedPtr x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->increasing(x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// diffn
//-----------------------------------------------------------------------------

void FlatZincInterface::diffn(TermList &x, TermList &y,
        TermList &dx, TermList &dy)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->diffn(x, y, dx, dy);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::diffn_nonstrict(TermList &x, TermList &y,
        TermList &dx, TermList &dy)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->diffn_nonstrict(x, y, dx, dy);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::diffn_nonoverlap_k(TermList &x1, TermList &w1,
        TermList &x2, TermList &w2)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->diffn_nonoverlap_k(x1, w1, x2, w2);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::diffn_nonstrict_nonoverlap_k(TermList &x1,
        TermList &w1, TermList &x2, TermList &w2)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->diffn_nonstrict_nonoverlap_k(x1, w1, x2, w2);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// distribute
//-----------------------------------------------------------------------------

void FlatZincInterface::distribute(TermList &card, TermList &value, TermList &base)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->distribute(card, value, base);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// geost
//-----------------------------------------------------------------------------

void FlatZincInterface::geost_nonoverlap_k(TermList &x1, TermList &w1,
        TermList &x2, TermList &w2)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->geost_nonoverlap_k(x1, w1, x2, w2);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// global_cardinality
//-----------------------------------------------------------------------------

void FlatZincInterface::global_cardinality(TermList &x,
        TermList &cover, TermList &costs)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->global_cardinality(x, cover, costs);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::global_cardinality_closed(TermList &x,
        TermList &cover, TermList &costs)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->global_cardinality_closed(x, cover, costs);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::global_cardinality_low_up(TermList &x,
        TermList &cover, TermList &lbound, TermList &ubound)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->global_cardinality_low_up(x, cover, lbound, ubound);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::global_cardinality_low_up_closed(TermList &x,
        TermList &cover, TermList &lbound, TermList &ubound)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->global_cardinality_low_up_closed(x, cover, lbound, ubound);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// int_set_channel
//-----------------------------------------------------------------------------

void FlatZincInterface::int_set_channel(TermList &x, FznSetListSharedPtr y,
        const NumInterval &xdom, const NumInterval &ydom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->int_set_channel(x, y, xdom, ydom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// inverse
//-----------------------------------------------------------------------------

void FlatZincInterface::inverse(TermList &f, TermList &invf,
        const NumInterval &fdom, const NumInterval &invfdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->inverse(f, invf, fdom, invfdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::inverse_set(FznSetListSharedPtr f,
        FznSetListSharedPtr invf, const NumInterval &fdom,
        const NumInterval &invfdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->inverse_set(f, invf, fdom, invfdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// link_set_to_booleans
//-----------------------------------------------------------------------------

void FlatZincInterface::link_set_to_booleans(FznSetSharedPtr s,
        TermList &b, const NumInterval &bdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->link_set_to_booleans(s, b, bdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// member
//-----------------------------------------------------------------------------

void FlatZincInterface::member(TermList &x, Term y)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->member(x, y);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::member(FznSetListSharedPtr x,
        FznSetSharedPtr y)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->member(x, y);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// nvalue
//-----------------------------------------------------------------------------

void FlatZincInterface::nvalue(Term n, TermList &x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->nvalue(n, x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// range
//-----------------------------------------------------------------------------

void FlatZincInterface::range(TermList &x, FznSetSharedPtr s,
        FznSetSharedPtr t, const NumInterval &xdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->range(x, s, t, xdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// bool_clause_reif
//-----------------------------------------------------------------------------

void FlatZincInterface::bool_clause_reif(TermList &as,
        TermList &bs, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->bool_clause_reif(as, bs, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// float_dom
//-----------------------------------------------------------------------------

void FlatZincInterface::float_in(Term x,
        Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_in(x, a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::float_dom(Term x, TermList &as,
        Term a, Term b)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->float_dom(x, as, a, b);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// roots
//-----------------------------------------------------------------------------

void FlatZincInterface::roots(TermList &x, FznSetSharedPtr s,
        FznSetSharedPtr t, const NumInterval &xdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->roots(x, s, t, xdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// sum_pred
//-----------------------------------------------------------------------------

void FlatZincInterface::sum_pred(Term i, FznSetListSharedPtr sets,
        TermList &cs, Term s, const NumInterval &csdom,
        const NumInterval &setsdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->sum_pred(i, sets, cs, s, csdom, setsdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// symmetric_all_different
//-----------------------------------------------------------------------------

void FlatZincInterface::symmetric_all_different(TermList &x,
        const NumInterval &xdom)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->symmetric_all_different(x, xdom);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// value_precede
//-----------------------------------------------------------------------------

void FlatZincInterface::value_precede(Term s, Term t,
        TermList &x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->value_precede(s, t, x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

void FlatZincInterface::value_precede(Term s, Term t,
        FznSetListSharedPtr x)
{
    init_env();

    if (!prefetch_phase_ && response_ != ERROR) {
        Term ret = constraints_->value_precede(s, t, x);
        assert(ret);
        env_->assert_formula(ret);
        response_ = SUCCESS;
    }
}

//-----------------------------------------------------------------------------
// Private Help Functions
//-----------------------------------------------------------------------------

void FlatZincInterface::print_model()
{
    // Nothing to do
}

void FlatZincInterface::init_env()
{
    if (!env_) {
        cmdline_->update_config(cfg_);
        env_ = new OptEnvironment(cfg_);

        mgr_ = env_->get_term_manager();

        bank_ = new FlatZincBank(this, env_, cmdline_);
        constraints_ = new FlatZincGlConstraints(this, env_, cmdline_, bank_);

        optenv_ = dynamic_cast<OptEnvironment*>(env_);
        prefetch_phase_ = true;
    }
}

void FlatZincInterface::raise(const std::exception &exc, size_t type)
{
    std::stringstream ss;
    
    if (flex_scanner_) {
        int lineno = msat_flatzinc_parser_get_lineno(flex_scanner_);
        ss << inputfile_ << ":" << lineno << ":\n";
    }
    
    ss << "\t";
    switch(type) {
        case SYNTAX_ERROR:
            ss << "syntax error:";
            break;
        case SYMBOL_ERROR:
            ss << "symbol error:";
            break;
        case TYPE_INST_ERROR:
            ss << "type-inst error:";
            break;
        case EVALUATION_ERROR:
            ss << "evaluation error:";
            break;
        case GENERIC_ERROR:
        default:
            ss << "error:";
            break;
    }
    ss << " " << exc.what();
    throw (ParserInterface::error(ss.str()));
}

void FlatZincInterface::raise_early_unsat(const std::exception &exc)
{
    status_ = Environment::UNSAT;
    std::stringstream ss;
    ss << "% " << inputfile_;
    
    if (flex_scanner_) {
        int lineno = msat_flatzinc_parser_get_lineno(flex_scanner_);
        ss << ":" << lineno;
    }
    ss << ": warning: " << exc.what() << ".";
    throw (FlatZincInterface::early_unsat(ss.str()));
}

}} // namespace msat::opt
