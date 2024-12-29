#ifndef MODERNLIB_CONVERSIONS_H
#define MODERNLIB_CONVERSIONS_H

#include "modernlib/macros.h"

#ifdef __cplusplus
#  include <cstdlib>
#  define safe_ptr_cast(src_ptr_type, src_ptr, dst_ptr_type, dst_ptr)   \
    std::memcpy(&dst_ptr, &src_ptr, sizeof(src_ptr_type))
#else
#define safe_ptr_cast(src_ptr_type, src_ptr, dst_ptr_type, dst_ptr)     \
    do {                                                                \
        union {                                                         \
            src_ptr_type src;                                           \
            dst_ptr_type dst;                                           \
        } INTERNAL_VAR(_punning_);                                      \
        INTERNAL_VAR(_punning_).src = src_ptr;                          \
        dst_ptr = INTERNAL_VAR(_punning_).dst;                          \
    } while (0)
#endif


#endif // MODERNLIB_CONVERSIONS_H
