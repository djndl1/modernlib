#ifndef MAYBE_OPTIONAL_H
#define MAYBE_OPTIONAL_H

#include <stdbool.h>

#define optional_funcname(typ, func) CONCAT(typ, CONCAT(_, func))

#ifdef __cplusplus
#define optional_some(opt_typ, value) (opt_typ { true, { value } })
#define optional_none(opt_typ) (opt_typ { false })
#else
#define optional_some(opt_typ, value) ((opt_typ) { ._present = true, ._hidden_obj.t_value = value })
#define optional_none(opt_typ) ((opt_typ) { ._present = false })
#endif

#define optional_try_get(opt_typ, opt, value) (optional_funcname(opt_typ, try_get)(opt, value))

#define optional_present(opt) (opt._present)
#define optional_empty(opt) (!opt._present)
#define optional_or_else(opt, alt) (opt._present ? _optional_val(opt) : alt)

#define _optional_val(opt) (opt._hidden_obj.t_value)

#define optional_map(U, opt, mapping) (optional_present(opt) ?           \
                                       optional_some(U, mapping(_optional_val(opt))) \
                                       : optional_none(U))

#define optional_filter(U, opt, filter) (optional_present(opt) \
                ? (filter(_optional_val(opt)) ? opt : optional_none(U)) \
                : optional_none(U))

// We won't be needing this anymore once we have if-declarations in C2y
#define optional_ifsome(opt_typ, opt, optval) \
    for (auto optval = optional_funcname(opt_typ, ifsome_helper)(opt); optval.temp_present; optval.temp_present = false)

#define optional_ifnone(opt_typ, opt, optval) \
    for (auto optval = optional_funcname(opt_typ, ifsome_helper)(opt); !optval.temp_present; optval.temp_present = true)

#if __GNUC__ >= 15  || defined(__cplusplus)
#define optional_if(opt, valvar) \
    if (auto valvar = _optional_val(opt); optional_present(opt))
#endif

#endif // MAYBE_OPTIONAL_H
