#if !defined(optional_element_type) || !defined(optional_type_name)
#error "optional_element_t or optional_name is not defined"
#endif

#include <stdbool.h>
#include "modernlib/basis.h"

#include "modernlib/optional.h"

typedef struct optional_type_name {
    bool _present;
    struct {
        optional_element_type t_value;
    } _hidden_obj;
} optional_type_name;

typedef struct {
    bool temp_present;
    optional_element_type value;
} CONCAT(__temp_var_, optiona_type_name);

MODERNLIB_ALWAYS_INLINE
static inline
CONCAT(__temp_var_, optiona_type_name) optional_funcname(optional_type_name, ifsome_helper)(const optional_type_name self)
{
    CONCAT(__temp_var_, optiona_type_name) temp;
    temp.value = _optional_val(self);
    temp.temp_present = self._present;

    return temp;
}

/**
 * Not safe due to use of out pointer
 */
MODERNLIB_ALWAYS_INLINE
static inline
bool optional_funcname(optional_type_name, try_get)(const optional_type_name self, optional_element_type *value)
{
    if (optional_present(self)) {
        if (value != nullptr) {
            *value = _optional_val(self);
        }
        return true;
    } else {
        return false;
    }
}

#undef optional_element_type
#undef optional_type_name
