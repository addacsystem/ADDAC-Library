/*

 */

#ifndef ADDAC_Probabilistic_h
#define ADDAC_Probabilistic_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


class ADDAC_Probabilistic{

public:
	
    ADDAC_Probabilistic();
    
	void update(float _p1, float _p2, float _p3, float _p4, float _offSet); // Function to be called from Arduino Environment
    void calc();
    float glide();
    void setGlide(bool _state);
    void switchGlide();
    float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
    
    float min1, min2, min3, min4, min5;
    float max1, max2, max3, max4, max5;
        
    float randomResult;  
    float randomResultOld;
    float actualPosition;
    
    float glideStream;
    float incG;
    
    float diffVoltage;
    float diffTime;
    long bangTime;
    long bangTimeOld;
    long inct;
    
    bool out1;
    bool out2;
    bool out3;
    bool out4;
    bool out5;
    bool cvUP;
    bool glideOn;
    bool startUp;
    
    
    float CVstream;
	
	
	
};
#endif
