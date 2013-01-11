 
/*
 * TIMER
 *
*/


#include "ADDAC_Timer.h"

//-----------------------------------------------------------------------ADDAC Timer-----------------
/*! \brief Default constructor for ADDAC_Timer. */
ADDAC_Timer::ADDAC_Timer(){	// INITIALIZE CLASS
	
	//Serial.println("ADDAC_Timer INITIALIZED");
    oldTime=0;
    actualTime=0;
    elapsedTime=0;
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief Set a Timer/metro 
 \param _time time (milliseconds) 
 */

bool ADDAC_Timer::set(long _time){ // DO SOMETHING !
	
     oldTime = millis();
    
     elapsedTime += abs(actualTime - oldTime);
    
     actualTime = millis();
    if (elapsedTime > _time){
        elapsedTime=0;
     return true;   
    }
    else return false;


}
// --------------------------------------------------------------------------- END -------------------------------