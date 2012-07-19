 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Clock.h"

//-----------------------------------------------------------------------ADDAC CLOCK-----------------


ADDAC_Clock::ADDAC_Clock(int _pin){
	pin=_pin;
	//Serial.println("OUT SET!");
	time=millis();
	oldTime=time;
	
	stepsPerBar=4;
	stepSize=1;
	actualStep=1;
	step=1;
	bars= 1; 
	actualBar=1;
	delay=0;
    Counter=0;
	
    Counter=0;
    gateVal=0;
    time = 0; 
    timeInterval=1000; 
    dutyCycle=100;
    state = false;
    CLKtrig=false;
    CLKval=false;
    CLKup=false;
    CLKdown=false;
    OUT=false;

	STEP=false;
	ON=false;
	CLOCK=false;
}



ADDAC_Clock::ADDAC_Clock(int _pin, int _steps, int _stepSize){
	pin=_pin;
	//Serial.println("simpleOUT SET!");
	time=millis();
	oldTime=time;
	
	stepsPerBar=_steps;
	stepSize=_stepSize;
	actualStep=1;
	bars= 1; 
	actualBar=1;
	delay=0;
	
    Counter=0;
    gateVal;
    time = 0; 
    timeInterval=1000; 
    dutyCycle=100;
    state = false;
    CLKtrig=false;
    CLKval=false;
    CLKup=false;
    CLKdown=false;
    OUT=false;
    
	STEP=false;
	ON=false;
	CLOCK=false;
}


void ADDAC_Clock::checkClock(bool _val){
    CLKval = _val;
  #ifdef DEBUG
    //Serial.print("  TuneTrig:");
    //Serial.print(CLKval, DEC);
  #endif
    // AVOID CONTINUOUS PRESSING
    if(CLKval && !CLKtrig){ // IF TRIGGER PRESSED
        CLKtrig=true; // ACTIVE ON
        CLKup=true;
    }else if(CLKval && CLKtrig){ // IF PRESSING
        CLKval=false; // DISABLE
    }else if(!CLKval && CLKtrig){ // WHEN RELEASED
        CLKtrig=false; // NOT ACTIVE
        CLKdown=true;
    }
}

void ADDAC_Clock::checkChangeState(){
    if(CLKup){
        CLKup=false;
        state=true;
        oldTime=time;
        time=millis();
        if(!RESEt){
            timeInterval = time-oldTime;
        }else{
            RESEt=false;
        }
        Counter++;
        CLOCK=true;
        
    }else if(CLKdown){
        CLKdown=false;
        dutyCycle = millis()-time;
        state = false;
    }
}

// --------------------------------------------------------------------------- UPDATE -------------------------
//

void ADDAC_Clock::update(bool _INval, bool _reset, unsigned long tempTime, int _pot1, int _pot2){
   
    Pot1Bars = _pot1;
    Pot2Steps = _pot2;
    
    if(_reset){
        time=millis();
        reset(time);
        RESEt=true;
    }
    
	if(CLOCK){
		clock(tempTime, interval, dutyCycle);
		CLOCK=false;
	}
    
    //digitalWrite(led0Pin, state);
    
    /*if(!state){
        //digitalWrite(led1Pin, LOW);
    }else{
        if(Counter%1==0) //digitalWrite(led1Pin, HIGH);
    }*/
    
    
    checkClock(_INval);
    checkChangeState();
    
	
	if (ON && oldTime+dutyCycle  < tempTime) {
		OUT=false;
     #ifdef DEBUG
        Serial.print(" |OFF| ");
      #endif
		ON=false;
	}
	
	stepUpdate(tempTime);
	
}

void ADDAC_Clock::simpleUpdate(int Counter, int _interval, int _dutyCycle, unsigned long tempTime, int _pot1, int _pot2){
	
	//if(_dutyCycle>stepTime*stepSize) dutyCycle=_dutyCycle/stepsPerBar;
	//else dutyCycle=_dutyCycle;
	//dutyCycle=50;
	stepUpdate(tempTime);
    if(STEP){
        int mod = (actualStep - 1 + ((actualBar-1)*stepsPerBar))  %  stepSize;
        if(mod == 0){
            OUT=true;
            ON=true;
            oldTime = tempTime;
        }
        STEP=false;
    }
    
	if (ON && oldTime+dutyCycle  < tempTime) {
		ON=false;
		OUT=false;
	}
}

