/*
 * ADDA5664
 * Version 0.1 November, 2009
 * Copyright 2009 AndrŽ Gonalves
 * For details, see http://
 *
 * AD5668 programming based on
 * DAC V11 by Robin Price 2009
 +
 * shiftIn Example 2.1 by Carlyn Maw 
 */

#ifndef ADDAC_Random_h
#define ADDAC_Random_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

extern volatile unsigned long timer0_millis;


class ADDAC_Random{
public:
	ADDAC_Random();
	
		// MODES
		float CVstream; 
		float actualCVstream; // replace DACvolts[4];
		float oldCVstream; // replace oldDACvolts[4];
		unsigned long RandomTime; // replace DACtimes[4];
		unsigned long oldRandomTime;
		int RandomDelay; // replace RNDdelays[4];
		bool GateDelay; // replace GateDelay[4];
		bool GateOut, ClockOut, StepReset;
		float BrownVal;
	
		int	BROWN,BROWNTIME;
		float fMin,fMax,fSeed,vMin,vMax;
		float threshold;
		float smooth;
		int TRIGGtime;
	
		// RANDOM
	
		void setBrownianRandom(bool brown);
		void setBrownianTime(bool brown);
		void setStepReset(bool _reset);
	
		void update(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth);
		void update(bool _gate, float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth);

private:
		void CalcRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth);
		void CalcGatedRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth);
		void CalcGatedRandomUpdate(float _smooth);
		
		void CalcNormalRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax);
		void CalcGaussianRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax);
		void CalcBrownianRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax);
		void CalcBrownianTimedRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax);
		
		void brownian(float _randomMin, float _randomMax);
		void brownianTime(float _randomMin, float _randomMax);
		
};


#endif
