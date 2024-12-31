#if !defined(dyn_string_type_name)
#error "string type name not defined!"
#endif
#if !defined(dyn_string_character_type)
#error "string character type name not defined!"
#endif

#if !defined (dyn_string_internal_array_type)
#error "internal array type used by string is not defined"
#endif

#if !defined (dyn_string_internal_array_result_type)
#error "internal array result type used by string is not defined"
#endif

#if !defined (dyn_string_internal_array_func)
#error "internal array type function composed used by string is not defined"
#endif

#include "modernlib/allocator.h"
#include "modernlib/internal/compilers.h"
#include "modernlib/dyn_str_macro.h"

typedef struct dyn_string_type_name {
    dyn_string_internal_array_type _char_array;
} dyn_string_type_name;

typedef struct dyn_string_result_type_name {
    int error;
    dyn_string_type_name str;
} dyn_string_result_type_name;

MODERNLIB_ALWAYS_INLINE
static inline dyn_string_character_type *dyn_string_func(nts)(const dyn_string_type_name self)
{
    return dyn_string_internal_array_func(get_data)(self._char_array);
}

MODERNLIB_ALWAYS_INLINE
static inline dyn_string_character_type dyn_string_func(at)(const dyn_string_type_name self, size_t idx)
{
    return dyn_string_func(nts)(self)[idx];
}

MODERNLIB_PUBLIC
dyn_string_result_type_name dyn_string_func(from)(const dyn_string_type_name str, const mem_allocator *allocator);

MODERNLIB_ALWAYS_INLINE
dyn_string_result_type_name dyn_string_func(duplicate)(const dyn_string_type_name str)
{
    return dyn_string_func(from)(str, str._char_array._data.allocator);
}

/**
 * create a string by copying string content from a memory buffer
 *
 * A new string is created by copying the character string from
 * the data buffer. If the string is already null-terminated, no additional
 * memory is allocated. Otherwise, an additional slot is allocated for
 * the terminating NUL.
 *
 * @param buf the source buffer
 * @param allocator memory allocator used to create a new string
 *
 * @return a new string created from the buffer's content
 * */
MODERNLIB_PUBLIC
dyn_string_result_type_name dyn_string_func(from_buffer)(const data_buffer buf, const mem_allocator *allocator);

MODERNLIB_ALWAYS_INLINE
static inline dyn_string_result_type_name dyn_string_func(from_stdalloc)(const dyn_string_type_name str)
{
    return dyn_string_func(from)(str, std_allocator);
}

MODERNLIB_PUBLIC
dyn_string_result_type_name dyn_string_func(from_nts)(const dyn_string_character_type *lit, const mem_allocator *allocator);

MODERNLIB_ALWAYS_INLINE
static inline dyn_string_result_type_name dyn_string_func(nts_stdalloc)(const dyn_string_character_type *lit)
{
    return dyn_string_func(from_nts)(lit, std_allocator);
}

MODERNLIB_ALWAYS_INLINE
static inline size_t dyn_string_func(len)(const dyn_string_type_name self)
{
    size_t arr_len = dyn_string_internal_array_func(size)(self._char_array);
    return arr_len > 0 ? arr_len - 1 : 0;
}

MODERNLIB_ALWAYS_INLINE
static inline size_t dyn_string_func(capacity)(const dyn_string_type_name self)
{
    return dyn_string_internal_array_func(capacity)(self._char_array);
}

MODERNLIB_PUBLIC
int dyn_string_func(compare)(const dyn_string_type_name self, const dyn_string_type_name other);

MODERNLIB_ALWAYS_INLINE
static bool dyn_string_func(equal)(const dyn_string_type_name self, const dyn_string_type_name other)
{
    return dyn_string_func(compare(self, other)) == 0;
}

MODERNLIB_ALWAYS_INLINE
static inline dyn_string_character_type *dyn_string_func(release)(dyn_string_type_name *self)
{
    return dyn_string_internal_array_func(release)(&(self->_char_array));
}

MODERNLIB_PUBLIC
void dyn_string_func(destroy)(dyn_string_type_name *self);
