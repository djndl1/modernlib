#if !defined(clamp_funcname)
#error "clamp function name not defined!"
#endif
#if !defined(clamp_typename)
#error "clamp's type name not defined!"
#endif

MODERNLIB_ALWAYS_INLINE
static inline
clamp_typename
#ifdef __cplusplus
clamp
#else
clamp_funcname
#endif
(clamp_typename value, clamp_typename min, clamp_typename max)
{
    auto max_clamped = value > max ? max : value;
    return max_clamped < min ? min : max_clamped;
}


#undef clamp_funcname
#undef clamp_typename
