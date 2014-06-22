/* Data Runtime Environment is a pool of global variables that can be shared through all the application.  It acts as a centralized data base for the functionality */

#include "gttc_types.h"
#include "prj_dre.h"

t_dre dre;

void dreInit(void){
  dre.ledState[0] = LOW;             // ledState used to set the LED
  dre.ledState[1] = LOW;             // ledState used to set the LED
  dre.ledState[2] = LOW;             // ledState used to set the LED
  dre.ledState[3] = LOW;             // ledState used to set the LED
}

