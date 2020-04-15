// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Defines the Exception class, the root of all exceptions raised by MathSAT
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_EXCEPTION_H_INCLUDED
#define MSAT_EXCEPTION_H_INCLUDED

#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <assert.h>
#include <signal.h>


namespace msat {

#ifndef NDEBUG
extern volatile sig_atomic_t exceptions_dump_and_raise_assertion;
#endif

/**
 * The root of the hierarchy of exceptions raised by MathSAT
 */
class Exception: public std::exception {
public:
    Exception(const std::string &msg="", bool dump=true): buf_()
    {
        buf_ << msg;
        if (dump) {
            dump_msg_and_raise_assertion();
        }
    }

    virtual ~Exception() throw() {}

    const std::string &get_msg() const { return (msg_ = buf_.str()); }

    template <class T>
    Exception &operator<<(const T &t)
    {
        buf_ << t;
        return *this;
    }

    // custom copy constructor and assignment
    Exception(const Exception &other):
        buf_()
    {
        buf_ << other.get_msg();
    }
    
    Exception &operator=(const Exception &other)
    {
        buf_.str("");
        buf_ << other.get_msg();
        return *this;
    }

    const char *what() const throw()
    {
        try {
            return get_msg().c_str();
        } catch (...) {
            return "";
        }
    }

private:
    void dump_msg_and_raise_assertion() throw();
    
    std::ostringstream buf_;
    mutable std::string msg_;
};


#define MSAT_DECLARE_EXCEPTION(name)                                \
    struct name: public msat::Exception {                           \
        name(const std::string &msg=""): msat::Exception(msg) {}    \
        ~name() throw() {}                                          \
    };                                                              

} // namespace msat

#endif // MSAT_EXCEPTION_H_INCLUDED
