// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../toplevel/flatzincbv.h"
#include "../utils/bvnumbers.h"

namespace msat {

namespace opt {

size_t fzn_get_sbv_size(int n)
{
    Number tmp(n);
    if (n < 0) {
        tmp = Number(-1 - n);
    }
    size_t ret = tmp.required_bits() + 1;
    return (ret > 1 ? ret : 2);
}

size_t fzn_get_sbv_size(const Number &n)
{
    Number tmp(n);
    if (n < Number(0)) {
        tmp = -n - Number(1);
    }
    size_t ret = tmp.required_bits() + 1;
    return (ret > 1 ? ret : 2);
}

Term fzn_make_sbv_number(
        TermManager *mgr,
        int n, size_t min)
{
    size_t width = fzn_get_sbv_size(n);
    if (width < min) width = min;

    Number tmp(n);
    if (n < 0) {
        tmp = BVNumber::twos_complement(tmp, width);
    }
    return mgr->make_bv_number(tmp, width);
}

Term fzn_make_sbv_number(
        TermManager *mgr,
        const Number &n, size_t min)
{
    size_t width = fzn_get_sbv_size(n);
    if (width < min) width = min;

    Number tmp(n);
    if (n < Number(0)) {
        tmp = BVNumber::twos_complement(n, width);
    }
    return mgr->make_bv_number(tmp, width);
}

Term fzn_make_bv_equal_bits(
        TermManager *mgr,
        Term a)
{
    size_t width_a = 0;
    bool ok;
    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);

    Term zero = fzn_make_sbv_number(mgr, 0, width_a);
    Term mone = fzn_make_sbv_number(mgr, -1, width_a);
    Term ret = mgr->get_true_term();
    return ret;
}

Term fzn_make_bv_equal(
        TermManager *mgr,
        Term a, Term b)
{
    size_t width_a = 0, width_b = 0;
    bool ok;
    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);
    ok = mgr->is_bv_type(b , &width_b);
    assert(ok);

    Term ret = NULL;
    Term op1 = NULL;
    Term op2 = NULL;
    if (width_a == width_b) {
        op1 = a;
        op2 = b;
        ret = mgr->make_true();
    } else if (width_a > width_b) {
        op1 = a;
        op2 = mgr->make_bv_sign_extend(width_a - width_b, b);
        ret = fzn_make_bv_equal_bits(mgr, mgr->make_bv_extract(width_a - 1, width_b - 1, op2));
    } else {
        op1 = mgr->make_bv_sign_extend(width_b - width_a, a);
        op2 = b;
        ret = fzn_make_bv_equal_bits(mgr, mgr->make_bv_extract(width_b - 1, width_a - 1, op1));
    }
    ret = mgr->make_and(ret,
          mgr->make_equal(op1, op2));
    return ret;
}

Term fzn_make_bv_sle(
        TermManager *mgr,
        Term a, Term b)
{
    size_t width_a = 0, width_b = 0;
    bool ok;
    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);
    ok = mgr->is_bv_type(b , &width_b);
    assert(ok);
    Term ret = NULL;
    Term op1 = NULL;
    Term op2 = NULL;
    if (width_a == width_b) {
        op1 = a;
        op2 = b;
        ret = mgr->make_true();
    } else if (width_a > width_b) {
        op1 = a;
        op2 = mgr->make_bv_sign_extend(width_a - width_b, b);
        ret = fzn_make_bv_equal_bits(mgr, mgr->make_bv_extract(width_a - 1, width_b - 1, op2));
    } else {
        op1 = mgr->make_bv_sign_extend(width_b - width_a, a);
        op2 = b;
        ret = fzn_make_bv_equal_bits(mgr, mgr->make_bv_extract(width_b - 1, width_a - 1, op1));
    }
    ret = mgr->make_and(ret,
          mgr->make_bv_sle(op1, op2));
    return ret;
    
}

