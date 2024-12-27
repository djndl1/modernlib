#include "modernlib/dyn_cstr.h"

#define dyn_string_type_name dyn_cstr
#define dyn_string_character_type char

static int ntscmp(const dyn_string_character_type* a, const dyn_string_character_type* b)
{
    return strcmp(a, b);
}

static size_t nts_len(const dyn_string_character_type *str)
{
    return strlen(str);
}

#include "modernlib/dyn_str_impl.h"
#undef dyn_string_type_name
#undef dyn_string_character_type
