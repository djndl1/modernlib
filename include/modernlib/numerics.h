#ifndef MODERNLIB_NUMERICS_H_
#define MODERNLIB_NUMERICS_H_

#include "modernlib/basis.h"

#define clamp(value, min, max) \
_Generic((value), \
    uint8_t : clamp_uint8_t,     \
    uint16_t : clamp_uint16_t,     \
    uint32_t : clamp_uint32_t,     \
    uint64_t : clamp_uint64_t,     \
    int64_t : clamp_int64_t,     \
    int32_t : clamp_int32_t,     \
    int16_t : clamp_int16_t,     \
    int8_t : clamp_int8_t,     \
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

MODERNLIB_ALWAYS_INLINE
static inline
unsigned char clamp_unsigned_char(unsigned char value, unsigned char min, unsigned char max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
char clamp_char(char value, char min, char max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
signed char clamp_signed_char(signed char value, signed char min, signed char max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
short clamp_short(short value, short min, short max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned short clamp_unsigned_short(unsigned short value, unsigned short min, unsigned short max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned int clamp_unsigned_int(unsigned int value, unsigned int min, unsigned int max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
int clamp_int(int value, int min, int max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned long clamp_unsigned_long(unsigned long value, unsigned long min, unsigned long max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
long clamp_long(long value, long min, long max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned long long clamp_unsigned_long_long(unsigned long long value, unsigned long long min, unsigned long long max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}
MODERNLIB_ALWAYS_INLINE
static inline
long long clamp_long_long(long long value, long long min, long long max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
float clamp_float(float value, float min, float max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
double clamp_double(double value, double min, double max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
int8_t clamp_int8_t(int8_t value, int8_t min, int8_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
int16_t clamp_int16_t(int16_t value, int16_t min, int16_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
int32_t clamp_int32_t(int32_t value, int32_t min, int32_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
int64_t clamp_int64_t(int64_t value, int64_t min, int64_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
uint64_t clamp_uint64_t(uint64_t value, uint64_t min, uint64_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
uint32_t clamp_uint32_t(uint32_t value, uint32_t min, uint32_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
uint16_t clamp_uint16_t(uint16_t value, uint16_t min, uint16_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

MODERNLIB_ALWAYS_INLINE
static inline
uint8_t clamp_uint8_t(uint8_t value, uint8_t min, uint8_t max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}

#endif /* ifndef MODERNLIB_NUMERICS_H_ */
