#include "utest.h"
#include <modernlib/datetime.h>

UTEST(DATETIME, NOW) {
    datetime now = datetime_now();

    fprintf(stdout, "%d, offset from utc %lf seconds", 
            now._c11time.tv_sec,
            timespan_as_seconds(now.offset_from_utc));
}

UTEST_MAIN();
