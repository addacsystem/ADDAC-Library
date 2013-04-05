//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
ADDAC VCC; 

//INCLUDE MIDI LIBRARY//
#include <ADDAC_Midi.h>
ADDAC_Midi MIDI;

//#define DEBUG   // Comment this line if you are not debugging

//Variable to store the amount of clocks received
int nClock=0;

//Clock Divider value - start with 12
int clockDivider=12;


void setup(){
  //setup all VCC main settings
  VCC.setup();

  //Setup MIDI settings
  Serial1.begin(31250);  // INITIALIZES SERIAL PORT 2
  MIDI.begin(1);    

  //debug settings
#ifdef DEBUG
  //serial speed communication 
  Serial.begin(115200);
#endif
}


void loop(){
  //UPDATE VCC 
  VCC.update();

  //UPDATE MIDI
  MIDI.update();

  //THIS FUNCTION WILL BE CALLED EVERY MIDI CLOCK
  MIDI.setHandleClock ( HandleClock );

  //SET CLOCK DIVIDER TO EQUALS CVIN 0.
  clockDivider=(VCC.ReadCv(A,0)*20)+1;



  if(nClock%clockDivider==0){   
    VCC.WriteChannel(0,1);

  }
  else{  

    VCC.WriteChannel(0,0);
  }


#ifdef DEBUG
  Serial.println(clockDivider);
  delay(10);
#endif


}

void HandleClock() {

  //INCREASE nClock VARIABLE EVERY MIDI CLOCK
  nClock++;

}

