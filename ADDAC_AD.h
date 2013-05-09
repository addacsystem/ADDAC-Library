/*
 * ADDAC_AD
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_AD.h> // This loads the Class when compiling
 ADDAC_AD AD; // This Instantiates 1 Class with the name "AD"
 
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

#ifndef ADDAC_AD_h
#define ADDAC_AD_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif



class ADDAC_AD{
public:
	ADDAC_AD();
	
    void trigger(float _A);
	void trigger();
	void release();
	void updateLin(bool _gate, float _Atime, float _Dtime);
   
    void updateLogExpMode(float _A, float _Atime, float _Ashape, float _Dtime, float _Dshape);
    void updateLogExpMode(bool _gate, float _A, float _Atime, float _Ashape, float _Dtime, float _Dshape);
	
    
    unsigned long ADSRtriggerTime;
	bool ADSRtrigger;
	
    
    float CVstream;
	unsigned int toAddDif;
	float TipPoint;
	float Attack;
	float floatPercentage, weakLink;
    
        float lastPosA,lastPosD;
    long passedTime, holdTime;
	
	bool SUSTAIN;
    
};
#endif
