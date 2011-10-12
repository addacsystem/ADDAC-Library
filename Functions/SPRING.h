/*
 * SPRING
 * Version 0.1 November, 2009
 * Copyright 2009 André Gonçalves
 * For details, see http://
 *
 * 
 */

#ifndef SPRING_h
#define SPRING_h

//#include "LissSpeed.h"
#include <WProgram.h>

// Provides ISR
#include <avr/interrupt.h>


#define addacMaxResolution 65535 



class SPRING{
public:
	SPRING();
		void setup(int _width, int _height, float _inc);
		void setup(float _inc, float _inc2);
		void setup(float _inc);
		void update();
		void update(int _t, int _t2);
		void setInc(float _inc);
		void calcs(float _gx, float _gy, float _material, float _speed);
		void updatePos();
	
	
	//LissSpeed Speed;
	float ancho,alto,AX,BX,a,b;
	float delta,t,t2,inc_t,inc_t2;	
	float rndF,rndF2, Ymin,Ymax,offset;
	
	float boundX, boundY;
	float x,y,x0,y0,t0,ax,bx,ay,by,gx,gy;
	float AinitCondition, Angle, Kelasticity, Mass, Bmaterial, Velocity; 
	bool hitWall;
};
#endif
