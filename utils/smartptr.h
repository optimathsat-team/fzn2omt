// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Generic smart pointers with reference counting
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_SMARTPTR_H_INCLUDED
#define MSAT_SMARTPTR_H_INCLUDED

#include <stdint.h>

namespace msat {

template <class T>
class SharedPtr {
public:
    explicit SharedPtr(T *elem=0);
    ~SharedPtr();

    SharedPtr(const SharedPtr<T> &other);
    SharedPtr &operator=(const SharedPtr<T> &other);

    operator bool() const;
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;

    T *get();
    void reset(T *elem=0);

    long use_count() const;
    bool unique() const;

private:
    void destroy();
    
    struct Data {
        T *elem;
        long refs;

        Data(T *e, long r): elem(e), refs(r) {}
    };

    mutable Data *data_;
};


template <class T>
class UniquePtr {
public:
    explicit UniquePtr(T *elem=0);
    ~UniquePtr();

    operator bool() const;
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;

    T *get();
    const T *get() const;
    T *release();
    void reset(T *elem=0);

private:
    UniquePtr(const UniquePtr<T> &other);
    UniquePtr &operator=(const UniquePtr<T> &other);
    
    T *elem_;
};



//-----------------------------------------------------------------------------
// SharedPtr
//-----------------------------------------------------------------------------


template <class T>
SharedPtr<T>::SharedPtr(T *elem):
    data_(new Data(elem, 1))
{
}


template <class T>
SharedPtr<T>::~SharedPtr()
{
    destroy();
}


template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &other):
    data_(other.data_)
{
    ++data_->refs;
}


template <class T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other)
{
    destroy();
    data_ = other.data_;
    ++data_->refs;
    return *this;
}


template <class T>
SharedPtr<T>::operator bool() const
{
    return data_->elem;
}


template <class T>
T &SharedPtr<T>::operator*()
{
    return *(data_->elem);
}


template <class T>
const T &SharedPtr<T>::operator*() const
{
    return *(data_->elem);
}


template <class T>
T *SharedPtr<T>::operator->()
{
    return data_->elem;
}


template <class T>
const T *SharedPtr<T>::operator->() const
{
    return data_->elem;
}


template <class T>
T *SharedPtr<T>::get()
{
    return data_->elem;
}


template <class T>
void SharedPtr<T>::reset(T *elem)
{
    destroy();
    data_ = new Data(elem, 1);
}


template <class T>
long SharedPtr<T>::use_count() const
{
    return data_->refs;
}


template <class T>
bool SharedPtr<T>::unique() const
{
    return data_->refs == 1;
}


template <class T>
void SharedPtr<T>::destroy()
{
    --data_->refs;
    if (!data_->refs) {
        if (data_->elem) {
            delete data_->elem;
        }
        delete data_;
        data_ = 0;
    }
}


//-----------------------------------------------------------------------------
// UniquePtr
//-----------------------------------------------------------------------------

template <class T>
UniquePtr<T>::UniquePtr(T *elem):
    elem_(elem)
{
}


template <class T>
UniquePtr<T>::~UniquePtr()
{
    if (elem_) {
        delete elem_;
    }
}


template <class T>
UniquePtr<T>::operator bool() const
{
    return elem_;
}


template <class T>
T &UniquePtr<T>::operator*()
{
    return *elem_;
}


template <class T>
const T &UniquePtr<T>::operator*() const
{
    return *elem_;
}


template <class T>
T *UniquePtr<T>::operator->()
{
    return elem_;
}


template <class T>
const T *UniquePtr<T>::operator->() const
{
    return elem_;
}


template <class T>
T *UniquePtr<T>::get()
{
    return elem_;
}


template <class T>
const T *UniquePtr<T>::get() const
{
    return elem_;
}


template <class T>
void UniquePtr<T>::reset(T *elem)
{
    if (elem_) {
        delete elem_;
    }
    elem_ = elem;
}


template <class T>
T *UniquePtr<T>::release()
{
    T *ret = elem_;
    elem_ = 0;
    return ret;
}


} // namespace msat

#endif // MSAT_SMARTPTR_H_INCLUDED
