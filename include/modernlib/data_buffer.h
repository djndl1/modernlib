#ifndef MODERNLIB_BUFFER_H_
#define MODERNLIB_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include <stdbool.h>
#include "basis.h"
#include "modernlib/errors.h"
#include "modernlib/allocator.h"

/**
 * A data buffer a chunk of memory. It contains a pointer to an allocator
 * object that is responsible for its allocation and deallocation.
 **/
typedef struct data_buffer {
    void *data;
    size_t length;

    const mem_allocator *allocator;
} data_buffer;

#ifdef __cplusplus
#  define DATA_BUFFER_TRANSIENT(dat, len) data_buffer{ dat, len, void_allocator }
#else
#  define DATA_BUFFER_TRANSIENT(dat, len) \
    ((data_buffer){ .data = dat, .length = len, .allocator = void_allocator })
#endif

/**
 * @return the byte lvalue at the specified index of the buffer
 **/
#define byte_buffer_at(self, idx) (data_buffer_as_byte_array(self)[idx])

typedef struct buffer_alloc_result {
    int error;
    data_buffer buffer;
} buffer_alloc_result;


MODERNLIB_PUBLIC
buffer_alloc_result data_buffer_new(size_t count, const mem_allocator *allocator);

MODERNLIB_PUBLIC
buffer_alloc_result std_allocate_buffer(size_t);

MODERNLIB_PUBLIC
void data_buffer_destroy(data_buffer*);

MODERNLIB_PUBLIC
buffer_alloc_result data_buffer_move_from(void **data,
                                          size_t count,
                                          const mem_allocator *const allocator);

MODERNLIB_PUBLIC
merror data_buffer_copy_content_from(data_buffer *self, const void *data, size_t byte_count);


MODERNLIB_PUBLIC
merror data_buffer_copy_to(const data_buffer, data_buffer*);

MODERNLIB_PUBLIC
merror data_buffer_resize(data_buffer *self, size_t newsize);

MODERNLIB_PUBLIC
bool data_buffer_compare(const data_buffer self, const data_buffer other, size_t count);

MODERNLIB_ALWAYS_INLINE
static inline uint8_t *data_buffer_as_byte_array(const data_buffer self)
{
    // uint8_t is unsigned char under the hood, no strict aliasing violation
    uint8_t *pointer = (uint8_t*)self.data;
    return pointer;
}


MODERNLIB_ALWAYS_INLINE
static inline void *data_buffer_release(data_buffer *buf)
{
    void *ptr = buf->data;
    buf->data = nullptr;
    buf->length = 0;
    buf->allocator = nullptr;

    return ptr;
}


MODERNLIB_ALWAYS_INLINE
static inline data_buffer data_buffer_move(data_buffer *old)
{
    data_buffer newbuf;
    newbuf.length = old->length;
    newbuf.allocator = old->allocator;
    newbuf.data = data_buffer_release(old);

    return newbuf;
}

MODERNLIB_ALWAYS_INLINE
static inline buffer_alloc_result data_buffer_copy(const data_buffer source)
{
    buffer_alloc_result newresult = data_buffer_new(source.length, source.allocator);
    if (newresult.error) {
        return newresult;
    }

    merror e = data_buffer_copy_to(source, &newresult.buffer);
    if (e.error) {
        data_buffer_destroy(&newresult.buffer);
        buffer_alloc_result copy_result = { 0  };
        copy_result.error = e.error;
        return copy_result;
    }

    buffer_alloc_result alloc_result = { 0 };
    alloc_result.buffer = data_buffer_move(&newresult.buffer);
    alloc_result.error = 0;
    return alloc_result;
}

#ifdef __cplusplus
}
#endif

#endif // BUFFER_H_
