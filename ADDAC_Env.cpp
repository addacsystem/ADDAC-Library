

#include "ADDAC_Env.h"

//-----------------------------------------------------------------------ADDAC-----------------

ADDAC_Env::ADDAC_Env(){	
	
	CVstream = 0;
    actualStep = 0;
    addPoint(0,0);
	//Serial.println("ADDAC_Env INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


// --------------------------------------------------------------------------- LINEAR ENV MODE --- OLD CLASS -> (to be deleted ...) ----------------------
//
//int _channel (1-8), bool _trigger (0=no - 1=yes), bool _inverted (0=no - 1=yes) 
//float _A (percentage (0-100% = 0.0f to 1.0f), float _Atime (millis)

// ADD top and bottom offset??

/*! \brief update Envelope values
 \param _trigger  trigger Envelope : true or false
 \param _inverted invert Envelope : true or false
 \param _A     Envelope Attack voltage
 \param _Atime Envelope Attack time
 \param _D     Envelope Decay voltage
 \param _Dtime Envelope Decay time
 \param _S     Envelope Sustain voltage
 \param _Stime Envelope Sustain time
 \param _Rtime Envelope Release time
 */
void ADDAC_Env::update(bool _trigger, bool _inverted, float _A, float _Atime, float _D, float _Dtime, float _S,float _Stime, float _Rtime){
	if(_trigger && !ENVtrigger){
		ENVtrigger=true;
		ENVtriggerTime=millis();
		CVstream=0;
	}
	//unsigned int toAddDif;
	if(!_inverted){ // normal
		if(millis()<=ENVtriggerTime+_Atime){ 
			// A
			float _floatPercentage = _A * addacMaxResolution;
			float _actualPos = _Atime-(ENVtriggerTime+_Atime-millis());
			CVstream = (_actualPos / _Atime * _floatPercentage);		
			
		}else if(millis()>ENVtriggerTime+_Atime && millis()<=ENVtriggerTime+_Atime+_Dtime){ 
			// D
			float _actualPos;
			long percentageDif = (_A - _D) * addacMaxResolution; // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif*-1.0f;
				toAddDif = _A*addacMaxResolution;
				_actualPos = _Dtime-(ENVtriggerTime+_Atime+_Dtime-millis());
			}else{
				toAddDif = _D*addacMaxResolution;
				_actualPos = ENVtriggerTime+_Atime+_Dtime-millis();
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif);
			
		}else if(millis()>ENVtriggerTime+_Atime+_Dtime && millis()<=ENVtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos;
			long percentageDif = (_D - _S) * addacMaxResolution; // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif*-1.0f;
				toAddDif = _D*addacMaxResolution;
				_actualPos = _Stime-(ENVtriggerTime+_Atime+_Dtime+_Stime-millis());
			}else{
				toAddDif = _S*addacMaxResolution;
				_actualPos = (ENVtriggerTime+_Atime+_Dtime+_Stime-millis());
			}
			CVstream = (_actualPos / _Stime * percentageDif + toAddDif);
			
		}else if(millis()>ENVtriggerTime+_Atime+_Dtime+_Stime && millis()<=ENVtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			unsigned int percentageDif = _S * addacMaxResolution; // intervalo
			float _actualPos = (ENVtriggerTime+_Atime+_Dtime+_Stime+_Rtime-millis());
			CVstream = (_actualPos / _Rtime * percentageDif);
			
		}else{
			ENVtrigger=false;
			CVstream=0;
		}
	}else{ // inverted
		if(millis()<=ENVtriggerTime+_Atime){ 
			// A
			float _floatPercentage = _A * addacMaxResolution;
			float _actualPos = (ENVtriggerTime+_Atime-millis());
			toAddDif = (_A-1)*-1.0f*addacMaxResolution;
			CVstream =(_actualPos / _Atime * _floatPercentage+toAddDif);		
			
		}else if(millis()>ENVtriggerTime+_Atime && millis()<=ENVtriggerTime+_Atime+_Dtime){ 
			// D
			float _actualPos;
			float percentageDif = (_A - _D); // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (1 - _D) * addacMaxResolution;
				_actualPos = (ENVtriggerTime+_Atime+_Dtime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (1 - _A) * addacMaxResolution;
				_actualPos = _Dtime-(ENVtriggerTime+_Atime+_Dtime-millis());
			}
			CVstream = (_actualPos / _Dtime * percentageDif + toAddDif);
			
		}else if(millis()>ENVtriggerTime+_Atime+_Dtime && millis()<=ENVtriggerTime+_Atime+_Dtime+_Stime){ 
			// S
			float _actualPos;
			float percentageDif = (_D - _S); // intervalo
			if(percentageDif<0){
				percentageDif = percentageDif * -1.0f * addacMaxResolution;
				toAddDif = (1 - _S) * addacMaxResolution;
				_actualPos = (ENVtriggerTime+_Atime+_Dtime+_Stime-millis());
			}else{
				percentageDif = percentageDif * addacMaxResolution;
				toAddDif = (1 - _D) * addacMaxResolution;
				_actualPos = _Stime-(ENVtriggerTime+_Atime+_Dtime+_Stime-millis());
			}
			CVstream =(_actualPos / _Stime * percentageDif + toAddDif);
			
		}else if(millis()>ENVtriggerTime+_Atime+_Dtime+_Stime && millis()<=ENVtriggerTime+_Atime+_Dtime+_Stime+_Rtime){ 
			// R
			float percentageDif = _S * addacMaxResolution; // intervalo
			float _actualPos = _Rtime-(ENVtriggerTime+_Atime+_Dtime+_Stime+_Rtime-millis());
			float toAddDif = (_S-1)*-1.0f*addacMaxResolution;
			CVstream = (_actualPos / _Rtime * percentageDif + toAddDif);
			
		}else{
			ENVtrigger=false;
			CVstream=addacMaxResolution;
		}
	}
}


