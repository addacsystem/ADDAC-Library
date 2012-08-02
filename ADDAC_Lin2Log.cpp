 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Lin2Log.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Lin2Log::ADDAC_Lin2Log(){	// INITIALIZE CLASS
	
	CVstream = 0;
	
	//Serial.println("ADDAC_Lin2Log INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


float ADDAC_Lin2Log::calc(float _val){ // DO SOMETHING !
	// do some fancy calculations
	CVstream = log10(_val)/3.0f+1;
	
	
	// return the value
	return CVstream;

}

float ADDAC_Lin2Log::calc(float _val, float _factor){ // factor between 0.0f & 1.0f
	// do some fancy calculations
	CVstream = log10(_val)/((_factor+1.0f)*10.0f)+1;
	if(CVstream<0.05f)CVstream=0.0f;
	// return the value
	return CVstream;
	
}

float ADDAC_Lin2Log::log10(float _x){ // DO SOMETHING !
		return (log(_x) / log(10));
	
}
// --------------------------------------------------------------------------- END ----------------------------------
//