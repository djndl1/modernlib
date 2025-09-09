#include <uchar.h>
#include <wchar.h>
#include "modernlib/basis.h"
#include "modernlib/u16char.h"
#include "modernlib/utfconverter.h"

#include"utest.h"

UTEST(UTFETest, BasicAssumptions) {
    // not guaranteed by the standard, I assume so
    ASSERT_EQ(4, sizeof(char32_t));
    ASSERT_EQ(2, sizeof(char16_t));
}

UTEST(UTFTest, NormalUTF8ToUTF16) {
    const char16_t utf16_str[] = u"中文ABCD";
    const char *utf8= u8"中文ABCD";

    const char16_t *utf16_result = utf8_to_utf16(utf8, strlen(utf8));

    ASSERT_EQ(u16cmp(utf16_str, utf16_result), 0);

    size_t expected_length = u16len(utf16_str);
    size_t actual_length = u16len(utf16_result);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, TruncatedUTF8ToUTF16) {
    const char16_t utf16_str[] = u"中文";
    const char *utf8= u8"中文ABCD";

    const char16_t *utf16_result = utf8_to_utf16(utf8, strlen(utf8) - 4);

    ASSERT_EQ(u16cmp(utf16_str, utf16_result), 0);

    size_t expected_length = u16len(utf16_str);
    size_t actual_length = u16len(utf16_result);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, EmptyUTF8ToUTF16) {
    const char16_t utf16_str[] = u"";
    const char *utf8= u8"";

    const char16_t *utf16_result = utf8_to_utf16(utf8, 0);
    ASSERT_EQ(u16cmp(utf16_str, utf16_result), 0);

    ASSERT_EQ(utf16_result[0], 0);

}

UTEST(UTFTest, NullUTF8ToUTF16) {
    const char16_t *utf16_result = utf8_to_utf16(nullptr, 0);
    ASSERT_EQ(utf16_result, nullptr);
}

UTEST(UTFTest, NormalUTF16ToUTF8) {
    const char16_t utf16_str[] = u"中文ABCD";

    const char *utf8_expected = u8"中文ABCD";

    const char *utf8_str = utf16_to_utf8(utf16_str, 6);

    ASSERT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, EmptyUTF16ToUTF8) {
    const char16_t utf16_str[] = u"";

    const char *utf8_expected = u8"";

    const char *utf8_str = utf16_to_utf8(utf16_str, 0);

    ASSERT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, NullUTF16ToUTF8) {
    const char *utf8_str = utf16_to_utf8(nullptr, 0);

    ASSERT_EQ(utf8_str, nullptr);
}

UTEST(UTFTest, TruncatedUTF16ToUTF8) {
    const char16_t utf16_str[] = u"中文ABCD";

    const char *utf8_expected = u8"中文AB";

    const char *utf8_str = utf16_to_utf8(utf16_str, 4);

    ASSERT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST_MAIN()
