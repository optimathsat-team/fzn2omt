// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#include "../toplevel/flatzincglconstraints.h"
#include "../api/optenvironment.h"

namespace msat {

namespace opt {

//-----------------------------------------------------------------------------
// Init/Deinit
//-----------------------------------------------------------------------------

FlatZincGlConstraints::FlatZincGlConstraints(FlatZincInterface *parser,
        Environment *env, CmdLine *cmdline,FlatZincBank *bank):
    FlatZincConstraints(parser, env, cmdline, bank)
{
    // nothing to do
}

FlatZincGlConstraints::~FlatZincGlConstraints()
{
    // nothing to do
}

//-----------------------------------------------------------------------------
// all_different
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::all_different(TermList &as)
{
    size_t width = 0;
    Term lower = NULL;
    Term upper = NULL;
    bool positive_domain = false;

    Term ret = true_;
    if (as.size() <= 1) {
        return ret;
    }
    Term (TermManager::* func)(Term, Term ) =
        &TermManager::make_equal;
    assert(as[0]);
    if (mgr_->is_bool_type(as[0]->get_type())) {
        func = &TermManager::make_iff;
    }
    for (TermList::const_iterator i = as.begin(), end = as.end();
             i != end; ++i) {
        Term a = *i;
        assert(a);
        for (TermList::const_iterator j = i+1; j != end; ++j) {
            Term b = *j;
            assert(b);
            Term eq = mgr_->make_not((mgr_->*func)(a, b));
            ret = mgr_->make_and(ret, eq);
        }
    }
    return ret;
}

Term FlatZincGlConstraints::all_different_except_0(TermList &as)
{
    size_t width = 0;
    Term lower = NULL;
    Term upper = NULL;
    bool positive_domain = false;

    Term ret = true_;
    Term zero = zero_;
    if (0 == as.size()) {
        return ret;
    }
    Term (TermManager::* func)(Term, Term ) =
        &TermManager::make_equal;
    assert(as[0]);
    if (mgr_->is_bool_type(as[0]->get_type())) {
        func = &TermManager::make_iff;
        zero = false_;
    }
    for (TermList::const_iterator i = as.begin(), end = as.end();
            i != end; ++i) {
        Term a = *i;
        assert(a);
        Term aez = (mgr_->*func)(a, zero);
        for (TermList::const_iterator j = i+1; j != end; ++j) {
            Term b = *j;
            assert(b);
            Term bez = (mgr_->*func)(b, zero);
            Term eq = mgr_->make_not((mgr_->*func)(a, b));
            Term cl = mgr_->make_or(eq,
                          mgr_->make_or(aez, bez));
            ret = mgr_->make_and(ret, cl);
        }
    }
    return ret;
}

Term FlatZincGlConstraints::all_different(FznSetListSharedPtr as)
{
    Term ret = true_;
    for (FznSetList::const_iterator it = as->begin(), end = as->end();
            it != end; ++it) {
        assert(*it);
        for (FznSetList::const_iterator jt = it+1; jt != end; ++jt) {
            assert(*jt);
            Term eq = set_ne(*it, *jt, true);
            ret = mgr_->make_and(ret, eq);
        }
    }
    return ret;
}

//-----------------------------------------------------------------------------
// disjoint
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::disjoint(FznSetSharedPtr s1,
        FznSetSharedPtr s2)
{
    assert(s1 && s2);
    const NumIntervalSet &aset = s1->get_domain();
    const NumIntervalSet &bset = s2->get_domain();

    NumIntervalSet a_i_b = aset.set_intersect(bset);
    Term ret = true_;
    for (NumIntervalSet::value_iterator it = a_i_b.value_begin(),
            end = a_i_b.value_end(); it != end; ++it) {
        Term apar = set_make_el(s1, *it);
        Term bpar = set_make_el(s2, *it);
        ret = mgr_->make_and(ret,
                mgr_->make_or(
                        mgr_->make_not(apar),
                        mgr_->make_not(bpar)
                    )
                );
    }
    return ret;
}

Term FlatZincGlConstraints::all_disjoint(FznSetListSharedPtr as)
{
    Term ret = true_;
    for (FznSetList::const_iterator it = as->begin(), end = as->end();
            it != end; ++it) {
        assert(*it);
        for (FznSetList::const_iterator jt = it+1; jt != end; ++jt) {
            assert(*jt);
            Term dis = disjoint(*it, *jt);
            ret = mgr_->make_and(ret, dis);
        }
    }
    return ret;
}

//-----------------------------------------------------------------------------
// disjunctive
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::disjunctive(TermList &s,
        TermList &d)
{
    Term ret = true_;
    if (s.size() != d.size()) {
        parser_->raise(ParserInterface::error("predicate `disjunctive' ")
            << "the array arguments must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }

    for (size_t j = 0; j < d.size(); ++j) {
        assert(d[j] && s[j]);
        assert(is_int(d[j]));
        assert(is_int(s[j]));
        Term bound = mgr_->make_leq(zero_, d[j]);
        ret = mgr_->make_and(ret, bound);
        for (size_t i = 0; i < j; ++i) {
            assert(d[i] && s[i]);
            Term t1 = mgr_->make_equal(d[i], zero_);
            Term t2 = mgr_->make_equal(d[j], zero_);
            Term t3 = mgr_->make_leq(
                            mgr_->make_plus(s[i], d[i]),
                            s[j]
                        );
            Term t4 = mgr_->make_leq(
                            mgr_->make_plus(s[j], d[j]),
                            s[i]
                        );
            Term big_or = mgr_->make_or(t1,
                          mgr_->make_or(t2,
                          mgr_->make_or(t3, t4)));
            ret = mgr_->make_and(ret, big_or);
        }
    }
    return ret;
}

Term FlatZincGlConstraints::disjunctive_strict(
        TermList &s, TermList &d)
{
    Term ret = true_;
    if (s.size() != d.size()) {
        parser_->raise(ParserInterface::error("predicate `disjunctive_strict' ")
            << "the array arguments must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }
    for (size_t j = 0; j < d.size(); ++j) {
        assert(d[j] && s[j]);
        assert(is_int(d[j]));
        assert(is_int(s[j]));
        Term bound = mgr_->make_leq(zero_, d[j]);
        ret = mgr_->make_and(ret, bound);
        for (size_t i = 0; i < j; ++i) {
            assert(d[i] && s[i]);
            Term t1 = mgr_->make_leq(
                            mgr_->make_plus(s[i], d[i]),
                            s[j]
                        );
            Term t2 = mgr_->make_leq(
                            mgr_->make_plus(s[j], d[j]),
                            s[i]
                        );
            Term big_or = mgr_->make_or(t1, t2);
            ret = mgr_->make_and(ret, big_or);
        }
    }
    return ret;
}

//-----------------------------------------------------------------------------
// all_equal
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::all_equal(TermList &x)
{
    Term ret = true_;
    if (x.size() <= 1) {
        return ret;
    }
    Term (TermManager::* func)(Term, Term ) =
        &TermManager::make_equal;
    assert(x[0]);
    if (mgr_->is_bool_type(x[0]->get_type())) {
        func = &TermManager::make_iff;
    }
    for (TermList::const_iterator i = x.begin(), end = x.end();
             i != end; ++i) {
        Term a = *i;
        assert(a);
        for (TermList::const_iterator j = i+1; j != end; ++j) {
            Term b = *j;
            assert(b);
            Term eq =(mgr_->*func)(a, b);
            ret = mgr_->make_and(ret, eq);
        }
    }
    return ret;
}

Term FlatZincGlConstraints::all_equal(FznSetListSharedPtr as)
{
    Term ret = true_;
    for (FznSetList::const_iterator it = as->begin(), end = as->end();
            it != end; ++it) {
        assert(*it);
        for (FznSetList::const_iterator jt = it+1; jt != end; ++jt) {
            assert(*jt);
            Term eq = set_eq(*it, *jt);
            ret = mgr_->make_and(ret, eq);
        }
    }
    return ret;
}

//-----------------------------------------------------------------------------
// among
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::among(Term n, TermList &x, FznSetSharedPtr v)
{
    assert(n && v);
    assert(is_int(n));
    Term ret = NULL;
    TermList clauses;
    clauses.reserve(x.size());
    for (TermList::const_iterator it = x.begin(), iend = x.end();
            it != iend; ++it) {
        assert(*it);
        assert(is_int(*it));
        Term nis = mgr_->make_not(set_in(*it, v, true));
        clauses.push_back(nis);
    }
    
    Term pbterm = bank_->make_private_pbsum(clauses, one_);
    ret = mgr_->make_equal(n, pbterm);
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, pbterm),
                mgr_->make_leq(pbterm, mgr_->make_number(x.size()))
          ));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, n),
                mgr_->make_leq(n, mgr_->make_number(x.size()))
          ));
    return ret;
}

