#ifndef MODERNLIB_REINTERPRET_H_
#define MODERNLIB_REINTERPRET_H_ 

#include "modernlib/basis.h"
#include <string.h>

MODERNLIB_ALWAYS_INLINE
static inline
unsigned char reinterpret_char_as_unsigned(char value)
{
    unsigned char result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned char reinterpret_signed_char_as_unsigned(signed char value)
{
    unsigned char result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned short reinterpret_short_as_unsigned(short value)
{
    unsigned short result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned int reinterpret_int_as_unsigned(int value)
{
    unsigned int result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

MODERNLIB_ALWAYS_INLINE
static inline
unsigned long reinterpret_long_as_unsigned(long value)
{
    unsigned long result;
    memcpy(&result, &value, sizeof(result));
    return result;
}
MODERNLIB_ALWAYS_INLINE
static inline
unsigned long long reinterpret_long_long_as_unsigned(long long value)
{
    unsigned long long result;
    memcpy(&result, &value, sizeof(result));
    return result;
}
MODERNLIB_ALWAYS_INLINE
static inline
uint8_t reinterpret_int8_t_as_unsigned(int8_t value)
{
    uint8_t result;
    memcpy(&result, &value, sizeof(result));
    return result;
}
MODERNLIB_ALWAYS_INLINE
static inline
uint16_t reinterpret_int16_t_as_unsigned(int16_t value)
{
    uint16_t result;
    memcpy(&result, &value, sizeof(result));
    return result;
}
MODERNLIB_ALWAYS_INLINE
static inline
uint32_t reinterpret_int32_t_as_unsigned(int32_t value)
{
    uint32_t result;
    memcpy(&result, &value, sizeof(result));
    return result;
}
MODERNLIB_ALWAYS_INLINE
static inline
uint64_t reinterpret_int64_t_as_unsigned(int64_t value)
{
    uint64_t result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

#endif /* ifndef MODERNLIB_REINTERPRET_H_ */
