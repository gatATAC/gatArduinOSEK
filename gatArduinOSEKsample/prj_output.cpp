#include "gttc_timer.h"
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
#ifdef CFG_USE_RGB_LEDS
  analogWrite(redLightPin,dre.redLight);
  analogWrite(greenLightPin,dre.greenLight);
  analogWrite(blueLightPin,dre.blueLight);
#endif
}

#define RPI_LED_STATE_INIT 0
#define RPI_LED_STATE_BLINKING_ON 1
#define RPI_LED_STATE_BLINKING_OFF 2
#define RPI_LED_STATE_ON 3
#define RPI_LED_STATE_OFF 4

#define RPI_PERIOD_INIT 20
#define RPI_PERIOD_GOINGOFF 5

uint8_t rpiLedState = RPI_LED_STATE_INIT;
uint8_t rpiLedPeriod=RPI_PERIOD_INIT;
uint8_t currentRPiPeriod = 0;

void handleRPiStatusPin(void){
  switch (rpiLedState){
  case RPI_LED_STATE_INIT:
    if (dre.rpiStatus==RPI_STATUS_INIT){
      rpiLedState=RPI_LED_STATE_BLINKING_ON;
      rpiLedPeriod=RPI_PERIOD_INIT;
      currentRPiPeriod = 0;
      digitalWrite(LED_RPI_STATUS, HIGH);
    }
    break;
  case RPI_LED_STATE_BLINKING_ON:
    if (dre.rpiStatus==RPI_STATUS_READY){
      rpiLedState=RPI_LED_STATE_ON;
      currentRPiPeriod = 0;
     digitalWrite(LED_RPI_STATUS, HIGH);
    } 
    else {
      if (dre.rpiStatus==RPI_STATUS_OFF){
        rpiLedState=RPI_LED_STATE_OFF;
        currentRPiPeriod = 0;
        digitalWrite(LED_RPI_STATUS, LOW);
      } 
      else {
        if (currentRPiPeriod>=rpiLedPeriod){
          rpiLedState=RPI_LED_STATE_BLINKING_OFF;
          currentRPiPeriod = 0;          
          digitalWrite(LED_RPI_STATUS, LOW);
        } 
        else {
          currentRPiPeriod++;
        }
      }
    }
    break;
  case RPI_LED_STATE_BLINKING_OFF:
    if (dre.rpiStatus==RPI_STATUS_READY){
      rpiLedState=RPI_LED_STATE_ON;
      currentRPiPeriod = 0;
      digitalWrite(LED_RPI_STATUS, HIGH);
    } 
    else {
      if (dre.rpiStatus==RPI_STATUS_OFF){
        rpiLedState=RPI_LED_STATE_OFF;
        currentRPiPeriod = 0;
        digitalWrite(LED_RPI_STATUS, LOW);
      } 
      else {
        if (currentRPiPeriod>=rpiLedPeriod){
          rpiLedState=RPI_LED_STATE_BLINKING_ON;
          digitalWrite(LED_RPI_STATUS, HIGH);
          currentRPiPeriod = 0;          
        } 
        else {
          currentRPiPeriod++;
        }
      }
    }
    break;
  case RPI_LED_STATE_ON:
    if (dre.rpiStatus==RPI_STATUS_GOINGOFF){
      rpiLedState=RPI_LED_STATE_BLINKING_ON;
      rpiLedPeriod=RPI_PERIOD_GOINGOFF;
      currentRPiPeriod = 0;
      digitalWrite(LED_RPI_STATUS, LOW);
    }
    break;
  case RPI_LED_STATE_OFF:
    if (dre.rpiStatus==RPI_STATUS_INIT){
      rpiLedState=RPI_LED_STATE_BLINKING_ON;
      rpiLedPeriod=RPI_PERIOD_INIT;
      currentRPiPeriod = 0;
      digitalWrite(LED_RPI_STATUS, HIGH);
    }
    break;
  }
}

void prjOutput(void){
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
#ifdef CFG_USE_TM1638
    module.setDisplayToDecNumber(CYCLE_TIME_MICROS-busyMicros, 0);
#endif
  }
  handleRPiStatusPin();
  
#ifdef CFG_USE_RGB_LEDS
  analogWrite(redLightPin,dre.redLight);
  analogWrite(greenLightPin,dre.greenLight);
  analogWrite(blueLightPin,dre.blueLight);
#endif  
}




