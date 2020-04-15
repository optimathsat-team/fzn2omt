// -*- C++ -*-
//
// Author: Giuseppe Spallitta <giuseppe.spallitta@unitn.it>

#ifndef MSAT_TOPLEVELINTERFACE_H_INCLUDED
#define MSAT_TOPLEVELINTERFACE_H_INCLUDED

#include "../api/environment.h"
#include "../parser/parserinterface.h"
#include "../utils/termination.h"
#include <istream>
#include <memory>

namespace msat {

class ToplevelInterface {
public:
    virtual ~ToplevelInterface() {}
    
    class TimeMemLimitTest: public TerminationTest {
        static const size_t BYTES_IN_MB = 1024 * 1024;
    public:
        TimeMemLimitTest(unsigned long millis, size_t max_mb):
            timeout_(millis), max_bytes_(max_mb * BYTES_IN_MB),
            last_check_time_(0)
        {
            reset();
        }

        void reset()
        {
            start_ = clock();
            last_check_time_ = 0;
        }

        void operator()() const throw(TerminationTest::terminated)
        {
        }
    private:
        unsigned long timeout_;
        size_t max_bytes_;
        clock_t start_;
        mutable double last_check_time_;
    };
    
};


class ToplevelInterfaceImpl: public ToplevelInterface {
public:
    ToplevelInterfaceImpl(Configuration *config);
    virtual ~ToplevelInterfaceImpl();


protected:
    virtual std::auto_ptr<ParserInterface> get_parser(TermManager *mgr) = 0;

private:

    TermManager mgr_;
    Configuration *config_;
    Environment *env_;
    double starttime_;
    double endtime_;
};

} // namespace msat

#endif // MSAT_TOPLEVELINTERFACE_H_INCLUDED
