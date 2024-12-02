#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "timespan.h"
#include <time.h>

typedef struct {
    clock_t start;
    clock_t end;
} stopwatch_t;

stopwatch_t stopwatch_new();

void stopwatch_start(stopwatch_t *self);

void stopwatch_stop(stopwatch_t *self);

clock_t stopwatch_elapsed_clocks(const stopwatch_t self);

timespan_t stopwatch_elapsed_time(const stopwatch_t self);

#endif // STOPWATCH_H_
