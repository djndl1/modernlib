#include "modernlib/internal/compilers.h"

#if defined (MODERNLIB_WINDOWS_TARGET)
#include <windows.h>
    #define timegm _mkgmtime
    #define localtime_r(a, b) (localtime_s(b, a))
    #define gmtime_r(a, b) (gmtime_s(b, a))

#else
    #define _DEFAULT_SOURCE 1
    #define _GNU_SOURCE 1
    #include <time.h>
    #define _XOPEN_SOURCE 700
    #include <unistd.h>
#endif

#if defined(__ANDROID__)  && __ANDROID_API__ < 29
    #define timespec_get(ts, base) clock_gettime(CLOCK_REALTIME, ts)
#endif

#include <time.h>
#include "modernlib/datetime.h"
#include "modernlib/timespan.h"

static int64_t local_offset_seconds_from_utc();

datetime datetime_from_tm(struct tm t, bool local)
{
    if (!local) {
        time_t timestamp = timegm(&t);
        return datetime_from_unix_seconds(timestamp);
    }

    int64_t offset = local_offset_seconds_from_utc();
    time_t timestamp = mktime(&t);
    datetime dt = datetime_from_unix_seconds(timestamp);
    dt.offset_from_utc = TIMESPAN_SECOND(offset);

    return dt;
}

struct tm datetime_to_tm(datetime self, bool localtm)
{
    time_t unix_seconds = datetime_to_unix_seconds(self);

    struct tm tm = { 0 };
    if (localtm) {
        localtime_r(&unix_seconds, &tm);
    } else {
        gmtime_r(&unix_seconds, &tm);
    }
    return tm;
}

static const int64_t UNIX_EPOCH_MICROSECONDS_SINCE_OLE_EPOCH = 2209161600000000LL;
static const int64_t MICROSECONDS_PER_DAY = 86400000000LL;

datetime datetime_from_ole_date(double oledate)
{
    int64_t micros = (int64_t)(oledate * MICROSECONDS_PER_DAY + (oledate >= 0 ? 0.5 : -0.5)); // simply to avoid conversion error
    if (micros < 0) {
        micros -= (micros % MICROSECONDS_PER_DAY) * 2;
    }
    micros -= UNIX_EPOCH_MICROSECONDS_SINCE_OLE_EPOCH;

    // this unix timestamp is local
    datetime dt = datetime_from_unix_microseconds(micros);
    dt.offset_from_utc = TIMESPAN_SECOND(local_offset_seconds_from_utc());
    return dt;
}

double datetime_to_ole_date(datetime self)
{
    int64_t unix_micros = datetime_to_unix_microseconds(self);
    int64_t ole_micros = unix_micros + UNIX_EPOCH_MICROSECONDS_SINCE_OLE_EPOCH;
    if (ole_micros < 0) {
        int64_t frac_part = ole_micros % MICROSECONDS_PER_DAY;
        // A, B (Integral, Fractional)
        // ole_macros = A + B
        // (A - 1) + (1 - B) = (A + B) - 2 - 2*B
        if (frac_part != 0) ole_micros -= (frac_part + MICROSECONDS_PER_DAY) * 2;
    }

    return (double)ole_micros / MICROSECONDS_PER_DAY;
}

#ifdef MODERNLIB_WINDOWS_TARGET

#define WINNT_TICKS_PER_SECOND 10000000UL
#define UNIX_EPOCH_IN_WINNT_EPOCH 11644473600LL

datetime datetime_from_winnt_filetime(FILETIME ft, bool local)
{
    ULARGE_INTEGER ftint = {
        .u.LowPart = ft.dwLowDateTime,
        .u.HighPart = ft.dwHighDateTime,
    };
    int64_t second_part_in_nt_epoch = ftint.QuadPart / WINNT_TICKS_PER_SECOND;
    int64_t second_part_in_unix_epoch = second_part_in_nt_epoch - UNIX_EPOCH_IN_WINNT_EPOCH;
    int64_t nanoseconds_part = (ftint.QuadPart % WINNT_TICKS_PER_SECOND) * 100;

    struct timespec tsp = {
        .tv_sec = second_part_in_unix_epoch,
        .tv_nsec = nanoseconds_part,
    };
    datetime dt = { 0 };
    dt._c11time = tsp;
    dt.offset_from_utc = local ? TIMESPAN_SECOND(local_offset_seconds_from_utc())
                               : TIMESPAN_ZERO;
    return dt;
}

FILETIME datetime_to_winnt_filetime(datetime dt)
{
    ULARGE_INTEGER ftint = { 0 };
    ftint.QuadPart = (((int64_t)dt._c11time.tv_sec) + UNIX_EPOCH_IN_WINNT_EPOCH) * WINNT_TICKS_PER_SECOND      // second part as ticks
        + ((int64_t)dt._c11time.tv_nsec) / 100 // nanosecond part as ticks
        + timespan_ticks(dt.offset_from_utc); // offset as ticks

    FILETIME ft = {
        .dwLowDateTime = ftint.u.LowPart,
        .dwHighDateTime = ftint.u.HighPart,
    };

    return ft;
}

SYSTEMTIME datetime_to_winnt_systemtime(datetime self)
{
    FILETIME ft = datetime_to_winnt_filetime(self);
    SYSTEMTIME st = { 0 };
    FileTimeToSystemTime(&ft, &st);
    return st;
}
#endif

static struct timespec get_utcnow(void)
{
    struct timespec ts = { 0 };
    timespec_get(&ts, TIME_UTC);

    return ts;
}

datetime datetime_utc_now(void)
{
    struct timespec ts = get_utcnow();

    return datetime_from_timespec(ts);
}

#include <stdio.h>

static int64_t local_offset_seconds_from_utc()
{
    int64_t diff;
#if defined(MODERNLIB_WINDOWS_TARGET)
    TIME_ZONE_INFORMATION tzinfo = { 0 };
    GetTimeZoneInformation(&tzinfo);
    diff = 60 * -tzinfo.Bias;
#else
    struct tm brokendown = { 0 };
    time_t seconds = 0;
    #if defined(__GLIBC__)  || defined(__ANDROID__) || defined(_GNU_SOURCE)
        localtime_r(&seconds, &brokendown);
        diff = brokendown.tm_gmtoff;
    #else
        localtime_r(&seconds, &brokendown);
        time_t now_seconds = timegm(&brokendown);
        diff = now_seconds - seconds;
    #endif
#endif
    return diff;
}

datetime datetime_now(void)
{
    datetime utcnow = datetime_utc_now();

    time_t seconds = utcnow._c11time.tv_sec;

    int64_t diff = local_offset_seconds_from_utc();
    time_t now_seconds = seconds + diff;

    utcnow._c11time.tv_sec = now_seconds;
    utcnow.offset_from_utc = TIMESPAN_SECOND(diff);
    return utcnow;
}
