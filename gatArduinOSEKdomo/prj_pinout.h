/* ---- This file describes all the pin assignments of the microcontroller --- */

#ifndef _PRJ_PINOUT_H
#define _PRJ_PINOUT_H

#include "gttc_types.h"

extern const uint8_t ledPin[];

#define CFG_LED_PINS {13}

void pinoutInit(void);

#endif // _PRJ_PINOUT_H

