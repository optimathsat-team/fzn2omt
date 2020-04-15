// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef INTERVALSET_H_INCLUDED
#define INTERVALSET_H_INCLUDED

#include "../utils/interval.h"

#include<algorithm>
#include<vector>
#include<assert.h>
#include<iostream>
#include<sstream>

namespace msat {

template <class T> class IntervalSetValueIter;
template <class T> class IntervalSetSubsetIter;

//-----------------------------------------------------------------------------
// IntervalSet
//-----------------------------------------------------------------------------

template <class T>
class IntervalSet {
public:
    IntervalSet();
    IntervalSet(Interval<T> ival);
    virtual ~IntervalSet();

    void add(const Interval<T> &ival);

    T set_card() const;
    const T &lower() const;
    const T &upper() const;
    inline bool is_empty() const { return 0 == ivals_.size(); };
    inline bool is_fragmented() const { return 1 < ivals_.size(); };
    bool contains(const T &v) const;

    bool set_eq(const IntervalSet &other) const;
    bool set_neq(const IntervalSet &other) const;
    bool set_in(const T &el) const;
    bool set_le(const IntervalSet &other) const;
    bool set_lt(const IntervalSet &other) const;
    bool set_subset(const IntervalSet &other) const;

    IntervalSet set_symdiff(const IntervalSet &other) const;
    IntervalSet set_union(const IntervalSet &other) const;
    IntervalSet set_diff(const IntervalSet &other) const;
    IntervalSet set_intersect(const IntervalSet &other) const;

    ///< value iterator
    friend class IntervalSetValueIter<T>;
    typedef IntervalSetValueIter<T> value_iterator;
    typedef const IntervalSetValueIter<T> const_value_iterator;
    value_iterator value_begin();
    value_iterator value_end();
    value_iterator value_find(const T &value);
    const_value_iterator value_begin() const;
    const_value_iterator value_end() const;
    const_value_iterator value_find(const T &value) const;

    ///< sub-interval iterator
    friend class IntervalSetSubsetIter<T>;
    typedef IntervalSetSubsetIter<T> subset_iterator;
    typedef const IntervalSetSubsetIter<T> const_subset_iterator;
    subset_iterator subset_begin();
    subset_iterator subset_end();
    const_subset_iterator subset_begin() const;
    const_subset_iterator subset_end() const;

private:
    std::vector< Interval<T> > ivals_;
    Interval<T> empty_;

    std::string to_str() const;

    template <class U>
    friend IntervalSet<U> set_symdiff(const IntervalSet<U> &iset, const IntervalSet<U> &other);
    template <class U>
    friend IntervalSet<U> set_union(const IntervalSet<U> &iset, const IntervalSet<U> &other);
    template <class U>
    friend IntervalSet<U> set_diff(const IntervalSet<U> &iset, const IntervalSet<U> &other);
    template <class U>
    friend IntervalSet<U> set_intersect(const IntervalSet<U> &iset, const IntervalSet<U> &other);
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const IntervalSet<U> &ival);
};

//-----------------------------------------------------------------------------
// IntervalSetValueIter
//-----------------------------------------------------------------------------

template <class T>
class IntervalSetValueIter: public std::iterator<std::forward_iterator_tag, T> {
public:
    IntervalSetValueIter(IntervalSet<T> *sval, size_t idx,
                    typename Interval<T>::iterator cur);
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    IntervalSetValueIter &operator++();
    const IntervalSetValueIter &operator++() const;
    IntervalSetValueIter &operator++(int) const;
    bool operator==(const IntervalSetValueIter<T> &other) const;
    bool operator!=(const IntervalSetValueIter<T> &other) const;
private:
    IntervalSet<T> *sval_;
    size_t idx_;
    typename Interval<T>::iterator cur_;
};

//-----------------------------------------------------------------------------
// IntervalSetSubsetIter
//-----------------------------------------------------------------------------

