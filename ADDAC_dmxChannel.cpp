 #include "ADDAC_dmxChannel.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_dmxChannel::ADDAC_dmxChannel(int _channel){	// INITIALIZE CLASS
	
    channel = _channel;
    DMXstream = 0;
    actualValue = 0;
    StartUp=true;
    fadeInBang=false;
    fadeOutBang=false;
    strobeON=false;

	
}



// --------------------------------------------------------------------------- UPDATE ----------------------------------
//


void ADDAC_dmxChannel::update(){ // UPDATE DMXstream

    
    if (fadeInBang) {
        fadeInC();
      
    }

    if (fadeOutBang) {
        fadeOutC();
        
    }
    
    
    if (strobeON) {
        strobeC(strobeRateT);
    }

    
}
// --------------------------------------------------------------------------- calcs ----------------------------------
//


//fadeIn BANG
void ADDAC_dmxChannel::fadeIn(float _maxValue, long _time)
{
    maxValue = _maxValue;
    inTime =_time;
    memMillisIn=0;
    fadeInBang=true;
    fadeOutBang=false;
    strobeON=false;
   
    
}


//fadeOut BANG
void ADDAC_dmxChannel::fadeOut(float _minValue, long _time)
{
    minValue = _minValue;
    outTime =_time;
    memMillisOut=0;
    fadeOutBang=true; 
    fadeInBang=false;
    strobeON=false;
    
}

//fadeOut BANG
void ADDAC_dmxChannel::strobe(long _time)
{   
    
    strobeRateT=_time;
    strobeON=!strobeON;
    fadeInBang=false;
    fadeOutBang=false;
    DMXstream=0;
    Serial.println(strobeON);
}


//fadeIn CALCS
void ADDAC_dmxChannel::fadeInC()
{
    

    float diffIn = abs(actualValue - maxValue);
    float timeInterval = (float)inTime/(float)diffIn;
    
    
//    Serial.print("total -> ");
//    Serial.print(inTime);
//    
//    Serial.print(" timeInterval -> ");
//    Serial.print(timeInterval);
//
//    Serial.print(" soma -> ");
//    Serial.print(memMillisIn + timeInterval);
                 
//    Serial.print(" DMXstream -> ");
//    Serial.println(DMXstream);
//             
    
    if (DMXstream>=maxValue) {
        
        DMXstream = maxValue;
        actualValue=DMXstream;
        fadeInBang=false;
               
    }
    else if (memMillisIn + timeInterval < millis()) {
        memMillisIn=millis();
        DMXstream++;
    }


}



//fadeOut CALCS
void ADDAC_dmxChannel::fadeOutC()
{
    
    float diffOut = abs(actualValue - minValue);    
    float timeInterval = (float)outTime/(float)diffOut;
        
    
    if (DMXstream<=minValue) {
        
        DMXstream = minValue;
        actualValue=DMXstream;
        fadeOutBang=false;
        
    }
    
    else if (memMillisOut + timeInterval < millis()) {
        memMillisOut=millis();
        DMXstream--;
    }

}


void ADDAC_dmxChannel::strobeC(long _time){
    
    if (strobeRate.set(_time)) DMXstream = 255;
    else DMXstream = 0;    
    
}



