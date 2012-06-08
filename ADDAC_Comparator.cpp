 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Comparator.h"

//-----------------------------------------------------------------------ADDAC  COMPARATOR-----------------

ADDAC_Comparator::ADDAC_Comparator(){	// INITIALIZE CLASS
	

	
	//Serial.println("ADDAC_Comparator INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//


bool ADDAC_Comparator::Comparator(float _input, float _tresh){ 
	
    triggerComparator=false;
    
    
    if(_input>=_tresh && !triggerState){ // TRUE
        triggerState = true;
        triggerComparator=true;
    
    }
    else if(_input>=_tresh && triggerState){
        triggerComparator=false;
        _input=0;
    }
    else if(_input<=_tresh && triggerState){
       triggerState=false;
    }
    
    
	return triggerComparator;

}



bool ADDAC_Comparator::Comparator(float _input, float _tresh, float _delay){ 
  
    
    oldTime=millis();
    
    if(triggerTimeCount) timeEleapsed =timeEleapsed+abs(time-oldTime);
    
    if(_input>=_tresh && !triggerState){ // TRUE
        
        triggerState = true;
        triggerTimeCount=true;
        
    }
    else if(_input>=_tresh && triggerState){
        _input=0;
    }
    else if(_input<=_tresh && triggerState){
        triggerState=false;
    }
    
    
        
    time=millis(); 
    
    if(timeEleapsed > _delay){
                
        triggerComparator=true;    
        triggerTimeCount=false;
        timeEleapsed=0;
        
    }
    
    else{
        triggerComparator=false; 
    }
    return triggerComparator;
}


// --------------------------------------------------------------------------- END ----------------------------------
//