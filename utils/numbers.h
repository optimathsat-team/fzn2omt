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
//
// the code is heavily based on boost::rational
// copyright notice of boost::rational
//
//  (C) Copyright Paul Moore 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/rational for documentation.

#ifndef MSAT_NUMBERS_H_INCLUDED
#define MSAT_NUMBERS_H_INCLUDED

#include <stddef.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <assert.h>
#include "../msatconfig.h"

#include <vector>

//#include "memorypool.h"

// if set to true, validate every operation by performing it again with GMP
// and comparing the results
#define QNUMBER_VALIDATE 0

#if QNUMBER_VALIDATE

#define qassert(expr) if (!(expr)) {            \
        std::cout << "NUMBER ERROR!" << std::endl;     \
        assert(false); abort();                 \
    }

#else

#define qassert(expr) 

#endif // QNUMBER_VALIDATE

namespace msat {

inline long gcd_nocache(long a, long b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    long t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

#ifndef MATHSAT_REENTRANT
const int GCD_CACHE_SIZE = 1024;
extern long gcd_cache[GCD_CACHE_SIZE][GCD_CACHE_SIZE];
#endif // MATHSAT_REENTRANT


inline long gcd(long a, long b)
{
#ifdef MATHSAT_REENTRANT
    return gcd_nocache(a, b);
#else // MATHSAT_REENTRANT
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    long t;
    while (b != 0) {
        if (a < GCD_CACHE_SIZE && b < GCD_CACHE_SIZE) {
            if (!gcd_cache[a][b]) {
                gcd_cache[a][b] = gcd_cache[b][a] = gcd_nocache(a, b);
            } else {
                return gcd_cache[a][b];
            }
        }
        t = b;
        b = a % b;
        a = t;
    }
    return a;
#endif // MATHSAT_REENTRANT
}


class QNumber {
    struct Gmp {
        mpz_t num;
        mpz_t den;
        //static ObjectPool<Gmp, true> pool;
        static Gmp *alloc() { return new Gmp; }
        static void free(Gmp *p) { delete p; }
    };
public:
    QNumber()
    {
        num = 0;
        den = 1;
    }

    ~QNumber()
    {
        if (big()) {
            assert(gmp);
            mpz_clear(gmp->num);
            mpz_clear(gmp->den);
            Gmp::free(gmp);
        }
    }

    explicit QNumber(long n)
    {
        num = n;
        den = 1;

        // corner case: if n == INT_MIN, we have to use GMP, because labs(n)
        // will overflow
        fix_int_min();
    }

    QNumber(long n, long d)
    {
        assert(d != 0);
        
        num = n;
        den = d;

        // corner case: if n == INT_MIN, we have to use GMP, because labs(n)
        // will overflow. The same for d
        fix_int_min();
        
        normalize();

#if QNUMBER_VALIDATE
        mpq_class c(n, d);
        c.canonicalize();
        qassert(!big() ? c == mpq_class(num, den) :
                c == mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)));
#endif
    }
    
    explicit QNumber(const mpq_class &n)
    {
        if (n.get_num().fits_sint_p() && n.get_den().fits_sint_p()) {
            num = long(n.get_num().get_si());
            den = long(n.get_den().get_si());
            // corner case: if num == INT_MIN, we have to use GMP, because
            // labs(n) will overflow. The same for den
            fix_int_min();
        } else {
            den = 0;
            gmp = Gmp::alloc();
            mpz_init_set(gmp->num, n.get_num().get_mpz_t());
            mpz_init_set(gmp->den, n.get_den().get_mpz_t());
        }
        normalize();

#if QNUMBER_VALIDATE
        if (!big()) {
            mpq_class c(num, den);
            c.canonicalize();
            qassert(c == n);
        } else {
            mpq_class c(mpz_class(gmp->num), mpz_class(gmp->den));
            c.canonicalize();
            qassert(c == n);
        }
#endif
    }

    QNumber(const mpz_class &n, const mpz_class &d)
    {
        if (n.fits_sint_p() && d.fits_sint_p()) {
            num = long(n.get_si());
            den = long(d.get_si());
            fix_int_min();
        } else {
            den = 0;
            gmp = Gmp::alloc();
            mpz_init_set(gmp->num, n.get_mpz_t());
            mpz_init_set(gmp->den, d.get_mpz_t());
        }
        normalize();

#if QNUMBER_VALIDATE
        if (!big()) {
            mpq_class c1(n, d);
            mpq_class c2(num, den);
            c1.canonicalize();
            qassert(c1 == c2);
        } else {
            mpq_class c(n, d);
            c.canonicalize();
            qassert(c == mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)));
        }
#endif
    }

    QNumber(const QNumber &other)
    {
        if (other.big()) {
            den = 0;
            gmp = Gmp::alloc();
            mpz_init_set(gmp->num, other.gmp->num);
            mpz_init_set(gmp->den, other.gmp->den);
        } else {
            num = other.num;
            den = other.den;
        }
    }

    bool big() const { return !den; }

    QNumber &operator=(const QNumber &other)
    {
        if (this != &other) {
            if (other.big()) {
                if (!big()) {
                    den = 0;
                    gmp = Gmp::alloc();
                    mpz_init(gmp->num);
                    mpz_init(gmp->den);
                }
                mpz_set(gmp->num, other.gmp->num);
                mpz_set(gmp->den, other.gmp->den);
            } else {
                if (big()) {
                    mpz_set_si(gmp->num, other.num);
                    mpz_set_si(gmp->den, other.den);
                } else {
                    num = other.num;
                    den = other.den;
                }
            }
        }
        return *this;
    }

    QNumber &operator=(long n)
    {
        if (big()) {
            mpz_set_si(gmp->num, n);
            mpz_set_si(gmp->den, 1);
        } else {
            num = n;
            den = 1;
            fix_int_min();
        }
        return *this;
    }
    
    // Arithmetic assignment operators
    QNumber& operator+=(const QNumber& r);
    QNumber& operator-=(const QNumber& r);
    QNumber& operator*=(const QNumber& r);
    QNumber& operator/=(const QNumber& r);

    QNumber& operator+=(long i);
    QNumber& operator-=(long i);
    QNumber& operator*=(long i);
    QNumber& operator/=(long i);

    friend bool operator<(const QNumber &a, const QNumber &b);
    friend bool operator==(const QNumber &a, const QNumber &b);

    friend QNumber operator-(const QNumber &r);

    friend std::ostream &operator<<(std::ostream &out, const QNumber &n);

    QNumber inv() const;
    QNumber neg() const;
    QNumber &self_neg();
    // like *this += a * b, but faster
    QNumber &self_addmul(const QNumber &a, const QNumber &b);
    friend QNumber abs(const QNumber &n);
    friend int sgn(const QNumber &n);
    friend int cmp(const QNumber &a, const QNumber &b);

    bool is_integer() const { return big() ? is_int_big() : is_int_normal(); }
    ///< checks whether this number is an integer

    bool to_int(int &out_value) const;
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2016-09-01 (p.t.): lemma lifting support
    bool to_int(long &out_value) const;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ///< like the above, but checks only for machine-native integers,
    ///< returning their value

    QNumber floor() const;
    ///< returns an integer c s.t. (c <= *this < c+1)

    bool fits(size_t num_bits) const;
    ///< returns true if *this can be represented with the given number of bits.
    ///< Precondition: is_integer() && *this >= 0

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2016-09-01 (p.t.): lemma lifting support
    size_t required_bits() const;
    ///< returns a number of bits that can hold the signed representation
    ///< of this number.
    ///< Precondition: is_integer() && *this >= 0
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    QNumber get_num() const;
    QNumber get_den() const;

    bool divides(const QNumber &other) const;
    void divmod(const QNumber &other, QNumber &q, QNumber &r) const;

    QNumber pow(unsigned int n) const; // returns (*this)^n

    // splits this fraction into a sum of an integer z and a fraction q
    // s.t. |q| < 1. the splitting is performed by taking as z the quotient of
    // the division between the numerator and the denominator, and as q the
    // ratio remainder/denominator.  returns false if z is set to zero
    // (indicating that no decomposition took place), true otherwise
    bool decompose(QNumber &z, QNumber &q);
    // as above, but modifies *this in place, setting it to q and returning z
    QNumber self_decompose();

    friend QNumber gcd(const QNumber &a, const QNumber &b);
    friend QNumber lcm(const QNumber &a, const QNumber &b);

    mpq_class to_mpq() const;

    size_t hash() const;

    std::string to_str() const;
    static QNumber from_str(const std::string &s);
    static QNumber pow2(size_t n); // returns 2^n
    
