#ifndef DYN_ARRAY_MACRO_H_
#define DYN_ARRAY_MACRO_H_

#define dyn_array_size(arr) (arr._len)
#define dyn_array_capacity(arr) (arr._data.length)

#undef dyn_array_result_type_name
#define dyn_array_result_type_name CONCAT(dyn_array_type_name, _result)
#undef dyn_array_func
#define dyn_array_func(funcname) CONCAT(dyn_array_type_name, _ ## funcname)
#undef dyn_array_get_result_type_name
#define dyn_array_get_result_type_name CONCAT(dyn_array_type_name, _get_result)




#endif // DYN_ARRAY_MACRO_H_
