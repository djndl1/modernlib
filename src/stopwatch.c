#include "stopwatch.h"

#include <time.h>

stopwatch stopwatch_new()
{
    stopwatch sw = { -1, -1 };

    return sw;
}

void stopwatch_start(stopwatch *self)
{
    self->start = clock();
}

void stopwatch_stop(stopwatch *self)
{
    self->end = clock();
}

clock_t stopwatch_elapsed_clocks(const stopwatch self)
{
    if (self.end == -1) {
        return 0;
    }
    return self.end - self.start;
}

timespan stopwatch_elapsed_time(const stopwatch self)
{
    clock_t clocks = stopwatch_elapsed_clocks(self);
    double secs = ((double)clocks) / CLOCKS_PER_SEC;
    return TIMESPAN_SECOND(secs);
}
