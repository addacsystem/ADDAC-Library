 
/*
 * SMOOTH BETWEEN VALUES
 *
*/


#include "ADDAC_Smooth.h"

//-----------------------------------------------------------------------ADDAC SMOOTH-----------------

ADDAC_Smooth::ADDAC_Smooth(){	// INITIALIZE CLASS
	
    oldValue=0;
    smoothed=0;
}



// --------------------------------------------------------------------------- SMOOTH -------------------------
//


// newValue - value to smooth, smoothFactor - smooth intensity 0-1.
float ADDAC_Smooth::calc(float newValue, float smoothFactor){ 
    
    
    
    smoothed = oldValue * smoothFactor + newValue * (1.0f - smoothFactor);
    
    oldValue = smoothed;
    
    return smoothed;

}

// --------------------------------------------------------------------------- END ----------------------------------



