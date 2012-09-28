 

#include "ADDAC.h"
//#include "ADDAchannels.h"
#include "ADDAgateSequencer.h"

#include <ADDAC_DigitalWriteFast.h>


// FUNCTIONS :
//#include "Functions/RANDOM.h"
//#include "Functions/LISS.h"
//#include "Functions/QUAD.h"

/*
ADDAsequencer1 ADDAgateSequencer(1, 1, 1, 50, 8, 0); // id, expansion, outputChannel, bpm, steps, byte sequence

ADDAgateSequencer.changeStep(2, 1); // step, gate
ADDAgateSequencer.changeStep(4, 0); // step, gate

ADDAgateSequencer.add8Steps(0, B10101010); // slot, 8 steps
ADDAgateSequencer.add8Steps(1, B10101010); // slot, 8 steps

ADDAgateSequencer.stepOffset(3); // stepOffset
ADDAgateSequencer.memoryPreset(3); //memoryPreset

//volatile irparams_t irparams;
//ADDAchannel channel1(1, 0);
//ADDAchannel channel2(2, 20000);
//ADDAchannel channel3(3, 40000);
 

*/
// POINTERS
long *pointerDACvolts;

//-----------------------------------------------------------------------ADDAC-----------------

/*! \brief Default constructor for ADDAC. */
ADDAC::ADDAC(){	
	for(int i=0;i<8;i++){
		DACvolts[i]=0; 
		DACtimes[i]=0; 
		direction[i]=true;
		Direction=true;
		rndStep[i]=0;
	}
	Serial.println("SETUP COMPLETE");
}

/*! \brief Setup the ADDAC main class, this should be called in the setup() from Arduino environment. */
void ADDAC::setup(){
	//EXTERNALS
	//
	//manual INS A
	truthTableA[0]=0;
	truthTableA[1]=1;
	truthTableA[2]=0;
	truthTableA[3]=1;
	truthTableA[4]=0;
	truthTableA[5]=1;
	truthTableA[6]=0;
	truthTableA[7]=1;
	//
	truthTableB[0]=0;
	truthTableB[1]=0;
	truthTableB[2]=1;
	truthTableB[3]=1;
	truthTableB[4]=0;
	truthTableB[5]=0;
	truthTableB[6]=1;
	truthTableB[7]=1;
	//
	truthTableC[0]=0;
	truthTableC[1]=0;
	truthTableC[2]=0;
	truthTableC[3]=0;
	truthTableC[4]=1;
	truthTableC[5]=1;
	truthTableC[6]=1;
	truthTableC[7]=1;
	//define 4051 pin modes
	// A
	pinMode(manualInAs0, OUTPUT);
	pinMode(manualInAs1, OUTPUT); 
	pinMode(manualInAs2, OUTPUT);
	// B
	pinMode(manualInBs0, OUTPUT);
	pinMode(manualInBs1, OUTPUT); 
	pinMode(manualInBs2, OUTPUT);
	// C
	pinMode(manualInCs0, OUTPUT);
	pinMode(manualInCs1, OUTPUT); 
	pinMode(manualInCs2, OUTPUT);
	
	// CV INPUTS A
	pinMode(cvInAs0, OUTPUT);
	pinMode(cvInAs1, OUTPUT); 
	pinMode(cvInAs2, OUTPUT);
	// B
	pinMode(cvInBs0, OUTPUT);
	pinMode(cvInBs1, OUTPUT); 
	pinMode(cvInBs2, OUTPUT);
	// C
	pinMode(cvInCs0, OUTPUT);
	pinMode(cvInCs1, OUTPUT); 
	pinMode(cvInCs2, OUTPUT);
	
	//
	// GATES INPUTS A
	pinMode(gateInAlatch, OUTPUT);
	pinMode(gateInAclock, OUTPUT);
	pinMode(gateInAdata, INPUT);
	// GATES INPUTS B
	pinMode(gateInBlatch, OUTPUT);
	pinMode(gateInBclock, OUTPUT);
	pinMode(gateInBdata, INPUT);
	// GATES INPUTS C
	pinMode(gateInClatch, OUTPUT);
	pinMode(gateInCclock, OUTPUT);
	pinMode(gateInCdata, INPUT);
	
	//
	// GATES OUTPUT A
	pinMode(gateOutAlatch, OUTPUT);
	pinMode(gateOutAclock, OUTPUT);
	pinMode(gateOutAdata, OUTPUT);
	// GATES OUTPUT B
	pinMode(gateOutBlatch, OUTPUT);
	pinMode(gateOutBclock, OUTPUT);
	pinMode(gateOutBdata, OUTPUT);
	// GATES OUTPUT C
	pinMode(gateOutClatch, OUTPUT);
	pinMode(gateOutCclock, OUTPUT);
	pinMode(gateOutCdata, OUTPUT);
	
	// GATES OUT A VALUES
	gateValuesOutA[0]=0;
	gateValuesOutA[1]=0;
	gateValuesOutA[2]=0;
	gateValuesOutA[3]=0;
	gateValuesOutA[4]=0;
	gateValuesOutA[5]=0;
	gateValuesOutA[6]=0;
	gateValuesOutA[7]=0;
	
	//ONBOARD
	//
	//define shiftIn pin modes
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT); 
	pinMode(dataPin, INPUT);
	//set AD5668 pin modes
	pinMode(ENVELOPE, INPUT);
	pinMode(DATAOUT, OUTPUT);
	pinMode(SPICLK, OUTPUT);
	pinMode(SLAVESELECT, OUTPUT);
	pinMode(CLR, OUTPUT);
	//INIT AD5668
	//disable DAC to start with
	digitalWriteFast(DATAOUT,LOW);
	digitalWriteFast(SPICLK, LOW);
	digitalWriteFast(SLAVESELECT, LOW);
	digitalWriteFast(CLR, LOW);
	delay(50);
	digitalWriteFast(CLR, HIGH);
	delay(50);
	write(SETUP_INTERNAL_REGISTER, 0, 1); //set up internal register on DAC
	delay(100);
	write(POWER, 0, 0);
	delay(100);
	write(RESET, 0, 0);
	delay(100);
	
	fMin=0;
	fMax=2000;
	fSeed=300;
	vMin=0;
	vMax=addacMaxResolution;
	//Start the timer and get the timer reload value.
	//timerLoadValue=SetupTimer2(40000);
	//set up interupt for zero crossing detector
	//attachInterrupt(0, zero, RISING);	
	pointerDACvolts=DACvolts;
}
// --------------------------------------------------------------------------- ONBOARD POT -------------------------
//
/*! \brief Update the ADDAC main class, this should be called in the update() from Arduino environment. */
void ADDAC::update(){
	readMODEswitch();
#ifndef VS3
	onboardVal=analogRead(onboardPotPin);
	onboardValMapped=onboardVal/1023.0f*65535.0f;
#endif

}	

