#ifndef MODERNLIB_COLLECTION_H_
#define MODERNLIB_COLLECTION_H_

#include <stddef.h>
#include "modernlib/interface.h"
#include "modernlib/internal/compilers.h"

struct collection_obj;

/**
 * This is actually the vtable of the `collection` interface
 */
typedef struct collection_itf {
    size_t (*count)(const struct collection_obj*);
} collection_itf;

/**
 * The base interface type of `collection`. Any implementation
 * should inherit this type.
 *
 * While the name ends with an `obj`, it is an interface object,
 * that is, an object that represents an implementation of a type
 * for an interface.
 */
typedef struct collection_obj {
    interface_base base;
    const collection_itf *itf;
} collection_obj;

/**
 * Create an base collection interface object with the specified allocator
 * and the vtable.
 */
MODERNLIB_ALWAYS_INLINE
static inline collection_obj collection_new(const mem_allocator *allocator,
                                            const collection_itf *itf)
{
    collection_obj obj;
    interface_base base = { allocator };
    obj.base = base;
    obj.itf = itf;

    return obj;
}

MODERNLIB_ALWAYS_INLINE
static inline size_t collection_count(const struct collection_obj* self)
{
    return self->itf->count(self);
}

#endif // COLLECTION_H_
