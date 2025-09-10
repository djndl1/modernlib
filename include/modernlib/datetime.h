#ifndef MODERNLIB_DATETIME_H_
#define MODERNLIB_DATETIME_H_ value

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
    return (datetime){ ._c11time = timestamp, .offset_from_utc = TIMESPAN_ZERO };
}

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_unix_seconds(time_t seconds)
{
    datetime dt = {
        ._c11time = {
            .tv_sec = seconds,
            .tv_nsec = 0,
        },
        .offset_from_utc = TIMESPAN_ZERO,
    };

    return dt;
}

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_unix_milliseconds(long milliseconds)
{
    struct timespec ts = { 
        .tv_sec = milliseconds / 1000,  
        .tv_nsec = (milliseconds % 1000) * 1000,
    };

    return datetime_from_timespec(ts);
}

MODERNLIB_PUBLIC
datetime datetime_utc_now(void);

MODERNLIB_PUBLIC
datetime datetime_now(void);

#endif /* ifndef MODERNLIB_DATETIME_H_ */
