// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// A helper class to temporarily set a variable to a given value, and reset it
// upon destruction
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_VARSETTER_H_INCLUDED
#define MSAT_VARSETTER_H_INCLUDED

namespace msat {

template <class T>
class VarSetter {
public:
    VarSetter(T &target, const T &curval, const T &resetval):
        target_(target), resetval_(resetval)
    {
        target_ = curval;
    }

    VarSetter(T &target, const T &curval):
        target_(target), resetval_(target)
    {
        target_ = curval;
    }

    ~VarSetter()
    {
        target_ = resetval_;
    }

private:
    T &target_;
    T resetval_;
};


template <class T, class Obj>
class VarMethodSetter {
public:
    typedef void (Obj::* Meth)(T);
    
    VarMethodSetter(Obj *target, Meth method,
                    const T &curval, const T &resetval):
        target_(target), method_(method), resetval_(resetval)
    {
        (target_->*method_)(curval);
    }

    ~VarMethodSetter()
    {
        (target_->*method_)(resetval_);
    }

private:
    Obj *target_;
    Meth method_;
    T resetval_;
};


} // namespace msat

#endif // MSAT_VARSETTER_H_INCLUDED
