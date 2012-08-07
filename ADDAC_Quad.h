/*
 * CARTESIAN / POLAR QUADRIPHONIC SPATIALIZER
 * Version 0.1 August, 2011
 * Copyright 2011 AndrŽ Gonalves / AndrŽ Perrota
 * For details, see http://
 *

 +
 * Spatialization algorithm by: Andre Perrota
 */

#ifndef ADDAC_Quad_h
#define ADDAC_Quad_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
// Provides ISR
#include <avr/interrupt.h>
#endif


#define addacMaxResolution 65535 



class ADDAC_Quad{
public:
	ADDAC_Quad();
		//void setup();
		void calc(int MODE, float _r, float _theta, float _in3, float _in4,float _in5);
	
    float r;
    float theta;
    
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;
    
    float amp1;
    float amp2;
    float amp3;
    float amp4;
    
    float dMax;
    float dMaxPower;
    
    float x, y;
    
    int auxTheta;
    
    float rSpeaker;
    float filterFreq;
    float filterFreqPower;
    
    float xAbs, yAbs;

	
};
#endif
