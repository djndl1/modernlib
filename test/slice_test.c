#include "modernlib/basis.h"
#include "modernlib/foreach.h"

#define slice_element_type int
#include "modernlib/slice_itf.h"

#ifdef __STDC_VERSION__
#define nullptr NULL
#endif
#include "utest.h"

UTEST(SLICE, from_array)
{
		int array[] = {1, 2, 3, 4, 5};
		auto slice = make_slice_from(int, array);

		int sum = 0;
		foreach_iter(slice_typename(int), slice, it) {
				sum += icurrent(it);
		}
		EXPECT_EQ(sum, 15);

		auto partial_slice = make_slice(int, &array[2], 3);
		sum = 0;
		foreach_iter(slice_typename(int), partial_slice, it) {
				sum += icurrent(it);
		}
		EXPECT_EQ(sum, 12);
}


UTEST_MAIN()
