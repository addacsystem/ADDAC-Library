 

#include "SPRING.h"
//#include "LissSpeed.h"



//-----------------------------------------------------------------------ADDAC-----------------

SPRING::SPRING(){	
	AinitCondition = 2;
	Angle = PI/2;
	Kelasticity = 1;
	Mass = 1; 
	Bmaterial = 1;
	x=0;
	y=0;
	x0=0;
	y0=0;
	t0=0;
	ax=0;
	bx=0;
	ay=0;
	by=0;
	gx=4;
	gy=-10;
	boundX=500;
	boundY=500;
	
	t=0.0f;
	inc_t = 0.01f;
	
	Ymin=0.0f;
	Ymax=1.0f;
	//Serial.println("SPRING COMPLETE");
	hitWall=false;
}

void SPRING::setup(float _inc, float _inc2){
	inc_t=_inc;
	inc_t2=_inc;
}


// --------------------------------------------------------------------------- UPDATE -------------------------
//

void SPRING::calcs(float _gx, float _gy, float _material, float _speed) {
    
	gx=_gx;
	gy =_gy;
	Bmaterial= _material;
	//boundX=_speed;
	//boundY=_speed;
	inc_t = _speed;
	//x = AinitCondition* encolher * cos(sqrt(Kelasticity/Mass)*t*(encolher))*cos(Angle);
	//y = -AinitCondition* encolher * cos(sqrt(Kelasticity/Mass)*t*(encolher))*sin(Angle);
	
	//x = (x+2) / 4.0f * addacMaxResolution;
	//y = (y+2) / 4.0f * addacMaxResolution;
	
	x = 0.5f * gx * (t*t) + (ax*t) + bx;
	y= 0.5f * gy * (t*t) + (ay*t) + by;
	
	
	hitWall=false;
	if(x < -boundX || x>boundX){
		if(x < -boundX) x=-boundX;
		else if(x > boundX) x=boundX;
		t0=t;
		t=0;
		bx=x;
		by=y;
		float vx=gx*t0 + ax;
		float vy=gy*t0 + ay;
		ax = -vx*Bmaterial;
		ay = vy*Bmaterial;
		if(gx!=0)hitWall=true;
	}
	if(y < -boundY || y>boundY){
		if(y < -boundY) y=-boundY;
		else if(y > boundY) y=boundY;
		t0=t;
		t=0;
		bx=x;
		by=y;
		float vx=gx*t0 + ax;
		float vy=gy*t0 + ay;
		ax = vx*Bmaterial;
		ay = -vy*Bmaterial;
		hitWall=true;
	}
	
	Velocity = sqrt((gx * t + ax)*(gx * t + ax) + (gy * t + ay)*(gy * t + ay));
	Velocity = constrain(Velocity,0,20);
	Velocity = Velocity/20.0f *addacMaxResolution;
	
	x=(x + boundX) / (boundX * 2) * addacMaxResolution;
	y=(y + boundY) / (boundY * 2) * addacMaxResolution;
	
	t = t+inc_t;
    
  }


// --------------------------------------------------------------------------- RETURNS -------------------------
//

void SPRING::setInc(float _inc){
    inc_t=_inc;
    inc_t2=_inc;
}


// --------------------------------------------------------------------------- END ----------------------------------
//