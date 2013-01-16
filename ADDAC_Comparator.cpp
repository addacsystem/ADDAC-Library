     
    /*
     * Some hints about what this Class does!
     *
    */


    #include "ADDAC_Comparator.h"

    //-----------------------------------------------------------------------ADDAC  COMPARATOR-----------------
    /*! \brief Default construtor for ADDAC_Comparator */
    ADDAC_Comparator::ADDAC_Comparator(){	// INITIALIZE CLASS
        
        triggerState=false;
         triggerComparator=false;
         triggerStateChange=false;
         triggerStateChangeUP=false;
         triggerComparatorRise=false;
         triggerStateRise=false;
         triggerComparatorFall=false;
         triggerStateFall=false;
         triggerTimeCount=false;
         rising=false;
         falling=false;
        
        //Serial.println("ADDAC_Comparator INITIALIZED");
    }



    // --------------------------------------------------------------------------- UPDATE -------------------------
    //

/*! \brief calculate comparator
 \param _state activate comparator : RISE, FALL or CHANGE
 \param _input input to comparate 
 \param _threshold threshold for comparator
 */
    bool ADDAC_Comparator::calc(int _state, float _input, float _threshold){ 

        triggerComparator=false;
        
        rising = false;
        falling = false;

        
        if (_state==0) {
            
            
            if(_input>=_threshold && !triggerStateRise){ // TRUE
                triggerStateRise = true;
                triggerComparatorRise=true;
                
            }
            else if(_input>=_threshold && triggerStateRise){
                triggerComparatorRise=false;
                _input=0;
            }
            else if(_input<=_threshold && triggerStateRise){
                triggerStateRise=false;
            }
            
            
            return triggerComparatorRise;
        }
        
        
        if (_state==1 ) {
            
            
            if(_input<=_threshold && !triggerStateFall){ // TRUE
                triggerStateFall = true;
                triggerComparatorFall=true;
                
            }
            else if(_input<=_threshold && triggerStateFall){
                triggerComparatorFall=false;
                _input=1;
            }
            else if(_input>=_threshold && triggerStateFall){
                triggerStateFall=false;
            }
            
            
            return triggerComparatorFall;
        }
        
        if(_state==2){
            
            
            if (_input > oldInput) { //up - Rising
                
                if(_input>=_threshold && !triggerStateChange){ // TRUE
                    triggerStateChange = true;
                    rising=true;
                    
                }
                else if(_input>=_threshold && triggerStateChange){
                    rising=false;
                    _input=0;
                }
                else if(_input<=_threshold && triggerStateChange){
                    triggerStateChange=false;
                }
            
                oldInput= _input;
            }
            
              
            if(_input < oldInput){ // down - Falling
                        //rising=false;

                if(_input<=_threshold && !triggerStateChange){ // TRUE
                    triggerStateChange = true;
                    falling=true;
                    
                }
                else if(_input<=_threshold && triggerStateChange){
                    falling=false;
                    _input=1;
                }
                else if(_input>=_threshold && triggerStateChange){
                    triggerStateChange=false;
                }
                
                oldInput= _input;

            }
                
             
            
             if(rising)
                 return rising;
            else if(falling)
                return falling;
            else 
                return 0;
       }
        
        
    }


/*! \brief calculate comparator with delay
 \param _state activate comparator : RISE, FALL or CHANGE
 \param _input input to comparate 
 \param _threshold threshold for comparator
 \param _delay comparator delay
 */
    bool ADDAC_Comparator::calc(int _state, float _input, float _threshold, float _delay){ 
      
        triggerComparator=false;

        oldTime=millis();
        
        if(triggerTimeCount) timeEleapsed =timeEleapsed+abs(time-oldTime);
        
        if (_state == 0) {
           
        
        if(_input>=_threshold && !triggerStateRise){ // TRUE
            
            triggerStateRise = true;
            triggerTimeCount=true;
            timeEleapsed=0;
            
        }
        else if(_input>=_threshold && triggerStateRise){
            _input=0;
        }
        else if(_input<=_threshold && triggerStateRise){
            triggerStateRise=false;
        }
            
            
            
            time=millis(); 
            
            if(timeEleapsed > _delay){
                
                triggerComparatorRise=true;    
                triggerTimeCount=false;
                timeEleapsed=0;
                
            }
            
            else{
                triggerComparatorRise=false; 
            }
            return triggerComparatorRise;
            
        }
        
        
        if (_state == 1) {
            
            
            if(_input<=_threshold && !triggerStateFall){ // TRUE
                
                triggerState = true;
                triggerTimeCount=true;
                timeEleapsed=0;
                
            }
            else if(_input<=_threshold && triggerStateFall){
                _input=1;
            }
            else if(_input>=_threshold && triggerStateFall){
                triggerStateFall=false;
            }
            
            
            time=millis(); 
            
            if(timeEleapsed > _delay){
                
                triggerComparatorFall=true;    
                triggerTimeCount=false;
                timeEleapsed=0;
                
            }
            
            else{
                triggerComparatorFall=false; 
            }
            return triggerComparatorFall;
            
        }
        
            
        
        if(_state==2){
            
            
            if (_input > oldInput) { //up - Rising
            

              
                if(_input>=_threshold && !triggerStateChange){ // TRUE
                    
                    rising=true;
                    triggerStateChange = true;
                    triggerTimeCount=true;
                    timeEleapsed=0;
                    
                }
                else if(_input>=_threshold && triggerStateChange){
                    _input=0;
                }
                else if(_input<=_threshold && triggerStateChange){
                    triggerStateChange=false;
                }
                oldInput= _input;
            }

            if(_input < oldInput){ // down - Falling
            
                
                
                if(_input<=_threshold && !triggerStateChange){ // TRUE
                    
                    falling=true;
                    triggerStateChange = true;
                    triggerTimeCount=true;
                    timeEleapsed=0;
                    
                }
                else if(_input<=_threshold && triggerStateChange){

                    _input=1;
                }
                else if(_input>=_threshold && triggerStateChange){
                    triggerStateChange=false;
                }
            oldInput= _input;
            
            }
            
            
            }  
        
        
        time=millis(); 
        
        if(timeEleapsed > _delay){
                    
                       
            triggerTimeCount=false;
            timeEleapsed=0;
            
            if(rising)
                return rising;
            else if(falling)
                return falling;
            

            
        }
        
        else 
        
            return false;        
      
    }


    // --------------------------------------------------------------------------- END ----------------------------------
    //