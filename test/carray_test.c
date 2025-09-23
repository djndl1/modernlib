#include "modernlib/basis.h"
#include "modernlib/carray_macro.h"
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

UTEST(CARRAY, FOREACH_ITER)
{
		auto a = make_array(carray_int, 4);
		a.data[0] = 1;
		a.data[1] = 1;
		a.data[2] = 3;
		a.data[3] = 3;

    int sum = 0;
		size_t counter = 0;
    foreach_iter(carray_int, a, it) {
        sum += icurrent(it);
				EXPECT_EQ(icurrent(it), a.data[counter]);

				counter++;
    }

    EXPECT_EQ(4, counter);
    EXPECT_EQ(8, sum);
}

UTEST(CARRAY, FOREACH_ITER_REV)
{
		auto a = make_array(carray_int, 4);
		a.data[0] = 1;
		a.data[1] = 2;
		a.data[2] = 3;
		a.data[3] = 4;

		auto b = make_array(carray_int, 4);
		int counter = 0;
    foreach_iter_rev(carray_int, a, it) {
				b.data[counter] = icurrent(it);

				EXPECT_EQ(b.data[counter], a.data[a.size - 1 - counter]);

				counter++;
    }
		EXPECT_EQ(4, counter);
}

UTEST(CARRAY, FOREACH_BEGIN_END)
{
		auto a = make_array(carray_int, 4);
		a.data[0] = 1;
		a.data[1] = 1;
		a.data[2] = 3;
		a.data[3] = 3;
		int sum = 0;
		foreach_begin_end(carray_int, iterator_begin(carray_int)(&a), iterator_end(carray_int)(&a), it) {
        sum += icurrent(it);
		}
    EXPECT_EQ(8, sum);
}


UTEST(CARRAY, GENERIC_FOREACH)
{
		auto a = make_array(carray_int, 4);
		a.data[0] = 1;
		a.data[1] = 1;
		a.data[2] = 3;
		a.data[3] = 3;

		int sum = 0;
		size_t counter = 0;
		foreach_next(carray_int, iterator_begin(carray_int)(&a), iterator_end(carray_int)(&a), it, next) {
        sum += icurrent(it);
				EXPECT_EQ(icurrent(it), a.data[counter]);

				counter++;
		}
    EXPECT_EQ(8, sum);

		auto b = make_array(carray_int, 4);
		counter = 0;
		foreach_next(carray_int, iterator_rbegin(carray_int)(&a), iterator_rend(carray_int)(&a), it, rev_next) {
				b.data[counter] = icurrent(it);

				EXPECT_EQ(b.data[counter], a.data[a.size - 1 - counter]);

				counter++;
    }
}


UTEST(CARRAY, FOREACH_ARRAY)
{
		int carr[] = { 1, 2, 3, 4, 5 };
    size_t sum = 0;
		size_t counter = 0;
    foreach_array(carr, it) {
				sum += acurrent(it);
				EXPECT_EQ(acurrent(it), carr[counter++]);
    }
    EXPECT_EQ(15, sum);
    EXPECT_EQ(5, counter);

		int rarr[] = { 5, 4, 3, 2, 1 };
    sum = 0;
		counter = 0;
    foreach_array_rev(rarr, it) {
				sum += acurrent(it);
				EXPECT_EQ(acurrent(it), carr[counter++]);
    }
    EXPECT_EQ(15, sum);
    EXPECT_EQ(5, counter);
}

UTEST_MAIN();
