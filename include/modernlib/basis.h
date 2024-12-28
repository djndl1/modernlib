#ifndef MODERNLIB_UTIL_H_
#define MODERNLIB_UTIL_H_

#include "modernlib/nullptr.h"
#include <stdint.h>
#include <stdbool.h>

#include "modernlib/resmgmt.h"
#include "modernlib/errors.h"

typedef struct {
    int error;
} error_t;

#ifdef __cplusplus
#  define ERR_FROM_CODE(e) (error_t{ e })
#else
#  define ERR_FROM_CODE(e) ((error_t) { .error = e })
#endif

#define E_OK ERR_FROM_CODE(0)

#define MIN(a, b) (((a) > (b)) ? (b) : (a))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif // UTIL_H_