//-----------------------------------------------------------------------------
// array_max/min
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::array_max(Term m, TermList &x)
{
    assert(m);
    assert(is_float(m));

    Term ret = false_;
    size_t len = x.size();
    if (0 == len) {
        parser_->raise(ParserInterface::error("predicate `array_T_maximum' ")
            << "undefined constraint over empty array",
            FlatZincInterface::EVALUATION_ERROR);
    } else if (1 == len) {
        assert(x[0]);
        assert(is_float(x[0]));
        ret = mgr_->make_equal(m, x[0]);
    } else {
        Term big_and = true_;
        Term big_or  = false_;
        for (TermList::const_iterator it = x.begin(),
                iend = x.end(); it != iend; ++it) {
            assert(*it);
            assert(is_float(*it));
            big_and = mgr_->make_and(big_and,
                            mgr_->make_leq(*it, m)
                        );
            big_or = mgr_->make_or(big_or,
                            mgr_->make_leq(m, *it)
                        );
        }
        ret = mgr_->make_and(big_and, big_or);
    }

    return ret;
}

Term FlatZincGlConstraints::array_min(Term m, TermList &x)
{
    assert(m);
    assert(is_float(m));

    Term ret = false_;
    size_t len = x.size();
    if (0 == len) {
        parser_->raise(ParserInterface::error("predicate `array_T_minimum' ")
            << "undefined constraint over empty array",
            FlatZincInterface::EVALUATION_ERROR);
    } else if (1 == len) {
        assert(x[0]);
        assert(is_float(x[0]));
        ret = mgr_->make_equal(m, x[0]);
    } else {
        Term big_and = true_;
        Term big_or  = false_;
        for (TermList::const_iterator it = x.begin(),
                iend = x.end(); it != iend; ++it) {
            assert(*it);
            assert(is_float(*it));
            big_and = mgr_->make_and(big_and,
                            mgr_->make_leq(m, *it)
                        );
            big_or = mgr_->make_or(big_or,
                            mgr_->make_leq(*it, m)
                        );
        }
        ret = mgr_->make_and(big_and, big_or);
    }

    return ret;
}

//-----------------------------------------------------------------------------
// maximum/minimum_arg
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::maximum_arg(TermList &x,
        Term i, const NumInterval &xdom)
{
    assert(i);
    assert(is_int(i));

    if (x.size() == 0) {
        parser_->raise(ParserInterface::error("predicate `maximum_arg_T' ")
            << "undefined constraint over empty array",
            FlatZincInterface::EVALUATION_ERROR);
    }

    assert(x[0]);
    Term max = bank_->make_private_term(x[0]->get_type());
    assert(max);
    Term ret = array_max(max, x);

    Term prev = false_;
    Term lb = mgr_->make_number(xdom.lower());
    for (size_t jdx = 0; jdx < x.size(); ++jdx) {
        assert(x[jdx]);
        assert(is_float(x[jdx]));
        Term eq1 = mgr_->make_equal(x[jdx], max);
        Term eq2 = mgr_->make_equal(i,
                   mgr_->make_plus(mgr_->make_number(jdx), lb));
        Term impl = mgr_->make_or(prev,
                    mgr_->make_or(mgr_->make_not(eq1), eq2));
        ret = mgr_->make_and(ret, impl);
        prev = mgr_->make_or(prev, eq1);
    }

    return ret;
}

Term FlatZincGlConstraints::minimum_arg(TermList &x,
        Term i, const NumInterval &xdom)
{
    assert(i);
    assert(is_int(i));

    if (x.size() == 0) {
        parser_->raise(ParserInterface::error("predicate `minimum_arg_T' ")
            << "undefined constraint over empty array",
            FlatZincInterface::EVALUATION_ERROR);
    }

    assert(x[0]);
    Term min = bank_->make_private_term(x[0]->get_type());
    assert(min);
    Term ret = array_min(min, x);

    Term prev = false_;
    Term lb = mgr_->make_number(xdom.lower());
    for (size_t jdx = 0; jdx < x.size(); ++jdx) {
        assert(x[jdx]);
        assert(is_float(x[jdx]));
        Term eq1 = mgr_->make_equal(x[jdx], min);
        Term eq2 = mgr_->make_equal(i,
                   mgr_->make_plus(mgr_->make_number(jdx), lb));
        Term impl = mgr_->make_or(prev,
                    mgr_->make_or(mgr_->make_not(eq1), eq2));
        ret = mgr_->make_and(ret, impl);
        prev = mgr_->make_or(prev, eq1);
    }

    return ret;
}

