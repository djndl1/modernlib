#include "stopwatch.h"

#include <time.h>

stopwatch_t stopwatch_new()
{
    stopwatch_t sw = { -1, -1 };

    return sw;
}

void stopwatch_start(stopwatch_t *self)
{
    self->start = clock();
}

void stopwatch_stop(stopwatch_t *self)
{
    self->end = clock();
}

clock_t stopwatch_elapsed_clocks(const stopwatch_t self)
{
    if (self.end == -1) {
        return 0;
    }
    return self.end - self.start;
}

timespan_t stopwatch_elapsed_time(const stopwatch_t self)
{
    clock_t clocks = stopwatch_elapsed_clocks(self);
    double secs = ((double)clocks) / CLOCKS_PER_SEC;
    return TIMESPAN_SECOND(secs);
}
