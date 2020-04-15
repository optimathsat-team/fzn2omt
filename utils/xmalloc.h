// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// A type-safe wrapper for malloc, that throws a bad_alloc exception on
// failure
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_XMALLOC_H_INCLUDED
#define MSAT_XMALLOC_H_INCLUDED

#include <stdlib.h>
#include <exception>
#include <algorithm>

namespace msat {

template <class T>
inline T *xmalloc(size_t n) throw(std::bad_alloc)
{
    // avoid implementation-defined malloc(0) behaviour    
    size_t sz = std::max(sizeof(T) * n, size_t(1)); 
    T *ret = static_cast<T *>(malloc(sz));
    if (!ret) {
        throw std::bad_alloc();
    }
    return ret;
}


template <class T>
inline T *xrealloc(T *ptr, size_t n) throw(std::bad_alloc)
{
    // avoid implementation-defined malloc(0) behaviour    
    size_t sz = std::max(sizeof(T) * n, size_t(1)); 
    T *ret = static_cast<T *>(realloc(ptr, sz));
    if (!ret) {
        throw std::bad_alloc();
    }
    return ret;
}


inline void xfree(void *ptr)
{
    free(ptr);
}

} // namespace msat

#endif // MSAT_XMALLOC_H_INCLUDED
