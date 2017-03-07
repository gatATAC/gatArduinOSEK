/* -- Timing and timer functions -- */

#include "gttc_timer.h"
#include "Arduino.h"

// See http://coverclock.blogspot.com.es/2012/02/arduino-data-types.html


/* As part of the project configuration, in some prj_*.h file or in the main project file, the user can define TIMEBASE_USE_MS constant, in order to use milliseconds as timing unit instead of microseconds */

/* ------------------------ Timer synchronization variables -------------------- */
#ifdef TIMEBASE_USE_MS
uint32_t previousMillis=0L;     // Stores the milliseconds time stamp of the last timerSync, used to detect a timer overflow when computing the ellapsed time.
uint32_t currentMillis = 0L;    // Stores the milliseconds time stamp of the current timerSync, used to detect a timer overflow when computing the ellapsed time.
uint32_t elapsedMillis = 0L;    // Accumulates the milliseconds ellapsed since the last main loop cycle synchronization.  Used to know when the cycle time has expired.
#endif

uint32_t elapsedMicros=0L;      // Stores the microseconds time stamp of the last timerSync, used to detect a timer overflow when computing the ellapsed time.
uint32_t previousMicros=0L;     // Stores the microseconds time stamp of the current timerSync, used to detect a timer overflow when computing the ellapsed time.
uint32_t currentMicros=0L;      // Accumulates the microseconds ellapsed since the last main loop cycle synchronization.  Used to know when the cycle time has expired.

/* ------------------------ Measurement variables -------------------- */
#ifdef TIMEBASE_USE_MS
uint32_t busyMillis=0L;         // Stores the ellapsed time at the end of the functional part of the main loop cycle (to know how much time is dedicated to functionality).
#endif
uint32_t busyMicros = 0L;       // Stores the ellapsed time at the end of the functional part of the main loop cycle (to know how much time is dedicated to functionality).
uint32_t syncInvocations=55L;    // This variable stores the number of timerSync() function invocations during the current main loop cycle.  It is a measure of the remaining free cycle time that is wasted in the timerSync loop at the end of the main loop.
boolean busyTimeStoreFlag=true;

uint32_t cycle_time_micros=CYCLE_TIME_MICROS_DEFAULT;

#ifdef GTTC_TIMER_USE_METRO
#include <Metro.h>

Metro sysTimer;
#endif

/* ----------- Timer Init functions -----------*/
void timerSetCycleTime(uint32_t cycle_time){
	cycle_time_micros=cycle_time;
#ifdef GTTC_TIMER_USE_METRO
sysTimer = Metro(cycle_time/1000);// milliseconds
sysTimer.reset();
#endif
}

uint32_t timerGetCycleTime(void){
	return cycle_time_micros;
}

/* ----------- Timer Synchronization function ------------------ */
/* This function is used to know if the main loop cycle time has expired or not */
boolean timerSync(void){
  boolean result=false;
  
  if (busyTimeStoreFlag==true){
    syncInvocations=1L;
    // This is the first time this function is invoked in current main loop cycle
    // Measurements to know how fast is our functionality handling and how much time is free to include new functionality
#ifdef TIMEBASE_USE_MS
    busyMillis=millis()-previousMillis;
#endif
    busyMicros=micros()-previousMicros;
    // As the busy measurement variables have been stored, we will not do it again until next main loop cycle is begun.
    busyTimeStoreFlag=false;
  } else {
  	syncInvocations++;          // Measurement variable increment
  }
#ifndef GTTC_TIMER_USE_METRO
  currentMicros = micros();   // Acquisition of the current microseconds time stamp of the system 
#ifdef TIMEBASE_USE_MS
  currentMillis = millis();
#endif

#ifdef TIMEBASE_USE_MS
  // Calculation of the ellapsedMillis syncronization variable
if (currentMillis<previousMillis){
    // Le hemos dado la vuelta al marcador
    elapsedMillis=(TIME_MS_MAX-previousMillis)+currentMillis;
  } 
  else {
    elapsedMillis=currentMillis-previousMillis;
  }
#endif

  // Calculation of the ellapsedMicros sincronization variable
  if (currentMicros<previousMicros){
    // Le hemos dado la vuelta ala marcador
    elapsedMicros=(TIME_MICROS_MAX-previousMicros)+currentMicros;
  } 
  else {
    elapsedMicros=currentMicros-previousMicros;
  }
#endif  
  // Time sync expiration time check
#ifdef GTTC_TIMER_USE_METRO
  if(sysTimer.check()){
#else
  if (elapsedMicros>=cycle_time_micros){
#endif
    result=true;  // Cycle time expired, result will be true

    // Store the current timestamps for calculating the next cycle time
#ifdef TIMEBASE_USE_MS
    previousMillis=millis();
#endif
    previousMicros=micros();
    
    // As a new cycle will be begin, force next invocation to store the measurement busy variables
    busyTimeStoreFlag=true;
  }
  
  return result;
}

