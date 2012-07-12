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

class ADDAC_Adsr{
public:
	ADDAC_Adsr();
	
	void adsrMode(bool _trigger, bool _inverted, float _Atime, float _D, float _Dtime,float _Stime, float _Rtime);
    void adsrMode(bool _trigger, bool _inverted, float _A, float _Atime, float _D, float _Dtime, float _Stime, float _Rtime);
	void adsrLogExpMode(bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _D, float _Dtime, float _Dshape, float _S, float _Stime, float _Sshape, float _Rtime, float _Rshape);
	void adsrWeirdMode(bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _D, float _Dtime, float _Dshape);
	
	void AD_trigger(float _A);
	void AD_trigger();
	void AD_release();
	void AD_update(float _Atime, float _Dtime);
	void ADSR_update(float _A, float _Atime, float _D, float _Dtime,float _S ,float _Stime, float _Rtime);
    
	
	unsigned long ADSRtriggerTime;
	bool ADSRtrigger;
	
    float CVstream;
	unsigned int toAddDif;
	long TipPoint;
	float Attack;
	float floatPercentage, weakLink;
	
	bool SUSTAIN;
	
};
#endif
