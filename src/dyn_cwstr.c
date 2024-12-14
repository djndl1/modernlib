#include "dyn_cwstr.h"

#define dyn_string_type_name dyn_cwstr
#define dyn_string_character_type wchar_t
#include "dyn_str_impl.h"
#undef dyn_string_type_name
#undef dyn_string_character_type
