 
/*
 * PVectors
 *
*/


#include "ADDAC_PVector.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

/*! \brief Default constructor for ADDAC_PVector. */
ADDAC_PVector::ADDAC_PVector(){	// INITIALIZE CLASS
	
	x=0;
    y=0;
    z=0;
}

/*! \brief PVector constructor
 \param _x Point X value
 \param _y Point Y value
 */


ADDAC_PVector::ADDAC_PVector(float _x, float _y){	// INITIALIZE CLASS
	
	x=_x;
    y=_y;
    z=0;
}

/*! \brief PVector constructor
 \param _x Point X value
 \param _y Point Y value
 \param _z Point Z value
 */
ADDAC_PVector::ADDAC_PVector(float _x, float _y, float _z){	// INITIALIZE CLASS
	
	x=_x;
    y=_y;
    z=_z;
}


void ADDAC_PVector::set(float _x, float _y){
    
    x=_x;
    y=_y;
    z=0;
}


void ADDAC_PVector::set(float _x, float _y, float _z){    
    
    x=_x;
    y=_y;
    z=_z;
    
}


/*! \brief Add some value to PVector
 \param _add Value to add
 */

void ADDAC_PVector::add(float _add){    
    
    x+=_add;
    y+=_add;
    z+=_add;
    
}


/*! \brief Add PVector to PVector
 \param _add PVector to add
 */

void ADDAC_PVector::add(ADDAC_PVector _add){    
    
    x+=_add.x;
    y+=_add.y;
    z+=_add.z;
    
}

/*! \brief Subtract some value to PVector
 \param _sub Value to subtract
 */

void ADDAC_PVector::sub(float _sub){    
    
    x-=_sub;
    y-=_sub;
    z-=_sub;
    
}


/*! \brief Subtract PVector to PVector
 \param _sub PVector to subtract
 */


void ADDAC_PVector::sub(ADDAC_PVector _sub){    
    
    x-=_sub.x;
    y-=_sub.y;
    z-=_sub.z;
    
}


/*! \brief Multiply PVector by some value 
 \param _mult Value to multiply
 */

void ADDAC_PVector::mult(float _mult){    
    
    x*=_mult;
    y*=_mult;
    z*=_mult;
    
}

/*! \brief Divide PVector by some value
 \param _mult Value to multiply
 */

void ADDAC_PVector::div(float _div){    
    
    x/=_div;
    y/=_div;
    z/=_div;
    
}


ADDAC_PVector ADDAC_PVector::divR(float _div){    
    
    ADDAC_PVector pv;
    
    pv.x=x;
    pv.y=y;
    pv.z=z;
    
    pv.x/=_div;
    pv.y/=_div;
    pv.z/=_div;

    return pv;
}



ADDAC_PVector ADDAC_PVector::div(ADDAC_PVector pv, float _div){ 
    
    return pv.divR(_div);
    
}


/*! \brief Normalize PVector
 */

void ADDAC_PVector::normalize(){  
    
    float length = sqrt((x*x)+(y*y)+(z*z));
    
    x/=length;
    y/=length;
    z/=length;
    
}








// --------------------------------------------------------------------------- END ----------------------------------
//