#ifndef DYN_CWSTR_H_
#define DYN_CWSTR_H_

#include "modernlib/dyn_wchar_array.h"

#undef dyn_string_internal_array_type
#define dyn_string_internal_array_type dyn_wchar_array

#undef dyn_string_internal_array_result_type
#define dyn_string_internal_array_result_type dyn_wchar_array_result

#undef dyn_string_internal_array_func
#define dyn_string_internal_array_func(funcname) CONCAT(dyn_wchar_array, _ ## funcname)


#define dyn_string_type_name dyn_cwstr
#define dyn_string_character_type wchar_t
#include "dyn_str_itf.h"
#undef dyn_string_type_name
#undef dyn_string_character_type

#endif // DYN_CWSTR_H_
