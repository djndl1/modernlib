#ifndef slice_element_type
    #error "slice_element_type is not defined"
#endif

#include "modernlib/slice_macro.h"

#define slice_realtypename slice_typename(slice_element_type)

typedef struct slice_realtypename {
    slice_element_type *start;
    size_t count;
} slice_realtypename;

#define array_typename slice_realtypename
#define array_element_type slice_element_type
#include "modernlib/array_iterator_itf.h"

MODERNLIB_ALWAYS_INLINE
static inline
iterator_typename(slice_realtypename) iterator_begin(slice_realtypename)(slice_realtypename *self)
{
    iterator_typename(slice_realtypename) iter;
    iter.value = self->start;
    return iter;
}

MODERNLIB_ALWAYS_INLINE
static inline
iterator_typename(slice_realtypename) iterator_end(slice_realtypename)(slice_realtypename *self)
{
    iterator_typename(slice_realtypename) iter;
    iter.value = self->start + self->count;
    return iter;
}

MODERNLIB_ALWAYS_INLINE
static inline
iterator_typename(slice_realtypename) iterator_rbegin(slice_realtypename)(slice_realtypename *self)
{
    iterator_typename(slice_realtypename) iter;
    iter.value = self->start + self->count - 1;
    return iter;
}

MODERNLIB_ALWAYS_INLINE
static inline
iterator_typename(slice_realtypename) iterator_rend(slice_realtypename)(slice_realtypename *self)
{
    iterator_typename(slice_realtypename) iter;
    iter.value = self->start - 1;
    return iter;
}

#undef slice_realtypename
#undef slice_element_type
