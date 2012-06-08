 

#include "ADDAC.h"
//#include "ADDAchannels.h"
#include "ADDAgateSequencer.h"

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
	digitalWrite(DATAOUT,LOW);
	digitalWrite(SPICLK, LOW);
	digitalWrite(SLAVESELECT, LOW);
	digitalWrite(CLR, LOW);
	delay(50);
	digitalWrite(CLR, HIGH);
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
void ADDAC::update(){
	readMODEswitch();
#ifndef VS3
	onboardVal=analogRead(onboardPotPin);
	onboardValMapped=onboardVal/1023.0f*65535.0f;
#endif

}	

// --------------------------------------------------------------------------- ONBOARD POT -------------------------
//
int ADDAC::readOnboardPot(){
		return onboardVal;
}

// --------------------------------------------------------------------------- READ CVS IN - ADDAC002 -----------
//
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


float ADDAC::ReadCv(int _socket, int _channel){ // EXTERNAL READING

	if(_socket == A){
		digitalWrite(cvInAs0, truthTableA[_channel]); 
		digitalWrite(cvInAs1, truthTableB[_channel]); 
		digitalWrite(cvInAs2, truthTableC[_channel]); 
        cvValuesA[_channel]=analogRead(cvInApin)/1023.0f;
		return cvValuesA[_channel];
	}else if(_socket == B){
		digitalWrite(cvInBs0, truthTableA[_channel]); 
		digitalWrite(cvInBs1, truthTableB[_channel]); 
		digitalWrite(cvInBs2, truthTableC[_channel]); 
		cvValuesB[_channel]=analogRead(cvInBpin)/1023.0f;
		return cvValuesB[_channel];
	}else if(_socket == C){
		digitalWrite(cvInCs0, truthTableA[_channel]); 
		digitalWrite(cvInCs1, truthTableB[_channel]); 
		digitalWrite(cvInCs2, truthTableC[_channel]); 
		cvValuesC[_channel]=analogRead(cvInCpin)/1023.0f;
		return cvValuesC[_channel];
	}
}


void ADDAC::StoreCvs(int _socket, int _channel){ // Store for prints
   
	if(_socket == A){
		digitalWrite(cvInAs0, truthTableA[_channel]); 
		digitalWrite(cvInAs1, truthTableB[_channel]); 
		digitalWrite(cvInAs2, truthTableC[_channel]); 
        cvValuesA[_channel]=analogRead(cvInApin)/1023.0f;

	}else if(_socket == B){
		digitalWrite(cvInBs0, truthTableA[_channel]); 
		digitalWrite(cvInBs1, truthTableB[_channel]); 
		digitalWrite(cvInBs2, truthTableC[_channel]); 
		cvValuesB[_channel]=analogRead(cvInBpin)/1023.0f;
	}else if(_socket == C){
		digitalWrite(cvInCs0, truthTableA[_channel]); 
		digitalWrite(cvInCs1, truthTableB[_channel]); 
		digitalWrite(cvInCs2, truthTableC[_channel]); 
		cvValuesC[_channel]=analogRead(cvInCpin)/1023.0f;

	}
}




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


float ADDAC::ReadManual(int _socket,int _channel){ // EXTERNAL READING
     if(_socket == A){
	digitalWrite(manualInAs0, truthTableA[_channel]); 
	digitalWrite(manualInAs1, truthTableB[_channel]); 
	digitalWrite(manualInAs2, truthTableC[_channel]); 
    manualValuesA[_channel] = analogRead(manualInApin)/1023.0f;
    return manualValuesA[_channel];
     }
    
    else if(_socket == B){
        digitalWrite(manualInBs0, truthTableA[_channel]); 
        digitalWrite(manualInBs1, truthTableB[_channel]); 
        digitalWrite(manualInBs2, truthTableC[_channel]); 
        manualValuesB[_channel] = analogRead(manualInBpin)/1023.0f;
		return manualValuesB[_channel];
    }
    else if(_socket == C){
        digitalWrite(manualInCs0, truthTableA[_channel]); 
        digitalWrite(manualInCs1, truthTableB[_channel]); 
        digitalWrite(manualInCs2, truthTableC[_channel]); 
        manualValuesC[_channel] = analogRead(manualInCpin)/1023.0f;
		return manualValuesC[_channel];
    }
    

}



