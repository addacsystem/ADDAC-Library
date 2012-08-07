/*
 * ULTRALISS
 * Version 0.1 November, 2012
 * Copyright 2009 AndrŽ Gonalves
 * For details, see http://
 *
 */

#ifndef ADDAC_Liss_h
#define ADDAC_Liss_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

// Provides ISR
#include <avr/interrupt.h>


#define addacMaxResolution 65535 



class ADDAC_Liss{
public:
	ADDAC_Liss();
		void setup(int _width, int _height, float _inc);
		void setup(float _inc, float _inc2);
		void setup(float _inc);
		void update();
		void update(int _t, int _t2);
		void setInc(float _inc);
		void calc(float _amp, float _speedx, float _speedy, bool _mirror);
	
	//LissSpeed Speed;
	float ancho,alto,AX,BX,a,b,x,y;
	float delta,t,t2,inc_t,inc_t2;	
	float rndF,rndF2, Ymin,Ymax,offset;
	
};
#endif
