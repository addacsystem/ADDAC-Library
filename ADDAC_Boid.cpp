 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Boid.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Boid::ADDAC_Boid(float _x, float _y){	// INITIALIZE CLASS

    pos.set(_x, _y);
    vel.set(0, 0);
    ac.set(0, 0);
    
    r = 5.0;
    maxSpeed = 2;
    maxForce = 0.03;
    mass=1;

}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_Boid::update(ADDAC_Boid boids[4], bool _warpAround){ 
    
   flock(boids);
    update();
//    borders(_wrapAround);   // entre  0-1
    //render();
    
    
}

void ADDAC_Boid::update(){ // DO SOMETHING !

}


void ADDAC_Boid::applyForce(ADDAC_PVector force) {

    // We could add mass here if we want A = F / M
    ADDAC_PVector f = force.divR(mass);
    ac.add(force);
}



void ADDAC_Boid::flock(ADDAC_Boid boids[4]){
    
    
    ADDAC_PVector sep = separate(boids);   // Separation
    ADDAC_PVector ali = align(boids);      // Alignment
    ADDAC_PVector coh = cohesion(boids);   // Cohesion
    
//    ADDAC_PVector atr = atractor(boids);   // atrattor___________________
//    ADDAC_PVector rpl = repulsor(boids);   // atrattor___________________
    
    // Arbitrarily weight these forces
    sep.mult(1.5);
    ali.mult(1.0);
    coh.mult(1.0);
    // Add the force vectors to acceleration
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
//    if (atractMode) applyForce(atr);
//    if (repulseMode) applyForce(rpl);

}


ADDAC_PVector ADDAC_Boid::separate(ADDAC_Boid boids[4]) {
//    float desiredseparation = Separation;
//    PVector steer = new PVector(0, 0, 0);
//    int count = 0;
//    // For every boid in the system, check if it's too close
//    for (Boid other : boids) {
//        float d = PVector.dist(location, other.location);
//        // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
//        if ((d > 0) && (d < desiredseparation)) {
//            // Calculate vector pointing away from neighbor
//            PVector diff = PVector.sub(location, other.location);
//            diff.normalize();
//            diff.div(d);        // Weight by distance
//            steer.add(diff);
//            count++;            // Keep track of how many
//        }
//    }
//    // Average -- divide by how many
//    if (count > 0) {
//        steer.div((float)count);
//    }
//    
//    // As long as the vector is greater than 0
//    if (steer.mag() > 0) {
//        // Implement Reynolds: Steering = Desired - Velocity
//        steer.normalize();
//        steer.mult(maxspeed);
//        steer.sub(velocity);
//        steer.limit(maxforce);
//    }
    //return steer;
    return ADDAC_PVector();
}

// Alignment
// For every nearby boid in the system, calculate the average velocity
ADDAC_PVector ADDAC_Boid::align(ADDAC_Boid boids[4]) {
//    float neighbordist = Aneighbordist;
//    PVector sum = new PVector(0, 0);
//    int count = 0;
//    for (Boid other : boids) {
//        float d = PVector.dist(location, other.location);
//        if ((d > 0) && (d < neighbordist)) {
//            sum.add(other.velocity);
//            count++;
//        }
//    }
//    if (count > 0) {
//        sum.div((float)count);
//        sum.normalize();
//        sum.mult(maxspeed);
//        PVector steer = PVector.sub(sum, velocity);
//        steer.limit(maxforce);
//        return steer;
//    } 
 //   else {
        return ADDAC_PVector();
//    }
}

// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
ADDAC_PVector ADDAC_Boid::cohesion(ADDAC_Boid boids[4]) {
//    float neighbordist = Cneighbordist;
//    PVector sum = new PVector(0, 0);   // Start with empty vector to accumulate all locations
//    int count = 0;
//    for (Boid other : boids) {
//        float d = PVector.dist(location, other.location);
//        if ((d > 0) && (d < neighbordist)) {
//            sum.add(other.location); // Add location
//            count++;
//        }
//    }
//    if (count > 0) {
//        sum.div(count);
//        return seek(sum);  // Steer towards the location
//    } 
//    else {
        return ADDAC_PVector();
  //  }
}




// --------------------------------------------------------------------------- END ----------------------------------
//