private:
    QNumber(const mpz_t n, const mpz_t d, bool b)
    {
        assert(b);
        den = 0;
        gmp = Gmp::alloc();
        mpz_init_set(gmp->num, n);
        mpz_init_set(gmp->den, d);
        normalize();
#if QNUMBER_VALIDATE
        mpq_class c = mpq_class(mpz_class(n), mpz_class(d));
        c.canonicalize();
        qassert(c == mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)));
#endif
    }

    // fixes the following corner case: if num.normal or den.normal is
    // INT_MIN, we have to use GMP, because labs() will overflow. Returns true
    // if the fix was applied
    bool fix_int_min()
    {
        assert(!big());
        if (num == std::numeric_limits<long>::min() ||
            den == std::numeric_limits<long>::min()) {
            long n = num, d = den;
            den = 0;
            gmp = Gmp::alloc();
            mpz_init_set_si(gmp->num, n);
            mpz_init_set_si(gmp->den, d);
            return true;
        }
        return false;
    }

    bool is_int_big() const { return mpz_cmp_si(gmp->den, 1) == 0; }
    bool is_int_normal() const { return den == 1; }
    
    static bool add_overflow(long &res, long a, long b);
    static bool sub_overflow(long &res, long a, long b);
    static bool mul_overflow(long &res, long a, long b);
    static bool div_overflow(long &res, long a, long b);

    static const size_t NUM_BITS_NORMAL = sizeof(long) * 8;

    // Implementation - numerator and denominator (normalized).  we keep both
    // in unions: if the values are small, we use plain integers, otherwise we
    // switch to GMP
    union {
        long num;
        Gmp *gmp;
    };
    long den;

    // Representation note: Fractions are kept in normalized form at all
    // times. normalized form is defined as gcd(num,den) == 1 and den > 0.
    void normalize();

    void make_big()
    {
        assert(!big());
        long n = num, d = den;
        den = 0;
        gmp = Gmp::alloc();
        mpz_init_set_si(gmp->num, n);
        mpz_init_set_si(gmp->den, d);        
    }

public:
#ifndef MATHSAT_REENTRANT
    struct GmpTemporaries {
        mpz_t tmp1, tmp2, tmp3, tmp4;

        GmpTemporaries()
        {
            mpz_init(tmp1);
            mpz_init(tmp2);
            mpz_init(tmp3);
            mpz_init(tmp4);
        }

        ~GmpTemporaries()
        {
            mpz_clear(tmp4);
            mpz_clear(tmp3);
            mpz_clear(tmp2);
            mpz_clear(tmp1);
        }
    };

    static GmpTemporaries gmp_tmp;
    
#else // MATHSAT_REENTRANT
    class GmpTmpCleaner {
    public:
        GmpTmpCleaner(mpz_t &n): num(n) {}
        ~GmpTmpCleaner() { mpz_clear(num); }
    private:
        mpz_t &num;
    };
#endif // MATHSAT_REENTRANT

    friend class BVNumber;
};


#ifndef MATHSAT_REENTRANT
#  define MSAT_GET_GMPTMP(name, num)            \
    mpz_t &name = msat::Number::gmp_tmp.tmp ## num;
#else // MATHSAT_REENTRANT
#  define MSAT_GET_GMPTMP(name, num)                                    \
    mpz_t name;                                                         \
    mpz_init(name);                                                     \
    msat::Number::GmpTmpCleaner name ## __cleaner__ ## num (name);      
#endif // MATHSAT_REENTRANT


typedef QNumber Number;

inline
QNumber operator-(const QNumber &r)
{
    return r.neg();
}


// Arithmetic assignment operators
inline
QNumber &QNumber::operator+=(const QNumber &r)
{
    // This calculation avoids overflow, and minimises the number of expensive
    // calculations. Thanks to Nickolay Mladenov for this algorithm.
    //
    // Proof:
    // We have to compute a/b + c/d, where gcd(a,b)=1 and gcd(b,c)=1.
    // Let g = gcd(b,d), and b = b1*g, d=d1*g. Then gcd(b1,d1)=1
    //
    // The result is (a*d1 + c*b1) / (b1*d1*g).
    // Now we have to normalize this ratio.
    // Let's assume h | gcd((a*d1 + c*b1), (b1*d1*g)), and h > 1
    // If h | b1 then gcd(h,d1)=1 and hence h|(a*d1+c*b1) => h|a.
    // But since gcd(a,b1)=1 we have h=1.
    // Similarly h|d1 leads to h=1.
    // So we have that h | gcd((a*d1 + c*b1) , (b1*d1*g)) => h|g
    // Finally we have gcd((a*d1 + c*b1), (b1*d1*g)) = gcd((a*d1 + c*b1), g)
    // Which proves that instead of normalizing the result, it is better to
    // divide num and den by gcd((a*d1 + c*b1), g)
    //
    // ORIGINAL ALGORITHM:
//     // Protect against self-modification
//     IntType r_num = r.num;
//     IntType r_den = r.den;

//     IntType g = gcd(den, r_den);
//     den /= g;  // = b1 from the calculations above
//     num = num * (r_den / g) + r_num * den;
//     g = gcd(num, g);
//     num /= g;
//     den *= r_den/g;

//     return *this;
    

    if (!big() && !r.big()) {
#if QNUMBER_VALIDATE
        mpq_class c1(num, den);
        mpq_class c2(r.num, r.den);
#endif

        // should be pretty fast if both are integers...
        if (is_int_normal() && r.is_int_normal()) {
            if (add_overflow(num, num, r.num)) {
                goto add_big;
            }
            return *this;
        }
                     
        // Protect against self-modification
        long r_num = r.num;
        long r_den = r.den;

        long s_num = num;
        long s_den = den;

        long g = gcd(s_den, r_den);
        if (!div_overflow(s_den, s_den, g)) {
            // = b1 from the calculations above
            long tmp1, tmp2;
            if (div_overflow(tmp1, r_den, g)) goto add_big;
            if (mul_overflow(tmp2, r_num, s_den)) goto add_big;
            if (mul_overflow(tmp1, tmp1, s_num)) goto add_big;
            if (add_overflow(s_num, tmp1, tmp2)) goto add_big;
            // now: num = num * (r_den / g) + r_num * den;
            g = gcd(s_num, g);
            if (div_overflow(s_num, s_num, g)) goto add_big;
            // now: num /= g;
            if (div_overflow(tmp1, r_den, g)) goto add_big;
            if (mul_overflow(s_den, s_den, tmp1)) goto add_big;
            // now: den *= r_den/g;
            num = s_num;
            den = s_den;
        } else {
            goto add_big;
        }

        qassert(mpq_class(num, den) == c1 + c2);
        
        return *this;
    }

    // fallback case - convert to GMP and do the addition there...
  add_big:
    if (!big()) {
        make_big();
    }
    if (!r.big()) {
#if QNUMBER_VALIDATE
        mpq_class c1(mpz_class(gmp->num), mpz_class(gmp->den));
        mpq_class c2(r.num, r.den);
#endif
        if (r.is_int_normal() && is_int_big()) {
            if (r.num >= 0) {
                mpz_add_ui(gmp->num, gmp->num,
                           static_cast<unsigned long>(r.num));
            } else {
                mpz_sub_ui(gmp->num, gmp->num,
                           static_cast<unsigned long>(-r.num));
            }
            qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) ==
                    c1 + c2);
            return *this;
        }
            
        long r_num = r.num;
        long r_den = r.den;
        //mpz_t &bg = gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(bg, 1);
        unsigned long g =
            static_cast<unsigned long>(mpz_gcd_ui(bg, gmp->den, labs(r_den)));
        mpz_divexact(gmp->den, gmp->den, bg); // = b1 from the calculations
                                              // above
        //mpz_t &tmp = gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(tmp, 2);
        mpz_mul_si(gmp->num, gmp->num, r_den/static_cast<long>(g));
        mpz_mul_si(tmp, gmp->den, r_num);
        mpz_add(gmp->num, gmp->num, tmp);
        g = static_cast<unsigned long>(mpz_gcd_ui(bg, gmp->num, g));
        mpz_divexact(gmp->num, gmp->num, bg);
        mpz_mul_si(gmp->den, gmp->den, r_den/static_cast<long>(g));

        qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) == c1 + c2);
    } else {
#if QNUMBER_VALIDATE
        mpq_class c1(mpz_class(gmp->num), mpz_class(gmp->den));
        mpq_class c2(mpz_class(r.gmp->num), mpz_class(r.gmp->den));
#endif
        if (is_int_big() && r.is_int_big()) {
            mpz_add(gmp->num, gmp->num, r.gmp->num);
            qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) ==
                    c1 + c2);
            return *this;
        }
        
        //mpz_t &r_num = gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(r_num, 1);
        //mpz_t &r_den = gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(r_den, 2);
        mpz_set(r_num, r.gmp->num);
        mpz_set(r_den, r.gmp->den);
        //mpz_t &g = gmp_tmp.tmp3;
        MSAT_GET_GMPTMP(g, 3);
        mpz_gcd(g, gmp->den, r_den);
        mpz_divexact(gmp->den, gmp->den, g);
        //mpz_t &tmp = gmp_tmp.tmp4;
        MSAT_GET_GMPTMP(tmp, 4);
        mpz_divexact(tmp, r_den, g);
        mpz_mul(gmp->num, gmp->num, tmp);
        mpz_mul(r_num, r_num, gmp->den);
        mpz_add(gmp->num, gmp->num, r_num);
        mpz_gcd(g, gmp->num, g);
        mpz_divexact(gmp->num, gmp->num, g);
        mpz_divexact(r_den, r_den, g);
        mpz_mul(gmp->den, gmp->den, r_den);

        qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) == c1 + c2);
    }

    return *this;
}


