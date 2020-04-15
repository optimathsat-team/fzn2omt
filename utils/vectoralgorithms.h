// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Some useful algorithms on vectors
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.
//
// Taken from MiniSat and modified. Copyright of original code follows
//
/*****************************************************************************[Sort.h]
MiniSat -- Copyright (c) 2003-2006, Niklas Een, Niklas Sorensson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************/

#ifndef MSAT_VECTORALGORITHMS_H_INCLUDED
#define MSAT_VECTORALGORITHMS_H_INCLUDED

#include <functional>
#include <algorithm>
#include <assert.h>

namespace msat {

//-----------------------------------------------------------------------------
// Declarations
//-----------------------------------------------------------------------------

template <class V, class T>
void remove(V &ts, const T &t);

template <class V, class T>
bool find(V &ts, const T &t);

template <class V, class LessThan>
void sort(V &v, LessThan lt);

template <class V>
void sort(V &v);


//-----------------------------------------------------------------------------
// Implementations
//-----------------------------------------------------------------------------

namespace sortimpl {

template <class T, class Sz, class LessThan>
inline void selection_sort(T *array, const Sz size, LessThan lt)
{
    Sz i, j, best_i;

    for (i = 0; i < size-1; ++i) {
        best_i = i;
        for (j = i+1; j < size; ++j) {
            if (lt(array[j], array[best_i])) {
                best_i = j;
            }
        }
        std::swap(array[i], array[best_i]);
    }
}


template<class T, class LessThan>
inline T med(const T &a, const T &b, const T &c, LessThan lt)
{
    if (lt(a, b)) {
        if (lt(b, c)) {
            return b;
        } else if (lt(a, c)) {
            return c;
        } else {
            return a;
        }
    } else if (lt(a, c)) {
        return a;
    } else if (lt(b, c)) {
        return c;
    } else {
        return b;
    }
}


template <class T, class Sz, class LessThan>
void do_sort(T *array, const Sz size, LessThan lt, int recdepth)
{
    if (size <= 15) {
        //selection_sort(array, size, lt);
    } else if (recdepth == 0) {
        std::make_heap(array, array+size, lt);
        std::sort_heap(array, array+size, lt);
    } else {
        T pivot = med(array[0], array[size / 2], array[size-1], lt);
        Sz i = 0;
        Sz j = size-1;

        while (true) {
            while (lt(array[i], pivot)) {
                ++i;
            }
            while (lt(pivot, array[j])) {
                --j;
            }

            if (i >= j) {
                break;
            }

            std::swap(array[i], array[j]);
            ++i;
            --j;
        }

        --recdepth;
        do_sort(array, i, lt, recdepth);
        do_sort(&array[i], size-i, lt, recdepth);
    }
}


template <class T, class Sz, class LessThan>
inline void do_insertion_sort(T *array, const Sz size, LessThan lt)
{
    Sz i, j;
    T value;

    for (i = 1; i < size; ++i) {
        value = array[i];
        for (j = i; j > 0 && lt(value, array[j-1]); --j) {
            array[j] = array[j-1];
        }
        array[j] = value;
    }
}

// selection sort for small inputs, otherwise a variant of introspective sort
template <class T, class Sz, class LessThan>
inline void sort(T *array, const Sz size, LessThan lt)
{
    if (size <= 15) {
        selection_sort(array, size, lt);
    } else {
        do_sort(array, size, lt, 32);
        do_insertion_sort(array, size, lt);
    }
}

} // namespace sortimpl


template <class V, class LessThan>
inline void sort(V &v, LessThan lt)
{
    if (v.size()) {
        sortimpl::sort(&(v[0]), v.size(), lt);
    }
}


template <class V>
inline void sort(V &v)
{
    sort(v, std::less<typename V::value_type>());
}

template <class V, class T>
inline void remove(V &ts, const T &t)
{
    typename V::size_type j = 0;
    for (; j < ts.size() && ts[j] != t; ++j) {}
    assert(j < ts.size());
    for (; j < ts.size()-1; ++j) ts[j] = ts[j+1];
    ts.pop_back();
}


template<class V, class T>
inline bool find(V &ts, const T &t)
{
    typename V::size_type j = 0;
    for (; j < ts.size() && ts[j] != t; ++j) {}
    return j < ts.size();
}


} // namespace msat

#endif // MSAT_VECTORALGORITHMS_H_INCLUDED
