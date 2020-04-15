// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
//
//
// gets resources usage of the program (CPU time and memory)
//
// NOTE 1: The memory stats part is copied from MiniSat v1.14
// NOTE 2: In general, the memory usage stats are not very accurate for
// Linux. See e.g. http://www.kdedevelopers.org/node/1445 for a good
// discussion of the issues
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#ifndef MSAT_RUSAGE_H_INCLUDED
#define MSAT_RUSAGE_H_INCLUDED

#include <stddef.h>
#include <time.h>

namespace msat {

double get_cpu_time_sec();
///< returns the total execution time

size_t get_mem_used_bytes();
///< returns the total amount of RAM used so far, including the
///< memory for loading the program and the needed shared libraries

size_t get_mem_allocated_bytes();
///< returns the total amount of RAM dynamically allocated so far

size_t get_total_system_memory_bytes();
///< returns the total amount of RAM of the current machine

struct tm get_local_time(const time_t *timep);
///< portable and thread-safe localtime() function

} // namespace msat

#endif // MSAT_RUSAGE_H_INCLUDED
