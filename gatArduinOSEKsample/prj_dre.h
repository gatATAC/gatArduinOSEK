/* Data Runtime Environment is a pool of global variables that can be shared through all the application.  It acts as a centralized data base for the functionality */

#ifndef _PRJ_DRE_H
#define _PRJ_DRE_H

#include "gttc_types.h"
#include "prj_cfg.h"
#include "prj_input.h"
#include "prj_output.h"

#define RPI_STATUS_UNKNOWN 0
#define RPI_STATUS_INIT 1
#define RPI_STATUS_READY 2
#define RPI_STATUS_GOINGOFF 3
#define RPI_STATUS_OFF 4
#define RPI_STATUS_MAX RPI_STATUS_OFF
#define RPI_STATUS_MIN RPI_STATUS_UNKNOWN

typedef struct {

  /*** Input ***/
  /** Led statuses **/
  uint8_t ledState[NUM_LEDS];             // ledState used to set the LED

  /** Button statuses **/
  uint8_t buttonState[NUM_BUTTONS];         // variable for reading the pushbutton status
  
  uint8_t rpiStatus;
} 
t_dre;

extern t_dre dre;

#ifdef __cplusplus
extern "C" 
#endif
void dreInit(void);

#endif // _PRJ_DRE_H

