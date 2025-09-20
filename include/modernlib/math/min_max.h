#ifndef MODERNLIB_MIN_MAX_H_
#define MODERNLIB_MIN_MAX_H_

#include "modernlib/basis.h"
#include "modernlib/math/type_alias.h"

#ifdef __STDC_VERSION__

#undef max
#ifdef MODERNLIB_USE_FIXED_INT_NUMERIC_FUNCTIONS
#define max(l, r) \
_Generic((l - r), \
    uint8_t : max_uint8_t,     \
    uint16_t : max_uint16_t,     \
    uint32_t : max_uint32_t,     \
    uint64_t : max_uint64_t,     \
    int64_t : max_int64_t,     \
    int32_t : max_int32_t,     \
    int16_t : max_int16_t,     \
    int8_t : max_int8_t,      \
    double : max_double,     \
    long double : max_longdouble,     \
    float : max_float)(l, r)

#define min(l, r) \
_Generic((l - r), \
    uint8_t : min_uint8_t,     \
    uint16_t : min_uint16_t,     \
    uint32_t : min_uint32_t,     \
    uint64_t : min_uint64_t,     \
    int64_t : min_int64_t,     \
    int32_t : min_int32_t,     \
    int16_t : min_int16_t,     \
    int8_t : min_int8_t,      \
    double : min_double,     \
    long double : min_longdouble,     \
    float : min_float)(l, r)

#define minmax(l, r) \
_Generic((l - r), \
    uint8_t : minmax_uint8_t,     \
    uint16_t : minmax_uint16_t,     \
    uint32_t : minmax_uint32_t,     \
    uint64_t : minmax_uint64_t,     \
    int64_t : minmax_int64_t,     \
    int32_t : minmax_int32_t,     \
    int16_t : minmax_int16_t,     \
    int8_t : minmax_int8_t,      \
    double : minmax_double,     \
    long double : minmax_longdouble,     \
    float : minmax_float)(l, r)
#else
#define max(l) \
_Generic((l - r), \
    long double : max_longdouble,     \
    double : max_double,     \
    float : max_float,     \
    long long : max_longlong,     \
    unsigned long long : max_ulonglong,     \
    long : max_long,     \
    unsigned long : max_ulong,     \
    int : max_int,     \
    unsigned int : max_uint,     \
    unsigned short : max_ushort,     \
    short : max_short,     \
    signed char : max_schar,     \
    char : max_char,     \
    unsigned char : max_uchar)(l, r)

#define min(l) \
_Generic((l - r), \
    long double : min_longdouble,     \
    double : min_double,     \
    float : min_float,     \
    long long : min_longlong,     \
    unsigned long long : min_ulonglong,     \
    long : min_long,     \
    unsigned long : min_ulong,     \
    int : min_int,     \
    unsigned int : min_uint,     \
    unsigned short : min_ushort,     \
    short : min_short,     \
    signed char : min_schar,     \
    char : min_char,     \
    unsigned char : min_uchar)(l, r)

#define minmax(l) \
_Generic((l - r), \
    long double : minmax_longdouble,     \
    double : minmax_double,     \
    float : minmax_float,     \
    long long : minmax_longlong,     \
    unsigned long long : minmax_ulonglong,     \
    long : minmax_long,     \
    unsigned long : minmax_ulong,     \
    int : minmax_int,     \
    unsigned int : minmax_uint,     \
    unsigned short : minmax_ushort,     \
    short : minmax_short,     \
    signed char : minmax_schar,     \
    char : minmax_char,     \
    unsigned char : minmax_uchar)(l, r)
#endif

#endif

#ifdef MODERNLIB_USE_FIXED_INT_NUMERIC_FUNCTIONS

#define min_max_typename int8_t 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename int16_t 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename int32_t 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename int64_t 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename uint64_t 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename uint32_t 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename uint16_t 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename uint8_t
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename


#ifdef __GNUC__

#define min_max_typename int128 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename uint128 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#endif

#else

#define min_max_typename uchar 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename char 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename schar
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename short 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename ushort 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename uint 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename int 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename ulong 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename long 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename ulonglong 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename longlong 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#endif

#define min_max_typename float 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename double 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#define min_max_typename longdouble 
#include "modernlib/math/min_max_itf.h"
#undef min_max_typename

#endif /* ifndef MODERNLIB_MIN_MAX_H_


 */
