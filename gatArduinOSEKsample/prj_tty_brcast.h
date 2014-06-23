/* --- Button status broadcast of status buttons and timer measurements --- */

#ifndef _PRJ_TTY_BRCAST_H
#define _PRJ_TTY_BRCAST_H

#include "gttc_types.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "prj_cfg.h"

/*** Broadcast period ***/
#define BUTTON_BROADCAST_PERIOD_MICROS 50000L
#define BUTTON_BROADCAST_PERIOD_CYCLES (BUTTON_BROADCAST_PERIOD_MICROS/CYCLE_TIME_MICROS)

#ifndef CFG_USE_I2C
void buttonBroadcast(void);
#else
void sendI2cData(void);
#endif

#endif // _PRJ_TTY_BRCAST_H

