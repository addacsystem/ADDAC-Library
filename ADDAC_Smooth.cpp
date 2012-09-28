 
/*
 * SMOOTH BETWEEN VALUES
 *
*/


#include "ADDAC_Smooth.h"

//-----------------------------------------------------------------------ADDAC SMOOTH-----------------
/*! \brief Default constructor for ADDAC_Smooth. */
ADDAC_Smooth::ADDAC_Smooth(){	// INITIALIZE CLASS
	
    oldValue=0;
    smoothed=0;
}



// --------------------------------------------------------------------------- SMOOTH -------------------------
//

/*! \brief Smooth a value
 \param newValue value to smooth 
 \param smoothFactor smooth intensity : 0 - 1 
 */
// newValue - value to smooth, smoothFactor - smooth intensity 0-1.
float ADDAC_Smooth::calc(float newValue, float smoothFactor){ 
    
    
    
    smoothed = oldValue * smoothFactor + newValue * (1.0f - smoothFactor);
    
    oldValue = smoothed;
    
    return smoothed;

}

// --------------------------------------------------------------------------- END ----------------------------------



