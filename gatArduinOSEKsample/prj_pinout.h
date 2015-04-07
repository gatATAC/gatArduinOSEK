/* ---- This file describes all the pin assignments of the microcontroller --- */

#ifndef _PRJ_PINOUT_H
#define _PRJ_PINOUT_H

#include "gttc_types.h"
#include "prj_input.h"
#include "prj_output.h"

#ifndef CFG_USE_TM1638
extern const uint8_t ledPin[];
extern const uint8_t buttonPin[];
#endif

#define LED_RPI_STATUS 13

#ifdef CFG_USE_RGB_LEDS
extern const uint8_t redLightPin;
extern const uint8_t greenLightPin;
extern const uint8_t blueLightPin;
#endif

void pinoutInit(void);

#endif // _PRJ_PINOUT_H


