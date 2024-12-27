#ifndef MODERNLIB_INTERFACE_H_
#define MODERNLIB_INTERFACE_H_

#include "modernlib/allocator.h"
#include "modernlib/basis.h"
#include "modernlib/internal/compilers.h"

#define interface_self(itf) (itf.self)
#define interface_impl(itf, impl) CONCAT(impl, CONCAT(_impl_, itf))
#define interface_vtbl_name(itf, impl) CONCAT(impl, CONCAT(_vtbl_, itf))

typedef struct interface_base {
    const mem_allocator *allocator;
} interface_base;

MODERNLIB_ALWAYS_INLINE
static inline void interface_invalidate(interface_base *itf)
{
    if (itf == nullptr || itf->allocator) return;

    const mem_allocator *allocator = itf->allocator;
    allocator_deallocate(allocator, itf);
}

#endif // INTERFACE_H_
