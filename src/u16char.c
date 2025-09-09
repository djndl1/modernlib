#include "modernlib/u16char.h"
#include "modernlib/allocator.h"
#include "modernlib/basis.h"
#include "modernlib/common_mem_ptr.h"

#include <errno.h>
#include <string.h>


size_t u16len(const uint16_t *s)
{
    const uint16_t *head = s;
    for (; *s; s++);
    return s - head;
}

size_t u16cmp(const uint16_t *l, const uint16_t *r)
{
	  for (; *l==*r && *l; l++, r++);
	  return *(uint16_t*)l - *(uint16_t*)r;
}

uint16_t *u16dup_allocator(const uint16_t *s, const mem_allocator *allocator)
{
  	size_t l = u16len(s);
  	auto alloc_result = allocator_allocate(allocator, l + sizeof(uint16_t));
  	if (alloc_result.error) {
        errno = alloc_result.error;
        return nullptr;
    }
  	return memcpy(alloc_result.mem, s, l + sizeof(uint16_t));
}

uint16_t *u16dup(const uint16_t *s)
{
    return u16dup_allocator(s, std_allocator);
}

uint16_t *u16concat_allocator(const uint16_t *l, const uint16_t* r, const mem_allocator *allocator)
{
    size_t l_len = u16len(l);
    size_t r_len = u16len(r);
    size_t cat_len = l_len + r_len + 1;
    auto alloc_result = uint16_mem_ptr_allocate(cat_len, allocator);
    if (alloc_result.error) {
        errno = alloc_result.error;
        return nullptr;
    }

    uint16_mem_ptr_copy_from_raw(alloc_result.result, 0, l, l_len);
    uint16_mem_ptr_copy_from_raw(alloc_result.result, l_len, r, r_len);
    alloc_result.result.ptr[l_len + r_len] = 0;

    return alloc_result.result.ptr;
}

uint16_t *u16concat(const uint16_t *l, const uint16_t* r)
{
    return u16concat_allocator(l, r, std_allocator);
}
