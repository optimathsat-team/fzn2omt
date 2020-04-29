// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../toplevel/flatzincconstraints.h"
#include "../api/optenvironment.h"
#include "../toplevel/flatzincbv.h"
#include<iostream>

namespace msat {

namespace opt {

//-----------------------------------------------------------------------------
// Init/Deinit
//-----------------------------------------------------------------------------

FlatZincConstraints::FlatZincConstraints(FlatZincInterface *parser,
        Environment *env, CmdLine *cmdline, FlatZincBank *bank):
    parser_(parser),
    env_(env),
    optenv_(NULL),
    cmdline_(cmdline),
    bank_(bank)
{
    assert(parser && env && cmdline);
    mgr_ = env_->get_term_manager();
    assert(mgr_);
    one_ = mgr_->make_number(1);
    zero_ = mgr_->make_number(0);
    true_ = mgr_->make_true();
    false_ = mgr_->make_false();
    optenv_ = dynamic_cast<opt::OptEnvironment*>(env);
}

FlatZincConstraints::~FlatZincConstraints()
{
    parser_ = NULL;
    env_ = NULL;
    optenv_ = NULL;
    cmdline_ = NULL;
    mgr_ = NULL;
    one_ = NULL;
    zero_ = NULL;
    true_ = NULL;
    false_ = NULL;
}

//-----------------------------------------------------------------------------
// Constraint Functions
//-----------------------------------------------------------------------------

Term FlatZincConstraints::array_bool_and(TermList &as, Term r)
{
    assert(r);
    assert(is_bool(r));

    Term ret = NULL;
    Term tgl = r;
    Term not_r = mgr_->make_not(r);
    for (TermList::const_iterator it = as.begin(),
            end = as.end(); it != end; it++) {
        assert(*it);
        assert(is_bool(*it));

        Term tlc = mgr_->make_or(not_r, *it);
        ret = (ret ? mgr_->make_and(ret, tlc) : tlc);
        tgl = mgr_->make_or(tgl, mgr_->make_not(*it));
    }
    ret = (ret ? mgr_->make_and(ret, tgl) : tgl);
    return ret;
}

Term FlatZincConstraints::array_element(Term b, TermList &as, Term c)
{
    assert(b && c);
    assert(is_int(b));
    Term ret = NULL;
    if (200 < as.size()) {
        Term lower = NULL;
        Term upper = NULL;
        if (cmdline_->fzn_bv_integers()) {
            lower = fzn_make_sbv_number(mgr_, 1);
            upper = fzn_make_sbv_number(mgr_, as.size());
            ret = mgr_->make_and(
                        fzn_make_bv_sle(mgr_, lower, b),
                        fzn_make_bv_sle(mgr_, b, upper)
                    );
        } else {
            lower = one_;
            upper = mgr_->make_number((int)as.size());
            ret = mgr_->make_and(
                        mgr_->make_leq(lower, b),
                        mgr_->make_leq(b, upper)
                    );
        }
    } else {
        Term big_or = false_;
        for (size_t i = 1; i <= as.size(); ++i) {
            if (cmdline_->fzn_bv_integers()) {
                Term idx = fzn_make_sbv_number(mgr_, i);
                big_or = mgr_->make_or(big_or,
                         fzn_make_bv_equal(mgr_, b, idx));
            } else {
                Term idx = mgr_->make_number(i);
                big_or = mgr_->make_or(big_or,
                         mgr_->make_equal(b, idx));
            }
        }
        ret = big_or;
    }
    Term (TermManager:: *func)(Term, Term) =
        &TermManager::make_equal;
    if (mgr_->is_bool_type(c->get_type())) {
        func = &TermManager::make_iff;
    }
    bool is_bv = mgr_->is_bv_type(c, NULL);
    size_t i = 1;
    for (TermList::const_iterator it = as.begin(),
            end = as.end(); it != end; it++, i++) {
        assert(*it);
        assert(are_compatible_types(*it, c));
        Term tor = NULL;
        if (is_bv) {
            assert(cmdline_->fzn_bv_integers());
            tor = fzn_make_bv_equal(mgr_, *it, c);
        } else {
            tor = (mgr_->*func)(*it, c);
        }
        if (cmdline_->fzn_bv_integers()) {
            Term idx = fzn_make_sbv_number(mgr_, Number(i));
            tor = mgr_->make_or(tor,
                  mgr_->make_not(fzn_make_bv_equal(mgr_, b, idx)));
        } else {
            Term idx = mgr_->make_number(i);
            tor = mgr_->make_or(tor,
                  mgr_->make_not(mgr_->make_equal(b, idx)));
        }
        ret = mgr_->make_and(ret, tor);
    }
    return ret;
}

Term FlatZincConstraints::array_bool_or(TermList &as, Term r)
{
    assert(r);
    assert(is_bool(r));
    Term ret = true_;
    if (mgr_->is_true(r->get_symbol())) {
        ret = false_;
        for (TermList::const_iterator it = as.begin(),
                end = as.end(); it != end; it++) {
            assert(*it);
            assert(is_bool(*it));
            ret = mgr_->make_or(ret, *it);
        }
    } else if (mgr_->is_false(r->get_symbol())) {
        for (TermList::const_iterator it = as.begin(),
                end = as.end(); it != end; it++) {
            assert(*it);
            assert(is_bool(*it));
            ret = mgr_->make_and(ret, mgr_->make_not(*it));
        }
    } else {
        Term tgl = mgr_->make_not(r);
        for (TermList::const_iterator it = as.begin(),
                end = as.end(); it != end; it++) {
            assert(*it);
            assert(is_bool(*it));
            Term tlc = mgr_->make_or(r, mgr_->make_not(*it));
            ret = mgr_->make_and(ret, tlc);
            tgl = mgr_->make_or(tgl, *it);
        }
        ret = mgr_->make_and(ret, tgl);
    }
    return ret;
}

Term FlatZincConstraints::array_bool_xor(TermList &as)
{
    Term ret = NULL;
    Term a = *(as.begin());
    Term not_a = (a ? mgr_->make_not(a) : NULL);
    for (TermList::const_iterator it = as.begin()+1, la = as.begin()+2,
            end = as.end(); it != end; it++, la++) {
        assert(*it);
        assert(is_bool(*it));
        Term tlc = NULL;
        Term b = *it;
        Term not_b = mgr_->make_not(b);
        if (la != end) {
            Term c = bank_->make_private_term(mgr_->get_bool_type());
            Term not_c = mgr_->make_not(c);
            tlc = mgr_->make_or(not_a, mgr_->make_or(not_b, not_c));
            tlc = mgr_->make_and(tlc,
                  mgr_->make_or(a, mgr_->make_or(b, not_c)));
            tlc = mgr_->make_and(tlc,
                  mgr_->make_or(a, mgr_->make_or(not_b, c)));
            tlc = mgr_->make_and(tlc,
                  mgr_->make_or(not_a, mgr_->make_or(b, c)));
            a = c;
            not_a = not_c;
        } else {
            tlc = mgr_->make_or(a, b);
            tlc = mgr_->make_and(tlc, mgr_->make_or(not_a, not_b));
        }
        ret = (ret ? mgr_->make_and(ret, tlc) : tlc);
    }
    if (!ret) {
        if (a) {
            return a;
        } else {
            parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                << "model inconsistency detected before search");
            return false_;
        }
    }
    return ret;
}

Term FlatZincConstraints::bool2int(Term a, Term b)
{
    assert(a && b);
    assert(is_bool(a));
    assert(is_int(b));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        Term zero = fzn_make_sbv_number(mgr_, 0);
        Term one = fzn_make_sbv_number(mgr_, 1);
        ret = mgr_->make_or(a, fzn_make_bv_equal(mgr_, b, zero));
        ret = mgr_->make_and(ret, mgr_->make_or(mgr_->make_not(a),
                             fzn_make_bv_equal(mgr_, one, b)));
    } else {
        Term eqzero = mgr_->make_leq(b, zero_);
        Term eqone = mgr_->make_leq(one_, b);
        ret = mgr_->make_or(mgr_->make_not(eqzero), mgr_->make_not(eqone));
        ret = mgr_->make_and(ret, mgr_->make_or(a, eqzero));
        ret = mgr_->make_and(ret, mgr_->make_or(mgr_->make_not(a), eqone));
        // NOTE(PT): lower-upper bounds *must* be enforced, `b` may not
        //           have been declared with a 0/1 domain
        ret = mgr_->make_and(ret, mgr_->make_leq(zero_, b));
        ret = mgr_->make_and(ret, mgr_->make_leq(b, one_));
    }
    return ret;
}

