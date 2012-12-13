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
    void calc(bool _MODE, bool _WRAPmode, float _r, float _theta, float _free1, float _free2, float _free3);
	
    bool WRAPmode, MODE;
    
    float r;
    float theta, oldTheta, thetaA;
    bool thetaUP;
    
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
    
    float rSpeaker;
    float filterFreq;
    float filterFreqPower;
    
    float xAbs, yAbs;
    
    float oldAngle, diff;  

	
};
#endif
