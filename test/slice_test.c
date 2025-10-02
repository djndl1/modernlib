#include "modernlib/basis.h"
#include "modernlib/foreach.h"
#include "modernlib/dyn_cstr.h"
#include "modernlib/data_buffer.h"

#define slice_element_type int
#include "modernlib/slice_itf.h"

#define slice_element_type char
#include "modernlib/slice_itf.h"

#define slice_element_type uint8_t
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

UTEST(SLICE, from_dyn_string)
{
		{
				dyn_cstr s;
				scoped(s = dyn_cstr_from_nts_stdalloc("ABCDEFG").str, dyn_cstr_destroy(&s)) {
						auto slice = make_slice(char, dyn_cstr_get_data_at(s, 2), 5);
						size_t count = 0;
						foreach_iter(slice_typename(char), slice, it) {
								count++;
						}
						EXPECT_STREQ(slice.start, "CDEFG");
						EXPECT_EQ(count, 5);
				}
		}
}

UTEST(SLICE, from_buffer) 
{
		{
				data_buffer buf;
				scoped(buf = std_allocate_buffer(10).buffer, data_buffer_destroy(&buf)) {
						size_t i = 0;
						foreach_iter(data_buffer, buf, it) {
								icurrent(it) = i;
								i++;
						}
						auto slice = make_slice(uint8_t, &byte_buffer_at(buf, 5), 5);

						i = 5;
						foreach_iter(slice_typename(uint8_t), slice, it) {
								EXPECT_EQ(icurrent(it), i++);
						}
				}
		}
}


UTEST_MAIN()
