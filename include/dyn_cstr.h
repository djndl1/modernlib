#ifndef DYN_CSTR_H_
#define DYN_CSTR_H_

#include "data_buffer.h"
#include "allocator.h"

typedef struct dyn_cstr {
    data_buffer _data;
    size_t _len;
} dyn_cstr;

typedef struct dyn_cstr_result {
    int error;
    dyn_cstr str;
} dyn_cstr_result;

typedef struct dyn_cstr_iter {
    dyn_cstr _str;
    char *_p;
} dyn_cstr_iter;


static inline char *dyn_cstr_nbts(dyn_cstr self)
{
    return ((char*)(self._data.data));
}

#define dyn_cstr_at(self, idx) ((dyn_cstr_nbts(self))[idx])

#define dyn_cstr_from_buffer_stdalloc(buf) (dyn_cstr_from_buffer(buf, std_allocator))

dyn_cstr_result dyn_cstr_from_buffer(data_buffer buf, const mem_allocator *allocator);

#define dyn_cstr_from_stdalloc(str) (dyn_cstr_from(str, std_allocator))

dyn_cstr_result dyn_cstr_from(dyn_cstr str, const mem_allocator *allocator);

#define dyn_cstr_literal_stdalloc(lit) (dyn_cstr_literal(lit, std_allocator))

dyn_cstr_result dyn_cstr_literal(const char *lit, const mem_allocator *allocator);

static inline size_t dyn_cstr_len(dyn_cstr self)
{
    return self._len;
}

int dyn_cstr_compare(dyn_cstr self, dyn_cstr other);

static bool dyn_cstr_equal(dyn_cstr self, dyn_cstr other)
{
    return dyn_cstr_compare(self, other) == 0;
}

void dyn_cstr_destroy(dyn_cstr self);

static inline dyn_cstr_iter dyn_cstr_iter_new(const dyn_cstr self)
{
    return (dyn_cstr_iter) {
        ._str = self,
        ._p = NULL,
    };
}

static inline char dyn_cstr_iter_cur(const dyn_cstr_iter self)
{
    return *(self._p);
}

static inline char *dyn_cstr_iter_cur_ref(const dyn_cstr_iter self)
{
    return self._p;
}

static inline const char *dyn_cstr_iter_cur_cref(const dyn_cstr_iter self)
{
    return self._p;
}

static inline bool dyn_cstr_iter_next(dyn_cstr_iter *self)
{
    char *tmp = (char*)self->_str._data.data;
    if (tmp == NULL || *tmp == '\0') {
        return false;
    }

    if (self->_p == NULL) {
        self->_p = (char*)self->_str._data.data;
        return true;
    }

    if (*self->_p != '\0') {
        self->_p++;
        return true;
    }

    return false;
}

#define dyn_cstr_foreach(it, str) \
    for (dyn_cstr_iter it = dyn_cstr_iter(str); dyn_cstr_iter_next(&it); )
#endif // DYN_CSTR_H_
