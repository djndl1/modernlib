#include <wchar.h>
#include "modernlib/basis.h"
#include "modernlib/utfconverter.h"

#include"utest.h"

UTEST(UTFTest, NormalUTF8ToUTF16) {
    const wchar_t utf16_str[] = L"中文ABCD";
    const char *utf8= u8"中文ABCD";

    const wchar_t *utf16_result = utf8_to_utf16(utf8, strlen(utf8) + 1);

    ASSERT_STREQ((const char*)utf16_str, (const char*)utf16_result);

    size_t expected_length = wcslen(utf16_str);
    size_t actual_length = wcslen(utf16_result);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, TruncatedUTF8ToUTF16) {
    const wchar_t utf16_str[] = L"中文";
    const char *utf8= u8"中文ABCD";

    const wchar_t *utf16_result = utf8_to_utf16(utf8, strlen(utf8) - 4);

    ASSERT_STREQ((const char*)utf16_str, (const char*)utf16_result);

    size_t expected_length = wcslen(utf16_str);
    size_t actual_length = wcslen(utf16_result);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, EmptyUTF8ToUTF16) {
    const wchar_t utf16_str[] = L"";
    const char *utf8= u8"";

    const wchar_t *utf16_result = utf8_to_utf16(utf8, 1);
    ASSERT_STREQ((const char*)utf16_str, (const char*)utf16_result);

    size_t expected_length = wcslen(utf16_str);
    size_t actual_length = wcslen(utf16_result);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, NullUTF8ToUTF16) {
    const wchar_t *utf16_result = utf8_to_utf16(nullptr, 1);
    ASSERT_EQ(utf16_result, nullptr);
}

UTEST(UTFTest, NormalUTF16ToUTF8) {
    const wchar_t utf16_str[] = L"中文ABCD";

    const char *utf8_expected = u8"中文ABCD";

    const char *utf8_str = utf16_to_utf8(utf16_str, strlen((const char*)utf16_str) + 2);

    ASSERT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST(UTFTest, EmptyUTF16ToUTF8) {
    const wchar_t utf16_str[] = L"";

    const char *utf8_expected = u8"";

    const char *utf8_str = utf16_to_utf8(utf16_str, strlen((const char*)utf16_str) + 2);

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
    const wchar_t utf16_str[] = L"中文ABCD";

    const char *utf8_expected = u8"中文AB";

    const char *utf8_str = utf16_to_utf8(utf16_str, strlen((const char*)utf16_str) + 2 - 4);

    ASSERT_STREQ(utf8_expected, utf8_str);

    size_t expected_length = strlen(utf8_expected);
    size_t actual_length = strlen(utf8_str);

    ASSERT_EQ(expected_length, actual_length);
}

UTEST_MAIN()
