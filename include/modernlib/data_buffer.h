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

typedef struct data_buffer {
    void *data;
    size_t length;

    const mem_allocator *allocator;
} data_buffer;

#ifdef __cplusplus
#  define DATA_BUFFER_TRANSIENT(dat, len) data_buffer{ dat, len, nullptr }
#else
#  define DATA_BUFFER_TRANSIENT(dat, len) \
    ((data_buffer){ .data = dat, .length = len, .allocator = nullptr })
#endif

#define byte_buffer_at(self, idx) (data_buffer_as_byte_array(self)[idx])

typedef struct buffer_alloc_result {
    int error;
    data_buffer buffer;
} buffer_alloc_result;


MODERNLIB_ALWAYS_INLINE
static inline uint8_t *data_buffer_as_byte_array(const data_buffer self)
{
    uint8_t *pointer = self.data;
    return pointer;
}

MODERNLIB_PUBLIC
bool data_buffer_compare(const data_buffer self, const data_buffer other, size_t count);

MODERNLIB_PUBLIC
error_t data_buffer_resize(data_buffer *self, size_t newsize);

MODERNLIB_PUBLIC
error_t data_buffer_copy_to(const data_buffer, data_buffer*);

MODERNLIB_PUBLIC
error_t data_buffer_copy_from(data_buffer *self, const void *data, size_t byte_count);

MODERNLIB_PUBLIC
buffer_alloc_result data_buffer_new(size_t count, const mem_allocator *allocator);

MODERNLIB_PUBLIC
buffer_alloc_result std_allocate_buffer(size_t);

MODERNLIB_PUBLIC
void data_buffer_destroy(data_buffer*);


#ifdef __cplusplus
}
#endif

#endif // BUFFER_H_
