/**
 * This header is not meant to be a base for various object. Rather,
 * it is meant to provide a model based on which an object should be written.
 *
 * In this header, a memory pointer will be wrapped as an object
 * to improve functionality and better safety.
 * */
#ifndef MODERNLIB_OBJECT_H_

#include "modernlib/allocator.h"
#include "modernlib/basis.h"

/**
 * Typically, an object should be wrapped in a struct
 * and a pointer to it should never be declared
 * unless pass-by-in-reference parameters are required to perform a mutable borrow.
 * All these types are not resources themselves but handles to resources.
 * They may be copied as values, borrowed as pointers to mutable structures.
 **/
typedef struct generic_mem_ptr {
    void *ptr;
} generic_mem_ptr;

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
static inline generic_mem_ptr generic_mem_ptr_move(generic_mem_ptr *ptr)
{
    // we don't check here and expect a segfault
    // to reveal an error early during development
    // if `ptr_var` really is a variable, then `&ptr_var` should always be valid
    generic_mem_ptr newptr;
    newptr.ptr = ptr->ptr;
    ptr->ptr = nullptr;
    return newptr;
}

/**
 * We don't known what to do when a pointer is no longer used because
 * we are not sure if the referenced resource needs destroying.
 * We simply set it to `NULL` here.
 * Skipping freeing resources is not a recommended way to deal with them.
 **/
MODERNLIB_ALWAYS_INLINE
static inline void generic_mem_ptr_destroy(generic_mem_ptr *ptr)
{
    if (ptr == nullptr) return;

    ptr->ptr = nullptr;
}

/**
 * A pointer may be dereferenced but only as the type of the referenced object
 * to ensure strict aliasing rules are not violated
 **/
#define mem_ptr_as(ptr, typ) ((typ*)ptr)
#define mem_ptr_deref(ptr, typ) (*mem_ptr_as(ptr, typ))

#define MODERNLIB_OBJECT_H_

#endif // MODERNLIB_OBJECT_H_