Term FlatZincConstraints::bool_clause(TermList &as, TermList &bs)
{
    Term ret = false_;
    for (TermList::const_iterator it = as.begin(),
            end = as.end(); it != end; it++) {
        assert(*it);
        assert(is_bool(*it));
        ret = (ret ? mgr_->make_or(ret, *it) : *it);
    }
    for (TermList::const_iterator it = bs.begin(),
            end = bs.end(); it != end; it++) {
        assert(*it);
        assert(is_bool(*it));
        Term not_it = mgr_->make_not(*it);
        ret = (ret ? mgr_->make_or(ret, not_it) : not_it);
    }
    if (!ret) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                << "model inconsistency detected before search");
        return false_;
    }
    return ret;
}

Term FlatZincConstraints::bool_eq(Term a, Term b)
{
    assert(a && b);
    assert(is_bool(a));
    assert(is_bool(b));
    return mgr_->make_iff(a, b);
}

Term FlatZincConstraints::bool_eq_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_bool(a));
    assert(is_bool(b));
    assert(is_bool(r));
    Term eq = mgr_->make_iff(a, b);
    Term ret = mgr_->make_iff(eq, r);
    return ret;
}

Term FlatZincConstraints::bool_le(Term a, Term b)
{
    assert(a && b);
    assert(is_bool(a));
    assert(is_bool(b));
    return mgr_->make_or(mgr_->make_not(a), b);
}

Term FlatZincConstraints::bool_le_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_bool(a));
    assert(is_bool(b));
    assert(is_bool(r));
    Term ret = mgr_->make_or(mgr_->make_not(r),
               mgr_->make_or(mgr_->make_not(a), b));
    ret = mgr_->make_and(ret, mgr_->make_or(r, a));
    ret = mgr_->make_and(ret, mgr_->make_or(r, mgr_->make_not(b)));
    return ret;
}

Term FlatZincConstraints::bool_lin_eq(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_int(c));
    Term ret = NULL;
    Term sum = make_bool_lin(as, bs, c);
    if (sum != NULL) {
        ret = mgr_->make_equal(c, sum);
    } else {
        parser_->raise(ParserInterface::error("predicate `bool_lin_eq' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var bool, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    //env_->assert_formula(ret);
    return ret;
}

Term FlatZincConstraints::bool_lin_le(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_int(c));
    Term ret = NULL;
    Term sum = make_bool_lin(as, bs, c);
    if (sum != NULL) {
        if (cmdline_->fzn_bv_integers()) {
            ret = fzn_make_bv_sle(mgr_, sum, c);
        } else {
            ret = mgr_->make_leq(sum, c);
        }
    } else {
        parser_->raise(ParserInterface::error("predicate `bool_lin_le' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var bool, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::bool_lt(Term a, Term b)
{
    assert(a && b);
    assert(is_bool(a));
    assert(is_bool(b));
    return mgr_->make_and(mgr_->make_not(a), b);
}

Term FlatZincConstraints::bool_lt_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_bool(a));
    assert(is_bool(b));
    assert(is_bool(r));
    Term not_r = mgr_->make_not(r);
    Term ret = mgr_->make_or(r,
               mgr_->make_or(a, mgr_->make_not(b)));
    ret = mgr_->make_and(ret,
          mgr_->make_or(not_r, mgr_->make_not(a)));
    ret = mgr_->make_and(ret,
          mgr_->make_or(not_r, b));
    return ret;
}

Term FlatZincConstraints::bool_not(Term a, Term b)
{
    assert(a && b);
    assert(is_bool(a));
    assert(is_bool(b));
    return mgr_->make_and(mgr_->make_or(mgr_->make_not(a),
                                        mgr_->make_not(b)),
                          mgr_->make_or(a, b));
}

Term FlatZincConstraints::bool_xor(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_bool(a));
    assert(is_bool(b));
    assert(is_bool(r));
    Term not_a = mgr_->make_not(a);
    Term not_b = mgr_->make_not(b);
    Term not_r = mgr_->make_not(r);
    Term ret = mgr_->make_or(not_r, mgr_->make_or(a, b));
    ret = mgr_->make_and(ret,
          mgr_->make_or(not_r, mgr_->make_or(not_a, not_b)));
    ret = mgr_->make_and(ret,
          mgr_->make_or(r, mgr_->make_or(a, not_b)));
    ret = mgr_->make_and(ret,
          mgr_->make_or(r, mgr_->make_or(not_a, b)));
    return ret;
}

Term FlatZincConstraints::float_abs(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    Term ret = NULL;
    Number v;
    if (mgr_->is_number(a->get_symbol(), &v)) {
        Term x = mgr_->make_number(abs(v));
        //env_->assert_formula(x);
        ret = mgr_->make_equal(x, b);
    } else {
        Term x =  mgr_->make_number(-1);
        Term minus_b = make_times(b,x);
        Term b_dom = mgr_->make_leq(zero_, b);
        Term a_dom = mgr_->make_and(
                mgr_->make_leq(minus_b, a),
                mgr_->make_leq(a, b)
            );
        Term a_val = mgr_->make_or(
                mgr_->make_leq(a,minus_b),
                mgr_->make_leq(b, a)
            );
        ret = mgr_->make_and(b_dom,
                mgr_->make_and(a_dom, a_val));
    }
    return ret;
}

Term FlatZincConstraints::float_div(Term a, Term b, Term c)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_float(c));
    Number n1, n2, n3;
    bool num1 = mgr_->is_number(a->get_symbol(), &n1);
    bool num2 = mgr_->is_number(b->get_symbol(), &n2);
    bool num3 = mgr_->is_number(c->get_symbol(), &n3);
    Term ret = NULL;

    if (num2 && n2 == 0) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                << "model inconsistency detected before search");
        return false_;
    }
    /* else: assert b != 0 */

    Term eq = mgr_->make_equal(c, mgr_->make_divide(a, b));
    Term nz = mgr_->make_not(mgr_->make_equal(zero_, b));
    ret = mgr_->make_and(eq, nz);
    return ret;
}

