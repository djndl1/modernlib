#include "modernlib/basis.h"
#include "modernlib/optional.h"

#ifdef __STDC_VERSION__

#define nullptr NULL
#endif
#include "utest.h"

#define optional_element_type bool
#define optional_type_name optional_bool
#include "modernlib/optional_itf.h"
#undef optional_type_name
#undef optional_element_type

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


UTEST_MAIN()
