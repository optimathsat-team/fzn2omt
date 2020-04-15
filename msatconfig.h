// -*- C++ -*-
//
// $MATHSAT5_LICENSE_BANNER_HERE$
// 
// Compile-time configuration settings 
// 
// Author: Alberto Griggio <griggio@fbk.eu>
//
// This file is part of MathSAT 5.

#define MATHSAT_NAME "MathSAT5"
/* #undef MSAT_MSVC */
#define USE_CUSTOM_HASH_MAP
#define USE_CUSTOM_REALLOC_VECTOR
/* #undef HAVE_EXT_HASH_MAP */
/* #undef HAVE_TR1_UNORDERED_MAP */
/* #undef HAVE_UNORDERED_MAP */
/* #undef LOGGING_SECTIONS_DISABLED */
#define HAVE_EXT_STDIO_FILEBUF_H
#define HAVE_FILENO
#define HAVE_ISATTY
/* #undef HAVE__ISATTY */
/* #undef MATHSAT_REENTRANT */
#define MSAT_UNSIGNED_ENUM 
/* #undef USE_GOOGLE_PROFILER */
/* #undef DPLL_TIMING_STATS */
/* #undef HAVE_LOCALTIME */
#define HAVE_LOCALTIME_R
#define HAVE_WARNING_PREPROC
#define USE_SPECIALIZED_IEEE_FLOATS
/* #undef MSAT_WINDOWS */

#define ENABLE_OPTIMATHSAT
#define ENABLE_FLATZINC

// for unit tests that need to access "private" data
#define msat_private_test public
