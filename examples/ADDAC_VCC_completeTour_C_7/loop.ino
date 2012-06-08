

/*

VCC BEHAVIOUR DEFINITIONS

- Defining how the system operates -


*/


// LOOP is the Basic Code Loop - No multi-threading
void loop(){
  //Serial.print("Mem:");
  //Serial.print( freeMemory() );
  //Serial.print("  |  ");
  
  //VCC.update(); // NEEDED TO UPDATE THE DAC CHIP

  // read from onBoard Input (VS1 & VS2 only)
  //onboardPot=VCC.readOnboardPot(); //number of channels to read
  
  // read new midi input data
  #ifdef MIDIenable
    //MIDIread();
    MIDI.read();
    
    readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
    ADSR1.AD_update(analogValsA[0]*4+1,analogValsA[2]*10+1);
    ADSR2.AD_update(analogValsA[0]*4+1,analogValsA[2]*10+1);
    ADSR3.AD_update(analogValsA[0]*4+1,analogValsA[2]*10+1);
    
    VCC.WriteChannel(1, ADSR1.CVstream);
    VCC.WriteChannel(2, ADSR2.CVstream);
    VCC.WriteChannel(3, ADSR3.CVstream);
   // Serial.print("CV STREAM:");
   // Serial.println(ADSR1.CVstream);
  #endif
  
  
  // NCHUNK
  #ifdef NCHUNK
    nunchuck_get_data();
    nunchuck_parse_data();
  #endif
  
    //PRINT IF DEBUGGING
  #ifdef DEBUGmodes
    Serial.print("MODE:");
    Serial.print(VCC.MODE);
    Serial.print(" | SUBMODE:");
    Serial.print(VCC.SUBMODE);
    Serial.print(" | ");
    //Serial.print(" | ONBOARDmanual:");
   // Serial.print(onboardPot);
  #endif
  #ifdef DEBUGspeed
    Serial.print(" || LOOPtime:");
    Serial.print(millis()-speedOldTimer);
    Serial.print(" || ");
    speedOldTimer=millis();
  #endif
  #ifdef MaxModes
    Serial.print("MODE ");
    Serial.println(MODE);
    Serial.print("SUBMODE ");
    Serial.println(SUBMODE);
    //Serial.print("onboardPot ");
    //Serial.println(onboardPot);
  #endif

  // MAX CONNECTION
  #ifdef MAXMSP
    checkMax();
  #endif
  
  //
  // READING INPUT VALUES HERE
  //
  //read from ADDAC002 - CV / MANUAL INPUTS
  //readCvsINA(6); // connected to input A -> (6) = reads 6 channels
  //read from ADDAC003 - MANUAL INPUTS
  //readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
  //readAnalogsINB(5);
  //read from ADDAC004 - GATE INPUTS
  //readGatesINA(8); // connected to input A -> (8) = reads 8 channels
  //  MIDIread();
    
  // PLAY CLAPPING MUSIC THROUGH GATE OUTPUTS  - old code...
  //ClappingMusic();
    
    
  // BEHAVIOUR FUNCTION - see tab BEHAVIOUR to define MODES
  BEHAVIOUR();
  
  #ifdef DEBUG
    //Serial.println();
    delay(10);
  #endif
}



