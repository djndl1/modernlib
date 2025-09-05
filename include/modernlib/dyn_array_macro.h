#ifndef DYN_ARRAY_MACRO_H_
#define DYN_ARRAY_MACRO_H_

#include "modernlib/basis.h"

#undef dyn_array_result_type_name
#define dyn_array_result_type_name CONCAT(dyn_array_type_name, _result)
#undef dyn_array_func
#define dyn_array_func(funcname) CONCAT(dyn_array_type_name, _ ## funcname)
#undef dyn_array_get_result_type_name
#define dyn_array_get_result_type_name CONCAT(dyn_array_type_name, _get_result)

#define dyn_array_enumerator_typename CONCAT(dyn_array_type_name, _ ## enumerator)

typedef struct find_array_index_result {
    bool found;
    size_t index;
} find_array_index_result;

#endif // DYN_ARRAY_MACRO_H_
