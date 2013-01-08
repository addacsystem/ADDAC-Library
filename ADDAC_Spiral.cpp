 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Spiral.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Spiral::ADDAC_Spiral(){	// INITIALIZE CLASS
	

	
	//Serial.println("ADDAC_Empty INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_Spiral::setup(){ // DO SOMETHING !
	
	for (int i = 0; i < numB; i++){
    
        point[i] =  ADDAC_Points(i);
    
    
    }
    
    
}



void ADDAC_Spiral::update(){ // DO SOMETHING !
	
	for (int i = 0; i < numB; i++){
        
        point[i].update();
        
    }
    checkSlots();
}
    
    void ADDAC_Spiral::checkSlots(){
    
        for (int i = 0; i < numB; i++){
            
            if(point[i].slot==0 && point[i].activated){
                slot[0]=1;
                point[i].activated=0;
            }
            
            if(point[i].slot==1 && point[i].activated){
                slot[1]=1;
                point[i].activated=0;
            }

            
            if(point[i].slot==2 && point[i].activated){
                slot[2]=1;
                point[i].activated=0;
            }

            
            if(point[i].slot==3 && point[i].activated){
                slot[3]=1;
                point[i].activated=0;
            }

            
            if(point[i].slot==4 && point[i].activated){
                slot[4]=1;
                point[i].activated=0;
            }

            
            if(point[i].slot==5 && point[i].activated){
                slot[5]=1;
                point[i].activated=0;
            }
            
        }
        
        if(tm.set(100)){
        for (int i = 0; i < 6; i++){
            if(slot[i])
            slot[i]=0;
        }
        }

    }


void ADDAC_Spiral::setSpeed(float _speed){
    
for (int i = 0; i < numB; i++){
    point[i].speed=(_speed*10000.0f)+10.0f;

}
}
// --------------------------------------------------------------------------- END ----------------------------------
//