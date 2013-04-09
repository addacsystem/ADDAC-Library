/*
 * ADDAC_Clock - - - > WORK ON PROGRESS - still buggy!!!
 * 
 */

#ifndef ADDAC_Clock_h
#define ADDAC_Clock_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


#define CPU_CLOCK 7500 // 125Hz


class ADDAC_Clock{
    
public:
    
    int BPM;
    int gateOnTime; //milliseconds for gate on time
    bool CLOCK_Flag;
    int counter;
    int hzToBpm;
    bool ON;
    unsigned long Time;
    
    ADDAC_Clock();
    
    void setup(void (*isr)());
    void update();
    void setBPM(int _bpm);
    void (*isrCallback)();
    
   
	
};

extern ADDAC_Clock CLK;

#endif
