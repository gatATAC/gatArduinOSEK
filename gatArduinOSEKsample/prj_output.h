#ifndef _PRJ_OUTPUT_H
#define _PRJ_OUTPUT_H

#ifdef CFG_USE_TM1638
#define NUM_LEDS 8
#else
#define NUM_LEDS 4
#endif

#ifdef __cplusplus
extern "C" 
#endif
void prjOutputInit(void);

#ifdef __cplusplus
extern "C" 
#endif
void prjOutput(void);

#endif /* _PRJ_OUTPUT_H */



