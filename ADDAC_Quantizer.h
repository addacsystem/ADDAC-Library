/*
 * ADDAC_Quantizer
 * Version 0.1 November, 2011
 * Copyright 2011 André Gonçalves
 */

#ifndef ADDAC_Quantizer_h
#define ADDAC_Quantizer_h

#include <WProgram.h>

// Provides ISR
#include <avr/interrupt.h>


#define addacMaxResolution 65535 



class ADDAC_Quantizer{
public:
	ADDAC_Quantizer();
	long quantize(unsigned int _val);
	
	float interval;
	float offset;
	
	float NOTES[61];
	bool NOTESactive[61];
	
};
#endif
