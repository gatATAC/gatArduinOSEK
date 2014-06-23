/* --- Serial console command parse module --- */
/* Each command is 3 char lenght:
 
 * l00 -> led 0 off
 * l01 -> led 0 on green
 * l02 -> led 0 on red*
 * l10 -> led 1 off
 * l11 -> led 1 on green
 * l12 -> led 1 on red*
 * l20 -> led 2 off
 * l21 -> led 2 on green
 * l22 -> led 2 on red*
 * l30 -> led 3 off
 * l31 -> led 3 on green
 * l32 -> led 3 on red*
 
 NOTE: TM1638 has two color leds (green, red).  For simple color direct leds the lx2 commands performs exactly like lx1 commands.
 
 */
#include "prj_cfg.h"
#include "prj_tty_cmds.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"

uint8_t ledToChange=0;

/** Auxiliary functions **/

void handle3rdCharForLed(uchar_t inByte){
  uint8_t value;
  
  value=inByte-'0';
  if (ledToChange>=0 && ledToChange<NUM_LEDS) {
    dre.ledState[ledToChange]=value;
  }
}

void handle2ndCharForLed(uchar_t inByte){
  ledToChange=inByte-'0';
}

/***** Finite State Machine *****/

/* Parsing states */
#define PARSING_COMMAND 0
#define PARSING_ARGUMENT1 1
#define PARSING_ARGUMENT2 2

#define COMMAND_IDLE 0
#define COMMAND_LED 1
#define COMMAND_MESSAGE 2

uchar_t parseState = PARSING_COMMAND;
uint8_t command=COMMAND_IDLE;
void ttyCmdParse(uchar_t charReceived){
  switch (parseState){
  case PARSING_COMMAND:
    switch (charReceived){
    case 'l':
      // Led command
      command=COMMAND_LED;
      break;
    default:
      command=COMMAND_IDLE;
      break;
    }
    parseState=PARSING_ARGUMENT1;
    break;
  case PARSING_ARGUMENT1:
    switch (command){
    case COMMAND_LED:
      // Led command
      handle2ndCharForLed(charReceived);
      break;
    }
    parseState=PARSING_ARGUMENT2;
    break;
  case PARSING_ARGUMENT2:
    switch (command){
    case COMMAND_LED:
      // Led command
      handle3rdCharForLed(charReceived);
      break;
    }
    parseState=PARSING_COMMAND;
    break;
  }

}

void ttyCmdHandle(uint8_t times){
  // We will try to read and parse N times
  uint8_t i;

  for (i=0;i<times;i++){
    if (Serial.available()>0){
      ttyCmdParse(Serial.read());      
    }
  }
}



