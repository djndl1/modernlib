#ifndef MODERNLIB_MACROS_H_
#define MODERNLIB_MACROS_H_
#include "modernlib/internal/compilers.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TOKENIZE(t) #t
#define _CONCAT(a, b) a##b
#define CONCAT(a, b) _CONCAT(a, b)
#define INTERNAL_VAR(v) CONCAT(v, __LINE__)

#ifdef __cplusplus
}
#endif

#endif // MODERNLIB_MACROS_H_
