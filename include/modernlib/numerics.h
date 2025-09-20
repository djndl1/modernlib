#ifndef MODERNLIB_NUMERICS_H_
#define MODERNLIB_NUMERICS_H_

#include "modernlib/basis.h"

#ifdef __STDC_VERSION__

#ifdef MODERNLIB_USE_FIXED_INT_NUMERICS
#define clamp(value, min, max) \
_Generic((value + min - max), \
    uint8_t : clamp_uint8_t,     \
    uint16_t : clamp_uint16_t,     \
    uint32_t : clamp_uint32_t,     \
    uint64_t : clamp_uint64_t,     \
    int64_t : clamp_int64_t,     \
    int32_t : clamp_int32_t,     \
    int16_t : clamp_int16_t,     \
    int8_t : clamp_int8_t,      \
    double : clamp_double,     \
    long double : clamp_long_double,     \
    float : clamp_float)(value, min, max)
#else
#define clamp(value, min, max) \
_Generic((value + min - max), \
    long double : clamp_long_double,     \
    double : clamp_double,     \
    float : clamp_float,     \
    long long : clamp_long_long,     \
    unsigned long long : clamp_unsigned_long_long,     \
    long : clamp_long,     \
    unsigned long : clamp_unsigned_long,     \
    int : clamp_int,     \
    unsigned int : clamp_unsigned_int,     \
    unsigned short : clamp_unsigned_short,     \
    short : clamp_short,     \
    signed char : clamp_signed_char,     \
    char : clamp_char,     \
    unsigned char : clamp_unsigned_char)(value, min, max)
#endif

#endif

#define clamp_typename unsigned char 
#define clamp_funcname clamp_unsigned_char
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename char 
#define clamp_funcname clamp_char
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename signed char 
#define clamp_funcname clamp_signed_char
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename short 
#define clamp_funcname clamp_short
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename unsigned short 
#define clamp_funcname clamp_unsigned_short
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename unsigned int 
#define clamp_funcname clamp_unsigned_int
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename int 
#define clamp_funcname clamp_int
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename unsigned long 
#define clamp_funcname clamp_unsigned_long 
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename long 
#define clamp_funcname clamp_long
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename unsigned long long 
#define clamp_funcname clamp_unsigned_long_long
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename long long 
#define clamp_funcname clamp_long_long
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename float 
#define clamp_funcname clamp_float
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename double 
#define clamp_funcname clamp_double
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename long double 
#define clamp_funcname clamp_long_double
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#ifdef MODERNLIB_USE_FIXED_INT_NUMERICS

#define clamp_typename int8_t 
#define clamp_funcname clamp_int8_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename int16_t 
#define clamp_funcname clamp_int16_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename int32_t 
#define clamp_funcname clamp_int32_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename int64_t 
#define clamp_funcname clamp_int64_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename uint64_t 
#define clamp_funcname clamp_uint64_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename uint32_t 
#define clamp_funcname clamp_uint32_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename uint16_t 
#define clamp_funcname clamp_uint16_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename uint8_t
#define clamp_funcname clamp_uint8_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#ifdef __GNUC__

#define clamp_typename __int128 
#define clamp_funcname clamp_int128_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#define clamp_typename unsigned __int128 
#define clamp_funcname clamp_uint128_t
#include "modernlib/clamp_itf.h"
#undef clamp_typename
#undef clamp_funcname

#endif

#endif

#endif /* ifndef MODERNLIB_NUMERICS_H_ */
