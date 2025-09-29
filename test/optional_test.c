#include "modernlib/basis.h"
#include "modernlib/optional.h"

#include "modernlib/dyn_cstr.h"

#ifdef __STDC_VERSION__

#define nullptr NULL
#endif
#include "utest.h"

#define optional_element_type bool
#define optional_type_name optional_bool
#include "modernlib/optional_itf.h"
#undef optional_type_name
#undef optional_element_type

#define optional_element_type int
#define optional_type_name optional_int
#include "modernlib/optional_itf.h"
#undef optional_type_name
#undef optional_element_type

#define optional_element_type dyn_cstr
#define optional_type_name optional_cstr
#include "modernlib/optional_itf.h"
#undef optional_type_name
#undef optional_element_type

#define optional_element_type size_t
#define optional_type_name optional_size
#include "modernlib/optional_itf.h"

UTEST(OPTIONAL, SOME)
{
		auto opt = optional_some(optional_bool, true);
		EXPECT_TRUE(optional_present(opt));

		EXPECT_TRUE(optional_or_else(opt, true));
		EXPECT_TRUE(optional_or_else(opt, false));

		opt = optional_some(optional_bool, false);
		EXPECT_TRUE(optional_present(opt));

		EXPECT_FALSE(optional_or_else(opt, true));
		EXPECT_FALSE(optional_or_else(opt, false));
}

UTEST(OPTIONAL, NONE)
{
		auto opt = optional_none(optional_bool);
		EXPECT_TRUE(!optional_present(opt));
		EXPECT_TRUE(optional_empty(opt));

		EXPECT_TRUE(optional_or_else(opt, true));
		EXPECT_FALSE(optional_or_else(opt, false));
}

UTEST(OPTIONAL, try_get) 
{
		auto opt = optional_some(optional_bool, true);
		bool value;
		bool some = optional_try_get(optional_bool, opt, &value);
		EXPECT_EQ(true, some);
		EXPECT_EQ(true, value);

		opt = optional_none(optional_bool);
		some = optional_try_get(optional_bool, opt, &value);
		EXPECT_EQ(false, some);

		some = optional_try_get(optional_bool, opt, nullptr);
		EXPECT_EQ(false, some);
}

UTEST(OPTIONAL, ifsome_ifnone)
{
		auto opt = optional_some(optional_bool, true);
		optional_ifsome(optional_bool, opt, optval) {
				EXPECT_EQ(optval.value, true);
		}
		optional_ifnone(optional_bool, opt, _) {
				ASSERT_FALSE(true);
		}
}

#if __GNUC__ >= 15  || defined(__cplusplus)
UTEST(OPTIONAL, if_declaration)
{
		auto opt = optional_some(optional_bool, true);
		optional_if(opt, value) {
				EXPECT_EQ(value, true);
		} else {
				ASSERT_FALSE(true);
		}
}
#endif
 
static bool is_even(int n) 
{
		return n % 2 == 0;
}

UTEST(OPTIONAL, filter)
{
		EXPECT_FALSE(optional_present(optional_filter(optional_int, optional_none(optional_int), is_even)));
		EXPECT_EQ(optional_or_else(optional_filter(optional_int, 
																								optional_some(optional_int, 3), 
																								is_even), 
																0), 
								0);
		EXPECT_EQ(optional_or_else(optional_filter(optional_int, 
																								optional_some(optional_int, 4), 
																								is_even), 
																0), 
								4);
}

UTEST(OPTIONAL, map)
{
		auto maybe_some_string = optional_some(optional_cstr, dyn_cstr_from_nts_stdalloc("Hello, World!").str);
		deferred(optional_inspect(optional_cstr, maybe_some_string, dyn_cstr_destroy)) {
				auto maybe_some_len = optional_map(optional_size, maybe_some_string, dyn_cstr_len);
				EXPECT_EQ(optional_or_else(maybe_some_len, 0), 13);

		}

		auto none = optional_none(optional_cstr);
		deferred(optional_inspect(optional_cstr, none, dyn_cstr_destroy)) {
				auto len_none = optional_map(optional_size, none, dyn_cstr_len);
				EXPECT_TRUE(optional_empty(len_none));
		}
}

UTEST_MAIN()
