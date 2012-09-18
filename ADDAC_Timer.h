/*
 * ADDAC_Timer
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_Timer.h> // This loads the Class when compiling
 ADDAC_Timer Timer; // This Instantiates 1 Class with the name "Timer"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = Timer.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, Timer.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:
 
 unsigned int CV = Timer.CVstream;
 
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

#define addacMaxResolution 65535 



class ADDAC_Timer{
public:
    
    float oldTime;
    float actualTime;
    float elapsedTime;
    
    
	ADDAC_Timer();
	
    
    bool set(long _time);
	
};
#endif
