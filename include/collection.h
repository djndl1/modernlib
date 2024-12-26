#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <stddef.h>
#include "interface.h"
#include "internal/compilers.h"

struct collection_obj;

typedef struct collection_itf {
    size_t (*count)(const struct collection_obj*);
} collection_itf;

typedef struct collection_obj {
    interface_base base;
    const collection_itf *itf;
} collection_obj;

MODERNLIB_ALWAYS_INLINE
static inline collection_obj collection_new(const mem_allocator *allocator,
                                            const collection_itf *itf)
{
    return (collection_obj){
        .base = (interface_base){ allocator },
        .itf = itf,
    };
}

MODERNLIB_ALWAYS_INLINE
static inline size_t collection_count(const struct collection_obj* self)
{
    return self->itf->count(self);
}

#endif // COLLECTION_H_