void ADDAC::StoreManuals(int _socket,int _channel){ // EXTERNAL READING
    if(_socket == A){
        digitalWrite(manualInAs0, truthTableA[_channel]); 
        digitalWrite(manualInAs1, truthTableB[_channel]); 
        digitalWrite(manualInAs2, truthTableC[_channel]);
        manualValuesA[_channel]=analogRead(manualInApin)/1023.0f;
       
         
    }
    
    else if(_socket == B){
        digitalWrite(manualInBs0, truthTableA[_channel]); 
        digitalWrite(manualInBs1, truthTableB[_channel]); 
        digitalWrite(manualInBs2, truthTableC[_channel]); 
        manualValuesB[_channel]=analogRead(manualInBpin)/1023.0f;
       
    }
    else if(_socket == C){
        digitalWrite(manualInCs0, truthTableA[_channel]); 
        digitalWrite(manualInCs1, truthTableB[_channel]); 
        digitalWrite(manualInCs2, truthTableC[_channel]); 
        manualValuesC[_channel]=analogRead(manualInCpin)/1023.0f;
     
    }
    
    
}



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
        Serial.print(" | MANUAL5:");
        Serial.print(manualValuesA[5]);
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
        Serial.print(" | MANUAL5:");
        Serial.print(manualValuesB[5]);
        
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
        Serial.print(" | MANUAL5:");
        Serial.print(manualValuesC[5]);
        
    }
}


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






byte ADDAC::ReadGates(int _socket){ // GATES A READING
    if(_socket==A){
	byte tempA = 0;
	//Pulse the latch pin:
	//set it to 1 to collect parallel data
	digitalWrite(gateInAlatch,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWrite(gateInAlatch,0);
	
	//while the shift register is in serial mode
	//collect each shift register into a byte
	tempA=shiftIn(gateInAdata, gateInAclock);
	return tempA;
    }
    
    else if(_socket==B){
        byte tempB = 0;
        digitalWrite(gateInBlatch,1);
        delayMicroseconds(20);
        digitalWrite(gateInBlatch,0);
        tempB=shiftIn(gateInBdata, gateInBclock);
        return tempB;
    }
    
    else if(_socket==C){
       
            byte tempC = 0;
            digitalWrite(gateInClatch,1);
            delayMicroseconds(20);
            digitalWrite(gateInClatch,0);
            tempC=shiftIn(gateInCdata, gateInCclock);
            return tempC;
        }
}

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
		digitalWrite(gateOutAlatch, 0);
		shiftOutGates(gateOutAdata, gateOutAclock, _data);
		digitalWrite(gateOutAlatch, 1);
		return 1;
	}else{
		return 0;
	}
    }
    else if(_socket==B){
        gatesOutMillisB=millis();
        if(gatesOutMillisB>oldGatesOutMillisB+waitTime){
            oldGatesOutMillisB=gatesOutMillisB;
            digitalWrite(gateOutBlatch, 0);
            shiftOutGates(gateOutBdata, gateOutBclock, _data);
            digitalWrite(gateOutBlatch, 1);
            return 1;
        }else{
            return 0;
        }
    }
    else if(_socket==C){
        gatesOutMillisC=millis();
        if(gatesOutMillisC>oldGatesOutMillisC+waitTime){
            oldGatesOutMillisC=gatesOutMillisC;
            digitalWrite(gateOutClatch, 0);
            shiftOutGates(gateOutCdata, gateOutCclock, _data);
            digitalWrite(gateOutClatch, 1);
            return 1;
        }else{
            return 0;
        }
    }
}


