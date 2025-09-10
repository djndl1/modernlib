#include "modernlib/datetime.h"

#if defined(__MINGW64__) || defined(__MINGW32__) || defined (_MSC_VER)
#include <windows.h>

    #define timegm _mkgmtime
    #define localtime_s(a, b) (localtime_s(b, a))
    #define gmtime_s(a, b) (gmtime_s(b, a))
    #define sleep(s) (Sleep)(s * 1000)
#elif defined(__STDC_LIB_EXT1__)
    #define __STDC_WANT_LIB_EXT1__ 1
#else
#define _XOPEN_SOURCE 700
#include <unistd.h>

    #define localtime_s(a, b) (localtime_r(a, b))
    #define gmtime_s(a, b) (gmtime_r(a, b))
#endif

#if defined(__ANDROID__)  && __ANDROID_API__ < 29
    #define timespec_get(ts, base) clock_gettime(CLOCK_REALTIME, ts)
#endif

#include <time.h>

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
    localtime_s(&seconds, &brokendown);
    time_t now_seconds = timegm(&brokendown);

    utcnow._c11time.tv_sec = now_seconds;
    utcnow.offset_from_utc = TIMESPAN_SECOND(now_seconds - seconds);
    return utcnow;
}
