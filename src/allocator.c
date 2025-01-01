#include "modernlib/allocator.h"

#include <stdlib.h>
#include <errno.h>
#include "modernlib/basis.h"

#if defined(_MSC_VER) || defined(__MINGW__)
#  include <malloc.h>
#  define alloca(s) (_alloca(s))
#else
#  include <alloca.h>
#endif

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

static mem_alloc_result static_allocator_func(const mem_allocator *const self, size_t count)
{
    return (mem_alloc_result){
        .error = ENOMEM,
        .mem = nullptr
    };
}

static mem_alloc_result static_reallocator_func(const mem_allocator *const self, void *mem, size_t newsize)
{
    return (mem_alloc_result){
        .error = ENOMEM,
        .mem = nullptr
    };
}

static void void_deallocator_func(const mem_allocator *const self, void *mem)
{ }

static const mem_allocator _static_allocator_table = {
    .user_data = nullptr,
    .allocate = static_allocator_func,
    .deallocate = void_deallocator_func,
    .reallocate = static_reallocator_func,
};

const mem_allocator *const void_allocator = &_static_allocator_table;

static mem_alloc_result stack_allocator_func(const mem_allocator *const self, size_t count)
{
    return (mem_alloc_result) {
            .mem = alloca(count),
            .error = 0,
    };
}

static mem_alloc_result stack_reallocator_func(const mem_allocator *const self, void *mem, size_t newsize)
{
    return (mem_alloc_result) {
            .mem = alloca(newsize),
            .error = 0,
    };
}

static const mem_allocator _stack_allocator_table = {
    .user_data = nullptr,
    .allocate = stack_allocator_func,
    .deallocate = void_deallocator_func,
    .reallocate = stack_reallocator_func,
};

const mem_allocator *const stack_allocator = &_stack_allocator_table;
