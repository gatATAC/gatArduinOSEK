#ifndef _PRJ_INPUT_H
#define _PRJ_INPUT_H

#ifdef CFG_USE_TM1638
#define NUM_BUTTONS 8
#else
#define NUM_BUTTONS 4
#endif

void prjInputInit(void);
void prjInput(void);

#endif /* _PRJ_INPUT_H */


