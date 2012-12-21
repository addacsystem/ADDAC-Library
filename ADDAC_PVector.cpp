 
/*
 * PVectors
 *
*/


#include "ADDAC_PVector.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_PVector::ADDAC_PVector(){	// INITIALIZE CLASS
	
	x=0;
    y=0;
    z=0;
}

ADDAC_PVector::ADDAC_PVector(float _x, float _y){	// INITIALIZE CLASS
	
	x=_x;
    y=_y;
    z=0;
}


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


void ADDAC_PVector::add(float _add){    
    
    x+=_add;
    y+=_add;
    z+=_add;
    
}


void ADDAC_PVector::add(ADDAC_PVector _add){    
    
    x+=_add.x;
    y+=_add.y;
    z+=_add.z;
    
}


void ADDAC_PVector::sub(float _sub){    
    
    x-=_sub;
    y-=_sub;
    z-=_sub;
    
}


void ADDAC_PVector::mult(float _mult){    
    
    x*=_mult;
    y*=_mult;
    z*=_mult;
    
}

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



void ADDAC_PVector::normalize(){  
    
    float length = sqrt((x*x)+(y*y)+(z*z));
    
    x/=length;
    y/=length;
    z/=length;
    
}






// --------------------------------------------------------------------------- END ----------------------------------
//