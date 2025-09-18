#if !defined(mem_ptr_typename) 
    #error "no type name of mem_ptr is not defined"
#endif
#if !defined(mem_ptr_target_typename) 
    #error "no target type name of mem_ptr is not defined"
#endif
/**
 * In this header, a memory pointer will be wrapped as an object
 * to improve functionality and better safety.
 * */

#include "modernlib/basis.h"
#include "modernlib/allocator.h"
#include "modernlib/mem_ptr_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

/**
 * Typically, an object should be wrapped in a struct
 * and a pointer to it should never be declared
 * unless pass-by-in-reference parameters are required to perform a mutable borrow.
 * All these types are not resources themselves but handles to resources.
 * They may be copied as values, borrowed as pointers to mutable structures.
 **/
typedef struct  {
    const mem_allocator *allocator;
    mem_ptr_target_typename *ptr;
} mem_ptr_typename;

typedef struct {
    int error;
    mem_ptr_typename result;
} mem_ptr_alloc_result;


/**
 * Allocate a memory region and creates a wrapper object for the memory pointer 
 */
MODERNLIB_ALWAYS_INLINE
static inline mem_ptr_alloc_result mem_ptr_funcname(allocate)(size_t n, const mem_allocator *const allocator)
{
    mem_alloc_result result = allocate_n_item(allocator, n, sizeof(mem_ptr_target_typename));
    mem_ptr_alloc_result ptr_result = { 0 };
    if (result.error) {
        ptr_result.error = result.error;
        return ptr_result;
    }
    ptr_result.error = 0;
    ptr_result.result.allocator = allocator;
    ptr_result.result.ptr = (mem_ptr_target_typename*)result.mem;

    return ptr_result;
}

/**
 * Copy memory area
 *
 * n `mem_ptr_target_typename` is copied into `self + start_index`
 */
MODERNLIB_ALWAYS_INLINE
static inline
void mem_ptr_funcname(copy_from_raw)(const mem_ptr_typename self, size_t start_index, const mem_ptr_target_typename *raw, size_t n)
{
    mem_ptr_target_typename *start_addr = self.ptr + start_index;
    memcpy(start_addr, raw, n * sizeof(mem_ptr_target_typename));
}

/**
 * An object with resources should never be assigned directly:
 * a move function or a clone function should be used
 * to enforce unique ownership.
 *
 * There is no way we can perform a deep clone on a pointer,
 * we can only move it here.
 *
 * This move function should be inlined whenever it is used. If a normal
 * version is required, wrap it on your own.
 */
MODERNLIB_ALWAYS_INLINE
static inline mem_ptr_typename mem_ptr_funcname(move)(mem_ptr_typename *ptr)
{
    // we don't check here and expect a segfault
    // to reveal an error early during development
    // if `ptr_var` really is a variable, then `&ptr_var` should always be valid
    mem_ptr_typename newptr = {
        .allocator = ptr->allocator,
        .ptr = ptr->ptr,
    };
    ptr->ptr = nullptr;
    ptr->allocator = nullptr;
    return newptr;
}

/**
 * Skipping freeing resources is not a recommended way to deal with them.
 **/
MODERNLIB_ALWAYS_INLINE
static inline void mem_ptr_funcname(destroy)(mem_ptr_typename *ptr)
{
    if (ptr == nullptr) return;

    if (ptr->allocator != nullptr) {
        allocator_deallocate(ptr->allocator, ptr->ptr);
    }

    ptr->allocator = nullptr;
    ptr->ptr = nullptr;
}

#ifdef __cplusplus
}
#endif

#undef mem_ptr_typename
#undef mem_ptr_target_typename