Term FlatZincConstraints::float_acos(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_asin(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_atan(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_cos(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_cosh(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_exp(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_ln(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_log2(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_log10(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_sqrt(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_sin(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_sinh(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_tan(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_tanh(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    parser_->raise(ParserInterface::error("unsupported"),
        FlatZincInterface::GENERIC_ERROR);
    return NULL;
}

Term FlatZincConstraints::float_eq(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    return mgr_->make_equal(a, b);
}

Term FlatZincConstraints::float_eq_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_bool(r));
    Term eq = mgr_->make_equal(a, b);
    Term ret = mgr_->make_or(mgr_->make_not(r), eq);
    ret = mgr_->make_and(ret, mgr_->make_or(r,
                              mgr_->make_not(eq)));
    return ret;
}

Term FlatZincConstraints::float_le(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    return mgr_->make_leq(a, b);
}

Term FlatZincConstraints::float_le_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_bool(r));
    Term leq = mgr_->make_leq(a, b);
    Term ret = mgr_->make_or(mgr_->make_not(r), leq);
    ret = mgr_->make_and(ret, mgr_->make_or(r,
                              mgr_->make_not(leq)));
    return ret;
}

Term FlatZincConstraints::float_lin_eq(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_float(c));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        ret = mgr_->make_equal(sum, c);
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_eq' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_float(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        Term eq = mgr_->make_equal(sum, c);
        ret = mgr_->make_or(mgr_->make_not(r), eq);
        ret = mgr_->make_and(ret, mgr_->make_or(r, mgr_->make_not(eq)));
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_eq_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lin_le(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_float(c));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        ret = mgr_->make_leq(sum, c);
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_le' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lin_le_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_float(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        Term leq = mgr_->make_leq(sum, c);
        ret = mgr_->make_or(mgr_->make_not(r), leq);
        ret = mgr_->make_and(ret, mgr_->make_or(r, mgr_->make_not(leq)));
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_le_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lin_lt(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_float(c));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        ret = mgr_->make_not(mgr_->make_leq(c, sum));
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_lt' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lin_lt_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_float(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        Term lei = mgr_->make_leq(c, sum);
        ret = mgr_->make_or(mgr_->make_not(r), mgr_->make_not(lei));
        ret = mgr_->make_and(ret, mgr_->make_or(r, lei));
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_lt_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lin_ne(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_float(c));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        ret = mgr_->make_not(mgr_->make_equal(sum, c));
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_ne' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_float(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_float_lin(as, bs, c);
    if (sum != NULL) {
        Term eq = mgr_->make_equal(sum, c);
        ret = mgr_->make_or(mgr_->make_not(r), mgr_->make_not(eq));
        ret = mgr_->make_and(ret, mgr_->make_or(r, eq));
    } else {
        parser_->raise(ParserInterface::error("predicate `float_lin_ne_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of float, array [int] of var float, float, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::float_lt(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    return mgr_->make_not(mgr_->make_leq(b, a));
}

Term FlatZincConstraints::float_lt_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_bool(r));
    Term lei = mgr_->make_leq(b, a);
    Term ret = mgr_->make_or(mgr_->make_not(r),
                             mgr_->make_not(lei));
    ret = mgr_->make_and(ret, mgr_->make_or(r, lei));
    return ret;
}

Term FlatZincConstraints::float_max(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_float(c));
    Term ret = NULL;
    Number num_a;
    Number num_b;
    if (mgr_->is_number(a->get_symbol(), &num_a)
            && mgr_->is_number(b->get_symbol(), &num_b)) {
        if (num_a < num_b) {
            ret = mgr_->make_equal(b, c);
        } else {
            ret = mgr_->make_equal(a, c);
        }
    } else {
        Term c_dom = mgr_->make_and(
                mgr_->make_leq(a, c),
                mgr_->make_leq(b, c)
            );
        Term c_val = mgr_->make_or(
                mgr_->make_leq(c, a),
                mgr_->make_leq(c, b)
            );
        ret = mgr_->make_and(c_dom, c_val);
    }
    return ret;
}

Term FlatZincConstraints::float_min(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_float(c));
    Term ret = NULL;
    Number num_a;
    Number num_b;
    if (mgr_->is_number(a->get_symbol(), &num_a)
            && mgr_->is_number(b->get_symbol(), &num_b)) {
        if (num_a < num_b) {
            ret = mgr_->make_equal(a, c);
        } else {
            ret = mgr_->make_equal(b, c);
        }
    } else {
        Term c_dom = mgr_->make_and(
                mgr_->make_leq(c, a),
                mgr_->make_leq(c, b)
            );
        Term c_val = mgr_->make_or(
                mgr_->make_leq(a, c),
                mgr_->make_leq(b, c)
            );
        ret = mgr_->make_and(c_dom, c_val);
    }
    return ret;
}

Term FlatZincConstraints::float_ne(Term a, Term b)
{
    assert(a && b);
    assert(is_float(a));
    assert(is_float(b));
    return mgr_->make_not(mgr_->make_equal(b, a));
}

Term FlatZincConstraints::float_ne_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_bool(r));
    Term eq = mgr_->make_equal(b, a);
    Term ret = mgr_->make_or(mgr_->make_not(r),
                             mgr_->make_not(eq));
    ret = mgr_->make_and(ret, mgr_->make_or(r, eq));
    return ret;
}

Term FlatZincConstraints::float_plus(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_float(c));
    return mgr_->make_equal(c, mgr_->make_plus(a, b));
}

Term FlatZincConstraints::float_times(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_float(a));
    assert(is_float(b));
    assert(is_float(c));
    // NOTE: this may create a non-linear constraint
    Term ret = mgr_->make_equal(c, make_times(a, b));
    return ret;
}

Term FlatZincConstraints::int_abs(Term a, Term b)
{
    assert(a && b);
    assert(is_int(a));
    assert(is_int(b));
    Term ret = NULL;
    //std::cout<<cmdline_->fzn_bv_integers()<<std::endl;
    if (cmdline_->fzn_bv_integers()) {
        Number v;
        if (mgr_->is_number(mgr_->make_int_from_sbv(a)->get_symbol(), &v)) {
            Term abs_v = fzn_make_sbv_number(mgr_, abs(v));
            ret = fzn_make_bv_equal(mgr_, abs_v, b);
        } else {
            Term minus_b = mgr_->make_bv_neg(mgr_->make_bv_sign_extend(1, b));
            Term ext_a = mgr_->make_bv_sign_extend(1, a);
            Term bvzero = fzn_make_sbv_number(mgr_, 0);
            Term b_dom = fzn_make_bv_sle(mgr_, bvzero, b);
            Term a_dom = mgr_->make_and(
                         fzn_make_bv_sle(mgr_, minus_b, ext_a),
                         fzn_make_bv_sle(mgr_, a, b));
            Term a_val = mgr_->make_or(
                         fzn_make_bv_sle(mgr_, ext_a, minus_b),
                         fzn_make_bv_sle(mgr_, b, a));
            ret = mgr_->make_and(b_dom,
                  mgr_->make_and(a_dom, a_val));

        }
    } else {
        ret = float_abs(a, b);
    }
    return ret;
}

Term FlatZincConstraints::int_div(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_int(c));

    Number n1, n2, n3;
    bool num1 = mgr_->is_number(a->get_symbol(), &n1);
    bool num2 = mgr_->is_number(b->get_symbol(), &n2);
    bool num3 = mgr_->is_number(c->get_symbol(), &n3);
    Term ret = NULL;

    if (num2 && n2 == 0) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                << "model inconsistency detected before search");
        return false_;
    }
    /* else: assert b != 0 */

    if (num1 && num2) {
        Number frac = n1 / n2;
        Term tmp = mgr_->make_number(frac);
        assert(tmp);
        if (frac.is_integer()) {
            ret = mgr_->make_equal(c, mgr_->make_number(frac));
        } else if (sgn(frac) >= 0) {
            ret = mgr_->make_equal(c, mgr_->make_number(frac.floor()));
        } else {
            Number tmp = frac + 1;
            ret = mgr_->make_equal(c, mgr_->make_number(tmp.floor()));
        }
    } else if (num2 && num3) {
        if (n3 == 0) {
            Term lower = NULL;
            Term upper = NULL;
            if (sgn(n2) < 0) {
                lower = b;
                upper = mgr_->make_number(-1 * n2);
            } else {
                lower = mgr_->make_number(-1 * n2);
                upper = b;
            }
            ret = mgr_->make_and(
                mgr_->make_not(mgr_->make_leq(a, lower)),
                mgr_->make_not(mgr_->make_leq(upper, a))
            );
        } else {
            Term lower = mgr_->make_times(b, c);
            Term upper = NULL;
            if (sgn(n2) == sgn(n3)) {
                upper = mgr_->make_number((n2 * n3) + abs(n2));
            } else {
                upper = mgr_->make_number((n2 * n3) - abs(n2));
            }
            ret = mgr_->make_and(
                mgr_->make_leq(lower, a),
                mgr_->make_not(mgr_->make_leq(upper, a))
            );
        }
    } else if (num1 && num3) {
        if (n3 == 0) {
            Term lower = NULL;
            Term upper = NULL;
            if (sgn(n1) < 0) {
                lower = mgr_->make_number(-1 * n1);
                upper = a;
            } else {
                lower = a;
                upper = mgr_->make_number(-1 * n1);
            }
            ret = mgr_->make_or(
                mgr_->make_not(mgr_->make_leq(b, lower)),
                mgr_->make_not(mgr_->make_leq(upper, b))
            );
        } else {
            Number v = abs(n1) / (abs(n3) + 1);
            Number lower = v.floor() + 1;
            v = abs(n1) / abs(n3);
            Number upper = v.floor();
            if (sgn(n1) != sgn(n3)) {
                Number tmp = lower;
                lower = -1 * upper;
                upper = -1 * tmp;
            }
            ret = mgr_->make_and(
                mgr_->make_leq(mgr_->make_number(lower), b),
                mgr_->make_leq(b, mgr_->make_number(upper))
            );
        }
    } else if (num2) {
        Term c_dist = bank_->make_private_term(mgr_->get_integer_type());
        Term q_dist = bank_->make_private_term(mgr_->get_rational_type());
        Term q = make_times(mgr_->make_number(n2.inv()), a);

        Term cs1 = float_abs(c, c_dist);
        Term cs2 = float_abs(q, q_dist);
        Term cs3 = mgr_->make_leq(c_dist, q_dist);
        Term cs4 = mgr_->make_and(
                mgr_->make_leq(mgr_->make_floor(q), c),
                mgr_->make_leq(c, mgr_->make_plus(one_, mgr_->make_floor(q))));
        Term cs5 = mgr_->make_not(mgr_->make_leq(
                        mgr_->make_plus(one_, q), c));
        Term cs6 = mgr_->make_or(
                mgr_->make_not(mgr_->make_leq(c, mgr_->make_floor(q))),
                mgr_->make_not(mgr_->make_leq(mgr_->make_plus(one_,
                               mgr_->make_floor(q)), c)));

        ret = mgr_->make_and(cs1,
                mgr_->make_and(cs2,
                    mgr_->make_and(cs3,
                        mgr_->make_and(cs4,
                            mgr_->make_and(cs5, cs6)))));
    } else {
        parser_->raise(ParserInterface::error("predicate `int_div' "
              "supported only when at least two arguments "
              "are constants or `b' is constant"),
              FlatZincInterface::GENERIC_ERROR);
    }

    return ret;
}


Term FlatZincConstraints::int_eq(Term a, Term b)
{
    assert(a && b);
    assert(is_int(a));
    assert(is_int(b));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        ret = fzn_make_bv_equal(mgr_, a, b);
    } else {
        ret = mgr_->make_equal(a, b);
    }
    return ret;
}