// --------------------------------------------------------------------------- ONBOARD POT -------------------------
//
/*! \brief Read and return on Board Pot Value (VS.I & II only) */
int ADDAC::readOnboardPot(){
		return onboardVal;
}

// --------------------------------------------------------------------------- READ CVS IN - ADDAC002 -----------
//
/*! \brief Read and return all Cv Inputs from ADDAC002 expansion
 \param _socket  connected socket : A or B	
 */
void ADDAC::ReadCvs(int _socket){ // INTERNAL READING
	if(_socket == A){
		for(int i=0;i<6;i++){
			StoreCvs(_socket,i); 
			//cvValuesAMapped[i]=cvValuesA[i]/1023.0f*65535.0f;
		}
	}else if(_socket == B){
		for(int i=0;i<6;i++){
			StoreCvs(_socket,i); 
			//cvValuesBMapped[i]=cvValuesB[i]/1023.0f*65535.0f;
		}
	}else if(_socket == C){
		for(int i=0;i<6;i++){
			StoreCvs(_socket,i); 
			//cvValuesCMapped[i]=cvValuesC[i]/1023.0f*65535.0f;
		}
	}
}

/*! \brief Read and return selected Cv Input from ADDAC002 expansion
\param _socket  connected socket : A or B	
\param _channel input to rea : 0 - 5 	
 */

float ADDAC::ReadCv(int _socket, int _channel){ // EXTERNAL READING

	if(_socket == A){
		digitalWriteFast(cvInAs0, truthTableA[_channel]); 
		digitalWriteFast(cvInAs1, truthTableB[_channel]); 
		digitalWriteFast(cvInAs2, truthTableC[_channel]); 
        cvValuesA[_channel]=analogRead(cvInApin)/1023.0f;
		return cvValuesA[_channel];
	}else if(_socket == B){
		digitalWriteFast(cvInBs0, truthTableA[_channel]); 
		digitalWriteFast(cvInBs1, truthTableB[_channel]); 
		digitalWriteFast(cvInBs2, truthTableC[_channel]); 
		cvValuesB[_channel]=analogRead(cvInBpin)/1023.0f;
		return cvValuesB[_channel];
	}else if(_socket == C){
		digitalWriteFast(cvInCs0, truthTableA[_channel]); 
		digitalWriteFast(cvInCs1, truthTableB[_channel]); 
		digitalWriteFast(cvInCs2, truthTableC[_channel]); 
		cvValuesC[_channel]=analogRead(cvInCpin)/1023.0f;
		return cvValuesC[_channel];
	}
}

/*! \ Store CV inputs - internal usage*/

void ADDAC::StoreCvs(int _socket, int _channel){ // Store for prints
   
	if(_socket == A){
		digitalWriteFast(cvInAs0, truthTableA[_channel]); 
		digitalWriteFast(cvInAs1, truthTableB[_channel]); 
		digitalWriteFast(cvInAs2, truthTableC[_channel]); 
        cvValuesA[_channel]=analogRead(cvInApin)/1023.0f;

	}else if(_socket == B){
		digitalWriteFast(cvInBs0, truthTableA[_channel]); 
		digitalWriteFast(cvInBs1, truthTableB[_channel]); 
		digitalWriteFast(cvInBs2, truthTableC[_channel]); 
		cvValuesB[_channel]=analogRead(cvInBpin)/1023.0f;
	}else if(_socket == C){
		digitalWriteFast(cvInCs0, truthTableA[_channel]); 
		digitalWriteFast(cvInCs1, truthTableB[_channel]); 
		digitalWriteFast(cvInCs2, truthTableC[_channel]); 
		cvValuesC[_channel]=analogRead(cvInCpin)/1023.0f;

	}
}

/*! \brief Print all Cv Inputs from ADDAC002 expansion in Monitor Log - usefull for DEBUG
 \param _socket  connected socket - A or B	
 */

void ADDAC::PrintCvs(int _socket){
    if(_socket==A){
        Serial.print(" | CV0:");
        Serial.print(cvValuesA[0]);
        Serial.print(" | CV1:");
        Serial.print(cvValuesA[1]);
        Serial.print(" | CV2:");
        Serial.print(cvValuesA[2]);
        Serial.print(" | CV3:");
        Serial.print(cvValuesA[3]);
        Serial.print(" | CV4:");
        Serial.print(cvValuesA[4]);
        Serial.print(" | CV5:");
        Serial.print(cvValuesA[5]);
    }
    else if(_socket==B){
        Serial.print(" | CV0:");
        Serial.print(cvValuesB[0]);
        Serial.print(" | CV1:");
        Serial.print(cvValuesB[1]);
        Serial.print(" | CV2:");
        Serial.print(cvValuesB[2]);
        Serial.print(" | CV3:");
        Serial.print(cvValuesB[3]);
        Serial.print(" | CV4:");
        Serial.print(cvValuesB[4]);
        Serial.print(" | CV5:");
        Serial.print(cvValuesB[5]);
        
    }
    else if(_socket==C){
        Serial.print(" | CV0:");
        Serial.print(cvValuesC[0]);
        Serial.print(" | CV1:");
        Serial.print(cvValuesC[1]);
        Serial.print(" | CV2:");
        Serial.print(cvValuesC[2]);
        Serial.print(" | CV3:");
        Serial.print(cvValuesC[3]);
        Serial.print(" | CV4:");
        Serial.print(cvValuesC[4]);
        Serial.print(" | CV5:");
        Serial.print(cvValuesC[5]);
        
    }
}

/*! \brief Print selected Cv Input from ADDAC002 expansion in Monitor Log - usefull for DEBUG 
 \param _socket  connected socket : A or B	
 \param _channel input to rea : 0 - 5 	
 */

