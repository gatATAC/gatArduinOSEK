/* --- Serial console command parse module --- */
/* Each command is 3 char lenght:
 
 * la1 -> led A on
 * la0 -> led A off
 * lb1 -> led B on
 * lb0 -> led B off
 * lc1 -> led C on
 * lc0 -> led C off
 * ld1 -> led D on
 * ld0 -> led D off
 
 */

#include "prj_tty_cmds.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"

uint8_t ledToChange=0;

/** Auxiliary functions **/

void handle3rdCharForLed(uchar_t inByte){
  uint8_t value;
  if (inByte=='0'){
    value=LOW;
  } 
  else {
    value=HIGH;
  }
  if (ledToChange>0 && ledToChange<=4) {
    dre.ledState[ledToChange-1]=value;
  }
}

void handle2ndCharForLed(uchar_t inByte){
  switch (inByte) {
  case 'a':
    ledToChange=1;
    break;
  case 'b':    
    ledToChange=2;
    break;
  case 'c':    
    ledToChange=3;
    break;
  case 'd':    
    ledToChange=4;
    break;
  }
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


