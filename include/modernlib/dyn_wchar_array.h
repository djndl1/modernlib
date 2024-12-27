#ifndef DYN_WCHAR_ARRAY_H_
#define DYN_WCHAR_ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <wchar.h>

#undef dyn_array_element_type
#define dyn_array_element_type wchar_t
#undef dyn_array_type_name
#define dyn_array_type_name dyn_wchar_array
#include "modernlib/dyn_array_itf.h"

#ifdef __cplusplus
}
#endif

#endif // DYN_WCHAR_ARRAY_H_
