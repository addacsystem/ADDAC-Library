 

#include "ADDAC_Liss.h"


//-----------------------------------------------------------------------ADDAC-----------------
ADDAC_Liss::ADDAC_Liss(){	
	wid = 1023;
	hei = 1023;
	
	AX = wid/2.0f;
	BX = hei/2.0f;
	
	a = 1;
	b= 2;
	delta = PI/2.0f;
	
	t=0.0f;
	inc_t = 0.01f;
	t2=0.0f;
	inc_t2 = 0.01f;
	
	Ymin=0.0f;
	Ymax=1.0f;
	
	inc_t	= random(0.0f, 1.0f)/100.0f;
    inc_t2	= random(0.0f, 1.0f)/100.0f;
	
	//Serial.println("LISS COMPLETE");
}

void ADDAC_Liss::setup(float _inc, float _inc2){
	inc_t=_inc;
	inc_t2=_inc;
	
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_Liss::update(float _min, float _max, float _speedX, float _speedY) {
    Ymin = _min;
	Ymax = _max;
    inc_t=_speedX/8184.0f; // TEMPO MIN = 0.0001 - > TEMPO MAX = 0.25
	inc_t2=_speedY/8184.0f; // TEMPO MIN = 0.0001 - > TEMPO MAX = 0.25
	
	if(inc_t>=1)inc_t=0.999f;
	else if(inc_t<=0)inc_t=0.0001f;
    if(inc_t2>=1)inc_t2=0.999f;
	else if(inc_t2<=0)inc_t2=0.0001f;
    
    //int dif=int(Ymax-Ymin+Ymin);
    
    x = AX*sin(a*t+delta);
    y = BX*sin(b*t2);
    
    x=x*(_min/1023.0f); //(Ymin/1000.0f);
    y=y*(_max/1023.0f); //(Ymax/1000.0f);
    
    x+=1023/2.0f;
    y+=1023/2.0f;
	
	x = x / 1023.0f * addacMaxResolution;
	y = y / 1023.0f * addacMaxResolution;
	
    t = t+inc_t;
    t2 = t2+inc_t2;
    
}


void ADDAC_Liss::update(float _min, float _max, float _speed) {
    Ymin = _min;
	Ymax = _max;
    inc_t=_speed/8184.0f; // TEMPO MIN = 0.0001 - > TEMPO MAX = 0.25
	if(inc_t>=1)inc_t=0.999f;
	else if(inc_t<=0)inc_t=0.0001f;
    inc_t2=inc_t;
    
    //int dif=int(Ymax-Ymin+Ymin);
    
    
    x = AX*sin(a*t+delta);
    y = BX*sin(b*t2);
    
    x=x*(_min/1023.0f); //(Ymin/1000.0f);
    y=y*(_max/1023.0f); //(Ymax/1000.0f);
    
    x+=1023/2.0f;
    y+=1023/2.0f;
	
	x = x / 1023.0f * addacMaxResolution;
	y = y / 1023.0f * addacMaxResolution;
	
    t = t+inc_t;
    t2 = t2+inc_t2;
    
  }

// --------------------------------------------------------------------------- RETURNS -------------------------
//

void ADDAC_Liss::setInc(float _inc){
    inc_t=_inc;
    inc_t2=_inc;
}


// --------------------------------------------------------------------------- END ----------------------------------
//