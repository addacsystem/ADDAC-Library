/*
 * ADDAC_Smooth
 * 
 */

#ifndef ADDAC_Smooth_h
#define ADDAC_Smooth_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 



class ADDAC_Smooth{
public:
	ADDAC_Smooth();
    
    float oldValue, smoothed;
	float calc(float newValue, float smoothFactor);
};
#endif
