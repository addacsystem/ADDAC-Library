/*
 * ADDAC_Timer
 *  
 *
 *
 */

#ifndef ADDAC_Timer_h
#define ADDAC_Timer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


class ADDAC_Timer{
public:
    
    long oldTime;
    long actualTime;
    long elapsedTime;
        
	ADDAC_Timer();
	
    bool set(long _time);
	
};
#endif
