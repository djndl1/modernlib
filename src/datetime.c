#include "modernlib/internal/compilers.h"

#if defined (MODERNLIB_WINDOWS_TARGET)
#include <windows.h>
    #define timegm _mkgmtime
    #define localtime_r(a, b) (localtime_s(b, a))

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

#include "modernlib/datetime.h"

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
