 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_SuperFormula.h"

//-----------------------------------------------------------------------ADDAC SuperFormula-----------------

ADDAC_SuperFormula::ADDAC_SuperFormula(){	// INITIALIZE CLASS
	
	CVstream = 0.0f;
    pos=0;
    pX=0;
    pY=0;
    numPoints = 360;
    loopMin=0;
    inc=1;
	mirror = false;
	//Serial.println("ADDAC_SuperFormula INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


long ADDAC_SuperFormula::update(float _val){ // DO SOMETHING !
	
	// return the value
	return CVstream;

}

// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_SuperFormula::superformula(float m, float n1, float n2, float n3, long _time) {
   
    long oldTime=millis();
    
    float phi = TWO_PI / 360;
    metroTime=_time;
    
   if(metro.set(metroTime)){
       

       
       if (mirror) {

           
           
           if(pos>numPoints){
               pos=numPoints;
               inc=-1;
           
           }
           
           if(pos<loopMin){
               pos=loopMin;
               inc=1;
           
           }
           
           pos+=inc;
           
       }
       else{ 
           pos++;
           if(pos>numPoints) pos = loopMin;
       }
       Serial.print("min: ");
       Serial.print(loopMin);
       Serial.print(" pos: ");
       Serial.print(pos);
       Serial.print(" max: ");
       Serial.println(numPoints);
       oldPos=pos;
    superformulaPoint(m, n1, n2, n3, phi);
 }
    
    long timeCpu=fabs(actualTime-oldTime);
    
    cpuPos++;
    if(cpuPos>9) cpuPos=0;
    
    cpuTime[cpuPos]=timeCpu;
    
    actualTime=millis();
     
}

void ADDAC_SuperFormula::superformulaPoint(float m, float n1, float n2, float n3, float phi) {
    
    
    //ponto actual
    float r;
    float t1, t2;
    float a=1, b=1;
    x = 0;
    y = 0;
    int i =pos;
    n1=50;
    

    t1 = cos(m * (phi*(i)) / 4) / a;  
    t1 = fabs(t1-0);
    t1 = pow(t1, n2);
    
    t2 = sin(m * (phi*(i)) / 4) / b;
    t2 = fabs(t2);
    t2 = pow(t2, n3);
    
    r = pow(t1+t2, 1/n1);
    if (fabs(r) == 0) {
        x = 0;
        y = 0;
    }  
    else {
        r = 1 / r;
        x = r * cos((phi*(i)));
        y = r * sin((phi*(i)));
    }
       
    
    //MIN and MAX
    //max and min values checked on processing if n1 value set to 50 //???
    x=constrain(x,minValueX,maxValueX);
    y=constrain(y,minValueY,maxValueY);
    
    
    
    //ponto anterior
    //arranjar outra maneira de calcular ponto anterior!!!!!!!
    
    r = 0;
    t1 = 0;
    t2 = 0;
    oldX = 0;
    oldY = 0;
    i = pos-1;
   
    
    t1 = cos(m * (phi*(i)) / 4) / a;  
    t1 = fabs(t1-0);
    t1 = pow(t1, n2);
    
    t2 = sin(m * (phi*(i)) / 4) / b;
    t2 = fabs(t2);
    t2 = pow(t2, n3);
    
    r = pow(t1+t2, 1/n1);
    if (fabs(r) == 0) {
        oldX = 0;
        oldY = 0;
    }  
    else {
        r = 1 / r;
        oldX = r * cos((phi*(i)));
        oldY = r * sin((phi*(i)));
    }
    
    
    //MIN and MAX
    // max and min values checked on processing if n1 value set to 50 //???
    oldX=constrain(oldX,minValueX,maxValueX);
    oldY=constrain(oldY,minValueY,maxValueY);
        
      
}

float ADDAC_SuperFormula::getX(){

    float interpolationX = (((float)fabs(oldX-x)) / ((float)(metroTime)/(float)CPUtime()));
    
    if(oldX<x)oldX+=interpolationX;
    if(oldX>x)oldX-=interpolationX;

    
  
    //map max and min values checked on processing if n1 value set to 50 //???
    pX = mapfloat(oldX, minValueX, maxValueX, 0.0f, 1.0f);
    
    //??
    pX = constrain(pX,0.0f,1.0f);
    
    return pX;

}

float ADDAC_SuperFormula::getY(){
    
    float interpolationY = (((float)fabs(oldY-y)) / ((float)(metroTime)/(float)CPUtime()));
    
    if(oldY<y)oldY+=interpolationY;
    if(oldY>y)oldY-=interpolationY;

    
    // Serial.println(oldY);

    //map max and min values checked on processing if n1 value set to 50 //???
    pY=mapfloat(oldY,minValueY,maxValueY,0.0f,1.0f);
    
    //??
    pY=constrain(pY,0.0f,1.0f);
    
    return pY;

}



void ADDAC_SuperFormula::setLoopMax(int _max){

    numPoints=_max;


}


void ADDAC_SuperFormula::setLoopMin(int _min){
    
    loopMin=_min;
    
    
}

void ADDAC_SuperFormula::setMirror(bool _mirror){
    
    mirror=_mirror;
    
    
}



float ADDAC_SuperFormula::mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}


//CPU AVERAGE
float ADDAC_SuperFormula::CPUtime()
{
   

float timeAverage;

for(int i=0;i<9;i++){

    timeAverage+=cpuTime[i];
   
}

timeAverage/=10;

return timeAverage;
}

// --------------------------------------------------------------------------- END ----------------------------------
//