Term FlatZincConstraints::int_eq_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_bool(r));
    Term eq = NULL;
    if (cmdline_->fzn_bv_integers()) {
        eq = fzn_make_bv_equal(mgr_, a, b);
    } else {
        eq = mgr_->make_equal(a, b);
    }
    Term ret = mgr_->make_and(mgr_->make_or(mgr_->make_not(r), eq),
                              mgr_->make_or(r, mgr_->make_not(eq)));
    return ret;
}

Term FlatZincConstraints::int_le(Term a, Term b)
{
    assert(a && b);
    assert(is_int(a));
    assert(is_int(b));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        ret = fzn_make_bv_sle(mgr_, a, b);
    } else {
        ret = mgr_->make_leq(a, b);
    }
    return ret;
}

Term FlatZincConstraints::int_le_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_bool(r));
    Term leq = NULL;
    if (cmdline_->fzn_bv_integers()) {
        leq = fzn_make_bv_sle(mgr_, a, b);
    } else {
        leq = mgr_->make_leq(a, b);
    }
    Term ret = mgr_->make_and(mgr_->make_or(mgr_->make_not(r), leq),
                              mgr_->make_or(r, mgr_->make_not(leq)));
    return ret;
}

Term FlatZincConstraints::int_lin_eq(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_int(c));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        if (cmdline_->fzn_bv_integers()) {
            ret = fzn_make_bv_equal(mgr_, sum, c);
        } else {
            ret = mgr_->make_equal(sum, c);
        }
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_eq' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lin_eq_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_int(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        Term eq = NULL;
        if (cmdline_->fzn_bv_integers()) {
            eq = fzn_make_bv_equal(mgr_, sum, c);
        } else {
            eq = mgr_->make_equal(sum, c);
        }
        ret = mgr_->make_and(mgr_->make_or(mgr_->make_not(r), eq),
                             mgr_->make_or(r, mgr_->make_not(eq)));
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_eq_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lin_le(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_int(c));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        if (cmdline_->fzn_bv_integers()) {
            ret = fzn_make_bv_sle(mgr_, sum, c);
        } else {
            ret = mgr_->make_leq(sum, c);
        }
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_le' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lin_le_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_int(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        Term leq = NULL;
        if (cmdline_->fzn_bv_integers()) {
            leq = fzn_make_bv_sle(mgr_, sum, c);
        } else {
            leq = mgr_->make_leq(sum, c);
        }
        ret = mgr_->make_and(mgr_->make_or(mgr_->make_not(r), leq),
                             mgr_->make_or(r, mgr_->make_not(leq)));
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_le_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lin_lt(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_int(c));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        if (cmdline_->fzn_bv_integers()) {
            ret = fzn_make_bv_slt(mgr_, sum, c);
        } else {
            ret = mgr_->make_not(mgr_->make_leq(c, sum));
        }
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_lt' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lin_lt_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_int(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        Term lt = NULL;
        if (cmdline_->fzn_bv_integers()) {
            lt = fzn_make_bv_slt(mgr_, sum, c);
        } else {
            lt = mgr_->make_not(mgr_->make_leq(c, sum));
        }
        ret = mgr_->make_and(mgr_->make_or(mgr_->make_not(r), lt),
                             mgr_->make_or(r, mgr_->make_not(lt)));
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_lt_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lin_ne(TermList &as, TermList &bs, Term c)
{
    assert(c);
    assert(is_int(c));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        if (cmdline_->fzn_bv_integers()) {
            ret = mgr_->make_not(fzn_make_bv_equal(mgr_, sum, c));
        } else {
            ret = mgr_->make_not(mgr_->make_equal(sum, c));
        }
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_ne' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lin_ne_reif(TermList &as, TermList &bs, Term c, Term r)
{
    assert(c && r);
    assert(is_int(c));
    assert(is_bool(r));
    Term ret = NULL;
    Term sum = make_int_lin(as, bs, c);
    if (sum != NULL) {
        Term eq = NULL;
        if (cmdline_->fzn_bv_integers()) {
            eq = fzn_make_bv_equal(mgr_, sum, c);
        } else {
            eq = mgr_->make_equal(sum, c);
        }
        ret = mgr_->make_or(mgr_->make_not(r), mgr_->make_not(eq));
        ret = mgr_->make_and(ret, mgr_->make_or(r, eq));
    } else {
        parser_->raise(ParserInterface::error("predicate `int_lin_ne_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array [int] of int, array [int] of var int, int, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    return ret;
}

Term FlatZincConstraints::int_lt(Term a, Term b)
{
    assert(a && b);
    assert(is_int(a));
    assert(is_int(b));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        ret = fzn_make_bv_slt(mgr_, a, b);
    } else {
        ret = mgr_->make_not(mgr_->make_leq(b, a));
    }
    return ret;
}

Term FlatZincConstraints::int_lt_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_bool(r));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        ret = mgr_->make_or(mgr_->make_not(r),
                            fzn_make_bv_slt(mgr_, a, b));
        ret = mgr_->make_and(ret,
              mgr_->make_or(r, fzn_make_bv_sle(mgr_, b, a)));
    } else {
        Term lei = mgr_->make_leq(b, a);
        ret = mgr_->make_or(mgr_->make_not(r),
                            mgr_->make_not(lei));
        ret = mgr_->make_and(ret, mgr_->make_or(r, lei));
    }
    return ret;
}

Term FlatZincConstraints::int_max(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_int(c));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        Number num_a;
        Number num_b;
        if (mgr_->is_number(mgr_->make_int_from_sbv(a)->get_symbol(), &num_a)
                && mgr_->is_number(mgr_->make_int_from_sbv(b)->get_symbol(), &num_b)) {
            
            if (num_a < num_b) {
                ret = fzn_make_bv_equal(mgr_, b, c);
            } else {
                ret = fzn_make_bv_equal(mgr_, a, c);
            }
        } else {
            Term c_dom = mgr_->make_and(
                    fzn_make_bv_sle(mgr_, a, c),
                    fzn_make_bv_sle(mgr_, b, c)
                );
            Term c_val = mgr_->make_or(
                    fzn_make_bv_sle(mgr_, c, a),
                    fzn_make_bv_sle(mgr_, c, b)
                );
            ret = mgr_->make_and(c_dom, c_val);
        }
    } else {
        Number num_a;
        Number num_b;
        if (mgr_->is_number(a->get_symbol(), &num_a)
                && mgr_->is_number(b->get_symbol(), &num_b)) {
            if (num_a < num_b) {
                ret = mgr_->make_equal(b, c);
            } else {
                ret = mgr_->make_equal(a, c);
            }
        } else {
            Term c_dom = mgr_->make_and(
                    mgr_->make_leq(a, c),
                    mgr_->make_leq(b, c)
                );
            Term c_val = mgr_->make_or(
                    mgr_->make_leq(c, a),
                    mgr_->make_leq(c, b)
                );
            ret = mgr_->make_and(c_dom, c_val);
        }
    }
    return ret;
}

Term FlatZincConstraints::int_min(Term a, Term b, Term c)
{
     assert(a && b && c);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_int(c));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        Number num_a;
        Number num_b;
        if (mgr_->is_number(mgr_->make_int_from_sbv(a)->get_symbol(), &num_a)
                && mgr_->is_number(mgr_->make_int_from_sbv(b)->get_symbol(), &num_b)) {
            if (num_a < num_b) {
                ret = fzn_make_bv_equal(mgr_, a, c);
            } else {
                ret = fzn_make_bv_equal(mgr_, b, c);
            }
        } else {
            Term c_dom = mgr_->make_and(
                    fzn_make_bv_sle(mgr_, c, a),
                    fzn_make_bv_sle(mgr_, c, b)
                );
            Term c_val = mgr_->make_or(
                    fzn_make_bv_sle(mgr_, a, c),
                    fzn_make_bv_sle(mgr_, b, c)
                );
            ret = mgr_->make_and(c_dom, c_val);
        }
    } else {
        Number num_a;
        Number num_b;
        if (mgr_->is_number(a->get_symbol(), &num_a)
                && mgr_->is_number(b->get_symbol(), &num_b)) {
            if (num_a < num_b) {
                ret = mgr_->make_equal(a, c);
            } else {
                ret = mgr_->make_equal(b, c);
            }
        } else {
            Term c_dom = mgr_->make_and(
                    mgr_->make_leq(c, a),
                    mgr_->make_leq(c, b)
                );
            Term c_val = mgr_->make_or(
                    mgr_->make_leq(a, c),
                    mgr_->make_leq(b, c)
                );
            ret = mgr_->make_and(c_dom, c_val);
        }
    }
    return ret;
}

