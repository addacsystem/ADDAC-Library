 

#include "ADDAC_Quad.h"


//-----------------------------------------------------------------------ADDAC-----------------

ADDAC_Quad::ADDAC_Quad(){	
    
    x1 = 256;
    y1 = 256;
    x2 = 784;
    y2 = 256;
    x4 = 256;
    y4 = 784;
    x3 = 784;
    y3 = 784;
    
    //dMax = 1023 + sqrt((256 - 512.0f)*(256.0f - 512.0f) + (256.0f - 512.0f)*(256.0f - 512.0f));
    dMax = 2*sqrt((256 - 512.0f)*(256.0f - 512.0f) + (256.0f - 512.0f)*(256.0f - 512.0f));
    dMaxPower = 512;
    
    rSpeaker = sqrt((x1 - 512.0f)*(x1 - 512.0f) + (y1 - 512.0f)*(y1 - 512.0f));
    
    r = dMax/1.8;
    theta = 0;
    
    xAbs=0;
    yAbs=0;
	//Serial.println("QUAD COMPLETE");
}


// --------------------------------------------------------------------------- UPDATE -------------------------
//

void ADDAC_Quad::calcs(int MODE, float _r, float _theta, float _free1,float _free2,float _free3) {
    //theta = _theta*360.0f/512.0f; por causa do CVinput manhoso tem q usar 512
    
    theta = _theta*360.0f/_free1;
    theta = theta*3.14f/180.0f;
    
    if(MODE == 0){ // POLAR
        x = _r*cos(theta) + 512.0f;
        y = _r*sin(theta) + 512.0f;
    }else{ // CARTESIAN
        x = (_r/1023.0f)* 2.0f * 1535 - 1535.0f;
        y = (_theta/1023.0f)* 2.0f * 1535 - 1535.0f;
    }
    
    
    amp1 = sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y))/dMax;
    amp1 = pow(amp1, _free2/512.0f);
    amp1 = 1 - amp1;
    amp1*=addacMaxResolution;///?
    if(amp1<0.0f)amp1=0;
    
    amp2 = sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y))/dMax;
    amp2 = pow(amp2, _free2/512.0f);
    amp2 = 1 - amp2;
    amp2*=addacMaxResolution;///?
    if(amp2<0.0f)amp2=0;
    amp3 = sqrt((x3 - x)*(x3 - x) + (y3 - y)*(y3 - y))/dMax;
    amp3 = pow(amp3, _free2/512.0f);
    amp3 = 1 - amp3;
    amp3*=addacMaxResolution;///?
    if(amp3<0.0f)amp3=0;
    amp4 = sqrt((x4 - x)*(x4 - x) + (y4 - y)*(y4 - y))/dMax;
    amp4 = pow(amp4, _free2/512.0f);
    amp4 = 1 - amp4;
    amp4*=addacMaxResolution;///?
    if(amp4<0.0f)amp4=0;
    
    xAbs = map(x,-1535.0f,1535.0f,0,addacMaxResolution);
    yAbs = map(y,-1535.0f,1535.0f,0,addacMaxResolution);
   
	if(_r >= rSpeaker){
        filterFreq = 1.0f - pow(((_r - rSpeaker)/128.0f), _free3/512.0f);
    }else{
        filterFreq = 1.0f;
    }
    
    if(filterFreq < 0.0f){
        filterFreq = 0.0;
    }
    
	//AMPS ENTRE 0.0f e 1.0f  - passar para * addacMaxResolution;
    
    
}

// --------------------------------------------------------------------------- RETURNS -------------------------
//


// --------------------------------------------------------------------------- END ----------------------------------
//