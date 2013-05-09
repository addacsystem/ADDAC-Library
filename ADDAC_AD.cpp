
/*
 * Some hints about what this Class does!
 *
 */


#include "ADDAC_AD.h"

//-----------------------------------------------------------------------ADDAC AD-----------------

/*! \brief Default construtor for ADDAC_AD */
ADDAC_AD::ADDAC_AD(){	// INITIALIZE CLASS
    
    
	//Serial.println("ADDAC_AD INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief update AD ATTACK time and DECAY time
 \param _Atime  ATTACK Time
 \param _Dtime  DECAY Time
 */

void ADDAC_AD::updateLin(bool _gate, float _Atime, float _Dtime){ //  a:ATTACK TIME  |  b:DECAY TIME    in millis
    
    float _A=1;
    float _D=0;
    float _Ashape=0.5;
    float _Dshape=0.5;
    
    if(_gate && !ADSRtrigger){
        
        trigger();
        
        
    }
    else if(!_gate && ADSRtrigger){
        release();
        
    }
    
    
    
    
    if(millis()<=ADSRtriggerTime+_Atime && SUSTAIN && ADSRtrigger){
        // A
        
        float _actualPos = (millis()-ADSRtriggerTime)/_Atime;
        //CVstream = (lastPosD+(pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A )))-lastPosD;
        CVstream = lastPosD+(pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A-lastPosD ));
        
        lastPosA=CVstream;
        
        
        
    }else if(millis()<=ADSRtriggerTime+_Dtime && !SUSTAIN && !ADSRtrigger){
        // D
        
        float _actualPos = (millis()-ADSRtriggerTime)/_Dtime;
        
        //CVstream = lastPos-(pow(_actualPos, exp(_Dshape*4.0f-2)) *lastPos );
        CVstream = (-(1-_D-(1-lastPosA))*pow(_actualPos, exp(_Dshape*4.0f-2)) +lastPosA);
        
        lastPosD=CVstream;
        
    }
    else if(SUSTAIN && ADSRtrigger){
        
        holdTime=millis()-(ADSRtriggerTime+_Atime);
        
        
    }
    //        float maxV=ADSRtriggerTime+_Atime+holdTime;
    //        float minV=ADSRtriggerTime+_Atime+_Dtime+holdTime;
    //        Serial.print(minV);
    //        Serial.print("> ");
    //        Serial.print(millis());
    //        Serial.print("> ");
    //        Serial.print(maxV);
    //        Serial.print("  |  +holdTime: ");
    //        Serial.println(millis()+holdTime);
      
}






void ADDAC_AD::updateLogExpMode(float _A, float _Atime, float _Ashape, float _Dtime, float _Dshape){
    
    float _D=0;
    
    
    
    if(millis()<=ADSRtriggerTime+_Atime && SUSTAIN && ADSRtrigger){
        // A
        
        float _actualPos = (millis()-ADSRtriggerTime)/_Atime;
        //CVstream = (lastPosD+(pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A )))-lastPosD;
        CVstream = lastPosD+(pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A-lastPosD ));
        
        lastPosA=CVstream;
        
        
        
    }else if(millis()<=ADSRtriggerTime+_Dtime && !SUSTAIN && !ADSRtrigger){
        // D
        
        float _actualPos = (millis()-ADSRtriggerTime)/_Dtime;
        
        //CVstream = lastPos-(pow(_actualPos, exp(_Dshape*4.0f-2)) *lastPos );
        CVstream = (-(1-_D-(1-lastPosA))*pow(_actualPos, exp(_Dshape*4.0f-2)) +lastPosA);
        
        lastPosD=CVstream;
        
    }
    else if(SUSTAIN && ADSRtrigger){
        
        holdTime=millis()-(ADSRtriggerTime+_Atime);
        
        
    }
    //        float maxV=ADSRtriggerTime+_Atime+holdTime;
    //        float minV=ADSRtriggerTime+_Atime+_Dtime+holdTime;
    //        Serial.print(minV);
    //        Serial.print("> ");
    //        Serial.print(millis());
    //        Serial.print("> ");
    //        Serial.print(maxV);
    //        Serial.print("  |  +holdTime: ");
    //        Serial.println(millis()+holdTime);
    
}







void ADDAC_AD::updateLogExpMode(bool _gate, float _A, float _Atime, float _Ashape, float _Dtime, float _Dshape){
    
    float _D=0;
    
    if(_gate && !ADSRtrigger){
        
        trigger();
        
        
    }
    else if(!_gate && ADSRtrigger){
        release();
        
    }
    
    
    
    
    if(millis()<=ADSRtriggerTime+_Atime && SUSTAIN && ADSRtrigger){
        // A
        
        float _actualPos = (millis()-ADSRtriggerTime)/_Atime;
        //CVstream = (lastPosD+(pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A )))-lastPosD;
        CVstream = lastPosD+(pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A-lastPosD ));
        
        lastPosA=CVstream;
        
        
        
    }else if(millis()<=ADSRtriggerTime+_Dtime && !SUSTAIN && !ADSRtrigger){
        // D
        
        float _actualPos = (millis()-ADSRtriggerTime)/_Dtime;
        
        //CVstream = lastPos-(pow(_actualPos, exp(_Dshape*4.0f-2)) *lastPos );
        CVstream = (-(1-_D-(1-lastPosA))*pow(_actualPos, exp(_Dshape*4.0f-2)) +lastPosA);
        
        lastPosD=CVstream;
        
    }
    else if(SUSTAIN && ADSRtrigger){
        
        holdTime=millis()-(ADSRtriggerTime+_Atime);
        
        
    }
    //        float maxV=ADSRtriggerTime+_Atime+holdTime;
    //        float minV=ADSRtriggerTime+_Atime+_Dtime+holdTime;
    //        Serial.print(minV);
    //        Serial.print("> ");
    //        Serial.print(millis());
    //        Serial.print("> ");
    //        Serial.print(maxV);
    //        Serial.print("  |  +holdTime: ");
    //        Serial.println(millis()+holdTime);
    
}



//OTHER METHODS



/*! \brief Trigger AD with default
 */
void ADDAC_AD::trigger(){ // FULL VELOCITY PERCENTAGE 1.0f for ADSR
    
	ADSRtrigger=true;
	SUSTAIN = true;
    holdTime=0;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
    
	
#ifdef DEBUG_adsr
    Serial.println("  -- ADSR TRIGGER");
#endif
}

/*! \brief Release AD
 */
void ADDAC_AD::release(){
    ADSRtrigger=false;
	SUSTAIN = false;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
    
#ifdef DEBUG_adsr
    Serial.println("  --  ADSR RELEASE");
#endif
}

// --------------------------------------------------------------------------- END ----------------------------------
//