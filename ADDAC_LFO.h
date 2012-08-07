/*
 * ADDAC_LFO
 * 
 * ag.09/2011
 * Version 0.1
 
 *
 * in the Arduino environment simply add at the very top:
 
 #include <ADDAC_LFO.h> // This loads the Class when compiling
 ADDAC_LFO LFO1; // This Instantiates 1 Class with the name "LFO1"
 
 
 *
 *
 */


#ifndef ADDAC_LFO_h
#define ADDAC_LFO_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 



class ADDAC_LFO{
public:
	ADDAC_LFO();
	void update(float _freq); // Function to be called from Arduino Environment
	
    void SINupdate();
    unsigned int SINget();
    
    void SINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top);
    void SINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset);
    void COSINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top);
    void COSINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset);
    void lfosMode(int _MODE, int _type, int _channel);
    
    
    unsigned long SINoldTimes[8];
    boolean direction[8];
    boolean Direction;
    unsigned int rndStep[8];
    unsigned int SINval, SIN;
    float increment, position;
    float CVstream;
    float stream;
    
};
#endif
