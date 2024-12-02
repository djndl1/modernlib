#ifndef _COMPILERS_H_
#define _COMPILERS_H_

#ifdef __GNUC__
#define ALWAYS_INLINE __attribute__ ((always_inline))
#elif _MSC_VER
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE
#endif


#endif // _COMPILERS_H_
