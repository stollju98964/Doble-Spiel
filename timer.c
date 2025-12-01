#include "timer.h"

#if __APPLE__
#include <sys/time.h>
static struct timespec start = {0, 0};

// Starts the timer.
void startTimer()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}

// Returns the time in seconds since startTimer() was called.
double stopTimer()
{
    struct timespec end;
    
    clock_gettime(CLOCK_MONOTONIC, &end);

    unsigned long long delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

    double measuredSeconds = (double)delta_us / 1000000.;

    if(start.tv_nsec > 0) {
        start.tv_nsec = 0;
        start.tv_sec = 0;
    }
    else
        measuredSeconds = -1;

    return measuredSeconds;
}
#else
#include <time.h>
static clock_t startClocks = 0;

// Starts the timer.
void startTimer()
{
    startClocks = clock();
}

// Returns the time in seconds since startTimer() was called.
double stopTimer()
{
    double measuredSeconds = (clock() - (double)startClocks) / CLOCKS_PER_SEC;

    if(startClocks > 0)
        startClocks = 0;
    else
        measuredSeconds = -1;

    return measuredSeconds;
}
#endif