Term FlatZincConstraints::int_mod(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_int(c));

    Number n1, n2, n3;
    bool num1 = mgr_->is_number(a->get_symbol(), &n1);
    bool num2 = mgr_->is_number(b->get_symbol(), &n2);
    bool num3 = mgr_->is_number(c->get_symbol(), &n3);
    Term ret = NULL;

    if (num2 && n2 == 0) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                << "model inconsistency detected before search");
        return false_;
    }
    /* else: assert b != 0 */

    if (num1 && num2) {
        Number q = abs(n1) / abs(n2);
        q = abs(n1) - (q.floor() * abs(n2));
        if (sgn(n1) < 0) {
            q = -q;
        }
        ret = mgr_->make_equal(c, mgr_->make_number(q));
    } else if (num2 && num3) {
        if (n3 <= - abs(n2) || abs(n2) <= n3) {
            parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                    << "model inconsistency detected before search");
            return false_;
        } else {
            Term x = bank_->make_private_term(mgr_->get_integer_type());
            if (sgn(n3) > 0) {
                ret = mgr_->make_leq(zero_, x);
            } else if (sgn(n3) < 0) {
                ret = mgr_->make_leq(x, zero_);
            }
            Term cs = mgr_->make_equal(a,
                        mgr_->make_plus(c,
                            mgr_->make_times(x, b)));
            ret = (ret ? mgr_->make_and(ret, cs) : cs);
        }
    } else if (num1 && num3) {
        if (sgn(n1) != sgn(n3)) {
            parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                    << "model inconsistency detected before search");
            return false_;
        } else if (abs(n1) < abs(n3)) {
            parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                    << "model inconsistency detected before search");
            return false_;
        } else if (n1 == n3) {
            ret = mgr_->make_or(
                mgr_->make_not(mgr_->make_leq(
                    mgr_->make_number(-1 * abs(n1)), b
                )),
                mgr_->make_not(mgr_->make_leq(b, mgr_->make_number(abs(n1))
                ))
            );
        } else {
            parser_->raise(ParserInterface::error("predicate `int_mod' "
                  "supported only when `b' is constant or special cases"),
                  FlatZincInterface::GENERIC_ERROR);
            return false_;
        }
    } else if (num2) {
        Term x = bank_->make_private_term(mgr_->get_integer_type());
        Term div = int_div(a, b, x);
        ret = mgr_->make_and(div,
                mgr_->make_equal(c,
                    mgr_->make_plus(a,
                        mgr_->make_times(x,
                            mgr_->make_number(-1 * n2)
                        )
                    )
                )
            );
    } else {
        parser_->raise(ParserInterface::error("predicate `int_mod' "
              "supported only when `b' is constant or special cases"),
              FlatZincInterface::GENERIC_ERROR);
        return false_;
    }

    return ret;
}

Term FlatZincConstraints::int_ne(Term a, Term b)
{
    assert(a && b);
    assert(is_int(a));
    assert(is_int(b));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        ret = mgr_->make_not(fzn_make_bv_equal(mgr_, a, b));
    } else {
        ret  = mgr_->make_not(mgr_->make_equal(a, b));
    }
    return ret;
}

Term FlatZincConstraints::int_ne_reif(Term a, Term b, Term r)
{
    assert(a && b && r);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_bool(r));
    Term eq = NULL;
    if (cmdline_->fzn_bv_integers()) {
        eq = fzn_make_bv_equal(mgr_, b, a);
    } else {
        eq = mgr_->make_equal(b, a);
    }
    Term ret = mgr_->make_or(mgr_->make_not(r),
                             mgr_->make_not(eq));
    ret = mgr_->make_and(ret, mgr_->make_or(r, eq));
    return ret;
}

Term FlatZincConstraints::int_plus(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_int(c));
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        ret = fzn_make_bv_equal(mgr_, c,
              fzn_make_bv_add(mgr_, a, b));
    } else {
        ret = mgr_->make_equal(c, mgr_->make_plus(a, b));
    }
    return ret;
}

Term FlatZincConstraints::int_times(Term a, Term b, Term c)
{
    assert(a && b && c);
    assert(is_int(a));
    assert(is_int(b));
    assert(is_int(c));
    Term ret = NULL;
    Number n;
    if (cmdline_->fzn_bv_integers()) {
        ret = fzn_make_bv_equal(mgr_, c,
              fzn_make_bv_mul(mgr_, a, b));
    } else {
        bool a_is_num = mgr_->is_number(a->get_symbol(),&n);
        bool b_is_num = mgr_->is_number(b->get_symbol(),&n);

        if (a_is_num || b_is_num) {
            return mgr_->make_equal(c, mgr_->make_times(a, b));
        } else {
            Term pbvar;
            if (bank_->is_pseudoboolean(a, pbvar)) {
                return mgr_->make_equal(c, mgr_->make_term_ite(pbvar, b, zero_));
            } else if (bank_->is_pseudoboolean(b, pbvar)) {
                return mgr_->make_equal(c, mgr_->make_term_ite(pbvar, a, zero_));
            } else {
                // non-linear product
                return make_linearized_times(a, b, c);
            }
        }
    }
    return ret;
}

Term FlatZincConstraints::int2float(Term a, Term b)
{
    assert(a && b);
    assert(is_int(a));
    assert(is_float(b));
    if (cmdline_->fzn_bv_integers()) {
        a = mgr_->make_int_from_sbv(a);
    }
    Term ret = mgr_->make_equal(a, b);
    return ret;
}

Term FlatZincConstraints::array_set_element(Term b, FznSetListSharedPtr as, FznSetSharedPtr c)
{
    assert(b && c);
    assert(is_int(b));
    Term ret = NULL;
    if (200 < as->size()) {
        Term lower = NULL;
        Term upper = NULL;
        if (cmdline_->fzn_bv_integers()) {
            lower = fzn_make_sbv_number(mgr_, 1);
            upper = fzn_make_sbv_number(mgr_, as->size());
            ret = mgr_->make_and(
                        fzn_make_bv_sle(mgr_, lower, b),
                        fzn_make_bv_sle(mgr_, b, upper)
                  );
        } else {
            lower = one_;
            upper = mgr_->make_number((int)as->size());
            ret = mgr_->make_and(
                        mgr_->make_leq(lower, b),
                        mgr_->make_leq(b, upper)
                  );
        }
    } else {
        Term big_or = false_;
        for (size_t i = 1; i <= as->size(); ++i) {
            if (cmdline_->fzn_bv_integers()) {
                Term idx = fzn_make_sbv_number(mgr_, i);
                big_or = mgr_->make_or(big_or,
                         fzn_make_bv_equal(mgr_, b, idx));
            } else {
                Term idx = mgr_->make_number(i);
                big_or = mgr_->make_or(big_or,
                         mgr_->make_equal(b, idx));
            }
        }
        ret = big_or;
    }
    size_t i = 1;
    for (FznSetList::const_iterator it = as->begin(),
            end = as->end(); it != end; it++, i++) {
        assert(*it);
        Term tor = set_eq(*it, c);
        if (cmdline_->fzn_bv_integers()) {
            Term idx = fzn_make_sbv_number(mgr_, Number(i));
            tor = mgr_->make_or(tor,
                  mgr_->make_not(fzn_make_bv_equal(mgr_, b, idx)));
        } else {
            Term idx = mgr_->make_number(i);
            tor = mgr_->make_or(tor,
                  mgr_->make_not(mgr_->make_equal(b, idx)));
        }
        ret = mgr_->make_and(ret, tor);
    }
    return ret;
}

Term FlatZincConstraints::set_card(FznSetSharedPtr a, Term b)
{
    assert(a && b);
    assert(is_int(b));
    const NumIntervalSet &aset = a->get_domain();
    if (a->is_set_literal()) {
        Term ret = NULL;
        if (cmdline_->fzn_bv_integers()) {
            Term v = fzn_make_sbv_number(mgr_, Number(aset.set_card()));
            ret = fzn_make_bv_equal(mgr_, b, v);
        } else {
            Term v = mgr_->make_number(aset.set_card());
            ret = mgr_->make_equal(b, v);
        }
        return ret;
    } else {
        if (aset.is_empty()) {
            Term ret = NULL;
            if (cmdline_->fzn_bv_integers()) {
                ret = fzn_make_bv_equal(mgr_, b,
                      fzn_make_sbv_number(mgr_, 0));
            } else {
                ret = mgr_->make_equal(b, zero_);
            }
            return ret;
        } else {
            
            TermList blist;
            size_t set_card = 0;
            for (NumIntervalSet::value_iterator it = aset.value_begin(),
                    end = aset.value_end(); it != end; ++it) {
                Term apar = set_make_el(a, *it);
                blist.push_back(mgr_->make_not(apar));
                set_card++;
            }
                        
            Term pbterm = bank_->make_private_pbsum(blist, one_);
            Term ret = NULL;
            if (cmdline_->fzn_bv_integers()) {
                size_t width = 0;
                bool ok = mgr_->is_bv_type(b, &width);
                assert(ok);
                Term bvpbterm = mgr_->make_int_to_bv(width, mgr_->make_floor(pbterm));
                Term card = fzn_make_sbv_number(mgr_, Number(set_card), width);
                Term zero = fzn_make_sbv_number(mgr_, 0, width);

                ret = fzn_make_bv_sle(mgr_, b, card);
                ret = mgr_->make_and(ret, fzn_make_bv_sle(mgr_, bvpbterm, card));
                ret = mgr_->make_and(ret, fzn_make_bv_sle(mgr_, zero, b));
                ret = mgr_->make_and(ret, fzn_make_bv_sle(mgr_, zero, bvpbterm));
                ret = mgr_->make_and(ret, fzn_make_bv_equal(mgr_, b, bvpbterm));
            } else {
                ret = mgr_->make_leq(b, mgr_->make_number(set_card));
                ret = mgr_->make_and(ret, mgr_->make_leq(pbterm,
                                          mgr_->make_number(set_card)));
                ret = mgr_->make_and(ret, mgr_->make_leq(zero_, b));
                ret = mgr_->make_and(ret, mgr_->make_leq(zero_, pbterm));
                ret = mgr_->make_and(ret, mgr_->make_equal(b, pbterm));
            }
            
            return ret;
        }
    }
}

