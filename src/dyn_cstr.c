#include "dyn_cstr.h"

#include <string.h>

static void sync_len(dyn_cstr *self)
{
    size_t l = 0;
    if (self->_data.data == NULL || self->_data.length == 0) {
        l = 0;
    } else {
        l = strlen(self->_data.data);
    }

    self->_len = l;
}

static dyn_cstr_result _create_dyn_cstr_from_data(const void *data,
                                                    size_t count,
                                                    const mem_allocator *allocator)
{
     buffer_alloc_result alloc_res = data_buffer_new(count + 1, allocator);
     if (alloc_res.error) {
         return (dyn_cstr_result) { .error = alloc_res.error };
     }
     data_buffer buf = alloc_res.buffer;

     memcpy(buf.data, data, count);

     dyn_cstr str = { ._data = buf };
     dyn_cstr_at(str, count) = '\0';
     sync_len(&str);

     return (dyn_cstr_result) { .error = 0, .str = str };
}

static dyn_cstr_result _create_dyn_cstr_from_nbts(const char *nbts,
                                                    const mem_allocator *allocator)
{
     size_t l = strlen(nbts);
     return  _create_dyn_cstr_from_data(nbts, l, allocator);
}

dyn_cstr_result dyn_cstr_from_buffer(data_buffer buf, const mem_allocator *allocator)
{
    return _create_dyn_cstr_from_data(buf.data, buf.length, allocator);
}

dyn_cstr_result dyn_cstr_from(dyn_cstr str, const mem_allocator *allocator)
{
    return _create_dyn_cstr_from_nbts(str._data.data, allocator);
}

dyn_cstr_result dyn_cstr_literal(const char *lit, const mem_allocator *allocator)
{
    return _create_dyn_cstr_from_nbts(lit, allocator);
}

int dyn_cstr_compare(dyn_cstr self, dyn_cstr other)
{
    return strcmp(self._data.data, other._data.data);
}

void dyn_cstr_destroy(dyn_cstr self)
{
    if (self._data.data == NULL || self._data.allocator == NULL) {
        return;
    }

    self._data.allocator->deallocate(self._data.allocator, self._data.data);
}
