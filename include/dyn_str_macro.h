#ifndef DYN_STR_MACRO_H_
#define DYN_STR_MACRO_H_

#undef dyn_string_result_type_name
#define dyn_string_result_type_name CONCAT(dyn_string_type_name, _result)
#undef dyn_string_func
#define dyn_string_func(funcname) CONCAT(dyn_string_type_name, _ ## funcname)
#undef dyn_array_get_result_type_name
#define dyn_string_get_result_type_name CONCAT(dyn_string_character_type, _get_result)

#endif // DYN_STR_MACRO_H_
