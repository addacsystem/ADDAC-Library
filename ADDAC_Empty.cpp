 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Empty.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Empty::ADDAC_Empty(){	// INITIALIZE CLASS
	
	CVstream = 0.0f;
	
	//Serial.println("ADDAC_Empty INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


long ADDAC_Empty::update(float _val){ // DO SOMETHING !
	// do some fancy calculations
	CVstream = _val / 2.0f * 4.0f / 2.0f;
	
	// return the value
	return CVstream;

}
// --------------------------------------------------------------------------- END ----------------------------------
//