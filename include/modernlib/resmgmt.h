#ifndef MODERNLIB_RESMGMT_H_
#define MODERNLIB_RESMGMT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "modernlib/internal/compilers.h"
#include "modernlib/macros.h"
#include "modernlib/nullptr.h"

#define move_res(src, dst, invalid) do {     \
        dst = src;                              \
        src = invalid;                          \
    } while (0)

#define move_ptr(src, dst) move_res(src, dst, nullptr)

// both begin and end are required to be expressions
// function calls, even void functions, are valid expressions.
#define scoped(begin, end) for ( \
        int INTERNAL_VAR(_i_) = (begin, 0);  \
        !INTERNAL_VAR(_i_);                  \
        ((INTERNAL_VAR(_i_)) += 1), end)

#define deferred(end) for ( \
        int INTERNAL_VAR(_i_) = 0;  \
        !INTERNAL_VAR(_i_);                  \
        ((INTERNAL_VAR(_i_)) += 1), end)

#ifdef __cplusplus
}
#endif

#endif // MODERNLIB_RESMGMT_H_
