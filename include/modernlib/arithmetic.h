#ifndef MODERNLIB_ARITHMETIC_H_
#define MODERNLIB_ARITHMETIC_H_

#include "modernlib/basis.h"

#define euclidean_modulo(a, b) \
    _Generic((a / b),          \
            signed char: euclidean_modulo_signed_char \
            short: euclidean_modulo_short \
            int: euclidean_modulo_int \
            long: euclidean_modulo_long \
            int8_t: euclidean_modulo_int8 \
            int16_t: euclidean_modulo_int16 \
            int32_t: euclidean_modulo_int32 \
            int64_t: euclidean_modulo_int64 \
            )(a, b)

MODERNLIB_ALWAYS_INLINE
static inline
signed char euclidean_modulo_signed_char(signed char dividend, signed char divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}

MODERNLIB_ALWAYS_INLINE
static inline
short euclidean_modulo_short(short dividend, short divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}

MODERNLIB_ALWAYS_INLINE
static inline
int euclidean_modulo_int(int dividend, int divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}
 
MODERNLIB_ALWAYS_INLINE
static inline
long euclidean_modulo_long(long dividend, long divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}

MODERNLIB_ALWAYS_INLINE
static inline
int8_t euclidean_modulo_int8(int8_t dividend, int8_t divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}

MODERNLIB_ALWAYS_INLINE
static inline
int16_t euclidean_modulo_int16(int16_t dividend, int16_t divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}

MODERNLIB_ALWAYS_INLINE
static inline
int32_t euclidean_modulo_int32(int32_t dividend, int32_t divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}
 
MODERNLIB_ALWAYS_INLINE
static inline
int64_t euclidean_modulo_int64(int64_t dividend, int64_t divisor)
{
     return ((dividend % divisor) + divisor) % divisor;
}

#endif /* ifndef MODERNLIB_ARITHMETIC_H_ */

