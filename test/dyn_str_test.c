#include "modernlib/dyn_cstr.h"
#include "modernlib/dyn_cwstr.h"
#include "modernlib/basis.h"

#include "utest.h"


UTEST(DYN_CSTR, from_nts)
{
    for (size_t i = 0; i < 10000000; i++) {
        dyn_cstr s;
        scoped(s = dyn_cstr_from_nts("ABCDEFGHIJKLM", std_allocator).str,
               dyn_cstr_destroy(&s)) {
            EXPECT_STREQ(dyn_cstr_nts(s), "ABCDEFGHIJKLM");
        }

        const size_t per_count = 10000000;
        if (i % per_count == 0) {
            size_t n_count = i / per_count;
            printf("DYN_CSTR.from_nts: %zu allocations and deallocations\n",
                n_count * per_count);
            fflush(stdout);
        }
    }
}

UTEST(DYN_CSTR, at)
{
    {
        dyn_cstr s;
        scoped(s = dyn_cstr_from_nts("ABC", std_allocator).str,
               dyn_cstr_destroy(&s)) {
            EXPECT_EQ('A', dyn_cstr_at(s, 0));
            EXPECT_EQ('B', dyn_cstr_at(s, 1));
            EXPECT_EQ('C', dyn_cstr_at(s, 2));
            EXPECT_EQ('\0', dyn_cstr_at(s, 3));
        }
    }
}

UTEST(DYN_CSTR, duplicate)
{
    for (size_t i = 0; i < 10000000; i++) {
        dyn_cstr s;
        scoped(s = dyn_cstr_from_nts("ABCDEFGHIJKLM", std_allocator).str,
               dyn_cstr_destroy(&s)) {
            EXPECT_STREQ(dyn_cstr_nts(s), "ABCDEFGHIJKLM");

            dyn_cstr dup;
            scoped(dup = dyn_cstr_duplicate(s).str, dyn_cstr_destroy(&dup)) {
                EXPECT_EQ(dyn_cstr_compare(s, dup), 0);
            }
        }
    }
}

UTEST(DYN_CSTR, from_buffer)
{
    dyn_cstr s = dyn_cstr_from_nts("中文ABCDEFGHIJKLM", std_allocator).str;
    for (size_t i = 0; i < 1000000; i++) {
        EXPECT_STREQ(dyn_cstr_nts(s), "中文ABCDEFGHIJKLM");

        dyn_cstr dup = dyn_cstr_from_buffer(s._char_array._data, std_allocator).str;
        EXPECT_EQ(dyn_cstr_compare(s, dup), 0);

        dyn_cstr temp = s;
        s = dup;
        dup = temp;

        if (i % 100000 == 0) {
            printf("%zu: from_buffer string capacity: %zu\n", i, dyn_cstr_capacity(s));
        }

        dyn_cstr_destroy(&dup);
    }
}

UTEST(DYN_CWSTR, from_buffer)
{
    dyn_cwstr s = dyn_cwstr_from_nts(L"中文ABCDEFGHIJKLM", std_allocator).str;
    for (size_t i = 0; i < 1000000; i++) {
        EXPECT_EQ(wcscmp(dyn_cwstr_nts(s), L"中文ABCDEFGHIJKLM"), 0);

        dyn_cwstr dup = dyn_cwstr_from_buffer(s._char_array._data, std_allocator).str;
        EXPECT_EQ(dyn_cwstr_compare(s, dup), 0);

        dyn_cwstr temp = s;
        s = dup;
        dup = temp;

        if (i % 100000 == 0) {
            printf("%zu: from_buffer string capacity: %zu\n", i, dyn_cwstr_capacity(s));
        }

        dyn_cwstr_destroy(&dup);
    }
}

UTEST(DYN_CSTR, len)
{
    dyn_cstr s;
    scoped(s = dyn_cstr_from_nts_stdalloc("ABCDEF").str, dyn_cstr_destroy(&s)) {
        EXPECT_EQ(dyn_cstr_len(s), 6);
    }
    scoped(s = dyn_cstr_from_nts_stdalloc("").str, dyn_cstr_destroy(&s)) {
        EXPECT_EQ(dyn_cstr_len(s), 0);
    }
    scoped(s = dyn_cstr_from_nts_stdalloc(nullptr).str, dyn_cstr_destroy(&s)) {
        EXPECT_EQ(dyn_cstr_len(s), 0);
    }
}

UTEST_MAIN();
