/*
 * ADDAC_Adsr
 * Version 0.1 November, 2011
 * Copyright 2011 AndrŽ Gonalves
 */

#ifndef ADDAC_Adsr_h
#define ADDAC_Adsr_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 

//#define DEBUG
//#define DEBUG_adsr
/*! \ADDAC_ADSR class */
class ADDAC_Adsr{
public:
	ADDAC_Adsr();
	
	void update(bool _trigger, bool _inverted, float _Atime, float _D, float _Dtime,float _Stime, float _Rtime);
    void update(bool _trigger, bool _inverted, float _A, float _Atime, float _D, float _Dtime, float _Stime, float _Rtime);
	void updateLogExpMode(bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _D, float _Dtime, float _Dshape,float _S, float _Stime, float _Sshape, float _Rtime, float _Rshape);
	
	
    ///
    
	void update(float _A, float _Atime, float _D, float _Dtime, float _S,float _Stime, float _Rtime);
	
    void trigger(float _A);
	void trigger();
	void release();
    
    
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