void ADDAC::WriteGatesStraight(int _socket, int _pos, int _data){ // WRITE 74HC595
     if(_socket==A){
		digitalWrite(gateOutAlatch, 0);
		shiftOutGates(gateOutAdata, gateOutAclock, _pos, _data);
		digitalWrite(gateOutAlatch, 1);
     }
     else if(_socket==B){
         digitalWrite(gateOutBlatch, 0);
         shiftOutGates(gateOutBdata, gateOutBclock, _pos, _data);
         digitalWrite(gateOutBlatch, 1);
     }
         else if(_socket==C){
             digitalWrite(gateOutClatch, 0);
             shiftOutGates(gateOutCdata, gateOutCclock, _pos, _data);
             digitalWrite(gateOutClatch, 1);
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
	digitalWrite(gateInAlatch,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWrite(gateInAlatch,0);
	
	//while the shift register is in serial mode
	//collect each shift register into a byte
	tempA=shiftIn(gateInAdata, gateInAclock);
	return tempA;
}
*/

// --------------------------------------------------------------------------- RANDOMS MODE -------------------------
//
void ADDAC::randomMode(int _MODE, int _channel){
	ReadManuals(A);
	if(_MODE==0){ // UPDATE ALL CHANNELS
		for(int i=0; i<8;i++){
			if(millis()>RNDdelays[i]+DACtimes[i]){
				DACtimes[i]=millis();
				RNDdelays[i]=random(50,1000);
				//randomSeed(random(analogRead(5)));//unusedPin, for now only!!!!!
				DACvolts[i]=random(0,addacMaxResolution);
				writeChannel(i,DACvolts[i]);
			}
		}
	}else if(_MODE==1){ // UPDATE INDIVIDUAL CHANNELS
		if(millis()>RNDdelays[_channel]+DACtimes[_channel]){
			DACtimes[_channel]=millis();
			RNDdelays[_channel]=random(50,1000);
			//randomSeed(random(analogRead(5)));
			DACvolts[_channel]=random(0,addacMaxResolution);
			writeChannel(_channel,DACvolts[_channel]);
		}
	}
}
void ADDAC::randomMode(int _channel, bool _inverted, float _randomMin, float _randomMax, float _randomFreqMin, float _randomFreqMax){
	if(millis()>RNDdelays[_channel]+DACtimes[_channel]){
		DACtimes[_channel]=millis();
		RNDdelays[_channel]=random(_randomFreqMin,_randomFreqMax);
		//randomSeed(random(analogRead(5)));
		if(!_inverted){	
			DACvolts[_channel]=random(_randomMin,_randomMax)*addacMaxResolution;
		}else{
			DACvolts[_channel]=(1-random(_randomMin,_randomMax))*addacMaxResolution;
		}
		writeChannel(_channel,DACvolts[_channel]);
	}
}
// RANDOM WITH SMOOTH
void ADDAC::randomModeSmoothed(int _channel, float _randomMin, float _randomMax, float _randomFreqMin, float _randomFreqMax, float _smooth){
	if(millis()>RNDdelays[_channel]+DACtimes[_channel]){
		DACtimes[_channel]=millis();
		if (_randomFreqMax > _randomFreqMin) {
			RNDdelays[_channel]=random(_randomFreqMin,_randomFreqMax);
		}else {
			//RNDdelays[_channel]=random(_randomFreqMax,_randomFreqMin);
			RNDdelays[_channel]=_randomFreqMin;
		}
		threshold=(_randomMax+_randomMin)/2;
		if(_randomMax > _randomMin){	
			float an2=(_smooth-1)*-1.0f;
			DACvolts[_channel]=DACvolts[_channel]*_smooth+(random(_randomMin,_randomMax)+random(1023))*an2;//*addacMaxResolution;
			//DACvolts[_channel]=random(_randomMin,_randomMax)+random(1023);//*addacMaxResolution;

			//if(DACvolts[_channel]>threshold){
			//	digitalWrite(_channel+2,HIGH);
			//}else{
			//	digitalWrite(_channel+2,LOW);
			//}
		}else{
			float an2=(_smooth-1)*-1.0f;
			//DACvolts[_channel]=DACvolts[_channel]*_smooth+(random(_randomMax,_randomMin)+random(1023))*an2;//*addacMaxResolution;
			DACvolts[_channel]=_randomMin;//*addacMaxResolution;
			//DACvolts[_channel]=random(_randomMax,_randomMin)+random(1023);//*addacMaxResolution;

			//if(DACvolts[_channel]>threshold){
			//	digitalWrite(_channel+2,HIGH);
			//}else{
			//	digitalWrite(_channel+2,LOW);
			//}
		}
		writeChannel(_channel,DACvolts[_channel]);
		
		if(_channel==0){
			Serial.print(" DAC:");
			Serial.print(DACvolts[_channel]);
			Serial.print(" DAC:");
			Serial.print(_randomMin);
			Serial.print(" DAC:");
			Serial.print(_randomMax);
			Serial.print(" DAC:");
			float an2=(_smooth-1)*-1.0f;
			Serial.print((random(_randomMin,_randomMax)+random(1023))*an2);
			Serial.println();
		}
	}
}




// --------------------------------------------------------------------------- SIN MODE -------------------------
//
//int _channel (1-8), bool _inverted (0=no - 1=yes) 
//float _freq (hertz (0.0-20000.0), float _bottom (percentage 0-1), float _top (percentage 0-1)

void ADDAC::sinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top){
	// EQUATION
	//y=(s*cos(freq*x+offset)+a)*addacMax; freq=100; T=0.8; B=0.2; S=T-B; I=1; Offset=0.5, invert=0; offset=Offset+invert/2*2¹; s=S/2, a=s+B
	/*float S=_top-_bottom;
	_offset=(_offset+_inverted/2)*TWO_PI;
	float s=S/2;
	float a=s+_bottom;
	DACvolts[_channel-1]=(s*cos(_freq*(millis()*_mult)+_offset)+a)*addacMaxResolution;*/
	_freq+=10;
	_mult+=1;
	float _dif = (_top - _bottom);
	_bottom = addacMaxResolution *_bottom;
	if(!_inverted){ // normal
		DACvolts[_channel]= _bottom+(sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) *_dif + _offset;
	}else{ // inverted
		DACvolts[_channel]= _bottom+(sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f)*_dif + _offset;
	}
	//old: sin(millis()/_freq)
	
	// UPDATE CHANNEL
	/*Serial.print(" | DACvolts_");
	Serial.print(_channel);
	Serial.print(":");
	Serial.print(DACvolts[_channel]);*/
	writeChannel(_channel,DACvolts[_channel]);
}

void ADDAC::sinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset){
	_freq+=10;
	_mult+=1;
	if(!_inverted){ // normal
		DACvolts[_channel]= (sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) + _offset;
	}else{ // inverted
		DACvolts[_channel]= (sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f) + _offset;
	}
	
	// UPDATE CHANNEL
	/*Serial.print(" | DACvolts_");
	Serial.print(_channel);
	Serial.print(":");
	Serial.print(DACvolts[_channel-1]);*/
	writeChannel(_channel,DACvolts[_channel]);
}
// --------------------------------------------------------------------------- COSIN MODE -------------------------
//
//int _channel (1-8), bool _inverted (0=no - 1=yes) 
//float _freq (hertz (0.0-20000.0), int _bottom (percentage 0-100%), int _top (percentage 0-100%)

