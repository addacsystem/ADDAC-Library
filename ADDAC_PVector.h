/*
 * ADDAC_PVector
 * 
 * PVectors like processing (work in progress)
 *
 */

#ifndef ADDAC_PVector_h
#define ADDAC_PVector_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif




class ADDAC_PVector{
public:
	ADDAC_PVector();
    ADDAC_PVector(float _x, float _y);
    ADDAC_PVector(float _x, float _y, float _z);
    
    float x;
    float y;
    float z;
    
    void set(float _x, float _y);
    void set(float _x, float _y, float _z);
    
    void add(float _add);
    void add(ADDAC_PVector _add);
    void sub(float _sub);
    void sub(ADDAC_PVector _sub);
    void mult(float _mult);
    void div(float _div);
    void normalize();
    
   
    
    
    ADDAC_PVector divR(float _div);
    ADDAC_PVector div(ADDAC_PVector pv1, float _div);
    
};
#endif
