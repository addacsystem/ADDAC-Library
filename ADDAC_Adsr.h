/*
 * ADDAC_Adsr
 * Version 0.1 November, 2011
 * Copyright 2011 André Gonçalves
 */

#ifndef ADDAC_Adsr_h
#define ADDAC_Adsr_h

#include <WProgram.h>

#define addacMaxResolution 65535 



class ADDAC_Adsr{
public:
	ADDAC_Adsr();
	
	void adsrMode(int _channel, bool _trigger, bool _inverted, float _A, float _Atime, float _D, float _Dtime, float _S,float _Stime, float _Rtime);
	void adsrLogExpMode(int _channel, bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _D, float _Dtime, float _Dshape, float _S, float _Stime, float _Sshape, float _Rtime, float _Rshape);
	void adsrWeirdMode(int _channel, bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _D, float _Dtime, float _Dshape);
	
	unsigned long ADSRtriggerTime;
	bool ADSRtrigger;
	
	unsigned int CVstream;
	
	
};
#endif
