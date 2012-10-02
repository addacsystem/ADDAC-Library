 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_CvToMidi.h"

//-----------------------------------------------------------------------ADDAC CvToMidi-----------------

ADDAC_CvToMidi::ADDAC_CvToMidi(){	// INITIALIZE CLASS
	
	
	
	//Serial.println("ADDAC_CvToMidi INITIALIZED");
}



void ADDAC_CvToMidi::calcNote(float _cv, int _velocity, int _channel){
    
  
    int Midinote = int(((_cv*100/5.0)*12.0)-110); ///CALCULOS INCORRECTOS ~=
    
    if(Midinote!=oldNoteOut){
        sendNoteOn(Midinote,_velocity,_channel);
        sendNoteOff(oldNoteOut,_velocity,_channel);
        oldNoteOut = Midinote;
    }
    
//    Serial.print(Midinote);
//    Serial.print("  ");
//    Serial.print(oldNoteOut);
}


void ADDAC_CvToMidi::calcCC(int _CCnumber, float _cv, int _channel){
    
    int cvOut = int(_cv*127);
    
    if(abs(cvOut-oldCvOut)>1){
        sendControlChange(_CCnumber,cvOut,_channel);
        oldCvOut=cvOut;
        
    }
   
}