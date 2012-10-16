 
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
   
    float phi = TWO_PI / 360;
    
   if(metro.set(_time)){
    pos++;
    if(pos>numPoints-1) pos = loopMin;
       
       superformulaPoint(m, n1, n2, n3, phi);
       
        Serial.print("pos: ");
        Serial.print(pos);
        Serial.print("min: ");
        Serial.print(loopMin);
        Serial.print("max");
       Serial.print(numPoints);
      
 }
     
}

void ADDAC_SuperFormula::superformulaPoint(float m, float n1, float n2, float n3, float phi) {
    
    float r;
    float t1, t2;
    float a=1, b=1;
    float x = 0;
    float y = 0;
    int i =pos;
    
    n1=50;
   // for (int i = 0; i<numPoints-1; i++) {
        
    
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
    
    //???
    x=constrain(x,-1.6999406,1.6999406);
    y=constrain(y,-1.6999406,1.6999406);

    
    //map max and min values checked on processing if n1 value set to 50 //????
      pX=mapfloat(x,-1.6999406,1.6999406,0.0f,1.0f);
      pY=mapfloat(y,-1.6999406,1.6999406,0.0f,1.0f);
    
    //pointX[i]=x;
    //pointY[i]=y;
        
   // }
}

float ADDAC_SuperFormula::getX(){
    
//   float Xpos = mapfloat(pointX[pos],minValueX,maxValueX,0.0f,1.0f);
//   return Xpos;

}

float ADDAC_SuperFormula::getY(){
    
//    float Ypos = mapfloat(pointY[pos],minValueY,maxValueY,0.0f,1.0f);
//    return Ypos;
}

///min/max

void ADDAC_SuperFormula::getMinMax(){
    
    
//    minValueX=pointX[0];
//    maxValueX=pointX[0];
//    
//    minValueY=pointY[0];
//    maxValueY=pointY[0];
//    
//    for (int i = 0; i<numPoints-1; i++) {
//        
//        if (pointX[i]<minValueX) minValueX=pointX[i];
//        if (pointX[i]>maxValueX) maxValueX=pointX[i];
//        
//        if (pointY[i]<minValueY) minValueY=pointY[i];
//        if (pointY[i]>maxValueY) maxValueY=pointY[i];
//    }
//    
//    
}


void ADDAC_SuperFormula::setLoopMax(int _max){

    numPoints=_max;


}


void ADDAC_SuperFormula::setLoopMin(int _min){
    
    loopMin=_min;
    
    
}



float ADDAC_SuperFormula::mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}





// --------------------------------------------------------------------------- END ----------------------------------
//