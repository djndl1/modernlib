#if !defined(dyn_array_element_type) || !defined(dyn_array_type_name)
#error "dynamic array type or dynamic array name not defined!"
#endif

#include "modernlib/data_buffer.h"
#include "modernlib/allocator.h"
#include "modernlib/basis.h"
#include "modernlib/collection.h"
#include "modernlib/internal/compilers.h"

#include "modernlib/dyn_array_macro.h"

typedef struct dyn_array_type_name {
    data_buffer _data;
    size_t _len;
} dyn_array_type_name;


typedef struct dyn_array_result_type_name {
    int error;
    dyn_array_type_name array;
} dyn_array_result_type_name;

MODERNLIB_PUBLIC
dyn_array_result_type_name dyn_array_func(of_capacity)(size_t capacity,
                                                       const mem_allocator *allocator);

MODERNLIB_PUBLIC
dyn_array_result_type_name dyn_array_func(from_data)(const void *data,
                                                     size_t count,
                                                     const mem_allocator *allocator);
MODERNLIB_PUBLIC
dyn_array_result_type_name dyn_array_func(move_from_data)(dyn_array_element_type **data,
                                                          size_t count,
                                                          const mem_allocator *allocator);

MODERNLIB_PUBLIC
dyn_array_result_type_name dyn_array_func(from_buffer)(const data_buffer data,
                                                       const mem_allocator *allocator);

MODERNLIB_PUBLIC
dyn_array_result_type_name dyn_array_func(from_array)(const dyn_array_type_name other,
                                                      const mem_allocator *allocator);

MODERNLIB_ALWAYS_INLINE
static inline size_t dyn_array_func(capacity)(const dyn_array_type_name self)
{
    return self._data.length / sizeof(dyn_array_element_type);
}

MODERNLIB_ALWAYS_INLINE
static inline size_t dyn_array_func(size)(const dyn_array_type_name self)
{
    return self._len;
}

typedef struct dyn_array_get_result_type_name {
    int error;
    dyn_array_element_type element;
} dyn_array_get_result_type_name;

MODERNLIB_PUBLIC
dyn_array_get_result_type_name dyn_array_func(get)(const dyn_array_type_name self, size_t idx);

MODERNLIB_PUBLIC
error_t dyn_array_func(set)(const dyn_array_type_name self, size_t idx, dyn_array_element_type value);

MODERNLIB_PUBLIC
void dyn_array_func(destroy)(dyn_array_type_name *self);

MODERNLIB_PUBLIC
error_t dyn_array_func(append)(dyn_array_type_name *self, dyn_array_element_type item);

MODERNLIB_PUBLIC
error_t dyn_array_func(clear)(dyn_array_type_name *self, void (*destructor)(dyn_array_element_type*));

MODERNLIB_PUBLIC
find_array_index_result dyn_array_func(find_index_of)(const dyn_array_type_name self,
                                                      const dyn_array_element_type item,
                                                      int (*comparer)(const dyn_array_element_type, const dyn_array_element_type),
                                                      size_t start);

MODERNLIB_ALWAYS_INLINE
static inline dyn_array_element_type *dyn_array_func(get_data)(const dyn_array_type_name self)
{
    // this cast does not violate strict aliasing:
    //      the data there is always accessed as dyn_array_element_type
    dyn_array_element_type *pointer = (dyn_array_element_type*)self._data.data;
    return pointer;
}


MODERNLIB_ALWAYS_INLINE
static inline dyn_array_element_type *dyn_array_func(release)(dyn_array_type_name *self)
{
    if (self == nullptr) return nullptr;

    dyn_array_element_type *pointer = dyn_array_func(get_data)(*self);
    self->_data.data = nullptr;
    self->_len = 0;

    return pointer;
}

MODERNLIB_PUBLIC
error_t dyn_array_func(overwrite_at)(const dyn_array_type_name self,
                                     size_t begin_index,
                                     const dyn_array_element_type *source,
                                     size_t count);

MODERNLIB_PUBLIC
error_t dyn_array_func(ensure_capacity)(dyn_array_type_name *self, size_t capacity);

MODERNLIB_PUBLIC
find_array_index_result dyn_array_func(find_index_of)(const dyn_array_type_name self,
                                                      const dyn_array_element_type item,
                                                      int (*comparer)(const dyn_array_element_type, const dyn_array_element_type),
                                                      size_t start);

MODERNLIB_PUBLIC
bool dyn_array_func(contains)(const dyn_array_type_name self,
                              const dyn_array_element_type item,
                              int (*comparer)(const dyn_array_element_type, const dyn_array_element_type));

MODERNLIB_PUBLIC
error_t dyn_array_func(remove_at)(dyn_array_type_name *self,
                                  size_t idx,
                                  void (*destructor)(dyn_array_element_type*));

MODERNLIB_PUBLIC
dyn_array_result_type_name dyn_array_func(concat)(const dyn_array_type_name one,
                                                  const dyn_array_type_name two,
                                                  const mem_allocator *allocator);

MODERNLIB_PUBLIC
bool dyn_array_func(remove)(dyn_array_type_name *self,
                            const dyn_array_element_type item,
                            int (*comparer)(const dyn_array_element_type, const dyn_array_element_type),
                            void (*destructor)(dyn_array_element_type*));

MODERNLIB_PUBLIC
error_t dyn_array_func(insert)(dyn_array_type_name *self,
                               size_t idx,
                               const dyn_array_element_type item);

MODERNLIB_PUBLIC
error_t dyn_array_func(clear)(dyn_array_type_name *self, void (*destructor)(dyn_array_element_type*));

MODERNLIB_PUBLIC
collection_obj *dyn_array_func(as_collection)(dyn_array_type_name self, const mem_allocator *allocator);

#undef dyn_array_element_type
#undef dyn_array_type_name
