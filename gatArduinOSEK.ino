/* --------- This file is an example of a main file in an Arduino project -----------------------------
 -- Additional files with gttc_ prefix are the gatArduinOSEK files, not to be modified in normal use -- 
 -- Additional files with prj_ prefix are the ones that must be configured for each project, they    -- 
 -- are part of the example.                                                                         -- 
 -- Project Functionality:
 -- This project uses 4 buttons and 4 leds and the serial port of the arduino.
 -- Buttons are read and the statuses are sent through the serial console.
 -- The user can send commands through the serial console to light the leds.
 -- Buttons and leds are connected to pins configured in prj_pinout.h
 -- Global variables of the project are shared through a DRE (Data Runtime Environment) defined in prj_dre.h and prj_dre.c
 -- The serial console commands are processed in prj_tty_cmds.h and prj_tty_cmds.c
 -- The serial console broadcast of the input statuses is done in prj_tty_brcast.h and prj_tty_brcast.c
 -- Please visit the wiki page for this project in http://gatatac.org/projects/gttcosarduino/wiki/GatArduinOSEKino_example_1


/***** gatArduinOSEK includes *****/
/*** Types ***/
#include "gttc_types.h"
/*** Timer ***/
//#define TIMEBASE_USE_MS 1  // <-- Normally the timer unit is the us (microseconds) but you can use this define to use ms (milliseconds)
#include "gttc_timer.h"

/* ---------------------------------------*/

/***** Project configuration includes *****/
#include "prj_pinout.h" // <-- The pinout of the project
#include "prj_dre.h"    // <-- The DRE of the project (global variables pools to share)
#include "prj_input.h"  // <-- The input module reads the microcontroller pinout
#include "prj_output.h"  // <-- The output module writes the microcontroller pinout

/**** Serial console ****/
/*** Command parse ***/
#include "prj_tty_cmds.h"
/*** Status broadcast ***/
#include "prj_tty_brcast.h"

/* ---------------------------------------*/

/***** Setup & Startup functions *****/

void setup() {
  dreInit();
  prjInputInit();
  prjOutputInit();
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);    
}

/* ---------------------------------------*/

/***** Main Loop *****/

void loop()
{
  
  // ----------- Functionality ----------------
  
  prjInput();

  // Button statuses broadcast through serial console
  buttonBroadcast();

 // Serial console commands handling (see prj_tty_cmds.h for protocol and functionality)
  // We will try to read and parse 3 times on each loop, so as to allow at least 3 characters (a command) if they come separately
  ttyCmdHandle(3);
  
  prjOutput();
  
  // ----------- End of Cycle Synchronization ----------------
  
  // Now the microcontroller will loose time until the end of cycle sincronization time expires
  boolean timSync=timerSync();
  while(timSync==false){
    if ((CYCLE_TIME_MICROS-busyMicros)>CYCLE_SECURITY_TIME_MICROS){
      
      
      /* As the remaining time is bigger than a secure quantity, we will try to perform a serial console parsing action, in order to reduce the answering time. */
      /* This security time must be set depending on the project (and depending of the worst case expected time for this command parsing action).  The quantity is part of the project
         configuration, not part of the OSEK configuration.  In this case it is part of the prj_tty_cmd.h file */
      ttyCmdHandle(1);      
    }
    // timerSync returns true when the end of cycle syncronization time expired.
    timSync=timerSync();
  }
}







