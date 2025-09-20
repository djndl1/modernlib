#include "modernlib/internal/compilers.h"
#if !defined(pair_typename)
#error "pair type name not defined!"
#endif

#if !defined(pair_left_type)
#error "pair left type not defined!"
#endif

#if !defined(pair_right_type)
#error "pair right type not defined!"
#endif

typedef struct pair_typename {
    pair_left_type left;
    pair_right_type right;
} pair_typename;

MODERNLIB_ALWAYS_INLINE
static inline
pair_typename CONCAT(make_, pair_typename)(pair_left_type left, pair_right_type right)
{
    pair_typename pair;
    pair.left = left;
    pair.right = right;

    return pair;
}

#undef pair_typename
#undef pair_left_type
#undef pair_right_type

