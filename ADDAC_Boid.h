/*
 * ADDAC_Boid
 */

#ifndef ADDAC_Boid_h
#define ADDAC_Boid_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


#include "ADDAC_PVector.h"



//min and max values - - - check if it's ok!!
#define maxWidth 1000
#define maxHeight 1000
//

class ADDAC_Boid{
    
public:
    ADDAC_Boid();
	ADDAC_Boid(float _x, float _y);
    void update(ADDAC_Boid boids[4], bool _warpAround);//POINTER???
	void update(bool _warpAround); // Function to be called from Arduino Environment
    void applyForce(ADDAC_PVector force);
    void flock(ADDAC_Boid boids[4]);//POINTER???
    
    ADDAC_PVector steer(ADDAC_PVector target, bool slowdown);
    
    
     float dist(ADDAC_PVector pt1, ADDAC_PVector pt2);
    
    ADDAC_PVector separate(ADDAC_Boid boids[4]);
    ADDAC_PVector align(ADDAC_Boid boids[4]);
    ADDAC_PVector cohesion(ADDAC_Boid boids[4]);
    
    ADDAC_PVector pos;
    ADDAC_PVector vel;
    ADDAC_PVector ac;
    
    float r;
    float maxForce;
    float maxSpeed;
    float mass;
    
    float separationV;
    float cohesionV;
    float alignV;
    float speedV;
    
};
#endif
