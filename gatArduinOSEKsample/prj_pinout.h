/* ---- This file describes all the pin assignments of the microcontroller --- */

#ifndef _PRJ_PINOUT_H
#define _PRJ_PINOUT_H

#include "gttc_types.h"

#ifndef CFG_USE_TM1638
extern uint8_t ledPin[NUM_LEDS];
extern uint8_t buttonPin[NUM_BUTTONS];
#endif

void pinoutInit(void);

#endif // _PRJ_PINOUT_H

