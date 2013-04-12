 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_ADLogExp.h"

//-----------------------------------------------------------------------ADDAC AD-----------------

/*! \brief Default construtor for ADDAC_ADLogExp */
ADDAC_ADLogExp::ADDAC_ADLogExp(){	// INITIALIZE CLASS

    
	//Serial.println("ADDAC_ADLogExp INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief update AD ATTACK time and DECAY time
 \param _Atime  ATTACK Time
 \param _Dtime  DECAY Time
 */

void ADDAC_ADLogExp::update(float _Atime, float _Dtime){ //  a:ATTACK TIME  |  b:DECAY TIME    in millis
	if(millis()<=ADSRtriggerTime+_Atime && SUSTAIN){
        
		// A
		float TipPointF = TipPoint;
		float difference, weakLink;
		if (TipPointF>Attack) {
			difference = TipPointF - Attack;
			weakLink=Attack;
		}else {
			difference = Attack - TipPointF;
			weakLink=TipPoint;
		}
		
		float _floatPercentage = difference;
		float _actualPos = _Atime-(ADSRtriggerTime+_Atime-millis());
		CVstream = _actualPos / _Atime * _floatPercentage + weakLink;
        
#ifdef DEBUG_adsr
        Serial.print("  --  perc:");
        Serial.print(_floatPercentage);
        Serial.print("  -- pos:");
        Serial.print(_actualPos);
        Serial.print("  --  Going Up:");
        Serial.println(CVstream);
#endif
	}else if(millis()<=ADSRtriggerTime+_Dtime && !SUSTAIN && ADSRtrigger){ 
		// D
		float _actualPos = ADSRtriggerTime+_Dtime-millis();
		CVstream = _actualPos / _Dtime * TipPoint;
		
#ifdef DEBUG_adsr
        Serial.print("  --  Going Down:");
        Serial.println(CVstream);
#endif
		
	}else if(!SUSTAIN){
		CVstream = 0;
		ADSRtrigger=false;
	}
	
}






void ADDAC_ADLogExp::updateLogExpMode(bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _Dtime, float _Dshape){
    
    float _D=0;
    
	if(_trigger && !ADSRtrigger){
		ADSRtrigger=true;
		ADSRtriggerTime=millis();
		CVstream=0;
	}
	//unsigned int toAddDif;
	if(!_inverted){ // normal
		if(millis()<=ADSRtriggerTime+_Atime){
			// A
			float _actualPos = (millis()-ADSRtriggerTime)/_Atime;
			CVstream = (pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A ));
			
            
            
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){
			// D

			float _actualPos = (millis()-ADSRtriggerTime-_Atime)/_Dtime;
			CVstream = (-(1-_D-(1-_A))*pow(_actualPos, exp(_Dshape*4.0f-2)) +_A);
			
		}else{
			ADSRtrigger=false;
			CVstream=0;
		}
	}
    
    
    
    
    else{ // inverted
		if(millis()<=ADSRtriggerTime+_Atime){
			// A
			
			float _floatPercentage = _A;
			float _actualPos = (ADSRtriggerTime+_Atime-millis());
			toAddDif = (_A/100.0f-1)*-1.0f;
			CVstream = (_actualPos / _Atime * _floatPercentage+toAddDif);
            Serial.print("A - ");
            Serial.print(CVstream);
			
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){
			// D
			
			float _actualPos;
			float percentageDif = (_A - _D); // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f ;
				toAddDif = (100 - _D) / 100.0f ;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime-millis());
			}else{
				percentageDif = percentageDif ;
				toAddDif = (100 - _A) / 100.0f ;
				_actualPos = _Dtime-(ADSRtriggerTime+_Atime+_Dtime-millis());
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif);
            Serial.print("D - ");
            Serial.print(CVstream);

			
		}else{
			ADSRtrigger=false;
			CVstream=1;
		}
	}
}







//OTHER METHODS

/*! \brief Trigger AD with defined ATTACK amplitude
 \param _A  ATTACK amplitude
 */

void ADDAC_ADLogExp::trigger(float _A){ // a:VELOCITY PERCENTAGE 0.0f & 1.0f for notes on
	Attack = _A;
	ADSRtrigger = true;
	SUSTAIN = true;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
    
#ifdef DEBUG_adsr
    Serial.println("  -- ADSR TRIGGER");
#endif
}

/*! \brief Trigger AD with default MAX ATTACK amplitude (1.0)
 */
void ADDAC_ADLogExp::trigger(){ // FULL VELOCITY PERCENTAGE 1.0f for ADSR
	Attack = 1.0f;
	ADSRtrigger=true;
	SUSTAIN = true;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
	
#ifdef DEBUG_adsr
    Serial.println("  -- ADSR TRIGGER");
#endif
}

/*! \brief Release AD
 */
void ADDAC_ADLogExp::release(){
	SUSTAIN = false;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
    
#ifdef DEBUG_adsr
    Serial.println("  --  ADSR RELEASE");
#endif
}

// --------------------------------------------------------------------------- END ----------------------------------
//