#ifndef DYN_CSTR_H_
#define DYN_CSTR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "modernlib/dyn_char_array.h"

#undef dyn_string_internal_array_type
#define dyn_string_internal_array_type dyn_char_array

#undef dyn_string_internal_array_result_type
#define dyn_string_internal_array_result_type dyn_char_array_result

#undef dyn_string_internal_array_func
#define dyn_string_internal_array_func(funcname) CONCAT(dyn_char_array, _ ## funcname)


#define dyn_string_type_name dyn_cstr
#define dyn_string_character_type char
#include "dyn_str_itf.h"
#undef dyn_string_type_name
#undef dyn_string_character_type

#ifdef __cplusplus
}
#endif

#endif // DYN_CSTR_H_
