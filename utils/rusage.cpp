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

#include "../utils/rusage.h"
#include "../msatconfig.h"

#ifdef MSAT_WINDOWS
#  include <windows.h>
#  include <psapi.h>
#  include <time.h>
#else 
#  include <sys/time.h>
#  include <sys/resource.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <unistd.h>
#  include <fcntl.h>
#  include <stdlib.h>
#endif // MSAT_WINDOWS

#ifdef __APPLE__
#  include <malloc/malloc.h>
#endif // __APPLE__

#include <stdio.h>


namespace msat {

double get_cpu_time_sec()
{
#ifdef MSAT_WINDOWS
    HANDLE self = GetCurrentProcess();
    FILETIME tcreation, texit, tkernel, tuser;
    if (GetProcessTimes(self, &tcreation, &texit, &tkernel, &tuser)) {
        double ret = 0;
        ULARGE_INTEGER tmp;
        tmp.LowPart = tkernel.dwLowDateTime;
        tmp.HighPart = tkernel.dwHighDateTime;
        ret += double(tmp.QuadPart) / 10000000;
        tmp.LowPart = tuser.dwLowDateTime;
        tmp.HighPart = tuser.dwHighDateTime;
        ret += double(tmp.QuadPart) / 10000000;
        return ret;
    } else {
        return (double)clock() / CLOCKS_PER_SEC;
    }
#else
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    double total = double(ru.ru_utime.tv_sec) +
        double(ru.ru_utime.tv_usec) / 1000000;
    total += double(ru.ru_stime.tv_sec) +
        double(ru.ru_stime.tv_usec) / 1000000;
    return total;
#endif
}


namespace {

size_t read_mem_stat(int field)
{
#ifdef __linux__
    /*
     * Fields of /proc/[pid]/statm (taken from man proc(5)):
     * 
     *  size       total program size
     *             (same as VmSize in /proc/[pid]/status)
     *  resident   resident set size
     *             (same as VmRSS in /proc/[pid]/status)
     *  share      shared pages (from shared mappings)
     *  text       text (code)
     *  lib        library (unused in Linux 2.6)
     *  data       data + stack
     *  dt         dirty pages (unused in Linux 2.6)
     *
     */
    static const size_t buf_sz = 1024;
    char buffer[buf_sz];
    pid_t pid = getpid();
    sprintf(buffer, "/proc/%d/statm", pid);
    int fd = open(buffer, O_RDONLY|O_NOATIME);
    if (fd < 0) {
        return 0;
    }
    int value = 0;
    if (read(fd, buffer, buf_sz) > 0) {
        // look for the field we want
        char *s = buffer;
        if (field > 0) {
            for (size_t i = 0; i < buf_sz; ++i) {
                if (buffer[i] == ' ') {
                    if (--field == 0) {
                        s = buffer+i+1;
                        break;
                    }
                }
            }
        }
        value = atoi(s);
    }
    close(fd);
    return value;
#else
    return 0;
#endif // __linux__
}

} // namespace

size_t get_mem_used_bytes()
{
#ifdef __linux__
    static size_t pagesz = size_t(getpagesize());
    return size_t(read_mem_stat(1)) * pagesz;
#elif defined MSAT_WINDOWS
    HANDLE self = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS stats;
    if (GetProcessMemoryInfo(self, &stats, sizeof(stats))) {
        return stats.PeakWorkingSetSize;
    } else {
        return 0;
    }
#elif defined __APPLE__
    malloc_statistics_t t;
    malloc_zone_statistics(NULL, &t);
    return t.max_size_in_use;
#else
    return 0;
#endif // __linux__, MSAT_WINDOWS, __APPLE__
}


size_t get_mem_allocated_bytes()
{
#ifdef __linux__
    size_t m = read_mem_stat(2) + read_mem_stat(3);
    return size_t(read_mem_stat(0) - m) * size_t(getpagesize());
#elif defined MSAT_WINDOWS
    HANDLE self = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS stats;
    if (GetProcessMemoryInfo(self, &stats, sizeof(stats))) {
        return stats.PeakPagefileUsage;
    } else {
        return 0;
    }
#elif defined __APPLE__
    malloc_statistics_t t;
    malloc_zone_statistics(NULL, &t);
    return t.size_allocated;    
#else
    return 0;
#endif // __linux__, MSAT_WINDOWS, __APPLE__
}


size_t get_total_system_memory_bytes()
{
#ifdef __linux__
    FILE *in = fopen("/proc/meminfo", "r");
    if (in == NULL) return 0;
    int value;
    if (fscanf(in, "MemTotal: %d kB", &value) == 1) {
        return value * 1024;
    } else {
        return 0;
    }
#elif defined MSAT_WINDOWS
    MEMORYSTATUS stats;
    GlobalMemoryStatus(&stats);
    return stats.dwTotalPhys;
#elif defined __APPLE__
    return mstats().bytes_total;
#else
    return 0;
#endif // __linux__ / MSAT_WINDOWS / __APPLE__
}


struct tm get_local_time(const time_t *timep)
{
    struct tm ret = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
#ifdef HAVE_LOCALTIME
    struct tm *tmp = localtime(timep);
    if (tmp) {
        ret = *tmp;
    }
#elif defined HAVE_LOCALTIME_R
    localtime_r(timep, &ret);
#endif
    return ret;
}

} // namespace msat
