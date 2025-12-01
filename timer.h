#ifndef TIMER_H
#define TIMER_H

// Usage of time.h: clock() returns the number of clock ticks since program start. CLOCKS_PER_SECONDS represents the
// number of clock ticks per second.

// Starts the timer.
void startTimer();

// Returns the time in seconds since startTimer() was called.
double stopTimer();

#endif
