#ifndef MODERNLIB_DATETIME_H_
#define MODERNLIB_DATETIME_H_ 

#include "modernlib/internal/compilers.h"
#include "modernlib/basis.h"
#include "modernlib/timespan.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdint.h>

typedef struct datetime {
    struct timespec _c11time;
    timespan offset_from_utc;
} datetime;

MODERNLIB_ALWAYS_INLINE
static inline bool datetime_is_utc(datetime self);

MODERNLIB_PUBLIC
datetime datetime_utc_now(void);

MODERNLIB_PUBLIC
datetime datetime_now(void);


MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_timespec(struct timespec timestamp)
{
    datetime dt = { 0 };
    dt._c11time = timestamp;
    dt.offset_from_utc = TIMESPAN_ZERO;
    return dt;
}

MODERNLIB_ALWAYS_INLINE
static inline struct timespec datetime_to_timespec(datetime self)
{
    const int64_t NANOSECONDS_PER_SECOND = 1000000000L;
    struct timespec result = self._c11time;

    if (datetime_is_utc(self)) {
        return result;
    }

    int64_t offset_nanos = timespan_as_nanoseconds(self.offset_from_utc);

    int64_t offset_nano_part = offset_nanos % NANOSECONDS_PER_SECOND;

    int64_t nano_sum = offset_nano_part + result.tv_nsec;
    result.tv_sec += (offset_nanos / NANOSECONDS_PER_SECOND 
                        + nano_sum / NANOSECONDS_PER_SECOND);
    result.tv_nsec = nano_sum % NANOSECONDS_PER_SECOND;

    return result;
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
static inline time_t datetime_to_unix_seconds(datetime self)
{
    struct timespec tsp = datetime_to_timespec(self);
    return tsp.tv_sec;
}

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_unix_milliseconds(int64_t milliseconds)
{
    struct timespec ts = { 0 };
    ts.tv_sec = milliseconds / 1000;  
    ts.tv_nsec = (milliseconds % 1000) * 1000000;

    return datetime_from_timespec(ts);
}

MODERNLIB_ALWAYS_INLINE
static inline int64_t datetime_to_unix_milliseconds(datetime self)
{
    struct timespec tsp = datetime_to_timespec(self);
    return tsp.tv_sec * 1000 + tsp.tv_nsec / 1000000;
}

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from_unix_microseconds(int64_t microseconds)
{
    struct timespec ts = { 0 };
    ts.tv_sec = microseconds / 1000000;  
    ts.tv_nsec = (microseconds % 1000000) * 1000;

    return datetime_from_timespec(ts);
}

MODERNLIB_ALWAYS_INLINE
static inline int64_t datetime_to_unix_microseconds(datetime self)
{
    struct timespec tsp = datetime_to_timespec(self);
    return tsp.tv_sec * 1000000 + tsp.tv_nsec / 1000;
}

MODERNLIB_PUBLIC
datetime datetime_from_tm(struct tm t, bool local);

MODERNLIB_PUBLIC
struct tm datetime_to_tm(datetime self, bool localtm);

MODERNLIB_ALWAYS_INLINE
static inline datetime datetime_from(int year, int month, int day, int hour, int minute, int second, int millisecond, bool local)
{
    struct tm broken_down = { 0 };
    broken_down.tm_year = year;
    broken_down.tm_mon = month;
    broken_down.tm_mday = day;
    broken_down.tm_hour = hour;
    broken_down.tm_min = minute;
    broken_down.tm_sec = second;
    datetime dt = datetime_from_tm(broken_down, local);
    dt._c11time.tv_nsec = millisecond * 1000000;

    return dt;
}

MODERNLIB_PUBLIC
datetime datetime_from_ole_date(double oledate);

MODERNLIB_PUBLIC
double datetime_to_ole_date(datetime self);

#ifdef MODERNLIB_WINDOWS_TARGET
#include <windows.h>

MODERNLIB_PUBLIC
datetime datetime_from_winnt_filetime(FILETIME ft, bool local);

MODERNLIB_PUBLIC
FILETIME datetime_to_winnt_filetime(const datetime dt);


MODERNLIB_ALWAYS_INLINE
static inline
datetime datetime_from_winnt_systemtime(SYSTEMTIME st, bool local)
{
    return datetime_from(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, local);
}

MODERNLIB_PUBLIC
SYSTEMTIME datetime_to_winnt_systemtime(datetime self);

#endif

MODERNLIB_ALWAYS_INLINE
static inline bool datetime_is_utc(datetime self)
{
    return timespan_ticks(self.offset_from_utc) == 0;
}

#ifdef __cplusplus
}
#endif

#endif /* ifndef MODERNLIB_DATETIME_H_ */
