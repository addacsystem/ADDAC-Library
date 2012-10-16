/*
 * ADDAC_SuperFormula
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_SuperFormula.h> // This loads the Class when compiling
 ADDAC_SuperFormula SuperFormula; // This Instantiates 1 Class with the name "SuperFormula"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = SuperFormula.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, SuperFormula.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:
 
 unsigned int CV = SuperFormula.CVstream;
 
 *
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


using namespace std;

// because it's up to you what to do with them.


#define addacMaxResolution 65535 



class ADDAC_SuperFormula{
public:
	ADDAC_SuperFormula();
    void calc(float m, float n1, float n2, float n3);
	long update(float _val); // Function to be called from Arduino Environment
	
	float CVstream; // Public Variables
    

    void superformula(float m, float n1, float n2, float n3, long _time); 

    void superformulaPoint(float m, float n1, float n2, float n3, float phi);
    
    void getMinMax();
    
    float minValueX;
    float maxValueX;
    
    float minValueY;
    float maxValueY;
    
    float getX();
    float getY();
    
    
    float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
    
//    float pointX[120];
//    float pointY[120];
    void setLoopMin(int _min);
    void setLoopMax(int _max);
    
    float oldValue;
    
    float pX;
    float pY;
    int pos;
    int numPoints;
    int loopMin;
    
    ADDAC_Timer metro;
      
};
#endif
