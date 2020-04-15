// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// Various utility functions for manipulating strings 
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_STRUTILS_H_INCLUDED
#define MSAT_STRUTILS_H_INCLUDED

#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sstream>
#include <functional>
#include <memory>
#include <iterator>
#include <iomanip>
#include "../utils/xmalloc.h"

namespace msat { namespace str {

using std::string;

template<class S, class Op>
inline S str_transformer_(const S &s, Op op)
{
    S tmp;
    std::transform(s.begin(), s.end(), std::back_inserter(tmp), op);
    return tmp;
}

/** returns a copy of s in upper case */
inline string upper(const string &s)
{
    return str_transformer_(s, static_cast<int(*)(int)>(toupper));
}

/** returns a copy of s in lower case */
inline string lower(const string &s)
{
    return str_transformer_(s, static_cast<int(*)(int)>(tolower));
}


/** case insensitive string comparison */
template<class S, class Op>
inline int cmp_nocase(const S &s1, const S &s2, Op op)
{
    typename S::const_iterator i1 = s1.begin(), i2 = s2.begin();
    int res = 0;
    for(; i1 != s1.end() && i2 != s2.end(); ++i1, ++i2)
    {
	if((res = op(*i1) - op(*i2)) != 0) return res;
    }
    return (s1.length() < s2.length() ? -1 :
            (s1.length() == s2.length() ? 0 : 1));
}

inline int cmp_nocase(const string &s1, const string &s2)
{
    return cmp_nocase(s1, s2, static_cast<int(*)(int)>(toupper));
}

/** returns a copy of s without the initial whitespace */
/*template <class Pred>
inline string lstrip(const string &s, Pred is_space)
{
    string::const_iterator i = s.begin();
    while (i != s.end() && is_space(*i)) ++i;
    return string(i, s.end());
}*/

inline string lstrip(const string &s)
{
    string::const_iterator i = s.begin();
    while (i != s.end() && isspace(*i)) ++i;
    return string(i, s.end());
}

/** returns a copy of s without the final whitespace */
/*template <class Pred>
inline string rstrip(const string &s, Pred is_space)
{
    
}*/

inline string rstrip(const string &s)
{
    string::const_reverse_iterator i = s.rbegin();
    while (i != s.rend() && isspace(*i)) ++i;
    return string(s.begin(), i.base());
}


/** returns a copy of s without initial and final whitespace */
/*template <class Pred>
inline string strip(const string &s, Pred is_space)
{
    return lstrip(rstrip(s));
}*/

inline string strip(const string &s)
{
    return lstrip(rstrip(s));
}


inline bool startswith(const string &s, const string &what)
{
    if (s.length() >= what.length()) {
        for (size_t i = 0; i < what.length(); ++i) {
            if (s[i] != what[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}


inline bool endswith(const string &s, const string &what)
{
    if (s.length() >= what.length()) {
        size_t off = s.length() - what.length();
        for (size_t i = 0; i < what.length(); ++i) {
            if (s[i+off] != what[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}


/**
 * a generic string tokenizer
 */
class TokenizerBase;

class TokenIterator:
        public std::iterator<std::input_iterator_tag, std::string> {
public:
    TokenIterator(TokenizerBase *t, size_t cur_pos):
        t_(t), cur_pos_(cur_pos) {}

    typedef const value_type &const_reference;
    
    TokenIterator &operator++();
    const_reference operator*();
    const pointer operator->();

    bool operator==(const TokenIterator &other) const
    { return (t_ == other.t_ && cur_pos_ == other.cur_pos_); }

    bool operator!=(const TokenIterator &other) const
    { return !(*this == other); }

private:
    TokenizerBase *t_;
    size_t cur_pos_;
};


class TokenizerBase {
public:
    virtual ~TokenizerBase() {}
protected:    
    friend class TokenIterator;
    friend class Tokenizer;

    virtual TokenIterator begin() = 0;
    virtual TokenIterator end() = 0;

    virtual size_t next_pos() = 0;
    virtual string *cur_token() = 0;
};

//-----------------------------------------------------------------------------
// TokenIterator inline methods
//-----------------------------------------------------------------------------

inline TokenIterator::const_reference TokenIterator::operator*()
{
    return *(t_->cur_token());
}


inline const TokenIterator::pointer TokenIterator::operator->()
{
    return t_->cur_token();
}


inline TokenIterator &TokenIterator::operator++()
{
    cur_pos_ = t_->next_pos();
    return *this;
}


inline TokenIterator operator++(TokenIterator &iter, int)
{
    TokenIterator ret = iter;
    ++iter;
    return ret;
}

//-----------------------------------------------------------------------------

class Tokenizer {
private:
    Tokenizer(TokenizerBase *impl): impl_(impl) {}
public:
    ~Tokenizer() { if (impl_) delete impl_; }

    typedef TokenIterator iterator;
    iterator begin() { return impl_ ? impl_->begin() : end(); }
    iterator end()
    { return impl_ ? impl_->end() : TokenIterator(NULL, std::string::npos); }

    Tokenizer(const Tokenizer &other)
    {
        impl_ = other.impl_;
        const_cast<Tokenizer &>(other).impl_ = NULL;
    }

private:
    Tokenizer &operator=(const Tokenizer &other);

public:

    class IsDelim: public std::unary_function<char, bool> {
    public:
        IsDelim(const std::string &delims): delims_(delims) {}
        
        bool operator()(const char &c) const
        {
            return delims_.find(c) != std::string::npos;
        }

    private:
        std::string delims_;
    };

    struct IsSpace: public std::unary_function<char, bool> {
        bool operator()(const char &c) const { return isspace(c); }
    };


public:    
    template <class Pred>
    class TokenizerImpl: public TokenizerBase {
    public:
        TokenizerImpl(const string &s, const Pred &is_delim, size_t maxtokens):
            s_(s), is_delim_(is_delim), maxtokens_(maxtokens), ntokens_(0),
            cur_token_(""), cur_pos_(0) {}

        TokenIterator begin() { advance(); return TokenIterator(this, 0); }
        TokenIterator end() { return TokenIterator(this, std::string::npos); }

    private:
        void advance()
        {
            size_t j = cur_pos_;
            if (maxtokens_ == 0 || ntokens_ < maxtokens_) {
                for (size_t i = j; i < s_.length(); ++i) {
                    char cur = s_[i];
                    if (is_delim_(cur)) {
                        cur_pos_ = i+1;
                        cur_token_ = s_.substr(j, i-j);
                        ++ntokens_;
                        return;
                    }
                }
            }
            if (j < s_.length()) {
                cur_token_ = s_.substr(j);
            } else {
                cur_token_ = "";
            }
            cur_pos_ = std::string::npos;
        }

        size_t next_pos()
        {
            size_t ret = cur_pos_;
            if (ret != std::string::npos) {
                advance();
            }
            return ret;
        }
    
        string *cur_token() { return &cur_token_; }
        
        const string &s_;
        Pred is_delim_;
        size_t maxtokens_;
        size_t ntokens_;
        string cur_token_;
        size_t cur_pos_;
    };

private:
    template <class Pred>
    friend Tokenizer get_tokenizer(const string &s, const Pred &is_delim,
                                   size_t maxtokens);
    
    TokenizerBase *impl_;
};


template <class Pred>
inline Tokenizer get_tokenizer(const string &s, const Pred &is_delim,
                               size_t maxtokens)
{
    Tokenizer::TokenizerImpl<Pred> *impl =
        new Tokenizer::TokenizerImpl<Pred>(s, is_delim, maxtokens);
    return Tokenizer(impl);
}

template <class Pred>
inline Tokenizer get_tokenizer(const string &s, const Pred &is_delim)
{
    return get_tokenizer(s, is_delim, 0);
}

inline Tokenizer get_tokenizer(const string &s, size_t maxtokens=0)
{
    return get_tokenizer(s, Tokenizer::IsSpace(), maxtokens);
}

inline Tokenizer get_tokenizer(const string &s, const std::string &delims,
                               size_t maxtokens=0)
{
    return get_tokenizer(s, Tokenizer::IsDelim(delims), maxtokens);
}

inline Tokenizer get_tokenizer(const string &s, const char *delims,
                               size_t maxtokens=0)
{
    return get_tokenizer(s, Tokenizer::IsDelim(delims), maxtokens);
}


/** joins a sequence of tokens */
template<class Iter>
inline string join(const string &sep, Iter begin, Iter end)
{
    std::ostringstream out;
    if (begin != end) out << (*begin++);
    while (begin != end) out << sep << (*begin++);
    return out.str();
}

/** printf-like interface for strings. returns false on error */
inline bool format(string &s, const char *fmt, va_list args)
{
    int size = 256;
    char *tmp = new char[size];
    while (true) {
        if (!tmp) return false;
        int res = vsnprintf(tmp, size, fmt, args);
        if (res > -1 && res < size) break;
        else if (res > -1) size = res+1;
        else size *= 2;
        delete[] tmp;
        tmp = new char[size];
    }
    s = string(tmp);
    delete[] tmp;
    return true;
}

inline bool format(string &s, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    bool res = format(s, fmt, args);
    va_end(args);
    return res;
}

inline string format(const char *fmt, ...)
{
    string tmp;
    va_list args;
    va_start(args, fmt);
    format(tmp, fmt, args);
    va_end(args);
    return tmp;
}


inline char *cstrdup(const char *s, size_t n=0)
{
    if (!n) {
        n = strlen(s);
    }
    char *ret = xmalloc<char>(n + 1);
    if (ret) {
        strncpy(ret, s, n);
        ret[n] = '\0';
    }
    return ret;
}


inline std::string replace(char c, const char *repl, const std::string &s)
{
    std::ostringstream tmp;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == c) {
            tmp << repl;
        } else {
            tmp << s[i];
        }
    }
    return tmp.str();
}


template <class T>
inline std::string to_string(
    const T &val, std::ios_base::fmtflags flags=std::ios_base::fmtflags(),
    int precision=-1)
{
    std::ostringstream buf;
    buf << std::setiosflags(flags);
    if (precision >= 0) {
        buf << std::setprecision(precision);
    }
    buf << val;
    return buf.str();
}

}} // namespace msat::str

#endif // MSAT_STRUTILS_H_INCLUDED

