#include "modernlib/basis.h"
#include "modernlib/foreach.h"
#define carray_typename carray_int
#define carray_element_type int
#define carray_size 4
#include "modernlib/carray_itf.h"
#undef carray_typename
#undef carray_element_type

#ifdef __STDC_VERSION__
#undef nullptr
#define nullptr NULL
#endif
#include "utest.h"

UTEST(CARRAY, FOREACH)
{
		auto a = make_array(carray_int, 4);
		a.data[0] = 1;
		a.data[1] = 1;
		a.data[2] = 3;
		a.data[3] = 3;

    int sum = 0;
    foreach_iter(carray_int, a, it) {
        sum += icurrent(it);
    }

    EXPECT_EQ(8, sum);
}

UTEST(CARRAY, WHILE_LOOP)
{
		int arr[] = { 1, 2, 3, 4, 5 };
		auto it = array_iter(carray_int, arr);

    int sum = 0;
		while (!iterator_stopped(carray_int)(it)) {
				sum += icurrent(it);
				iterator_next(carray_int)(&it);
		}
    EXPECT_EQ(15, sum);

}

UTEST_MAIN();
