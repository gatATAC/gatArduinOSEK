/* ['Common headers' begin (DON'T REMOVE THIS LINE!)] */
#ifdef CFG_USE_RGB_LEDS
#include "rgbFSM.h"
/* ['Common headers' end (DON'T REMOVE THIS LINE!)] */

/* ['BlueCycle' begin (DON'T REMOVE THIS LINE!)] */
STATE_T BlueCycle(  )
{
    /* set initial state */
    static STATE_T state = ID_BLUECYCLE_INITIAL;

    switch( state )
    {
        /* State ID: ID_BLUECYCLE_INITIAL */
        case ID_BLUECYCLE_INITIAL:
        {
            if( true )
            {
                /* Transition ID: ID_BLUECYCLE_INIT */
                /* Actions: */
                /* ['<global>::shutDownLights' begin] */
                dre.redLight=0;
                dre.greenLight=0;
                dre.blueLight=0;
                /* ['<global>::shutDownLights' end] */
                state = ID_BLUECYCLE_INCREASING;
            }
            return ID_BLUECYCLE_INITIAL;
        }
        /* State ID: ID_BLUECYCLE_INCREASING */
        case ID_BLUECYCLE_INCREASING:
        {
            if( dre.blueLight>=255 )
            {
                /* Transition ID: ID_BLUECYCLE_END */
                state = ID_BLUECYCLE_FINAL;
            }
            else if( dre.blueLight<255 )
            {
                /* Transition ID: ID_BLUECYCLE_STEP */
                /* Actions: */
                /* ['<global>::incrBlue' begin] */
                incrColor(dre.blueLight);
                /* ['<global>::incrBlue' end] */
            }
            return ID_BLUECYCLE_INCREASING;
        }
        /* State ID: ID_BLUECYCLE_FINAL */
        case ID_BLUECYCLE_FINAL:
        {
            state = ID_BLUECYCLE_INITIAL;
            return ID_BLUECYCLE_FINAL;
        }
    }
}
/* ['BlueCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['GreenCycle' begin (DON'T REMOVE THIS LINE!)] */
STATE_T GreenCycle(  )
{
    /* set initial state */
    static STATE_T state = ID_GREENCYCLE_INITIAL;

    switch( state )
    {
        /* State ID: ID_GREENCYCLE_INITIAL */
        case ID_GREENCYCLE_INITIAL:
        {
            if( true )
            {
                /* Transition ID: ID_GREENCYCLE_INIT */
                /* Actions: */
                /* ['<global>::shutDownLights' begin] */
                dre.redLight=0;
                dre.greenLight=0;
                dre.blueLight=0;
                /* ['<global>::shutDownLights' end] */
                state = ID_GREENCYCLE_INCREASING;
            }
            return ID_GREENCYCLE_INITIAL;
        }
        /* State ID: ID_GREENCYCLE_INCREASING */
        case ID_GREENCYCLE_INCREASING:
        {
            if( dre.greenLight>=255 )
            {
                /* Transition ID: ID_GREENCYCLE_END */
                state = ID_GREENCYCLE_FINAL;
            }
            else if( dre.greenLight<255 )
            {
                /* Transition ID: ID_GREENCYCLE_STEP */
                /* Actions: */
                /* ['<global>::incrGreen' begin] */
                incrColor(dre.greenLight);
                /* ['<global>::incrGreen' end] */
            }
            return ID_GREENCYCLE_INCREASING;
        }
        /* State ID: ID_GREENCYCLE_FINAL */
        case ID_GREENCYCLE_FINAL:
        {
            state = ID_GREENCYCLE_INITIAL;
            return ID_GREENCYCLE_FINAL;
        }
    }
}
/* ['GreenCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['RedCycle' begin (DON'T REMOVE THIS LINE!)] */
STATE_T RedCycle(  )
{
    /* set initial state */
    static STATE_T state = ID_REDCYCLE_INITIAL;

    switch( state )
    {
        /* State ID: ID_REDCYCLE_INITIAL */
        case ID_REDCYCLE_INITIAL:
        {
            if( true )
            {
                /* Transition ID: ID_REDCYCLE_INIT */
                /* Actions: */
                /* ['<global>::shutDownLights' begin] */
                dre.redLight=0;
                dre.greenLight=0;
                dre.blueLight=0;
                /* ['<global>::shutDownLights' end] */
                state = ID_REDCYCLE_INCREASING;
            }
            return ID_REDCYCLE_INITIAL;
        }
        /* State ID: ID_REDCYCLE_INCREASING */
        case ID_REDCYCLE_INCREASING:
        {
            if( dre.redLight>=255 )
            {
                /* Transition ID: ID_REDCYCLE_END */
                state = ID_REDCYCLE_FINAL;
            }
            else if( dre.redLight<255 )
            {
                /* Transition ID: ID_REDCYCLE_STEP */
                /* Actions: */
                /* ['<global>::incrRed' begin] */
                incrColor(dre.redLight);
                /* ['<global>::incrRed' end] */
            }
            return ID_REDCYCLE_INCREASING;
        }
        /* State ID: ID_REDCYCLE_FINAL */
        case ID_REDCYCLE_FINAL:
        {
            state = ID_REDCYCLE_INITIAL;
            return ID_REDCYCLE_FINAL;
        }
    }
}
/* ['RedCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['WhiteCycle' begin (DON'T REMOVE THIS LINE!)] */
STATE_T WhiteCycle(  )
{
    /* set initial state */
    static STATE_T state = ID_WHITECYCLE_INITIAL;

    switch( state )
    {
        /* State ID: ID_WHITECYCLE_INITIAL */
        case ID_WHITECYCLE_INITIAL:
        {
            if( true )
            {
                /* Transition ID: ID_WHITECYCLE_INIT */
                /* Actions: */
                /* ['<global>::shutDownLights' begin] */
                dre.redLight=0;
                dre.greenLight=0;
                dre.blueLight=0;
                /* ['<global>::shutDownLights' end] */
                state = ID_WHITECYCLE_INCREASING;
            }
            return ID_WHITECYCLE_INITIAL;
        }
        /* State ID: ID_WHITECYCLE_INCREASING */
        case ID_WHITECYCLE_INCREASING:
        {
            if( dre.redLight<255 )
            {
                /* Transition ID: ID_WHITECYCLE_STEP */
                /* Actions: */
                /* ['<global>::incrRed' begin] */
                incrColor(dre.redLight);
                /* ['<global>::incrRed' end] */
                /* ['<global>::incrGreen' begin] */
                incrColor(dre.greenLight);
                /* ['<global>::incrGreen' end] */
                /* ['<global>::incrBlue' begin] */
                incrColor(dre.blueLight);
                /* ['<global>::incrBlue' end] */
            }
            else if( dre.redLight>=255 )
            {
                /* Transition ID: ID_WHITECYCLE_END */
                state = ID_WHITECYCLE_FINAL;
            }
            return ID_WHITECYCLE_INCREASING;
        }
        /* State ID: ID_WHITECYCLE_FINAL */
        case ID_WHITECYCLE_FINAL:
        {
            state = ID_WHITECYCLE_INITIAL;
            return ID_WHITECYCLE_FINAL;
        }
    }
}
/* ['WhiteCycle' end (DON'T REMOVE THIS LINE!)] */

