#include "dyn_wchar_array.h"

#undef dyn_array_element_type
#define dyn_array_element_type wchar_t
#undef dyn_array_type_name
#define dyn_array_type_name dyn_wchar_array
#include "dyn_array_impl.h"
