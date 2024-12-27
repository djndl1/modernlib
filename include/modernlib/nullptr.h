#ifndef NULLPTR_H_
#define NULLPTR_H_

#if ((__cplusplus >= 201103L) || (__STDC_VERSION__ >= 202311L)) && defined(nullptr)
    #undef nullptr
#else
    #ifndef nullptr
        #include <stddef.h>
        #define nullptr NULL
    #endif
#endif

#endif // NULLPTR_H_
