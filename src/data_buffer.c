#include "data_buffer.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "errors.h"


buffer_alloc_result std_allocate_buffer(size_t count)
{
    return data_buffer_new(count, std_allocator);
}

buffer_alloc_result data_buffer_new(size_t count, const mem_allocator *allocator)
{
    buffer_alloc_result result = {
    .error = 0,
    .buffer = {
        .data = nullptr,
        .length = 0,
        .allocator = nullptr,
        }
    };

    if (allocator == nullptr || allocator->allocate == nullptr) {
        result.error = EINVAL;
        return result;
    }

    mem_alloc_result mem_res = allocator->allocate(allocator, count);
    if (mem_res.error != 0) {
        result.error = mem_res.error;
        return result;
    }

    result.error = 0;
    result.buffer.data = mem_res.mem;
    result.buffer.length = count;
    result.buffer.allocator = allocator;

    return result;
}

void data_buffer_destroy(data_buffer *buf)
{
    if (buf == nullptr) return;
    allocator_deallocate(buf->allocator, buf->data);
    buf->data = nullptr;
    buf->length = 0;
}

error_t data_buffer_resize(data_buffer *self, size_t newsize)
{
    if (self->allocator == nullptr || self->allocator->reallocate == nullptr) {
        return E_INVALID_OPERATION;
    }

    mem_alloc_result r = allocator_reallocate(self->allocator, self->data, newsize);
    if (r.error != 0) {
        return ERR_FROM_CODE(r.error);
    }
    self->data = r.mem;
    self->length = newsize;

    return E_OK;
}

static bool buffers_overlapping(const data_buffer a, const data_buffer b)
{
    uint8_t *s1 = a.data;
    uint8_t *e1 = (uint8_t*)a.data + a.length;

    uint8_t *s2 = b.data;
    uint8_t *e2 = (uint8_t*)b.data + b.length;

    return MIN(e1, e2) - MAX(s1, s2) > 0;
}

bool data_buffer_compare(const data_buffer self, const data_buffer other, size_t count)
{
    if (self.data == nullptr && other.data == nullptr
        || self.data != nullptr && other.data == nullptr) {
        return false;
    }

    size_t self_cmp_len = MIN(self.length, count);
    size_t other_cmp_len = MIN(other.length, count);

    if (self_cmp_len != other_cmp_len) return false;

    return memcmp(self.data, other.data, self_cmp_len) == 0;
}

error_t data_buffer_copy_to(const data_buffer self, data_buffer *target)
{
    if (self.data == nullptr || self.length == 0
         || target == nullptr || target->data == nullptr || target->length == 0) {
        return E_INVALID_ARGS;
    }

    if (buffers_overlapping(self, *target)) {
        return E_OVERLAPPING_MEMORY;
    }

    size_t l = MIN(self.length, target->length);

    memcpy(target->data, self.data, l);

    return E_OK;
}

error_t data_buffer_copy_from(data_buffer *self, const void *data, size_t byte_count)
{
    if (self == nullptr) return E_INVALID_ARGS;

    const data_buffer temp_buf = (data_buffer){ .data = (void*)data, .length = byte_count, .allocator = self->allocator };
    return data_buffer_copy_to(temp_buf, self);
}
