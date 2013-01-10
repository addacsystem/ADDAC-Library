 
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



void ADDAC_Spiral::update(float _speed, float _factor, float _offset){ // DO SOMETHING !
	
	for (int i = 0; i < numB; i++){
        
        point[i].update(_speed, _factor, _offset);
        checkSlots(i);
    }
    
    //Reset slots - std 30millis | 60 millis for now!
    if(tm.set(60)){
        for (int p = 0; p < 6; p++){
            if(slot[p])
                slot[p]=0;
        }
    }
    
}
    
    void ADDAC_Spiral::checkSlots(int i){
    
      //TRIGGERS VS GATES - triggers for now!
            
            if( point[i].activated){
                
            switch (point[i].slot) {
                
                case 0:
                    slot[0]=1;
                    point[i].activated=0;
                    break;

                case 1:
                    slot[1]=1;
                    point[i].activated=0;
                    break;

                case 2:
                    slot[2]=1;
                    point[i].activated=0;
                    break;

                case 3:
                    slot[3]=1;
                    point[i].activated=0;
                    break;

                case 4:
                    slot[4]=1;
                    point[i].activated=0;
                    break;

                case 5:
                    slot[5]=1;
                    point[i].activated=0;
                    break;
            }

        }

    }

// --------------------------------------------------------------------------- END ----------------------------------
//