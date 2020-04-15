// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef INTERVAL_H_INCLUDED
#define INTERVAL_H_INCLUDED

#include<algorithm>
#include<vector>
#include<assert.h>
#include<iostream>
#include<sstream>

namespace msat {

template <class T> class IntervalSet;
template <class T> class IntervalIter;

//-----------------------------------------------------------------------------
// Interval
//-----------------------------------------------------------------------------

template <class T>
class Interval {
public:
    Interval();
    Interval(const T value);
    Interval(const T lower, const T upper);
    virtual ~Interval();

    T card() const;
    inline const T &lower() const { assert(!is_empty()); return lower_; };
    inline const T &upper() const { assert(!is_empty()); return upper_; };
    inline bool is_empty() const { return upper_ < lower_; };

    bool intersect(const Interval &other) const;
    bool adjacent(const Interval &other) const;
    bool contains(const Interval &other) const;

    void merge(const Interval &other);

    ///< iterator
    friend class IntervalIter<T>;
    typedef IntervalIter<T> iterator;
    typedef const IntervalIter<T> const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

private:
    T lower_;
    T upper_;

    std::string to_str() const;

    template <class U>
    friend bool operator==(const Interval<U> &ival, const Interval<U> &other);
    template <class U>
    friend bool operator!=(const Interval<U> &ival, const Interval<U> &other);
    template <class U>
    friend bool operator<(const Interval<U> &ival, const Interval<U> &other);
    template <class U>
    friend bool operator>(const Interval<U> &ival, const Interval<U> &other);
    ///< '>','<' assume that first and other do not intersect
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const Interval<U> &ival);

    friend class IntervalSet<T>;
};

//-----------------------------------------------------------------------------
// IntervalIter
//-----------------------------------------------------------------------------

template <class T>
class IntervalIter: public std::iterator<std::forward_iterator_tag, T> {
public:
    IntervalIter(Interval<T> *ival, T cur);
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    IntervalIter &operator++();
    const IntervalIter &operator++() const;
    IntervalIter &operator++(int) const;
    bool operator==(const IntervalIter &other) const;
    bool operator!=(const IntervalIter &other) const;

private:
    Interval<T> *ival_;
    T cur_;
};

//-----------------------------------------------------------------------------
// Interval
//-----------------------------------------------------------------------------

template <class T>
Interval<T>::Interval()
    : lower_(0), upper_(-1)
{
    // nothing to do
}

template <class T>
Interval<T>::Interval(const T value)
    : lower_(value), upper_(value)
{
    // nothing to do
}

template <class T>
Interval<T>::Interval(const T lower, const T upper)
    : lower_(lower), upper_(upper)
{
    // nothing to do
}

template <class T>
Interval<T>::~Interval()
{
    // nothing to do
}

template <class T>
T Interval<T>::card() const
{
    T ret = upper_ - lower_ + 1;
    T zero(0);
    return (ret > zero ? ret : zero);
}

template <class T>
bool Interval<T>::intersect(const Interval &other) const
{
    if (is_empty()) {
        return false;
    } else {
        return this->lower_ <= other.upper_ && other.lower_ <= this->upper_;
    }
}

template <class T>
bool Interval<T>::adjacent(const Interval &other) const
{
    if (is_empty() || other.is_empty()) {
        return false;
    } else {
        return other.lower_ == (this->upper_ + T(1))
               || (other.upper_ + T(1)) == this->lower_;
    }
}

template <class T>
bool Interval<T>::contains(const Interval &other) const
{
    if (is_empty() || other.is_empty()) {
        return false;
    } else {
        return this->lower_ <= other.lower_ && other.upper_ <= this->upper_;
    }
}

template <class T>
void Interval<T>::merge(const Interval &other)
{
    if (!is_empty() && !other.is_empty()) {
        assert(this->intersect(other) || this->adjacent(other));

        this->lower_ = (this->lower_ < other.lower_ ? this->lower_ : other.lower_);
        this->upper_ = (this->upper_ > other.upper_ ? this->upper_ : other.upper_);
    } // empty set need no adjustment
}

template <class T>
typename Interval<T>::iterator Interval<T>::begin()
{
    if (!is_empty()) {
        return Interval<T>::iterator(this, this->lower_);
    } else {
        return end(); // prevent value iteration over empty set
    }
}

template <class T>
typename Interval<T>::iterator Interval<T>::end()
{
    return Interval<T>::iterator(this, this->upper_ + T(1));
}

template <class T>
typename Interval<T>::const_iterator Interval<T>::begin() const
{
    return const_cast<Interval<T> *>(this)->begin();
}

template <class T>
typename Interval<T>::const_iterator Interval<T>::end() const
{
    return const_cast<Interval<T> *>(this)->end();
}

template <class T>
inline bool operator == (const Interval<T> &ival, const Interval<T> &other)
{
    return (ival.is_empty() && other.is_empty())
           || (ival.lower_ == other.lower_ && ival.upper_ == other.upper_);
}

template <class T>
inline bool operator != (const Interval<T> &ival, const Interval<T> &other)
{
    return ! (ival == other);
}

template <class T>
inline bool operator < (const Interval<T> &ival, const Interval<T> &other)
{
    assert(!ival.is_empty() && !other.is_empty());
    return ival.lower_ < other.lower_;
}

template <class T>
inline bool operator > (const Interval<T> &ival, const Interval<T> &other)
{
    assert(!ival.is_empty() && !other.is_empty());
    return ival.lower_ > other.lower_;
}

template <class T>
std::string Interval<T>::to_str() const
{
    std::ostringstream out;
    out << *this;
    return out.str();
}

template <class T>
inline std::ostream &operator << (std::ostream &out, const Interval<T> &ival)
{
    if (ival.is_empty()) {
        out << "[ ]";
    } else {
        out << "[" << ival.lower_ << "," << ival.upper_ << "]";
    }
    return out;
}

//-----------------------------------------------------------------------------
// IntervalIter
//-----------------------------------------------------------------------------

template <class T>
IntervalIter<T>::IntervalIter(Interval<T> *ival, T cur):
        ival_(ival), cur_(cur)
{
    // nothing to do
}

template <class T>
T &IntervalIter<T>::operator*()
{
    return cur_;
}

template <class T>
const T &IntervalIter<T>::operator*() const
{
    return const_cast<IntervalIter<T> *>(this)->operator*();
}

template <class T>
T *IntervalIter<T>::operator->()
{
    return &cur_;
}

template <class T>
const T *IntervalIter<T>::operator->() const
{
    return const_cast<IntervalIter<T> *>(this)->operator->();
}

template <class T>
IntervalIter<T> &IntervalIter<T>::operator++()
{
    cur_+=T(1);
    return *this;
}

template <class T>
const IntervalIter<T> &IntervalIter<T>::operator++() const
{
    return const_cast<IntervalIter<T> *>(this)->operator++();
}

template <class T>
IntervalIter<T> &IntervalIter<T>::operator++(int) const
{
    IntervalIter<T> ret(ival_, cur_);
    ++(*this);
    return ret;
}

template <class T>
bool IntervalIter<T>::operator==(const IntervalIter<T> &other) const
{
    return ival_ == other.ival_ && cur_ == other.cur_;
}

template <class T>
bool IntervalIter<T>::operator!=(const IntervalIter<T> &other) const
{
    return !((*this) == other);
}

} // namespace msat
#endif
