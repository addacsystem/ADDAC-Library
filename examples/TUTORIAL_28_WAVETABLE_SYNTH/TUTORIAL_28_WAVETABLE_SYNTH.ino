//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////
#include "ADDAC.h"
#include "waveform.h"
ADDAC VCC;

int point=0;
int pitch=0;
float time;
int prescale;


void setup(){
  //setup VCC class
  VCC.setup();


  //map the Wave Array values to the bipolar voltage level.
  for(int i =0; i<256;i++){
    waveform[i]=mapfloat(waveform[i],-127,126,0.48f,0.52f);
  }

  //Initialize the Timer with a prescale of 1024 running at 1000HZ  
  initializeTimer(1024,1000);

}



void loop(){
  
  //set pitch
  pitch=100*VCC.ReadCv(A,0);
  //update VCC class
  VCC.update();
}

void initializeTimer(int _prescale, long _time){

  prescale=_prescale;
  time=_time;

  cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = (16000000) / (time*prescale) - 1; //(must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts

}



ISR(TIMER1_COMPA_vect){//timer1 interrupt 
  point+=pitch;
  if(point>=256)point-=256;
  //Write to DAC
  VCC.WriteChannel(0,waveform[point]);

}


float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)

{

  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;

}
