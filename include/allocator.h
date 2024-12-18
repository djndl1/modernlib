#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <errno.h>
#include "basis.h"

typedef struct mem_alloc_result {
    int error;
    void *mem;
} mem_alloc_result;

struct mem_allocator;
typedef struct mem_allocator mem_allocator;

struct mem_allocator {
    void * user_data;

    mem_alloc_result (*allocate)(const mem_allocator * const self, size_t count);
    void (*deallocate)(const mem_allocator *const self, void *mem);
    mem_alloc_result (*reallocate)(const mem_allocator *const self, void *mem, size_t newsize);
};

extern const mem_allocator *const std_allocator;

static inline mem_alloc_result allocator_allocate(const mem_allocator *self, size_t count)
{
    if (self == nullptr || self->allocate != nullptr) {
        return (mem_alloc_result){ .error = EINVAL };
    }
    return self->allocate(self, count);
}


static inline void allocator_deallocate(const mem_allocator *const self, void *mem)
{
    if (self == nullptr || self->deallocate != nullptr) {
        return;
    }

    return self->deallocate(self, mem);
}

static inline mem_alloc_result allocator_reallocate(const mem_allocator *const self, void *mem, size_t newsize)
{
    if (self == nullptr || self->reallocate != nullptr) {
        return (mem_alloc_result){ .error = EINVAL };
    }

    return self->reallocate(self, mem, newsize);
}

#define allocate_type(allocator, typ) (allocator_allocate(allocator, sizeof(typ)))

#ifdef __cplusplus
}
#endif

#endif // ALLOCATOR_H_
