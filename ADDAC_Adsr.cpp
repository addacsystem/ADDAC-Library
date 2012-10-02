

#include "ADDAC_Adsr.h"

//-----------------------------------------------------------------------ADDAC-----------------
/*! \brief Default construtor for ADDAC_ADSR */
ADDAC_Adsr::ADDAC_Adsr(){	
	
	CVstream = 0;
	//Serial.println("ADDAC_Adsr INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


// --------------------------------------- LINEAR ADSR MODE --- OLD CLASS -> (to be deleted ...) ----------------------
//
//int _channel (1-8), bool _trigger (0=no - 1=yes), bool _inverted (0=no - 1=yes) 
//float _A (percentage (0-100% = 0.0f to 1.0f), float _Atime (millis)

// ADD top and bottom offset??

/*! \brief update ADSR values - Attack will be max voltage
 \param _trigger  trigger ADSR : true or false
 \param _inverted invert ADSR : true or false
 \param _Atime ADSR Attack time
 \param _D ADSR Decay amplitude
 \param _Dtime ADSR Decay time
 \param _Stime ADSR Sustain time
 \param _Rtime ADSR Release time
 */
void ADDAC_Adsr::update(bool _trigger, bool _inverted, float _Atime, float _D, float _Dtime, float _Stime, float _Rtime){
	if(_trigger && !ADSRtrigger){
		ADSRtrigger=true;
		ADSRtriggerTime=millis();
		CVstream=0.0;
	}
    float _A=1.0f;
    float _S=_D;
	//unsigned int toAddDif;
	if(!_inverted){ // normal
		if(millis()<=ADSRtriggerTime+_Atime){ 
			// A
			float _floatPercentage = _A;
			float _actualPos = _Atime-(ADSRtriggerTime+_Atime-millis());
			CVstream = (_actualPos / _Atime * _floatPercentage);		
			
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){ 
			// D
			float _actualPos;
			float percentageDif = (_A - _D) * addacMaxResolution; // intervalo
      
			if(percentageDif<0){
				percentageDif = percentageDif*-1.0f;
				toAddDif = _A*addacMaxResolution;
				_actualPos = _Dtime-(ADSRtriggerTime+_Atime+_Dtime-millis());
			}else{
				toAddDif = _D*addacMaxResolution;
				_actualPos = ADSRtriggerTime+_Atime+_Dtime-millis();
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos;
			long percentageDif = (_D - _S) * addacMaxResolution; // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif*-1.0f;
				toAddDif = _D*addacMaxResolution;
				_actualPos = _Stime-(ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}else{
				toAddDif = _S*addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}
			CVstream = (_actualPos / _Stime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime+_Stime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			unsigned int percentageDif = _S * addacMaxResolution; // intervalo
			float _actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime-millis());
			CVstream = (_actualPos / _Rtime * percentageDif)/addacMaxResolution;
			
		}else{
			ADSRtrigger=false;
			CVstream=0;
		}
	}else{ // inverted
		if(millis()<=ADSRtriggerTime+_Atime){ 
			// A
			float _floatPercentage = _A * addacMaxResolution;
			float _actualPos = (ADSRtriggerTime+_Atime-millis());
			toAddDif = (_A-1)*-1.0f*addacMaxResolution;
			CVstream =(_actualPos / _Atime * _floatPercentage+toAddDif)/addacMaxResolution;		
			
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){ 
			// D
			float _actualPos;
			float percentageDif = (_A - _D); // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (1 - _D) * addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (1 - _A) * addacMaxResolution;
				_actualPos = _Dtime-(ADSRtriggerTime+_Atime+_Dtime-millis());
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos;
			float percentageDif = (_D - _S); // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (1 - _S) * addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (1 - _D) * addacMaxResolution;
				_actualPos = _Stime-(ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}
			CVstream =(_actualPos / _Stime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime+_Stime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			float percentageDif = _S * addacMaxResolution; // intervalo
			float _actualPos = _Rtime-(ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime-millis());
			float toAddDif = (_S-1)*-1.0f*addacMaxResolution;
			CVstream = (_actualPos / _Rtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else{
			ADSRtrigger=false;
			CVstream=addacMaxResolution/addacMaxResolution;
		}
	}
}


/*! \brief update ADSR values
 \param _trigger  trigger ADSR : true or false
 \param _inverted invert ADSR : true or false
 \param _A ADSR Attack to amplitude
 \param _Atime ADSR Attack time
 \param _D ADSR Decay to amplitude
 \param _Dtime ADSR Decay time
 \param _Stime ADSR Sustain time
 \param _Rtime ADSR Release time
 */

void ADDAC_Adsr::update(bool _trigger, bool _inverted,float _A, float _Atime, float _D, float _Dtime, float _Stime, float _Rtime){
	if(_trigger && !ADSRtrigger){
		ADSRtrigger=true;
		ADSRtriggerTime=millis();
		CVstream=0;
	}
    
    float _S=_D;
	//unsigned int toAddDif;
	if(!_inverted){ // normal
		if(millis()<=ADSRtriggerTime+_Atime){ 
			// A
			float _floatPercentage = _A * addacMaxResolution;
			float _actualPos = _Atime-(ADSRtriggerTime+_Atime-millis());
			CVstream = (_actualPos / _Atime * _floatPercentage)/addacMaxResolution;		
			
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){ 
			// D
			float _actualPos;
			long percentageDif = (_A - _D) * addacMaxResolution; // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif*-1.0f;
				toAddDif = _A*addacMaxResolution;
				_actualPos = _Dtime-(ADSRtriggerTime+_Atime+_Dtime-millis());
			}else{
				toAddDif = _D*addacMaxResolution;
				_actualPos = ADSRtriggerTime+_Atime+_Dtime-millis();
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos;
			long percentageDif = (_D - _S) * addacMaxResolution; // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif*-1.0f;
				toAddDif = _D*addacMaxResolution;
				_actualPos = _Stime-(ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}else{
				toAddDif = _S*addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}
			CVstream = (_actualPos / _Stime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime+_Stime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			unsigned int percentageDif = _S * addacMaxResolution; // intervalo
			float _actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime-millis());
			CVstream = (_actualPos / _Rtime * percentageDif)/addacMaxResolution;
			
		}else{
			ADSRtrigger=false;
			CVstream=0;
		}
	}else{ // inverted
		if(millis()<=ADSRtriggerTime+_Atime){ 
			// A
			float _floatPercentage = _A * addacMaxResolution;
			float _actualPos = (ADSRtriggerTime+_Atime-millis());
			toAddDif = (_A-1)*-1.0f*addacMaxResolution;
			CVstream =(_actualPos / _Atime * _floatPercentage+toAddDif)/addacMaxResolution;		
			
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){ 
			// D
			float _actualPos;
			float percentageDif = (_A - _D); // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (1 - _D) * addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (1 - _A) * addacMaxResolution;
				_actualPos = _Dtime-(ADSRtriggerTime+_Atime+_Dtime-millis());
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos;
			float percentageDif = (_D - _S); // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (1 - _S) * addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (1 - _D) * addacMaxResolution;
				_actualPos = _Stime-(ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}
			CVstream =(_actualPos / _Stime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime+_Stime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			float percentageDif = _S * addacMaxResolution; // intervalo
			float _actualPos = _Rtime-(ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime-millis());
			float toAddDif = (_S-1)*-1.0f*addacMaxResolution;
			CVstream = (_actualPos / _Rtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else{
			ADSRtrigger=false;
			CVstream=addacMaxResolution/addacMaxResolution;
		}
	}
}



// --------------------------------------------------------------------------- EXP / LOG ADSR ENVELOPE MODE -------------------------
//


/*! \brief update ADSR with logarithmic and/or exponencial curves
 \param _trigger  trigger ADSR : true or false
 \param _inverted invert ADSR : true or false
 \param _A Attack amplitude
 \param _Atime Attack time
 \param _Ashape Attack curve shape
 \param _D Decay amplitude
 \param _Dtime Decay time
 \param _Dshape Decay curve shape
 \param _S Sustain amplitude
 \param _Stime Sustain time
 \param _Sshape Sustain curve shape
 \param _R Release amplitude
 \param _Rtime Release time
 \param _Rshape Release curve shape
 */

//int _channel (1-8), bool _trigger (0=no - 1=yes), bool _inverted (0=no - 1=yes) 
//float _A (0-1), float _Atime (millis), float _Ashape (0-1)
void ADDAC_Adsr::updateLogExpMode(bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, float _D, float _Dtime, float _Dshape, float _S, float _Stime, float _Sshape, float _Rtime, float _Rshape){
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
			CVstream = (pow(_actualPos, exp(_Ashape*4.0f-2)) * (_A * addacMaxResolution))/addacMaxResolution;		
			
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){ 
			// D
			float _actualPos = (millis()-ADSRtriggerTime-_Atime)/_Dtime;
			CVstream = (-(1-_D-(1-_A))*pow(_actualPos, exp(_Dshape*4.0f-2)) +_A);
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos=(millis()-ADSRtriggerTime-_Atime-_Dtime)/_Stime;
			CVstream = (-(1-_S-(1-_D))*pow(_actualPos, exp(_Sshape*4.0f-2)) +_D) ;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime+_Stime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			unsigned int percentageDif = _S * addacMaxResolution; // intervalo
			float _actualPos=(millis()-ADSRtriggerTime-_Atime-_Dtime-_Stime)/_Rtime;
			CVstream = ((-pow(_actualPos, exp(_Rshape*4-2))+1) * percentageDif)/addacMaxResolution;
			
		}else{
			ADSRtrigger=false;
			CVstream=0;
		}
	}else{ // inverted
		if(millis()<=ADSRtriggerTime+_Atime){ 
			// A
			Serial.print(" | A");
			float _floatPercentage = _A / 100.0f * addacMaxResolution;
			float _actualPos = (ADSRtriggerTime+_Atime-millis());
			toAddDif = (_A/100.0f-1)*-1.0f*addacMaxResolution;
			CVstream = (_actualPos / _Atime * _floatPercentage+toAddDif)/addacMaxResolution;		
			
		}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime){ 
			// D
			Serial.print(" | D");
			float _actualPos;
			float percentageDif = (_A - _D)/100.0f; // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (100 - _D) / 100.0f * addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (100 - _A) / 100.0f * addacMaxResolution;
				_actualPos = _Dtime-(ADSRtriggerTime+_Atime+_Dtime-millis());
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos;
			float percentageDif = (_D - _S) /100.0f; // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (100 - _S) / 100.0f * addacMaxResolution;
				_actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (100 - _D) / 100.0f * addacMaxResolution;
				_actualPos = _Stime-(ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
			}
			CVstream = (_actualPos / _Stime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else if(millis()>ADSRtriggerTime+_Atime+_Dtime+_Stime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			float percentageDif = _S / 100.0f * addacMaxResolution; // intervalo
			float _actualPos = _Rtime-(ADSRtriggerTime+_Atime+_Dtime+_Stime+_Rtime-millis());
			float toAddDif = (_S/100.0f-1)*-1.0f*addacMaxResolution;
			CVstream = (_actualPos / _Rtime * percentageDif + toAddDif)/addacMaxResolution;
			
		}else{
			ADSRtrigger=false;
			CVstream=addacMaxResolution/addacMaxResolution;
		}
	}
}






//UPDATE WITHOUT TRIGGER

/*! \brief update ADSR values

 \param _A  Attack amplitude
 \param _Atime  Attack time
 \param _D  Decay amplitude
 \param _Dtime  Decay time
 \param _S  Sustain amplitude
 \param _Stime Sustain time
 \param _Rtime Release time
 */

void ADDAC_Adsr::update(float _A, float _Atime, float _D, float _Dtime, float _S,float _Stime, float _Rtime){ //  a:ATTACK TIME  |  b:DECAY TIME    in millis
	if(millis()<=ADSRtriggerTime+_Atime && SUSTAIN){ 
		// A
		float TipPointF = TipPoint/addacMaxResolution;
		float difference;
		if (TipPointF > _A) {
			difference = TipPointF - _A;
			weakLink = _A * addacMaxResolution;
		}else {
			difference = _A - TipPointF;
			weakLink=TipPoint;
		}
		
		floatPercentage = difference * addacMaxResolution;
		float _actualPos = _Atime-(ADSRtriggerTime+_Atime-millis());
		CVstream = _actualPos / _Atime * floatPercentage + weakLink;	
		
		#ifdef DEBUG_adsr
			Serial.print("  -ATTACK-  perc:");
			Serial.print(floatPercentage);
			Serial.print("  -- pos:");
			Serial.print(_actualPos);
			Serial.print("  --  Going Up:");
			Serial.println(CVstream);
		#endif
		
	}else if(millis()>ADSRtriggerTime+_Atime && millis()<=ADSRtriggerTime+_Atime+_Dtime && SUSTAIN){ 
		// D
		float _actualPos;
		long percentageDif = (_A - _D) * addacMaxResolution; // intervalo
		if(percentageDif<0){
			percentageDif = percentageDif*-1.0f;
			toAddDif = _A*addacMaxResolution;
			_actualPos = _Dtime-(ADSRtriggerTime+_Atime+_Dtime-millis());
		}else{
			toAddDif = _D*addacMaxResolution;
			_actualPos = ADSRtriggerTime+_Atime+_Dtime-millis();
		}
		CVstream = _actualPos / _Dtime * percentageDif + toAddDif;
		
		#ifdef DEBUG_adsr
			Serial.print("  -DECAY-  perc:");
			Serial.print(floatPercentage);
			Serial.print("  -- pos:");
			Serial.print(_actualPos);
			Serial.print("  --  Going:");
			Serial.println(CVstream);
		#endif
		
		
	}else if(millis()>ADSRtriggerTime+_Atime+_Dtime && millis()<=ADSRtriggerTime+_Atime+_Dtime+_Stime && SUSTAIN){ 
		// S
		float _actualPos;
		long percentageDif = (_D - _S) * addacMaxResolution; // intervalo
		if(percentageDif<0){
			percentageDif = percentageDif*-1.0f;
			toAddDif = _D*addacMaxResolution;
			_actualPos = _Stime-(ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
		}else{
			toAddDif = _S*addacMaxResolution;
			_actualPos = (ADSRtriggerTime+_Atime+_Dtime+_Stime-millis());
		}
		CVstream = _actualPos / _Stime * percentageDif + toAddDif;
		
		#ifdef DEBUG_adsr
			Serial.print("  -SUSTAIN-  perc:");
			Serial.print(floatPercentage);
			Serial.print("  -- pos:");
			Serial.print(_actualPos);
			Serial.print("  --  Going:");
			Serial.println(CVstream);
		#endif
		
	}else if(millis()<=ADSRtriggerTime+_Rtime && !SUSTAIN && ADSRtrigger){ 
		// R
		float _actualPos = ADSRtriggerTime+_Rtime-millis();
		CVstream = _actualPos / _Rtime * TipPoint;
		
		#ifdef DEBUG_adsr
			Serial.print("  -RELEASE-  Going Down:");
			Serial.println(CVstream);
		#endif
		
	}else if(!SUSTAIN){
		CVstream = 0;
		ADSRtrigger=false;
	}
	
}

/*! \brief Trigger ADSR Envelope with defined attack amplitude
 \param _A  Attack amplitude	
 */

void ADDAC_Adsr::trigger(float _A){ // a:VELOCITY PERCENTAGE 0.0f & 1.0f for notes on
	Attack = _A;
	ADSRtrigger = true;
	SUSTAIN = true;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
    
#ifdef DEBUG_adsr
    Serial.println("  -- ADSR TRIGGER");
#endif
} 

/*! \brief Trigger ADSR Envelope with attack amplitude of 1.0	*/
void ADDAC_Adsr::trigger(){ // FULL VELOCITY PERCENTAGE 1.0f for ADSR
	Attack = 1.0f;
	ADSRtrigger=true;
	SUSTAIN = true;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
	
#ifdef DEBUG_adsr
    Serial.println("  -- ADSR TRIGGER");
#endif
}

/*! \brief Release ADSR Envelope */
void ADDAC_Adsr::release(){
	SUSTAIN = false;
	ADSRtriggerTime=millis();
	TipPoint = CVstream;
    
#ifdef DEBUG_adsr
    Serial.println("  --  ADSR RELEASE");
#endif
}
