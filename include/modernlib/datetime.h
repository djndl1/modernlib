#ifndef MODERNLIB_DATETIME_H_
#define MODERNLIB_DATETIME_H_ 

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include "modernlib/basis.h"
#include "modernlib/timespan.h"

typedef struct datetime {
    struct timespec _c11time;
    timespan offset_from_utc;
} datetime;

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_timespec(const struct timespec timestamp)
{
    datetime dt = { 0 };
    dt._c11time = timestamp;
    dt.offset_from_utc = TIMESPAN_ZERO;
    return dt;
}

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_unix_seconds(time_t seconds)
{
    datetime dt = { 0 };
    dt._c11time.tv_sec = seconds;
    dt._c11time.tv_nsec = 0;
    dt.offset_from_utc = TIMESPAN_ZERO;

    return dt;
}

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_unix_milliseconds(long milliseconds)
{
    struct timespec ts = { 0 };
    ts.tv_sec = milliseconds / 1000;  
    ts.tv_nsec = (milliseconds % 1000) * 1000;

    return datetime_from_timespec(ts);
}

MODERNLIB_PUBLIC
datetime datetime_utc_now(void);

MODERNLIB_PUBLIC
datetime datetime_now(void);

#ifdef __cplusplus
}
#endif

#endif /* ifndef MODERNLIB_DATETIME_H_ */
