// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCBV_H_INCLUDED
#define FLATZINCBV_H_INCLUDED

#include "../utils/numbers.h"
#include "../terms/termmanager.h"
#include "../parser/flatzincparser.h"

namespace msat {
namespace opt {

size_t fzn_get_sbv_size(int n);
size_t fzn_get_sbv_size(const Number &n);
Term fzn_make_sbv_number(TermManager *mgr, int n, size_t min = 2);
Term fzn_make_sbv_number(TermManager *mgr, const Number &n, size_t min = 2);
Term fzn_make_bv_equal_bits(TermManager *mgr, Term a);
Term fzn_make_bv_equal(TermManager *mgr, Term a, Term b);
Term fzn_make_bv_sle(TermManager *mgr, Term a, Term b);
Term fzn_make_bv_slt(TermManager *mgr, Term a, Term b);
Term fzn_make_bv_add(TermManager *mgr, Term a, Term b);
Term fzn_make_bv_sub(TermManager *mgr, Term a, Term b);
Term fzn_make_bv_mul(TermManager *mgr, Term a, Term b);
Term fzn_make_bv_sdiv(TermManager *mgr, Term a, Term b);
void fzn_make_bv_to_int(TermManager *mgr, TermList &as);


size_t get_sbv_size(Number &n1, Number &n2);

size_t get_sbv_size(TermManager *mgr, Term t1, Term t2);

size_t get_sbv_size(NumFlatZincDomain *dom);

bool extend_bv_width_to(TermManager *mgr, Term &t, size_t value);

size_t make_same_bv_width(TermManager *mgr, Term &t1, Term &t2);

size_t make_same_bv_width(TermManager *mgr, Term &t1, Term &t2, Term &t3);

size_t make_same_bv_width(TermManager *mgr, Term &t1, Term &t2, Term &t3, Term &t4);

size_t make_same_bv_width(TermManager *mgr, TermList &as, Term &c);

size_t make_same_bv_width(TermManager *mgr, TermList &as, TermList &bs, Term &c);


}} // namespace

#endif // FLATZINCBV_H_INCLUDED
