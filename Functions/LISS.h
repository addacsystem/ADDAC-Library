/*
 * LISS
 * Version 0.1 November, 2009
 * Copyright 2009 André Gonçalves
 * For details, see http://
 *
 * AD5668 programming based on
 * DAC V11 by Robin Price 2009
 +
 * shiftIn Example 2.1 by Carlyn Maw 
 */

#ifndef LISS_h
#define LISS_h

//#include "LissSpeed.h"
#include <WProgram.h>

// Provides ISR
#include <avr/interrupt.h>


#define addacMaxResolution 65535 



class LISS{
public:
	LISS();
		void setup(int _width, int _height, float _inc);
		void setup(float _inc, float _inc2);
		void setup(float _inc);
		void update();
		void update(int _t, int _t2);
		void setInc(float _inc);
		void calcs(float _min, float _max, float _speed);
	
	//LissSpeed Speed;
	float ancho,alto,AX,BX,a,b,x,y;
	float delta,t,t2,inc_t,inc_t2;	
	float rndF,rndF2, Ymin,Ymax,offset;
	
};
#endif
