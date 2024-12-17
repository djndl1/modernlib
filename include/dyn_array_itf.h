#if !defined(dyn_array_element_type) || !defined(dyn_array_type_name)
#error "dynamic array type or dynamic array name not defined!"
#endif

#include "data_buffer.h"
#include "allocator.h"
#include "basis.h"

#include "dyn_array_macro.h"

typedef struct dyn_array_type_name {
    data_buffer _data;
    size_t _len;
} dyn_array_type_name;


typedef struct dyn_array_result_type_name {
    int error;
    dyn_array_type_name array;
} dyn_array_result_type_name;

dyn_array_result_type_name dyn_array_func(of_capacity)(size_t capacity,
                                                       const mem_allocator *allocator);

dyn_array_result_type_name dyn_array_func(from_data)(const void *data,
                                                     size_t count,
                                                     const mem_allocator *allocator);

dyn_array_result_type_name dyn_array_func(from_buffer)(const data_buffer data,
                                                       const mem_allocator *allocator);

dyn_array_result_type_name dyn_array_func(from_array)(const dyn_array_type_name other,
                                                      const mem_allocator *allocator);

typedef struct dyn_array_get_result_type_name {
    int error;
    dyn_array_element_type element;
} dyn_array_get_result_type_name;

dyn_array_get_result_type_name dyn_array_func(get)(const dyn_array_type_name self, size_t idx);

error_t dyn_array_func(set)(const dyn_array_type_name self, size_t idx, dyn_array_element_type value);

void dyn_array_func(destroy)(dyn_array_type_name self);

#undef dyn_array_element_type
#undef dyn_array_type_name
