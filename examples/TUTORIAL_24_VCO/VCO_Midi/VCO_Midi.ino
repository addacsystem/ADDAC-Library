//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////


#include <ADDAC.h>
#include <ADDAC_VCO.h>

//INCLUDE MIDI LIBRARY//
#include <ADDAC_Midi.h>
ADDAC_Midi MIDI;

//#define DEBUG

// INCLUDES THE MAIN ADDAC LIBRARY

// THEN INITIALIZES LIBRARY CLASS
ADDAC VCC; // From now on the class will be called "VCC"

boolean UP=true;
float volume=0;


void setup(){
  VCC.setup();
  
  // initialize VCO 
  VCO.initialize();         // initialize timer1, and set a 1/2 second period
  VCO.startup(VCO_update);  // attaches callback() as a timer overflow interrupt
  
  
  Serial1.begin(31250);  // INITIALIZES SERIAL PORT 2
  MIDI.begin(1);         // INITIALIZES MIDI CHANNEL 1  ||  0 = INITIALIZES MIDI in ALL CHANNELS.
  MIDI.useNotes(true);      // ACTIVATES Note ON & OFF ANALYSIS
  
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
}

void VCO_update(){ // DO NOT OVERLOAD THIS FUNCTION!!!
  VCC.WriteChannel(0, UP* volume+ ((1- volume)/2.0f));
  UP=!UP;
}


void loop(){
  MIDI.update();
  VCC.update(); // NEED TO UPDATE THE VCC!

  volume = MIDI.monoVelocity/127.0f; 
  VCO.update(MIDI.monoNote, volume); 
   
    #ifdef DEBUG
      Serial.print(" MONOPHONIC:");
      Serial.print(MIDI.monoNote);
      Serial.print(", ");
      Serial.print(volume);
    
      Serial.println();
      delay(20);
    #endif

}





