

//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>   
#include <Wire.h>
////////////////////////////////////


// DEBUG ?
#define DEBUG



#include <ADDAC.h>
#include <ADDAC_Random.h>
#include <ADDAC_Quantizer.h>
#include <ADDAC_Lin2Log.h>
#include <ADDAC_Comparator.h>
ADDAC VCC;

//INCLUDE MIDI LIBRARY//
#include <ADDAC_Midi.h>
ADDAC_Midi MIDI;


void setup(){
  #if defined DEBUG
    Serial.begin(115200); // SERIAL COMMUNICATION BAUD RATE - 115200 - RECOMMENDED!
  #endif
  
  // STARTS MIDI
  Serial1.begin(31250);  // INITIALIZES SERIAL PORT 2
  MIDI.begin(1);         // INITIALIZES MIDI
  MIDI.useCC(true);      // ACTIVATES ControlChange READINGS
  
}


void loop(){
  MIDI.update(); // USE THIS TO UPDATE MIDI READINGS
  
  #ifdef DEBUG
    Serial.print(" CC10:");
    Serial.print(MIDI.CCvals[1][10]); // CHANNEL, CC
    Serial.print(" CC11:");
    Serial.print(MIDI.CCvals[1][11]);
    Serial.print(" CC12:");
    Serial.print(MIDI.CCvals[1][12]);
    
    Serial.println();
    delay(50);
  #endif
}
