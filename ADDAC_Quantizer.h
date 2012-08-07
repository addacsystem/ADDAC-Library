/*
 * ADDAC_Quantizer
 * Version 0.1 November, 2011
 * Copyright 2011 AndrŽ Gonalves
 */

#ifndef ADDAC_Quantizer_h
#define ADDAC_Quantizer_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include <WProgram.h>
	// Provides ISR
	#include <avr/interrupt.h>
#endif

#define addacMaxResolution 65535 



class ADDAC_Quantizer{
public:
	ADDAC_Quantizer();
	float calc(float _val);
	float Note(int _val, double _partial);
	float Note(int _val);
	
	float interval;
	float offset;
	
	float NOTES[128];
	bool NOTESactive[128];
	
};
#endif
