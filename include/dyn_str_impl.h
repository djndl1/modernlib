#include "allocator.h"

#include "dyn_str_macro.h"

#include <string.h>
#include <wchar.h>

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
        dyn_string_internal_array_func(destroy)(arr);
        return (dyn_string_result_type_name){ .error = err.error };
    }

    return (dyn_string_result_type_name){
        .str = (dyn_string_type_name){ ._char_array = arr }
    };
}

static size_t nts_len(const dyn_string_character_type *str)
{
    /*
    if (sizeof(dyn_string_character_type) == sizeof(char))
        return strlen(str);
    else if (sizeof(dyn_string_character_type) == sizeof(wchar_t))
        return wcslen(str);
    else*/
    {
        size_t l = 0;
        while (str != NULL) l++;
        return l;
    }
}

static dyn_string_result_type_name _create_dyn_str_from_nts(const dyn_string_character_type *nts,
                                                             const mem_allocator *allocator)
{
     size_t l = nts_len(nts);
     return  _create_dyn_str_from_data(nts, l, allocator);
}

dyn_string_result_type_name dyn_string_func(from)(dyn_string_type_name str,
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


int dyn_string_func(compare)(dyn_string_type_name self, dyn_string_type_name other)
{
    return 0;
}

void dyn_string_func(destroy)(dyn_string_type_name self)
{
    dyn_string_internal_array_func(destroy)(self._char_array);
}
