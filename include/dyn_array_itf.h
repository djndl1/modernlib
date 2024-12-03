#if !defined(dyn_array_element_type) || !defined(dyn_array_type_name)
#error "dynamic array type or dynamic array name not defined!"
#endif

#include "data_buffer.h"
#include "allocator.h"
#include "util.h"

#include "dyn_array_macro.h"

typedef struct dyn_array_type_name {
    data_buffer _data;
    size_t _len;
} dyn_array_type_name;


typedef struct dyn_array_result_type_name {
    int error;
    dyn_array_type_name array;
} dyn_array_result_type_name;

dyn_array_result_type_name dyn_array_func(from_data)(const void *data,
                                                     size_t count,
                                                     const mem_allocator *allocator);

#undef dyn_array_element_type
#undef dyn_array_type_name