template <class T>
class IntervalSetSubsetIter: public std::iterator<std::forward_iterator_tag, T> {
public:
    IntervalSetSubsetIter(IntervalSet<T> *sval,
                     typename std::vector< Interval<T> >::iterator cur);
    Interval<T> &operator*();
    const Interval<T> &operator*() const;
    Interval<T> *operator->();
    const Interval<T> *operator->() const;
    IntervalSetSubsetIter &operator++();
    const IntervalSetSubsetIter &operator++() const;
    IntervalSetSubsetIter &operator++(int) const;
    bool operator==(const IntervalSetSubsetIter<T> &other) const;
    bool operator!=(const IntervalSetSubsetIter<T> &other) const;
private:
    IntervalSet<T> *sval_;
    typename std::vector< Interval<T> >::iterator cur_;
};

//-----------------------------------------------------------------------------
// IntervalSet
//-----------------------------------------------------------------------------

template <class T>
IntervalSet<T>::IntervalSet()
{
    // nothing to do
}

template <class T>
IntervalSet<T>::IntervalSet(Interval<T> ival)
{
    this->add(ival);
}

template <class T>
IntervalSet<T>::~IntervalSet()
{
    // nothing to do
}

template <class T>
void IntervalSet<T>::add(const Interval<T> &ival)
{
    /**
     * Assumption: the two vectors are in canonic form
     */
    if (ival.is_empty()) {
        return;
    }
    typename std::vector< Interval<T> >::iterator it = ivals_.begin();
    for (typename std::vector< Interval<T> >::iterator next = it+1,
            end = ivals_.end(); it != end; ++it, ++next) {
        Interval<T> &iother = *it;
        if (ival.intersect(iother) || ival.adjacent(iother)) {
            iother.merge(ival);
            if (next != end) {
                if (iother.intersect(*next) || iother.adjacent(*next)) {
                    iother.merge(*next);
                    ivals_.erase(next);
                }
            }
            return; // no insert necessary
        }
        if (ival < iother) {
            break; // insert in current position
        }
    }
    ivals_.insert(it, ival);
}

template <class T>
T IntervalSet<T>::set_card() const
{
    T ret(0);
    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            end = ivals_.end(); it != end; ++it) {
        ret += it->card();
    }
    return ret;
}

template <class T>
inline const T &IntervalSet<T>::lower() const
{
    assert(!is_empty());
    return ivals_[0].lower();
}

template <class T>
inline const T &IntervalSet<T>::upper() const
{
    assert(!is_empty());
    return ivals_.back().upper();
}

