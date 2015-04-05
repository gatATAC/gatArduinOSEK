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
 
 
/***** Project configuration include (before OSEK includes to allow OSEK configuration ******/
#include "prj_cfg.h"
 
/***** gatArduinOSEK includes *****/
/*** Types ***/
#include <gttc_types.h>
/*** Timer ***/
//#define TIMEBASE_USE_MS 1  // <-- Normally the timer unit is the us (microseconds) but you can use this define to use ms (milliseconds)
#include <gttc_timer.h>

/* ---------------------------------------*/

/***** Project includes *****/
#include "prj_pinout.h" // <-- The pinout of the project
#include "prj_dre.h"    // <-- The DRE of the project (global variables pools to share)
#include "prj_input.h"  // <-- The input module reads the microcontroller pinout
#include "prj_output.h"  // <-- The output module writes the microcontroller pinout

/**** Serial console ****/
/*** Command parse ***/
#include "prj_tty_cmds.h"
/*** Status broadcast ***/
#include "prj_tty_brcast.h"

#ifdef CFG_USE_TM1638
#include <TM1638.h>

// define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(11, 2, 12);
#endif

#ifdef CFG_USE_I2C
#include <Wire.h>
#define SLAVE_ADDRESS 0x04
#endif

#ifdef CFG_USE_LCD
  #include <LiquidCrystal.h>
  #include "prj_lcd.h"
#endif


/* ---------------------------------------*/

/***** Setup & Startup functions *****/

void setup() {
  timerSetCycleTime(CYCLE_TIME_IN_MICROS);
  dreInit();
  prjInputInit();
  prjOutputInit();
#ifndef CFG_USE_I2C  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
#else  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveI2cData);
  Wire.onRequest(sendI2cData);
#endif

#ifdef CFG_USE_LCD
  prj_lcd_setup();
#endif
}

/* ---------------------------------------*/

/***** Main Loop *****/

void loop()
{
  // ----------- Functionality ----------------

  prjInput();

#ifndef CFG_USE_I2C  
  // Button statuses broadcast through serial console
  buttonBroadcast();

  // Serial console commands handling (see prj_tty_cmds.h for protocol and functionality)
  // We will try to read and parse 3 times on each loop, so as to allow at least 3 characters (a command) if they come separately
  ttyCmdHandle(3);
#endif

#ifdef CFG_USE_LCD
  prj_lcd_process();
#endif

  prjOutput();

  // ----------- End of Cycle Synchronization ----------------

  // Now the microcontroller will loose time until the end of cycle sincronization time expires
  boolean timSync=timerSync();
  while(timSync==false){
    if ((CYCLE_TIME_MICROS-elapsedMicros)>CYCLE_SECURITY_TIME_MICROS){


#ifndef CFG_USE_I2C  
      /* As the remaining time is bigger than a secure quantity, we will try to perform a serial console parsing action, in order to reduce the answering time. */
      /* This security time must be set depending on the project (and depending of the worst case expected time for this command parsing action).  The quantity is part of the project
       configuration, not part of the OSEK configuration.  In this case it is part of the prj_tty_cmd.h file */
      ttyCmdHandle(1);      
#endif
    }
    // timerSync returns true when the end of cycle syncronization time expired.
    timSync=timerSync();
  }
}