Term FlatZincConstraints::set_diff(FznSetSharedPtr a, FznSetSharedPtr b, FznSetSharedPtr c)
{
    assert(a && b && c);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();
    const NumIntervalSet &cset = c->get_domain();

    NumIntervalSet fsetc = cset.set_diff(aset);
    Term ret = set_make_and_false(fsetc, c);

    NumIntervalSet fseta = aset.set_diff(bset).set_diff(cset);
    Term tmp = set_make_and_false(fseta, a);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet aimplb = aset.set_intersect(bset).set_diff(cset);
    tmp = set_make_imply(aimplb, a, b);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet aeqc = cset.set_intersect(aset.set_diff(bset));
    tmp = set_make_equal(aeqc, a, c);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet set = aset.set_intersect(bset).set_intersect(cset);
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
        Term apar = set_make_el(a, *it);
        Term bpar = set_make_el(b, *it);
        Term cpar = set_make_el(c, *it);
        Term not_cpar = set_make_not_el(c, *it);
        Term cl = mgr_->make_and(
                  mgr_->make_and(
            // !a v b v c
            mgr_->make_or(mgr_->make_not(apar),
               mgr_->make_or(bpar, cpar)),
            // !c v !b
            mgr_->make_or(not_cpar, mgr_->make_not(bpar))),
            // !c v a
            mgr_->make_or(not_cpar, apar));
        ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }
    return (ret ? ret : true_);
}

Term FlatZincConstraints::set_eq(FznSetSharedPtr a, FznSetSharedPtr b)
{
    assert(a && b);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();

    if (aset.is_empty() && bset.is_empty()) {
        return true_;
    }

    NumIntervalSet fset1 = aset.set_diff(bset);
    Term ret = set_make_and_false(fset1, a);

    NumIntervalSet fset2 = bset.set_diff(aset);
    Term tmp = set_make_and_false(fset2, b);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet set = aset.set_intersect(bset);
    tmp = set_make_equal(set, a, b);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    return (ret ? ret : true_);
}

Term FlatZincConstraints:: FlatZincConstraints::set_eq_reif(FznSetSharedPtr a,
        FznSetSharedPtr b, Term c)
{
    assert(a && b && c);
    assert(is_bool(c));
    Term ret = set_eq(a, b);
    return mgr_->make_iff(ret, c);
}

Term FlatZincConstraints::set_in(Term a, FznSetSharedPtr b, bool internal)
{
    assert(a && b);
    assert(is_int(a));
    const NumIntervalSet &bset = b->get_domain();

    if (bset.is_empty()) {
        if (!internal) {
            parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                    << "model inconsistency detected before search");
        }
        return false_;
    }

    /* bounds for LAR-propagation on a */
    Term ret = NULL;
    Term flower = NULL;
    Term lupper = NULL;
    for (NumIntervalSet::subset_iterator it = bset.subset_begin(),
            end = bset.subset_end(); it != end; ++it) {
        Term tlower;
        Term tupper;
        Term cl = NULL;
            tlower = mgr_->make_number(it->lower());
            tupper = mgr_->make_number(it->upper());
            cl = mgr_->make_and(
                      mgr_->make_leq(tlower, a),
                      mgr_->make_leq(a, tupper));
        ret = (ret ? mgr_->make_or(ret, cl) : cl);
        if (!flower) {
            flower = tlower;
        }
        lupper = tupper;
    }

    if (ret && bset.is_fragmented()) { // cut
            ret = mgr_->make_and(ret,
                  mgr_->make_and(
                  mgr_->make_leq(flower, a),
                  mgr_->make_leq(a, lupper)));
    }

    /* actual set-in encoding */
    for (NumIntervalSet::value_iterator it = bset.value_begin(),
            end = bset.value_end(); it != end; ++it) {
        Term bpar = set_make_el(b, *it);
        Term eq = NULL;
            Term v = mgr_->make_number(*it);
            eq = mgr_->make_equal(a, v);
        Term cl = mgr_->make_or(mgr_->make_not(eq), bpar);
        if (cl != true_) {
            ret = (ret ? mgr_->make_and(ret, cl) : cl);
        }
    }
    return ret;
}

Term FlatZincConstraints::set_in_reif(Term a,
        FznSetSharedPtr b, Term c)
{
    assert(a && b && c);
    assert(is_int(a));
    assert(is_bool(c));
    Term ret = set_in(a, b, true);
    return mgr_->make_iff(ret, c);
}

Term FlatZincConstraints::set_intersect(FznSetSharedPtr a,
        FznSetSharedPtr b, FznSetSharedPtr c)
{
    assert(a && b && c);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();
    const NumIntervalSet &cset = c->get_domain();

    NumIntervalSet a_i_b = aset.set_intersect(bset);

    NumIntervalSet fsetc = cset.set_diff(a_i_b);
    Term ret = set_make_and_false(fsetc, c);

    NumIntervalSet fsetab = a_i_b.set_diff(cset);
    for (NumIntervalSet::value_iterator it = fsetab.value_begin(),
            end = fsetab.value_end(); it != end; ++it) {
        Term not_apar = set_make_not_el(a, *it);
        Term not_bpar = set_make_not_el(b, *it);
        Term cl = mgr_->make_or(not_apar, not_bpar);
        ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }

    NumIntervalSet set = aset.set_intersect(bset).set_intersect(cset);
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
        Term apar = set_make_el(a, *it);
        Term bpar = set_make_el(b, *it);
        Term cpar = set_make_el(c, *it);
        Term not_apar = set_make_not_el(a, *it);
        Term not_bpar = set_make_not_el(b, *it);
        Term not_cpar = set_make_not_el(c, *it);
        Term cl = mgr_->make_and(
                  mgr_->make_and(
            // !a v !b v c
            mgr_->make_or(not_apar, mgr_->make_or(not_bpar, cpar)),
            // !c v b
            mgr_->make_or(not_cpar, bpar)),
            // !c v a
            mgr_->make_or(not_cpar, apar));
        ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }
    return (ret ? ret : true_);
}


Term FlatZincConstraints::set_le(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    return set_le_lt_base(a, b, NULL, false);
}

Term FlatZincConstraints::set_lt(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    return set_le_lt_base(a, b, NULL, true);
}

Term FlatZincConstraints::set_ne(FznSetSharedPtr a,
        FznSetSharedPtr b, bool internal)
{
    assert(a && b);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();

    if (aset.is_empty() && bset.is_empty()) {
        if (!internal) {
            parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
                    << "model inconsistency detected before search");
        }
        return false_;
    }

    NumIntervalSet fset1 = aset.set_diff(bset);
    Term ret = set_make_or_true(fset1, a);

    NumIntervalSet fset2 = bset.set_diff(aset);
    Term tmp = set_make_or_true(fset2, b);
    if (tmp) {
        ret = (ret ? mgr_->make_or(ret, tmp) : tmp);
    }

    NumIntervalSet set = aset.set_intersect(bset);
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
        Term apar = set_make_el(a, *it);
        Term bpar = set_make_el(b, *it);
        Term cl = mgr_->make_not(mgr_->make_iff(apar, bpar));
        ret = (ret ? mgr_->make_or(ret, cl) : cl);
    }
    return (ret ? ret : true_);
}

Term FlatZincConstraints::set_ne_reif(FznSetSharedPtr a,
        FznSetSharedPtr b, Term c)
{
    assert(a && b && c);
    assert(is_bool(c));
    Term ret = set_ne(a, b, true);
    return mgr_->make_iff(ret, c);
}

Term FlatZincConstraints::set_subseteq(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    assert(a && b);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();

    if (aset.is_empty()) {
        return true_;
    }

    NumIntervalSet fset = aset.set_diff(bset);
    Term ret = set_make_and_false(fset, a);

    NumIntervalSet set = aset.set_intersect(bset);
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
        Term not_apar = set_make_not_el(a, *it);
        Term bpar = set_make_el(b, *it);
        Term cl = mgr_->make_or(not_apar, bpar);
        ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }
    return (ret ? ret : true_);
}

