/*
 * ADDAC_liss
 * Version 0.1 March, 2011
 */

#ifndef ADDAC_Liss_h
#define ADDAC_Liss_h

#define addacMaxResolution 65535 

#include <WProgram.h>

class ADDAC_Liss{
public:
	ADDAC_Liss();
		void setup(float _inc, float _inc2);
		void setInc(float _inc);
		void update(float _min, float _max, float _speed);
		void update(float _min, float _max, float _speedX, float _speedY);
	
	//LissSpeed Speed;
	float wid,hei,AX,BX,a,b,x,y;
	float delta,t,t2,inc_t,inc_t2;	
	float rndF,rndF2, Ymin,Ymax,offset;
	
};
#endif
