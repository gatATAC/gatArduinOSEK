#include "prj_cfg.h"
#include "prj_input.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"

#ifdef CFG_USE_TM1638
#include <TM1638.h>

extern TM1638 module;
#endif

void prjInputInit(void){
#ifndef CFG_USE_TM1638
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);     
  pinMode(buttonPin2, INPUT);     
  pinMode(buttonPin3, INPUT);     
  pinMode(buttonPin4, INPUT);
#endif
}

void prjInput(void){
#ifdef CFG_USE_TM1638
  uint8_t i;
  byte keys = module.getButtons();
  
  for (i=0;i<NUM_BUTTONS;i++){
    dre.buttonState[i] = (keys & (0x01<<i))>0;
  }
  
#else
  // Buttons statuses read
  dre.buttonState[0] = digitalRead(buttonPin1);
  dre.buttonState[1] = digitalRead(buttonPin2);
  dre.buttonState[2] = digitalRead(buttonPin3);
  dre.buttonState[3] = digitalRead(buttonPin4);
#endif
}
