#ifndef MODERNLIB_COMPILERS_H_
#define MODERNLIB_COMPILERS_H_

#ifdef __GNUC__
#define MODERNLIB_ALWAYS_INLINE __attribute__ ((always_inline))
#elif _MSC_VER
#define MODERNLIB_ALWAYS_INLINE __forceinline
#else
#define MODERNLIB_ALWAYS_INLINE
#endif

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
#  if defined(MODERNLIB_SHARED_BUILD)
#     define MODERNLIB_PUBLIC __declspec(dllexport)
#  elif defined(MODERNLIB_STATIC_BUILD)
#     define MODERNLIB_PUBLIC
#  else
#     define MODERNLIB_PUBLIC __declspec(dllimport)
#  endif
#elif defined(__GNUC__)
#  define MODERNLIB_PUBLIC __attribute__((visibility("default")))
#else
#  define MODERNLIB_PUBLIC
#endif

#ifdef __cplusplus
#   if defined(__GNUC__)
#       define restrict __restrict__
#   elif defined (_MSC_VER)
#       define restrct __restrict
#   else
#       define restrict
#   endif
#endif

#endif // MODERNLIB_COMPILERS_H_
