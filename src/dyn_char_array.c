#include "dyn_char_array.h"

#undef dyn_array_element_type
#define dyn_array_element_type char
#undef dyn_array_type_name
#define dyn_array_type_name dyn_char_array
#include "dyn_array_impl.h"