template <class T>
bool IntervalSet<T>::contains(const T &v) const
{
    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            end = ivals_.end(); it != end; ++it) {
        if (it->contains(v)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool IntervalSet<T>::set_eq(const IntervalSet &other) const
{
    /**
     * Assumption: the two vectors are in canonic form
     */
    if (this->ivals_.size() != other.ivals_.size()) {
        return false;
    }
    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            ot = other.ivals_.begin(), end = ivals_.end(); it != end; ++it, ++ot) {
        if (*it != *ot) {
            return false;
        }
    }
    return true;
}

template <class T>
bool IntervalSet<T>::set_neq(const IntervalSet &other) const
{
    return !(this->set_eq(other));
}

template <class T>
bool IntervalSet<T>::set_in(const T &el) const
{
    /**
     * Assumption: the two vectors are in canonic form
     */
    Interval<T> singleton(el);
    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            end = ivals_.end(); it != end; ++it) {
        if (singleton < *it) {
            return false;
        }
        if (it->intersect(singleton)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool IntervalSet<T>::set_le(const IntervalSet &other) const
{
    if (this->set_subset(other)) {
        return true;
    }
    IntervalSet tmp = this->set_symdiff(other);
    if (tmp.ivals_.size() == 0) {
        return false;
    }
    T el = ivals_[0].lower_;
    return tmp.set_in(el);
}

template <class T>
bool IntervalSet<T>::set_lt(const IntervalSet &other) const
{
    if (this->set_subset(other)) {
        return this->set_neq(other);
    }
    IntervalSet tmp = this->set_symdiff(other);
    if (tmp.ivals_.size() == 0) {
        return false;
    }
    T el = ivals_[0].lower_;
    return tmp.set_in(el);
}

template <class T>
bool IntervalSet<T>::set_subset(const IntervalSet &other) const
{
    /**
     * Assumption: the two vectors are in canonic form
     */
    if (this->ivals_.size() == 0) {
        return true;
    }
    if (other.ivals_.size() == 0) {
        return false;
    }
    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            ot = other.ivals_.begin(), iend = ivals_.end(), oend = other.ivals_.end();
            it != iend && ot != oend;) {
        if (*it < *ot) {
            return false;
        } else {
            if (it->intersect(*ot)) {
                if (ot->contains(*it)) {
                    ++it; // match, check next element
                } else {
                    return false;
                }
            } else {
                ++ot;
                if (ot == oend) { // candidates exhaused
                    return false;
                }
            }
        }
    }
    return true;
}

template <class T>
IntervalSet<T> IntervalSet<T>::set_symdiff(const IntervalSet &other) const
{
    IntervalSet a_m_b = this->set_diff(other);
    IntervalSet b_m_a = other.set_diff(*this);
    return a_m_b.set_union(b_m_a);
}

template <class T>
IntervalSet<T> IntervalSet<T>::set_union(const IntervalSet &other) const
{
    IntervalSet ret;
    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            end = ivals_.end(); it != end; ++it) {
        ret.add(*it);
    }
    for (typename std::vector< Interval<T> >::const_iterator it = other.ivals_.begin(),
            end = other.ivals_.end(); it != end; ++it) {
        ret.add(*it);
    }
    return ret;
}

template <class T>
IntervalSet<T> IntervalSet<T>::set_diff(const IntervalSet &other) const
{
    bool cur_unset = true;
    IntervalSet<T> ret;
    Interval<T> cur;

    if (other.ivals_.size() == 0 || this->ivals_.size() == 0) {
        return (*this);
    }

    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            ot = other.ivals_.begin(), iend = ivals_.end(), oend = other.ivals_.end();
            it != iend && ot != oend;) {
        if (cur_unset) {
            cur = *it;
        }
        if (cur.intersect(*ot)) {
            if (ot->contains(cur)) {
                ++it;  // skip the whole set
                cur_unset = true;
            } else {
                if (cur < *ot) {
                    ret.add(Interval<T>(cur.lower_, ot->lower_ - T(1)));
                    cur = Interval<T>(ot->lower_, cur.upper_);
                } else {
                    cur = Interval<T>(ot->upper_ + T(1), cur.upper_);
                }
                cur_unset = false;
            }
        } else {
            if (cur < *ot) { // && dijoint!
                ret.add(cur);
                ++it;
                cur_unset = true;
            } else {
                ++ot;
                if (ot == oend) {
                    ret.add(cur);
                    ++it; // *it is superset of cur, skip it
                    for (; it != iend; ++it) { ret.add(*it); }
                    break;
                }
            }
        }
    }
    return ret;
}

template <class T>
IntervalSet<T> IntervalSet<T>::set_intersect(const IntervalSet &other) const
{
    bool cur_unset = true;
    IntervalSet<T> ret;
    Interval<T> cur;
    for (typename std::vector< Interval<T> >::const_iterator it = ivals_.begin(),
            ot = other.ivals_.begin(), iend = ivals_.end(), oend = other.ivals_.end();
            it != iend && ot != oend;) {
        if (cur_unset) {
            cur = *it;
        }
        if (cur.intersect(*ot)) {
            if (ot->contains(cur)) {
                ret.add(cur);
                ++it;
                cur_unset = true;
            } else {
                if (cur < *ot) {
                    cur = Interval<T>(ot->lower_, cur.upper_);
                } else {
                    ret.add(Interval<T>(cur.lower_, ot->upper_));
                    cur = Interval<T>(ot->upper_ + T(1), cur.upper_);
                }
                cur_unset = false;
            }
        } else {
            if (cur < *ot) { // && dijoint!
                ++it;
                cur_unset = true;
            } else {
                ++ot;
            }
        }
    }
    return ret;
}

