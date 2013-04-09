 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_Clock.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Clock CLK;
// INTERRUPT TIMER 1 - needs no changes!
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)

    
   

    
    if(CLK.counter++ >CLK.hzToBpm/60){ // add /60 hzToBpm Bad!!!!! -------- ??????
        // IT'S CLOCK TIME!
        
        //CALL FUNCYION FROM ARDUINO
            CLK.isrCallback();
//          Serial.println("clock");
        
        CLK.counter=0;
        CLK.ON=true;
        CLK.CLOCK_Flag=true;
        //VCC.WriteGatesStraight(A,1,1);
    }
    
//    Serial.print(" CLK.counter - ");
//    Serial.print(CLK.counter);
//    Serial.print(" CLK.hzToBpm - ");
//    Serial.println(CLK.hzToBpm);

    
    /*if(counter >hzToBpm/2){
     // IT'S CLOCK TIME!
     counter=0;
     ON=false;
     VCC.WriteGatesStraight(A,1,0);
     }*/
}





ADDAC_Clock::ADDAC_Clock(){	// INITIALIZE CLASS
	
}


void ADDAC_Clock::setup(void (*isr)()){	// setup CLASS
    
    BPM = 120;
    gateOnTime = 50; //milliseconds for gate on time
    CLOCK_Flag = false;
    // other variables needed for the interrupt timer
    counter = 0;
    hzToBpm = CPU_CLOCK / BPM;
    ON=false;
    Time=0;
    
    //FOR CALLBACK
    isrCallback = isr;                                       // register the user's callback with the real ISR
    
    //Set TIMER
    // TIMER INTERRUPTS - DO NOT CHANGE THIS CHUNK!
    cli();//stop interrupts
    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 124; //  124 = 7500bpm <=> 125HZ <=> (16*10^6) / (125*1024) - 1 (must be <65536)
    //OCR1A = 24; // 24 = 37500bpm <=> 625HZ <=> (16*10^6) / (625*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12 and CS10 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei();//allow interrupts
    
	setBPM(120);

}


void ADDAC_Clock::update(){	// update CLASS
    
    
    
    if(CLOCK_Flag){
        CLOCK_Flag=false;
       // VCC.WriteGatesStraight(A,1,1);
        Time = millis();
    }
    
    if(Time + gateOnTime <millis()){
        //VCC.WriteGatesStraight(A,1,0);
    }
	
    
}


void ADDAC_Clock::setBPM(int _bpm){	// set BPM CLASS
	
    
   // int tempBPM = int(VCC.ReadManual(A,0)*500+1); // Manual 1 controls from 1 to 501 BPMs
    int tempBPM=_bpm;
    if(BPM != tempBPM){
        hzToBpm = CPU_CLOCK / BPM;
        BPM=tempBPM;//add this???
        counter=0;
    }
    
    
}


