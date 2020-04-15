// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// custom infinite-precision rational numbers, that use plain integers for
// small values, and GMP for big ones
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#include "../utils/numbers.h"
#include "../utils/exception.h"
#include <sstream>
#include <ctype.h>

namespace msat {


#ifndef MATHSAT_REENTRANT
long gcd_cache[GCD_CACHE_SIZE][GCD_CACHE_SIZE];
QNumber::GmpTemporaries QNumber::gmp_tmp;
#endif // MATHSAT_REENTRANT


std::string QNumber::to_str() const
{
    std::ostringstream out;
    out << (*this);
    return out.str();
}


namespace {

bool fast_long_from_str(const char *s, long &out)
{
    out = 0;

    bool neg = (*s == '-');
    if (neg) {
        ++s;
    }

    long maxval = std::numeric_limits<long>::max() / 10;
    long maxdigit = std::numeric_limits<long>::max() % 10;
    if (neg) {
        ++maxdigit; // because abs(LONG_MIN) == abs(LONG_MAX)+1
    }

    while (*s) {
        char c = *s++;
        if (!isdigit(c)) {
            return false; // invalid input
        }
        long digit = c - '0';
        if (out > maxval || (out == maxval && digit > maxdigit)) {
            return false; // overflow
        }
        out *= 10;
        out += digit;
    }

    if (neg) {
        out = -out;
    }

    return true;
}

} // namespace


QNumber QNumber::from_str(const std::string &s)
{
    long l;
    
    if (fast_long_from_str(s.c_str(), l)) {
        return QNumber(l);
    }
    
    try {
        size_t dot = s.find('.');
        size_t exp =
            s.find_first_of("eE", (dot == std::string::npos) ? 0 : dot+1);
        if (dot != std::string::npos || exp != std::string::npos) {
            long e = 0;
            if (exp != std::string::npos) {
                std::istringstream tmp(s.substr(exp+1));
                if (!(tmp >> e)) {
                    throw Exception(
                        "invalid argument to Number::from_str: " + s);
                }
            }
            std::ostringstream tmp;
            size_t len = std::min(s.size(), exp);
            if (dot == std::string::npos) {
                tmp << s.substr(0, len) << "/1" << std::string(len-1, '0');
            } else {
                tmp << s.substr(0, dot) << s.substr(dot+1, len-dot-1) << "/1"
                    << std::string(len-dot-1, '0');
            }
            std::string tmps = tmp.str();
            const char *cs = tmps.c_str();
            mpq_class n(cs, 10);
            if (!sgn(n.get_den())) {
                throw Exception("invalid argument to Number::from_str: " + s);
            }
            if (e != 0) {
                mpz_class p;
                mpz_ui_pow_ui(p.get_mpz_t(), 10, labs(e));
                if (e < 0) {
                    n /= p;
                } else {
                    n *= p;
                }
            }
            n.canonicalize();
            return QNumber(n);
        } else {
            mpq_class n(s.c_str(), 10);
            if (!sgn(n.get_den())) {
                throw Exception("invalid argument to Number::from_str: " + s);
            }
            n.canonicalize();
            return QNumber(n);
        }
    } catch (std::invalid_argument &e) {
        throw Exception("invalid argument to Number::from_str: " + s);
    }
}


} // namespace msat
