#ifndef MODERNLIB_RESMGMT_H_
#define MODERNLIB_RESMGMT_H_

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

#ifdef __GNUC__
/*
 * from https://gustedt.wordpress.com/2025/01/06/simple-defer-ready-to-use/
 */

#define gnu_defer __GNU_DEFER(__COUNTER__)
#define __GNU_DEFER(N) __GNU_DEFER_(N)
#define __GNU_DEFER_(N) __GNU_DEFER__(__DEFER_FUNCTION_ ## N, __DEFER_VARIABLE_ ## N)

#define __GNU_DEFER__(F, V)      \
    MODERNLIB_ALWAYS_INLINE inline \
    auto void F(int*);         \
    __attribute__((cleanup(F))) int V; \
    MODERNLIB_ALWAYS_INLINE inline \
    auto void F(int*)

#endif

#if defined(__cplusplus)

template<typename T>
struct __df_st  : T {
    MODERNLIB_ALWAYS_INLINE
    inline __df_st(T g) : T(g) { }
    MODERNLIB_ALWAYS_INLINE
    inline ~__df_st() 
    {
      T::operator()();
    }
};
 
#define cpp_defer __CPP_DEFER(__COUNTER__)
#define __CPP_DEFER(N) __CPP_DEFER_(N)
#define __CPP_DEFER_(N) __CPP_DEFER__(__DEFER_VARIABLE_ ## N)
#define __CPP_DEFER__(V)  __df_st const V = [&](void)->void

#endif

#if defined(cpp_defer)
    #define defer_stmt cpp_defer
#elif defined(gnu_defer)
    #define defer_stmt gnu_defer
#endif

#endif // MODERNLIB_RESMGMT_H_