inline
QNumber &QNumber::operator-=(const QNumber &r)
{
    // ORIGINAL ALGORITHM - this is the same as += (with - where appropriate...)
//     // Protect against self-modification
//     IntType r_num = r.num;
//     IntType r_den = r.den;

//     // This calculation avoids overflow, and minimises the number of expensive
//     // calculations. It corresponds exactly to the += case above
//     IntType g = gcd(den, r_den);
//     den /= g;
//     num = num * (r_den / g) - r_num * den;
//     g = gcd(num, g);
//     num /= g;
//     den *= r_den/g;

//     return *this;

    if (!big() && !r.big()) {
#if QNUMBER_VALIDATE
        mpq_class c1(num, den);
        mpq_class c2(r.num, r.den);
#endif

        // should be pretty fast if both are integers...
        if (is_int_normal() && r.is_int_normal()) {
            if (sub_overflow(num, num, r.num)) {
                goto sub_big;
            }
            return *this;
        }
                     
        // Protect against self-modification
        long r_num = r.num;
        long r_den = r.den;

        long s_num = num;
        long s_den = den;

        long g = gcd(s_den, r_den);
        if (!div_overflow(s_den, s_den, g)) {
            // = b1 from the calculations above
            long tmp1, tmp2;
            if (div_overflow(tmp1, r_den, g)) goto sub_big;
            if (mul_overflow(tmp2, r_num, s_den)) goto sub_big;
            if (mul_overflow(tmp1, tmp1, s_num)) goto sub_big;
            if (sub_overflow(s_num, tmp1, tmp2)) goto sub_big;
            // now: num = num * (r_den / g) - r_num * den;
            g = gcd(s_num, g);
            if (div_overflow(s_num, s_num, g)) goto sub_big;
            // now: num /= g;
            if (div_overflow(tmp1, r_den, g)) goto sub_big;
            if (mul_overflow(s_den, s_den, tmp1)) goto sub_big;
            // now: den *= r_den/g;
            num = s_num;
            den = s_den;
        } else {
            goto sub_big;
        }

        qassert(mpq_class(num, den) == c1 - c2);
        
        return *this;
    }

    // fallback case - convert to GMP and do the addition there...
  sub_big:
    if (!big()) {
        make_big();
    }
    if (!r.big()) {
#if QNUMBER_VALIDATE
        mpq_class c1(mpz_class(gmp->num), mpz_class(gmp->den));
        mpq_class c2(r.num, r.den);
#endif
        if (r.is_int_normal() && is_int_big()) {
            if (r.num >= 0) {
                mpz_sub_ui(gmp->num, gmp->num,
                           static_cast<unsigned long>(r.num));
            } else {
                mpz_add_ui(gmp->num, gmp->num,
                           static_cast<unsigned long>(-r.num));
            }
            qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) ==
                    c1 - c2);
            return *this;
        }
            
        long r_num = r.num;
        long r_den = r.den;
        //mpz_t &bg = gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(bg, 1);
        unsigned long g =
            static_cast<unsigned long>(mpz_gcd_ui(bg, gmp->den, labs(r_den)));
        mpz_divexact(gmp->den, gmp->den, bg); // = b1 from the calculations
                                              // above
        //mpz_t &tmp = gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(tmp, 2);
        mpz_mul_si(gmp->num, gmp->num, r_den/static_cast<long>(g));
        mpz_mul_si(tmp, gmp->den, r_num);
        mpz_sub(gmp->num, gmp->num, tmp);
        g = static_cast<unsigned long>(mpz_gcd_ui(bg, gmp->num, g));
        mpz_divexact(gmp->num, gmp->num, bg);
        mpz_mul_si(gmp->den, gmp->den, r_den/static_cast<long>(g));

        qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) == c1 - c2);
    } else {
#if QNUMBER_VALIDATE
        mpq_class c1(mpz_class(gmp->num), mpz_class(gmp->den));
        mpq_class c2(mpz_class(r.gmp->num), mpz_class(r.gmp->den));
#endif
        if (is_int_big() && r.is_int_big()) {
            mpz_sub(gmp->num, gmp->num, r.gmp->num);
            qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) ==
                    c1 - c2);
            return *this;
        }
        
        //mpz_t &r_num = gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(r_num, 1);
        //mpz_t &r_den = gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(r_den, 2);
        mpz_set(r_num, r.gmp->num);
        mpz_set(r_den, r.gmp->den);
        //mpz_t &g = gmp_tmp.tmp3;
        MSAT_GET_GMPTMP(g, 3);
        mpz_gcd(g, gmp->den, r_den);
        mpz_divexact(gmp->den, gmp->den, g);
        //mpz_t &tmp = gmp_tmp.tmp4;
        MSAT_GET_GMPTMP(tmp, 4);
        mpz_divexact(tmp, r_den, g);
        mpz_mul(gmp->num, gmp->num, tmp);
        mpz_mul(r_num, r_num, gmp->den);
        mpz_sub(gmp->num, gmp->num, r_num);
        mpz_gcd(g, gmp->num, g);
        mpz_divexact(gmp->num, gmp->num, g);
        mpz_divexact(r_den, r_den, g);
        mpz_mul(gmp->den, gmp->den, r_den);

        qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) == c1 - c2);
    }

    return *this;
}


