#ifndef MODERNLIB_TIMESPAN_H_
#define MODERNLIB_TIMESPAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include "modernlib/internal/compilers.h"

#ifdef _MSC_VER
#include <winsock.h>
#endif

typedef struct timespan {
    int64_t _ticks;
} timespan;

#define TS_TICK_RESOLUTION 100
#define TS_TICKS_PER_MICROSECOND 10
#define TS_TICKS_PER_MILLISECOND (10 * TS_TICKS_PER_MICROSECOND)
#define TS_TICKS_PER_SECOND (1000UL * TS_TICKS_PER_MILLISECOND)
#define TS_TICKS_PER_MINUTE (60UL * TS_TICKS_PER_SECOND)
#define TS_TICKS_PER_HOUR (60UL * TS_TICKS_PER_MINUTE)
#define TS_TICKS_PER_DAY (24UL * TS_TICKS_PER_HOUR)

#ifdef __cplusplus
#  define TIMESPAN_TICK(tick) timespan{ tick }
#else
#  define TIMESPAN_TICK(tick) ((timespan){ ._ticks = tick })
#endif

#define TIMESPAN_ZERO TIMESPAN_TICK(0)
#define TIMESPAN_MIN TIMESPAN_TICK(INT64_MAX)
#define TIMESPAN_MAX TIMESPAN_TICK(INT64_MIN)
#define TIMESPAN_SECOND(n) timespan_from_ticks(n * TS_TICKS_PER_SECOND)
#define TIMESPAN_MINUTE(n) timespan_from_ticks(n * TS_TICKS_PER_MINUTE)
#define TIMESPAN_HOUR(n) timespan_from_ticks(n * TS_TICKS_PER_HOUR)
#define TIMESPAN_DAY(n) timespan_from_ticks(n * TS_TICKS_PER_DAY)
#define TIMESPAN(d, h, m, secs, msecs, usecs) _timespan_from(d, h, m, secs, msecs, usecs)

MODERNLIB_ALWAYS_INLINE
static inline timespan _timespan_from(int d, int h, int m, int64_t secs, int64_t msecs, int64_t usecs)
{
    int64_t dticks = TS_TICKS_PER_DAY * (int64_t)d;
    int64_t hticks = TS_TICKS_PER_HOUR * (int64_t)h;
    int64_t mticks = TS_TICKS_PER_MINUTE * (int64_t)m;
    int64_t secsticks = TS_TICKS_PER_SECOND * (int64_t)secs;
    int64_t msecsticks = TS_TICKS_PER_MILLISECOND * (int64_t)msecs;
    int64_t usecsticks = TS_TICKS_PER_MICROSECOND * (int64_t)usecs;

    int64_t ticks = dticks + hticks + mticks + secsticks + msecsticks + usecsticks;

    return TIMESPAN_TICK(ticks);
}

MODERNLIB_ALWAYS_INLINE
static inline timespan timespan_from_ticks(int64_t ticks)
{
    return TIMESPAN_TICK(ticks);
}

MODERNLIB_ALWAYS_INLINE
static inline timespan timespan_add(const timespan self, const timespan b)
{
    return TIMESPAN_TICK(self._ticks + b._ticks);
}

MODERNLIB_ALWAYS_INLINE
static inline timespan timespan_minus(const timespan self, const timespan b)
{
    return TIMESPAN_TICK(self._ticks - b._ticks);
}

MODERNLIB_ALWAYS_INLINE
static inline timespan timespanimes(const timespan self, double factor)
{
    return TIMESPAN_TICK(self._ticks * factor);
}

MODERNLIB_ALWAYS_INLINE
static inline timespan timespan_divided_by(const timespan self, double factor)
{
    return TIMESPAN_TICK((double)self._ticks / factor );
}

MODERNLIB_ALWAYS_INLINE
static inline timespan timespan_negative(const timespan self)
{
    return TIMESPAN_TICK(-self._ticks);
}

