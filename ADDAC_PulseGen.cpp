 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_PulseGen.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_PulseGen::ADDAC_PulseGen(){	// INITIALIZE CLASS
	

	
	//Serial.println("ADDAC_Empty INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


void ADDAC_PulseGen::setup(){ // DO SOMETHING !
	
	for (int i = 0; i < numB; i++){
    
        point[i] =  ADDAC_Points(i);
    
    }
    
    for (int i = 0; i < 6; i++){
        
        slot[i] =  false;
        
    }
    
}



void ADDAC_PulseGen::update(int _pulsePerCluster, float _speed, float _factor, float _offset){ // DO SOMETHING !
	
	for (int i = 0; i < numB; i++){
        
        point[i].update(_pulsePerCluster, _speed, _factor, _offset);
        
        
    }
    
    checkSlots();
    
    
    
}
    
    void ADDAC_PulseGen::checkSlots(){
    
        int count1=0;
        int count2=0;
        int count3=0;
        int count4=0;
        int count5=0;
        int count6=0;
        
        for(int i = 0; i < numB; i++){
            
           
            //slot0
            if(i>=39)
                if(point[i].activated)
                    slot[0]=true;
            
                else count1++;
            
            if(count1>7){
                count1=0;
                slot[0]=false;
            }     
            
            
            //slot1
            if(i>=31 && i<39){
                if(point[i].activated)
                    slot[1]=true;
                
                else count2++;
                
                if(count2>7){
                    count2=0;
                    slot[1]=false;
                }
                
                
            }
            
            
            //slot2
            if(i>=23 && i<31){
                if(point[i].activated)
                    slot[2]=true;
                
                else count3++;
                
                if(count3>7){
                    count3=0;
                    slot[2]=false;
                }
                
                
            }
            
            //slot3
            if(i>=15 && i<23){
                if(point[i].activated)
                    slot[3]=true;
                
                else count4++;
                
                if(count4>7){
                    count4=0;
                    slot[3]=false;
                }
            }
            
            //slot4
            if(i>=7 && i<15){
                if(point[i].activated)
                    slot[4]=true;
                
                else count5++;
                
                if(count5>7){
                    count5=0;
                    slot[4]=false;
                }
                
                
            }
            
            
            //slot4
            if(i<=7){
                if(point[i].activated)
                    slot[5]=true;
                
                else count6++;
                
                if(count6>7){
                    count6=0;
                    slot[5]=false;
                }
                
                
            }
            
            
        }            
            
            
        
//            if(point[i].activated){
//                
//            switch (point[i].slot) {
//                
//                case 1:
//                    slot[0]=1;
//                    //point[i].activated=0;
//                    break;
//
//                case 2:
//                    slot[1]=1;
//                    //point[i].activated=0;
//                    break;
//
//                case 3:
//                    slot[2]=1;
//                    //point[i].activated=0;
//                    break;
//
//                case 4:
//                    slot[3]=1;
//                    //point[i].activated=0;
//                    break;
//
//                case 5:
//                    slot[4]=1;
//                    //point[i].activated=0;
//                    break;
//
//                case 6:
//                    slot[5]=1;
//                    //point[i].activated=0;
//                    break;
//                                 
//            }
//            
//
//            }
//        }
//
//        
//        
//        
//        //Reset slots - std 30millis | 60 millis for now!
//        if(tm.set(60)){
//            for (int p = 0; p < 6; p++){
//                
//                    slot[p]=0;
//            }
//        }

    }



void ADDAC_PulseGen::reset(){
    
    
    for (int i=0; i<numB; i++) {
         
         point[i].pos.x=0;
         point[i].pos.y=0;
         point[i].inc=0;
        
    }



}

// --------------------------------------------------------------------------- END ----------------------------------
//