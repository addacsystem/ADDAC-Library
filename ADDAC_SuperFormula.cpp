/*
 * Some hints about what this Class does!
 *
 */


#include "ADDAC_SuperFormula.h"

//-----------------------------------------------------------------------ADDAC SuperFormula-----------------
/*! \brief Default constructor for ADDAC_SuperFormula. */
ADDAC_SuperFormula::ADDAC_SuperFormula(){	// INITIALIZE CLASS
	
    pos=0;
    pX=0;
    pY=0;
    numPoints = 360;
    loopMin=0;
    inc=1;
	mirror = false;
    startUp=true;
	//Serial.println("ADDAC_SuperFormula INITIALIZED");
}




// --------------------------------------------------------------------------- UPDATE -------------------------
//


/*! \brief update SuperFormula calcs
 \param m Superformula number of petals : 0 - 1
 \param n2 Superformula shape variable 1 : 0 - 1
 \param n3 Superformula shape variable 2 : 0 - 1 
 \param _speed Superformula speed calculation
 */
// newValue - value to smooth, smoothFactor - smooth intensity 0-1.
void ADDAC_SuperFormula::update(float m, float n2, float n3, long _speed) {
    
    long oldTime=millis();
    m*=1000.0f;
    m*2;
    n2*=100.0f;
    n3*=100.0f;
    //values checked on processing for default min and max values//
    n2=constrain(n2,0,100);
    n3=constrain(n3,0,100);
    n2=mapfloat(n2,0,100,-50,100);
    n3=mapfloat(n3,0,100,-50,100);
    ///////////////////////////////////////////////////////////////
    
    float phi = TWO_PI / 360;
    if(startUp){ 
        metroTime=1;
        startUp=false;
        
    }
    else metroTime=_speed;
    
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
        
        oldPos=pos;
        superformulaPoint(m, n2, n3, phi);
    }
    
    long timeCpu=fabs(actualTime-oldTime);
    
    cpuPos++;
    if(cpuPos>9) cpuPos=0;
    
    cpuTime[cpuPos]=timeCpu;
    
    actualTime=millis();
    
}

void ADDAC_SuperFormula::superformulaPoint(float m, float n2, float n3, float phi) {
    
  
    //actual Point
    float r;
    float t1, t2;
    float a=1, b=1;
    x = 0;
    y = 0;
    int i =pos;
    float n1=50;
    
    
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
    

   float difX=(float)fabs(oldX-x);
   float difY=(float)fabs(oldY-y);
    
   interpolationX = difX / ((float)(metroTime+CPUtime())/(float)CPUtime());
   interpolationY = difY / ((float)(metroTime+CPUtime())/(float)CPUtime());
    
}


/*! \Get SuperFormula X position Stream
 */

float ADDAC_SuperFormula::getX(){

    if(oldX<=x)oldX+=interpolationX;
    if(oldX>=x)oldX-=interpolationX;
   
    
    
    //map max and min values checked on processing if n1 value set to 50 //???
    pX = mapfloat(oldX, minValueX, maxValueX, 0.0f, 1.0f);
    pX = constrain(pX,0.0f,1.0f);
    
//    Serial.print("OldX : ");
//    Serial.print(oldX);
//    Serial.print(" X : ");
//    Serial.print(x);
//    Serial.print(" interpolationX : ");
//    Serial.print(interpolationX);
    
    return pX;
    
}

/*! \Get SuperFormula Y position Stream
 */

float ADDAC_SuperFormula::getY(){
   
    if(oldY<=y)oldY+=interpolationY;
    if(oldY>=y)oldY-=interpolationY;
    
    
    //map max and min values checked on processing if n1 value set to 50 //???
    pY=mapfloat(oldY,minValueY,maxValueY,0.0f,1.0f);
    pY=constrain(pY,0.0f,1.0f);
    
    
//    Serial.print("OldY : ");
//    Serial.print(oldY);
//    Serial.print(" Y : ");
//    Serial.print(y);
//    Serial.print(" interpolationY : ");
//    Serial.print(interpolationY,DEC);
    
    return pY;
    
}



/*! \Set the loop Max value
  \param _max max value of the loop : 0 - 360 | Default 360
 */

void ADDAC_SuperFormula::setLoopMax(int _max){
    
    numPoints=_max;
    
    
}


/*! \Set the loop Min value
 \param _min min value of the loop : 0 - 360 | Defalut 0
 */
void ADDAC_SuperFormula::setLoopMin(int _min){
    
    loopMin=_min;
    
    
}

/*! \Turn On/Off the PingPong Mode | Default false
 \param _max max value of the loop : 0 - 360
 */
void ADDAC_SuperFormula::setPingPongMode(bool _mirror){
    
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