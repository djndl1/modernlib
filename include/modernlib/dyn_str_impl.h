#include "modernlib/allocator.h"

#include "modernlib/dyn_str_macro.h"

#include <string.h>
#include <wchar.h>
#include <errno.h>

static dyn_string_result_type_name _create_dyn_str_from_data(const void *data,
                                                             size_t count,
                                                             const mem_allocator *allocator)
{
    // one more slot for '\0'
    dyn_string_internal_array_result_type arr_result = dyn_string_internal_array_func(from_data)(data, count + 1, allocator);
    if (arr_result.error) {
        return (dyn_string_result_type_name){ .error = arr_result.error };
    }

    dyn_string_internal_array_type arr = arr_result.array;
    error_t err = dyn_string_internal_array_func(set)(arr, count, 0);
    if (err.error) {
        dyn_string_internal_array_func(destroy)(&arr);
        return (dyn_string_result_type_name){ .error = err.error };
    }

    return (dyn_string_result_type_name){
        .str = (dyn_string_type_name){ ._char_array = arr }
    };
}

dyn_string_result_type_name dyn_string_func(from_buffer)(const data_buffer buf,
                                                         const mem_allocator *allocator)
{
    if (buf.data == nullptr || buf.length == 0) {
        return (dyn_string_result_type_name){
            .error = EINVAL,
        };
    }
    size_t l = buf.length / sizeof(dyn_string_character_type);

    return _create_dyn_str_from_data(buf.data, l, allocator);
}

static dyn_string_result_type_name _create_dyn_str_from_nts(const dyn_string_character_type *nts,
                                                            const mem_allocator *allocator)
{
     size_t l = nts_len(nts);
     return  _create_dyn_str_from_data(nts, l, allocator);
}

dyn_string_result_type_name dyn_string_func(from)(const dyn_string_type_name str,
                                                  const mem_allocator *allocator)
{
     return _create_dyn_str_from_data(
         dyn_string_func(nts)(str),
         dyn_string_func(len)(str),
         allocator);
}

dyn_string_result_type_name dyn_string_func(from_nts)(const dyn_string_character_type *nbts, const mem_allocator *allocator)
{
    return _create_dyn_str_from_nts(nbts, allocator);
}


int dyn_string_func(compare)(const dyn_string_type_name self, const dyn_string_type_name other)
{
    return ntscmp(
        dyn_string_func(nts)(self),
        dyn_string_func(nts)(other)
    );
}

void dyn_string_func(destroy)(dyn_string_type_name *self)
{
    dyn_string_internal_array_func(destroy)(&self->_char_array);
}
