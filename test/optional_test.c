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

static bool generate_false()
{
		return false;
}

UTEST(OPTIONAL, SOME)
{
		auto opt = optional_some(optional_bool, true);
		EXPECT_TRUE(optional_present(opt));

		EXPECT_TRUE(optional_unwrap_or(opt, true));
		EXPECT_TRUE(optional_unwrap_or(opt, false));
		EXPECT_TRUE(optional_unwrap_or_else(opt, generate_false));

		opt = optional_some(optional_bool, false);
		EXPECT_TRUE(optional_present(opt));

		EXPECT_FALSE(optional_unwrap_or(opt, true));
		EXPECT_FALSE(optional_unwrap_or(opt, false));
}

UTEST(OPTIONAL, NONE)
{
		auto opt = optional_none(optional_bool);
		EXPECT_TRUE(!optional_present(opt));
		EXPECT_TRUE(optional_empty(opt));

		EXPECT_TRUE(optional_unwrap_or(opt, true));
		EXPECT_FALSE(optional_unwrap_or(opt, false));
		EXPECT_FALSE(optional_unwrap_or_else(opt, generate_false));
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
		EXPECT_EQ(optional_unwrap_or(optional_filter(optional_int, 
																								optional_some(optional_int, 3), 
																								is_even), 
																0), 
								0);
		EXPECT_EQ(optional_unwrap_or(optional_filter(optional_int, 
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
				EXPECT_EQ(optional_unwrap_or(maybe_some_len, 0), 13);

		}

		auto none = optional_none(optional_cstr);
		deferred(optional_inspect(optional_cstr, none, dyn_cstr_destroy)) {
				auto len_none = optional_map(optional_size, none, dyn_cstr_len);
				EXPECT_TRUE(optional_empty(len_none));
		}
}

static bool greater_than_one(int x)
{
		return x > 1;
}

static bool length_greater_than_one(const dyn_cstr str)
{
		return dyn_cstr_len(str) > 1;
}

UTEST(OPTION, is_some_and)
{
		auto x = optional_some(optional_int, 2);
		EXPECT_TRUE(optional_is_some_and(x, greater_than_one));

		x = optional_some(optional_int, 0);
		EXPECT_FALSE(optional_is_some_and(x, greater_than_one));

		x = optional_none(optional_int);
		EXPECT_FALSE(optional_is_some_and(x, greater_than_one));

		auto y = optional_some(optional_cstr, dyn_cstr_from_nts_stdalloc("ownership").str);
		deferred(optional_inspect(optional_cstr, y, dyn_cstr_destroy)) {
				EXPECT_TRUE(optional_is_some_and(y, length_greater_than_one));
		}
}

UTEST(OPTION, is_none_or)
{
		auto x = optional_some(optional_int, 2);
		EXPECT_TRUE(optional_is_none_or(x, greater_than_one));

		x = optional_some(optional_int, 0);
		EXPECT_FALSE(optional_is_none_or(x, greater_than_one));

		x = optional_none(optional_int);
		EXPECT_TRUE(optional_is_none_or(x, greater_than_one));

		auto y = optional_some(optional_cstr, dyn_cstr_from_nts_stdalloc("ownership").str);
		deferred(optional_inspect(optional_cstr, y, dyn_cstr_destroy)) {
				EXPECT_TRUE(optional_is_none_or(y, length_greater_than_one));
		}
}

UTEST_MAIN()
