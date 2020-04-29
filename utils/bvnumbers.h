#ifndef MSAT_BVNUMBERS_H_INCLUDED
#define MSAT_BVNUMBERS_H_INCLUDED

#include "../utils/numbers.h"
#include <limits.h>

namespace msat {

class BVNumber {
public:
    static bool fits(const Number &n, size_t num_bits);
    ///< returns true if *this can be represented with the given number of bits.

    static bool is_pow2(const Number &n, size_t *out_n=NULL);
    ///< checks whether this number is a power of two. If true is returned and
    ///< out_n is not NULL, the exponent will be stored in *out_n.

    static void twos_complement(const Number &n, size_t num_bits, Number *out);
    static Number twos_complement(const Number &n, size_t num_bits);
    ///< returns the 2's complement of the given number, using the given
    ///< number of bits

    static void pow2(size_t n, Number *out);
    static Number pow2(size_t n);
    ///< returns 2^n

    // bit-manipulating functions

    static bool test_bit(const Number &n, size_t index);
    ///< returns true if the given bit of the binary representation of the
    ///< number is set
    
    static void set_bit(Number &n, size_t index, bool value);
    ///< sets the given bit of the binary representation of the number to the
    ///< given value

    static void bit_and(const Number &n1, const Number &n2, Number *out);
    static Number bit_and(const Number &n1, const Number &n2);
    ///< returns the bitwise and of n1 and n2
    
    static void bit_or(const Number &n1, const Number &n2, Number *out);
    static Number bit_or(const Number &n1, const Number &n2);
    ///< returns the bitwise or of n1 and n2
    
    static void bit_xor(const Number &n1, const Number &n2, Number *out);
    static Number bit_xor(const Number &n1, const Number &n2);
    ///< returns the bitwise xor of n1 and n2
    
    static void bit_complement(const Number &n, Number *out);
    static Number bit_complement(const Number &n);
    ///< returns the 1's complement of n

    static void bit_left_shift(const Number &n, size_t i, Number *out);
    static Number bit_left_shift(const Number &n, size_t i);
    ///< returns (n << i)

    static void bit_right_shift(const Number &n, size_t i, Number *out);
    static Number bit_right_shift(const Number &n, size_t i);
    ///< returns (n >> i)

    static size_t scan_bit_1(const Number &n, size_t start_index);
    ///< returns the index of the first bit 1, starting from start_index.
    ///< returns std::numeric_limits<size_t>::max() if no bit 1 is found

    static size_t scan_bit_0(const Number &n, size_t start_index);
    ///< returns the index of the first bit 0, starting from start_index.
    ///< returns std::numeric_limits<size_t>::max() if no bit 0 is found
    
    static size_t count_leading_zeros(const Number &n, size_t width);
    ///< returns the number of leading zeros assuming that n is stored in
    ///< width bits. If n doesn't fit in width, 0 is returned

    static bool to_long(const Number &n, long *out);
    ///< tries to convert the number to a positive signed long. returns true if
    ///< this is possible, false otherwise

    static Number trim(const Number &n, size_t width);
    static void trim(Number &n, size_t width);

    static void add(size_t width, const Number &a, const Number &b, 
                    Number *out);
    static Number add(size_t width, const Number &a, const Number &b);
    
    static void sub(size_t width, const Number &a, const Number &b,
                    Number *out);
    static Number sub(size_t width, const Number &a, const Number &b);

    static void neg(size_t width, const Number &a, Number *out);
    static Number neg(size_t width, const Number &a);

    static void mul(size_t width, const Number &a, const Number &b,
                    Number *out);
    static Number mul(size_t width, const Number &a, const Number &b);

    static void udiv(size_t width, const Number &a, const Number &b,
                     Number *out);
    static Number udiv(size_t width, const Number &a, const Number &b);

    static void urem(size_t width, const Number &a, const Number &b,
                     Number *out);
    static Number urem(size_t width, const Number &a, const Number &b);

    static void sdiv(size_t width, const Number &a, const Number &b,
                     Number *out);
    static Number sdiv(size_t width, const Number &a, const Number &b);