MODERNLIB_ALWAYS_INLINE
static inline int timespan_compare(const timespan self, const timespan other)
{
    return self._ticks == other._ticks ? 0
        : (self._ticks < other._ticks ? -1 : 1);
}

MODERNLIB_ALWAYS_INLINE
static inline int64_t timespan_ticks(const timespan ts)
{
    return ts._ticks;
}

MODERNLIB_ALWAYS_INLINE
static inline int timespan_day_part(const timespan ts)
{
    return ts._ticks / TS_TICKS_PER_DAY;
}

MODERNLIB_ALWAYS_INLINE
static inline int timespan_hour_part(const timespan ts)
{
    return (ts._ticks % TS_TICKS_PER_DAY) / TS_TICKS_PER_HOUR;
}

MODERNLIB_ALWAYS_INLINE
static inline int timespan_minute_part(const timespan ts)
{
    return (ts._ticks % TS_TICKS_PER_HOUR) / TS_TICKS_PER_MINUTE;
}

MODERNLIB_ALWAYS_INLINE
static inline int timespan_second_part(const timespan ts)
{
    return (ts._ticks % TS_TICKS_PER_MINUTE) / TS_TICKS_PER_SECOND;
}

MODERNLIB_ALWAYS_INLINE
static inline int timespan_millisecond_part(const timespan ts)
{
    return (ts._ticks % TS_TICKS_PER_SECOND) / TS_TICKS_PER_MILLISECOND;
}

MODERNLIB_ALWAYS_INLINE
static inline int timespan_microsecond_part(const timespan ts)
{
    return (ts._ticks % TS_TICKS_PER_MILLISECOND) / TS_TICKS_PER_MICROSECOND;
}

MODERNLIB_ALWAYS_INLINE
static inline timespan timespan_duration(const timespan ts)
{
    return TIMESPAN_TICK(imaxabs(ts._ticks));
}

MODERNLIB_ALWAYS_INLINE
static inline double timespan_as_microseconds(const timespan ts)
{
    return (double)ts._ticks / TS_TICKS_PER_MICROSECOND;
}

MODERNLIB_ALWAYS_INLINE
static inline double timespan_as_milliseconds(const timespan ts)
{
    return (double)ts._ticks / TS_TICKS_PER_MILLISECOND;
}

MODERNLIB_ALWAYS_INLINE
static inline double timespan_as_seconds(const timespan ts)
{
    return (double)ts._ticks / TS_TICKS_PER_SECOND;
}

MODERNLIB_ALWAYS_INLINE
static inline double timespan_as_nanoseconds(const timespan ts)
{
    return (double)ts._ticks * TS_TICK_RESOLUTION;
}

MODERNLIB_ALWAYS_INLINE
static inline struct timespec timespan_as_timespec(const timespan ts)
{
    time_t secs = ts._ticks / TS_TICKS_PER_SECOND;
    unsigned long nsecs = (ts._ticks % TS_TICKS_PER_SECOND) * TS_TICK_RESOLUTION;
    struct timespec tsp;
    tsp.tv_sec = secs;
    tsp.tv_nsec = nsecs;
    return tsp;
}

MODERNLIB_ALWAYS_INLINE
static inline clock_t timespan_as_clock(const timespan ts)
{
    return CLOCKS_PER_SEC * timespan_as_seconds(ts);
}

MODERNLIB_ALWAYS_INLINE
static inline struct timeval timespan_as_timeval(const timespan ts)
{
    time_t secs = ts._ticks / TS_TICKS_PER_SECOND;
    unsigned long usecs = (ts._ticks % TS_TICKS_PER_SECOND) / TS_TICKS_PER_MICROSECOND;
    struct timeval tv;
    tv.tv_sec = secs;
    tv.tv_usec = usecs;
    return tv;
}

// TODO format, parsing


#ifdef __cplusplus
}
#endif

#endif // TIMESPAN_H_