inline
QNumber &QNumber::operator*=(const QNumber &r)
{
    // ORIGINAL ALGORITHM:
//     // Protect against self-modification
//     IntType r_num = r.num;
//     IntType r_den = r.den;

//     // Avoid overflow and preserve normalization
//     IntType gcd1 = gcd<IntType>(num, r_den);
//     IntType gcd2 = gcd<IntType>(r_num, den);
//     num = (num/gcd1) * (r_num/gcd2);
//     den = (den/gcd2) * (r_den/gcd1);

//     return *this;

    if (!big() && !r.big()) {
#if QNUMBER_VALIDATE
        mpq_class c1(num, den);
        mpq_class c2(r.num, r.den);
#endif

        if (is_int_normal() && r.is_int_normal()) {
            if (mul_overflow(num, num, r.num)) {
                goto mul_big;
            }
            return *this;
        }
        
        // Protect against self-modification
        long r_num = r.num;
        long r_den = r.den;

        long s_num = num;
        long s_den = den;

        // Avoid overflow and preserve normalization
        long gcd1 = gcd(s_num, r_den);
        long gcd2 = gcd(r_num, s_den);

        long tmp;
        if (div_overflow(tmp, s_num, gcd1)) goto mul_big;
        if (div_overflow(r_num, r_num, gcd2)) goto mul_big;
        if (mul_overflow(s_num, tmp, r_num)) goto mul_big;
        // num = (num/gcd1) * (r_num/gcd2);
        if (div_overflow(tmp, s_den, gcd2)) goto mul_big;
        if (div_overflow(r_den, r_den, gcd1)) goto mul_big;
        if (mul_overflow(s_den, tmp, r_den)) goto mul_big;
        // den = (den/gcd2) * (r_den/gcd1);

        num = s_num;
        den = s_den;
        
        qassert(mpq_class(num, den) == c1 * c2);
        
        return *this;
    }
  mul_big:
    
    if (!big()) {
        make_big();
    }
    if (!r.big()) {
#if QNUMBER_VALIDATE
        mpq_class c1(mpz_class(gmp->num), mpz_class(gmp->den));
        mpq_class c2(r.num, r.den);
#endif

        if (r.is_int_normal() && is_int_big()) {
            mpz_mul_si(gmp->num, gmp->num, r.num);
            qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) ==
                    c1 * c2);
            return *this;
        }
        
        long r_num = r.num;
        long r_den = r.den;

        if (!r_num) {
            // multiplication by zero, easy (we can't use the general case
            // because of this: if labs(r_num) is zero and den.big is indeed
            // big, mpz_gcd_ui will return zero. If we let this go, we will
            // get a division by zero later on...
            mpz_clear(gmp->num);
            mpz_clear(gmp->den);
            Gmp::free(gmp);
            num = 0;
            den = 1;
            qassert(mpq_class(num, den) == c1 * c2);
//             mpz_set_si(num.big, 0);
//             mpz_set_si(den.big, 1);
//             qassert(mpq_class(mpz_class(num.big), mpz_class(den.big)) ==
//                     c1 * c2);
            return *this;
        }

        //mpz_t &g1 = gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(g1, 1);
        //mpz_t &g2 = gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(g2, 2);
        unsigned long gcd1 =
            static_cast<unsigned long>(mpz_gcd_ui(g1, gmp->num, labs(r_den)));
        unsigned long gcd2 =
            static_cast<unsigned long>(mpz_gcd_ui(g2, gmp->den, labs(r_num)));
        mpz_divexact_ui(gmp->num, gmp->num, gcd1);
        mpz_mul_si(gmp->num, gmp->num, r_num/static_cast<long>(gcd2));
        mpz_divexact_ui(gmp->den, gmp->den, gcd2);
        mpz_mul_si(gmp->den, gmp->den, r_den/static_cast<long>(gcd1));

        qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) == c1 * c2);
    } else {
#if QNUMBER_VALIDATE
        mpq_class c1(mpz_class(gmp->num), mpz_class(gmp->den));
        mpq_class c2(mpz_class(r.gmp->num), mpz_class(r.gmp->den));
#endif

        if (is_int_big() && r.is_int_big()) {
            mpz_mul(gmp->num, gmp->num, r.gmp->num);
            qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) ==
                    c1 * c2);
            return *this;
        }
        
        //mpz_t &r_num = gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(r_num, 1);
        //mpz_t &r_den = gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(r_den, 2);
        mpz_set(r_num, r.gmp->num);
        mpz_set(r_den, r.gmp->den);
        //mpz_t &gcd1 = gmp_tmp.tmp3;
        MSAT_GET_GMPTMP(gcd1, 3);
        //mpz_t &gcd2 = gmp_tmp.tmp4;
        MSAT_GET_GMPTMP(gcd2, 4);
        mpz_gcd(gcd1, gmp->num, r_den);
        mpz_gcd(gcd2, r_num, gmp->den);
        mpz_divexact(gmp->num, gmp->num, gcd1);
        mpz_divexact(r_num, r_num, gcd2);
        mpz_mul(gmp->num, gmp->num, r_num);
        mpz_divexact(gmp->den, gmp->den, gcd2);
        mpz_divexact(r_den, r_den, gcd1);
        mpz_mul(gmp->den, gmp->den, r_den);

        qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) == c1 * c2);
    }

    return *this;
}


inline
QNumber &QNumber::operator/=(const QNumber & r)
{
    if (!r.big()) {
        return (*this *= QNumber(r.den, r.num));
    } else {
        return (*this *= QNumber(r.gmp->den, r.gmp->num, true));
    }
//     // Protect against self-modification
//     IntType r_num = r.num;
//     IntType r_den = r.den;

//     // Avoid repeated construction
//     IntType zero(0);

//     // Trap division by zero
//     if (r_num == zero)
//         throw bad_QNumber();
//     if (num == zero)
//         return *this;

//     // Avoid overflow and preserve normalization
//     IntType gcd1 = gcd<IntType>(num, r_num);
//     IntType gcd2 = gcd<IntType>(r_den, den);
//     num = (num/gcd1) * (r_den/gcd2);
//     den = (den/gcd2) * (r_num/gcd1);

//     if (den < zero) {
//         num = -num;
//         den = -den;
//     }
//     return *this;
}

// Mixed-mode operators
inline
QNumber &QNumber::operator+=(long i)
{
    return operator+=(QNumber(i));
}

inline
QNumber &QNumber::operator-=(long i)
{
    return operator-=(QNumber(i));
}

inline
QNumber &QNumber::operator*=(long i)
{
    return operator*=(QNumber(i));
}

inline
QNumber &QNumber::operator/=(long i)
{
    return operator/=(QNumber(i));
}


