 

#include "ADDAC_Liss.h"
//#include "LissSpeed.h"



//-----------------------------------------------------------------------ADDAC-----------------
/*! \brief Default construtor for ADDAC_Lissajous */
ADDAC_Liss::ADDAC_Liss(){	
	ancho = 1023.0f;
	alto = 1023.0f;
	
	AX = ancho/2.0f;
	BX = alto/2.0f;
	
	a = 1.0f;
	b= 2.0f;
	delta = PI/2.0f;
	
	t=0.0f;
	inc_t = 0.01f;
	t2=0.0f;
	inc_t2 = 0.01f;
	
	Ymin=0.0f;
	Ymax=1.0f;
	//HITMODE=0;
	//Serial.println("ULTRALISS COMPLETE");
}
/*! \brief setup function */
void ADDAC_Liss::setup(float _inc, float _inc2){
	inc_t=_inc;
	inc_t2=_inc;
	rndF=random(0.0f, 1.0f)/100.0f;
    rndF2=random(0.0f, 1.0f)/100.0f;
}


// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief calculate a lissajous curve 
 \param _amp lissajous amplitude
 \param _speedx X speed 
 \param _speedy Y speed
 \param _mirror mode : true -> mirror, false -> warp around 
 */
void ADDAC_Liss::calc(float _amp, float _speedx, float _speedy, bool _mirror) {
    
    _amp*=1000.0f;
    _speedx*=1000.0f;
    _speedy*=1000.0f;
    
    Ymin = 1023.0f*2.0f-_amp*2.0f;
	Ymax = _amp*2.0f;
    inc_t=_speedx/1184.0f; // TEMPO MIN = 0.0001 - > TEMPO MAX = 0.25
	if(inc_t>=1)inc_t=0.999f;
	else if(inc_t<=0)inc_t=0.00001f;
	
	inc_t2=_speedy/1184.0f; // TEMPO MIN = 0.0001 - > TEMPO MAX = 0.25
	if(inc_t2>=1)inc_t2=0.999f;
	else if(inc_t2<=0)inc_t2=0.00001f;
    //inc_t2=inc_t;
    
    //int dif=int(Ymax-Ymin+Ymin);
    
    
    x = AX*sin(a*t+delta);
    y = BX*sin(b*t2);
    
    x=x*(Ymin/1023.0f); //(Ymin/1000.0f);
    y=y*(Ymin/1023.0f); //(Ymax/1000.0f);
    
    x+=1023.0f/2.0f;
    y+=1023.0f/2.0f;
	
	if(!_mirror==0){
		// COLLISION REFLECTION
		//Serial.print(" x:");
		//Serial.print(x);
		if(x<0)x=-x;//ancho*2-x;
		else if(x>ancho) x=ancho*2-x;
		if(y<0) y=-y;
		else if(y>alto)y=alto*2-y;
		//print(" |0xy| " + x + " :  " + y + " || ");
		//Serial.print(" x2:");
		//Serial.println(x);
    }else{
		// WRAP AROUND
		//Serial.print(" x:");
		//Serial.print(x);
		if(x<0)x+=ancho;//ancho*2-x;
		else if(x>ancho) x-=ancho;
		if(y<0) y+=alto;
		else if(y>alto)y-=alto;
		//print(" |1xy| " + x + " :  " + y + " || ");
		//Serial.print(" x2:");
		//Serial.print(x);
    }
	
	x = x / 1023.0f;// * addacMaxResolution;
	y = y / 1023.0f;// * addacMaxResolution;
    
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
    t += inc_t/(32.0f-_speedx/32.0f);
    t2 += inc_t2/(32.0f-_speedy/32.0f);
    
  }

// --------------------------------------------------------------------------- RETURNS -------------------------
//

void ADDAC_Liss::setInc(float _inc){
    inc_t=_inc;
    inc_t2=_inc;
}


// --------------------------------------------------------------------------- END ----------------------------------
//