void ADDAC::PrintCv(int _socket, int _channel ){
    if(_socket==A){
        Serial.print(" | CV" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(cvValuesA[_channel]);
    }
    else if(_socket==B){
        Serial.print(" | CV" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(cvValuesB[_channel]);
    }
    else if(_socket==C){
        Serial.print(" | CV" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(cvValuesC[_channel]);
    }
}



// --------------------------------------------------------------------------- READ manualS IN - ADDAC003 -----------
//

/*! \brief Read and return all Manual inputs from ADDAC003 expansion
 \param _socket  connected socket - A or B	
 */

void ADDAC::ReadManuals(int _socket){ // INTERNAL READING
	for(int i=0;i<5;i++){
        if(_socket == A){
		 
            StoreManuals(_socket,i); 
		//manualValuesAMapped[i]=manualValuesA[i]/1023.0f*65535.0f;
        }
        else if(_socket == B){
            for(int i=0;i<5;i++){
                 StoreManuals(_socket,i);  
               // manualValuesBMapped[i]=manualValuesB[i]/1023.0f*65535.0f;
            }
        
        
        }
        
        else if(_socket == C){
            for(int i=0;i<5;i++){
                manualValuesC[i]=ReadManual(_socket,i); 
                //manualValuesCMapped[i]=manualValuesC[i]/1023.0f*65535.0f;
            }
            
            
        }
	}
}

/*! \brief Read and return selected Manual input from ADDAC003 expansion
 \param _socket  connected socket - A or B
  \param _channel input to rea : 0 - 4 	
 */


float ADDAC::ReadManual(int _socket,int _channel){ // EXTERNAL READING
     if(_socket == A){
	digitalWriteFast(manualInAs0, truthTableA[_channel]); 
	digitalWriteFast(manualInAs1, truthTableB[_channel]); 
	digitalWriteFast(manualInAs2, truthTableC[_channel]); 
    manualValuesA[_channel] =1-( analogRead(manualInApin)/1023.0f);
    return manualValuesA[_channel];
     }
    
    else if(_socket == B){
        digitalWriteFast(manualInBs0, truthTableA[_channel]); 
        digitalWriteFast(manualInBs1, truthTableB[_channel]); 
        digitalWriteFast(manualInBs2, truthTableC[_channel]); 
        manualValuesB[_channel] =1-( analogRead(manualInBpin)/1023.0f);
		return manualValuesB[_channel];
    }
    else if(_socket == C){
        digitalWriteFast(manualInCs0, truthTableA[_channel]); 
        digitalWriteFast(manualInCs1, truthTableB[_channel]); 
        digitalWriteFast(manualInCs2, truthTableC[_channel]); 
        manualValuesC[_channel] = 1-(analogRead(manualInCpin)/1023.0f);
		return manualValuesC[_channel];
    }
    

}


/*! \ Store Manual inputs - internal usage*/

void ADDAC::StoreManuals(int _socket,int _channel){ // EXTERNAL READING
    if(_socket == A){
        digitalWriteFast(manualInAs0, truthTableA[_channel]); 
        digitalWriteFast(manualInAs1, truthTableB[_channel]); 
        digitalWriteFast(manualInAs2, truthTableC[_channel]);
        manualValuesA[_channel]=1-(analogRead(manualInApin)/1023.0f);
       
         
    }
    
    else if(_socket == B){
        digitalWriteFast(manualInBs0, truthTableA[_channel]); 
        digitalWriteFast(manualInBs1, truthTableB[_channel]); 
        digitalWriteFast(manualInBs2, truthTableC[_channel]); 
        manualValuesB[_channel]=1-(analogRead(manualInBpin)/1023.0f);
       
    }
    else if(_socket == C){
        digitalWriteFast(manualInCs0, truthTableA[_channel]); 
        digitalWriteFast(manualInCs1, truthTableB[_channel]); 
        digitalWriteFast(manualInCs2, truthTableC[_channel]); 
        manualValuesC[_channel]=1-(analogRead(manualInCpin)/1023.0f);
     
    }
    
    
}


/*! \brief Print all Manual inputs from ADDAC003 expansion in Monitor Log - usefull for DEBUG 
 \param _socket  connected socket - A or B	
 */

void ADDAC::PrintManuals(int _socket){
    if(_socket==A){
        Serial.print(" | MANUAL0:");
        Serial.print(manualValuesA[0]);
        Serial.print(" | MANUAL1:");
        Serial.print(manualValuesA[1]);
        Serial.print(" | MANUAL2:");
        Serial.print(manualValuesA[2]);
        Serial.print(" | MANUAL3:");
        Serial.print(manualValuesA[3]);
        Serial.print(" | MANUAL4:");
        Serial.print(manualValuesA[4]);

    }
    else if(_socket==B){
        Serial.print(" | MANUAL0:");
        Serial.print(manualValuesB[0]);
        Serial.print(" | MANUAL1:");
        Serial.print(manualValuesB[1]);
        Serial.print(" | MANUAL2:");
        Serial.print(manualValuesB[2]);
        Serial.print(" | MANUAL3:");
        Serial.print(manualValuesB[3]);
        Serial.print(" | MANUAL4:");
        Serial.print(manualValuesB[4]);

        
    }
    else if(_socket==C){
        Serial.print(" | MANUAL0:");
        Serial.print(manualValuesC[0]);
        Serial.print(" | MANUAL1:");
        Serial.print(manualValuesC[1]);
        Serial.print(" | MANUAL2:");
        Serial.print(manualValuesC[2]);
        Serial.print(" | MANUAL3:");
        Serial.print(manualValuesC[3]);
        Serial.print(" | MANUAL4:");
        Serial.print(manualValuesC[4]);

        
    }
}

/*! \brief Print selected Manual input from ADDAC003 expansion in Monitor Log - usefull for DEBUG
 \param _socket  connected socket - A or B
 \param _channel input to rea : 0 - 4 	
 */


void ADDAC::PrintManual(int _socket, int _channel ){
    if(_socket==A){
        Serial.print(" | MANUAL" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(manualValuesA[_channel]);
    }
    else if(_socket==B){
        Serial.print(" | MANUAL" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(manualValuesB[_channel]);
    }
    else if(_socket==C){
        Serial.print(" | MANUAL" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(manualValuesC[_channel]);
    }
}




// --------------------------------------------------------------------------- READ GATES IN - ADDAC004 -----------
//

/*! \brief Read and return all Gate inputs from ADDAC004 expansion
 \param _socket  connected socket - A or B
  \param _invert  inverted read - true or false
 */
void ADDAC::ReadGates(int _socket, bool _invert){ // READS GATES AND UPDATES ARRAY
   
    // BJORN REQUEST FOR INVERTING / NON_INVERTING GATE READS 
    // (ALSO AVAILABLE TO CORRECT CIRCUIT "BUG" WITH INVERTED READINGS FROM ADDAC004)
    
      if(_socket==A){
           byte gatesValsAbin = ReadGates(_socket);
    if(_invert){ // INVERTING MODE
        for(int i=0;i<8;i++){
            gateValuesA[i] = gatesValsAbin & (1<<i);
            gateValuesA[i]=gateValuesA[i]>>i;
            gateValuesA[i]=!gateValuesA[i];
        }
    }else{ // NON-INVERTING MODE 
        for(int i=0;i<8;i++){
            gateValuesA[i] = gatesValsAbin & (1<<i);
            gateValuesA[i]=gateValuesA[i]>>i;
        }
    }
      }
    else if(_socket==B){
         byte gatesValsBbin = ReadGates(_socket);
        if(_invert){ // INVERTING MODE
            for(int i=0;i<8;i++){
                gateValuesB[i] = gatesValsBbin & (1<<i);
                gateValuesB[i]=gateValuesB[i]>>i;
                gateValuesB[i]=!gateValuesB[i];
            }
        }else{ // NON-INVERTING MODE 
            for(int i=0;i<8;i++){
                gateValuesB[i] = gatesValsBbin & (1<<i);
                gateValuesB[i]=gateValuesB[i]>>i;
            }
        }

    
    }
    
    else if(_socket==C){
         byte gatesValsCbin = ReadGates(_socket);
        if(_invert){ // INVERTING MODE
            for(int i=0;i<8;i++){
                gateValuesC[i] = gatesValsCbin & (1<<i);
                gateValuesC[i]=gateValuesC[i]>>i;
                gateValuesC[i]=!gateValuesC[i];
            }
        }else{ // NON-INVERTING MODE 
            for(int i=0;i<8;i++){
                gateValuesC[i] = gatesValsCbin & (1<<i);
                gateValuesC[i]=gateValuesC[i]>>i;
            }
        }
 
    }
}

/*! \brief Read and return selected Gate input from ADDAC004 expansion
 \param _socket  connected socket - A or B
 \param _invert  inverted read - true or false
 \param _channel input to read : 0 - 7
 */

boolean ADDAC::ReadGate(int _socket, bool _invert, int _channel){ // READS GATES AND UPDATES ARRAY
    
   
    
    if(_socket==A){
        byte gatesValsAbin = ReadGates(_socket);
        if(_invert){ // INVERTING MODE
        
                gateValuesA[_channel] = gatesValsAbin & (1<<_channel);
                gateValuesA[_channel]=gateValuesA[_channel]>>_channel;
                gateValuesA[_channel]=!gateValuesA[_channel];
            
        }else{ // NON-INVERTING MODE 
          
                gateValuesA[_channel] = gatesValsAbin & (1<<_channel);
                gateValuesA[_channel]=gateValuesA[_channel]>>_channel;
         
        }
        return gateValuesA[_channel];
    }
    else if(_socket==B){
        byte gatesValsBbin = ReadGates(_socket);
        if(_invert){ // INVERTING MODE
            
                gateValuesB[_channel] = gatesValsBbin & (1<<_channel);
                gateValuesB[_channel]=gateValuesB[_channel]>>_channel;
                gateValuesB[_channel]=!gateValuesB[_channel];
           
        }else{ // NON-INVERTING MODE 
            
                gateValuesB[_channel] = gatesValsBbin & (1<<_channel);
                gateValuesB[_channel]=gateValuesB[_channel]>>_channel;
            
        }
        return gateValuesB[_channel];
        
    }
    
    else if(_socket==C){
        byte gatesValsCbin = ReadGates(_socket);
        if(_invert){ // INVERTING MODE
            
                gateValuesC[_channel] = gatesValsCbin & (1<<_channel);
                gateValuesC[_channel]=gateValuesC[_channel]>>_channel;
                gateValuesC[_channel]=!gateValuesC[_channel];
           
        }else{ // NON-INVERTING MODE 
           
                gateValuesC[_channel] = gatesValsCbin & (1<<_channel);
                gateValuesC[_channel]=gateValuesC[_channel]>>_channel;
            
        }
        return gateValuesC[_channel];
    }
}



/*! \Internal usage for Gates Reading
 */

byte ADDAC::ReadGates(int _socket){ // GATES A READING
    if(_socket==A){
	byte tempA = 0;
	//Pulse the latch pin:
	//set it to 1 to collect parallel data
	digitalWriteFast(gateInAlatch,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWriteFast(gateInAlatch,0);
	
	//while the shift register is in serial mode
	//collect each shift register into a byte
	tempA=shiftIn(gateInAdata, gateInAclock);
	return tempA;
    }
    
    else if(_socket==B){
        byte tempB = 0;
        digitalWriteFast(gateInBlatch,1);
        delayMicroseconds(20);
        digitalWriteFast(gateInBlatch,0);
        tempB=shiftIn(gateInBdata, gateInBclock);
        return tempB;
    }
    
    else if(_socket==C){
       
            byte tempC = 0;
            digitalWriteFast(gateInClatch,1);
            delayMicroseconds(20);
            digitalWriteFast(gateInClatch,0);
            tempC=shiftIn(gateInCdata, gateInCclock);
            return tempC;
        }
}


/*! \brief Sends values to MAX-MSP when the communication is enabled
 \param _socket  connected socket - A or B
 */


void ADDAC::MAXsendGates(int _socket){
     if(_socket==A){
    Serial.print("GateA0 ");
    Serial.println(gateValuesA[0],BIN);
    Serial.print("GateA1 ");
    Serial.println(gateValuesA[1],BIN);
    Serial.print("GateA2");
    Serial.println(gateValuesA[2],BIN);
    Serial.print("GateA3 ");
    Serial.println(gateValuesA[3],BIN);
    Serial.print("GateA4 ");
    Serial.println(gateValuesA[4],BIN);
    Serial.print("GateA5 ");
    Serial.println(gateValuesA[5],BIN);
    Serial.print("GateA6 ");
    Serial.println(gateValuesA[6],BIN);
    Serial.print("GateA7 ");
    Serial.println(gateValuesA[7],BIN);
     }
    
     else if(_socket==B){
         Serial.print("GateB0 ");
         Serial.println(gateValuesB[0],BIN);
         Serial.print("GateB1 ");
         Serial.println(gateValuesB[1],BIN);
         Serial.print("GateB2 ");
         Serial.println(gateValuesB[2],BIN);
         Serial.print("GateB3 ");
         Serial.println(gateValuesB[3],BIN);
         Serial.print("GateB4 ");
         Serial.println(gateValuesB[4],BIN);
         Serial.print("GateB5 ");
         Serial.println(gateValuesB[5],BIN);
         Serial.print("GateB6 ");
         Serial.println(gateValuesB[6],BIN);
         Serial.print("GateB7 ");
         Serial.println(gateValuesB[7],BIN);
     
     }
     else if(_socket==C){
         Serial.print("GateC0 ");
         Serial.println(gateValuesC[0],BIN);
         Serial.print("GateC1 ");
         Serial.println(gateValuesC[1],BIN);
         Serial.print("GateC2 ");
         Serial.println(gateValuesC[2],BIN);
         Serial.print("GateC3 ");
         Serial.println(gateValuesC[3],BIN);
         Serial.print("GateC4 ");
         Serial.println(gateValuesC[4],BIN);
         Serial.print("GateC5 ");
         Serial.println(gateValuesC[5],BIN);
         Serial.print("GateC6 ");
         Serial.println(gateValuesC[6],BIN);
         Serial.print("GateC7 ");
         Serial.println(gateValuesC[7],BIN);
     }
}


/*! \brief print all Gate inputs from ADDAC004 expansion
 \param _socket  connected socket - A or B
 */

void ADDAC::PrintGates(int _socket){
    if(_socket==A){
        Serial.print(" | GATE0:");
        Serial.print(gateValuesA[0],BIN);
        Serial.print(" | GATE1:");
        Serial.print(gateValuesA[1],BIN);
        Serial.print(" | GATE2:");
        Serial.print(gateValuesA[2],BIN);
        Serial.print(" | GATE3:");
        Serial.print(gateValuesA[3],BIN);
        Serial.print(" | GATE4:");
        Serial.print(gateValuesA[4],BIN);
        Serial.print(" | GATE5:");
        Serial.print(gateValuesA[5],BIN);
        Serial.print(" | GATE6:");
        Serial.print(gateValuesA[6],BIN);
        Serial.print(" | GATE7:");
        Serial.print(gateValuesA[7],BIN);
        
    }
    else if(_socket==B){
        Serial.print(" | GATE0:");
        Serial.print(gateValuesB[0],BIN);
        Serial.print(" | GATE1:");
        Serial.print(gateValuesB[1],BIN);
        Serial.print(" | GATE2:");
        Serial.print(gateValuesB[2],BIN);
        Serial.print(" | GATE3:");
        Serial.print(gateValuesB[3],BIN);
        Serial.print(" | GATE4:");
        Serial.print(gateValuesB[4],BIN);
        Serial.print(" | GATE5:");
        Serial.print(gateValuesB[5],BIN);
        Serial.print(" | GATE6:");
        Serial.print(gateValuesB[6],BIN);
        Serial.print(" | GATE7:");
        Serial.print(gateValuesB[7],BIN);

        
    }
    else if(_socket==C){
        Serial.print(" | GATE0:");
        Serial.print(gateValuesC[0],BIN);
        Serial.print(" | GATE1:");
        Serial.print(gateValuesC[1],BIN);
        Serial.print(" | GATE2:");
        Serial.print(gateValuesC[2],BIN);
        Serial.print(" | GATE3:");
        Serial.print(gateValuesC[3],BIN);
        Serial.print(" | GATE4:");
        Serial.print(gateValuesC[4],BIN);
        Serial.print(" | GATE5:");
        Serial.print(gateValuesC[5],BIN);
        Serial.print(" | GATE6:");
        Serial.print(gateValuesC[6],BIN);
        Serial.print(" | GATE7:");
        Serial.print(gateValuesC[7],BIN);

        
    }
}


/*! \brief print selected Gate input from ADDAC004 expansion in Monitor Log - usefull for DEBUG
 \param _socket  connected socket - A or B
  \param _channel  selected input : 0 - 7
 */
void ADDAC::PrintGate(int _socket, int _channel ){
    if(_socket==A){
        Serial.print(" | GATE" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(gateValuesA[_channel]);
    }
    else if(_socket==B){
        Serial.print(" | GATE" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(gateValuesB[_channel]);
    }
    else if(_socket==C){
        Serial.print(" | MANUAL" );
        Serial.print(_channel );
        Serial.print(": " );
        Serial.print(gateValuesC[_channel]);
    }
}





// --------------------------------------------------------------------------- WRITE GATES OUT - ADDAC005 -----------
//
int ADDAC::WriteGates(int _socket, byte _data, int bpm){ // WRITE 74HC595
	int waitTime=1000*(60.0f/bpm);//bpm to millis
    
    if(_socket==A){
	gatesOutMillisA=millis();
	if(gatesOutMillisA>oldGatesOutMillisA+waitTime){
		oldGatesOutMillisA=gatesOutMillisA;
		digitalWriteFast(gateOutAlatch, 0);
		shiftOutGates(gateOutAdata, gateOutAclock, _data);
		digitalWriteFast(gateOutAlatch, 1);
		return 1;
	}else{
		return 0;
	}
    }
    else if(_socket==B){
        gatesOutMillisB=millis();
        if(gatesOutMillisB>oldGatesOutMillisB+waitTime){
            oldGatesOutMillisB=gatesOutMillisB;
            digitalWriteFast(gateOutBlatch, 0);
            shiftOutGates(gateOutBdata, gateOutBclock, _data);
            digitalWriteFast(gateOutBlatch, 1);
            return 1;
        }else{
            return 0;
        }
    }
    else if(_socket==C){
        gatesOutMillisC=millis();
        if(gatesOutMillisC>oldGatesOutMillisC+waitTime){
            oldGatesOutMillisC=gatesOutMillisC;
            digitalWriteFast(gateOutClatch, 0);
            shiftOutGates(gateOutCdata, gateOutCclock, _data);
            digitalWriteFast(gateOutClatch, 1);
            return 1;
        }else{
            return 0;
        }
    }
}


/*! \brief Write selected Gate  from ADDAC005 expansion
 \param _socket  connected socket - A or B
 \param _pos  selected input : 0 - 7
 \param _data  gate value : true or false */

void ADDAC::WriteGatesStraight(int _socket, int _pos, int _data){ // WRITE 74HC595
     if(_socket==A){
		digitalWriteFast(gateOutAlatch, 0);
		shiftOutGates(gateOutAdata, gateOutAclock, _pos, _data);
		digitalWriteFast(gateOutAlatch, 1);
     }
     else if(_socket==B){
         digitalWriteFast(gateOutBlatch, 0);
         shiftOutGates(gateOutBdata, gateOutBclock, _pos, _data);
         digitalWriteFast(gateOutBlatch, 1);
     }
         else if(_socket==C){
             digitalWriteFast(gateOutClatch, 0);
             shiftOutGates(gateOutCdata, gateOutCclock, _pos, _data);
             digitalWriteFast(gateOutClatch, 1);
         }
}

//



// --------------------------------------------------------------------------- GATE DELAY -----------
//
/*
 
 TENHO DE CRIAR .H PARALELO PARA INICIAR QD ME APETECER E MANTER O TIMER...
 
void ADDAC::gateDelayFunctionInit(int _gateInput, int _channelIn, int _channelOut, int _delayTime){ // INIT FUNCTION
 
 int gateID =  _gateInput*100 + _channelIn;
 
	int DelayFunctionTimeOld
	byte gatesValsAbin=ADDAC.ReadGatesA(8);
	for(int i=0;i<8;i++){
		gatesValsA[i] = gatesValsAbin & (1<<i);
		gatesValsA[i]=gatesValsA[i]>>i;
  }
}

byte ADDAC::ReadGatesA(int _channel){ // EXTERNAL READING
	byte tempA = 119;
	//Pulse the latch pin:
	//set it to 1 to collect parallel data
	digitalWriteFast(gateInAlatch,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWriteFast(gateInAlatch,0);
	
	//while the shift register is in serial mode
	//collect each shift register into a byte
	tempA=shiftIn(gateInAdata, gateInAclock);
	return tempA;
}
*/




// --------------------------------------------------------------------------- MIXER MODE -------------------------


/*! \brief Mix and calculates the average of the first 7 channels and updates channel 7 with the result.*/

void ADDAC::mixerMode(){ // MIX ALL 7 FIRST
	unsigned long avg=0;
	for(int i=0; i<7; i++){
		avg+=DACvolts[i];
	}
	DACvolts[8]=avg/7;
	// UPDATE CHANNEL
	writeChannel(7,DACvolts[8]);
}

/*! \brief Mix and calculates the average of the channels up to the selected channel, and updates channel 7 with the result.
 \param _upToX  mix up to this channel : 0 - 7
 */

void ADDAC::mixerMode(int _upToX){ // MIX ALL FIRSTS up to X
	unsigned long avg=0;
	for(int i=0; i<_upToX; i++){ 
		avg+=DACvolts[i];
	}
	DACvolts[8]=avg/_upToX;
	// UPDATE CHANNEL
	writeChannel(7,DACvolts[8]);
}


/*! \brief Mix and calculates the average of channel A and B, and updates selected channel with the result.
 \param _channel  output channel with the result
 \param _A  first channel to Mix
 \param _B  second channel to Mix
 */
void ADDAC::mixerMode(int _channel, int _A, int _B){ // MIX 2
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	DACvolts[_channel]=avg/2;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}


/*! \brief Mix and calculates the average of channel A, B and C, and updates selected channel with the result.
 \param _channel  output channel with the result
 \param _A  first channel to Mix
 \param _B  second channel to Mix
 \param _C  third channel to Mix
 */
void ADDAC::mixerMode(int _channel, int _A, int _B, int _C){ // MIX 3
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	avg+=DACvolts[_C];
	DACvolts[_channel]=avg/3;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}

/*! \brief Mix and calculates the average of channel A, B, C and D, and updates selected channel with the result.
 \param _channel  output channel with the result
 \param _A  first channel to Mix
 \param _B  second channel to Mix
 \param _C  third channel to Mix
 \param _D  fourth channel to Mix
 */
void ADDAC::mixerMode(int _channel, int _A, int _B, int _C, int _D){ // MIX 4
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	avg+=DACvolts[_C];
	avg+=DACvolts[_D];
	DACvolts[_channel]=avg/4;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}

/*! \brief Mix and calculates the average of channel A, B, C, D and E, and updates selected channel with the result.
 \param _channel  output channel with the result
 \param _A  first channel to Mix
 \param _B  second channel to Mix
 \param _C  third channel to Mix
 \param _D  fourth channel to Mix
 \param _E  fifth channel to Mix
 */
void ADDAC::mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E){ // MIX 5
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	avg+=DACvolts[_C];
	avg+=DACvolts[_D];
	avg+=DACvolts[_E];
	DACvolts[_channel]=avg/5;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}

/*! \brief Mix and calculates the average of channel A, B, C, D, E and F, and updates selected channel with the result.
 \param _channel  output channel with the result
 \param _A  first channel to Mix
 \param _B  second channel to Mix
 \param _C  third channel to Mix
 \param _D  fourth channel to Mix
 \param _E  fifth channel to Mix
 \param _F  sixth channel to Mix
 */
void ADDAC::mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E, int _F){ // MIX 6
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	avg+=DACvolts[_C];
	avg+=DACvolts[_D];
	avg+=DACvolts[_E];
	avg+=DACvolts[_F];
	DACvolts[_channel]=avg/6;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}

/*! \brief Mix and calculates the average of channel A, B, C, D, E, F an G, and updates selected channel with the result.
 \param _channel  output channel with the result
 \param _A  first channel to Mix
 \param _B  second channel to Mix
 \param _C  third channel to Mix
 \param _D  fourth channel to Mix
 \param _E  fifth channel to Mix
 \param _F  sixth channel to Mix
 \param _G  seventh channel to Mix
 */
void ADDAC::mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E, int _F, int _G){ // MIX 7
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	avg+=DACvolts[_C];
	avg+=DACvolts[_D];
	avg+=DACvolts[_E];
	avg+=DACvolts[_F];
	avg+=DACvolts[_G];
	DACvolts[_channel]=avg/7;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}


/*! \brief Mix and calculates the average of channel A, B, C, D, E, F, G and H, and updates selected channel with the result.
 \param _channel  output channel with the result
 \param _A  first channel to Mix
 \param _B  second channel to Mix
 \param _C  third channel to Mix
 \param _D  fourth channel to Mix
 \param _E  fifth channel to Mix
 \param _F  sixth channel to Mix
 \param _G  seventh channel to Mix
 \param _H  eigthth channel to Mix
 */
void ADDAC::mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E, int _F, int _G, int _H){ // MIX 8
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	avg+=DACvolts[_C];
	avg+=DACvolts[_D];
	avg+=DACvolts[_E];
	avg+=DACvolts[_F];
	avg+=DACvolts[_G];
	avg+=DACvolts[_H];
	DACvolts[_channel]=avg/8;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}


// --------------------------------------------------------------------------- AD5668 RELATED -----------------------
//
/*! \writeChannel - internal Reading (don't use).
 */
void ADDAC::writeChannel(int _channel, float _voltage){ // INTERNAL
    unsigned int _realVoltage= _voltage*addacMaxResolution;
	byte b1 = B11110000|WRITE_UPDATE_N; //padding at beginning of byte
	byte b2 = _channel << 4 | _realVoltage >> 12; //4 address bits and 4 MSBs of data
	byte b3 = (_realVoltage << 4) >> 8; // middle 8 bits of data
	byte b4 = (_realVoltage << 12) >> 8 | B00001111;
	#ifdef DEBUG
		Serial.print("b1 ");
		Serial.println(b1, BIN);
		Serial.print("b2 ");
		Serial.println(b2, BIN);
		Serial.print("b3 ");
		Serial.println(b3, BIN);
		Serial.print("b4 ");
		Serial.println(b4, BIN);
		Serial.println();
	#endif
	digitalWriteFast(SLAVESELECT, LOW);
	delayMicroseconds(1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
	delayMicroseconds(1);
	delayMicroseconds(1);
	delayMicroseconds(1);
	digitalWriteFast(SLAVESELECT, HIGH);
    
    
    
}

/*! \brief  Sends Voltage to a VCC Output channel
 \param _channel  VCC Output Channel : 0 - 7
 \param _voltage  Voltage to send
 */
void ADDAC::WriteChannel(int _channel, float _voltage){ // EXTERNAL - WRITING FROM ARDUINO ENVIRONMENT
    unsigned int _realVoltage= _voltage*addacMaxResolution;
	byte b1 = B11110000|WRITE_UPDATE_N; //padding at beginning of byte
	byte b2 = _channel << 4 | _realVoltage >> 12; //4 address bits and 4 MSBs of data
	byte b3 = (_realVoltage << 4) >> 8; // middle 8 bits of data
	byte b4 = (_realVoltage << 12) >> 8 | B00001111;
#ifdef DEBUG
	Serial.print("b1 ");
	Serial.println(b1, BIN);
	Serial.print("b2 ");
	Serial.println(b2, BIN);
	Serial.print("b3 ");
	Serial.println(b3, BIN);
	Serial.print("b4 ");
	Serial.println(b4, BIN);
	Serial.println();
#endif
	digitalWriteFast(SLAVESELECT, LOW);
	delayMicroseconds(1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
	delayMicroseconds(1);
	delayMicroseconds(1);
	delayMicroseconds(1);
	digitalWriteFast(SLAVESELECT, HIGH);
    
    //update array to mixerMode and others...
    DACvolts[_channel]=_realVoltage;
}

/*! \write - internal Reading (don't use).
 */

void ADDAC::write(int command, int address, unsigned int data){
		switch (command) {
			case WRITE_UPDATE_N:{
				byte b1 = B11110000|command; //padding at beginning of byte
				#ifdef DEBUG
				Serial.print("b1 ");
				Serial.println(b1, BIN);
				#endif
				byte b2 = address << 4 | data >> 12; //4 address bits and 4 MSBs of data
				#ifdef DEBUG
				Serial.print("b2 ");
				Serial.println(b2, BIN);
				#endif
				byte b3 = (data << 4) >> 8; // middle 8 bits of data
				#ifdef DEBUG
				Serial.print("b3 ");
				Serial.println(b3, BIN);
				#endif
				byte b4 = (data << 12) >> 8 | B00001111;
				#ifdef DEBUG
				Serial.print("b4 ");
				Serial.println(b4, BIN);
				Serial.println();
				#endif
				digitalWriteFast(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				delayMicroseconds(1);
				delayMicroseconds(1);
				digitalWriteFast(SLAVESELECT, HIGH);
				break;
			}case SETUP_INTERNAL_REGISTER:{
				byte b1 = B11111000; //padding at beginning of byte
				//Serial.print("b1 ");
				//Serial.println(b1, BIN);
				byte b2 = B00000000;
				//Serial.print("b2 ");
				//Serial.println(b2, BIN);
				byte b3 = B00000000;
				//Serial.print("b2 ");
				//Serial.println(b3, BIN);
				byte b4 = B00000000|data;
				//Serial.print("b4 ");
				//Serial.println(b4, BIN);
				//Serial.println();
				digitalWriteFast(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				digitalWriteFast(SLAVESELECT, HIGH);
				break;
			}case RESET:{
				byte b1 = B11110111; //padding at beginning of byte
				//Serial.print("b1 ");
				//Serial.println(b1, BIN);
				byte b2 = B00000000;
				//Serial.print("b2 ");
				//Serial.println(b2, BIN);
				byte b3 = B00000000;
				//Serial.print("b2 ");
				//Serial.println(b3, BIN);
				byte b4 = B00000000|data;
				//Serial.print("b4 ");
				//Serial.println(b4, BIN);
				//Serial.println();
				digitalWriteFast(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				digitalWriteFast(SLAVESELECT, HIGH);
				break;
			}case POWER:{
				byte b1 = B11110100; //padding at beginning of byte
				//Serial.print("b1 ");
				//Serial.println(b1, BIN);
				byte b2 = B00000000;
				//Serial.print("b2 ");
				//Serial.println(b2, BIN);
				byte b3 = B00000000;
				//Serial.print("b2 ");
				//Serial.println(b3, BIN);
				byte b4 = B11111111;
				//Serial.print("b4 ");
				//Serial.println(b4, BIN);
				//Serial.println();
				digitalWriteFast(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				digitalWriteFast(SLAVESELECT, HIGH);
				break;
			}
		}
}

// --------------------------------------------------------------------------- MODES SWITCH -------------------------
//
/*! \Updates MODE & SUBMODE Variables (Presets).
 */

void ADDAC::readMODEswitch(){
#if defined VS3
	byte switchVar1 = 0;
	byte modeByte = 0;
	byte submodeByte = 0;
	//Pulse the latch pin:
	//set it to 1 to collect parallel data
	digitalWriteFast(latchPin,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWriteFast(latchPin,0);
	
	//while the shift register is in serial mode
	//collect each shift register into a byte
	//the register attached to the chip comes in first 
	switchVar1 = shiftIn(dataPin, clockPin);
	modeByte = switchVar1 <<4;
	modeByte = modeByte >>4;
	submodeByte = switchVar1 >>4;
	SUBMODE=(int)modeByte;
	MODE=(int)submodeByte;
#elif defined VS2
	byte switchVar1 = 0;
	byte modeByte = 0;
	byte submodeByte = 0;
	//Pulse the latch pin:
	//set it to 1 to collect parallel data
	digitalWriteFast(latchPin,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWriteFast(latchPin,0);
	
	//while the shift register is in serial mode
	//collect each shift register into a byte
	//the register attached to the chip comes in first 
	switchVar1 = shiftIn(dataPin, clockPin);
	modeByte = switchVar1 <<4;
	modeByte = modeByte >>4;
	submodeByte = switchVar1 >>4;
	MODE=(int)modeByte;
	SUBMODE=(int)submodeByte;
#else
	byte switchVar1 = 72;  //01001000
	byte switchVar2 = 159; //10011111
	byte switchVar3 = 119; 
	byte switchA = 0; 
	byte switchB = 0; 
	//Pulse the latch pin:
	//set it to 1 to collect parallel data
	digitalWriteFast(latchPin,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWriteFast(latchPin,0);
	
	//while the shift register is in serial mode
	//collect each shift register into a byte
	//the register attached to the chip comes in first 
	switchVar1 = shiftIn(dataPin, clockPin);
	switchVar2 = shiftIn(dataPin, clockPin);
	switchVar3 = shiftIn(dataPin, clockPin);
	// Divide bits in 2nd 4021
	switchA = switchVar2 <<4;
	switchA = switchA >>4;
	switchB = switchVar2 >>4;
	
	if(switchVar1==1)MODE=1;
	else if(switchVar1==2)MODE=2;
	else if(switchVar1==4)MODE=3;
	else if(switchVar1==8)MODE=4;
	else if(switchVar1==16)MODE=5;
	else if(switchVar1==32)MODE=6;
	else if(switchVar1==64)MODE=7;
	else if(switchVar1==128)MODE=8;
	else if(switchA==1)MODE=9;
	else if(switchA==2)MODE=10;
	else if(switchA==4)MODE=11;
	
	if(switchVar3==1)SUBMODE=1;
	else if(switchVar3==2)SUBMODE=2;
	else if(switchVar3==4)SUBMODE=3;
	else if(switchVar3==8)SUBMODE=4;
	else if(switchVar3==16)SUBMODE=5;
	else if(switchVar3==32)SUBMODE=6;
	else if(switchVar3==64)SUBMODE=7;
	else if(switchVar3==128)SUBMODE=8;
	else if(switchB==1)SUBMODE=9;
	else if(switchB==2)SUBMODE=10;
	else if(switchB==4)SUBMODE=11;
#endif
}

/*! \Brief Reads & returns the MODE button position:
 */
int ADDAC::readMODE(){
	return MODE;
}

/*! \Brief Reads & returns the SUBMODE button position:
 */
int ADDAC::readSUBMODE(){
	return SUBMODE;
}
////// ----------------------------------------shiftIn function
///// just needs the location of the data pin and the clock pin
///// it returns a byte with each bit in the byte corresponding
///// to a pin on the shift register. leftBit 7 = Pin 7 / Bit 0= Pin 0

byte ADDAC::shiftIn(int myDataPin, int myClockPin) { 
	int temp = 0;
	byte myDataIn = 0;

	//at the begining of each loop when we set the clock low, it will
	//be doing the necessary low to high drop to cause the shift
	//register's DataPin to change state based on the value
	//of the next bit in its serial information flow.
	//The register transmits the information about the pins from pin 7 to pin 0
	//so that is why our function counts down
	for (int i=7; i>=0; i--){
		digitalWriteFast(myClockPin, 0);
		delayMicroseconds(2);
		temp = digitalRead(myDataPin);
		if (temp) {
			myDataIn = myDataIn | (1 << i);
		}
		digitalWriteFast(myClockPin, 1);
	}
	return myDataIn;
}

// the GATES OUT shift out
void ADDAC::shiftOutGates(int myDataPin, int myClockPin, byte myDataOut) {
	// This shifts 8 bits out MSB first, 
	//on the rising edge of the clock,
	//clock idles low
	
	//internal function setup
	int i=0;
	int pinState;
	//clear everything out just in case to
	//prepare shift register for bit shifting
	digitalWriteFast(myDataPin, 0);
	digitalWriteFast(myClockPin, 0);
	
	//for each bit in the byte myDataOut
	//NOTICE THAT WE ARE COUNTING DOWN in our for loop
	//This means that %00000001 or "1" will go through such
	//that it will be pin Q0 that lights. 
	for (i=7; i>=0; i--)  {
		digitalWriteFast(myClockPin, 0);
		
		//if the value passed to myDataOut and a bitmask result 
		// true then... so if we are at i=6 and our value is
		// %11010100 it would the code compares it to %01000000 
		// and proceeds to set pinState to 1.
		if ( myDataOut & (1<<i) ) {
			pinState= 1;
		}else {	
			pinState= 0;
		}
		
		//Sets the pin to HIGH or LOW depending on pinState
		digitalWriteFast(myDataPin, pinState);
		//register shifts bits on upstroke of clock pin  
		digitalWriteFast(myClockPin, 1);
		//zero the data pin after shift to prevent bleed through
		digitalWriteFast(myDataPin, 0);
	}
	
	//stop shifting
	digitalWriteFast(myClockPin, 0);
}
// the GATES OUT shift out
void ADDAC::shiftOutGates(int myDataPin, int myClockPin, int _pin, int _myDataOut) {
	// This shifts 8 bits out MSB first, 
	//on the rising edge of the clock,
	//clock idles low
	gateValuesOutA[_pin]=_myDataOut;
	//internal function setup
	int i=0;
	int pinState;
	//clear everything out just in case to
	//prepare shift register for bit shifting
	digitalWriteFast(myDataPin, 0);
	digitalWriteFast(myClockPin, 0);
	
	//for each bit in the byte myDataOut
	//NOTICE THAT WE ARE COUNTING DOWN in our for loop
	//This means that %00000001 or "1" will go through such
	//that it will be pin Q0 that lights. 
	for (i=7; i>=0; i--)  {
		digitalWriteFast(myClockPin, 0);
		
		//if the value passed to myDataOut and a bitmask result 
		// true then... so if we are at i=6 and our value is
		// %11010100 it would the code compares it to %01000000 
		// and proceeds to set pinState to 1.
		if ( gateValuesOutA[i]==1 ) {
			pinState= 1;
		}else {	
			pinState= 0;
		}
		
		//Sets the pin to HIGH or LOW depending on pinState
		digitalWriteFast(myDataPin, pinState);
		//register shifts bits on upstroke of clock pin  
		digitalWriteFast(myClockPin, 1);
		//zero the data pin after shift to prevent bleed through
		digitalWriteFast(myDataPin, 0);
	}
	
	//stop shifting
	digitalWriteFast(myClockPin, 0);
}

// --------------------------------------------------------------------------- END ----------------------------------
//

