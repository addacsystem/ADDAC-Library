 

#include "RANDOM.h"
//#include "RANDOMSpeed.h"



//-----------------------------------------------------------------------ADDAC-----------------

RANDOM::RANDOM(){	
	ancho = 1023;
	alto = 1023;
	
	AX = ancho/2.0f;
	BX = alto/2.0f;
	
	a = 1;
	b= 2;
	delta = PI/2.0f;
	
	t=0.0f;
	inc_t = 0.01f;
	t2=0.0f;
	inc_t2 = 0.01f;
	
	Ymin=0.0f;
	Ymax=1.0f;
	//Serial.println("RANDOM COMPLETE");
}

void RANDOM::setup(float _inc, float _inc2){
	inc_t=_inc;
	inc_t2=_inc;
	rndF=random(0.0f, 1.0f)/100.0f;
    rndF2=random(0.0f, 1.0f)/100.0f;
}


// --------------------------------------------------------------------------- UPDATE -------------------------
//

void RANDOM::calcs(float _min, float _max, float _speed) {
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
	//x*=addacMaxResolution;
	//y*=addacMaxResolution;
    //x=(x*(_max/100.0f))+500-dif/2
    //x=int(map(x,0,1000,Ymin,Ymax)+Ymin);
    //y=int(map(y,0,1000,Ymin,Ymax)*(1.0f-Ymin/1000.0f)+Ymin/2);
    /* Incrementamos el tiempo */
    //t = t+(inc_t*0.995f)+(spd.getfX()+spd.getfY())/2.0f*0.005f;
    //t = t+(inc_t*0.9935f)+ spd.getfX()*0.0065f;
    //inc_t=mouseX/10000.0f+rndF;
    //inc_t2=mouseY/10000.0f+rndF;
    t = t+inc_t;
    t2 = t2+inc_t2;
    
  }

// --------------------------------------------------------------------------- RETURNS -------------------------
//

void RANDOM::setInc(float _inc){
    inc_t=_inc;
    inc_t2=_inc;
}


// --------------------------------------------------------------------------- END ----------------------------------
//