// Comparison operators
inline
bool operator<(const QNumber &n, const QNumber &r)
{
//    std::cout << n << " < " << r << ": ";
    
    if (!n.big() && !r.big()) {
        // If the two values have different signs, we don't need to do the
        // expensive calculations below. We take advantage here of the fact
        // that the denominator is always positive.
        if (n.num < 0 && r.num >= 0) { // -ve < +ve
//            std::cout << "yes" << std::endl;
            qassert(mpq_class(n.num, n.den) < mpq_class(r.num, r.den));
            return true;
        }
        if (n.num >= 0 && r.num <= 0) {
            // +ve or zero is not < -ve or zero
//            std::cout << "no" << std::endl;
            qassert(!(mpq_class(n.num, n.den) < mpq_class(r.num, r.den)));
            return false;
        }

        if (n.is_int_normal() && r.is_int_normal()) {
            return n.num < r.num;
        }
        
        // Try to avoid overflow
        long gcd1 = gcd(n.num, r.num);
        long gcd2 = gcd(r.den, n.den);
        bool ret;
        if (sizeof(long long) == sizeof(long) * 2) {
            // we *have to* cast to long long here, because the multiplication
            // might overflow...
            ret = ((long long)(n.num/gcd1) * (long long)(r.den/gcd2) <
                   (long long)(n.den/gcd2) * (long long)(r.num/gcd1));
        } else {
            // on 64-bits, we use the safe multiplication
            long tmp1, tmp2;
            long d1 = n.num/gcd1, d2 = r.den/gcd2;
            long d3 = n.den/gcd2, d4 = r.num/gcd1;
            if (!QNumber::mul_overflow(tmp1, d1, d2) &&
                !QNumber::mul_overflow(tmp2, d3, d4)) {
                ret = tmp1 < tmp2;
            } else {
                // convert to mpz and do the comparison there
                //mpz_t &mp_tmp1 = QNumber::gmp_tmp.tmp1;
                MSAT_GET_GMPTMP(mp_tmp1, 1);
                //mpz_t &mp_tmp2 = QNumber::gmp_tmp.tmp2;
                MSAT_GET_GMPTMP(mp_tmp2, 2);
                mpz_set_si(mp_tmp1, d1);
                mpz_mul_si(mp_tmp1, mp_tmp1, d2);
                mpz_set_si(mp_tmp2, d3);
                mpz_mul_si(mp_tmp2, mp_tmp2, d4);
                ret = (mpz_cmp(mp_tmp1, mp_tmp2) < 0);
            }
        }
        qassert((mpq_class(n.num, n.den) < mpq_class(r.num, r.den)) == ret);
        return ret;
    } else if (!r.big()) {
        int num_sgn = mpz_sgn(n.gmp->num);
        if (num_sgn < 0 && r.num >= 0) {
            qassert(mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den)) <
                    mpq_class(r.num, r.den));
            return true;
        }
        if (num_sgn >= 0 && r.num <= 0) {
            qassert(!(mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den)) <
                      mpq_class(r.num, r.den)));
            return false;
        }

        if (r.is_int_normal() && n.is_int_big()) {
            return mpz_cmp_si(n.gmp->num, r.num) < 0;
        }

        if (!r.num) {
            // comparison with zero, easy (we can't use the general case
            // because of this: if labs(r.num.normal) is zero and n.num.big is
            // indeed big, mpz_gcd_ui will return zero. If we let this go, we
            // will get a division by zero later on...
            return mpz_sgn(n.gmp->num) < 0;
        }

        //mpz_t &tmp = QNumber::gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(tmp, 1);
        unsigned long gcd1 =
            static_cast<unsigned long>(mpz_gcd_ui(tmp, n.gmp->num,labs(r.num)));
        unsigned long gcd2 =
            static_cast<unsigned long>(mpz_gcd_ui(tmp, n.gmp->den,labs(r.den)));
        //mpz_t &tmp2 = QNumber::gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(tmp2, 2);
        mpz_divexact_ui(tmp, n.gmp->num, gcd1);
        mpz_mul_si(tmp, tmp, r.den/static_cast<long>(gcd2));
        mpz_divexact_ui(tmp2, n.gmp->den, gcd2);
        mpz_mul_si(tmp2, tmp2, r.num/static_cast<long>(gcd1));
        int ret = mpz_cmp(tmp, tmp2);

        qassert((mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den)) <
                 mpq_class(r.num, r.den)) == (ret < 0));
        
        return ret < 0;
    } else if (!n.big()) {
        int r_num_sgn = mpz_sgn(r.gmp->num);
        if (n.num < 0 && r_num_sgn >= 0) {
            qassert(mpq_class(n.num, n.den) <
                    mpq_class(mpz_class(r.gmp->num), mpz_class(r.gmp->den)));
            return true;
        }
        if (n.num >= 0 && r_num_sgn <= 0) {
            qassert(!(mpq_class(n.num, n.den) <
                      mpq_class(mpz_class(r.gmp->num), mpz_class(r.gmp->den))));
            return false;
        }

        if (n.is_int_normal() && r.is_int_big()) {
            return mpz_cmp_si(r.gmp->num, n.num) > 0;
        }

        if (!n.num) {
            // comparison with zero, easy (we can't use the general case
            // because of this: if labs(r.num.normal) is zero and n.num.big is
            // indeed big, mpz_gcd_ui will return zero. If we let this go, we
            // will get a division by zero later on...
            return mpz_sgn(r.gmp->num) > 0;
        }

        //mpz_t &tmp = QNumber::gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(tmp, 1);
        unsigned long gcd1 =
            static_cast<unsigned long>(mpz_gcd_ui(tmp, r.gmp->num,labs(n.num)));
        unsigned long gcd2 =
            static_cast<unsigned long>(mpz_gcd_ui(tmp, r.gmp->den,labs(n.den)));
        //mpz_t &tmp2 = QNumber::gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(tmp2, 2);
        mpz_divexact_ui(tmp, r.gmp->den, gcd2);
        mpz_mul_si(tmp, tmp, n.num/static_cast<long>(gcd1));
        mpz_divexact_ui(tmp2, r.gmp->num, gcd1);
        mpz_mul_si(tmp2, tmp2, n.den/static_cast<long>(gcd2));
        int ret = mpz_cmp(tmp, tmp2);

        qassert((mpq_class(n.num, n.den) <
                 mpq_class(mpz_class(r.gmp->num), mpz_class(r.gmp->den))) ==
                (ret < 0));
        
        return ret < 0;
    } else {
        int n_num_sgn = mpz_sgn(n.gmp->num);
        int r_num_sgn = mpz_sgn(r.gmp->num);
        if (n_num_sgn < 0 && r_num_sgn >= 0) {
            qassert(mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den)) <
                    mpq_class(mpz_class(r.gmp->num), mpz_class(r.gmp->den)));
            return true;
        }
        if (n_num_sgn >= 0 && r_num_sgn <= 0) {
            qassert(!(mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den)) <
                      mpq_class(mpz_class(r.gmp->num), mpz_class(r.gmp->den))));
            return false;
        }

        if (n.is_int_big() && r.is_int_big()) {
            return mpz_cmp(n.gmp->num, r.gmp->num) < 0;
        }

        //mpz_t &gcd1 = QNumber::gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(gcd1, 1);
        //mpz_t &gcd2 = QNumber::gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(gcd2, 2);
        //mpz_t &tmp1 = QNumber::gmp_tmp.tmp3;
        MSAT_GET_GMPTMP(tmp1, 3);
        //mpz_t &tmp2 = QNumber::gmp_tmp.tmp4;
        MSAT_GET_GMPTMP(tmp2, 4);
        
        mpz_gcd(gcd1, n.gmp->num, r.gmp->num);
        mpz_gcd(gcd2, r.gmp->den, n.gmp->den);
        mpz_divexact(tmp1, n.gmp->num, gcd1);
        mpz_divexact(tmp2, r.gmp->den, gcd2);
        mpz_mul(tmp1, tmp1, tmp2);
        mpz_divexact(tmp2, n.gmp->den, gcd2);
        mpz_divexact(gcd2, r.gmp->num, gcd1);
        mpz_mul(tmp2, tmp2, gcd2);

        int ret = mpz_cmp(tmp1, tmp2);
                
        qassert((mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den)) <
                 mpq_class(mpz_class(r.gmp->num), mpz_class(r.gmp->den))) ==
                (ret < 0));
        
        return ret < 0;
    }
}


inline
bool operator==(const QNumber &n, const QNumber &r)
{
    if (!n.big() && !r.big()) {
        return ((n.num == r.num) && (n.den == r.den));
    } else if (!n.big()) {
        return (!mpz_cmp_si(r.gmp->num, n.num) &&
                !mpz_cmp_si(r.gmp->den, n.den));
    } else if (!r.big()) {
        return (!mpz_cmp_si(n.gmp->num, r.num) &&
                !mpz_cmp_si(n.gmp->den, r.den));
    } else {
        return (!mpz_cmp(n.gmp->num, r.gmp->num) &&
                !mpz_cmp(n.gmp->den, r.gmp->den));
    }
}


inline
std::ostream &operator<<(std::ostream &out, const QNumber &n)
{
    if (!n.big()) {
        if (n.den != 1) {
            return (out << n.num << "/" << n.den);
        } else {
            return (out << n.num);
        }
    } else {
        char *nn = mpz_get_str(NULL, 10, n.gmp->num);
        if (mpz_cmp_si(n.gmp->den, 1) != 0) {
            char *dd = mpz_get_str(NULL, 10, n.gmp->den);
            out << nn << "/" << dd;
            free(dd);
        } else {
            out << nn;
        }
        free(nn);
        return out;
    }
}


