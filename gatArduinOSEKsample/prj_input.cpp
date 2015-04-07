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

}

void prjInput(void){
  uint8_t i;
#ifdef CFG_USE_TM1638
  byte keys = module.getButtons();
#endif
  for (i=0;i<NUM_BUTTONS;i++){
#ifdef CFG_USE_TM1638
    dre.buttonState[i] = (keys & (0x01<<i))>0;
#else
    // Buttons status read
    dre.buttonState[0] = digitalRead(buttonPin[i]);
#endif
  }
}