/*! \brief MultiEnvelope, trigger a multienvelope with as many points as you want
 \param _trigger  trigger Envelope : true or false
 \param _inverted invert Envelope : true or false
 */

void ADDAC_Env::MultiEnv(bool _trigger, bool _inverted){
    
    //for (int i=0; i<amplitude.size(); i++) {
        
        Serial.print("  actualStep:");
        Serial.print(actualStep);
        Serial.print("  | ");
    
    if(_trigger){ // && !ENVtrigger){
        
        Serial.print("trigged");
        ENVtrigger=true;
        ENVtriggerTime=millis();
        //CVstream=0;
        actualStep=0;
    }
    
 if(amplitude.size()>1 && ENVtrigger){
     
    
        long totalTime = ENVtriggerTime;
        for (int i =0; i<actualStep ; i++) {
            totalTime+= time[0+i];
        }

        //unsigned int toAddDif;
    
    
    if(millis() > totalTime+time[actualStep]){
        
         if(actualStep>=amplitude.size()){
             ENVtrigger=false;
             actualStep=amplitude.size();
            
             
                         
             
         }else{
             actualStep++;
         }
    }else{
        float _x = (millis()-totalTime)/time[actualStep]; 
        /*Serial.print(" m:");
        Serial.print(millis());
        Serial.print(" - tTime:");
        Serial.print(totalTime);
        Serial.print(" /actuTime:");
        Serial.print(time[actualStep]);
        Serial.print(" x:");
        Serial.print(_x);*/
        if(amplitude[actualStep] > amplitude[actualStep-1]){ // SOBE
            float percentageDif = (amplitude[actualStep] - amplitude[actualStep-1]);
            CVstream = (_x*percentageDif + amplitude[actualStep-1]);
            /*Serial.print(" goingUP  x:");
            Serial.print(_x);
            Serial.print(" *percDif:");
            Serial.print(percentageDif);
            Serial.print(" +ampStep-1:");
            Serial.print(amplitude[actualStep-1]);
            Serial.print(" =");
            Serial.print(CVstream);*/
        }else{ // DESCE
            float percentageDif = (amplitude[actualStep-1] - amplitude[actualStep]);
            CVstream = (-_x*percentageDif+ amplitude[actualStep-1]);
            /*Serial.print(" goingDOWN:");
            Serial.print(_x);
            Serial.print(" *percDif:");
            Serial.print(percentageDif);
            Serial.print(" +ampStep-1:");
            Serial.print(amplitude[actualStep-1]);
            Serial.print(" =");
            Serial.print(CVstream);*/
        }

    }
  }
           
    if(_inverted) CVstream = 1.0f-CVstream;
    
}