template <class T>
typename IntervalSet<T>::value_iterator IntervalSet<T>::value_begin()
{
    if (ivals_.size() > 0) {
        return IntervalSet<T>::value_iterator(this, 0, ivals_[0].begin());
    } else {
        return IntervalSet<T>::value_iterator(this, 0, empty_.end());
    }
}

template <class T>
typename IntervalSet<T>::value_iterator IntervalSet<T>::value_end()
{
    return IntervalSet<T>::value_iterator(this, this->ivals_.size(), empty_.end());
}

template <class T>
typename IntervalSet<T>::value_iterator IntervalSet<T>::value_find(const T &value)
{
    IntervalSet<T>::value_iterator it = value_begin();
    for (typename IntervalSet<T>::value_iterator end = value_end(); it != end; ++it) {
        if (value == *it) {
            return it;
        }
    }
    return it;
}

template <class T>
typename IntervalSet<T>::const_value_iterator IntervalSet<T>::value_begin() const
{
   return const_cast<IntervalSet<T> *>(this)->value_begin();
}

template <class T>
typename IntervalSet<T>::const_value_iterator IntervalSet<T>::value_end() const
{
    return const_cast<IntervalSet<T> *>(this)->value_end();
}

template <class T>
typename IntervalSet<T>::const_value_iterator IntervalSet<T>::value_find(const T &value) const
{
    return const_cast<IntervalSet<T> *>(this)->value_find(value);
}

template <class T>
typename IntervalSet<T>::subset_iterator IntervalSet<T>::subset_begin()
{
    if (ivals_.size() > 0) {
        return IntervalSet<T>::subset_iterator(this, ivals_.begin());
    } else {
        return IntervalSet<T>::subset_iterator(this, ivals_.end());
    }
}

template <class T>
typename IntervalSet<T>::subset_iterator IntervalSet<T>::subset_end()
{
    return IntervalSet<T>::subset_iterator(this, ivals_.end());
}

template <class T>
typename IntervalSet<T>::const_subset_iterator IntervalSet<T>::subset_begin() const
{
   return const_cast<IntervalSet<T> *>(this)->subset_begin();
}

template <class T>
typename IntervalSet<T>::const_subset_iterator IntervalSet<T>::subset_end() const
{
    return const_cast<IntervalSet<T> *>(this)->subset_end();
}

template <class T>
inline IntervalSet<T> set_symdiff(const IntervalSet<T> &sval, const IntervalSet<T> &other)
{
    return sval.set_symdiff(other);
}

template <class T>
inline IntervalSet<T> set_union(const IntervalSet<T> &sval, const IntervalSet<T> &other)
{
    return sval.set_union(other);
}

template <class T>
inline IntervalSet<T> set_diff(const IntervalSet<T> &sval, const IntervalSet<T> &other)
{
    return sval.set_diff(other);
}

template <class T>
inline IntervalSet<T> set_intersect(const IntervalSet<T> &sval, const IntervalSet<T> &other)
{
    return sval.set_intersect(other);
}

template <class T>
std::string IntervalSet<T>::to_str() const
{
    std::ostringstream out;
    out << *this;
    return out.str();
}

template <class T>
inline std::ostream &operator << (std::ostream &out, const IntervalSet<T> &sval)
{
    out << "{ ";
    for (typename std::vector< Interval<T> >::const_iterator it = sval.ivals_.begin(),
            end = sval.ivals_.end(); it != end; ++it) {
        out << *it << " ";
    }
    out << "}";
    return out;
}

//-----------------------------------------------------------------------------
// IntervalSetValueIter
//-----------------------------------------------------------------------------