void ADDAC::cosinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top){
	_freq+=10;
	_mult+=1;
	float _dif = _top - _bottom;
	_bottom = addacMaxResolution *_bottom;
	if(!_inverted){ // normal
		DACvolts[_channel]= _bottom + (cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) * _dif + _offset;
	}else{ // inverted
		DACvolts[_channel]= _bottom + (cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f) * _dif + _offset;
	}
	
	// UPDATE CHANNEL
	/*Serial.print(" | DACvolts_");
	Serial.print(_channel);
	Serial.print(":");
	Serial.print(DACvolts[_channel-1]);*/
	writeChannel(_channel,DACvolts[_channel]);
}
void ADDAC::cosinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset){
	_freq+=10;
	_mult+=1;
	if(!_inverted){ // normal
		DACvolts[_channel]= (cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) + _offset;
	}else{ // inverted
		DACvolts[_channel]= (cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f) + _offset;
	}
	
	// UPDATE CHANNEL
	/*Serial.print(" | DACvolts_");
	 Serial.print(_channel);
	 Serial.print(":");
	 Serial.print(DACvolts[_channel-1]);*/
	writeChannel(_channel,DACvolts[_channel]);
}

// --------------------------------------------------------------------------- TAN MODE  buggy!!! EXCLUDE !!! -------------------------
//
//int _channel (1-8), bool _inverted (0=no - 1=yes) 
//float _freq (hertz (0.0-20000.0), int _bottom (percentage 0-100%), int _top (percentage 0-100%)

