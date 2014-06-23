#include "prj_cfg.h"
#include "prj_output.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"

#ifdef CFG_USE_TM1638
#include <TM1638.h>

extern TM1638 module;
#endif

void prjOutputInit(void){
#ifdef CFG_USE_TM1638
  // Do nothing
#else
  // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);      
  pinMode(ledPin2, OUTPUT);      
  pinMode(ledPin3, OUTPUT);      
  pinMode(ledPin4, OUTPUT); 
#endif
}

void prjOutput(void){
  // Do nothing
  uint8_t i;
  for (i=0;i<NUM_LEDS;i++){
    if (dre.ledState[i]>0){
#ifdef CFG_USE_TM1638
      if (dre.ledState[i]>1){
        module.setLED(TM1638_COLOR_RED, i);
      } 
      else {
        module.setLED(TM1638_COLOR_GREEN, i);
      }
#else
      digitalWrite(ledPin[i],HIGH);
#endif
    } 
    else {
#ifdef CFG_USE_TM1638
      module.setLED(TM1638_COLOR_NONE, i);
#else
      digitalWrite(ledPin[i],LOW);
#endif
    }
  }
}


