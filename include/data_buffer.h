#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include <stddef.h>

#include <stdbool.h>
#include "util.h"
#include "errors.h"
#include "allocator.h"

typedef struct data_buffer {
    void *data;
    size_t length;

    const mem_allocator *allocator;
} data_buffer;

#define DATA_BUFFER_TRANSIENT(dat, len) \
    ((data_buffer){ .data = dat, .length = len, .allocator = NULL })

#define data_buffer_element_at(self, typ, idx) \
    (((typ*)self.data)[idx])
#define byte_buffer_at(self, idx) data_buffer_element_at(self, uint8_t, idx)

typedef struct buffer_alloc_result {
    int error;
    data_buffer buffer;
} buffer_alloc_result;

bool data_buffer_compare(const data_buffer self, data_buffer other, size_t count);

error_t data_buffer_resize(data_buffer self, size_t newsize);

error_t data_buffer_copy_to(const data_buffer, data_buffer);

buffer_alloc_result data_buffer_new(size_t count, const mem_allocator *allocator);

buffer_alloc_result std_allocate_buffer(size_t);

void data_buffer_deallocate(data_buffer);



#endif // BUFFER_H_
