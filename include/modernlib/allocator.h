#ifndef MODERNLIB_ALLOCATOR_H_
#define MODERNLIB_ALLOCATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <errno.h>
#include "modernlib/basis.h"
#include "modernlib/internal/compilers.h"

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

MODERNLIB_PUBLIC
extern const mem_allocator *const std_allocator;

MODERNLIB_ALWAYS_INLINE
static inline mem_alloc_result allocator_allocate(const mem_allocator *self, size_t count)
{
    if (self == nullptr || self->allocate == nullptr) {
        mem_alloc_result result;
        result.error = EINVAL;
        return result;
    }
    return self->allocate(self, count);
}


MODERNLIB_ALWAYS_INLINE
static inline void allocator_deallocate(const mem_allocator *const self, void *mem)
{
    if (self == nullptr || self->deallocate == nullptr) {
        return;
    }

    return self->deallocate(self, mem);
}

MODERNLIB_ALWAYS_INLINE
static inline mem_alloc_result allocator_reallocate(const mem_allocator *const self, void *mem, size_t newsize)
{
    if (self == nullptr || self->reallocate == nullptr) {
        mem_alloc_result result;
        result.error = EINVAL;
        return result;
    }

    return self->reallocate(self, mem, newsize);
}

#define allocate_n_item(allocator, n, item_size) (allocator_allocate(allocator, n * item_size))
#define allocate_type(allocator, typ) allocate_n_item(allocator, 1, sizeof(typ))
#define allocate_typed_array(allocator, typ, item_count) allocate_n_item(allocator, item_count, sizeof(typ))

#ifdef __cplusplus
}
#endif

#endif // ALLOCATOR_H_
