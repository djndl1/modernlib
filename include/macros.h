#ifndef MODERNLIB_MACROS_H_
#define MODERNLIB_MACROS_H_

#include <internal/compilers.h>

#if MODERLIB_USE_INLINE
#define MODERNLIB_INLINE ALWAYS_INLINE
#else
#define MODERNLIB_INLINE
#endif


#endif // MODERNLIB_MACROS_H_
