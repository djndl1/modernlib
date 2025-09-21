#ifndef carray_element_type
    #error "carray element type is not defined!"
#endif

#ifndef carray_size
    #error "carray size is not defined!"
#endif

#ifndef carray_typename
    #error "carray typename is not defined!"
#endif

#include "modernlib/internal/compilers.h"
#include "modernlib/carray_macro.h"
#include "modernlib/foreach.h"
#include <stddef.h>

#define carray_real_type carray_type(carray_typename, carray_size)

typedef struct carray_real_type {
		carray_element_type data[carray_size];
		size_t size;
} carray_real_type;

#define array_typename carray_typename
#define array_element_type carray_element_type
#include "modernlib/array_iterator_itf.h"
#undef array_typename
#undef array_element_type

MODERNLIB_ALWAYS_INLINE
static inline
iterator_typename(carray_typename) iterator_new(carray_typename)(carray_real_type self)
{
    iterator_typename(carray_typename) iter;
    iter.current = self.data;
    iter.end = self.data + self.size;
    return iter;
}

#undef carray_real_type
#undef carray_element_type
#undef carray_typename
