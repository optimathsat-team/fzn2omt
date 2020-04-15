// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
// Author: Patrick Trentin <patrick.trentin@unitn.it>
//
// This file is part of OptiMathSAT.

#ifndef FLATZINCDOMAIN_H_INCLUDED
#define FLATZINCDOMAIN_H_INCLUDED

#include "../utils/intervalset.h"
#include<iostream>
#include<vector>

using namespace std;

namespace msat {

typedef enum {
    FZN_BOOL = 1,
    FZN_INT = 2,
    FZN_FLOAT = 4,
    FZN_NUMERIC = 6
} FznType;

//-----------------------------------------------------------------------------
// FlatZincDomain Class
//-----------------------------------------------------------------------------

template <class T>
class FlatZincDomain {
public:
    FlatZincDomain(FznType type);
    FlatZincDomain(FznType type, T lower, T upper);
    FlatZincDomain(FznType type, std::vector<T> &values);
    virtual ~FlatZincDomain();

    bool is_empty() const;
    bool is_unbounded() const;
    bool is_fragmented() const;
    bool is_single_valued() const;
    bool is_zero_one_domain() const;
    bool contains(T &v) const;

    void apply_domain_restriction(const FlatZincDomain &other);

    const T &lower() const;
    const T &upper() const;
    const IntervalSet<T> &domain_values() const;
    inline const FznType type() const { return type_; };
    
private:
    const FznType type_;
    ///< type declaration
    IntervalSet<T> domain_;
    ///< allowed values
    bool is_unbounded_;
    ///< TRUE if domain is not restricted
    bool is_zero_one_;
    ///< TRUE if domain is { 0, 1 }
};

//-----------------------------------------------------------------------------
// FlatZincDomain Methods
//-----------------------------------------------------------------------------

template<class T>
FlatZincDomain<T>::FlatZincDomain(FznType type):
        type_(type), is_unbounded_(true), is_zero_one_(false)
{
    // nothing to do
}

template<class T>
FlatZincDomain<T>::FlatZincDomain(FznType type, T lower, T upper):
        type_(type), is_unbounded_(false)
{
    domain_.add(Interval<T>(lower, upper));

    if (type_ == FZN_INT &&
            upper == T(1) && lower == T(0)) {
        is_zero_one_ = true;
    } else {
        is_zero_one_ = false;
    }
}

template<class T>
FlatZincDomain<T>::FlatZincDomain(FznType type, std::vector<T> &values):
        type_(type), is_unbounded_(false)
{
    for (typename std::vector<T>::iterator it = values.begin(),
            end = values.end(); it != end; ++it) {
        domain_.add(Interval<T>(*it, *it));
    }

    if (type_ == FZN_INT &&
            domain_.upper() == T(1) && domain_.lower() == T(0)) {
        is_zero_one_ = true;
    } else {
        is_zero_one_ = false;
    }
}

template<class T>
FlatZincDomain<T>::~FlatZincDomain()
{
    // nothing to do
}

template<class T>
bool FlatZincDomain<T>::is_empty() const
{
    return !is_unbounded_ && domain_.is_empty();
}

template<class T>
bool FlatZincDomain<T>::is_unbounded() const
{
    return is_unbounded_;
}

template<class T>
bool FlatZincDomain<T>::is_fragmented() const
{
    return domain_.is_fragmented();
}

template<class T>
bool FlatZincDomain<T>::is_single_valued() const
{
    return (upper() - lower() == T(0));
}

template<class T>
bool FlatZincDomain<T>::is_zero_one_domain() const
{
    return is_zero_one_;
}

template<class T>
bool FlatZincDomain<T>::contains(T &v) const
{
    if (type_ != FZN_BOOL) {
        return is_unbounded_ || domain_.contains(v);
    }
    return false;
}

template<class T>
void FlatZincDomain<T>::apply_domain_restriction(
    const FlatZincDomain<T> &other)
{
    if (!other.is_unbounded_) {
        if (is_unbounded_) {
            domain_ = other.domain_;
            is_unbounded_ = false;
        } else {
            domain_ = domain_.set_intersect(other.domain_);
        }
    }
}

template<class T>
const T &FlatZincDomain<T>::lower() const
{
    return domain_.lower();
}

template<class T>
const T &FlatZincDomain<T>::upper() const
{
    return domain_.upper();
}

template<class T>
const IntervalSet<T> &FlatZincDomain<T>::domain_values() const
{
    return domain_;
}

} // namespace msat

#endif
