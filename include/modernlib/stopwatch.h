#ifndef MODERNLIB_STOPWATCH_H_
#define MODERNLIB_STOPWATCH_H_

#include "modernlib/timespan.h"
#include <time.h>
#include "modernlib/internal/compilers.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stopwatch {
    clock_t start;
    clock_t end;
} stopwatch;

MODERNLIB_PUBLIC
stopwatch stopwatch_new();

MODERNLIB_PUBLIC
void stopwatch_start(stopwatch *self);

MODERNLIB_PUBLIC
void stopwatch_stop(stopwatch *self);

MODERNLIB_PUBLIC
clock_t stopwatch_elapsed_clocks(const stopwatch self);

MODERNLIB_PUBLIC
timespan stopwatch_elapsed_time(const stopwatch self);

#ifdef __cplusplus
}
#endif


#endif // STOPWATCH_H_
