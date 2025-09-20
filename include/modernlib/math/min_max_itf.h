#if !defined(min_max_typename)
#error "min max: type name not defined!"
#endif

#include "modernlib/basis.h"


MODERNLIB_ALWAYS_INLINE
static inline
min_max_typename
#ifdef __cplusplus
max
#else
CONCAT(max_, min_max_typename)
#endif
(min_max_typename l, min_max_typename r)
{
    return l > r ? l : r;
}

MODERNLIB_ALWAYS_INLINE
static inline
min_max_typename
#ifdef __cplusplus
min
#else
CONCAT(min_, min_max_typename)
#endif
(min_max_typename l, min_max_typename r)
{
    return l < r ? l : r;
}

#define minmax_return_type CONCAT(min_max_typename, _minmax_return)

#define pair_typename minmax_return_type
#define pair_left_type min_max_typename
#define pair_right_type min_max_typename
#include "modernlib/pair_itf.h"
#undef pair_typename
#undef pair_left_type
#undef pair_right_type

#include "modernlib/pair_macro.h"


MODERNLIB_ALWAYS_INLINE
static inline
minmax_return_type
#ifdef __cplusplus
minmax
#else
CONCAT(minmax_, min_max_typename)
#endif
(min_max_typename l, min_max_typename r)
{
    min_max_typename max_member, min_member;
    if (l > r) {
        max_member = l;
        min_member = r;
    } else {
        max_member = r;
        min_member = l;
    }
    return make_pair(minmax_return_type, min_member, max_member);
}

#undef max_funcname
#undef max_typename
#undef minmax_return_type
