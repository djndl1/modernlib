#ifndef MAYBE_OPTIONAL_H
#define MAYBE_OPTIONAL_H

#include <stdbool.h>

#define optional_present(opt) (opt._present)
#define optional_empty(opt) (!opt._present)
#define optional_or_else(opt, alt) (opt._present ? _optional_val(opt) : alt)


#define match_begin(typ, match_obj)  {                              \
    typ __ca3ecda3_7219_428c_8ea3_cebaff20be9b = match_obj; \

#define on_some_begin(typ, val) {                                          \
    typ val = _optional_val(__ca3ecda3_7219_428c_8ea3_cebaff20be9b);           \
    if (optional_present(__ca3ecda3_7219_428c_8ea3_cebaff20be9b))

#define on_some_end }

#define on_none_begin {                                    \
    if (!optional_present(__ca3ecda3_7219_428c_8ea3_cebaff20be9b))
#define on_none_end }
#define match_end }

#define _optional_val(opt) (opt._hidden_obj.t_value)
#define optional_funcname(func) CONCAT()

#endif // MAYBE_OPTIONAL_H
