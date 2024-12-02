/**
 * result_t(err, value)
 * In case of an error, only the err value may be retrieved reliably
 * otherwise, only the value is retrieved
 * the exact result is not permitted to be retrieved directly without first
 * checking whether there is an error
 */
#ifndef VARIANT_RESULT_H_
#define VARIANT_RESULT_H_

#include <stdbool.h>

#define scoped_stmt(...) do { __VA_ARGS__; } while (false)

#define _CONCAT(a, b) a##b
#define CONCAT(a, b) _CONCAT(a, b)

#define VARIANT_RESULT_INLINE __attribute__ ((always_inline))

#define result_is_ok(result) (!result._has_error)
#define result_or_else(result, alt) (result_is_ok(result) ? result._val : alt)

#define match_begin(result_typ, result)  {                              \
    result_typ __ca3ecda3_7219_428c_8ea3_cebaff20be9b = result; \

#define on_ok_begin(typ, val) {                                          \
    typ val = __ca3ecda3_7219_428c_8ea3_cebaff20be9b._val;           \
    if (result_is_ok(__ca3ecda3_7219_428c_8ea3_cebaff20be9b))

#define on_ok_end }

#define on_err_begin(typ, err) {                                    \
    typ err = __ca3ecda3_7219_428c_8ea3_cebaff20be9b._err;           \
    if (!result_is_ok(__ca3ecda3_7219_428c_8ea3_cebaff20be9b))
#define on_err_end }

#define match_end }


#endif // VARIANT_RESULT_H_

#if defined(variant_result_err_t) && defined(variant_result_val_t) \
  && defined(variant_result_name)

typedef struct {
    bool _has_error;

    union {
        variant_result_err_t _err;
        variant_result_val_t _val;
    };
} variant_result_name;

VARIANT_RESULT_INLINE
static inline variant_result_name CONCAT(variant_result_name, _ok)(variant_result_val_t val)
{
    return (variant_result_name) {
        ._has_error = false,
        ._val = val,
    };
}

VARIANT_RESULT_INLINE
static inline variant_result_name CONCAT(variant_result_name, _err)(variant_result_err_t err)
{
    return (variant_result_name) {
        ._has_error = true,
        ._err = err,
    };
}

#endif // variant_result parameters
#undef variant_result_err_t
#undef variant_result_val_t
#undef variant_result_name
