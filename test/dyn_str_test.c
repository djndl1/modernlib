#include "modernlib/dyn_cstr.h"
#include "modernlib/basis.h"

#include "utest.h"


UTEST(DYN_CSTR, from_nts)
{
    for (size_t i = 0; i < 500000000; i++) {
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

UTEST_MAIN();
