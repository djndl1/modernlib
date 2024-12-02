
#define SMART_ENUM_INSTANCE_TYPE my_enum_meta_t
#define MY_ENUM_TYPE(ROW) \
    ROW(MY_A, 3, "Enum Value A") \
    ROW(MY_B, 40000000, "Enum Value B") \
    ROW(MY_C, 40000001, "Enum Value C")

typedef struct my_enum_meta_t {
    int enum_val;
    int code;
    char *name;
} my_enum_meta_t;
const my_enum_meta_t invalid_my_enum_instance = { -1 };



#define SMART_ENUM_INIT_EXPR(a, b, c) { .enum_val = a, .code = b, .name = c }
#include "smart_enum.h"
SMART_ENUM_DEF_CUSTOM_VAL(MY_ENUM_TYPE, my_enum, invalid_my_enum_instance)
#undef SMART_ENUM_INIT_EXPR

#undef SMART_ENUM_INSTNANCE_TYPE

#define static_array_length(arr) ((sizeof(arr)) / sizeof(arr[0]))

int main(void)
{
    for (int i = 0; i < static_array_length(my_enum_instance_array); i++) {
        const my_enum e = my_enum_enum_values[i];
        const my_enum_meta_t instance = my_enum_get_instance(e);
        printf("%s = %d\n", my_enum_get_instance(e).name, my_enum_get_instance(e).code);
    }
}
