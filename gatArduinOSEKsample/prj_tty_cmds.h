#ifndef _PRJ_TTY_CMDS_H
#define _PRJ_TTY_CMDS_H
#include "prj_cfg.h"
#include "gttc_types.h"

#define CYCLE_SECURITY_TIME_MICROS 100L

void ttyCmdHandle(uint8_t times);

#ifdef CFG_USE_I2C
// callback for received data
void receiveI2cData(int byteCount);
#endif

#endif // _PRJ_TTY_CMDS_H