inline
QNumber QNumber::inv() const
{
    if (!big()) {
        return QNumber(den, num);
    } else {
        QNumber ret(gmp->den, gmp->num, true);
        ret.normalize();

        qassert(mpq_class(mpz_class(gmp->num), mpz_class(gmp->den)) ==
                1/mpq_class(mpz_class(ret.gmp->num), mpz_class(ret.gmp->den)));
        
        return ret;
    }
}


inline
QNumber &QNumber::self_neg()
{
    if (!big()) {
        if (num == std::numeric_limits<long>::min()) {
            // this overflows!
            make_big();
            mpz_neg(gmp->num, gmp->num);
        } else {
            num = -num;
        }
    } else {
        mpz_neg(gmp->num, gmp->num);
    }
    return *this;
}


inline
QNumber QNumber::neg() const
{
    QNumber ret(*this);
    return ret.self_neg();
}


// derived operations

inline
QNumber operator+(const QNumber &a, const QNumber &b)
{ return QNumber(a) += b; }
inline
QNumber operator+(const QNumber &a, long b)
{ return QNumber(a) += b; }
inline
QNumber operator+(long a, const QNumber &b)
{ return QNumber(a) += b; }

inline
QNumber operator-(const QNumber &a, const QNumber &b)
{ return QNumber(a) -= b; }
inline
QNumber operator-(const QNumber &a, long b)
{ return QNumber(a) -= b; }
inline
QNumber operator-(long a, const QNumber &b)
{ return QNumber(a) -= b; }

inline
QNumber operator*(const QNumber &a, const QNumber &b)
{ return QNumber(a) *= b; }
inline
QNumber operator*(const QNumber &a, long b)
{ return QNumber(a) *= b; }
inline
QNumber operator*(long a, const QNumber &b)
{ return QNumber(a) *= b; }

inline
QNumber operator/(const QNumber &a, const QNumber &b)
{ return QNumber(a) /= b; }
inline
QNumber operator/(const QNumber &a, long b)
{ return QNumber(a) /= b; }
inline
QNumber operator/(long a, const QNumber &b)
{ return QNumber(a) /= b; }


inline bool operator<(long a, const QNumber &b) { return QNumber(a) < b; }
inline bool operator<(const QNumber &a, long b) { return a < QNumber(b); }
inline bool operator>(const QNumber &a, const QNumber &b) { return b < a; }
inline bool operator>(long a, const QNumber &b) { return b < a; }
inline bool operator>(const QNumber &a, long b) { return b < a; }
inline bool operator==(long a, const QNumber &b) { return QNumber(a) == b; }
inline bool operator==(const QNumber &a, long b) { return QNumber(b) == a; }
inline bool operator==(int a, const QNumber &b) { return QNumber(a) == b; }
inline bool operator==(const QNumber &a, int b) { return QNumber(b) == a; }

inline bool operator<=(const QNumber &a, const QNumber &b)
{ return a == b || a < b; }
inline bool operator<=(long a, const QNumber &b)
{ return a == b || b > a; }
inline bool operator<=(const QNumber &a, long b)
{ return a == b || a < b; }

inline bool operator>=(const QNumber &a, const QNumber &b)
{ return a == b || a > b; }
inline bool operator>=(long a, const QNumber &b)
{ return a == b || a > b; }
inline bool operator>=(const QNumber &a, long b)
{ return a == b || a > b; }

inline bool operator!=(const QNumber &a, const QNumber &b) { return !(a == b); }
inline bool operator!=(long a, const QNumber &b) { return !(a == b); }
inline bool operator!=(const QNumber &a, long b) { return !(a == b); }


inline
QNumber abs(const QNumber &n)
{
    if (!n.big()) {
        QNumber ret(labs(n.num), n.den);
        qassert(abs(mpq_class(n.num, n.den)) == mpq_class(ret.num, ret.den));
        return ret;
    } else {
        QNumber ret(n.gmp->num, n.gmp->den, true);
        mpz_abs(ret.gmp->num, ret.gmp->num);

        qassert(abs(mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den))) ==
                mpq_class(mpz_class(ret.gmp->num), mpz_class(ret.gmp->den)));
        
        return ret;
    }
}


inline
int sgn(const QNumber &n)
{
    if (!n.big()) {
        int ret = (n.num < 0) ? -1 : (n.num > 0);
        qassert(ret == sgn(mpq_class(n.num, n.den)));
        return ret;
    } else {
        int ret = mpz_sgn(n.gmp->num);

        qassert(ret ==
                sgn(mpq_class(mpz_class(n.gmp->num), mpz_class(n.gmp->den))));
        
        return ret;
    }
}


inline
int cmp(const QNumber &a, const QNumber &b)
{
    int ret = (a < b) ? -1 : (a != b);

#if QNUMBER_VALIDATE
    if (a.big() && b.big()) {
        int r2 = cmp(mpq_class(mpz_class(a.gmp->num), mpz_class(a.gmp->den)),
                     mpq_class(mpz_class(b.gmp->num), mpz_class(b.gmp->den)));
        qassert(((ret == 0) == (r2 == 0)) && ((ret < 0) == (r2 < 0)));
    } else if (a.big()) {
        mpq_class c1(mpz_class(a.gmp->num), mpz_class(a.gmp->den));
        mpq_class c2(b.num, b.den);
        int r2 = cmp(c1, c2);
        qassert((!ret && !r2) || ((ret < 0) == (r2 < 0)));
    } else if (b.big()) {
        int r2 = cmp(mpq_class(a.num, a.den),
                     mpq_class(mpz_class(b.gmp->num), mpz_class(b.gmp->den)));
        qassert(((ret == 0) == (r2 == 0)) && ((ret < 0) == (r2 < 0)));
    } else {
        int r2 = cmp(mpq_class(a.num, a.den),
                     mpq_class(b.num, b.den));
        qassert(((ret == 0) == (r2 == 0)) && ((ret < 0) == (r2 < 0)));
    }
#endif
    
    return ret;
}


inline
QNumber gcd(const QNumber &a, const QNumber &b)
{
    assert(a.is_integer() && b.is_integer());

    if (!a.big()) {
        if (!b.big()) {
            return QNumber(gcd(a.num, b.num));
        } else {
            if (!a.num) {
                return sgn(b) < 0 ? -QNumber(b) : QNumber(b);
            } else {
                long n = long(mpz_gcd_ui(NULL, b.gmp->num, labs(a.num)));
                return QNumber(n);
            }
        }
    } else {
        if (!b.big()) {
            if (!b.num) {
                return sgn(a) < 0 ? -QNumber(a) : QNumber(a);
            } else {
                long n = long(mpz_gcd_ui(NULL, a.gmp->num, labs(b.num)));
                return QNumber(n);
            }
        } else {
            //mpz_t &n = QNumber::gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(n, 1);
            //mpz_t &d = QNumber::gmp_tmp.tmp2;
            MSAT_GET_GMPTMP(d, 2);
            mpz_set_si(d, 1);
            mpz_gcd(n, a.gmp->num, b.gmp->num);
            return QNumber(n, d, true);
        }
    }
}


