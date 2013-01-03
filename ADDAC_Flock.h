/*
 * ADDAC_Flock
 */

#ifndef ADDAC_Flock_h
#define ADDAC_Flock_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#include "ADDAC_Boid.h"



class ADDAC_Flock{
public:
	ADDAC_Flock();
	void update(bool _wrapAround); // Function to be called from Arduino Environment\
    
    void setup();
    
    
    //check this functions - look for min and max, get better names!
    void setSeparation(float _sep);
    void setCohesion(float _coe);
    void setAlign(float _ali);
    void setSpeed(float _speed);
    //-------
    
    
    float getBoidPositionX(int _boidNumber);
    float getBoidPositionY(int _boidNumber);
    float getBoidPositionM(int _boidNumber);
    
    ADDAC_Boid boids[4];
	
	
};
#endif
