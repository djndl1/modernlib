#include "modernlib/dyn_cwstr.h"

#define dyn_string_type_name dyn_cwstr
#define dyn_string_character_type wchar_t

static size_t nts_len(const dyn_string_character_type *str)
{
    return wcslen(str);
}

static int ntscmp(const dyn_string_character_type* a, const dyn_string_character_type* b)
{
    return wcscmp(a, b);
}


#include "modernlib/dyn_str_impl.h"
#undef dyn_string_type_name
#undef dyn_string_character_type
