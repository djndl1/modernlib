#include <stdio.h>
#include <stdlib.h>

#ifndef SMART_ENUM_H_
#define SMART_ENUM_H_

#define SMART_ENUM_EXPAND_AS_ARRAY_ELM(a, ...) a,
#define SMART_ENUM_EXPAND_AS_ENUM_DEF(a, b, ...) a = b,
#define SMART_ENUM_EXPAND_AS_ENUM_DEFAULT_DEF(a, ...) a,

#define SMART_ENUM_DEF_ENUM_CUSTOM_VAL(TABLE, enum_tag)     \
    typedef enum enum_tag {                                 \
    TABLE(SMART_ENUM_EXPAND_AS_ENUM_DEF)                    \
} enum_tag;

#define SMART_ENUM_DEF_ENUM_DEFAULT_VAL(TABLE, enum_tag)          \
    typedef enum enum_tag {                                       \
    TABLE(SMART_ENUM_EXPAND_AS_ENUM_DEFAULT_DEF)                  \
} enum_tag;

#define SMART_ENUM_INSTANCE(e) e ## _instance
#define SMART_ENUM_DEF_INSTANCES(TABLE) TABLE(SMART_ENUM_EXPAND_AS_FIELD_STRUCT_INIT)
#define SMART_ENUM_EXPAND_AS_INSTANCE(a, ...) SMART_ENUM_INSTANCE(a),

#define SMART_ENUM_EXPAND_AS_CASE(a, ...) case a: return SMART_ENUM_INSTANCE(a);

#define SMART_ENUM_GEN_ENUM_ARRAY(TABLE, enum_tag) \
    const enum_tag enum_tag ## _enum_values[] = { \
    TABLE(SMART_ENUM_EXPAND_AS_ARRAY_ELM)       \
};

#define SMART_ENUM_DEF_CUSTOM_VAL(TABLE, enum_tag, default_instance_val) \
    SMART_ENUM_DEF_ENUM_CUSTOM_VAL(TABLE, enum_tag)                     \
    SMART_ENUM_DEF_INSTANCES(TABLE)           \
    SMART_ENUM_DEF_GET_INSTANCE_FUNC(TABLE, enum_tag, default_instance_val) \
    SMART_ENUM_GEN_ENUM_ARRAY(TABLE, enum_tag)                          \
    SMART_ENUM_GEN_ENUM_INSTANCE_ARRAY(TABLE, enum_tag)

#define SMART_ENUM_DEF_DEFAULT_VAL(TABLE, enum_tag, default_instance_val) \
    SMART_ENUM_DEF_ENUM_DEFUALT_VAL(TABLE, enum_tag)                     \
    SMART_ENUM_DEF_INSTANCES(TABLE)           \
    SMART_ENUM_DEF_GET_INSTANCE_FUNC(TABLE, enum_tag, default_instance_val) \
    SMART_ENUM_GEN_ENUM_ARRAY(TABLE, enum_tag)                          \
    SMART_ENUM_GEN_ENUM_INSTANCE_ARRAY(TABLE, enum_tag)

#define static_array_length(arr) ((sizeof(arr)) / sizeof(arr[0]))


#endif

#ifndef SMART_ENUM_INSTANCE_TYPE
    #error "Smart enum instance type not defined"
#else

#define SMART_ENUM_DEF_GET_INSTANCE_FUNC(TABLE, enum_tag, default_val)  \
static inline SMART_ENUM_INSTANCE_TYPE enum_tag ## _get_instance(enum_tag e) \
{                                                                       \
    switch (e)                                                          \
    {                                                                   \
        TABLE(SMART_ENUM_EXPAND_AS_CASE)                                \
        default: return default_val;                                    \
    }                                                                   \
}

#define SMART_ENUM_GEN_ENUM_INSTANCE_ARRAY(TABLE, enum_tag) \
    const SMART_ENUM_INSTANCE_TYPE enum_tag ## _instance_array[] = {    \
    TABLE(SMART_ENUM_EXPAND_AS_INSTANCE)                                \
};

#ifndef SMART_ENUM_INIT_EXPR
    #error "Smart enum instance initializer expression is not defined"
#else
    #define SMART_ENUM_EXPAND_AS_FIELD_STRUCT_INIT(a, ...)  \
        const SMART_ENUM_INSTANCE_TYPE SMART_ENUM_INSTANCE(a) \
             = (SMART_ENUM_INSTANCE_TYPE)SMART_ENUM_INIT_EXPR(a, __VA_ARGS__);
#endif

#endif
