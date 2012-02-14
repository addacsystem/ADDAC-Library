/*
 * ADDAC_Clock
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_Clock.h> // This loads the Class when compiling
 ADDAC_Clock Empty; // This Instantiates 1 Class with the name "Empty"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = Empty.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, Empty.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:
 
 unsigned int CV = Empty.CVstream;
 
 *
 *
 */

#ifndef ADDAC_Clock_h
#define ADDAC_Clock_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 

#define DEBUG

class ADDAC_Clock{
public:
	ADDAC_Clock(int _pin);
	ADDAC_Clock(int _pin, int _steps, int _stepSize);
	void update(bool _INval, bool _reset, unsigned long tempTime, int _pot1, int _pot2);
    void simpleUpdate(int Counter, int _interval, int _dutyCycle, unsigned long tempTime, int _pot1, int _pot2);
    
	void reset(unsigned long _time);
	void clock(unsigned long _time, int _interval, int _dutyCycle);
	void simpleClock(unsigned long _time, int _interval, int _dutyCycle);
	
    void stepUpdate(unsigned long tempTime);
    void simpleStepUpdate(unsigned long tempTime);
	
    void checkClock(bool _val);
    void checkChangeState();
    
	unsigned long time, oldTime;
	int pin;
	bool STATE;
	
	
	int dutyCycle, stepTime;
	int stepsPerBar, stepSize, actualStep, step; 
	int bars, actualBar;
	int delay;
	bool STEP; 
    bool ON; 
    bool CLOCK;
    bool OUT;
    
    
    bool RESEt;
    
    int Counter, Change;
    int Pot1Bars, Pot2Steps;
    int gateVal;
    bool CLKtrig, CLKval, CLKup, CLKdown;
    int timeInterval, interval;
    int state;
	
};
#endif
