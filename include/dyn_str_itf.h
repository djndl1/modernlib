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

#include "allocator.h"
#include "dyn_str_macro.h"

typedef struct dyn_string_type_name {
    dyn_string_internal_array_type _char_array;
} dyn_string_type_name;

typedef struct dyn_string_result_type_name {
    int error;
    dyn_string_type_name str;
} dyn_string_result_type_name;

static inline dyn_string_character_type *dyn_string_func(nts)(const dyn_string_type_name self)
{
    return ((dyn_string_character_type*)(self._char_array._data.data));
}

static inline dyn_string_character_type dyn_string_func(at)(const dyn_string_type_name self, size_t idx)
{
    return dyn_string_func(nts)(self)[idx];
}


dyn_string_result_type_name dyn_string_func(from)(dyn_string_type_name str, const mem_allocator *allocator);

static inline dyn_string_result_type_name dyn_string_func(from_stdalloc)(const dyn_string_type_name str)
{
    return dyn_string_func(from)(str, std_allocator);
}

dyn_string_result_type_name dyn_string_func(from_nts)(const dyn_string_character_type *lit, const mem_allocator *allocator);

static inline dyn_string_result_type_name dyn_string_func(nts_stdalloc)(const dyn_string_character_type *lit)
{
    return dyn_string_func(from_nts)(lit, std_allocator);
}

static inline size_t dyn_string_func(len)(dyn_string_type_name self)
{
    return self._char_array._len > 0 ? self._char_array._len - 1 : 0;
}

static inline size_t dyn_string_func(capacity)(dyn_string_type_name self)
{
    return (self._char_array._data.length);
}

int dyn_string_func(compare)(dyn_string_type_name self, dyn_string_type_name other);

static bool dyn_string_func(equal)(dyn_string_type_name self, dyn_string_type_name other)
{
    return dyn_string_func(compare(self, other)) == 0;
}

void dyn_string_func(destroy)(dyn_string_type_name self);
