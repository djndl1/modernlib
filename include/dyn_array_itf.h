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

static inline size_t dyn_array_func(capacity)(const dyn_array_type_name self)
{
    return self._data.length / sizeof(dyn_array_element_type);
}

static inline size_t dyn_array_func(size)(const dyn_array_type_name self)
{
    return self._len;
}

typedef struct dyn_array_get_result_type_name {
    int error;
    dyn_array_element_type element;
} dyn_array_get_result_type_name;

dyn_array_get_result_type_name dyn_array_func(get)(const dyn_array_type_name self, size_t idx);

error_t dyn_array_func(set)(const dyn_array_type_name self, size_t idx, dyn_array_element_type value);

void dyn_array_func(destroy)(dyn_array_type_name self);

static inline dyn_array_element_type *dyn_array_func(release)(dyn_array_type_name *self)
{
    if (self == nullptr) return nullptr;

    dyn_array_element_type *pointer = self->_data.data;
    self->_data.data = nullptr;
    self->_len = 0;

    return pointer;
}

static inline dyn_array_element_type *dyn_array_func(get_data)(dyn_array_type_name self)
{
    return self._data.data;
}

#undef dyn_array_element_type
#undef dyn_array_type_name
