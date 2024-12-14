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
        .data = NULL,
        .length = 0,
        .allocator = NULL,
        }
    };

    if (allocator == NULL || allocator->allocate == NULL) {
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

void data_buffer_deallocate(data_buffer buf)
{
    if (buf.allocator != NULL && buf.allocator->deallocate != NULL) {
        buf.allocator->deallocate(buf.allocator, buf.data);
    }
}

error_t data_buffer_resize(data_buffer self, size_t newsize)
{
    if (self.allocator == NULL || self.allocator->reallocate == NULL) {
        return ERR_FROM_CODE(E_INVALID_OP);
    }

    mem_alloc_result r = self.allocator->reallocate(self.allocator, self.data, newsize);
    if (r.error != 0) {
        return ERR_FROM_CODE(r.error);
    }
    self.data = r.mem;
    self.length = newsize;

    return E_OK;
}

static bool buffers_overlapping(const data_buffer a, const data_buffer b)
{
    void *s1 = a.data;
    void *e1 = a.data + a.length;

    void *s2 = b.data;
    void *e2 = b.data + b.length;

    return MIN(e1, e2) - MAX(s1, s2) > 0;
}

bool data_buffer_compare(const data_buffer self, data_buffer other, size_t count)
{
    if (self.data == NULL && other.data == NULL
        || self.data != NULL && other.data == NULL) {
        return false;
    }

    size_t self_cmp_len = MIN(self.length, count);
    size_t other_cmp_len = MIN(other.length, count);

    if (self_cmp_len != other_cmp_len) return false;

    return memcmp(self.data, other.data, self_cmp_len) == 0;
}

error_t data_buffer_copy_to(const data_buffer self, data_buffer target)
{
    if (self.data == NULL || self.length == 0
         || target.data == NULL || target.length == 0) {
        return ERR_FROM_CODE(EINVAL);
    }

    if (buffers_overlapping(self, target)) {
        return ERR_FROM_CODE(E_OVERLAP_MEM);
    }

    size_t l = MIN(self.length, target.length);

    memcpy(target.data, self.data, l);

    return E_OK;
}

error_t data_buffer_copy_from(data_buffer self, const void *data, size_t byte_count)
{
    const data_buffer temp_buf = (data_buffer){ .data = (void*)data, .length = byte_count, .allocator = self.allocator };
    return data_buffer_copy_to(temp_buf, self);
}