// ADD top and bottom offset??
void ADDAC::tanMode(int _channel, bool _inverted, float _freq, int _bottom, int _top){
	//SINoldTimes[_channel-1];
	Serial.print(" | freq:");
	Serial.print(_freq);
	if(!_inverted){ // normal
		DACvolts[_channel-1]= tan(millis()/_freq)*addacMaxResolution;
		Serial.print(" | tan:");
		Serial.print(tan(millis()/_freq)+1.0f);
	}else{ // inverted
		DACvolts[_channel-1]= tan(millis()/_freq)*-1.0f*addacMaxResolution;
		Serial.print(" | InvTan:");
		Serial.print(tan(millis()/_freq)+1.0f);
	}
	
	// UPDATE CHANNEL
	Serial.print(" | DACvolts_");
	Serial.print(_channel);
	Serial.print(":");
	Serial.print(DACvolts[_channel-1]);
	writeChannel(_channel-1,DACvolts[_channel-1]);
}


// --------------------------------------------------------------------------- LFOS MODE ----------------------------
//
void ADDAC::lfosMode(int _MODE, int _type, int _channel){
	ReadManuals(A);
	if(_MODE==0){ // UPDATE ALL CHANNELS
		if(_type==0){ // TRIANGLE   -   still buggy!!  passar para unsigned long??
			int inc=1.0f*(manualValuesA[0]*16.0f+1.0f);
			for(int i=0; i<8;i++){
				if(direction[i]){
					DACvolts[i]+=inc;
					if(DACvolts[i]>=manualValuesAMapped[2]){ //manualValuesA[2] = MAX
						DACvolts[i]=manualValuesAMapped[2];
						direction[i]=false;
					}
				}else{
					DACvolts[i]-=inc;
					if(DACvolts[i]<=manualValuesAMapped[1]){ //manualValuesA[1] = MIN
						DACvolts[i]=manualValuesAMapped[1];
						direction[i]=true;
					}
				}
				writeChannel(i,DACvolts[i]);
			}
		}else if(_type==1){ // BUGGY TRIANGLE   -   still buggy!!  passar para unsigned long??
				int inc=1.0f*(manualValuesA[0]*16.0f+1.0f);
				for(int i=0; i<8;i++){
					if(Direction){
						DACvolts[i]+=inc;
						if(DACvolts[i]>=manualValuesAMapped[2]){ //manualValuesA[2] = MAX
							DACvolts[i]=manualValuesAMapped[2];
							Direction=false;
						}
					}else{
						DACvolts[i]-=inc;
						if(DACvolts[i]<=manualValuesAMapped[1]){ //manualValuesA[1] = MIN
							DACvolts[i]=manualValuesAMapped[1];
							Direction=true;
						}
					}
					writeChannel(i,DACvolts[i]);
				}
		}else if(_type==2){ // SAW
			int inc=1.0f*(manualValuesA[0]*8.0f+1.0f);
			for(int i=0; i<8;i++){
				DACvolts[i]+=inc;
				if(DACvolts[i]+inc>=manualValuesAMapped[2] || DACvolts[i]<manualValuesAMapped[1]){ //manualValuesA[2] = MAX
					DACvolts[i]=manualValuesAMapped[1]; //manualValuesA[1] = MIN
				}
				writeChannel(i,DACvolts[i]);
			}
		}else if(_type==3){ // INVERTED SAW
			int inc=1.0f*(manualValuesA[0]*8.0f+1.0f);
			for(int i=0; i<8;i++){
				DACvolts[i]-=inc;
				if(DACvolts[i]-inc<=manualValuesAMapped[1] || DACvolts[i]-inc>manualValuesAMapped[2]){ //manualValuesA[2] = MAX
					DACvolts[i]=manualValuesAMapped[2]; //manualValuesA[1] = MIN
				}
				writeChannel(i,DACvolts[i]);
				if(i==0){
					Serial.print("inc:");
					Serial.print(inc);
					Serial.print(" Max:");
					Serial.print(manualValuesAMapped[1]);
					Serial.print(" Min:");
					Serial.print(manualValuesAMapped[2]);
					Serial.print(" DAC:");
					Serial.println(DACvolts[i]);
				}
			}
		}else if(_type==4){ // RND RAMPS
			int inc=1.0f*(manualValuesA[0]*16.0f+1.0f);
			for(int i=0; i<8;i++){
				if(DACvolts[i]==rndStep[i]){
					rndStep[i]=random(manualValuesAMapped[1],manualValuesAMapped[2]);
				}
				if(DACvolts[i]>rndStep[i]){
					direction[i]=false;
				}else{
					direction[i]=true;
				}
				if(direction[i]){
					DACvolts[i]+=inc;
					if(DACvolts[i]>=rndStep[i]){ //manualValuesA[2] = MAX
						DACvolts[i]=rndStep[i];
					}
				}else{
					DACvolts[i]-=inc;
					if(DACvolts[i]<=rndStep[i]){ //manualValuesA[1] = MIN
						DACvolts[i]=rndStep[i];
					}
				}
				writeChannel(i,DACvolts[i]);
			}
		}
	}else if(_MODE==1){ // UPDATE INDIVIDUAL CHANNELS
		DACvolts[_channel]+=1*(manualValuesA[0]+1);
		writeChannel(_channel,DACvolts[_channel]);
	}
	
	/*Serial.print("inc:");
	Serial.print(inc);
	Serial.print(" AN1");
	Serial.print(manualValuesAMapped[1]);
	Serial.print(" AN2");
	Serial.print(manualValuesAMapped[2]);
	Serial.print(" step:");
	Serial.print(rndStep[0]);
	Serial.print(" DAC:");
	Serial.print(DACvolts[0]);
	Serial.println();*/
}


