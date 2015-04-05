#include "gttc_timer.h"
#include "prj_cfg.h"
#include "prj_output.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"

void prjOutputInit(void){
  uint8_t i;
  for (i=0;i<NUM_LEDS;i++) {
    // set the digital pin as output:
    pinMode(ledPin[i], OUTPUT);      
  }
}

void prjOutput(void){
  uint8_t i;
  for (i=0;i<NUM_LEDS;i++){
    if (dre.ledState[i]==HIGH){
      digitalWrite(ledPin[i],HIGH);
    } 
    else {
      digitalWrite(ledPin[i],LOW);
    }
  }
}