Term fzn_make_bv_slt(
        TermManager *mgr,
        Term a, Term b)
{
    size_t width_a = 0, width_b = 0;
    bool ok;
    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);
    ok = mgr->is_bv_type(b , &width_b);
    assert(ok);

    Term ret = NULL;
    Term op1 = NULL;
    Term op2 = NULL;
    if (width_a == width_b) {
        op1 = a;
        op2 = b;
        ret = mgr->make_true();
    } else if (width_a > width_b) {
        op1 = a;
        op2 = mgr->make_bv_sign_extend(width_a - width_b, b);
        ret = fzn_make_bv_equal_bits(mgr, mgr->make_bv_extract(width_a - 1, width_b - 1, op2));
    } else {
        op1 = mgr->make_bv_sign_extend(width_b - width_a, a);
        op2 = b;
        ret = fzn_make_bv_equal_bits(mgr, mgr->make_bv_extract(width_b - 1, width_a - 1, op1));
    }
    ret = mgr->make_and(ret,
          mgr->make_bv_slt(op1, op2));
    return ret;
}

Term fzn_make_bv_add(
        TermManager *mgr,
        Term a, Term b)
{
    size_t width_a = 0, width_b = 0;
    bool ok;
    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);
    ok = mgr->is_bv_type(b , &width_b);
    assert(ok);
    size_t width = (width_a > width_b ? width_a : width_b) + 1;
    Term ret = mgr->make_bv_add(
               mgr->make_bv_sign_extend(width - width_a, a),
               mgr->make_bv_sign_extend(width - width_b, b));
    assert(ret);
    return ret;
}

Term fzn_make_bv_sub(
        TermManager *mgr,
        Term a, Term b)
{
    size_t width_a = 0, width_b = 0;
    bool ok;
    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);
    ok = mgr->is_bv_type(b , &width_b);
    assert(ok);

    size_t width = (width_a > width_b ? width_a : width_b) + 1;
    Term ret = mgr->make_bv_sub(
               mgr->make_bv_sign_extend(width - width_a, a),
               mgr->make_bv_sign_extend(width - width_b, b));
    assert(ret);
    return ret;
}

Term fzn_make_bv_mul(
        TermManager *mgr,
        Term a, Term b)
{
    size_t width_a = 0, width_b = 0;
    bool ok;

    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);
    ok = mgr->is_bv_type(b , &width_b);
    assert(ok);

    Term ret = mgr->make_bv_mul(
               mgr->make_bv_sign_extend(width_b, a),
               mgr->make_bv_sign_extend(width_a, b));
    assert(ret);
    return ret;
}

Term fzn_make_bv_sdiv(
        TermManager *mgr,
        Term a, Term b)
{
    size_t width_a = 0, width_b = 0;
    bool ok;
    ok = mgr->is_bv_type(a , &width_a);
    assert(ok);
    ok = mgr->is_bv_type(b , &width_b);
    assert(ok);

    size_t max = (width_a > width_b ? width_a : width_b);
    Term ret = mgr->make_bv_sdiv(
               mgr->make_bv_sign_extend(max - width_a, a),
               mgr->make_bv_sign_extend(max - width_b, b));
    assert(ret);
    return ret;
}

void fzn_make_bv_to_int(TermManager *mgr, TermList &as)
{
    for (size_t i = 0; i < as.size(); i++) {
        as[i] = mgr->make_int_from_sbv(as[i]);
    }
}


size_t get_sbv_size(Number &n1, Number &n2)
{
    size_t s1 = fzn_get_sbv_size(n1);
    size_t s2 = fzn_get_sbv_size(n2);
    return (s1 > s2 ? s1 : s2);
}

size_t get_sbv_size(TermManager *mgr, Term t1, Term t2)
{
    assert(mgr);
    assert(t1);
    assert(t2);
    Number n1;
    Number n2;
    bool ok = mgr->is_number(t1->get_symbol(), &n1);
    assert(ok);
    ok = mgr->is_number(t2->get_symbol(), &n2);
    assert(ok);
    size_t s1 = fzn_get_sbv_size(n1);
    size_t s2 = fzn_get_sbv_size(n2);
    return (s1 > s2 ? s1 : s2);
}

size_t get_sbv_size(NumFlatZincDomain *dom)
{
    assert(dom);
    assert(!dom->is_unbounded());
    Number low = dom->lower();
    Number upp = dom->upper();
    return get_sbv_size(low, upp);
}

bool extend_bv_width_to(TermManager *mgr, Term &t, size_t value)
{
    assert(mgr);
    size_t width = 0;
    bool ok = mgr->is_bv_type(t , &width);
    if (value >= width) {
        t = mgr->make_bv_sign_extend(value - width, t);
        return true;
    } else {
        return false;
    }
}

