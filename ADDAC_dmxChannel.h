/*
 DMX CHANNELS
 */

#ifndef ADDAC_dmxChannel_h
#define ADDAC_dmxChannel_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#include "ADDAC_Timer.h"


class ADDAC_dmxChannel{
public:
    
    int channel;
    int DMXstream;
    float actualValue;
    
    long inTime, outTime;
    float minValue, maxValue; 
    bool fadeInBang, fadeOutBang;
    bool StartUp;
    
    
    ADDAC_dmxChannel(int _channel);

    void setup();
    void update();
    
    void fadeIn(float _maxValue, long _time);
    void fadeOut(float _minValue, long _time);
    void strobe(long _time);
    
    void fadeInC();
    void fadeOutC();
    
    long memMillisIn, memMillisOut;
    long addedMillis;
   
    void strobeC(long _rate);
    long strobeRateT;
    bool strobeON;
    
    
    ADDAC_Timer strobeRate;
    
  
};
#endif
