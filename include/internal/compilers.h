#ifndef _COMPILERS_H_
#define _COMPILERS_H_

#ifdef __GNUC__
#define MODERNLIB_ALWAYS_INLINE __attribute__ ((always_inline))
#elif _MSC_VER
#define MODERNLIB_ALWAYS_INLINE __forceinline
#else
#define MODERNLIB_ALWAYS_INLINE
#endif

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW32__)
#  if defined(MODERNLIB_SHARED_BUILD)
#     define MODERNLIB_PUBLIC declspec(dllexport)
#  elif defined(MODERNLIB_STATIC_BUILD)
#     define MODERNLIB_PUBLIC
#  else
#     define MODERNLIB_PUBLIC declspec(dllimport)
#  endif
#elif defined(__GNUC__)
#  define MODERNLIB_PUBLIC __attribute__((visibility("default")))
#else
#  define MODERNLIB_PUBLIC
#endif

#endif // _COMPILERS_H_
