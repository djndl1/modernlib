#include "modernlib/internal/compilers.h"
#if !defined(enumerator_type_name)
    #error "The type name of enumerator is not defined"
#endif

#if !defined(enumerator_element_type_name)
    #error "The element type name of enumerator is not defined"
#endif


#include "modernlib/basis.h"
#include "modernlib/interface.h"
#include "modernlib/enumerator_macro.h"
#include "modernlib/mem_ptr.h"

struct enumerator_type_name;

typedef struct enumerator_vtable(enumerator_type_name) {
    enumerator_element_type_name (*current)(const struct enumerator_type_name*); 
    bool (*next)(const struct enumerator_type_name*);
    void (*reset)(const struct enumerator_type_name*);
} enumerator_vtable(enumerator_type_name);

typedef struct enumerator_itf(enumerator_type_name) {
    interface_base base;
    const enumerator_vtable(enumerator_type_name) *vtable;
} enumerator_itf(enumerator_type_name);

typedef struct enumerator_type_name {
    enumerator_itf(enumerator_type_name) *itf;
} enumerator_type_name;

MODERNLIB_ALWAYS_INLINE
static inline
enumerator_element_type_name enumerator_func(current)(const enumerator_type_name self)
{
    return self.itf->vtable->current(&self);
}

MODERNLIB_ALWAYS_INLINE
static inline
bool enumerator_func(next)(const struct enumerator_type_name self)
{
    return self.itf->vtable->next(&self);
}

MODERNLIB_ALWAYS_INLINE
static inline
void enumerator_func(reset)(const struct enumerator_type_name self)
{
    self.itf->vtable->reset(&self);
}

#undef enumerator_type_name
#undef enumerator_element_type_name
