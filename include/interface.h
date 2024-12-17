#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "allocator.h"
#include "basis.h"

#define interface_self(itf) (itf.self)
#define interface_impl(itf, impl) CONCAT(impl, CONCAT(_as_, itf))
#define interface_vtbl_name(itf, impl) CONCAT(impl, CONCAT(_vtbl_, itf))

typedef struct interface_base {
    const mem_allocator *allocator;
} interface_base;

static inline void interface_invalidate(interface_base *itf)
{
    if (itf != nullptr
        && itf->allocator != nullptr
        && itf->allocator->deallocate != nullptr) {
        itf->allocator->deallocate(itf->allocator, itf);
    }
}

#endif // INTERFACE_H_
