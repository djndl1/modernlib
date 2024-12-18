#include "data_buffer.h"
#include "errors.h"
#include <errno.h>

#include "dyn_array_macro.h"
#include <string.h>

dyn_array_result_type_name dyn_array_func(of_capacity)(size_t capacity,
                                                       const mem_allocator *allocator)
{
     size_t elem_size = sizeof(dyn_array_element_type);
     buffer_alloc_result alloc_res = data_buffer_new(capacity * elem_size, allocator);
     if (alloc_res.error) {
         return (dyn_array_result_type_name) { .error = alloc_res.error };
     }
     data_buffer buf = alloc_res.buffer;
     dyn_array_type_name arr = { ._data = buf, ._len = 0 };

     return (dyn_array_result_type_name) { .error = 0, .array = arr };
}

dyn_array_result_type_name dyn_array_func(from_data)(const void *data,
                                                     size_t count,
                                                     const mem_allocator *allocator)
{
    dyn_array_result_type_name creation_result = dyn_array_func(of_capacity)(count, allocator);
    if (creation_result.error) {
        return creation_result;
    }
    dyn_array_type_name newarr = creation_result.array;

    error_t err = data_buffer_copy_from(&newarr._data, data, count * sizeof(dyn_array_element_type));
    if (err.error) {
        data_buffer_destroy(&newarr._data);
        return (dyn_array_result_type_name) { .error = err.error };
    }
    newarr._len = count;

    return (dyn_array_result_type_name) { .array = newarr };
}

dyn_array_result_type_name dyn_array_func(from_buffer)(const data_buffer data,
                                                       const mem_allocator *allocator)
{
    return dyn_array_func(from_data)(data.data, data.length, allocator);
}

dyn_array_result_type_name dyn_array_func(from_array)(const dyn_array_type_name other,
                                                      const mem_allocator *allocator)
{
    return dyn_array_func(from_buffer)(other._data, allocator);
}

dyn_array_get_result_type_name dyn_array_func(get)(const dyn_array_type_name self, size_t idx)
{
    if (idx >= dyn_array_func(size)(self)) {
        return (dyn_array_get_result_type_name){ .error = ERANGE };
    }


    return (dyn_array_get_result_type_name){
        .element = data_buffer_element_at(self._data, dyn_array_element_type, idx),
    };
}

error_t dyn_array_func(set)(const dyn_array_type_name self, size_t idx, dyn_array_element_type value)
{
    if (idx >= dyn_array_func(size)(self)) {
        return ERR_FROM_CODE(ERANGE);
    }

    data_buffer_element_at(self._data, dyn_array_element_type, idx) = value;
    return E_OK;
}

void dyn_array_func(destroy)(dyn_array_type_name *self)
{
    data_buffer_destroy(&self->_data);
}

error_t dyn_array_func(append)(dyn_array_type_name *self, dyn_array_element_type item)
{
    if (self == nullptr) return ERR_FROM_CODE(EINVAL);

    size_t current_size = dyn_array_func(size)(*self);
    size_t capacity = dyn_array_func(capacity)(*self);
    if (current_size >= capacity) {
        error_t resize_status = data_buffer_resize(&(self->_data),
                                                   self->_data.length * 2);
        if (resize_status.error) {
            return resize_status;
        }
    }
    data_buffer_element_at(self->_data, dyn_array_element_type, current_size) = item;
    current_size++;

    return E_OK;
}

typedef struct {
    collection_obj base;
    dyn_array_type_name impl;
} interface_impl(collection, dyn_array_type_name);

static size_t dyn_array_func(collection_count)(const collection_obj *self)
{
    interface_impl(collection, dyn_array_type_name) *impl = (interface_impl(collection, dyn_array_type_name)*)self;

    return dyn_array_func(size)(impl->impl);
}

static const collection_itf interface_vtbl_name(collection, dyn_array_type_name) = {
     .count = dyn_array_func(collection_count),
};

collection_obj *dyn_array_func(as_collection)(dyn_array_type_name self, const mem_allocator *allocator)
{
    mem_alloc_result alloc_result = allocate_type(allocator, interface_impl(collection, dyn_array_type_name));

    if (alloc_result.error) {
        return nullptr;
    }

    interface_impl(collection, dyn_array_type_name) *wrapper = alloc_result.mem;
    wrapper->base = collection_new(allocator, &interface_vtbl_name(collection, dyn_array_type_name));
    wrapper->impl = self;
    return (collection_obj*)wrapper;
}
