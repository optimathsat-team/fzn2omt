// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// wrappers C I/O structures (FILE *) with C++ streams
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.
//
// This relies on GNU libstdc++ extensions to do the wrapping efficiently.
// If these extensions are not present, we use a "minimal" streambuf
// implementation
//

#ifndef MSAT_CIOWRAP_H_INCLUDED
#define MSAT_CIOWRAP_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include "../msatconfig.h"

#ifdef HAVE_EXT_STDIO_FILEBUF_H
#  include <ext/stdio_filebuf.h>
#else
#  ifdef MSAT_WINDOWS
#    include <io.h>
#  else
#    include <unistd.h>
#  endif // MSAT_WINDOWS
#endif // HAVE_EXT_STDIO_FILEBUF_H

namespace msat {

#ifdef HAVE_EXT_STDIO_FILEBUF_H

typedef __gnu_cxx::stdio_filebuf<char> file_outbuf;
typedef __gnu_cxx::stdio_filebuf<char> file_inbuf;

#else

class file_outbuf: public std::streambuf {
public:
    file_outbuf(FILE *f, std::ios_base::openmode,
                size_t size = static_cast<size_t>(BUFSIZ)):
        file_(f)
    {
        bufsize_ = size ? size : 1;
        buffer_ = new char[bufsize_];
        // setp tells the base class about the output buffer size and the
        // current location (0)
        setp(buffer_, buffer_ + bufsize_);
    }

    ~file_outbuf()
    {
        sync();
        delete[] buffer_;
    }

    // sync is called to flush the buffer
    int sync()
    {
        // pptr() returns a pointer to the current position in the buffer,
        // pbase() to the beginning of the buffer
        if (pptr() > pbase()) {
            size_t n = pptr() - pbase();
            if (fwrite(buffer_, sizeof(char), n, file_) < n) {
                return -1;
            } else {
                fflush(file_);
            }
            setp(buffer_, buffer_ + bufsize_);
        }
        return 0;
    }

    // overflow is called when the buffer is full
    int overflow(int c)
    {
        if (sync() != 0) {
            return traits_type::eof();
        }
        if (c != EOF) {
            *pptr() = c;
            pbump(1);
        }
        return c;
    }

    FILE *file() { return file_; }

    int fd()
    {
#ifdef HAVE_FILENO
        return fileno(file_);
#else
        return -1;
#endif
    }

private:
    FILE *file_;
    char *buffer_;
    size_t bufsize_;
};


class file_inbuf: public std::streambuf {
public:
    file_inbuf(FILE *f, std::ios_base::openmode,
               size_t bufsz = static_cast<size_t>(BUFSIZ)):
        file_(f), bufsize_(bufsz)
    {
        buffer_ = new char[bufsize_];
        // setg tells the base class about the input buffer size and the
        // current location. Since the buffer is empty, we set the current
        // location to its end
        setg(buffer_, buffer_ + bufsize_, buffer_ + bufsize_);       
    }

    ~file_inbuf() { delete[] buffer_; }

    // underflow is called when the input buffer is empty
    int underflow()
    {
        // if the buffer is not full, we simply return the current char
        if (gptr() < egptr()) {
            return *gptr();
        }

        if (fd() != -1) {
            int n = read(fd(), buffer_, bufsize_);
            if (n == 0) {
                return traits_type::eof();
            } else {
                setg(buffer_, buffer_, buffer_ + n);
                return *gptr();
            }
        } else {
            int c = fgetc(file_);
            if (c == EOF) {
                return traits_type::eof();
            } else {
                setg(buffer_, buffer_, buffer_ + 1);
                *gptr() = c;
                return *gptr();
            }
        }
    }

    FILE *file() { return file_; }

    int fd()
    {
#ifdef HAVE_FILENO
        return fileno(file_);
#else
        return -1;
#endif
    }

private:
    FILE *file_;
    char *buffer_;
    size_t bufsize_;
};

#endif // HAVE_EXT_STDIO_FILEBUF_H

/**
 * returns an ostream that wraps the "out" FILE *. "out" must be already open
 * before invoking this function, and is *not* closed automatically!. After
 * invoking this function, operating on "out" directly (other than by
 * fclose()ing it when done) should be considered forbidden.
 */
class file_ostream: public std::ostream {
public:
    file_ostream(FILE *out): std::ostream(&buf), buf(out, std::ios::out) {}
private:
    file_outbuf buf;
};

/**
 * returns an istream that wraps the "in" FILE *. The same caveats as above
 * apply (i.e. you must close "in" explicitly, and this is the only thing you
 * can do with it after invoking this function)
 */
class file_istream: public std::istream {
public:
    file_istream(FILE *in): std::istream(&buf), buf(in, std::ios::in) {}
private:
    file_inbuf buf;
};

} // namespace msat

#endif // MSAT_CIOWRAP_H_INCLUDED
