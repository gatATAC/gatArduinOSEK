/* ['Common headers' begin (DON'T REMOVE THIS LINE!)] */
#include "rgbFSM_CI.h"
/* ['Common headers' end (DON'T REMOVE THIS LINE!)] */

/* ['BlueCycle' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_BLUECYCLE_INITIAL 6
#define ID_BLUECYCLE_FINAL 7
#define ID_BLUECYCLE_INCREASING 8

STATE_T BlueCycle(  );
/* ['BlueCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['GreenCycle' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_GREENCYCLE_INITIAL 9
#define ID_GREENCYCLE_FINAL 10
#define ID_GREENCYCLE_INCREASING 11

STATE_T GreenCycle(  );
/* ['GreenCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['RedCycle' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_REDCYCLE_INITIAL 0
#define ID_REDCYCLE_FINAL 1
#define ID_REDCYCLE_INCREASING 2

STATE_T RedCycle(  );
/* ['RedCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['WhiteCycle' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_WHITECYCLE_INITIAL 3
#define ID_WHITECYCLE_FINAL 4
#define ID_WHITECYCLE_INCREASING 5

STATE_T WhiteCycle(  );
/* ['WhiteCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['rgbCycle' begin (DON'T REMOVE THIS LINE!)] */
/* State IDs */
#define ID_RGBCYCLE_INITIAL 12
#define ID_RGBCYCLE_GREENCYCLE 13
#define ID_RGBCYCLE_BLUECYCLE 14
#define ID_RGBCYCLE_WHITECYCLE 15
#define ID_RGBCYCLE_REDCYCLE 16

void rgbCycle(  );
/* ['rgbCycle' end (DON'T REMOVE THIS LINE!)] */
