/*
 * ADDAC_SuperFormula
 * 
 * 
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_SuperFormula.h> // This loads the Class when compiling
 ADDAC_SuperFormula SuperFormula; // This Instantiates 1 Class with the name "SuperFormula"
 
 *
 */

#ifndef ADDAC_SuperFormula_h
#define ADDAC_SuperFormula_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC_Timer.h>


//max and min values checked on processing if n1 value set to 50
#define minValueX -1.6999406
#define maxValueX  1.6999398

#define minValueY -1.6999372
#define maxValueY  1.6999389




class ADDAC_SuperFormula{
public:
	ADDAC_SuperFormula();
 
    void update(float m, float n2, float n3, long _time); 
    void superformulaPoint(float m, float n2, float n3, float phi);
    
    float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
    float getX();
    float getY();
    
    void setLoopMin(int _min);
    void setLoopMax(int _max);
    void setPingPongMode(bool _mirror);
    
    bool mirror;
    bool startUp;
    
    float oldValue;
    float pX;
    float pY;
    float oldX;
    float oldY;
    float x;
    float y;
    float interpolationX;
    float interpolationY;
    
    int pos;
    int inc;
    int oldPos;
    int numPoints;
    int loopMin;
    
    float CPUtime();
    long cpuTime[10];
    long actualTime;
    int cpuPos;
    
    long metroTime;
    ADDAC_Timer metro;
    ADDAC_Timer metro2;
          
};
#endif
