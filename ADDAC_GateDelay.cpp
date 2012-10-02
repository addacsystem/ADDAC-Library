 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_GateDelay.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

/*! \brief Default construtor for ADDAC_GateDelay */
ADDAC_GateDelay::ADDAC_GateDelay(){	// INITIALIZE CLASS
	

}


/*! \brief Rise Time */
void ADDAC_GateDelay::GateDelayRise(){ 
    
	time = millis();
   
    
}


/*! \brief Fall Time */
void ADDAC_GateDelay::GateDelayFall(){ 
    
	timeFall = millis();
    totalTime = timeFall - time;
    
    
       
}




// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief Return true when GateDelay
  \param _delay  delay (milliseconds)
 */
bool ADDAC_GateDelay::update(float _delay){ 
    

    
    if (time + _delay + totalTime < millis()){
    
        state = 0;
    }
    
    else if (time + _delay < millis()) {
        state = 1;
    }
    
    else {
    
        state = 0;
    }
	Serial.print(" | ");
    Serial.print(state);
    
    
    
    if (oldState != state){
        
        oldState = state;
        return true;
    }
    
    else{
    
        return false;
    }
    
    
    
    
  


}
// --------------------------------------------------------------------------- END ----------------------------------
//