size_t make_same_bv_width(TermManager *mgr, Term &t1, Term &t2)
{
    assert(mgr);
    size_t w1 = 0, w2 = 0;
    mgr->is_bv_type(t1 , &w1);
    mgr->is_bv_type(t2 , &w2);
    size_t max = (w1 > w2 ? w1 : w2);
    t1 = mgr->make_bv_sign_extend(max - w1, t1);
    t2 = mgr->make_bv_sign_extend(max - w2, t2);
    return max;
}

size_t make_same_bv_width(TermManager *mgr, Term &t1, Term &t2, Term &t3)
{
    assert(mgr);
    size_t w1 = 0, w2 = 0, w3 = 0;
    mgr->is_bv_type(t1 , &w1);
    mgr->is_bv_type(t2 , &w2);
    mgr->is_bv_type(t3 , &w3);
    size_t max = (w2 > w3 ? (w1 > w2 ? w1 : w2)
                          : (w1 > w3 ? w1 : w3));
    t1 = mgr->make_bv_sign_extend(max - w1, t1);
    t2 = mgr->make_bv_sign_extend(max - w2, t2);
    t3 = mgr->make_bv_sign_extend(max - w3, t3);
    return max;
}

size_t make_same_bv_width(TermManager *mgr, Term &t1, Term &t2, Term &t3, Term &t4)
{
    assert(mgr);
    size_t w1 = 0, w2 = 0, w3 = 0, w4 = 0;
    mgr->is_bv_type(t1 , &w1);
    mgr->is_bv_type(t2 , &w2);
    mgr->is_bv_type(t3 , &w3);
    mgr->is_bv_type(t4 , &w4);
    size_t max = (w3 > w4 ? (w2 > w3 ? (w1 > w2 ? w1 : w2)
                                     : (w1 > w3 ? w1 : w3))
                          : (w2 > w4 ? (w1 > w2 ? w1 : w2)
                                     : (w1 > w4 ? w1 : w4)));
    t1 = mgr->make_bv_sign_extend(max - w1, t1);
    t2 = mgr->make_bv_sign_extend(max - w2, t2);
    t3 = mgr->make_bv_sign_extend(max - w3, t3);
    t4 = mgr->make_bv_sign_extend(max - w4, t4);
    return max;
}

size_t make_same_bv_width(TermManager *mgr, TermList &as, Term &c)
{
    assert(mgr);
    std::vector<size_t> was;
    size_t wc = 0, max = 0;
    mgr->is_bv_type(c , &wc);
    max = wc;
    was.reserve(as.size());
    for (size_t i = 0; i < as.size(); i++) {
        size_t width;
        mgr->is_bv_type(as[i] , &width);
        was.push_back(width);
        if (width > max) {
            max = width;
        }
    }
    c = mgr->make_bv_sign_extend(max - wc, c);
    for (size_t i = 0; i < as.size(); i++) {
        as[i] = mgr->make_bv_sign_extend(max - was[i], as[i]);
    }
    return max;
}

size_t make_same_bv_width(TermManager *mgr, TermList &as, TermList &bs, Term &c)
{
    assert(mgr);
    std::vector<size_t> was, wbs;
    size_t wc = 0, max = 0;
    mgr->is_bv_type(c , &wc);
    max = wc;
    was.reserve(as.size());
    for (size_t i = 0; i < as.size(); i++) {
        size_t width;
        mgr->is_bv_type(as[i] , &width);
        was.push_back(width);
        if (width > max) {
            max = width;
        }
    }
    wbs.reserve(bs.size());
    for (size_t i = 0; i < bs.size(); i++) {
        size_t width;
        mgr->is_bv_type(bs[i] , &width);
        wbs.push_back(width);
        if (width > max) {
            max = width;
        }
    }
    c = mgr->make_bv_sign_extend(max - wc, c);
    for (size_t i = 0; i < as.size(); i++) {
        as[i] = mgr->make_bv_sign_extend(max - was[i], as[i]);
    }
    for (size_t i = 0; i < bs.size(); i++) {
        bs[i] = mgr->make_bv_sign_extend(max - wbs[i], bs[i]);
    }
    return max;
}

}} // namespace
