/*
 * ADDAC_GateDelay
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_GateDelay.h> // This loads the Class when compiling
 ADDAC_GateDelay Empty; // This Instantiates 1 Class with the name "Empty"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = Empty.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, Empty.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:
 
 unsigned int CV = Empty.CVstream;
 
 *
 *
 */

#ifndef ADDAC_GateDelay_h
#define ADDAC_GateDelay_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 



class ADDAC_GateDelay{
public:
	ADDAC_GateDelay();
	long update(); // Function to be called from Arduino Environment
    
	void GateDelayRise();
    
    void GateDelayFall();
    
	bool update(float _delay);
    
    
    float time, timeFall, totalTime;
    int state, oldState;
	
};
#endif
