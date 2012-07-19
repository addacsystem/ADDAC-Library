/*
 * ADDAC_Empty
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_Empty.h> // This loads the Class when compiling
 ADDAC_Empty Empty; // This Instantiates 1 Class with the name "Empty"
 
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

#ifndef ADDAC_Empty_h
#define ADDAC_Empty_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 



class ADDAC_Comparator{
public:
	ADDAC_Comparator();
	
    bool Comparator(float _input, float _threshold); // Function to be called from Arduino Environment
    bool Comparator(float _input, float _threshold, float _delay); // Function to be called from Arduino Environment

    bool triggerComparator;
    bool triggerState;
    bool triggerTimeCount;
    
    float timeEleapsed;
    float time;
    float oldTime;
	
    
	
};
#endif
