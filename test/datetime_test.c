#include <modernlib/datetime.h>
#include <inttypes.h>
#include "utest.h"

UTEST(DATETIME, NOW) {
    datetime now = datetime_now();

    fprintf(stdout, "%"PRIu64", offset from utc %lf seconds\n", 
            (int64_t)now._c11time.tv_sec,
            timespan_as_seconds(now.offset_from_utc));
}

UTEST_MAIN();
