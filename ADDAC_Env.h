/*
 * ADDAC_Adsr
 * Version 0.1 November, 2011
 * Copyright 2011 André Gonçalves
 */

#ifndef ADDAC_Env_h
#define ADDAC_Env_h

#include <StandardCplusplus.h>
#include <vector>


using namespace std;
// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.



#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 

//#define DEBUG
//#define DEBUG_env

/*! \ADDAC_Env class */
class ADDAC_Env{
public:
	ADDAC_Env();
	
	void update(bool _trigger, bool _inverted, float _A, float _Atime, float _D, float _Dtime, float _S,float _Stime, float _Rtime);
	
    
    void MultiEnv(bool _trigger, bool _inverted);
    void MultiEnvLoop(bool _trigger, bool _inverted);
    void PrintMultiEnv();
    void addPoint(float _amp, float _time);
	
	unsigned long ENVtriggerTime;
	int actualStep;
    bool ENVtrigger;
	
    float CVstream;
	unsigned int toAddDif;
	long TipPoint;
	float Attack;
	float floatPercentage, weakLink;
	
	bool SUSTAIN;
    bool _loopON;
    
    vector<float> time;
    vector<float> amplitude;
	
};
#endif
