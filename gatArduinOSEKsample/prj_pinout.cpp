#include "gttc_types.h"
#include "prj_cfg.h"
#include "prj_pinout.h"

#ifdef CFG_USE_TM1638
#include <TM1638.h>

extern TM1638 module;

const uint8_t ledPin[]={13,12,11,10};
const uint8_t buttonPin[]={2,3,4,5};
#endif

#ifdef CFG_USE_RGB_LEDS
const uint8_t redLightPin = 3;
const uint8_t greenLightPin = 5;
const uint8_t blueLightPin = 6;
#endif

void pinoutInit(void){
#ifndef CFG_USE_TM1638
  uint8_t i;
  for (i=0;i<NUM_BUTTONS;i++){
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin[i], INPUT);     
  }
#endif  
  
  // set the digital pin as output:
  pinMode(LED_RPI_STATUS, OUTPUT);

#ifdef CFG_USE_TM1638
  module.setDisplayToDecNumber(101010, 0);
#else
  for (i=0;i<NUM_LEDS;i++) {
    // set the digital pin as output:
    pinMode(ledPin[i], OUTPUT);      
  }
#endif

#ifdef CFG_USE_RGB_LEDS
  pinMode(redLightPin,OUTPUT);
  pinMode(greenLightPin,OUTPUT);
  pinMode(blueLightPin,OUTPUT);
#endif
}