// --------------------------------------------------------------------------- MIXER MODE -------------------------

void ADDAC::mixerMode(){ // MIX ALL 7 FIRST
	unsigned long avg=0;
	for(int i=0; i<7; i++){
		avg+=DACvolts[i];
	}
	DACvolts[8]=avg/7;
	// UPDATE CHANNEL
	writeChannel(7,DACvolts[8]);
}
void ADDAC::mixerMode(int _upToX){ // MIX ALL FIRSTS up to X
	unsigned long avg=0;
	for(int i=0; i<_upToX; i++){ 
		avg+=DACvolts[i];
	}
	DACvolts[8]=avg/_upToX;
	// UPDATE CHANNEL
	writeChannel(7,DACvolts[8]);
}
void ADDAC::mixerMode(int _channel, int _A, int _B){ // MIX 2
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	DACvolts[_channel]=avg/2;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}
void ADDAC::mixerMode(int _channel, int _A, int _B, int _C){ // MIX 3
	unsigned long avg=0;
	avg+=DACvolts[_A];
	avg+=DACvolts[_B];
	avg+=DACvolts[_C];
	DACvolts[_channel]=avg/3;
	// UPDATE CHANNEL
	writeChannel(_channel,DACvolts[_channel]);
}
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
void ADDAC::writeChannel(int _channel, unsigned int _voltage){ // INTERNAL
	byte b1 = B11110000|WRITE_UPDATE_N; //padding at beginning of byte
	byte b2 = _channel << 4 | _voltage >> 12; //4 address bits and 4 MSBs of data
	byte b3 = (_voltage << 4) >> 8; // middle 8 bits of data
	byte b4 = (_voltage << 12) >> 8 | B00001111;
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
	digitalWrite(SLAVESELECT, LOW);
	delayMicroseconds(1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
	delayMicroseconds(1);
	delayMicroseconds(1);
	delayMicroseconds(1);
	digitalWrite(SLAVESELECT, HIGH);
    
    
    
}

void ADDAC::WriteChannel(int _channel, unsigned int _voltage){ // EXTERNAL - WRITING FROM ARDUINO ENVIRONMENT
	byte b1 = B11110000|WRITE_UPDATE_N; //padding at beginning of byte
	byte b2 = _channel << 4 | _voltage >> 12; //4 address bits and 4 MSBs of data
	byte b3 = (_voltage << 4) >> 8; // middle 8 bits of data
	byte b4 = (_voltage << 12) >> 8 | B00001111;
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
	digitalWrite(SLAVESELECT, LOW);
	delayMicroseconds(1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
	shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
	delayMicroseconds(1);
	delayMicroseconds(1);
	delayMicroseconds(1);
	digitalWrite(SLAVESELECT, HIGH);
    //update array to mixerMode and others...
    DACvolts[_channel]=_voltage;
}

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
				digitalWrite(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				delayMicroseconds(1);
				delayMicroseconds(1);
				digitalWrite(SLAVESELECT, HIGH);
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
				digitalWrite(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				digitalWrite(SLAVESELECT, HIGH);
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
				digitalWrite(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				digitalWrite(SLAVESELECT, HIGH);
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
				digitalWrite(SLAVESELECT, LOW);
				delayMicroseconds(1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b1);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b2);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b3);
				shiftOut(DATAOUT, SPICLK, MSBFIRST, b4);
				delayMicroseconds(1);
				digitalWrite(SLAVESELECT, HIGH);
				break;
			}
		}
}

