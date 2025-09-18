#ifndef MODERNLIB_NULLPTR_H_
#define MODERNLIB_NULLPTR_H_

#if __cplusplus 
		#if (__cplusplus < 201103L) && !defined(nullptr)
        #include <cstddef>
        #define nullptr NULL
		#endif
#else
		#if (__STDC_VERSION__ < 202311L) && !defined(nullptr)
        #include <stddef.h>
        #define nullptr NULL
		#endif
#endif

#endif // MODERNLIB_NULLPTR_H_
