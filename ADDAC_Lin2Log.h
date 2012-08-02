/*
 * ADDAC_Lin2Log
 * 
 *
 *
 *
 *
 *
 *
 *
 */

#ifndef ADDAC_Lin2Log_h
#define ADDAC_Lin2Log_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


class ADDAC_Lin2Log{
public:
	ADDAC_Lin2Log();
	
	float calc(float _val); // Function to be called from Arduino Environment
	float calc(float _val, float _factor);
	float log10(float _x);
	
	float CVstream; // Public Variables
	
};
#endif
