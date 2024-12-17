#ifndef UTIL_H_
#define UTIL_H_

#include "nullptr.h"

typedef struct {
    int error;
} error_t;

#define ERR_FROM_CODE(e) ((error_t) { .error = e })
#define E_OK ERR_FROM_CODE(0)

#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define TOKENIZE(t) #t
#define _CONCAT(a, b) a##b
#define CONCAT(a, b) _CONCAT(a, b)
#define INTERNAL_VAR(v) CONCAT(v, __LINE__)

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

#endif // UTIL_H_