/*! \brief MultiEnvelopeLoop, trigger a multienvelope with as many points as you want in Loop
 \param _trigger  trigger Envelope : true or false
 \param _inverted invert Envelope : true or false
 */
void ADDAC_Env::MultiEnvLoop(bool _trigger, bool _inverted){
    
    //for (int i=0; i<amplitude.size(); i++) {
    
    Serial.print("  actualStep:");
    Serial.print(actualStep);
    Serial.print("  | ");
    
    if(_trigger){ // && !ENVtrigger){
        ENVtrigger=true;
        ENVtriggerTime=millis();
        //CVstream=0;
        actualStep=0;
        _loopON=true;
    }
    
    if(amplitude.size()>1 && ENVtrigger){
        
        
        long totalTime = ENVtriggerTime;
        for (int i =0; i<actualStep ; i++) {
            totalTime+= time[0+i];
        }
        Serial.print(" tTime:");
        Serial.print(totalTime);
        //unsigned int toAddDif;
        
        
        if(millis() > totalTime+time[actualStep]){
            
            if(actualStep>=amplitude.size()){
                ENVtrigger=false;
                actualStep=amplitude.size();
                
                
                if (_loopON) {
                    
                
                ENVtrigger=true;
                ENVtriggerTime=millis();
                //CVstream=0;
                actualStep=0;
                }
                
            }else{
                actualStep++;
            }
        }else{
            float _x = (millis()-totalTime)/time[actualStep]; 
            /*Serial.print(" m:");
             Serial.print(millis());
             Serial.print(" - tTime:");
             Serial.print(totalTime);
             Serial.print(" /actuTime:");
             Serial.print(time[actualStep]);
             Serial.print(" x:");
             Serial.print(_x);*/
            if(amplitude[actualStep] > amplitude[actualStep-1]){ // SOBE
                float percentageDif = (amplitude[actualStep] - amplitude[actualStep-1]);
                CVstream = (_x*percentageDif + amplitude[actualStep-1]);
                /*Serial.print(" goingUP  x:");
                 Serial.print(_x);
                 Serial.print(" *percDif:");
                 Serial.print(percentageDif);
                 Serial.print(" +ampStep-1:");
                 Serial.print(amplitude[actualStep-1]);
                 Serial.print(" =");
                 Serial.print(CVstream);*/
            }else{ // DESCE
                float percentageDif = (amplitude[actualStep-1] - amplitude[actualStep]);
                CVstream = (-_x*percentageDif+ amplitude[actualStep-1]);
                /*Serial.print(" goingDOWN:");
                 Serial.print(_x);
                 Serial.print(" *percDif:");
                 Serial.print(percentageDif);
                 Serial.print(" +ampStep-1:");
                 Serial.print(amplitude[actualStep-1]);
                 Serial.print(" =");
                 Serial.print(CVstream);*/
            }
            
        }
    }
    
    if(_inverted) CVstream = 1.0f-CVstream;
    
}


/*! \brief add Points to MultiEnvelope
 \param _amp  amplitude value
 \param _time time value
 */
void ADDAC_Env::addPoint(float _amp, float _time){
    
    amplitude.push_back(_amp);
    time.push_back(_time*10000);
    


}


/*! \brief Print multiEnvelope Points vector in monitor log - usefull for DEBUG
 \param _amp  amplitude value
 \param _time time value
 */
void ADDAC_Env::PrintMultiEnv(){

    for (int i=0; i<amplitude.size(); i++) {
        Serial.print(" |a:");
        Serial.print(amplitude[i]);
        Serial.print(" t:");
        Serial.print(time[i]);
        Serial.print("| ");
    }

}

// --------------------------------------------------------------------------- END ----------------------------------
