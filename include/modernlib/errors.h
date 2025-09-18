#ifndef MODERNLIB_ERRORS_H_
#define MODERNLIB_ERRORS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>

#define EOVERLAPMEM 10001
#define EINVALIDOP 10002

#define E_OVERLAPPING_MEMORY ERR_FROM_CODE(EOVERLAPMEM)
#define E_INVALID_OPERATION ERR_FROM_CODE(EINVALIDOP)
#define E_INVALID_ARGS ERR_FROM_CODE(EINVAL)
#define E_OUT_OF_RANGE ERR_FROM_CODE(ERANGE)

#ifdef __cplusplus
}
#endif

#endif // ERRORS_H_
