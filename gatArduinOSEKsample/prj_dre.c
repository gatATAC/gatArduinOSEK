/* Data Runtime Environment is a pool of global variables that can be shared through all the application.  It acts as a centralized data base for the functionality */

#include "gttc_types.h"
#include "prj_cfg.h"
#include "prj_dre.h"

t_dre dre;

void dreInit(void){
  uint8_t i;
  for (i=0;i<NUM_LEDS;i++){
    dre.ledState[i] = LOW;             // ledState used to set the LED
  }
}