/* ['rgbCycle' begin (DON'T REMOVE THIS LINE!)] */
void rgbCycle(  )
{
    /* set initial state */
    static STATE_T state = ID_RGBCYCLE_INITIAL;

    switch( state )
    {
        /* State ID: ID_RGBCYCLE_INITIAL */
        case ID_RGBCYCLE_INITIAL:
        {
            if( true )
            {
                /* Transition ID: ID_RGBCYCLE_BOOT */
                state = ID_RGBCYCLE_WHITECYCLE;
            }
            break;
        }
        /* State ID: ID_RGBCYCLE_WHITECYCLE */
        case ID_RGBCYCLE_WHITECYCLE:
        {
            /* call substate function */
            STATE_T whitecycle_retval = WhiteCycle(  );
            if( dre.redLight>=255 )
            {
                /* Transition ID: ID_RGBCYCLE_TORED */
                state = ID_RGBCYCLE_REDCYCLE;
            }
            break;
        }
        /* State ID: ID_RGBCYCLE_REDCYCLE */
        case ID_RGBCYCLE_REDCYCLE:
        {
            /* call substate function */
            STATE_T redcycle_retval = RedCycle(  );
            if( dre.redLight>=255 )
            {
                /* Transition ID: ID_RGBCYCLE_TOGREEN */
                state = ID_RGBCYCLE_GREENCYCLE;
            }
            break;
        }
        /* State ID: ID_RGBCYCLE_GREENCYCLE */
        case ID_RGBCYCLE_GREENCYCLE:
        {
            /* call substate function */
            STATE_T greencycle_retval = GreenCycle(  );
            if( dre.greenLight>=255 )
            {
                /* Transition ID: ID_RGBCYCLE_TOBLUE */
                state = ID_RGBCYCLE_BLUECYCLE;
            }
            break;
        }
        /* State ID: ID_RGBCYCLE_BLUECYCLE */
        case ID_RGBCYCLE_BLUECYCLE:
        {
            /* call substate function */
            STATE_T bluecycle_retval = BlueCycle(  );
            if( dre.blueLight>=255 )
            {
                /* Transition ID: ID_RGBCYCLE_TOWHITE */
                state = ID_RGBCYCLE_WHITECYCLE;
            }
            break;
        }
    }
}
/* ['rgbCycle' end (DON'T REMOVE THIS LINE!)] */
#endif
