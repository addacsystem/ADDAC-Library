 
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

void ADDAC_AD::update(float _Atime, float _Dtime){ //  a:ATTACK TIME  |  b:DECAY TIME    in millis
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

//OTHER METHODS

/*! \brief Trigger AD with defined ATTACK amplitude
 \param _A  ATTACK amplitude
 */

void ADDAC_AD::trigger(float _A){ // a:VELOCITY PERCENTAGE 0.0f & 1.0f for notes on
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
void ADDAC_AD::trigger(){ // FULL VELOCITY PERCENTAGE 1.0f for ADSR
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
void ADDAC_AD::release(){
	SUSTAIN = false;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
    
#ifdef DEBUG_adsr
    Serial.println("  --  ADSR RELEASE");
#endif
}

// --------------------------------------------------------------------------- END ----------------------------------
//