//-----------------------------------------------------------------------------
// at_least/exactly/at_most
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::at_least_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v)
{
    assert(n && v);
    assert(is_int(n));
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_leq(n, count);
    ret = mgr_->make_and(ret, mgr_->make_leq(n, mgr_->make_number(x->size())));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x->size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::exactly_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v)
{
    assert(n && v);
    assert(is_int(n));
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_equal(count, n);
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, n),
                mgr_->make_leq(n, mgr_->make_number(x->size()))
          ));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x->size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::at_most_set(Term n, FznSetListSharedPtr x, FznSetSharedPtr v)
{
    assert(n && v);
    assert(is_int(n));
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_leq(count, n);
    ret = mgr_->make_and(ret, mgr_->make_leq(zero_, n));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x->size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::at_most_1(FznSetListSharedPtr s)
{
    Term ret = true_;
    TermList clauses;
    for (FznSetList::const_iterator it = s->begin(), end = s->end();
            it != end; ++it) {
        assert(*it);
        for (FznSetList::const_iterator jt = it+1; jt != end; ++jt) {
            assert(*jt);
            const NumIntervalSet &aset = (*it)->get_domain();
            const NumIntervalSet &bset = (*jt)->get_domain();
            NumIntervalSet aib = aset.set_intersect(bset);

            if (aib.is_empty()) {
                continue;
            }

            clauses.clear();
            for (NumIntervalSet::value_iterator v = aib.value_begin(),
                    vend = aib.value_end(); v != vend; ++v) {
                Term not_apar = set_make_not_el(*it, *v);
                Term not_bpar = set_make_not_el(*jt, *v);
                Term cl = mgr_->make_or(not_apar, not_bpar);
                clauses.push_back(cl);
            }
            
            Term pbterm = bank_->make_private_pbsum(clauses, one_);

            Term eq = mgr_->make_and(
                        mgr_->make_leq(zero_, pbterm),
                        mgr_->make_leq(pbterm, one_)
                      );

            ret = mgr_->make_and(ret, eq);
        }
    }
    return ret;
}

//-----------------------------------------------------------------------------
// bin_packing
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::bin_packing(Term c,
        TermList &bin, TermList &w)
{
    assert(c);
    assert(is_int(c));

    Number zero(0);
    Term ret = true_;

    if (bin.size() != w.size()) {
        parser_->raise(ParserInterface::error("predicate `bin_packing' ")
            << "the bin and weight arrays must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }

    Number v;
    bool v_is_num = mgr_->is_number(c->get_symbol(), &v);
    assert(v_is_num);
    if (v < zero) {
        parser_->raise(ParserInterface::error("predicate `bin_packing' ")
            << "capacity must be non-negative",
            FlatZincInterface::GENERIC_ERROR);
    }

    for (TermList::const_iterator it = w.begin(),
            iend = w.end(); it != iend; ++it) {
        assert(*it);
        assert(is_int(*it));
        Number v;
        bool v_is_num = mgr_->is_number((*it)->get_symbol(), &v);
        assert(v_is_num);
        if (v < zero) {
            parser_->raise(ParserInterface::error("predicate `bin_packing' ")
                << "the weights must be non-negative",
                FlatZincInterface::GENERIC_ERROR);
        }
    }

    Term upper = mgr_->make_number(bin.size());
    for (TermList::const_iterator it = bin.begin(),
            iend = bin.end(); it != iend; ++it) {
        assert(*it);
        assert(is_int(*it));
        Term t = mgr_->make_and(
                mgr_->make_leq(one_, *it),
                mgr_->make_leq(*it, upper)
            );
        ret = mgr_->make_and(ret, t);
    }

    TermList clauses;
    for (size_t b = 0; b < bin.size(); ++b) {
        Term bterm = mgr_->make_number(b+1);
        assert(bterm);
        clauses.clear();
        clauses.reserve(bin.size());
        for (size_t i = 0; i < bin.size(); ++i) {
            Term neq = mgr_->make_not(mgr_->make_equal(bterm, bin[i]));
            clauses.push_back(neq);
        }
        
        Term pbterm = bank_->make_private_pbsum(clauses, w);
        Term tbounds = mgr_->make_and(
                mgr_->make_leq(zero_, pbterm),
                mgr_->make_leq(pbterm, c)
            );
        ret = mgr_->make_and(ret, tbounds);
    }

    return ret;
}

Term FlatZincGlConstraints::bin_packing_capa(TermList &c,
        TermList &bin, TermList &w, const NumInterval &cdom)
{
    Number zero(0);
    Term ret = true_;

    if (bin.size() != w.size()) {
        parser_->raise(ParserInterface::error("predicate `bin_packing_capa' ")
            << "the bin and weight arrays must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }

    for (TermList::const_iterator it = w.begin(),
            iend = w.end(); it != iend; ++it) {
        assert(*it);
        assert(is_int(*it));
        Number v;
        bool v_is_num = mgr_->is_number((*it)->get_symbol(), &v);
        assert(v_is_num);
        if (v < zero) {
            parser_->raise(ParserInterface::error("predicate `bin_packing_capa' ")
                << "the weights must be non-negative",
                FlatZincInterface::GENERIC_ERROR);
        }
    }

    Term clower = mgr_->make_number(cdom.lower());
    Term cupper = mgr_->make_number(cdom.upper());

    for (TermList::const_iterator it = bin.begin(),
            iend = bin.end(); it != iend; ++it) {
        assert(*it);
        assert(is_int(*it));
        Term t = mgr_->make_and(
                mgr_->make_leq(clower, *it),
                mgr_->make_leq(*it, cupper)
            );
        ret = mgr_->make_and(ret, t);
    }

    TermList clauses;
    for (size_t idx = 0; idx < c.size(); ++idx) {
        Term bterm = mgr_->make_plus(mgr_->make_number(idx), clower);
        assert(bterm && c[idx]);
        assert(is_int(c[idx]));
        Number v;
        bool v_is_num = mgr_->is_number(c[idx]->get_symbol(), &v);
        assert(v_is_num);
        if (v < zero) {
            parser_->raise(ParserInterface::error("predicate `bin_packing_capa' ")
                << "the capacities must be non-negative",
                FlatZincInterface::GENERIC_ERROR);
        }
        clauses.clear();
        clauses.reserve(bin.size());
        for (size_t i = 0; i < bin.size(); ++i) {
            Term neq = mgr_->make_not(mgr_->make_equal(bterm, bin[i]));
            clauses.push_back(neq);
        }
        
        Term pbterm = bank_->make_private_pbsum(clauses, w);
        Term tbounds = mgr_->make_and(
                mgr_->make_leq(zero_, pbterm),
                mgr_->make_leq(pbterm, c[idx])
            );
        ret = mgr_->make_and(ret, tbounds);
    }

    return ret;
}

Term FlatZincGlConstraints::bin_packing_load(TermList &load,
        TermList &bin, TermList &w, const NumInterval &loaddom)
{
    Number zero(0);
    Number tot_weight(0);

    if (bin.size() != w.size()) {
        parser_->raise(ParserInterface::error("predicate `bin_packing_load' ")
            << "the bin and weight arrays must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }

    for (TermList::const_iterator it = w.begin(),
            iend = w.end(); it != iend; ++it) {
        assert(*it);
        assert(is_int(*it));
        Number v;
        bool v_is_num = mgr_->is_number((*it)->get_symbol(), &v);
        assert(v_is_num);
        if (v < zero) {
            parser_->raise(ParserInterface::error("predicate `bin_packing_load' ")
                << "the weights must be non-negative",
                FlatZincInterface::GENERIC_ERROR);
        }
        tot_weight = tot_weight + v;
    }

    Term tweight = mgr_->make_number(tot_weight);
    Term ret = mgr_->make_equal(
                make_sum(load),
                tweight
          );

    Term loadlower = mgr_->make_number(loaddom.lower());
    Term loadupper = mgr_->make_number(loaddom.upper());

    for (TermList::const_iterator it = bin.begin(),
            iend = bin.end(); it != iend; ++it) {
        assert(*it);
        assert(is_int(*it));
        Term t = mgr_->make_and(
                mgr_->make_leq(loadlower, *it),
                mgr_->make_leq(*it, loadupper)
            );
        ret = mgr_->make_and(ret, t);
    }

    TermList clauses;
    clauses.reserve(bin.size());
    Term lb = mgr_->make_number(loaddom.lower());
    for (size_t idx = 0; idx < load.size(); ++idx) {
        Term bterm = mgr_->make_plus(mgr_->make_number(idx), lb);
        assert(bterm && load[idx]);
        assert(is_int(load[idx]));
        clauses.clear();
        for (size_t i = 0; i < bin.size(); ++i) {
            Term neq = mgr_->make_not(mgr_->make_equal(bterm, bin[i]));
            clauses.push_back(neq);
        }
        
        Term pbterm = bank_->make_private_pbsum(clauses, w);
        Term t = mgr_->make_equal(pbterm, load[idx]);
        Term tbounds = mgr_->make_and(
                mgr_->make_leq(zero_, pbterm),
                mgr_->make_leq(pbterm, tweight)
            );
        Term lbounds = mgr_->make_and(
                mgr_->make_leq(zero_, load[idx]),
                mgr_->make_leq(load[idx], tweight)
            );
        Term big_and = mgr_->make_and(t,
                mgr_->make_and(tbounds, lbounds)
            );
        ret = mgr_->make_and(ret, big_and);
    }

    return ret;
}

//-----------------------------------------------------------------------------
// element
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::element(Term i, TermList &x,
        Term y, NumInterval &xdom)
{
    assert(i && y);
    if (!is_int(i)) {
        parser_->raise(ParserInterface::error("predicate `element_T' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(var int, array[int] of var T, var T)'\n"
            << "\twhere T = bool, int or float",
            FlatZincInterface::TYPE_INST_ERROR);
    }

    Term ret = mgr_->make_and(
                    mgr_->make_leq(mgr_->make_number(xdom.lower()), i),
                    mgr_->make_leq(i, mgr_->make_number(xdom.upper()))
                );

    Term (TermManager:: *func)(Term, Term) =
        &TermManager::make_equal;
    if (mgr_->is_bool_type(y->get_type())) {
        func = &TermManager::make_iff;
    }

    Number v(xdom.lower());
    for (TermList::const_iterator it = x.begin(),
            iend = x.end(); it != iend; it++) {
        assert(*it);
        if (!are_compatible_types(*it, y)) {
            parser_->raise(ParserInterface::error("predicate `element_T' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(var int, array[int] of var T, var T)'\n"
                << "\twhere T = bool, int or float",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term tor = (mgr_->*func)(*it, y);
        tor = mgr_->make_or(tor,
              mgr_->make_not(mgr_->make_equal(i, mgr_->make_number(v))));
        ret = mgr_->make_and(ret, tor);
        v = v + Number(1);
    }
    return ret;
}

Term FlatZincGlConstraints::element(Term i, FznSetListSharedPtr x,
        FznSetSharedPtr y, NumInterval &xdom)
{
    assert(i && y);
    if (!is_int(i)) {
        parser_->raise(ParserInterface::error("predicate `element_set' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(var int, array[int] of var set of int, "
            << "var set of int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = mgr_->make_and(
                    mgr_->make_leq(mgr_->make_number(xdom.lower()), i),
                    mgr_->make_leq(i, mgr_->make_number(xdom.upper()))
                );

    Number v(xdom.lower());
    for (FznSetList::const_iterator it = x->begin(),
            iend = x->end(); it != iend; it++) {
        assert(*it);
        Term tor = set_eq(*it, y);
        tor = mgr_->make_or(tor,
              mgr_->make_not(mgr_->make_equal(i, mgr_->make_number(v))));
        ret = mgr_->make_and(ret, tor);
        v = v + Number(1);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// comparison_rel_array
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::comparison_rel_array(
        TermList &rels, Term rel)
{
    assert(rel);
    if (rels.size() == 0) {
        parser_->raise(ParserInterface::error("predicate `comparison_rel_array' ")
            << "undefined constraint over empty array",
            FlatZincInterface::EVALUATION_ERROR);
    }
    TermList r;
    r.reserve(rels.size() + 1);
    for (size_t i = 0; i <= rels.size(); ++i) {
        Term t = bank_->make_private_term(mgr_->get_integer_type());
        assert(t);
        r.push_back(t);
    }
    Term ret = mgr_->make_and(
                    mgr_->make_equal(r[0], zero_),
                    mgr_->make_equal(r[rels.size()], rel)
                );
    for (size_t i = 1; i <= rels.size(); ++i) {
        assert(rels[i-1]);
        Term eq = mgr_->make_equal(r[i-1], zero_);
        Term t1 = mgr_->make_equal(r[i], rels[i-1]);
        Term neq = mgr_->make_not(eq);
        Term t2 = mgr_->make_equal(r[i], r[i-1]);
        assert(eq && t1 && neq && t2);
        Term i1 = mgr_->make_or(neq, t1);
        Term i2 = mgr_->make_or(eq, t2);
        assert(i1 && i2);
        ret = mgr_->make_and(ret,
              mgr_->make_and(i1, i2));
    }
    return ret;
}

//-----------------------------------------------------------------------------
// count
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::count_eq(Term n, TermList &x, Term v)
{
    assert(n && v);
    if (!is_int(n) || !is_int(v)) {
        parser_->raise(ParserInterface::error("predicate `count_eq' ")
            << "argument list has invalid type-isnt:\n"
            <<"\texpected `(array[int] of var int, var int, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_equal(count, n);
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, n),
                mgr_->make_leq(n, mgr_->make_number(x.size()))
          ));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x.size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::count_geq(Term n, TermList &x, Term v)
{
    assert(n && v);
    if (!is_int(n) || !is_int(v)) {
        parser_->raise(ParserInterface::error("predicate `count_geq' ")
            << "argument list has invalid type-isnt:\n"
            <<"\texpected `(array[int] of var int, var int, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_leq(n, count);
    ret = mgr_->make_and(ret, mgr_->make_leq(n, mgr_->make_number(x.size())));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x.size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::count_gt(Term n, TermList &x, Term v)
{
    assert(n && v);
    if (!is_int(n) || !is_int(v)) {
        parser_->raise(ParserInterface::error("predicate `count_gt' ")
            << "argument list has invalid type-isnt:\n"
            <<"\texpected `(array[int] of var int, var int, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_not(mgr_->make_leq(count, n));
    ret = mgr_->make_and(ret,
            mgr_->make_not(mgr_->make_leq(mgr_->make_number(x.size()), n)));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x.size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::count_leq(Term n, TermList &x, Term v)
{
    assert(n && v);
    if (!is_int(n) || !is_int(v)) {
        parser_->raise(ParserInterface::error("predicate `count_leq' ")
            << "argument list has invalid type-isnt:\n"
            <<"\texpected `(array[int] of var int, var int, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_leq(count, n);
    ret = mgr_->make_and(ret, mgr_->make_leq(zero_, n));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x.size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::count_lt(Term n, TermList &x, Term v)
{
    assert(n && v);
    if (!is_int(n) || !is_int(v)) {
        parser_->raise(ParserInterface::error("predicate `count_lt' ")
            << "argument list has invalid type-isnt:\n"
            <<"\texpected `(array[int] of var int, var int, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_not(mgr_->make_leq(n, count));
    ret = mgr_->make_and(ret, mgr_->make_not(mgr_->make_leq(n, zero_)));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x.size()))
          ));
    return ret;
}

Term FlatZincGlConstraints::count_neq(Term n, TermList &x, Term v)
{
    assert(n && v);
    if (!is_int(n) || !is_int(v)) {
        parser_->raise(ParserInterface::error("predicate `count_neq' ")
            << "argument list has invalid type-isnt:\n"
            <<"\texpected `(array[int] of var int, var int, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = NULL;
    Term count = make_count(x, v);
    ret = mgr_->make_not(mgr_->make_equal(count, n));
    ret = mgr_->make_and(ret,
            mgr_->make_and(
                mgr_->make_leq(zero_, count),
                mgr_->make_leq(count, mgr_->make_number(x.size()))
          ));
    return ret;
}

//-----------------------------------------------------------------------------
// decreasing/increasing
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::decreasing(TermList &x)
{
    Term ret = true_;

    if (x.size() <= 1) {
        return true_;
    }

    assert(x[0]);
    if (mgr_->is_bool_type(x[0]->get_type())) {
        // bool array
        for (size_t i = 1; i < x.size(); ++i) {
            assert(x[i]);
            Term le = mgr_->make_or(x[i-1], mgr_->make_not(x[i]));
            ret = mgr_->make_and(ret, le);
        }
    } else {
        // float/int array
        for (size_t i = 1; i < x.size(); ++i) {
            assert(x[i]);
            Term le = mgr_->make_leq(x[i], x[i-1]);
            ret = mgr_->make_and(ret, le);
        }
    }

    return ret;
}

Term FlatZincGlConstraints::decreasing(FznSetListSharedPtr x)
{
    if (x->size() <= 1) {
        return true_;
    }

    assert((*x)[0]);
    Term ret = true_;
    for (size_t i = 1; i < x->size(); ++i) {
        assert((*x)[i]);
        Term le = set_le((*x)[i], (*x)[i-1]);
        ret = mgr_->make_and(ret, le);
    }

    return ret;
}

Term FlatZincGlConstraints::increasing(TermList &x)
{
    Term ret = true_;

    if (x.size() <= 1) {
        return ret;
    }

    assert(x[0]);
    if (mgr_->is_bool_type(x[0]->get_type())) {
        // bool array
        for (size_t i = 1; i < x.size(); ++i) {
            assert(x[i]);
            Term le = mgr_->make_or(mgr_->make_not(x[i-1]), x[i]);
            ret = mgr_->make_and(ret, le);
        }
    } else {
        // float/int array
        for (size_t i = 1; i < x.size(); ++i) {
            assert(x[i]);
            Term le = mgr_->make_leq(x[i-1], x[i]);
            ret = mgr_->make_and(ret, le);
        }
    }

    return ret;
}

Term FlatZincGlConstraints::increasing(FznSetListSharedPtr x)
{
    if (x->size() <= 1) {
        return true_;
    }

    Term ret = true_;
    assert((*x)[0]);
    for (size_t i = 1; i < x->size(); ++i) {
        assert((*x)[i]);
        Term le = set_le((*x)[i-1], (*x)[i]);
        ret = mgr_->make_and(ret, le);
    }

    return ret;
}

//-----------------------------------------------------------------------------
// diffn
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::diffn(TermList &x, TermList &y,
        TermList &dx, TermList &dy)
{
    size_t len = x.size();

    if (len != y.size() || len != dx.size() || len != dy.size()) {
        parser_->raise(ParserInterface::error("predicate `diffn' ")
            << "index sets mismatch",
            FlatZincInterface::GENERIC_ERROR);
    }

    Term ret = true_;

    for (size_t i = 0; i < len; i++) {
        assert(x[i] && y[i] && dx[i] && dy[i]);
        if (!is_int(x[i]) || !is_int(y[i]) || !is_int(dx[i]) || !is_int(dy[i])) {
            parser_->raise(ParserInterface::error("predicate `diffn' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of var int, "
                << "array[int] of var int, array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        for (size_t j = i + 1; j < len; j++) {
            assert(x[j] && y[j] && dx[j] && dy[j]);
            Term t1 = mgr_->make_leq(mgr_->make_plus(x[i], dx[i]), x[j]);
            Term t2 = mgr_->make_leq(mgr_->make_plus(y[i], dy[i]), y[j]);
            Term t3 = mgr_->make_leq(mgr_->make_plus(x[j], dx[j]), x[i]);
            Term t4 = mgr_->make_leq(mgr_->make_plus(y[j], dy[j]), y[i]);
            Term big_or = mgr_->make_or(t1,
                          mgr_->make_or(t2,
                          mgr_->make_or(t3, t4)));
            ret = mgr_->make_and(ret, big_or);
        }
    }

/*
    // PTNOTE: experimentally not efficient
    Term xlower = NULL;
    Term xupper = NULL;
    bool xpos_dom = false;
    size_t xwidth = bank_->get_required_bv_bits(x, xlower, xupper, xpos_dom);
    Term dxlower = NULL;
    Term dxupper = NULL;
    bool dxpos_dom = false;
    size_t dxwidth = bank_->get_required_bv_bits(dx, dxlower, dxupper, dxpos_dom);
    Term ylower = NULL;
    Term yupper = NULL;
    bool ypos_dom = false;
    size_t ywidth = bank_->get_required_bv_bits(y, ylower, yupper, ypos_dom);
    Term dylower = NULL;
    Term dyupper = NULL;
    bool dypos_dom = false;
    size_t dywidth = bank_->get_required_bv_bits(dy, dylower, dyupper, dypos_dom);

    size_t width = (xwidth >= dxwidth ? xwidth : dxwidth);
    width = (width >= ywidth ? width : ywidth);
    width = (width >= dywidth ? width : dywidth);
    bool positive_domain = xpos_dom & dxpos_dom & ypos_dom & dypos_dom;

    assert(width > 0);

    TermList bvx;
    TermList bvdx;
    TermList bvy;
    TermList bvdy;

    for(size_t i = 0; i < len; i++) {
        Term t = mgr_->make_int_to_bv(width, x[i]);
        Term bvbounds = NULL;
        if (positive_domain) {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_ule(mgr_->make_int_to_bv(width, xlower), t),
                mgr_->make_bv_ule(t, mgr_->make_int_to_bv(width, xupper))
            );
        } else {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_sle(mgr_->make_int_to_bv(width, xlower), t),
                mgr_->make_bv_sle(t, mgr_->make_int_to_bv(width, xupper))
            );
        }
        ret = (ret ? mgr_->make_and(ret, bvbounds) : bvbounds);
        bvx.push_back(t);
    }
    for(size_t i = 0; i < len; i++) {
        Term t = mgr_->make_int_to_bv(width, dx[i]);
        Term bvbounds = NULL;
        if (positive_domain) {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_ule(mgr_->make_int_to_bv(width, dxlower), t),
                mgr_->make_bv_ule(t, mgr_->make_int_to_bv(width, dxupper))
            );
        } else {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_sle(mgr_->make_int_to_bv(width, dxlower), t),
                mgr_->make_bv_sle(t, mgr_->make_int_to_bv(width, dxupper))
            );
        }
        ret = (ret ? mgr_->make_and(ret, bvbounds) : bvbounds);
        bvdx.push_back(t);
    }
    for(size_t i = 0; i < len; i++) {
        Term t = mgr_->make_int_to_bv(width, y[i]);
        Term bvbounds = NULL;
        if (positive_domain) {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_ule(mgr_->make_int_to_bv(width, ylower), t),
                mgr_->make_bv_ule(t, mgr_->make_int_to_bv(width, yupper))
            );
        } else {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_sle(mgr_->make_int_to_bv(width, ylower), t),
                mgr_->make_bv_sle(t, mgr_->make_int_to_bv(width, yupper))
            );
        }
        ret = (ret ? mgr_->make_and(ret, bvbounds) : bvbounds);
        bvy.push_back(t);
    }
    for(size_t i = 0; i < len; i++) {
        Term t = mgr_->make_int_to_bv(width, dy[i]);
        Term bvbounds = NULL;
        if (positive_domain) {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_ule(mgr_->make_int_to_bv(width, dylower), t),
                mgr_->make_bv_ule(t, mgr_->make_int_to_bv(width, dyupper))
            );
        } else {
            bvbounds = mgr_->make_and(
                mgr_->make_bv_sle(mgr_->make_int_to_bv(width, dylower), t),
                mgr_->make_bv_sle(t, mgr_->make_int_to_bv(width, dyupper))
            );
        }
        ret = (ret ? mgr_->make_and(ret, bvbounds) : bvbounds);
        bvdy.push_back(t);
    }

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (positive_domain) {
                Term t1 = mgr_->make_bv_ule(mgr_->make_bv_add(bvx[i], bvdx[i]), bvx[j]);
                Term t2 = mgr_->make_bv_ule(mgr_->make_bv_add(bvy[i], bvdy[i]), bvy[j]);
                Term t3 = mgr_->make_bv_ule(mgr_->make_bv_add(bvx[j], bvdx[j]), bvx[i]);
                Term t4 = mgr_->make_bv_ule(mgr_->make_bv_add(bvy[j], bvdy[j]), bvy[i]);
                Term big_or = mgr_->make_or(t1,
                              mgr_->make_or(t2,
                              mgr_->make_or(t3, t4)));
                ret = (ret ? mgr_->make_and(ret, big_or) : big_or);
            } else {
                Term t1 = mgr_->make_bv_sle(mgr_->make_bv_add(bvx[i], bvdx[i]), bvx[j]);
                Term t2 = mgr_->make_bv_sle(mgr_->make_bv_add(bvy[i], bvdy[i]), bvy[j]);
                Term t3 = mgr_->make_bv_sle(mgr_->make_bv_add(bvx[j], bvdx[j]), bvx[i]);
                Term t4 = mgr_->make_bv_sle(mgr_->make_bv_add(bvy[j], bvdy[j]), bvy[i]);
                Term big_or = mgr_->make_or(t1,
                              mgr_->make_or(t2,
                              mgr_->make_or(t3, t4)));
                ret = (ret ? mgr_->make_and(ret, big_or) : big_or);
            }
        }
    }
*/

    return ret;
}

Term FlatZincGlConstraints::diffn_nonstrict(TermList &x, TermList &y,
        TermList &dx, TermList &dy)
{
    size_t len = x.size();

    if (len != y.size() || len != dx.size() || len != dy.size()) {
        parser_->raise(ParserInterface::error("predicate `diffn_nonstrict' ")
            << "index sets mismatch",
            FlatZincInterface::GENERIC_ERROR);
    }

    Term ret = true_;

    for (size_t i = 0; i < len; i++) {
        assert(x[i] && y[i] && dx[i] && dy[i]);
        if (!is_int(x[i]) || !is_int(y[i]) || !is_int(dx[i]) || !is_int(dy[i])) {
            parser_->raise(ParserInterface::error("predicate `diffn_nonstrict' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of var int, "
                << "array[int] of var int, array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        for (size_t j = i + 1; j < len; j++) {
            assert(x[j] && y[j] && dx[j] && dy[j]);
            Term t1 = mgr_->make_leq(mgr_->make_plus(x[i], dx[i]), x[j]);
            Term t2 = mgr_->make_leq(mgr_->make_plus(y[i], dy[i]), y[j]);
            Term t3 = mgr_->make_leq(mgr_->make_plus(x[j], dx[j]), x[i]);
            Term t4 = mgr_->make_leq(mgr_->make_plus(y[j], dy[j]), y[i]);
            Term t5 = mgr_->make_equal(dx[i], zero_);
            Term t6 = mgr_->make_equal(dx[j], zero_);
            Term t7 = mgr_->make_equal(dy[i], zero_);
            Term t8 = mgr_->make_equal(dy[j], zero_);

            Term big_or = mgr_->make_or(t1,
                          mgr_->make_or(t2,
                          mgr_->make_or(t3,
                          mgr_->make_or(t4,
                          mgr_->make_or(t5,
                          mgr_->make_or(t6,
                          mgr_->make_or(t7, t8)))))));
            ret = mgr_->make_and(ret, big_or);
        }
    }

    return ret;
}

Term FlatZincGlConstraints::diffn_nonoverlap_k(TermList &x1, TermList &w1,
        TermList &x2, TermList &w2)
{
    size_t len = x1.size();

    if (len != w1.size() || len != x2.size() || len != w2.size()) {
        parser_->raise(ParserInterface::error("predicate `diffn_nonoverlap_k' ")
            << "index sets mismatch",
            FlatZincInterface::GENERIC_ERROR);
    }

    Term ret = true_;

    for (size_t i = 0; i < len; i++) {
        assert(x1[i] && w1[i] && x2[i] && w2[i]);
        if (!is_int(x1[i]) || !is_int(w1[i]) || !is_int(x2[i]) || !is_int(w2[i])) {
            parser_->raise(ParserInterface::error("predicate `diffn_nonoverlap_k' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of var int, "
                << "array[int] of var int, array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term t1 = mgr_->make_leq(mgr_->make_plus(x1[i], w1[i]), x2[i]);
        Term t2 = mgr_->make_leq(mgr_->make_plus(x2[i], w2[i]), x1[i]);

        Term big_or = mgr_->make_or(t1, t2);
        ret = mgr_->make_and(ret, big_or);
    }

    return ret;
}

Term FlatZincGlConstraints::diffn_nonstrict_nonoverlap_k(TermList &x1,
        TermList &w1, TermList &x2, TermList &w2)
{
    size_t len = x1.size();
    if (len != w1.size() || len != x2.size() || len != w2.size()) {
        parser_->raise(ParserInterface::error("predicate `diffn_nonstrict_nonoverlap_k' ")
            << "index sets mismatch",
            FlatZincInterface::GENERIC_ERROR);
    }
    Term ret = true_;
    for (size_t i = 0; i < len; i++) {
        assert(x1[i] && w1[i] && x2[i] && w2[i]);
        if (!is_int(x1[i]) || !is_int(w1[i]) || !is_int(x2[i]) || !is_int(w2[i])) {
            parser_->raise(ParserInterface::error("predicate `diffn_nonstrict_nonoverlap_k' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of var int, "
                << "array[int] of var int, array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term t1 = mgr_->make_leq(mgr_->make_plus(x1[i], w1[i]), x2[i]);
        Term t2 = mgr_->make_leq(mgr_->make_plus(x2[i], w2[i]), x1[i]);
        Term t3 = mgr_->make_equal(w1[i], zero_);
        Term t4 = mgr_->make_equal(w2[i], zero_);

        Term big_or = mgr_->make_or(t1,
                      mgr_->make_or(t2,
                      mgr_->make_or(t3, t4)));
        ret = mgr_->make_and(ret, big_or);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// distribute
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::distribute(TermList &card,
        TermList &value, TermList &base)
{
    Term ret = true_;
    if (card.size() != value.size()) {
        parser_->raise(ParserInterface::error("predicate `distribute' ")
            << "card and value arrays must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }
    for (TermList::const_iterator it = card.begin(), jt = value.begin(),
            iend = card.end(), jend = card.end(); it != iend && jt != jend; ++it, ++jt) {
        assert(*it && *jt);
        Term count = make_count(base, *jt);
        Term eq = mgr_->make_equal(*it, count);
        ret = mgr_->make_and(ret, eq);
        ret = mgr_->make_and(ret,
                mgr_->make_and(
                    mgr_->make_leq(zero_, *it),
                    mgr_->make_leq(*it, mgr_->make_number(base.size()))
              ));
        ret = mgr_->make_and(ret,
                mgr_->make_and(
                    mgr_->make_leq(zero_, count),
                    mgr_->make_leq(count, mgr_->make_number(base.size()))
              ));
    }
    return ret;
}

//-----------------------------------------------------------------------------
// geost
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::geost_nonoverlap_k(TermList &x1,
        TermList &w1, TermList &x2, TermList &w2)
{
    if (x1.size() != w1.size() || x1.size() != x2.size() || x1.size() != w2.size()) {
        parser_->raise(ParserInterface::error("predicate `geost_nonoverlap_k' ")
            << "index sets of arguments do not match",
            FlatZincInterface::GENERIC_ERROR);
    }
    Term ret = false_;
    for (size_t i = 0; i < x1.size(); ++i) {
        assert(x1[i] && w1[i] && x2[i] && w2[i]);
        if (!is_int(x1[i]) || !is_int(w1[i]) || !is_int(x2[i]) || !is_int(w2[i])) {
            parser_->raise(ParserInterface::error("predicate `geost_nonoverlap_k' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of int, "
                << "array[int] of var int, array[int] of int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term t1 = mgr_->make_leq(
                        mgr_->make_plus(x1[i], w1[i]),
                        x2[i]
                    );
        Term t2 = mgr_->make_leq(
                        mgr_->make_plus(x2[i], w2[i]),
                        x1[i]
                    );
        ret = mgr_->make_or(ret, t1);
        ret = mgr_->make_or(ret, t2);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// global_cardinality
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::global_cardinality(TermList &x,
        TermList &cover, TermList &counts)
{
    if (cover.size() != counts.size()) {
        parser_->raise(ParserInterface::error("predicate `global_cardinality' ")
            << "cover and counts must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }
    if (cover.size() == 0) {
        return true_;
    }
    Term ret = mgr_->make_leq(
                make_sum(counts),
                mgr_->make_number(x.size())
          );
    for (size_t i = 0; i < cover.size(); ++i ) {
        assert(cover[i] && counts[i]);
        if (!is_int(cover[i]) || !is_int(counts[i])) {
            parser_->raise(ParserInterface::error("predicate `global_cardinality' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term cterm = count_eq(counts[i], x, cover[i]);
        ret = mgr_->make_and(ret, cterm);
    }
    return ret;
}

Term FlatZincGlConstraints::global_cardinality_closed(TermList &x,
        TermList &cover, TermList &counts)
{
    if (cover.size() != counts.size()) {
        parser_->raise(ParserInterface::error("predicate `global_cardinality_closed' ")
            << "cover and counts must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }

    if (cover.size() == 0) {
        return true_;
    }

    Term ret = mgr_->make_equal(
                make_sum(counts),
                mgr_->make_number(x.size())
          );

    for (size_t i = 0; i < cover.size(); ++i ) {
        assert(cover[i] && counts[i]);
        if (!is_int(cover[i]) || !is_int(counts[i])) {
            parser_->raise(ParserInterface::error("predicate `global_cardinality_closed' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of int, "
                << "array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term cterm = count_eq(counts[i], x, cover[i]);
        ret = mgr_->make_and(ret, cterm);
    }

    for (TermList::const_iterator it = x.begin(),
            iend = x.end(); it != iend; ++it) {
        assert(*it);
        if (!is_int(*it)) {
            parser_->raise(ParserInterface::error("predicate `global_cardinality_closed' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of int, "
                << "array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term big_or = false_;
        for (TermList::const_iterator jt = cover.begin(),
                jend = cover.end(); jt != jend; ++jt) {
            assert(*jt);
            Term eq = mgr_->make_equal(*it, *jt);
            big_or = mgr_->make_or(big_or, eq);
        }
        ret = mgr_->make_and(ret, big_or);
    }

    return ret;
}

Term FlatZincGlConstraints::global_cardinality_low_up(TermList &x,
        TermList &cover, TermList &lbound, TermList &ubound)
{
    if (cover.size() != lbound.size() || cover.size() != ubound.size()) {
        parser_->raise(ParserInterface::error("predicate `global_cardinality_low_up' ")
            << "cover, lbound and ubound must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }

    if (cover.size() == 0) {
        return true_;
    }

    Term ret = true_;

    for (size_t i = 0; i < cover.size(); ++i ) {
        assert(cover[i] && lbound[i] && ubound[i]);
        if (!is_int(cover[i]) || !is_int(lbound[i]) || !is_int(ubound[i])) {
            parser_->raise(ParserInterface::error("predicate `global_cardinality_low_up' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of int, "
                << "array[int] of int, array[int] of int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term count = make_count(x, cover[i]);
        Term t = mgr_->make_and(
                    mgr_->make_leq(lbound[i], count),
                    mgr_->make_leq(count, ubound[i])
                );
        ret = mgr_->make_and(ret, t);
    }

    return ret;
}

Term FlatZincGlConstraints::global_cardinality_low_up_closed(
        TermList &x, TermList &cover, TermList &lbound, TermList &ubound)
{
    if (cover.size() != lbound.size() || cover.size() != ubound.size()) {
        parser_->raise(ParserInterface::error("predicate `global_cardinality_low_up_closed' ")
            << "cover, lbound and ubound must have identical index sets",
            FlatZincInterface::GENERIC_ERROR);
    }

    if (cover.size() == 0) {
        return true_;
    }

    Term ret = global_cardinality_low_up(x, cover, lbound, ubound);

    Term x_len = mgr_->make_number(x.size());

    ret = mgr_->make_and(ret,
                mgr_->make_and(
                    mgr_->make_leq(make_sum(lbound), x_len),
                    mgr_->make_leq(x_len, make_sum(ubound))
                )
            );

    for (TermList::const_iterator it = x.begin(),
            iend = x.end(); it != iend; ++it) {
        assert(*it);
        if (!is_int(*it)) {
            parser_->raise(ParserInterface::error("predicate `global_cardinality_low_up_closed' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of int, "
                << "array[int] of int, array[int] of int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term big_or = false_;
        for (TermList::const_iterator jt = cover.begin(),
                jend = cover.end(); jt != jend; ++jt) {
            assert(*jt);
            Term eq = mgr_->make_equal(*it, *jt);
            big_or = mgr_->make_or(big_or, eq);
        }
        ret = mgr_->make_and(ret, big_or);
    }

    return ret;
}

//-----------------------------------------------------------------------------
// int_set_channel
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::int_set_channel(TermList &x, FznSetListSharedPtr y,
        const NumInterval &xdom, const NumInterval &ydom)
{
    FznSetSharedPtr xset(new FlatZincSet(true));
    FznSetSharedPtr yset(new FlatZincSet(true));
    assert(xset && yset);
    xset->add_set_elements(xdom);
    yset->add_set_elements(ydom);
    Term ret = true_;
    for (TermList::const_iterator it = x.begin(),
            iend = x.end(); it != iend; ++it) {
        Term x_in_yset = set_in(*it, yset, true);
        assert(x_in_yset);
        ret = mgr_->make_and(ret, x_in_yset);
    }
    for (FznSetList::const_iterator jt = y->begin(),
            jend = y->end(); jt != jend; ++jt) {
        Term y_in_xset = set_subseteq(*jt, xset);
        assert(y_in_xset);
        ret = mgr_->make_and(ret, y_in_xset);
    }
    Term xlb = mgr_->make_number(xdom.lower());
    Term ylb = mgr_->make_number(ydom.lower());
    for (size_t idx = 0; idx < x.size(); ++idx) {
        Term i = mgr_->make_plus(mgr_->make_number(idx), xlb);
        for (size_t idy = 0; idy < y->size(); ++idy) {
            Term j = mgr_->make_plus(mgr_->make_number(idy), ylb);
            Term t1 = mgr_->make_equal(x[idx], j);
            Term t2 = set_in(i, (*y)[idy], true);
            ret = mgr_->make_and(ret,
                  mgr_->make_iff(t1, t2));
        }
    }
    return ret;
}

//-----------------------------------------------------------------------------
// inverse
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::inverse(TermList &f, TermList &invf,
        const NumInterval &fdom, const NumInterval &invfdom)
{
    Term ret = true_;

    if (f.size() != invf.size()) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
        return false_;
    }

    // interval domain specification
    Term flower = mgr_->make_number(fdom.lower());
    Term fupper = mgr_->make_number(fdom.upper());
    Term invflower = mgr_->make_number(invfdom.lower());
    Term invfupper = mgr_->make_number(invfdom.upper());
    for (TermList::const_iterator it = f.begin(),
            iend = f.end(); it != iend; ++it) {
        assert(*it);
        if (!is_int(*it)) {
            parser_->raise(ParserInterface::error("predicate `inverse' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term fbounds = mgr_->make_and(
                            mgr_->make_leq(invflower, *it),
                            mgr_->make_leq(*it, invfupper)
                        );
        ret = mgr_->make_and(ret, fbounds);
    }
    for (TermList::const_iterator jt = invf.begin(),
            jend = invf.end(); jt != jend; ++jt) {
        assert(*jt);
        if (!is_int(*jt)) {
            parser_->raise(ParserInterface::error("predicate `inverse' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term invfbounds = mgr_->make_and(
                                mgr_->make_leq(flower, *jt),
                                mgr_->make_leq(*jt, fupper)
                            );
        ret = mgr_->make_and(ret, invfbounds);
    }

    Term flb = mgr_->make_number(fdom.lower());
    Term ilb = mgr_->make_number(invfdom.lower());
    for (size_t idx = 0; idx < f.size(); ++idx) {
        Term iv = mgr_->make_plus(mgr_->make_number(idx), flb);
        for (size_t jdx = 0; jdx < invf.size(); ++jdx) {
            Term jv = mgr_->make_plus(mgr_->make_number(jdx), ilb);
            Term eq1 = mgr_->make_equal(f[idx], jv);
            Term eq2 = mgr_->make_equal(invf[jdx], iv);
            Term iff = mgr_->make_iff(eq1, eq2);
            ret = mgr_->make_and(ret, iff);
        }
    }

    return ret;
}

Term FlatZincGlConstraints::inverse_set(FznSetListSharedPtr f,
        FznSetListSharedPtr invf, const NumInterval &fdom,
        const NumInterval &invfdom)
{
    Term ret = true_;

    if (f->size() != invf->size()) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
        return false_;
    }

    FznSetSharedPtr fdomset(new FlatZincSet(true));
    FznSetSharedPtr invfdomset(new FlatZincSet(true));
    fdomset->add_set_elements(fdom);
    invfdomset->add_set_elements(invfdom);

    for (FznSetList::const_iterator it = f->begin(),
            iend = f->end(); it != iend; ++it) {
        assert(*it);
        Term t = set_subseteq(*it, invfdomset);
        ret = mgr_->make_and(ret, t);
    }

    for (FznSetList::const_iterator jt = invf->begin(),
            jend = invf->end(); jt != jend; ++jt) {
        assert(*jt);
        Term t = set_subseteq(*jt, fdomset);
        ret = mgr_->make_and(ret, t);
    }

    Term flb = mgr_->make_number(fdom.lower());
    Term ilb = mgr_->make_number(invfdom.lower());
    for (size_t idx = 0; idx < f->size(); ++idx) {
        Term iv = mgr_->make_plus(mgr_->make_number(idx), flb);
        for (size_t jdx = 0; jdx < invf->size(); ++jdx) {
            Term jv = mgr_->make_plus(mgr_->make_number(jdx), ilb);
            Term incl1 = set_in(jv, (*f)[idx], true);
            Term incl2 = set_in(iv, (*invf)[jdx], true);
            Term iff = mgr_->make_iff(incl1, incl2);
            ret = mgr_->make_and(ret, iff);
        }
    }

    return ret;
}

//-----------------------------------------------------------------------------
// link_set_to_booleans
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::link_set_to_booleans(FznSetSharedPtr s,
        TermList &b, const NumInterval &bdom)
{
    assert(s);

    FznSetSharedPtr bset(new FlatZincSet(true));
    assert(bset);
    bset->add_set_elements(bdom);

    Term ret = set_subseteq(s, bset);

    Term lb = mgr_->make_number(bdom.lower());
    for (size_t idx = 0; idx < b.size(); ++idx) {
        assert(b[idx]);
        if (!is_bool(b[idx])) {
            parser_->raise(ParserInterface::error("predicate `link_set_to_booleans' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(var set of int, array[int] of var bool)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term i = mgr_->make_plus(mgr_->make_number(idx), lb);
        Term i_in_s = set_in(i, s, true);
        Term iff = mgr_->make_iff(b[idx], i_in_s);
        ret = mgr_->make_and(ret, iff);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// member
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::member(TermList &x, Term y)
{
    assert(y);

    if (x.size() <= 0) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
        return false_;
    }

    Term (TermManager::* func)(Term, Term ) =
        &TermManager::make_equal;
    if (mgr_->is_bool_type(y->get_type())) {
        func = &TermManager::make_iff;
    }

    Term ret = false_;
    for (TermList::const_iterator it = x.begin(),
            iend = x.end(); it != iend; ++it) {
        assert(*it);
        Term eq = (mgr_->*func)(*it, y);
        ret = mgr_->make_or(ret, eq);
    }

    return ret;
}

Term FlatZincGlConstraints::member(FznSetListSharedPtr x,
        FznSetSharedPtr y)
{
    assert(y);

    if (x->size() <= 0) {
        parser_->raise_early_unsat(FlatZincInterface::early_unsat("")
            << "model inconsistency detected before search");
        return false_;
    }

    Term ret = false_;
    for (FznSetList::const_iterator it = x->begin(),
            iend = x->end(); it != iend; ++it) {
        assert(*it);
        Term eq = set_eq(*it, y);
        ret = mgr_->make_or(ret, eq);
    }

    return ret;
}

//-----------------------------------------------------------------------------
// nvalue
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::nvalue(Term n, TermList &x)
{
    assert(n);

    if (x.size() == 0) {
        parser_->raise(ParserInterface::error("predicate `nvalue' ")
            << "empty set",
            FlatZincInterface::GENERIC_ERROR);
    }

    if (!is_int(n)) {
        parser_->raise(ParserInterface::error("predicate `nvalue' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(var int, array[int] of var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }

    // assumption: flatzinc values can all be stored in long
    std::unordered_map<long, Term> map;
    for (TermList::const_iterator it = x.begin(),
            iend = x.end(); it != iend; ++it) {
        assert(*it);
        if (!is_int(*it)) {
            parser_->raise(ParserInterface::error("predicate `nvalue' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(var int, array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Number nlower;
        Number nupper;
        bool status = bank_->get_var_bounds(*it, nlower, nupper);
        if (!status) {
            parser_->raise(ParserInterface::error("predicate `nvalue' ")
                << "infinite set",
                FlatZincInterface::GENERIC_ERROR);
        }
        long llower = 0;
        long lupper = 0;
        status = nlower.to_int(llower);
        if (!status) {
            parser_->raise(ParserInterface::error("predicate `nvalue' ")
                << "domain value too large, it can not be handled",
                FlatZincInterface::GENERIC_ERROR);
        }
        status = nupper.to_int(lupper);
        if (!status) {
            parser_->raise(ParserInterface::error("predicate `nvalue' ")
                << "domain value too large, it can not be handled",
                FlatZincInterface::GENERIC_ERROR);
        }
        for (; llower <= lupper; ++llower) {
            Term eq = mgr_->make_equal(*it, mgr_->make_number(llower));
            std::unordered_map<long, Term>::iterator jt = map.find(llower);
            if (jt != map.end()) {
                map[llower] = mgr_->make_or(jt->second, eq);
            } else {
                map[llower] = eq;
            }
        }
    }

    TermList clauses;
    for (std::unordered_map<long, Term>::iterator it = map.begin(),
            iend = map.end(); it != iend; ++it) {
        assert(it->second);
        clauses.push_back(mgr_->make_not(it->second));
    }
    
    Term pbterm = bank_->make_private_pbsum(clauses, one_);
    Term ret = mgr_->make_equal(pbterm, n);
    return ret;
}

//-----------------------------------------------------------------------------
// range
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::range(TermList &x, FznSetSharedPtr s,
        FznSetSharedPtr t, const NumInterval &xdom)
{
    assert(s && t);
    const NumIntervalSet &sset = s->get_domain();
    const NumIntervalSet &tset = t->get_domain();
    FznSetSharedPtr xset(new FlatZincSet(true));
    xset->add_set_elements(xdom);
    Term ret = set_subseteq(s, xset);
    assert(ret);
    Number lb = xdom.lower();
    for (size_t idx = 0; idx < x.size(); ++idx) {
        Number v = Number(idx) + lb;
        if (!sset.contains(v)) {
            continue;
        }
        assert(x[idx]);
        if (!is_int(x[idx])) {
            parser_->raise(ParserInterface::error("predicate `range' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, "
                << "var set of int, var set of int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term t1 = set_in(mgr_->make_number(v), s, true);
        Term t2 = set_in(x[idx], t, true);
        assert (t1 && t2);
        Term impl = mgr_->make_or(mgr_->make_not(t1), t2);
        assert(impl);
        ret = mgr_->make_and(ret, impl);
    }
    for (NumIntervalSet::value_iterator it = tset.value_begin(),
            iend = tset.value_end(); it != iend; ++it) {
        Term pre = set_in(mgr_->make_number(*it), t, true);
        Term inum = mgr_->make_number(*it);
        assert(pre && inum);
        Term big_or = false_;
        for (size_t jdx = 0; jdx < x.size(); ++jdx) {
            Number v = Number(jdx) + lb;
            if (!sset.contains(v)) {
                continue;
            }
            assert(x[jdx]);
            Term t1 = set_in(mgr_->make_number(v), s, true);
            Term t2 = mgr_->make_equal(x[jdx], inum);
            assert(t1 && t2);
            Term t3 = mgr_->make_and(t1, t2);
            assert(t3);
            big_or = mgr_->make_or(big_or, t3);
        }
        Term impl = mgr_->make_or(mgr_->make_not(pre), big_or);
        assert(impl);
        ret = mgr_->make_and(ret, impl);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// bool_clause_reif
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::bool_clause_reif(TermList &as,
        TermList &bs, Term b)
{
    assert(b);

    if (!is_bool(b)) {
        parser_->raise(ParserInterface::error("predicate `bool_clause_reif' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(array[int] of var bool, "
            << "array[int] of var bool, var bool)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }

    Term ret = true_;
    Term clause = mgr_->make_not(b);

    for (TermList::const_iterator it = as.begin(),
            end = as.end(); it != end; it++) {
        assert(*it);
        if (!is_bool(*it)) {
            parser_->raise(ParserInterface::error("predicate `bool_clause_reif' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var bool, "
                << "array[int] of var bool, var bool)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        clause = mgr_->make_or(clause, *it);
        ret = mgr_->make_and(ret,
                    mgr_->make_or(mgr_->make_not(*it), b)
                );
    }

    for (TermList::const_iterator it = bs.begin(),
            end = bs.end(); it != end; it++) {
        assert(*it);
        if (!is_bool(*it)) {
            parser_->raise(ParserInterface::error("predicate `bool_clause_reif' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var bool, "
                << "array[int] of var bool, var bool)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        clause = mgr_->make_or(clause, mgr_->make_not(*it));
        ret = mgr_->make_and(ret,
                    mgr_->make_or(*it, b)
                );
    }

    ret = mgr_->make_and(ret, clause);
    return ret;
}

//-----------------------------------------------------------------------------
// float_dom
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::float_in(Term x, Term a, Term b)
{
    assert(x && a && b);
    Number v;
    if (!is_float(x) || !is_float(a) || !is_float(b)
            || !mgr_->is_number(a->get_symbol(), &v)
            || !mgr_->is_number(b->get_symbol(), &v)) {
        parser_->raise(ParserInterface::error("predicate `float_in' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(var float, float, float)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }
    Term ret = mgr_->make_and(
                    mgr_->make_leq(a, x),
                    mgr_->make_leq(x, b)
                );
    return ret;
}

Term FlatZincGlConstraints::float_dom(Term x, TermList &as,
        Term a, Term b)
{
    assert(x && a && b);
    Term ret = float_in(x, a, b);
    Term big_or = false_;
    for (size_t i = 0; i < (as.size() / 2); ++i) {
        assert(as[2*i] && as[2*i+1]);
        Term t = float_in(x, as[2*i], as[2*i+1]);
        assert(t);
        big_or = mgr_->make_or(big_or, t);
    }
    ret = mgr_->make_and(ret, big_or);
    return ret;
}

//-----------------------------------------------------------------------------
// range
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::roots(TermList &x, FznSetSharedPtr s,
        FznSetSharedPtr t, const NumInterval &xdom)
{
    assert(s && t);
    const NumIntervalSet &sset = s->get_domain();
    const NumIntervalSet &tset = t->get_domain();
    FznSetSharedPtr xset(new FlatZincSet(true));
    xset->add_set_elements(xdom);
    Term ret = set_subseteq(s, xset);
    assert(ret);
    Number lb = xdom.lower();
    for (size_t idx = 0; idx < x.size(); ++idx) {
        Number v = Number(idx) + lb;
        if (!sset.contains(v)) {
            continue;
        }
        assert(x[idx]);
        if (!is_int(x[idx])) {
            parser_->raise(ParserInterface::error("predicate `range' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int, "
                << "var set of int, var set of int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        Term t1 = set_in(mgr_->make_number(v), s, true);
        Term t2 = set_in(x[idx], t, true);
        assert (t1 && t2);
        Term impl = mgr_->make_or(mgr_->make_not(t1), t2);
        assert(impl);
        ret = mgr_->make_and(ret, impl);
    }
    for (NumIntervalSet::value_iterator it = tset.value_begin(),
            iend = tset.value_end(); it != iend; ++it) {
        Term pre = set_in(mgr_->make_number(*it), t, true);
        Term inum = mgr_->make_number(*it);
        assert(pre && inum);
        Term big_and = true_;
        for (size_t jdx = 0; jdx < x.size(); ++jdx) {
            Number j = Number(jdx) + lb;
            assert(x[jdx]);
            Term t1 = mgr_->make_equal(x[jdx], inum);
            Term t2 = set_in(mgr_->make_number(j), s, true);
            assert(t1 && t2);
            Term t3 = mgr_->make_or(mgr_->make_not(t1), t2);
            assert(t3);
            big_and = mgr_->make_and(big_and, t3);
        }
        Term impl = mgr_->make_or(mgr_->make_not(pre), big_and);
        assert(impl);
        ret = mgr_->make_and(ret, impl);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// sum_pred
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::sum_pred(Term i, FznSetListSharedPtr sets,
        TermList &cs, Term s, const NumInterval &csdom,
        const NumInterval &setsdom)
{
    assert(i && s);

    if (!is_int(i) || !is_int(s)) {
        parser_->raise(ParserInterface::error("predicate `sum_pred' ")
            << "argument list has invalid type-inst:\n"
            << "\texpected `(var int, array[int] of set of int, "
            << "array[int] of int, var int)'",
            FlatZincInterface::TYPE_INST_ERROR);
    }

    Term ret = NULL;
    // assumption: sets is an array of set literals

    Number ivalue(0);
    long il;
    bool res1 = mgr_->is_number(i->get_symbol(), &ivalue);
    bool res2 = ivalue.to_int(il);

    if (res1 && res2) {
        TermList els;
        Number v1 = ivalue - setsdom.lower();
        long zero_idx;
        res2 = v1.to_int(zero_idx);
        assert(res2);
        assert((*sets)[zero_idx] && (*sets)[zero_idx]->is_set_literal());
        const NumIntervalSet &bset = (*sets)[zero_idx]->get_domain();
        for (NumInterval::const_iterator jt = csdom.begin(),
                jend = csdom.end(); jt != jend; ++jt) {
            if (bset.contains(*jt)) {
                Number v2 = *jt - csdom.lower();
                long zero_jdx;
                res2 = v2.to_int(zero_jdx);
                assert(res2);
                assert(cs[zero_jdx]);
                els.push_back(cs[zero_jdx]);
            }
        }
        ret = mgr_->make_equal(s, make_sum(els));
    } else {
        TermList clauses;
        for (NumInterval::const_iterator jt = csdom.begin(),
                jend = csdom.end(); jt != jend; ++jt) {
            Term big_or = false_;
            for (NumInterval::const_iterator kt = setsdom.begin(),
                    kend = setsdom.end(); kt != kend; ++kt) {
                Number v3 = *kt - setsdom.lower();
                long zero_idx = 0;
                res2 = v3.to_int(zero_idx);
                assert(res2);
                assert((*sets)[zero_idx] && (*sets)[zero_idx]->is_set_literal());
                const NumIntervalSet &bset = (*sets)[zero_idx]->get_domain();
                if (bset.contains(*jt)) {
                    Term t = mgr_->make_equal(i, mgr_->make_number(*kt));
                    big_or = mgr_->make_or(t, big_or);
                }
            }
            if (big_or) {
                clauses.push_back(mgr_->make_not(big_or));
            }
        }
        
        Term pbterm = bank_->make_private_pbsum(clauses, cs);
        ret = mgr_->make_equal(s, pbterm);
    }
    assert(ret);
    return ret;
}

//-----------------------------------------------------------------------------
// symmetric_all_different
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::symmetric_all_different(TermList &x,
        const NumInterval &xdom)
{
    Term ret = true_;
    if (x.size() <= 1) {
        return ret;
    }
    ret = all_different(x);
    Number lb = xdom.lower();
    for (size_t idx = 0; idx < x.size(); ++idx) {
        Term it = mgr_->make_number(lb + Number(idx));
        assert(x[idx] && it);
        if (!is_int(x[idx])) {
            parser_->raise(ParserInterface::error("predicate `symmetric_all_different' ")
                << "argument list has invalid type-inst:\n"
                << "\texpected `(array[int] of var int)'",
                FlatZincInterface::TYPE_INST_ERROR);
        }
        for (size_t jdx = (idx + 1); jdx < x.size(); ++jdx) {
            Term jt = mgr_->make_number(lb + Number(jdx));
            assert(x[jdx] && jt);
            Term t1 = mgr_->make_equal(x[idx], jt);
            Term t2 = mgr_->make_equal(x[jdx], it);
            ret = mgr_->make_and(ret,
                        mgr_->make_iff(t1, t2));
        }
    }
    return ret;
}

//-----------------------------------------------------------------------------
// value_precede
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::value_precede(Term s, Term t, TermList &x)
{
    assert(s && t);
    TermList b;
    b.reserve(x.size() + 1);
    b.push_back(false_);
    for (size_t i = 0; i < x.size(); ++i) {
        Term t = bank_->make_private_term(mgr_->get_bool_type());
        assert(t);
        b.push_back(t);
    }
    Term ret = true_;
    for (size_t i = 0; i < x.size(); ++i) {
        Term xis = mgr_->make_equal(x[i], s);
        Term t1 = mgr_->make_or(mgr_->make_not(xis), b[i+1]);
        Term t2 = mgr_->make_or(xis, mgr_->make_iff(b[i], b[i+1]));
        Term t3 = mgr_->make_or(b[i], mgr_->make_not(mgr_->make_equal(x[i], t)));
        ret = mgr_->make_and(ret,
              mgr_->make_and(t1,
              mgr_->make_and(t2, t3)));
    }
    return ret;
}

Term FlatZincGlConstraints::value_precede(Term s, Term t,
        FznSetListSharedPtr x)
{
    assert(s && t);
    TermList b;
    b.reserve(x->size() + 1);
    b.push_back(false_);
    for (size_t i = 0; i < x->size(); ++i) {
        Term t = bank_->make_private_term(mgr_->get_bool_type());
        assert(t);
        b.push_back(t);
    }
    Term ret = true_;
    for (size_t i = 0; i < x->size(); ++i) {
        assert((*x)[i]);
        Term sxi  = set_in(s, (*x)[i], true);
        Term ntxi = mgr_->make_not(set_in(t, (*x)[i], true));
        assert(sxi && ntxi);
        Term xis = mgr_->make_and(sxi, ntxi);
        Term t1 = mgr_->make_or(mgr_->make_not(xis), b[i+1]);
        Term t2 = mgr_->make_or(xis, mgr_->make_iff(b[i], b[i+1]));
        Term t3 = mgr_->make_or(b[i], mgr_->make_or(sxi, ntxi));
        ret = mgr_->make_and(ret,
              mgr_->make_and(t1,
              mgr_->make_and(t2, t3)));
    }
    return ret;
}

//-----------------------------------------------------------------------------
// Private Help Functions
//-----------------------------------------------------------------------------

Term FlatZincGlConstraints::make_count(TermList &x, Term v)
{
    assert(v);
    if (x.size() == 0) {
        return zero_;
    }
    TermList clauses;
    clauses.reserve(x.size());
    for (TermList::const_iterator it = x.begin(), iend = x.end();
            it != iend; ++it) {
        assert(*it);
        Term neq = mgr_->make_not(mgr_->make_equal(*it, v));
        clauses.push_back(neq);
    }
    
    Term pbterm = bank_->make_private_pbsum(clauses, one_);
    return pbterm;
}

Term FlatZincGlConstraints::make_count(FznSetListSharedPtr x, FznSetSharedPtr v)
{
    assert(v);
    if (x->size() == 0) {
        return zero_;
    }
    TermList clauses;
    clauses.reserve(x->size());
    for (FznSetList::const_iterator it = x->begin(), iend = x->end();
            it != iend; ++it) {
        assert(*it);
        Term neq = mgr_->make_not(set_eq(*it, v));
        clauses.push_back(neq);
    }
    Term pbterm = bank_->make_private_pbsum(clauses, one_);
    return pbterm;
}

}} // namespace msat
