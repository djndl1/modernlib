#include "modernlib/data_buffer.h"
#include "modernlib/errors.h"
#include <errno.h>

#include "modernlib/dyn_array_macro.h"
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

#define dyn_array_get_direct(self, idx) (dyn_array_func(get_data)(self)[idx])

#define dyn_array_get_directp(pself, idx)  (dyn_array_func(get_data)(*self)[idx])

dyn_array_get_result_type_name dyn_array_func(get)(const dyn_array_type_name self, size_t idx)
{
    if (idx >= dyn_array_func(size)(self)) {
        return (dyn_array_get_result_type_name){ .error = ERANGE };
    }


    return (dyn_array_get_result_type_name){
        .element = dyn_array_get_direct(self, idx),
    };
}

error_t dyn_array_func(set)(const dyn_array_type_name self, size_t idx, dyn_array_element_type value)
{
    if (idx >= dyn_array_func(size)(self)) {
        return E_INVALID_ARGS;
    }

    dyn_array_get_direct(self, idx) = value;
    return E_OK;
}

void dyn_array_func(destroy)(dyn_array_type_name *self)
{
    data_buffer_destroy(&self->_data);
}

error_t dyn_array_func(ensure_capacity)(dyn_array_type_name *self, size_t capacity)
{
    size_t cur_capacity = dyn_array_func(capacity)(*self);
    if (capacity > cur_capacity) {
        size_t newsize = cur_capacity == 0
            ? sizeof(dyn_array_element_type) * capacity
            : (capacity / cur_capacity + 1) * self->_data.length;
        error_t resize_status = data_buffer_resize(&(self->_data), newsize);

        if (resize_status.error) {
            return resize_status;
        }
    }
    return E_OK;
}

error_t dyn_array_func(append)(dyn_array_type_name *self, dyn_array_element_type item)
{
    return dyn_array_func(insert)(self, self->_len, item);
}

error_t dyn_array_func(clear)(dyn_array_type_name *self, void (*destructor)(dyn_array_element_type*))
{
    if (self == nullptr) return E_INVALID_ARGS;

    if (destructor != nullptr) {
        for (size_t i = 0; i < self->_len; i++) {
            destructor(&dyn_array_get_directp(self, i));
        }
    }

    self->_len = 0;
    return E_OK;
}

error_t dyn_array_func(remove_at)(dyn_array_type_name *self, size_t idx, void (*destructor)(dyn_array_element_type*))
{
    if (self == nullptr) return E_INVALID_ARGS;
    if (idx >= self->_len) return E_OUT_OF_RANGE;

    if (destructor != nullptr) {
        destructor(&dyn_array_get_directp(self, idx));
    }
    size_t remaining_count_after = self->_len - 1 - idx;
    if (remaining_count_after > 0) {
        memmove(&dyn_array_get_directp(self, idx),
                &dyn_array_get_directp(self, idx + 1),
                remaining_count_after * sizeof(dyn_array_element_type));
    }
    self->_len--;
    return E_OK;
}

error_t dyn_array_func(insert)(dyn_array_type_name *self,
                               size_t idx,
                               const dyn_array_element_type item)
{
    if (self == nullptr) return E_INVALID_ARGS;
    if (idx > self->_len) return E_OUT_OF_RANGE;

    error_t err = dyn_array_func(ensure_capacity)(self, self->_len + 1);
    if (err.error) {
        return err;
    }

    size_t count_after = self->_len - idx;
    if (count_after > 0) {
        memmove(&dyn_array_get_directp(self, idx + 1),
                &dyn_array_get_directp(self, idx),
                count_after * sizeof(dyn_array_element_type));
    }
    dyn_array_get_directp(self, idx) = item;
    self->_len++;

    return E_OK;
}

bool dyn_array_func(remove)(dyn_array_type_name *self,
                            const dyn_array_element_type item,
                            int (*comparer)(const dyn_array_element_type, const dyn_array_element_type),
                            void (*destructor)(dyn_array_element_type*))
{
    if (self == nullptr) return false;

    find_array_index_result find_result = dyn_array_func(find_index_of)(*self, item, comparer, 0);
    if (!find_result.found) {
        return false;
    }

    error_t err = dyn_array_func(remove_at)(self, find_result.index, destructor);
    if (err.error) {
        return false;
    }

    return true;
}

find_array_index_result dyn_array_func(find_index_of)(const dyn_array_type_name self,
                                                      const dyn_array_element_type item,
                                                      int (*comparer)(const dyn_array_element_type, const dyn_array_element_type),
                                                      size_t start)
{
    if (start >= self._len) {
        return (find_array_index_result){ .found = false };
    }

    for (size_t i = start; i < self._len; i++) {
        dyn_array_element_type cur = dyn_array_get_direct(self, i);
        if (comparer(cur, item) == 0) {
            return (find_array_index_result){ .found = true, .index = i };
        }
    }
    return (find_array_index_result){ .found = false };
}

bool dyn_array_func(contains)(const dyn_array_type_name self,
                              const dyn_array_element_type item,
                              int (*comparer)(const dyn_array_element_type, const dyn_array_element_type))
{
    find_array_index_result idx_result = dyn_array_func(find_index_of)(self, item, comparer, 0);

    return idx_result.found;
}

typedef struct {
    collection_obj base;
    dyn_array_type_name impl;
} interface_impl(collection, dyn_array_type_name);

static size_t dyn_array_func(collection_count)(const collection_obj *self)
{
    // valid cast to the implementation structure by the standard
    interface_impl(collection, dyn_array_type_name) *impl
        = (interface_impl(collection, dyn_array_type_name)*)self;

    // a valid alias to access its `base` and `impl` members by strict aliasing rules
    // no violation of strict aliasing
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

    // valid cast. Really a pointer to its first member
    // no aliasing violation
    // as we are not accessing the implementation structure
    // only its first member
    return (collection_obj*)wrapper;
}