    static void srem(size_t width, const Number &a, const Number &b,
                     Number *out);
    static Number srem(size_t width, const Number &a, const Number &b);

    static void lshl(size_t width, Number a, Number b, Number *out);
    static Number lshl(size_t width, const Number &a, const Number &b);

    static void lshr(size_t width, Number a, Number b, Number *out);
    static Number lshr(size_t width, const Number &a, const Number &b);

    static void ashr(size_t width, const Number &a, const Number &b,
                     Number *out);
    static Number ashr(size_t width, const Number &a, const Number &b);
    
private:
    static void check_bv(const Number &n);

    template<class bitop_normal_fun, class bitop_big_fun>
    static void bit_op(const Number &n1, const Number &n2,
                       bitop_normal_fun normalop, bitop_big_fun bigop,
                       Number *out);
    static long bit_and_l(long a, long b) { return a & b; }
    static long bit_or_l(long a, long b) { return a | b; }
    static long bit_xor_l(long a, long b) { return a ^ b; }
    static size_t scan_bit_1_l(long n, size_t start_index);
};


inline void BVNumber::check_bv(const Number &n)
{
    assert(n.is_integer());
    assert(sgn(n) >= 0);
}


inline bool BVNumber::fits(const Number &n, size_t num_bits)
{
    check_bv(n);
    
    if (!n.big()) {
        if (num_bits >= Number::NUM_BITS_NORMAL) {
            return true;
        } else {
            return (static_cast<unsigned long>(n.num) <
                    static_cast<unsigned long>(1ul << num_bits));
        }
    } else {
        return mpz_sizeinbase(n.gmp->num, 2) <= num_bits;
    }
}


inline bool BVNumber::is_pow2(const Number &n, size_t *out_n)
{
    check_bv(n);

    if (!n.big()) {
        if (n.num && (n.num & (n.num - 1)) == 0) {
            if (out_n) {
                unsigned long m = n.num;
                *out_n = 0;
                m >>= 1;
                while (m) {
                    ++(*out_n);
                    m >>= 1;
                }
            }
            return true;
        } else {
            return false;
        }
    } else {
        if (mpz_popcount(n.gmp->num) == 1) {
            if (out_n) {
                *out_n = mpz_scan1(n.gmp->num, 0);
            }
            return true;
        } else {
            return false;
        }
    }
}


inline void BVNumber::pow2(size_t n, Number *out)
{
    if (n < Number::NUM_BITS_NORMAL - 2) {
        *out = long(size_t(1) << n);
    } else {
        MSAT_GET_GMPTMP(tmpnum, 1);
        mpz_set_si(tmpnum, 1);
        mpz_mul_2exp(tmpnum, tmpnum, n);
        if (mpz_fits_slong_p(tmpnum)) {
            *out = Number(long(mpz_get_si(tmpnum)), 1);
        } else {
            *out = Number(mpz_class(tmpnum), mpz_class(1));
        }
    }
}

inline Number BVNumber::pow2(size_t n)
{
    Number ret;
    pow2(n, &ret);
    return ret;
}


inline void BVNumber::twos_complement(const Number &n, size_t width,
                                      Number *out)
{
    *out = n;
    if (sgn(*out) < 0) {
        *out += pow2(width);
    }
}

inline Number BVNumber::twos_complement(const Number &n, size_t width)
{
    Number ret;
    twos_complement(n, width, &ret);
    return ret;
}


inline bool BVNumber::test_bit(const Number &n, size_t index)
{
    check_bv(n);

    if (n.big()) {
        return mpz_tstbit(n.gmp->num, index);
    } else {
        if (index >= Number::NUM_BITS_NORMAL) {
            return false;
        } else {
            return n.num & (1ul << index);
        }
    }
}


inline void BVNumber::set_bit(Number &n, size_t index, bool value)
{
    check_bv(n);

    if (n.big()) {
        if (value) {
            mpz_setbit(n.gmp->num, index);
        } else {
            mpz_clrbit(n.gmp->num, index);
        }
    } else if (index < Number::NUM_BITS_NORMAL-1 /* we must avoid making the
                                                  * number signed! */) {
        if (value) {
            n.num |= (1ul << index);
        } else {
            n.num &= ~(1ul << index);
        }
    } else if (value) {
        n.make_big();
        mpz_setbit(n.gmp->num, index);
    }
}


template <class bitop_normal_fun, class bitop_big_fun>
inline void BVNumber::bit_op(const Number &n1, const Number &n2,
                             bitop_normal_fun normalop, bitop_big_fun bigop,
                             Number *out)
{
    check_bv(n1);
    check_bv(n2);
    
    if (!n1.big() && !n2.big()) {
        // fast path
        *out = Number(normalop(n1.num, n2.num), 1);
    } else {
        MSAT_GET_GMPTMP(tmp1, 1);
        if (!n1.big()) {
            mpz_set_si(tmp1, n1.num);
            bigop(tmp1, tmp1, n2.gmp->num);
        } else if (!n2.big()) {
            mpz_set_si(tmp1, n2.num);
            bigop(tmp1, tmp1, n1.gmp->num);
        } else {
            bigop(tmp1, n1.gmp->num, n2.gmp->num);
        }
        if (n1.big()) {
            *out = Number(tmp1, n1.gmp->den, true);
        } else {
            *out = Number(tmp1, n2.gmp->den, true);
        }
    }
}


inline void BVNumber::bit_and(const Number &n1, const Number &n2, Number *out)
{
    bit_op(n1, n2, BVNumber::bit_and_l, mpz_and, out);
}

inline Number BVNumber::bit_and(const Number &n1, const Number &n2)
{
    Number ret;
    bit_and(n1, n2, &ret);
    return ret;
}


inline void BVNumber::bit_or(const Number &n1, const Number &n2, Number *out)
{
    bit_op(n1, n2, BVNumber::bit_or_l, mpz_ior, out);
}

inline Number BVNumber::bit_or(const Number &n1, const Number &n2)
{
    Number ret;
    bit_or(n1, n2, &ret);
    return ret;
}


inline void BVNumber::bit_xor(const Number &n1, const Number &n2, Number *out)
{
    bit_op(n1, n2, BVNumber::bit_xor_l, mpz_xor, out);
}

inline Number BVNumber::bit_xor(const Number &n1, const Number &n2)
{
    Number ret;
    bit_xor(n1, n2, &ret);
    return ret;
}


inline void BVNumber::bit_complement(const Number &n, Number *out)
{
    check_bv(n);

    if (!n.big()) {
        *out = Number(~(n.num), 1);
    } else {
        MSAT_GET_GMPTMP(tmp1, 1);
        mpz_com(tmp1, n.gmp->num);
        *out = Number(tmp1, n.gmp->den, true);
    }
}

inline Number BVNumber::bit_complement(const Number &n)
{
    Number ret;
    bit_complement(n, &ret);
    return ret;
}


inline void BVNumber::bit_left_shift(const Number &n, size_t i, Number *out)
{
    check_bv(n);

    if (!i) {
        *out = n;
        return;
    }

    if (i < Number::NUM_BITS_NORMAL - 2 && !n.big()) {
        size_t j = i + 1; // if num has a 1 at position (#bits - i), it will
                          // become negative after shifting...
        size_t mask = (~(size_t(1) << j)) << (Number::NUM_BITS_NORMAL - j);
        if ((size_t(n.num) & mask) == 0) {
            *out = Number(n.num << i);
            return;
        }
    }

    MSAT_GET_GMPTMP(tmp1, 1);
    if (!n.big()) {
        mpz_set_si(tmp1, n.num);
    } else {
        mpz_set(tmp1, n.gmp->num);
    }
    mpz_mul_2exp(tmp1, tmp1, i);
    if (mpz_fits_slong_p(tmp1)) {
        *out = Number(long(mpz_get_si(tmp1)), 1);
    } else {
        MSAT_GET_GMPTMP(tmp2, 2);
        mpz_set_si(tmp2, 1);
        *out = Number(tmp1, tmp2, true);
    }
}

inline Number BVNumber::bit_left_shift(const Number &n, size_t i)
{
    Number ret;
    bit_left_shift(n, i, &ret);
    return ret;
}


inline void BVNumber::bit_right_shift(const Number &n, size_t i, Number *out)
{
    check_bv(n);

    if (!i) {
        *out = n;
        return;
    }

    if (!n.big()) {
        if (i >= Number::NUM_BITS_NORMAL) {
            *out = Number(0, 1);
        } else {
            *out = Number(n.num >> i, 1);
        }
    } else {
        MSAT_GET_GMPTMP(tmp1, 1);
        mpz_fdiv_q_2exp(tmp1, n.gmp->num, i);
        *out = Number(tmp1, n.gmp->den, true);
    }
}

inline Number BVNumber::bit_right_shift(const Number &n, size_t i)
{
    Number ret;
    bit_right_shift(n, i, &ret);
    return ret;
}


inline size_t BVNumber::scan_bit_1_l(long n, size_t start_index)
{
    // naive algorithm, hardly a bottleneck for us :-)
    if (!n || start_index >= Number::NUM_BITS_NORMAL) {
        return std::numeric_limits<size_t>::max();
    } else {
        unsigned long r = (static_cast<unsigned long>(n) >> start_index);
        assert(sizeof(r) == 4 || sizeof(r) == 8);

        if (!r) {
            start_index = std::numeric_limits<size_t>::max();
        } else if (!(r & 0x1)) { // if r is odd, start_index is already fine
            start_index += 1;
            if (sizeof(r) == 8) {
                if ((r & 0xffffffffUL) == 0) {
                    // do it in two stages to avoid annoying GCC warning on
                    // 32-bit platforms
                    r >>= 16;
                    r >>= 16;
                    start_index += 32;
                }
            }
            if ((r & 0xffff) == 0) {  
                r >>= 16;  
                start_index += 16;
            }
            if ((r & 0xff) == 0) {  
                r >>= 8;  
                start_index += 8;
            }
            if ((r & 0xf) == 0) {  
                r >>= 4;
                start_index += 4;
            }
            if ((r & 0x3) == 0) {  
                r >>= 2;
                start_index += 2;
            }
            start_index -= r & 0x1;
        }

        return start_index;
        // while (r) {
        //     if (r & 1) return start_index;
        //     ++start_index;
        //     r = r >> 1;
        // }
        // return std::numeric_limits<size_t>::max();
    }
}


inline size_t BVNumber::scan_bit_1(const Number &n, size_t start_index)
{
    check_bv(n);

    if (!n.big()) {
        return scan_bit_1_l(n.num, start_index);
    } else {
        unsigned long r =
            static_cast<unsigned long>(mpz_scan1(n.gmp->num, start_index));
        size_t ret = r;
        if (r == ULONG_MAX) {
            ret = std::numeric_limits<size_t>::max();
        }
        return ret;
    }
}


inline size_t BVNumber::scan_bit_0(const Number &n, size_t start_index)
{
    check_bv(n);

    if (!n.big()) {
        return scan_bit_1_l(~(n.num), start_index);
    } else {
        unsigned long r =
            static_cast<unsigned long>(mpz_scan0(n.gmp->num, start_index));
        size_t ret = r;
        if (r == ULONG_MAX) {
            ret = std::numeric_limits<size_t>::max();
        }
        return ret;
    }
}


inline size_t BVNumber::count_leading_zeros(const Number &n, size_t width)
{
    check_bv(n);

    if (!n.big()) {
        static const unsigned char count_tbl[] = {
            8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };
        
        typedef unsigned long ulong;
        ulong l = n.num;
        size_t ret = 0;
        size_t w = Number::NUM_BITS_NORMAL;
        while (w > 8) {
            w >>= 1;
            size_t w2 = (Number::NUM_BITS_NORMAL - w);
            if (l < (ulong(1) << w2)) {
                ret += w;
                l <<= w;
            }
        }
        l >>= (Number::NUM_BITS_NORMAL - w);

        assert(l < 256);
        ret += size_t(count_tbl[l]);

        if (width > Number::NUM_BITS_NORMAL) {
            ret += (width - Number::NUM_BITS_NORMAL);
        } else if (width < Number::NUM_BITS_NORMAL) {
            size_t d = (Number::NUM_BITS_NORMAL - width);
            if (ret >= d) {
                ret -= d;
            } else {
                ret = 0;
            }
            // if (ulong(n.num) >= (ulong(1) << width)) {
            //     ret = 0;
            // }
        }

        return ret;
    } else {
        size_t ret = mpz_sizeinbase(n.gmp->num, 2);
        if (ret == 1 && !mpz_sgn(n.gmp->num)) {
            ret = 0;
        }
        if (ret <= width) {
            ret = width - ret;
        } else {
            ret = 0;
        }
        return ret;
    }
}


inline bool BVNumber::to_long(const Number &n, long *out)
{
    check_bv(n);

    if (!n.big()) {
        *out = n.num;
        return true;
    } else if (mpz_fits_slong_p(n.gmp->num)) {
        *out = long(mpz_get_si(n.gmp->num));
        return true;
    }
    return false;
}


inline void BVNumber::trim(Number &n, size_t width)
{
    check_bv(n);

    if (!fits(n, width)) {
        Number mask;
        pow2(width, &mask);
        mask -= 1;
        bit_and(n, mask, &n);
    }
}


inline Number BVNumber::trim(const Number &n, size_t width)
{
    Number ret(n);
    trim(ret, width);
    return ret;
}


inline void BVNumber::add(size_t width, const Number &a, const Number &b,
                          Number *out)
{
    check_bv(a);
    check_bv(b);
    
    *out = a;
    *out += b;

    trim(*out, width);
}

inline Number BVNumber::add(size_t width, const Number &a, const Number &b)
{
    Number ret;
    add(width, a, b, &ret);
    return ret;
}


inline void BVNumber::neg(size_t width, const Number &a, Number *out)
{
    check_bv(a);

    if (!sgn(a)) {
        *out = a;
    } else {
        *out = BVNumber::pow2(width);
        *out -= a;
    }
}

inline Number BVNumber::neg(size_t width, const Number &a)
{
    Number ret;
    neg(width, a, &ret);
    return ret;
}


inline void BVNumber::sub(size_t width, const Number &a, const Number &b,
                          Number *out)
{
    check_bv(a);
    check_bv(b);

    neg(width, b, out);
    *out += a;

    trim(*out, width);
}

inline Number BVNumber::sub(size_t width, const Number &a, const Number &b)
{
    Number ret;
    sub(width, a, b, &ret);
    return ret;
}


inline void BVNumber::mul(size_t width, const Number &a, const Number &b,
                          Number *out)
{
    check_bv(a);
    check_bv(b);

    Number q, n;
    n = a * b;
    Number modfactor = pow2(width);
    n.divmod(modfactor, q, *out);
}

inline Number BVNumber::mul(size_t width, const Number &a, const Number &b)
{
    Number ret;
    mul(width, a, b, &ret);
    return ret;
}


inline void BVNumber::udiv(size_t width, const Number &a, const Number &b,
                           Number *out)
{
    check_bv(a);
    check_bv(b);
    assert(sgn(b));

    Number r;
    a.divmod(b, *out, r);
}

inline Number BVNumber::udiv(size_t width, const Number &a, const Number &b)
{
    Number ret;
    udiv(width, a, b, &ret);
    return ret;
}


inline void BVNumber::urem(size_t width, const Number &a, const Number &b,
                           Number *out)
{
    check_bv(a);
    check_bv(b);
    assert(sgn(b));

    Number q;
    a.divmod(b, q, *out);
}

inline Number BVNumber::urem(size_t width, const Number &a, const Number &b)
{
    Number ret;
    urem(width, a, b, &ret);
    return ret;
}


inline void BVNumber::sdiv(size_t width, const Number &a, const Number &b,
                           Number *out)
{
    check_bv(a);
    check_bv(b);
    assert(sgn(b));

    bool asign = test_bit(a, width-1);
    bool bsign = test_bit(b, width-1);
    Number r;

    if (!asign && !bsign) {
        a.divmod(b, *out, r);
    } else if (asign && !bsign) {
        Number na = neg(width, a);
        na.divmod(b, *out, r);
        *out = neg(width, *out);
    } else if (!asign && bsign) {
        Number nb = neg(width, b);
        a.divmod(nb, *out, r);
        *out = neg(width, *out);
    } else {
        Number na = neg(width, a);
        Number nb = neg(width, b);
        na.divmod(nb, *out, r);
    }
}

inline Number BVNumber::sdiv(size_t width, const Number &a, const Number &b)
{
    Number ret;
    sdiv(width, a, b, &ret);
    return ret;
}


inline void BVNumber::srem(size_t width, const Number &a, const Number &b,
                           Number *out)
{
    check_bv(a);
    check_bv(b);
    assert(sgn(b));

    bool asign = test_bit(a, width-1);
    bool bsign = test_bit(b, width-1);
    Number q;
    Number na = a;
    Number nb = b;

    bool negate = asign;
    if (asign) {
        na = neg(width, a);
    }
    if (bsign) {
        nb = neg(width, b);
    }
    
    na.divmod(nb, q, *out);

    if (asign) {
        *out = neg(width, *out);
    }
}

inline Number BVNumber::srem(size_t width, const Number &a, const Number &b)
{
    Number ret;
    srem(width, a, b, &ret);
    return ret;
}


inline void BVNumber::lshl(size_t width, Number a, Number b, Number *out)
{
    if (b >= width) {
        *out = 0;
        return;
    }
    long w;
    if (BVNumber::to_long(b, &w)) {
        a = BVNumber::bit_left_shift(a, w);
    } else {
        // use the slow way...
        while (sgn(b)) {
            a = BVNumber::bit_left_shift(a, 1);
            b -= 1;
        }
    }
    Number q, r, n;
    n = a;
    Number modfactor = BVNumber::pow2(width);
    n.divmod(modfactor, q, r);
    *out = r;    
}

inline Number BVNumber::lshl(size_t width, const Number &a, const Number &b)
{
    Number ret;
    lshl(width, a, b, &ret);
    return ret;
}


inline void BVNumber::lshr(size_t width, Number a, Number b, Number *out)
{
    if (b >= width) {
        *out = 0;
        return;
    }
    long w;
    if (BVNumber::to_long(b, &w)) {
        a = BVNumber::bit_right_shift(a, w);
    } else {
        // use the slow way...
        while (sgn(b)) {
            a = BVNumber::bit_right_shift(a, 1);
            b -= 1;
        }            
    }
    *out = a;
}

inline Number BVNumber::lshr(size_t width, const Number &a, const Number &b)
{
    Number ret;
    lshr(width, a, b, &ret);
    return ret;
}


inline void BVNumber::ashr(size_t width, const Number &a, const Number &b,
                           Number *out)
{
    // asr is defined as
    // sign(left) ? (left >> right) : ~((~left) >> right)
    size_t msb = width - 1;
    bool sign = BVNumber::test_bit(a, msb);
    lshr(width, a, b, out);
    if (sign) {
        size_t padlen = width;
        if (width > b) {
            long l = 0;
            bool ok = BVNumber::to_long(b, &l);
            assert(ok);
            padlen = l;
        }
        assert(width >= padlen);
        for (size_t i = width - padlen; i < width; ++i) {
            BVNumber::set_bit(*out, i, true);
        }
        *out = BVNumber::twos_complement(*out, width);
    }
}


inline Number BVNumber::ashr(size_t width, const Number &a, const Number &b)
{
    Number ret;
    ashr(width, a, b, &ret);
    return ret;
}


} // namespace msat

#endif // MSAT_BVNUMBERS_H_INCLUDED
