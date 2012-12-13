 

#include "ADDAC_Quad.h"


//-----------------------------------------------------------------------ADDAC-----------------
/*! \brief Default constructor for ADDAC_Quad. */
ADDAC_Quad::ADDAC_Quad(){
	
    thetaA=0;
    
    x1 = 0.25f;
    y1 = 0.25f;
    x2 = 0.75f;
    y2 = 0.25f;
    x4 = 0.25f;
    y4 = 0.75f;
    x3 = 0.75f;
    y3 = 0.75f;
    
    //dMax = 1023 + sqrt((256 - 512.0f)*(256.0f - 512.0f) + (256.0f - 512.0f)*(256.0f - 512.0f));
    //dMax = 2*sqrt((0.25f - 0.5f)*(0.25f - 0.5f) + (0.25f - 0.5f)*(0.25f - 0.5f));
     dMax=0.5;
    dMaxPower = 0.5f;
    
    rSpeaker = sqrt((x1 - 0.5f)*(x1 - 0.5f) + (y1 - 0.5f)*(y1 - 0.5f));
    
    //r = dMax/1.8;
    theta = 0;
    
    xAbs=0;
    yAbs=0;
    
    oldTheta = theta;
    thetaUP=false;
    
    
    WRAPmode=false;
	//Serial.println("QUAD COMPLETE");
}


// --------------------------------------------------------------------------- UPDATE -------------------------
//
/*! \brief calculate Quad Spatialization
 \param _MODE if false-> CARTESIAN Mode | if true-> POLAR Mode
 \param _WRAPmode if false-> Absolute Mode | if true-> Continuos Mode
 \param _r Radius/X
 \param _theta Angle/Y
 \param _free1 OFFSET
 \param _free2 Spatialization Curve
 \param _free3 Filter Curve
 */
void ADDAC_Quad::calc(bool _MODE, bool _WRAPmode, float _r, float _theta, float _free1, float _free2, float _free3) {
    
    WRAPmode=_WRAPmode;
    MODE=_MODE;
    
    
    // MAPPINGS DA CURVA PARA SER SIMETRICO entre LOG e EXP
    // CENTRO DO BUTAO = LINEAR
    // < CENTRO = LOG
    // > CENTRO = EXP
    if (_free2< 0.5f) {
        _free2 = _free2*2.0f *0.7 +0.3f; // 0.3 -> 1.0
    }
    else {
        _free2 = (_free2 - 0.5f) *2.0f *2.3f + 1.0f; // 1.0 -> 3.3
    }
    
    
    // CURVA DO FILTRO
    if (_free3< 0.5f) {
        _free3 = _free3*2.0f *0.7 +0.3f;  // 0.3 -> 1.0
    }
    else {
        _free3 = (_free3 - 0.5f) *2.0f *2.3f + 1.0f; // 1.0 -> 3.3
    }
    
    theta = _theta*360.0f; //*(_free1*4+1);
    
    //print(" Theta:"+theta);
    if (WRAPmode && MODE==true) { //  !MODE  --->> MODE>0       
        diff = (abs(theta-oldTheta));
        oldTheta=theta;
        //print("  Diff:"+diff);
        
        thetaA += diff;    
        //println(" Theta+Diff:"+thetaA);
        theta = thetaA+_free1*360;
    }
    else
    {
        theta = theta+_free1*360;
    }
    
    
    
    
    //      diff=abs(oldAngle-theta);
    //      println(diff/360);
    //      oldAngle=theta;
    
    //coloca offset no final
    //theta = thetaA+_free1*360;
    
    // ADICIONAR FREE1, para multiplicar angulo! ??? not needed anymore!?
    float thetaR = theta*PI/180.0f;
    
    
    
    if (MODE == true) { // POLAR
        _r/=2;//???<---------------------------------------
        
        x = _r*cos(thetaR) + 0.5f;// + 512.0f;
        y = _r*sin(thetaR) + 0.5f;// + 512.0f;
    }
    else { // CARTESIAN
        x = (_r);//* 2.0f * 1535.0f - 1535.0f;
        y = (_theta);//* 2.0f * 1535.0f - 1535.0f;
    }
    
    
    amp1 = sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y))/dMax;
    amp1 = pow(amp1, _free2);
    amp1 = 1 - amp1;
    //amp1*=addacMaxResolution;///?
    if (amp1<0.0f)amp1=0;
    
    amp2 = sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y))/dMax;
    amp2 = pow(amp2, _free2);
    amp2 = 1 - amp2;
    //amp2*=addacMaxResolution;///?
    
    if (amp2<0.0f)amp2=0;
    amp3 = sqrt((x3 - x)*(x3 - x) + (y3 - y)*(y3 - y))/dMax;
    amp3 = pow(amp3, _free2);
    amp3 = 1 - amp3;
    //amp3*=addacMaxResolution;///?
    
    if (amp3<0.0f)amp3=0;
    amp4 = sqrt((x4 - x)*(x4 - x) + (y4 - y)*(y4 - y))/dMax;
    amp4 = pow(amp4, _free2);
    amp4 = 1 - amp4;
    //amp4*=addacMaxResolution;///?
    if (amp4<0.0f)amp4=0;
    
    
    xAbs = constrain(x, 0.0f, 1.0f);// / 3070.0f + 0.5f;/// 3070.0fmap(x, -1535.0f, 1535.0f, 0.0f, 1.0f);
    yAbs = constrain(y, 0.0f, 1.0f);// / 3070.0f + 0.5f;//map(y, -1535.0f, 1535.0f, 0.0f, 1.0f);
    
    
    if (_r >= rSpeaker) {
        filterFreq = 1.0f - (_r - rSpeaker)/0.65f;
        //        print(" FILTERpre:");
        //        print(filterFreq);
        filterFreq = pow( filterFreq, _free3);
    }
    else {
        filterFreq = 1.0f;
    }
    
    if (filterFreq < 0.0f) {
        filterFreq = 0.0;
    }
    //    print(" FILTERpost:");
    //    print(filterFreq);
    //   print(" SKR:");
    //    print(rSpeaker);
}
    
   


// --------------------------------------------------------------------------- RETURNS -------------------------
//


// --------------------------------------------------------------------------- END ----------------------------------
//