void ADDAC_Clock::stepUpdate(unsigned long tempTime){
	if(!STEP && time < tempTime && step<=stepsPerBar){
		time+=stepTime;
		if(step==1 && actualStep>1)actualStep++;
		else if(step!=1)actualStep++;
		
		step++;
		
      #ifdef DEBUG
		Serial.println();
		Serial.print(" | step:");
		Serial.print(step);
		Serial.print("  |  bars:");
		Serial.print(bars);
		Serial.print("  |  actualBar:");
		Serial.print(actualBar);
		Serial.print("  |  BarSteps:");
		Serial.print(stepsPerBar);
		Serial.print("  |  actualStep:");
		Serial.print(actualStep);
		Serial.print("  |  stepSize:");
		Serial.print(stepSize);
		//Serial.print("  |  stepTime:");
		//Serial.print(stepTime);
		//Serial.print("  |  dCycle:");
		//Serial.print(dutyCycle);
      #endif
        
		int mod = (actualStep - 1)  %  stepSize;
        #ifdef DEBUG
		  Serial.print(" | MODULUS:");
		  Serial.print(mod);
        #endif
		
        if(mod == 0){
			//digitalWrite(pin,HIGH);
			OUT=true;
            ON=true;
			oldTime = tempTime;//time-stepTime;
          #ifdef DEBUG
			Serial.print("  |ON| ");
          #endif
		}
	}else{
      #ifdef DEBUG
		//Serial.print(".");
      #endif
	}
}

void ADDAC_Clock::simpleStepUpdate(unsigned long tempTime){
	if(!STEP && time+stepTime < tempTime){
		time+=stepTime;
		actualStep++;
		STEP=true;
	}
}




void ADDAC_Clock::reset(unsigned long _time){
	step=1;
	time=_time;
	actualBar=1;
	actualStep=1;
	stepSize = Pot1Bars/1024.0f*(stepsPerBar*2)+1; // prevent divide by zero!!
	
	for (int i = 1; i<50; i++) {
		int temp = (stepSize * i) % stepsPerBar;
		if(temp == 0){
			bars = i;
			break;
		}
	}
	stepUpdate(_time);
}

void ADDAC_Clock::clock(unsigned long _time, int _interval, int _dutyCycle){
	step=1;
	time=_time;
	stepsPerBar = Pot2Steps/1023.0f*12; // prevent divide by zero!!
	stepTime = _interval/stepsPerBar;
	stepSize = Pot1Bars/1024.0f*(stepsPerBar*2)+1; // prevent divide by zero!!
	
	dutyCycle=stepTime*stepSize/2;
	
	if(stepSize>1){
		int div=0;
		for (int i = 1; i<50; i++) {
			div = (stepsPerBar-stepSize + div) % stepSize;
			if(div == 0){
				bars = i;
				break;
			}
		}
	}else{
		bars=1;
		
	}
	
	if(actualBar < bars){
		actualBar++;
		stepUpdate(_time);
	}else {
		actualBar=1;
		actualStep=1;
	}
}

void ADDAC_Clock::simpleClock(unsigned long _time, int _interval, int _dutyCycle){
	time=_time;
	oldTime=time;
	STEP=true;

	stepTime = _interval/stepsPerBar;

	dutyCycle=stepTime*stepSize/2;
	if(stepSize>1){
		int div=0;
		for (int i = 1; i<50; i++) {
			div = (stepsPerBar-stepSize + div) % stepSize;
			if(div == 0){
				bars = i;
				break;
			}
		}
	}else{
		bars=1;
		
	}
	
	if(actualBar < bars){
		actualBar++;
	}else {
		actualBar=1;
		actualStep=1;
	}
}



// --------------------------------------------------------------------------- END ----------------------------------
//