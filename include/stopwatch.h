#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "timespan.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stopwatch {
    clock_t start;
    clock_t end;
} stopwatch;

stopwatch stopwatch_new();

void stopwatch_start(stopwatch *self);

void stopwatch_stop(stopwatch *self);

clock_t stopwatch_elapsed_clocks(const stopwatch self);

timespan stopwatch_elapsed_time(const stopwatch self);

#ifdef __cplusplus
}
#endif


#endif // STOPWATCH_H_