inline
QNumber lcm(const QNumber &a, const QNumber &b)
{
    assert(a.is_integer() && b.is_integer());

    if (!a.big()) {
        if (!b.big()) {
            //mpz_t &n = QNumber::gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(n, 1);
            //mpz_t &a1 = QNumber::gmp_tmp.tmp2;
            MSAT_GET_GMPTMP(a1, 2);
            mpz_set_si(a1, a.num);
            mpz_lcm_ui(n, a1, labs(b.num));
            if (mpz_fits_slong_p(n)) {
                return QNumber(long(mpz_get_si(n)), 1);
            } else {
                mpz_set_si(a1, 1);
                return QNumber(n, a1, true);
            }
        } else {
            //mpz_t &n = QNumber::gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(n, 1);
            //mpz_t &d = QNumber::gmp_tmp.tmp2;
            MSAT_GET_GMPTMP(d, 2);
            mpz_set_si(d, 1);
            mpz_lcm_ui(n, b.gmp->num, labs(a.num));
            return QNumber(n, d, true);
        }
    } else {
        //mpz_t &n = QNumber::gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(n, 1);
        //mpz_t &d = QNumber::gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(d, 2);
        mpz_set_si(d, 1);
        if (!b.big()) {
            mpz_lcm_ui(n, a.gmp->num, labs(b.num));
            return QNumber(n, d, true);
        } else {
            mpz_lcm(n, a.gmp->num, b.gmp->num);
            return QNumber(n, d, true);
        }
    }
}


inline
QNumber &QNumber::self_addmul(const QNumber &a, const QNumber &b)
{
    if (!a.big() && !b.big()) {
        return (*this += a * b);
    } else {
#if QNUMBER_VALIDATE
        mpq_class n1, n2;
#endif
        
        //mpz_t &n = gmp_tmp.tmp1;
        MSAT_GET_GMPTMP(n, 1);
        //mpz_t &d = gmp_tmp.tmp2;
        MSAT_GET_GMPTMP(d, 2);
        if (a.big() && b.big()) {
            mpz_mul(n, a.gmp->num, b.gmp->num);
            mpz_mul(d, a.gmp->den, b.gmp->den);
#if QNUMBER_VALIDATE
            n1 = mpq_class(mpz_class(a.gmp->num), mpz_class(a.gmp->den));
            n2 = mpq_class(mpz_class(b.gmp->num), mpz_class(b.gmp->den));
#endif
        } else if (a.big()) {
            mpz_mul_si(n, a.gmp->num, b.num);
            mpz_mul_si(d, a.gmp->den, b.den);
#if QNUMBER_VALIDATE
            n1 = mpq_class(mpz_class(a.gmp->num), mpz_class(a.gmp->den));
            n2 = mpq_class(b.num, b.den);
#endif
        } else { // b.big
            mpz_mul_si(n, b.gmp->num, a.num);
            mpz_mul_si(d, b.gmp->den, a.den);
#if QNUMBER_VALIDATE
            n1 = mpq_class(a.num, a.den);
            n2 = mpq_class(mpz_class(b.gmp->num), mpz_class(b.gmp->den));
#endif
        }

#if QNUMBER_VALIDATE
        mpq_class r1 = mpq_class(mpz_class(n), mpz_class(d));
        r1.canonicalize();
        mpq_class r2 = n1 * n2;
        if (r1 != r2) {
            std::cout << "ERROR!!!" << std::endl;
            std::cout << "a: " << a << ", b: " << b << std::endl;
            std::cout << "n: " << mpz_get_str(NULL, 10, n)
                      << ", d: " << mpz_get_str(NULL, 10, d) << std::endl;
            std::cout << "n1: " << n1.get_str() << ", n2: " << n2.get_str()
                      << ", result: " << r1.get_str() << std::endl;
            std::cout << "n1 * n2: " << r2.get_str() << std::endl;
            abort();
        }
#endif
        
        return (*this += QNumber(n, d, true));
    }
}


