// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Interface for parsers of various input formats
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_PARSERINTERFACE_H_INCLUDED
#define MSAT_PARSERINTERFACE_H_INCLUDED

#include "../terms/termmanager.h"
#include "../utils/exception.h"
#include "../utils/xmalloc.h"
#include "../utils/strutils.h"
#include <iostream>

namespace msat {

class ParserInterface {
public:
    MSAT_DECLARE_EXCEPTION(error)

    class str_alloc {
    public:
        str_alloc(): taken_(false) {}

        char *str_dup(const char *s, int n)
        {
            if (taken_ || n >= str_len_) {
                return str::cstrdup(s);
            } else {
                taken_ = true;
                memcpy(str_, s, n+1);
                return str_;
            }
        }
        
        void str_free(char *s)
        {
            if (s == str_) {
                taken_ = false;
            } else {
                xfree(s);
            }
        }
        
    private:
        static const int str_len_ = 256;
        bool taken_;
        char str_[str_len_];
    };
    struct istream_info {
        std::istream *stream;
        str_alloc *alloc;
        bool done;

        istream_info(std::istream *s=NULL, str_alloc *a=NULL):
            stream(s), alloc(a), done(false) {}
    };
    
    ParserInterface(/*TermManager *mgr): mgr_(mgr*/) {}
    virtual ~ParserInterface() {}

    virtual Term parse(std::istream &source) = 0;
    ///< parse the given source stream, and return the term corresponding to
    ///< the parsed formula
    
    virtual std::string get_logic() const { return ""; }
    ///< for input formats that support a logic attribute (e.g. SMT-LIB),
    ///< this returns the logic name

    enum status {
        UNKNOWN,
        UNSAT,
        SAT
    };
    virtual status get_status() const { return UNKNOWN; }
    ///< for input formats that support a status attribute (e.g. SMT-LIB),
    ///< this returns the parsed status

    static int flex_get_input(std::istream *source, char *buf, size_t max_size);
    ///< convenience function to make Flex parse from a C++ istream instead of
    ///< a FILE *. This can be used by defining the macro YY_INPUT like this:
    ///<
    ///< #define YY_INPUT(buf,result,max_size) 
    ///<       result = ParserInterface::flex_get_input(istream, buf, max_size)
    ///<

protected:
    TermManager *mgr_;
};


inline
int ParserInterface::flex_get_input(std::istream *source,
                                    char *buf, size_t max_size)
{
    char c;
    if (!max_size) {
        return 0;
    } else if (source->readsome(buf, max_size) || source->eof()) {
        return int(source->gcount());
    } else if (source->get(c)) {
        *buf = c;
        int r = flex_get_input(source, buf+1, max_size-1);
        return 1 + r;
    } else {
        return 0;
    }
}


} // namespace msat

#endif // MSAT_PARSERINTERFACE_H_INCLUDED
