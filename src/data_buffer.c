#include "modernlib/data_buffer.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "modernlib/errors.h"


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
    move_ptr(mem_res.mem, result.buffer.data);
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
    move_ptr(r.mem, self->data);
    self->length = newsize;

    return E_OK;
}

static bool buffers_overlapping(const data_buffer a, const data_buffer b)
{
    // uint8_t or unsigned char may alias any object
    const uint8_t *s1 = a.data;
    const uint8_t *e1 = (const uint8_t*)a.data + a.length;

    const uint8_t *s2 = b.data;
    const uint8_t *e2 = (const uint8_t*)b.data + b.length;

    return MIN(e1, e2) - MAX(s1, s2) > 0;
}

bool data_buffer_compare(const data_buffer self, const data_buffer other, size_t count)
{
    if ((self.data == nullptr && other.data != nullptr)
        || (self.data != nullptr && other.data == nullptr)) {
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

error_t data_buffer_copy_content_from(data_buffer *self, const void *data, size_t byte_count)
{
    if (self == nullptr) return E_INVALID_ARGS;

    size_t l = MIN(self->length, byte_count);
    memcpy(self->data, data, l);

    return E_OK;
}

buffer_alloc_result data_buffer_move_from(void **data,
                                          size_t count,
                                          const mem_allocator *const allocator)
{
    if (data == nullptr || *data == nullptr) {
        return (buffer_alloc_result){
            .error = EINVAL,
        };
    }

    void *d;
    move_ptr(*data, d);

    return (buffer_alloc_result){
    .buffer = (data_buffer){
            .allocator = allocator,
            .data = d,
            .length = count,
        },
    };
}
