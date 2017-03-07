/* -- Timing and timer functions -- */

#ifndef _GTTC_TIMER_H
#define _GTTC_TIMER_H

#include "gttc_types.h"

/* Cycle time if no timerSetCycleTime() used */
#define CYCLE_TIME_MICROS_DEFAULT 40000L

#define TIME_MICROS_MAX 4294967295L
#define TIME_MS_MAX 4294967295L

#define CALC_CYCLE_COUNT_FOR_TIME(x) ((x)/timerGetCycleTime())

/* ------------------------ Timer synchronization variables -------------------- */
#ifdef TIMEBASE_USE_MS
extern uint32_t previousMillis;     // Stores the milliseconds time stamp of the last timerSync, used to detect a timer overflow when computing the ellapsed time.
extern uint32_t currentMillis;    // Stores the milliseconds time stamp of the current timerSync, used to detect a timer overflow when computing the ellapsed time.
extern uint32_t elapsedMillis;    // Accumulates the milliseconds ellapsed since the last main loop cycle synchronization.  Used to know when the cycle time has expired.
#endif

extern uint32_t elapsedMicros;      // Stores the microseconds time stamp of the last timerSync, used to detect a timer overflow when computing the ellapsed time.
extern uint32_t previousMicros;     // Stores the microseconds time stamp of the current timerSync, used to detect a timer overflow when computing the ellapsed time.
extern uint32_t currentMicros;      // Accumulates the microseconds ellapsed since the last main loop cycle synchronization.  Used to know when the cycle time has expired.

/* ------------------------ Measurement variables -------------------- */
#ifdef TIMEBASE_USE_MS
extern uint32_t busyMillis;         // Stores the ellapsed time at the end of the functional part of the main loop cycle (to know how much time is dedicated to functionality).
#endif
extern uint32_t busyMicros;       // Stores the ellapsed time at the end of the functional part of the main loop cycle (to know how much time is dedicated to functionality).
extern uint32_t syncInvocations;    // This variable stores the number of timerSync() function invocations during the current main loop cycle.  It is a measure of the remaining free cycle time that is wasted in the timerSync loop at the end of the main loop.

/* ----------- Timer Synchronization function ------------------ */
/* This function is used to know if the main loop cycle time has expired or not */
#ifdef __cplusplus
extern "C" 
#endif
boolean timerSync(void);

#ifdef __cplusplus
extern "C" 
#endif
void timerSetCycleTime(uint32_t cycle_time);

#ifdef __cplusplus
extern "C" 
#endif
uint32_t timerGetCycleTime(void);

#endif // _GTTC_TIMER_H

