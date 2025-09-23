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
		array_element_type *value;
} iterator_typename(array_typename);


MODERNLIB_ALWAYS_INLINE
static inline
bool iterator_stopped(array_typename)(iterator_typename(array_typename) l, iterator_typename(array_typename) end)
{
    return l.value == end.value;
}

MODERNLIB_ALWAYS_INLINE
static inline
void iterator_next(array_typename)(iterator_typename(array_typename) *self)
{
    if (self == nullptr) {
        return;
    }

    self->value++;
}

MODERNLIB_ALWAYS_INLINE
static inline
void iterator_rev_next(array_typename)(iterator_typename(array_typename) *self)
{
    if (self == nullptr) {
        return;
    }

    self->value--;
}
