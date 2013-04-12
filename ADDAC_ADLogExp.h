/*
 * ADDAC_ADLogExp
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_ADLogExp.h> // This loads the Class when compiling
 ADDAC_ADLogExp AD; // This Instantiates 1 Class with the name "AD"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = AD.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, AD.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:
 
 unsigned int CV = AD.CVstream;
 
 *
 *
 */

#ifndef ADDAC_ADLogExp_h
#define ADDAC_ADLogExp_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif



class ADDAC_ADLogExp{
public:
	ADDAC_ADLogExp();
	
    void trigger(float _A);
	void trigger();
	void release();
	void update(float _Atime, float _Dtime);
    
    void updateLogExpMode(bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _Dtime, float _Dshape);
	
    
    unsigned long ADSRtriggerTime;
	bool ADSRtrigger;
	
    
    float CVstream;
	unsigned int toAddDif;
	float TipPoint;
	float Attack;
	float floatPercentage, weakLink;
	
	bool SUSTAIN;
    
};
#endif
