 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Flock.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Flock::ADDAC_Flock(){	// INITIALIZE CLASS
	
	
}


void ADDAC_Flock::setup(){

    boids[0] = ADDAC_Boid();
    boids[1] = ADDAC_Boid();
    boids[2] = ADDAC_Boid();
    boids[3] = ADDAC_Boid();

}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_Flock::update(bool _wrapAround){
    
    // array.size()??
    for (int i = 0; i<4; i++) {
        boids[i].update(boids, _wrapAround);
    }
    
}




ADDAC_PVector ADDAC_Flock::getBoidPosition(int _boidNumber){
    
  return  boids[_boidNumber].pos;


}







// --------------------------------------------------------------------------- END ----------------------------------
//