Term FlatZincConstraints::set_subseteq_reif(
FznSetSharedPtr a,
        FznSetSharedPtr b, Term c)
{
    assert(a && b && c);
    assert(is_bool(c));
    Term ret = set_subseteq(a, b);
    return mgr_->make_iff(ret, c);
}

Term FlatZincConstraints::set_subsetneq(FznSetSharedPtr a,
        FznSetSharedPtr b)
{
    assert(a && b);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();

    if (aset.is_empty()) {
        return true_;
    }

    NumIntervalSet fset = aset.set_diff(bset);
    Term ret = set_make_and_false(fset, a);

    NumIntervalSet set = aset.set_intersect(bset);
    Term gcl = NULL;
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
        Term not_apar = set_make_not_el(a, *it);
        Term bpar = set_make_el(b, *it);
        // if an element is in A then it must be also in B
        Term cl = mgr_->make_or(not_apar, bpar);
        ret = (ret ? mgr_->make_and(ret, cl) : cl);
        // at least one element in B is not in A
        Term lcl = mgr_->make_or(not_apar, mgr_->make_not(bpar));
        gcl = (gcl ? mgr_->make_or(gcl, lcl) : lcl);
    }
    if (gcl && ret) {
        ret = mgr_->make_and(ret, gcl);
    }
    return (ret ? ret : true_);
}

Term FlatZincConstraints::set_subsetneq_reif(FznSetSharedPtr a,
        FznSetSharedPtr b, Term c)
{
    assert(a && b && c);
    assert(is_bool(c));
    Term ret = set_subsetneq(a, b);
    return mgr_->make_iff(ret, c);
}

Term FlatZincConstraints::set_symdiff(FznSetSharedPtr a,
        FznSetSharedPtr b, FznSetSharedPtr c)
{
    assert(a && b && c);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();
    const NumIntervalSet &cset = c->get_domain();

    NumIntervalSet fseta = aset.set_diff(bset.set_union(cset));
    Term ret = set_make_and_false(fseta, a);

    NumIntervalSet fsetb = bset.set_diff(aset.set_union(cset));
    Term tmp = set_make_and_false(fsetb, b);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet fsetc = cset.set_diff(aset.set_union(bset));
    tmp = set_make_and_false(fsetc, c);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet aic = cset.set_intersect(aset.set_diff(bset));
    tmp = set_make_imply(aic, a, c);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }


    NumIntervalSet bic = cset.set_intersect(bset.set_diff(aset));
    tmp = set_make_imply(bic, b, c);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet a_i_b = aset.set_intersect(bset);

    NumIntervalSet aeb = a_i_b.set_diff(cset);
    tmp = set_make_equal(aeb, a, b);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet set = a_i_b.set_intersect(cset);
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
        Term apar = set_make_el(a, *it);
        Term bpar = set_make_el(b, *it);
        Term cpar = set_make_el(c, *it);
        Term not_apar = set_make_not_el(a, *it);
        Term not_bpar = set_make_not_el(b, *it);
        Term not_cpar = set_make_not_el(c, *it);
        Term cl = mgr_->make_and(
                  mgr_->make_and(
                  mgr_->make_and(
            // !a v !b v !c
            mgr_->make_or(not_apar, mgr_->make_or(not_bpar, not_cpar)),
            // a v b v !c
            mgr_->make_or(apar, mgr_->make_or(bpar, not_cpar))),
            // !a v b v c
            mgr_->make_or(not_apar, mgr_->make_or(bpar, cpar))),
            // a v !b v c
            mgr_->make_or(apar, mgr_->make_or(not_bpar, cpar)));
        ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }
    return (ret ? ret : true_);
}

Term FlatZincConstraints::set_union(FznSetSharedPtr a,
        FznSetSharedPtr b, FznSetSharedPtr c)
{
    assert(a && b && c);
    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();
    const NumIntervalSet &cset = c->get_domain();

    NumIntervalSet fseta = aset.set_diff(cset);
    Term ret = set_make_and_false(fseta, a);

    NumIntervalSet fsetb = bset.set_diff(cset);
    Term tmp = set_make_and_false(fsetb, b);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet fsetc = cset.set_diff(aset.set_union(bset));
    tmp = set_make_and_false(fsetc, c);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet aec = cset.set_intersect(aset).set_diff(bset);
    tmp = set_make_equal(aec, a, c);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet bec = cset.set_intersect(bset).set_diff(aset);
    tmp = set_make_equal(bec, b, c);
    if (tmp) {
        ret = (ret ? mgr_->make_and(ret, tmp) : tmp);
    }

    NumIntervalSet set = aset.set_intersect(bset).set_intersect(cset);
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
        Term apar = set_make_el(a, *it);
        Term bpar = set_make_el(b, *it);
        Term cpar = set_make_el(c, *it);
        Term not_apar = set_make_not_el(a, *it);
        Term not_bpar = set_make_not_el(b, *it);
        Term not_cpar = set_make_not_el(c, *it);
        Term cl = mgr_->make_and(
                  mgr_->make_and(
            // a v b v !c
            mgr_->make_or(apar, mgr_->make_or(bpar, not_cpar)),
            // !a v c
            mgr_->make_or(not_apar, cpar)),
            // !b v c
            mgr_->make_or(not_bpar, cpar));
        ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }
    return (ret ? ret : true_);
}

//-----------------------------------------------------------------------------
// Private Help Functions
//-----------------------------------------------------------------------------

bool FlatZincConstraints::are_compatible_types(Term t1, Term t2) const
{
    assert(t1 && t2);
    if (is_bool(t1)) {
        return is_bool(t2);
    } else if (is_float(t1)) {
        return is_float(t2);
    } else {
        return is_int(t1) && is_int(t2);
    }
}

bool FlatZincConstraints::is_float(Term t) const
{
    assert(t);
    const DataType *tp = t->get_type();
    return mgr_->is_rational_type(tp) || mgr_->is_integer_type(tp);
}

bool FlatZincConstraints::is_int(Term t) const
{
    assert(t);
    const DataType *tp = t->get_type();
    return mgr_->is_integer_type(tp);
}

bool FlatZincConstraints::is_bool(Term t) const
{
    assert(t);
    const DataType *tp = t->get_type();
    return mgr_->is_bool_type(tp);
}

Term FlatZincConstraints::make_ite(Term a, Term b, Term c)
{
    
    if (mgr_->is_true(a->get_symbol())) {
        return b;
    } else if (mgr_->is_false(a->get_symbol())) {
        return c;
    } else {
        return mgr_->make_and(
               mgr_->make_or(mgr_->make_not(a), b),
               mgr_->make_or(a, c));
    }
}

Term FlatZincConstraints::make_times(Term a, Term b)
{
    Number n;
    if (cmdline_->fzn_bv_integers()
            && mgr_->is_bv_type(a, NULL)
            && mgr_->is_bv_type(b, NULL)) {
        return fzn_make_bv_mul(mgr_, a, b);
    }
    
    bool a_is_num = mgr_->is_number(a->get_symbol(),&n);
    bool b_is_num = mgr_->is_number(b->get_symbol(),&n);
    if (a_is_num || b_is_num) {
        return mgr_->make_times(a, b);
    } else {
        Term pbvar;
        if (bank_->is_pseudoboolean(a, pbvar)) {
            return mgr_->make_term_ite(pbvar, b, zero_);
        } else if (bank_->is_pseudoboolean(b, pbvar)) {
            return mgr_->make_term_ite(pbvar, a, zero_);
        } else {
            return mgr_->make_times(a, b);
        }
    }
}

Term FlatZincConstraints::make_linearized_times(Term a, Term b, Term c)
{
    Term ret;
    Number a_lower;
    Number b_lower;
    Number a_upper;
    Number b_upper;
    bool a_bounded = bank_->get_var_bounds(a, a_lower, a_upper);
    bool b_bounded = bank_->get_var_bounds(b, b_lower, b_upper);
    if (a_bounded && b_bounded) {
        Number a_delta = a_upper - a_lower;
        Number b_delta = b_upper - b_lower;
        if (a_delta <= b_delta) {
            ret = do_make_linearized_times(a, b, a_lower, a_upper, c);
        } else {
            ret = do_make_linearized_times(b, a, b_lower, b_upper, c);
        }
    } else if (a_bounded) {
        ret = do_make_linearized_times(a, b, a_lower, a_upper, c);
    } else if (b_bounded) {
        ret = do_make_linearized_times(b, a, b_lower, b_upper, c);
    } else {
        // non-linear encoding is the only option
        ret = mgr_->make_equal(c, mgr_->make_times(a, b));
    }
    return ret;
}

