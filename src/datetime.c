#if defined(__MINGW64__) || defined(__MINGW32__) || defined (_MSC_VER)
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

datetime datetime_now(void)
{
    datetime utcnow = datetime_utc_now();

    time_t seconds = utcnow._c11time.tv_sec;

    struct tm brokendown = { 0 };
    localtime_r(&seconds, &brokendown);

    time_t now_seconds;
    long diff;
#if defined(__GLIBC__)  || defined(__ANDROID__) || defined(_GNU_SOURCE)
    diff = brokendown.tm_gmtoff;
    now_seconds = seconds + diff;
#else
    now_seconds = timegm(&brokendown);
    diff = now_seconds - seconds;
#endif

    utcnow._c11time.tv_sec = now_seconds;
    utcnow.offset_from_utc = TIMESPAN_SECOND(diff);
    return utcnow;
}
