 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Flock.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Flock::ADDAC_Flock(){	// INITIALIZE CLASS
	
	
}



/*! \brief Setup a Flock with four Boids
 */

void ADDAC_Flock::setup(){

    boids[0] = ADDAC_Boid();
    boids[1] = ADDAC_Boid();
    boids[2] = ADDAC_Boid();
    boids[3] = ADDAC_Boid();

}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


/*! \brief Update the Flock variables
    \param _wrapAround true - the flock will wrapAround | false - the flock will mirror 
 */

void ADDAC_Flock::update(bool _wrapAround){
    
    // array.size()??
    for (int i = 0; i<4; i++) {
        boids[i].update(boids, _wrapAround);
    }
    
}




/*! \brief get Boid XPosition stream
 \param _boidNumber boid number (0-4)
 */

float ADDAC_Flock::getBoidPositionX(int _boidNumber){
    
  return  boids[_boidNumber].pos.x/maxWidth;


}

/*! \brief get Boid YPosition stream
 \param _boidNumber boid number (0-4)
 */

float ADDAC_Flock::getBoidPositionY(int _boidNumber){
    
    return  boids[_boidNumber].pos.y/maxHeight;
    
    
}


/*! \brief get Boid X and Y Average Position stream
 \param _boidNumber boid number (0-4)
 */

float ADDAC_Flock::getBoidPositionM(int _boidNumber){
    
    return  ((boids[_boidNumber].pos.y/1000)+(boids[_boidNumber].pos.y/1000))/2;
    
    
}


/*! \brief set Separation value
 \param _sep separation value (0-1000)
 */

void ADDAC_Flock::setSeparation(float _sep){

    
    for (int i = 0; i<4; i++) {
    boids[i].separationV=_sep;
    }

}


/*! \brief set Cohesion value
 \param _coe Cohesion value (0-1000)
 */

void ADDAC_Flock::setCohesion(float _coe){
    
    
    for (int i = 0; i<4; i++) {
        boids[i].cohesionV=_coe;
    }
    
}


/*! \brief set Align value
 \param _ali Align value (0-1000)
 */

void ADDAC_Flock::setAlign(float _ali){
    
    
    for (int i = 0; i<4; i++) {
        boids[i].alignV=_ali;
    }
    
}


/*! \brief set Speed value
 \param _speed Align value (0-1)
 */

void ADDAC_Flock::setSpeed(float _speed){
    
    
    _speed=(_speed*5.0f);
    
    for (int i = 0; i<4; i++) {
        boids[i].speedV=_speed;
    }
    
}










// --------------------------------------------------------------------------- END ----------------------------------
//