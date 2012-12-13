//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>   
////////////////////////////////////

// DEBUG ?
// USE DEBUG FOR TESTING PURPOSES ONLY IT WILL LOOSE MESSAGES IF ACTIVE!!
#define DEBUG

#include <ADDAC.h>
ADDAC VCC;

//INCLUDE MIDI LIBRARY//
#include <ADDAC_Midi.h>
ADDAC_Midi MIDI;

boolean UP=true;


void setup(){
  #ifdef DEBUG
    Serial.begin(115200); // INITIALIZE SERIAL COMMUNICATION BAUD RATE - 115200 - RECOMMENDED!
  #endif
  
  // STARTING MIDI
  // MIDI SHOULD BE RESTRAINED TO 1 CHANNEL
  // IF MORE IS NEEDED -CHANGE ADDAC_Midi.h file in library folder - 
  // TAKE IN CONSIDERATION THAT EACH CHANNEL USES 128 bytes for CC storage
  // WORKING BY DEFAULT ON CHANNELS 1 & 2
  // COMMON ERROR OF EXCEEDING MEMORY IS A TOTAL STALL OF THE PROCESS, NO PRINTS, NO ACTIVITY...
  Serial1.begin(31250);  // INITIALIZES SERIAL PORT 2
  MIDI.begin(1);         // INITIALIZES MIDI CHANNEL X  ||  0 = INITIALIZES MIDI in ALL CHANNELS.
  MIDI.useCC(true);      // ACTIVATES ControlChange READINGS
  
  // NOTES ON & OFF
  // NOTES REGARD NO CHANNEL, ANY CHANNEL IS MERGED INTO ONE SINGLE ARRAY
  MIDI.useNotes(true);      // ACTIVATES Note ON & OFF ANALYSIS

}


void loop(){
  MIDI.update(); // USE THIS TO UPDATE MIDI READINGS

  // PRINTING MIDI INPUTS
  // for matching purposes array [0] is not used, starts at [1] to match cc control values
  #ifdef DEBUG
    // CALLING MIDI CC VALUES FROM STORED VALUES
    Serial.print(" CC10:");
    Serial.print(MIDI.CCvals[1][10]); // CHANNEL, CC
    Serial.print(" CC11:");
    Serial.print(MIDI.CCvals[1][11]); // CHANNEL, CC
    
    Serial.print(" Active Notes: ");
    for(int i=0; i<128; i++){ // Prints active notes on midi channel 1
      if(MIDI.notesOn[i]){
        Serial.print(" (");
        Serial.print(i);
        Serial.print(", ");
        Serial.print(MIDI.notesVelocity[i]);
        Serial.print("), ");
      }
    }
    Serial.print(" TOTAL:");
    Serial.print(MIDI.totalNotes);
    
    Serial.print(" MONOPHONIC:");
    Serial.print(MIDI.monoNote);
    Serial.print(", ");
    Serial.print(MIDI.monoVelocity);
    
    Serial.println();
    delay(20);
  #endif
}
