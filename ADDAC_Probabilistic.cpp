 
/*
 * SORT A RANDOM PROBABLISTIC VALUE
 *
*/


#include "ADDAC_Probabilistic.h"

//-----------------------------------------------------------------------ADDAC PROBABILISTIC-----------------

ADDAC_Probabilistic::ADDAC_Probabilistic(){	// INITIALIZE CLASS
    
    out1=false;
    out2=false;
    out3=false;
    out4=false;
    out5=false;  
    
    glideOn= false;
    
    randomResult=0;
    CVstream=0;
    startUp=true;
    
}

// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_Probabilistic::update(float _p1, float _p2, float _p3, float _p4, float _offSet){ // DO SOMETHING !
	    
    min1=0.0f; 
    max1=_p1+_offSet;
    
    if (max1>1.0f) max1-=1.0f;
    
    min2=max1;
    max2=mapfloat(_p2, 0.0f, 1.0f, max1, 1.0f);
    
    min3=max2;
    max3=mapfloat(_p3, 0.0f, 1.0f, max2, 1.0f);
    
    min4=max3;
    max4=mapfloat(_p4, 0.0f, 1.0f, max3, 1.0f);
    
    min5=max4;
    max5=1.0f;
    
    
    if(startUp){ 
        calc();
        startUp=false;
    }
    
    //update CVstream
    if (glideOn)  CVstream=glide();
    else CVstream = randomResult;
    
    CVstream = mapfloat(CVstream,0.0f,5.0f,0.0f,1.0f);

}

// --------------------------------------------------------------------------- CALC ----------------------------------
//


void ADDAC_Probabilistic::calc(){

    
    randomResultOld = actualPosition;
    //glideStream = randomResultOld;
    bangTimeOld = bangTime;
    inct=bangTimeOld;
    
    bangTime=millis();
    randomResult = random(0, 100);
    randomResult/=100.0f;

    
    int voltageA=0;
    
    if ((randomResult>min1 && randomResult<max1)) {
        voltageA=0;
        out1=true;
        out2=false;
        out3=false;
        out4=false;
        out5=false;

    }
    
    else if ((randomResult>min2 && randomResult<max2)) {
        voltageA= 1;
        out1=false;
        out2=true;
        out3=false;
        out4=false;
        out5=false;

    }
    
    else if ((randomResult>min3 && randomResult<max3)) {
        voltageA= 2;
        out1=false;
        out2=false;
        out3=true;
        out4=false;
        out5=false;

    }
    
    else if ((randomResult>min4 && randomResult<max4)) {
        voltageA= 3;
        out1=false;
        out2=false;
        out3=false;
        out4=true;
        out5=false;

    }
    
    else if (randomResult>min5 && randomResult<max5) {
        voltageA= 4;
        out1=false;
        out2=false;
        out3=false;
        out4=false;
        out5=true;

    }
    
    randomResult += voltageA;

}


// --------------------------------------------------------------------------- GLIDE CALCS ----------------------------------
//


float ADDAC_Probabilistic::glide() {
    
    diffTime = abs(bangTimeOld - bangTime);
    
    
    long inct=(long)constrain(millis()-diffTime,bangTimeOld,bangTime);
    
    glideStream=mapfloat(inct,bangTimeOld,bangTime,randomResultOld,randomResult);
    
    actualPosition=glideStream;
    
    return glideStream;
}


// --------------------------------------------------------------------------- GLIDE SET ON/OFF ----------------------------------
//


void ADDAC_Probabilistic::setGlide(bool _state){

    glideOn=_state;

}


// --------------------------------------------------------------------------- GLIDE SWITCH STATE ----------------------------------
//


void ADDAC_Probabilistic::switchGlide(){
    
    glideOn=!glideOn;
    
}


// --------------------------------------------------------------------------- FLOAT MAPPING ----------------------------------
//


float ADDAC_Probabilistic::mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
