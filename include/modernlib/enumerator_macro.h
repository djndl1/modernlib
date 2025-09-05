#ifndef ENUMERATOR_MACRO_H_
#define ENUMERATOR_MACRO_H_

#include "modernlib/basis.h"

#undef enumerator_vtable
#define enumerator_vtable(typ) CONCAT(typ, _enumerator_vtable)

#undef enumerator_itf
#define enumerator_itf(typ) CONCAT(typ, _enumrator_itf)

#undef enumerator_func
#define enumerator_func(funcname) CONCAT(enumerator_type_name, _ ## funcname)

#endif /* ENUMERATOR_MACRO_H_  */
