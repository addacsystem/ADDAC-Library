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
#include "ADDAC_Lin2Log.h"

#define width 1000
#define height 1000

#define numB 48


class ADDAC_Points{

public:
    

    
    ADDAC_PVector origin;
    ADDAC_PVector pos;
    ADDAC_PVector vel;
    
    bool activated;
    
    int slot;
    int position;
    
    float slotSize;
    float inc;
    
    float factor;
    float offSet;
    float speed;
    
    ADDAC_Timer timer;
    ADDAC_Lin2Log ltl;
    ADDAC_Points(){}
    
    ADDAC_Points(int _position){
    
        origin.set(width/2, height/2);
        pos.set(width/2, height/2);
        vel.set(0, 0);
       
        position=(20*_position);
        speed=1000.0f;
        slotSize=numB/6;
        
        factor = 0.01f;
        offSet=48;
        speed=0.05f;
        
        if (_position<slotSize) slot = 5;
        else if (_position<(slotSize)*2) slot = 4;
        else if (_position<(slotSize)*3) slot = 3;
        else if (_position<(slotSize)*4) slot = 2;
        else if (_position<(slotSize)*5) slot = 1;
        else if (_position<(slotSize)*6) slot = 0;
        
    }
    

    void update(float _speed, float _factor, float _offset){
        
        speed=ltl.calc(_speed,0.85f)+0.0001f;
        //speed=_speed;
       // Serial.println(speed);
        factor=_factor;
        offSet=_offset;
        
        pos.x = position*6.0f * cos(inc) + width/2;
        pos.y = position*6.0f * sin(inc) + height/2;
        
        
        float temp = ((float)(abs(offSet-position)+1.0f)/numB)/10.0f+1.0f;
        float temp2 = (temp-1.0f)*factor*100.0f+1.0f;
        
        
        inc+=(temp*temp2)*speed;

        
        checkAngle(pos);
        
        }
    
    
    
    void checkAngle(ADDAC_PVector _angleToCheck) {
        
    
        float angle = atan2(origin.x-_angleToCheck.x,origin.y-_angleToCheck.y);
        
        float tresh = 0.055f;    
        
        if(angle+tresh > -PI/2 && angle-tresh < -PI/2)
            activated = 1;
    }

};



class ADDAC_Spiral{
public:
	ADDAC_Spiral();
    
    
    void setup();	
    void update(float _speed, float _factor, float _offset);
    
    void checkSlots(int i);
    
	
    ADDAC_Points point[numB];
    ADDAC_Timer tm;
    
    bool slot[6];
    
    
    

	
};
#endif
