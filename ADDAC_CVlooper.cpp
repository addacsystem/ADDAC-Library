 

#include "ADDAC_CVlooper.h"


//-----------------------------------------------------------------------ADDAC CV LOOPER -----------------

ADDAC_CVlooper::ADDAC_CVlooper(){	
	
	index=0;
	buffsNum=1;
	buffSize=256;
	ADDAC_CVbuffer temp;
	for(int i=0;i<3;i++){ // 5 = MAXIMUM OF 256*5*2 bytes
		CVbuffer[i]= temp;//temp;
		//CVbufferTimes[i]= temp;//temp;
	}
	
	currentVal=0;
	interval=36;
	time=millis();
	
	Serial.println("CVrec COMPLETE");
}

void ADDAC_CVlooper::update(int _MODE, int _interval, float _wet, int _val){
	//_MODE 0 == LOOP MODE
	//_MODE 1 == OVERDUB MODE
	//_MODE 2 == ERASE MODE
	
	wet=_wet; // INPUT Strength, 
	
	if(millis()>time+interval){
		interval=_interval/2; // BETWEEN 0(i.e. full sampleRate) and 511 ms
		time=millis();
		Serial.print(currentVal);
		if(currentVal<buffsNum*buffSize){ // BUFFER/ LOOP SIZE!!! IMPLEMENT DINAMIC MODE!
			record(_val);
			Serial.print(" /: ");
			Serial.print(currentVal/buffSize);
			Serial.print(" %: ");
			Serial.print(currentVal%buffSize);
			//analogWrite(pwmPin,analogRead(0)/4);
			currentVal++;
			Serial.print(" millis: ");
			Serial.print(millis());
		}else{
			if(_MODE==1){			// OVERDUB
				overdub(_val);	
			}else if(_MODE==2){		// ERASE
				clearRecord(_val);
				Serial.print(" recMode: ");
				Serial.print(_MODE);
			}else{					// PLAY
				play();
			}
		}
		//Serial.println();
  }
}

void ADDAC_CVlooper::loopSize(int _val){
	buffSize = _val%256;
	buffsNum = _val/256;
	
}


void ADDAC_CVlooper::record(int _val){
	if(index>buffSize*buffsNum){
		index=0;
	}else{
	b_index=index/buffSize;
	n_index=index%buffSize;
	Serial.print(" : Rec:");
	CVbuffer[b_index].write(n_index, _val);
	//CVbufferTimes[b_index].write(n_index, millis());
	CVstream=CVbuffer[b_index].read(n_index)/1023.0f*addacMaxResolution;
	//writeChannel(0,DACvolts[0]);
	//analogWrite(PWM_PIN, CVbuffer[b_index].read(n_index)/4);
	Serial.print(CVbuffer[b_index].read(n_index));
		index++;
	}
	
}

void ADDAC_CVlooper::clearRecord(int _val){
	if(playIndex>buffSize*buffsNum){
		playIndex=0;
	}else{
		b_index=playIndex/buffSize;
		n_index=playIndex%buffSize;
		Serial.print(" : ClearRec:");
		CVbuffer[b_index].write(n_index, _val);
		//CVbufferTimes[b_index].write(n_index, millis());
		CVstream=CVbuffer[b_index].read(n_index)/1023.0f*addacMaxResolution;
		//writeChannel(0,DACvolts[0]);
		//analogWrite(PWM_PIN, CVbuffer[b_index].read(n_index)/4);
		Serial.print(CVbuffer[b_index].read(n_index));
		playIndex++;
	}
	
}

void ADDAC_CVlooper::overdub(int _val){
	if(playIndex>buffSize*buffsNum){
		playIndex=0;
	}else{
		b_index=playIndex/buffSize;
		n_index=playIndex%buffSize;
		Serial.print(" : Overdub:");
		CVbuffer[b_index].write(n_index, int(_val*wet + CVbuffer[b_index].read(n_index)*(1.0f-wet)));
		CVstream=CVbuffer[b_index].read(n_index)/1023.0f*addacMaxResolution;
		//writeChannel(0,DACvolts[0]);
		//analogWrite(PWM_PIN, CVbuffer[b_index].read(n_index)/4);
		Serial.print(CVbuffer[b_index].read(n_index));
		playIndex++;
	}
}

void ADDAC_CVlooper::play(){
	if(playIndex>buffSize*buffsNum){
		playIndex=0;
	}else{
		b_index=playIndex/buffSize;
		n_index=playIndex%buffSize;
		Serial.print(" : CVplaying:");
		CVstream=CVbuffer[b_index].read(n_index)/1023.0f*addacMaxResolution;
		//writeChannel(0,DACvolts[0]);
		
		//analogWrite(PWM_PIN, CVbuffer[b_index].read(n_index)/4);
		Serial.print(CVbuffer[b_index].read(n_index));
		playIndex++;
	}
}


// --------------------------------------------------------------------------- END ----------------------------------
//

