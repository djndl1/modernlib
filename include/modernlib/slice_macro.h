#ifndef MODERNLIB_SLICE_MACRO_H_
#define MODERNLIB_SLICE_MACRO_H_

#define slice_typename(elm_type) CONCAT(elm_type, CONCAT(_, slice))

#ifdef __cplusplus
    #define make_slice(elm_type, start, count) (slice_typename(elm_type) { start, count })

    #define make_slice_from(elm_type, array)(slice_typename(elm_type) \
            {                                                           \
                array,                 \
                countof(array) \
            })
#else
    #define make_slice(elm_type, start, count) ((slice_typename(elm_type)) { start, count })

    #define make_slice_from(elm_type, arr)((slice_typename(elm_type)) \
            {                                                           \
                .start = arr,                 \
                .count = countof(arr) \
            })
#endif

#endif /* ifndef MODERNLIB_SLICE_MACRO_H_


 */