// --------------------------------------------------------------------------- MODES SWITCH -------------------------
//
void ADDAC::readMODEswitch(){
#if defined VS3
	byte switchVar1 = 0;
	byte modeByte = 0;
	byte submodeByte = 0;
	//Pulse the latch pin:
	//set it to 1 to collect parallel data
	digitalWrite(latchPin,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWrite(latchPin,0);
	
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
	digitalWrite(latchPin,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWrite(latchPin,0);
	
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
	digitalWrite(latchPin,1);
	//set it to 1 to collect parallel data, wait
	delayMicroseconds(20);
	//set it to 0 to transmit data serially  
	digitalWrite(latchPin,0);
	
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
int ADDAC::readMODE(){
	return MODE;
}
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
		digitalWrite(myClockPin, 0);
		delayMicroseconds(2);
		temp = digitalRead(myDataPin);
		if (temp) {
			myDataIn = myDataIn | (1 << i);
		}
		digitalWrite(myClockPin, 1);
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
	digitalWrite(myDataPin, 0);
	digitalWrite(myClockPin, 0);
	
	//for each bit in the byte myDataOut
	//NOTICE THAT WE ARE COUNTING DOWN in our for loop
	//This means that %00000001 or "1" will go through such
	//that it will be pin Q0 that lights. 
	for (i=7; i>=0; i--)  {
		digitalWrite(myClockPin, 0);
		
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
		digitalWrite(myDataPin, pinState);
		//register shifts bits on upstroke of clock pin  
		digitalWrite(myClockPin, 1);
		//zero the data pin after shift to prevent bleed through
		digitalWrite(myDataPin, 0);
	}
	
	//stop shifting
	digitalWrite(myClockPin, 0);
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
	digitalWrite(myDataPin, 0);
	digitalWrite(myClockPin, 0);
	
	//for each bit in the byte myDataOut
	//NOTICE THAT WE ARE COUNTING DOWN in our for loop
	//This means that %00000001 or "1" will go through such
	//that it will be pin Q0 that lights. 
	for (i=7; i>=0; i--)  {
		digitalWrite(myClockPin, 0);
		
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
		digitalWrite(myDataPin, pinState);
		//register shifts bits on upstroke of clock pin  
		digitalWrite(myClockPin, 1);
		//zero the data pin after shift to prevent bleed through
		digitalWrite(myDataPin, 0);
	}
	
	//stop shifting
	digitalWrite(myClockPin, 0);
}

// --------------------------------------------------------------------------- END ----------------------------------
//

