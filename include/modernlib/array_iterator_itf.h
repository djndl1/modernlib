#ifndef array_typename
    #error "array typename is not defined!"
#endif
#ifndef array_element_type
    #error "array element type is not defined!"
#endif

#include "modernlib/foreach.h"
#include "modernlib/basis.h"
#include "modernlib/carray_macro.h"

typedef struct iterator_typename(array_typename) {
		array_element_type *current;
		const array_element_type *end;
} iterator_typename(array_typename);

#undef array_iter
#define array_iter(typ, arr) (iterator_new_from(typ)(arr, arr + array_size(arr)))

MODERNLIB_ALWAYS_INLINE
static inline
iterator_typename(array_typename) iterator_new_from(array_typename)(array_element_type* begin, const array_element_type* end)
{
    iterator_typename(array_typename) iter;
    iter.current = begin;
    iter.end = end;
    return iter;
}

MODERNLIB_ALWAYS_INLINE
static inline
bool iterator_stopped(array_typename)(iterator_typename(array_typename) self)
{
    return self.current == self.end;
}

MODERNLIB_ALWAYS_INLINE
static inline
void iterator_next(array_typename)(iterator_typename(array_typename) *self)
{
    if (self == nullptr) {
        return;
    }

    self->current++;
}