template <class T>
IntervalSetValueIter<T>::IntervalSetValueIter(IntervalSet<T> *sval, size_t idx,
    typename Interval<T>::iterator cur):
        sval_(sval), idx_(idx), cur_(cur)
{
    // nothing to do
}

template <class T>
T &IntervalSetValueIter<T>::operator*()
{
    return *cur_;
}

template <class T>
const T &IntervalSetValueIter<T>::operator*() const
{
    return const_cast<IntervalSetValueIter<T> *>(this)->operator*();
}

template <class T>
T *IntervalSetValueIter<T>::operator->()
{
    return &(*cur_);
}

template <class T>
const T *IntervalSetValueIter<T>::operator->() const
{
    return const_cast<IntervalIter<T> *>(this)->operator->();
}

template <class T>
IntervalSetValueIter<T> &IntervalSetValueIter<T>::operator++()
{
    if (idx_ < sval_->ivals_.size()) {
        ++cur_;
        if (cur_ == sval_->ivals_[idx_].end()) {
           ++idx_;
            if (idx_ < sval_->ivals_.size()) {
                cur_ = sval_->ivals_[idx_].begin();
            } else {
                cur_ = sval_->empty_.end();
            }
        }
    }
    return *this;
}

template <class T>
const IntervalSetValueIter<T> &IntervalSetValueIter<T>::operator++() const
{
    return const_cast<IntervalSetValueIter<T> *>(this)->operator++();
}

template <class T>
IntervalSetValueIter<T> &IntervalSetValueIter<T>::operator++(int) const
{
    IntervalSetValueIter<T> ret(sval_, idx_, cur_);
    ++(*this);
    return ret;
}

template <class T>
bool IntervalSetValueIter<T>::operator==(const IntervalSetValueIter<T> &other) const
{
    return sval_ == other.sval_
           && idx_ == other.idx_
           && cur_ == other.cur_;
}

template <class T>
bool IntervalSetValueIter<T>::operator!=(const IntervalSetValueIter<T> &other) const
{
    return !((*this) == other);
}

//-----------------------------------------------------------------------------
// IntervalSetSubsetIter
//-----------------------------------------------------------------------------

template <class T>
IntervalSetSubsetIter<T>::IntervalSetSubsetIter(IntervalSet<T> *sval,
    typename std::vector< Interval<T> >::iterator cur):
        sval_(sval), cur_(cur)
{
    // nothing to do
}

template <class T>
Interval<T> &IntervalSetSubsetIter<T>::operator*()
{
    return *cur_;
}

template <class T>
const Interval<T> &IntervalSetSubsetIter<T>::operator*() const
{
    return const_cast<IntervalSetSubsetIter<T> *>(this)->operator*();
}

template <class T>
Interval<T> *IntervalSetSubsetIter<T>::operator->()
{
    return &(*cur_);
}

template <class T>
const Interval<T> *IntervalSetSubsetIter<T>::operator->() const
{
    return const_cast<IntervalIter<T> *>(this)->operator->();
}

template <class T>
IntervalSetSubsetIter<T> &IntervalSetSubsetIter<T>::operator++()
{
    ++cur_;
    return *this;
}

template <class T>
const IntervalSetSubsetIter<T> &IntervalSetSubsetIter<T>::operator++() const
{
    return const_cast<IntervalSetSubsetIter<T> *>(this)->operator++();
}

template <class T>
IntervalSetSubsetIter<T> &IntervalSetSubsetIter<T>::operator++(int) const
{
    IntervalSetSubsetIter<T> ret(sval_, cur_);
    ++(*this);
    return ret;
}

template <class T>
bool IntervalSetSubsetIter<T>::operator==(const IntervalSetSubsetIter<T> &other) const
{
    return sval_ == other.sval_
           && cur_ == other.cur_;
}

template <class T>
bool IntervalSetSubsetIter<T>::operator!=(const IntervalSetSubsetIter<T> &other) const
{
    return !((*this) == other);
}

} // namespace msat
#endif
