
/*
 * Some hints about what this Class does!
 *
 */


#include "ADDAC_Boid.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Boid::ADDAC_Boid(){
    
    
    pos.set(random(0,maxWidth), random(0,maxHeight));
    vel.set(0, 0);
    ac.set(0, 0);
    
    r = 0;
    maxSpeed = 2;
    maxForce = 0.03;
    mass=1;
    
    separationV=25.0f;
    alignV=50.0f;
    cohesionV=500.0f;
    speedV=2;
    
    
    
    
    
}


ADDAC_Boid::ADDAC_Boid(float _x, float _y){	// INITIALIZE CLASS
    
    pos.set(_x, _y);
    vel.set(0, 0);
    ac.set(0, 0);
    
    r = 0;
    maxSpeed = 2;
    maxForce = 0.03;
    mass=1;
    
    
    separationV=25.0f;
    alignV=50.0f;
    cohesionV=500.0f;
    
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_Boid::update(ADDAC_Boid boids[4], bool _warpAround){ 
    maxSpeed = speedV;
    
    flock(boids);
    update(_warpAround);
   
    
    
}

void ADDAC_Boid::update(bool _warpAround){ // DO SOMETHING !
    
    vel.x += ac.x;   // Update velocity
    vel.y += ac.y;
    vel.x = constrain(vel.x, -maxSpeed, maxSpeed);  // Limit speed
	vel.y = constrain(vel.y, -maxSpeed, maxSpeed);  // Limit speed
    pos.add(vel);
    ac.x = 0;  // Reset accelertion to 0 each cycle
    ac.y = 0;
    
    
    if(_warpAround){
    if (pos.x < -r) pos.x = maxWidth+r;
    if (pos.y < -r) pos.y = maxHeight+r;
    if (pos.x > maxWidth+r) pos.x = -r;
    if (pos.y > maxHeight+r) pos.y = -r;
    }
    
    else{
    
        if (pos.x < -r){ pos.x=-r; vel.x*=-1;}
        if (pos.y < -r){ pos.y=-r; vel.y*=-1;}
        if (pos.x > maxWidth+r){ pos.x=maxWidth+r; vel.x*=-1;}
        if (pos.y > maxHeight+r){ pos.y=maxHeight+r; vel.y*=-1;}
    }
    
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





// A method that calculates a steering vector towards a target
// Takes a second argument, if true, it slows down as it approaches the target
ADDAC_PVector ADDAC_Boid::steer(ADDAC_PVector target, bool slowdown) {
    ADDAC_PVector steer;  // The steering vector
    ADDAC_PVector desired; // A vector pointing from the location to the target
    desired.x=target.x-pos.x;
    desired.y=target.y-pos.y;
    
    float d = dist(target, pos); // Distance from the target is the magnitude of the vector
    
	// If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {
		
		desired.div(d); // Normalize desired
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((slowdown) && (d < 100.0f)) {
			desired.mult(maxSpeed * (d/100.0f)); // This damping is somewhat arbitrary
		} else {
			desired.mult(maxSpeed);
		}
		// Steering = Desired minus Velocity
		steer.x = desired.x - vel.x;
        steer.y = desired.y - vel.y;
		
        steer.x = constrain(steer.x, -maxForce, maxForce); // Limit to maximum steering force
		steer.y = constrain(steer.y, -maxForce, maxForce); 
    }
    return steer;
}





ADDAC_PVector ADDAC_Boid::separate(ADDAC_Boid boids[4]) {
    
    float desiredseparation = separationV;
    ADDAC_PVector steer;
    int count = 0;
	
    // For every boid in the system, check if it's too close
    for (int i = 0 ; i < 4; i++) {
		ADDAC_Boid other = boids[i];
		float d = dist(pos, other.pos);
		// If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
		if ((d > 0) && (d < desiredseparation)) {
			
			// Calculate vector pointing away from neighbor
			ADDAC_PVector diff;
            diff.x = pos.x - other.pos.x;
            diff.y = pos.y - other.pos.y;
            
            diff.div(d);			// normalize
			diff.div(d);       // Weight by distance
			steer.add(diff);
			count++;            // Keep track of how many
		}
    }
    // Average -- divide by how many
    if (count > 0) {
		steer.div((float)count);
    }
	
	
    // As long as the vector is greater than 0
	float mag = sqrt(steer.x*steer.x + steer.y*steer.y);
    
    if (mag > 0) {
		// Implement Reynolds: Steering = Desired - Velocity
        
        steer.div(mag);
        steer.mult(maxSpeed);
        steer.sub(vel);
        steer.x = constrain(steer.x,-maxForce, maxForce);
        steer.y = constrain(steer.y,-maxForce, maxForce);
        
    }
    return steer;
    
}




// Alignment
// For every nearby boid in the system, calculate the average velocity
ADDAC_PVector ADDAC_Boid::align(ADDAC_Boid boids[4]) {
    float neighbordist = alignV;
    ADDAC_PVector steer;
    int count = 0;
    for (int i = 0 ; i < 4; i++) {
		ADDAC_Boid other = boids[i];
		
		float d = dist(pos, other.pos);
		if ((d > 0) && (d < neighbordist)) {
			steer.add(other.vel);
			count++;
		}
    }
    if (count > 0) {
		steer.div((float)count);
    }
	
    // As long as the vector is greater than 0
	float mag = sqrt(steer.x*steer.x + steer.y*steer.y);
    if (mag > 0) {
		// Implement Reynolds: Steering = Desired - Velocity
		steer.div(mag);
		steer.mult(maxSpeed);
		steer.sub(vel);
		steer.x = constrain(steer.x, -maxForce, maxForce);
		steer.y = constrain(steer.y, -maxForce, maxForce);
    }
    return steer;
}




// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
ADDAC_PVector ADDAC_Boid::cohesion(ADDAC_Boid boids[4]) {
    float neighbordist = cohesionV;
    ADDAC_PVector sum;   // Start with empty vector to accumulate all locations
    int count = 0;
    for (int i = 0 ; i < 4; i++) {
		ADDAC_Boid other = boids[i];
		float d = dist(pos, other.pos);
		if ((d > 0) && (d < neighbordist)) {
			// Add location
            sum.add(other.pos);
			count++;
		}
    }
    if (count > 0) {
		sum.div((float)count);
		return steer(sum, false);  // Steer towards the location
    }
    return sum;
}



// --------------------------------------------------------------------------- END ----------------------------------
//



float ADDAC_Boid::dist(ADDAC_PVector pt1, ADDAC_PVector pt2){  
    
    return sqrt(double((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y)));
}
