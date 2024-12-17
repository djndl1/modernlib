#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct mem_alloc_result {
    int error;
    void *mem;
} mem_alloc_result;

struct mem_allocator;
typedef struct mem_allocator mem_allocator;

struct mem_allocator {
    void *user_data;

    mem_alloc_result (*allocate)(const mem_allocator * const self, size_t count);
    void (*deallocate)(const mem_allocator *const self, void *mem);
    mem_alloc_result (*reallocate)(const mem_allocator *const self, void *mem, size_t newsize);
};

extern const mem_allocator *const std_allocator;

#ifdef __cplusplus
}
#endif

#endif // ALLOCATOR_H_
