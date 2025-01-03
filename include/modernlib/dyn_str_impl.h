#include "modernlib/allocator.h"

#include "modernlib/dyn_str_macro.h"

#include <string.h>
#include <wchar.h>
#include <errno.h>

static const dyn_string_character_type empty_char_array[] = { 0 };

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
    uint8_t *bytes = data_buffer_as_byte_array(buf);
    // but there might be embedding NUL
    size_t string_len = 0;
    for (size_t i = 0; i < buf.length; i += sizeof(dyn_string_character_type)) {
        dyn_string_character_type ch;
        // memcpy for safe type punning in case the source data is not of the character type
        memcpy(&ch, &bytes[i], sizeof(dyn_string_character_type));
        if (ch == 0) {
            break;
        }
        string_len++;
    }

    return _create_dyn_str_from_data(buf.data, string_len, allocator);
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

dyn_string_result_type_name dyn_string_func(from_nts)(const dyn_string_character_type *nts,
                                                      const mem_allocator *const allocator)
{
    const dyn_string_character_type *source = (nts == nullptr) ? empty_char_array : nts;
    return _create_dyn_str_from_nts(source, allocator);
}

dyn_string_result_type_name dyn_string_func(move_from_nts)(dyn_string_character_type **nts,
                                                          const mem_allocator * const allocator)
{
    if (nts == nullptr || *nts == nullptr) {
        return (dyn_string_result_type_name){
            .error = EINVAL,
        };
    }

    dyn_string_character_type *source = *nts;
    size_t count = nts_len(source);
    dyn_string_internal_array_result_type arr_result = dyn_string_internal_array_func(move_from_data)(&source, count, allocator);
    if (arr_result.error) {
        return (dyn_string_result_type_name){ .error = arr_result.error };
    }
    *nts = source;

    dyn_string_type_name s = { ._char_array = arr_result.array };
    return (dyn_string_result_type_name){ .str = s, .error = 0 };
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

dyn_string_result_type_name dyn_string_func(concat)(const dyn_string_type_name one,
                                                    const dyn_string_type_name two,
                                                    const mem_allocator *const allocator)
{
    size_t len_one = dyn_string_func(len)(one);
    size_t len_two = dyn_string_func(len)(two);

    size_t len_concat = len_one + len_two;
    if (len_concat == 0) {
        return _create_dyn_str_from_nts(empty_char_array, allocator);
    }

    dyn_string_internal_array_result_type newarr_result = dyn_string_internal_array_func(of_capacity)(
        len_concat + 1, allocator);
    if (newarr_result.error) {
        return (dyn_string_result_type_name){ .error = newarr_result.error };
    }
    dyn_string_internal_array_type arr = newarr_result.array;
    arr._len = len_concat + 1;

    error_t err1 = dyn_string_internal_array_func(overwrite_at)(
        arr, 0, dyn_string_internal_array_func(get_data)(one._char_array), len_one);
    if (err1.error) {
        dyn_string_internal_array_func(destroy)(&arr);
        return (dyn_string_result_type_name){ .error = err1.error };
    }

    error_t err2 = dyn_string_internal_array_func(overwrite_at)(
        arr, len_one, dyn_string_internal_array_func(get_data)(two._char_array), len_two);
    if (err2.error) {
        dyn_string_internal_array_func(destroy)(&arr);
        return (dyn_string_result_type_name){ .error = err2.error };
    }
    dyn_string_internal_array_func(set)(arr, len_concat, 0);

    return (dyn_string_result_type_name){
        .error = 0,
        .str = { ._char_array = arr },
    };
}
