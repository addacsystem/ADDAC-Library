/*
 * ADDAC_Spiral
 * 
 *
 */

#ifndef ADDAC_Spiral_h
#define ADDAC_Spiral_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


#include "ADDAC_PVector.h"
#include "ADDAC_Timer.h"

#define width 1000
#define height 1000

#define numB 48


class ADDAC_Points{

public:
    
    int position;
    
    ADDAC_PVector origin;
    ADDAC_PVector pos;
    ADDAC_PVector vel;
    float inc;
    float slot;
    float slotSize;
    bool activated;
    float teste;
    
    float speed;
    
    ADDAC_Timer timer;
    ADDAC_Points(){}
    
    ADDAC_Points(int _position){
    
        origin.set(width/2, height/2);
        pos.set(width/2, height/2);
        vel.set(0, 0);
       
        position=(20*_position);
        speed=1000.0f;
        slotSize=numB/6;
        
        if (_position<slotSize) slot = 0;
        else if (_position<(slotSize)*2) slot = 1;
        else if (_position<(slotSize)*3) slot = 2;
        else if (_position<(slotSize)*4) slot = 3;
        else if (_position<(slotSize)*5) slot = 4;
        else if (_position<(slotSize)*6) slot = 5;
        
    }
    
    void setup(){
        
        
    }


    void update(){
        
        pos.x = position/5 * cos(inc) + width/2;
        pos.y = position/5 * sin(inc) + height/2;
        
        
        inc += sqrt(((numB-position/numB)*(numB-position/numB)))/speed;
        
        checkAngle(pos);
        
        }
    
    
    
    void checkAngle(ADDAC_PVector _angleToCheck) {
        
    
        float angle = atan2(origin.x-_angleToCheck.x,origin.y-_angleToCheck.y);
        teste=angle;
        
        float tresh = 0.035f;    
        if(angle+tresh > -PI/2 && angle-tresh < -PI/2)
            activated = 1;
    }

    
    

};



class ADDAC_Spiral{
public:
	ADDAC_Spiral();
    
    
    void setup();	
    void update();
    
    void checkSlots();
    
    void setSpeed(float _speed);
	
    ADDAC_Points point[numB];
        ADDAC_Timer tm;
    
    bool slot[6];
    
    
    

	
};
#endif
