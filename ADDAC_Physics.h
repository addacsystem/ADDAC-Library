/*
 * ADDAC_Physics
 * Version 0.1 July, 2011
 *
 *
 * AndrŽ Gonalves + Pedro Boavida
 *
 * 
 */

#ifndef ADDAC_Physics_h
#define ADDAC_Physics_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 



class ADDAC_Physics{
public:
	ADDAC_Physics();
		//void setup(float _inc, float _inc2);
		void setInc(float _inc);
		void update(float _gx, float _gy, float _material, float _speed);	
		void bump(int _fMinGateVal);
	
	
	float AX,BX,a,b;
	float delta,t,t2,inc_t,inc_t2;	
	float rndF,rndF2, Ymin,Ymax,offset;
	
	float boundX, boundY;
	float x,y,x0,y0,t0,ax,bx,ay,by,gx,gy;
	float AinitCondition, Angle, Kelasticity, Mass, Bmaterial, velocity; 
	bool hitXWall,hitYWall;
	int gateThreshold;

};
#endif
