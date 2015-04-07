/* ['Common headers' begin (DON'T REMOVE THIS LINE!)] */
#include "rgbFSM_CI.h"
/* ['Common headers' end (DON'T REMOVE THIS LINE!)] */

/* ['Common definitions for 'Code items generator'' begin (DON'T REMOVE THIS LINE!)] */
/* Generic code items' definitions */
t_dre dre;

void incrColor( uint8_t& color )
{
    /* ['<global>::incrColor' begin] */
    if (color>=255){
        color=0;
    } else {
        color=color+1;
    }
    /* ['<global>::incrColor' end] */
}
/* ['Common definitions for 'Code items generator'' end (DON'T REMOVE THIS LINE!)] */

/* ['Common definitions for 'Hierarchical State Chart generator'' begin (DON'T REMOVE THIS LINE!)] */
/* Code items' definitions */
/* ['Common definitions for 'Hierarchical State Chart generator'' end (DON'T REMOVE THIS LINE!)] */
