#include "allocator.h"

#include <stdlib.h>
#include <errno.h>
#include "basis.h"

mem_alloc_result std_allocator_func(const mem_allocator *const self, size_t count)
{
    void *mem = malloc(count);
    if (mem == nullptr) {
        return (mem_alloc_result) { .error = errno, .mem = nullptr };
    }

    return (mem_alloc_result) { .error = 0, .mem = mem };
}

void std_deallocator_func(const mem_allocator *const self, void *mem)
{
    free(mem);
}

mem_alloc_result std_reallocator_func(const mem_allocator *const self, void *mem, size_t newsize)
{
    void *newmem = realloc(mem, newsize);
    if (newmem == nullptr) {
        return (mem_alloc_result) { .error = errno, .mem = nullptr };
    }

    return (mem_alloc_result) { .error = 0, .mem = newmem };
}


static const mem_allocator _std_allocator_table = {
    .user_data = nullptr,
    .allocate = std_allocator_func,
    .deallocate = std_deallocator_func,
    .reallocate = std_reallocator_func,
};

const mem_allocator *const std_allocator = &_std_allocator_table;
