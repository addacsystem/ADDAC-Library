 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Lin2Log.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------
/*! \brief Default construtor for ADDAC_Lin2Log */
ADDAC_Lin2Log::ADDAC_Lin2Log(){	// INITIALIZE CLASS
	
	CVstream = 0;
	
	//Serial.println("ADDAC_Lin2Log INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief transforms a linear progression to logarithmic with a default factor of 10  
 \param _val value to convert
 */
float ADDAC_Lin2Log::calc(float _val){ // DO SOMETHING !
	// do some fancy calculations
	CVstream = log10(_val)/3.0f+1;
	
	
	// return the value
	return CVstream;

}

/*! \brief transforms a linear progression to logarithmic with a defined factor  
 \param _val value to convert
 \param _factor logarithmic factor 
 */
float ADDAC_Lin2Log::calc(float _val, float _factor){ // factor between 0.0f & 1.0f
    
    _val=constrain(_val,0.0f,1.0f);
    
    if (_factor< 0.5f) {
        _factor = _factor*2.0f *0.84 +0.16f;  // 0.3 -> 1.0
    }
    else {
        _factor = (_factor - 0.5f) *2.0f *5.3f + 1.0f; // 1.0 -> 3.3
    }
    
    CVstream=pow(_val, _factor);
	
	// return the value
	return CVstream;
	
}


float ADDAC_Lin2Log::log10(float _x){ // DO SOMETHING !
    
		return (log(_x) / log(10));
	
}
// --------------------------------------------------------------------------- END ----------------------------------
//