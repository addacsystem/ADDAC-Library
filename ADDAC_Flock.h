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
    
    ADDAC_PVector getBoidPosition(int _boidNumber);
    
    ADDAC_Boid boids[4];
	
	
};
#endif