inline
bool QNumber::to_int(int &out_value) const
{
    if (!big() && is_int_normal() &&
        num <= long(std::numeric_limits<int>::max()) &&
        num >= long(std::numeric_limits<int>::min())) {
        out_value = num;
        return true;
    } else if (big() && is_int_big() &&
               mpz_fits_sint_p(gmp->num)) {
        out_value = int(mpz_get_si(gmp->num));
        return true;
    } else {
        return false;
    }
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2016-09-01 (p.t.): lemma lifting support
inline
bool QNumber::to_int(long &out_value) const
{
    if (!big() && is_int_normal() &&
        num <= long(std::numeric_limits<long>::max()) &&
        num >= long(std::numeric_limits<long>::min())) {
        out_value = num;
        return true;
    } else if (big() && is_int_big() &&
               mpz_fits_slong_p(gmp->num)) {
        out_value = long(mpz_get_si(gmp->num));
        return true;
    } else {
        return false;
    }
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

inline
QNumber QNumber::floor() const
{
    if (is_integer()) return *this;
    if (!big()) {
        long r = num / den;
        if (num < 0) --r;
        return QNumber(r);
    } else {
        MSAT_GET_GMPTMP(tmp1, 1);
        MSAT_GET_GMPTMP(tmp2, 2);
        mpz_fdiv_q(tmp1, gmp->num, gmp->den);
        mpz_set_ui(tmp2, 1);
        return QNumber(tmp1, tmp2, true);
    }
}


inline
bool QNumber::fits(size_t num_bits) const
{
    assert(is_integer());
    assert(sgn(*this) >= 0);
    
    if (!big()) {
        if (num_bits >= sizeof(unsigned long) * 8) {
            return true;
        } else {
            return (static_cast<unsigned long>(num) <
                    static_cast<unsigned long>(1ul << num_bits));
        }
    } else {
        return mpz_sizeinbase(gmp->num, 2) <= num_bits;
    }
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// EDIT 2018-04-16 (p.t.): flatzinc int via bitvectors support
inline
size_t QNumber::required_bits() const
{
    assert(is_integer());
    assert(sgn(*this) >= 0);

    if (!big()) {
        unsigned long n = num;
        size_t ret = 0;
        for (ret = 0; n != 0; ++ret) n >>= 1;
        return ret;
    } else {
        return mpz_sizeinbase(gmp->num, 2);
    }
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

inline
QNumber QNumber::get_num() const
{
    if (big()) return QNumber(mpz_class(gmp->num), mpz_class(1)); 
    else return QNumber(num, 1);
}


inline
QNumber QNumber::get_den() const
{
    if (big()) return QNumber(mpz_class(gmp->den), mpz_class(1));
    else return QNumber(den, 1);
}


inline
bool QNumber::divides(const QNumber &other) const
{
    assert(is_integer() && other.is_integer());
    
    if (!big()) {
        if (!other.big()) {
            return other.num % num == 0;
        } else {
            //mpz_t &r = gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(r, 1);
            return mpz_mod_ui(r, other.gmp->num, num) == 0;
        }
    } else {
        if (!other.big()) {
            //mpz_t &a = gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(a, 1);
            mpz_set_si(a, other.num);
            //mpz_t &r = gmp_tmp.tmp2;
            MSAT_GET_GMPTMP(r, 2);
            mpz_mod(r, a, gmp->num);
            return mpz_sgn(r) == 0;
        } else {
            //mpz_t &r = gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(r, 1);
            mpz_mod(r, other.gmp->num, gmp->num);
            return mpz_sgn(r) == 0;
        }
    }
}


inline
void QNumber::divmod(const QNumber &other, QNumber &q, QNumber &r) const
{
    assert(is_integer() && other.is_integer());

    if (!big()) {
        if (!other.big()) {
            ldiv_t res = ldiv(num, other.num);
            q = res.quot;
            r = res.rem;
        } else {
            //mpz_t &a = gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(a, 1);
            mpz_set_si(a, num);

            // clear/initialize the bignums for q and r
            if (q.big()) {
                mpz_set_si(q.gmp->den, 1);
            } else {
                q.den = 0;
                q.gmp = Gmp::alloc();
                mpz_init_set_si(q.gmp->den, 1);
                mpz_init(q.gmp->num);
            }
            if (r.big()) {
                mpz_set_si(r.gmp->den, 1);
            } else {
                r.den = 0;
                r.gmp = Gmp::alloc();
                mpz_init_set_si(r.gmp->den, 1);
                mpz_init(r.gmp->num);
            }

            mpz_fdiv_qr(q.gmp->num, r.gmp->num, a, other.gmp->num);
        }
    } else {
        // clear/initialize the bignums for q and r
        if (q.big()) {
            mpz_set_si(q.gmp->den, 1);
        } else {
            q.den = 0;
            q.gmp = Gmp::alloc();
            mpz_init_set_si(q.gmp->den, 1);
            mpz_init(q.gmp->num);
        }
        if (r.big()) {
            mpz_set_si(r.gmp->den, 1);
        } else {
            r.den = 0;
            r.gmp = Gmp::alloc();
            mpz_init_set_si(r.gmp->den, 1);
            mpz_init(r.gmp->num);
        }
        if (!other.big()) {
            //mpz_t &b = gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(b, 1);
            mpz_set_si(b, other.num);
            
            mpz_fdiv_qr(q.gmp->num, r.gmp->num, gmp->num, b);
        } else {
            mpz_fdiv_qr(q.gmp->num, r.gmp->num, gmp->num, other.gmp->num);
        }
    }
}


inline QNumber QNumber::pow(unsigned int e) const
{
    QNumber ret(1);
    for (unsigned int i = 0; i < e; ++i) {
        ret *= *this;
    }
    return ret;
}


inline
QNumber QNumber::self_decompose()
{
    if (!big()) {
        ldiv_t res = ldiv(num, den);
        *this = QNumber(res.rem, den);
        return QNumber(res.quot);
    } else {
        QNumber ret;
        ret.den = 0;
        ret.gmp = Gmp::alloc();
        mpz_init_set_si(ret.gmp->den, 1);
        mpz_init(ret.gmp->num);
        mpz_fdiv_qr(ret.gmp->num, gmp->num, gmp->num, gmp->den);
        return ret;
    }
}


inline
bool QNumber::decompose(QNumber &z, QNumber &q)
{
    q = *this;
    z = q.self_decompose();
    return sgn(z);
}


inline
mpq_class QNumber::to_mpq() const
{
    if (big()) return mpq_class(mpz_class(gmp->num), mpz_class(gmp->den));
    else return mpq_class(num, den);
}

inline size_t bit_rotate_left(size_t x, size_t amount)
{
    static const size_t numbits = sizeof(size_t) * 8;
    assert(numbits > amount);
    return (x << amount) | (x >> (numbits - amount));
}

// Normalisation
inline
void QNumber::normalize()
{
    // Handle the case of zero separately, to avoid division by zero
    if (!big()) {
        if (num == 0) {
            den = 1;
            return;
        }

        long g = gcd(num, den);

        num /= g;
        den /= g;

        // Ensure that the denominator is positive
        if (den < 0) {
            num = -num;
            den = -den;
        }
    } else {
        assert(gmp);
        if (!mpz_sgn(gmp->num)) {
            mpz_set_si(gmp->den, 1);
            return;
        }
        if (mpz_cmpabs_ui(gmp->den, 1) != 0) {
            //mpz_t &g = gmp_tmp.tmp1;
            MSAT_GET_GMPTMP(g, 1);
            mpz_gcd(g, gmp->num, gmp->den);
            mpz_divexact(gmp->num, gmp->num, g);
            mpz_divexact(gmp->den, gmp->den, g);
        }
        if (mpz_sgn(gmp->den) < 0) {
            mpz_neg(gmp->num, gmp->num);
            mpz_neg(gmp->den, gmp->den);
        }
    }
}


// hash function for QNumbers
inline
size_t QNumber::hash() const
{
    size_t ret = 0;
    static const size_t halfsz = sizeof(size_t) * 4;
    if (!big()) {
        // lucky case
        //ret = size_t(num + (den << 1));
        ret = bit_rotate_left(num, halfsz) + size_t(den << 1);
    } else {
        if (mpz_fits_sint_p(gmp->num) && mpz_fits_sint_p(gmp->den)) {
            long n = long(mpz_get_si(gmp->num));
            long d = long(mpz_get_si(gmp->den));
            if (n != std::numeric_limits<long>::min() &&
                d != std::numeric_limits<long>::min()) {
                ret = bit_rotate_left(n, halfsz) + size_t(d << 1);
            }
        }
        if (!ret) {
            for (size_t i = 0; i < mpz_size(gmp->num); ++i) {
                ret ^= mpz_getlimbn(gmp->num, i) + (ret << 6) + (ret >> 2);
            }
            for (size_t i = 0; i < mpz_size(gmp->den); ++i) {
                ret ^= mpz_getlimbn(gmp->num, i) + (ret << 6) + (ret >> 2);
            }
        }
    }
    return ret;
}




// Overflow functions adapted from David LeBlanc's article about the SafeInt
// class (as appears on MSDN)

inline
bool QNumber::add_overflow(long &res, long lhs, long rhs)
{
    if (!((rhs ^ lhs) < 0)) { //test for +/- combo
        //either two negatives, or 2 positives
        if (rhs < 0) {
            //two negatives
            // we use <= instead of < to fix the corner case of INT_MIN
            // (see QNumber::fix_int_min())            
            if (lhs <= std::numeric_limits<long>::min() - rhs) {
                //remember rhs < 0
                return true;
            }
            //ok
        } else {
            //two positives
            if (std::numeric_limits<long>::max() - lhs < rhs) {
                return true;
            }
            //OK
        }
    }
    //else overflow not possible
    res = lhs + rhs;
    return false;
}


inline
bool QNumber::sub_overflow(long &res, long lhs, long rhs)
{
    if ((rhs ^ lhs) < 0) { //test for +/- combo
        //mixed positive and negative
        //two cases - +X - -Y => X + Y - check for overflow against MaxInt()
        //            -X - +Y - check for overflow against MinInt()
        if (lhs >= 0) { //first case
            //test is X - -Y > MaxInt()
            //equivalent to X > MaxInt() - +Y
            //Y == MinInt() creates special case
            //Even 0 - MinInt() can't be done
            //note that the special case collapses into the general 
            //case, due to the fact
            //MaxInt() - MinInt() == -1, and lhs is non-negative
            if (lhs > std::numeric_limits<long>::max() + rhs) {
                //remember that rhs is negative
                return true;
            }
            //fall through to return value
        } else {
            //second case
            //test is -X - Y < MinInt()
            //or      -X < MinInt() + Y
            //we do not have the same issues because 
            //abs(MinInt()) > MaxInt()
            // we use <= instead of < to fix the corner case of INT_MIN
            // (see QNumber::fix_int_min())
            if (lhs <= std::numeric_limits<long>::min() + rhs) {
                return true;
            }
            //fall through to return value
        }
    }
    // else 
    //both negative, or both positive
    //no possible overflow
    res = lhs - rhs;
    return false;
}


inline
bool QNumber::mul_overflow(long &res, long lhs, long rhs)
{
    if (sizeof(long long) == sizeof(long) * 2) {
        // fast path: on 32-bit systems we can cast to a 64-bit integer and
        // perform multiplication there
        long long tmp = (static_cast<long long>(lhs) *
                         static_cast<long long>(rhs));
        if (tmp > std::numeric_limits<long>::max() ||
            // use <= instead of < to fix the corner case of INT_MIN
            // (see QNumber::fix_int_min())
            tmp <= std::numeric_limits<long>::min()) {
            return true;
        }
        res = static_cast<long>(tmp);
        return false;
    } else {
        // on 64-bit machines, we check whether (|lhs| > LONG_MAX/|rhs|)
        // since |LONG_MAX| < |LONG_MIN|, this should be enough...
        // moreover, since both arguments to division are positive, division
        // can't overflow
        if (rhs && labs(lhs) > std::numeric_limits<long>::max() / labs(rhs)) {
            return true;
        }
        res = lhs * rhs;
        return false;
    }
}


inline
bool QNumber::div_overflow(long &res, long lhs, long rhs)
{
    if (lhs == std::numeric_limits<long>::min() && rhs == -1) {
        return true;
    }
    res = lhs / rhs;
    return false;
}


} // namespace msat


#endif  // MSAT_NUMBERS_H_INCLUDED

