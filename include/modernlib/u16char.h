#ifndef U16CHAR_H_
#define U16CHAR_H_

#include "modernlib/allocator.h"
#include "modernlib/common_mem_ptr.h"
#include <stdint.h>

MODERNLIB_PUBLIC
size_t u16len(const uint16_t *s);

MODERNLIB_PUBLIC
size_t u16cmp(const uint16_t *s1, const uint16_t *s2);

MODERNLIB_PUBLIC
uint16_t *u16dup_allocator(const uint16_t *s, const mem_allocator *allocator);

MODERNLIB_PUBLIC
uint16_t *u16dup(const uint16_t *s);

MODERNLIB_PUBLIC
uint16_t *u16concat_allocator(const uint16_t *l, const uint16_t* r, const mem_allocator *allocator);

MODERNLIB_PUBLIC
uint16_t *u16concat(const uint16_t *l, const uint16_t* r);

#endif /* ifndef U16CHAR_H_ */
