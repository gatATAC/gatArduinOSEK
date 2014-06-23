/* Data Runtime Environment is a pool of global variables that can be shared through all the application.  It acts as a centralized data base for the functionality */

#ifndef _PRJ_DRE_H
#define _PRJ_DRE_H

#include "gttc_types.h"
#include "prj_cfg.h"

typedef struct {

  /*** Input ***/
  /** Led statuses **/
  uint8_t ledState[NUM_LEDS];             // ledState used to set the LED

  /** Button statuses **/
  uint8_t buttonState[NUM_BUTTONS];         // variable for reading the pushbutton status
} 
t_dre;

extern t_dre dre;

#ifdef __cplusplus
extern "C" 
#endif
void dreInit(void);

#endif // _PRJ_DRE_H

