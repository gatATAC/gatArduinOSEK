#ifndef _PRJ_CFG_H
#define _PRJ_CFG_H

//#define CFG_USE_TM1638 1

#ifdef CFG_USE_TM1638
#define NUM_LEDS 8
#define NUM_BUTTONS 8
#else
#define NUM_LEDS 4
#define NUM_BUTTONS 4
#endif

#endif /* _PRJ_CFG_H */

