#if !defined(optional_element_type) || !defined(optional_type_name)
#error "optional_element_t or optional_name is not defined"
#endif

#include <stdbool.h>
#include "util.h"

#include "macros.h"

typedef struct optional_type_name {
    bool _present;
    struct {
        optional_element_type t_value;
    } _hidden_obj;
} optional_type_name;

#define optional_funcname(func) CONCAT(optional_element_type, _ ## func)

MODERNLIB_INLINE
static inline optional_type_name optional_funcname(some)(optional_element_type val)
{
    return (optional_name){ ._present = true, ._hidden_obj.t_value = val, };
}

#define optional_map_to(U, opt, mapping) (optional_present(opt) ?           \
                                       optional_some(U)(mapping(_optional_val(opt))) \
                                       : optional_none(U))

typedef bool (*CONCAT(optional_element_t, _pred))(optional_element_t);

MODERNLIB_INLINE
static inline optional_name CONCANT(optional_element_t, _filter)(
    optional_name opt,
    CONCAT(optional_element_t, _pred) pred)
{
    return optional_present(opt)
        ? (pred(_optional_val(opt)) ? opt : optional_none(optional_element_t))
        : optional_none(optional_element_t);
}

#endif // optional_element_t
#undef optional_element_t
#undef optional_name
