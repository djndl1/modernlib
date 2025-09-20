#include "modernlib/numerics.h"
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>

#ifdef __STDC__
#undef nullptr
#define nullptr NULL
#endif
#include "utest.h"


UTEST(CLAMP, UINT8)
{
    auto expected = (uint8_t)6;
    auto result = clamp((uint8_t)7, (uint8_t)1, (uint8_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, UINT16)
{
    auto expected = (uint16_t)6;
    auto result = clamp((uint16_t)7, (uint16_t)1, (uint16_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, UINT32)
{
    auto expected = (uint32_t)6;
    auto result = clamp((uint32_t)7, (uint32_t)1, (uint32_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, UINT64)
{
    auto expected = (uint64_t)6;
    auto result = clamp((uint64_t)7, (uint64_t)1, (uint64_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, INT8)
{
    auto expected = (int8_t)6;
    auto result = clamp((int8_t)7, (int8_t)1, (int8_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, INT16)
{
    auto expected = (int16_t)6;
    auto result = clamp((int16_t)7, (int16_t)1, (int16_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, INT32)
{
    auto expected = (int32_t)6;
    auto result = clamp((int32_t)7, (int32_t)1, (int32_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, INT64)
{
    auto expected = (int64_t)6;
    auto result = clamp((int64_t)7, (int64_t)1, (int64_t)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, FLOAT)
{
    auto expected = (float)6;
    auto result = clamp((float)7, (float)1, (float)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, DOUBLE)
{
    auto expected = (double)6;
    auto result = clamp((double)7, (double)1, (double)6);
    EXPECT_EQ(expected, result);
}

UTEST(CLAMP, LONG_DOUBLE)
{
    auto expected = (long double)6;
    auto result = clamp((long double)7, (long double)1, (long double)6);
    EXPECT_EQ(expected, result);
}



UTEST_MAIN();