Term FlatZincConstraints::do_make_linearized_times(Term a, Term b, Number &a_lower, Number &a_upper, Term c)
{
    Term ret = true_;
    for (Number i = a_lower; i <= a_upper; i = i + Number(1)) {
        Term iv = mgr_->make_number(i);
        Term aeq = mgr_->make_equal(a, iv);
        ret = mgr_->make_and(ret,
              mgr_->make_or(mgr_->make_not(aeq),
                            mgr_->make_equal(c, make_times(iv, b))
              ));
    }
    return ret;
}

Term FlatZincConstraints::make_bool_lin(TermList &as, TermList &bs, Term c)
{
    Term ret = NULL;
    size_t width = 0;
    if (cmdline_->fzn_bv_integers()) {
        bool ok = mgr_->is_bv_type(c, &width);
        assert(ok);
    }
    if (0 == as.size() || 0 == bs.size()) {
        if (cmdline_->fzn_bv_integers()) {
            ret = fzn_make_sbv_number(mgr_, 0, width);
        } else {
            ret = zero_;
        }
    } else {
        if (cmdline_->fzn_bv_integers()) {
            fzn_make_bv_to_int(mgr_, as);
        }
        ret = bank_->make_private_pbsum(bs, as);
        if (cmdline_->fzn_bv_integers()) {
            ret = mgr_->make_int_to_bv(width, mgr_->make_floor(ret));
        }        
    }
    return ret;
}

Term FlatZincConstraints::make_float_lin(TermList &as, TermList &bs, Term c)
{
    Term ret = zero_;
        for (TermList::const_iterator itas = as.begin(), itbs = bs.begin(),
                asend = as.end(), bsend = bs.end(); itas != asend && itbs != bsend;
                itas++, itbs++) {
            assert(*itas && *itbs);
            if (!is_float(*itas) || !is_float(*itbs)) {
                ret = NULL;
                break;
            }
            Term prod = make_times(*itas, *itbs);
            ret = mgr_->make_plus(ret, prod);
        }
        return ret;
}

Term FlatZincConstraints::make_int_lin(TermList &as, TermList &bs, Term c)
{
    Term ret = NULL;
    if (cmdline_->fzn_bv_integers()) {
        if (0 == as.size() || 0 == bs.size()) {
            ret = fzn_make_sbv_number(mgr_, 0);
        } else {
            for (TermList::const_iterator itas = as.begin(), itbs = bs.begin(),
                    asend = as.end(), bsend = bs.end(); itas != asend && itbs != bsend;
                    itas++, itbs++) {
                assert(*itas && *itbs);
                if (!is_int(*itas) || !is_int(*itbs)) {
                    ret = NULL;
                    break;
                }
                Term prod = fzn_make_bv_mul(mgr_, *itas, *itbs);
                ret = (ret ? fzn_make_bv_add(mgr_, ret, prod) : prod);
            }
        }
    } else {
        ret = make_float_lin(as, bs, c);
    }
    return ret;
}

Term FlatZincConstraints::make_sum(TermList &terms)
{
    if (terms.size() == 0) {
        return zero_;
    } else {
        Term ret = terms[0];
        assert(ret);
        for (size_t i = 1; i < terms.size(); ++i) {
            assert(terms[i]);
            ret = mgr_->make_plus(ret, terms[i]);
        }
        return ret;
    }
}

Term FlatZincConstraints::set_make_and_true(const NumIntervalSet &set,
        FznSetSharedPtr a) const
{
    assert(a);
    Term ret = NULL;
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
         Term apar = set_make_el(a, *it);
         ret = (ret ? mgr_->make_and(ret, apar) : apar);
    }
    return ret;
}

Term FlatZincConstraints::set_make_and_false(const NumIntervalSet &set,
        FznSetSharedPtr a) const
{
    Term ret = NULL;
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
         Term not_apar = set_make_not_el(a, *it);
         ret = (ret ? mgr_->make_and(ret, not_apar) : not_apar);
    }
    return ret;
}

Term FlatZincConstraints::set_make_or_true(const NumIntervalSet &set,
        FznSetSharedPtr a) const
{
    Term ret = NULL;
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
         Term apar = set_make_el(a, *it);
         ret = (ret ? mgr_->make_or(ret, apar) : apar);
    }
    return ret;
}

Term FlatZincConstraints::set_make_or_false(const NumIntervalSet &set,
        FznSetSharedPtr a) const
{
    Term ret = NULL;
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
         Term not_apar = set_make_not_el(a, *it);
         ret = (ret ? mgr_->make_or(ret, not_apar) : not_apar);
    }
    return ret;
}

Term FlatZincConstraints::set_make_imply(const NumIntervalSet &set,
        FznSetSharedPtr a, FznSetSharedPtr b) const
{
    Term ret = NULL;
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
         Term not_apar = set_make_not_el(a, *it);
         Term bpar = set_make_el(b, *it);
         Term cl = mgr_->make_or(not_apar, bpar);
         ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }
    return ret;
}

Term FlatZincConstraints::set_make_equal(const NumIntervalSet &set,
        FznSetSharedPtr a, FznSetSharedPtr b)
{
    Term ret = NULL;
    for (NumIntervalSet::value_iterator it = set.value_begin(),
            end = set.value_end(); it != end; ++it) {
         Term apar = set_make_el(a, *it);
         Term bpar = set_make_el(b, *it);
         Term cl = mgr_->make_iff(apar, bpar);
         ret = (ret ? mgr_->make_and(ret, cl) : cl);
    }
    return ret;
}

Term FlatZincConstraints::set_make_el(FznSetSharedPtr a, Number val) const
{
    assert(a);
    if (a->domain_contains(val)) {
        if (a->is_set_literal()) {
            return true_;
        } else {
            return bank_->make_private_term(a->get_ident(), val,
                                            mgr_->get_bool_type());
        }
    } else {
        return false_;
    }
}

Term FlatZincConstraints::set_make_not_el(FznSetSharedPtr a, Number val) const
{
    assert(a);
    if (a->domain_contains(val)) {
        if (a->is_set_literal()) {
            return false_;
        } else {
            return mgr_->make_not(bank_->make_private_term(a->get_ident(), val,
                                                           mgr_->get_bool_type()));
        }
    } else {
        return true_;
    }
}

Term FlatZincConstraints::get_max_rear_set_els(FznSetSharedPtr b, Number i)
{
    assert(b);
    const NumIntervalSet &bset = b->get_domain();
    if (bset.is_empty()) {
        return false_;
    } else if(i > bset.upper()) {
        return false_;
    } else if(i < bset.lower()) {
        return get_max_rear_set_els(b, bset.lower());
    } else {
        return mgr_->make_or(set_make_el(b, i),
                             get_max_rear_set_els(b, i+1));
    }
}

Term FlatZincConstraints::set_le_lt_base(FznSetSharedPtr a,
        FznSetSharedPtr b, Term fValReif, bool fStrict)
{
    assert(a && b); // fValReif may be NULL

    const NumIntervalSet &aset = a->get_domain();
    const NumIntervalSet &bset = b->get_domain();

    bool aempty = (0 == aset.set_card());
    bool bempty = (0 == bset.set_card());

    Term ret = true_;
    if (aempty && bempty) {
        if (fValReif) {
            ret = mgr_->make_iff(fValReif, (fStrict ? false_ : true_));
        } else {
            ret = (fStrict ? false_ : true_);
        }
    } else if (!aempty && !bempty && aset.upper() < bset.lower() && !fStrict) {
        ret = (fValReif ? fValReif : true_);
    } else if (!aempty && !bempty && aset.lower() > bset.upper() && fStrict) {
        ret = (fValReif ? mgr_->make_not(fValReif) : false_);
    } else {
        const NumIntervalSet &udom = aset.set_union(bset);
        Term prev = (fValReif ? fValReif : true_);
        for(NumIntervalSet::const_value_iterator it = udom.value_begin(),
                iend = udom.value_end(); it != iend; ++it) {
            Term bxi = set_make_el(a, *it);
            Term byi = set_make_el(b, *it);
            Term mx = get_max_rear_set_els(a, *it + 1);
            Term my = get_max_rear_set_els(b, *it + 1);
            assert(bxi && byi && mx && my);
            Term cur = bank_->make_private_term(mgr_->get_bool_type());
            assert(cur);
            Term t1 = mgr_->make_and(mgr_->make_iff(bxi, byi), cur);
            Term t2 = mgr_->make_and(bool_lt(bxi, byi), mgr_->make_not(mx));
            Term t3 = mgr_->make_and(bool_lt(byi, bxi), my);
            assert(t1 && t2 && t3);
            Term tor = mgr_->make_or(t1,
                       mgr_->make_or(t2, t3));
            assert(tor);
            Term iff = mgr_->make_iff(prev, tor);
            assert(iff);
            ret = mgr_->make_and(ret, iff);
            prev = cur;
        }
        ret = mgr_->make_and(ret,
              mgr_->make_iff(prev, (fStrict ? false_ : true_)));
    }
    return ret ;
}

}} // namespace msat::opt
