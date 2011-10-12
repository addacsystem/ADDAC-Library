/*
 * CARTESIAN / POLAR QUADRIPHONIC 
 * Version 0.1 August, 2011
 * Copyright 2011 André Gonçalves / Andre Perrota
 * For details, see http://
 *

 +
 * Spatialization algorithm by: Andre Perrota
 */

#ifndef QUAD_h
#define QUAD_h

#include <WProgram.h>

// Provides ISR
#include <avr/interrupt.h>


#define addacMaxResolution 65535 



class QUAD{
public:
	QUAD();
		void setup();
		void calcs(int MODE, float _r, float _theta, float _in3,float _in4,float _in5);
	
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
