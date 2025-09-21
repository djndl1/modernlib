#ifndef MODERNLIB_CARRAY_H_
#define MODERNLIB_CARRAY_H_

#include "modernlib/basis.h"

#define carray_funcname(funcname) CONCAT(carray_typename, _ ## carray_size _ ## funcname)
#define carray_type(array_typ, N) CONCAT(array_typ, CONCAT(_, N))


#ifdef __cplusplus

#define make_array(typ, N) (typ{ { 0 }, N })

#else

#define make_array(typ, N) ((carray_type(typ, N)){ .data = { 0 }, .size = N })

#endif


#endif /* ifndef MODERNLIB_CARRAY_H_ */
