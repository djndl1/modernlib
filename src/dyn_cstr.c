#include "dyn_cstr.h"

#define dyn_string_type_name dyn_cstr
#define dyn_string_character_type char
#include "dyn_str_impl.h"
#undef dyn_string_type_name
#undef dyn_string_character_type
