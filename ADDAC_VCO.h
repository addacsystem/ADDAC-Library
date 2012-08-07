/*
 *  Interrupt and PWM utilities for 16 bit Timer3 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */


#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include <WProgram.h>
#endif


#include <avr/io.h>
#include <avr/interrupt.h>

#define RESOLUTION 65536    // Timer3 is 16 bit

class ADDAC_VCO
{
  public:
  
    // properties
    unsigned int pwmPeriod;
    unsigned char clockSelectBits;
	
	int channel, offset;
	float vol,volOffset;
	bool UP;
	int mode;
  
	// methods
    void initialize();
	void update(float _Notes05v, float _vol);
	
    void start();
    void stop();
    void restart();
    void pwm(char pin, int duty, long microseconds=-1);
    void disablePwm(char pin);
    void startup(void (*isr)(), long microseconds=-1);
    void detachInterrupt();
    void setPeriod(long microseconds);
    void setPwmDuty(char pin, int duty);
    void (*isrCallback)();
private:
	float Period(float _Notes05v);
	
	
	
};

extern ADDAC_VCO VCO;
