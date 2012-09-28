 

#include "ADDAC_Physics.h"



//-----------------------------------------------------------------------ADDAC-----------------
/*! \brief Default constructor for ADDAC_Physics. */
ADDAC_Physics::ADDAC_Physics(){	
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
	
	gateThreshold = 400; // 1.25v !!
	
	//Serial.println("PHYSICS COMPLETE");
	hitXWall=false;
	hitYWall=false;
}


// --------------------------------------------------------------------------- UPDATE -------------------------
//
/*! \brief Marble Physics update
 \param _gx X gravity/force
 \param _gy Y gravity/force
 \param _material ball ellasticity
 \param _speed ball spped
 */

void ADDAC_Physics::update(float _gx, float _gy, float _material, float _speed) {
    
	gx =_gx-0.5;//1023.0f - 0.5f;
	gy =_gy-0.5;//1023.0f - 0.5f;
	Bmaterial= _material/2.0f+0.5;///1023.0f/2+0.5f;
	//boundX=_speed;
	//boundY=_speed;
	inc_t = _speed*4.0f;
	
	//x = AinitCondition* encolher * cos(sqrt(Kelasticity/Mass)*t*(encolher))*cos(Angle);
	//y = -AinitCondition* encolher * cos(sqrt(Kelasticity/Mass)*t*(encolher))*sin(Angle);
	
	//x = (x+2) / 4.0f * addacMaxResolution;
	//y = (y+2) / 4.0f * addacMaxResolution;
	
	x = 0.5f * gx * (t*t) + (ax*t) + bx;
	y= 0.5f * gy * (t*t) + (ay*t) + by;
	
	
	hitXWall=false;
	hitYWall=false;
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
		if(gx!=0)hitXWall=true;
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
		hitYWall=true;
	}
	
	Velocity = sqrt((gx * t + ax)*(gx * t + ax) + (gy * t + ay)*(gy * t + ay));
	Velocity = constrain(Velocity,0,20);
	Velocity = Velocity/20.0f;
	
	x=(x + boundX) / (boundX * 2);
	y=(y + boundY) / (boundY * 2);
	
	t = t+inc_t;
    
  }


/*! \brief Bump Marble
 \param _fMinGateVal force
 */
void ADDAC_Physics::bump(int _fMinGateVal){
	if(_fMinGateVal>gateThreshold){
        Serial.print(" GATED!");
        t=0;
		x=0;
        y=0;
        x0=0;
		y0=0;
        ax=10; // vel inicial x
		bx=0;
		ay=-10.0f; // vel inicial y
		by=0;
		//Spring.gx= map(mouseX,0,width,0,2)-1;
        //Spring.gy= map(mouseY,0,height,0,2)-1;
        t=0;
      }
}

// --------------------------------------------------------------------------- OTHER -------------------------
//

void ADDAC_Physics::setInc(float _inc){
    inc_t=_inc;
    inc_t2=_inc;
}


// --------------------------------------------------------------------------- END ----------------------------------
//