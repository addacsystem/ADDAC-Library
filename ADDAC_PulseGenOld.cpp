 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_PulseGenOld.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_PulseGenOld::ADDAC_PulseGenOld(){	// INITIALIZE CLASS
	

	
	//Serial.println("ADDAC_Empty INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_PulseGenOld::setup(){ // DO SOMETHING !
	
	for (int i = 0; i < numB; i++){
    
        point[i] =  ADDAC_Points(i);
    
    }
    
}



void ADDAC_PulseGenOld::update(int _pulsePerCluster, float _speed, float _factor, float _offset){ // DO SOMETHING !
	
	for (int i = 0; i < numB; i++){
        
        point[i].update(_pulsePerCluster, _speed, _factor, _offset);
        
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
    
    void ADDAC_PulseGenOld::checkSlots(int i){
    
      //TRIGGERS VS GATES - triggers for now!
            
            if(point[i].activated){
                
            switch (point[i].slot) {
                
                case 1:
                    slot[0]=1;
                    point[i].activated=0;
                    break;

                case 2:
                    slot[1]=1;
                    point[i].activated=0;
                    break;

                case 3:
                    slot[2]=1;
                    point[i].activated=0;
                    break;

                case 4:
                    slot[3]=1;
                    point[i].activated=0;
                    break;

                case 5:
                    slot[4]=1;
                    point[i].activated=0;
                    break;

                case 6:
                    slot[5]=1;
                    point[i].activated=0;
                    break;
                                 
            }

        }

    }



void ADDAC_PulseGenOld::reset(){
    
    
    for (int i=0; i<numB; i++) {
         
         point[i].pos.x=0;
         point[i].pos.y=0;
         point[i].inc=0;
        
    }



}

// --------------------------------------------------------------------------- END ----------------------------------
//