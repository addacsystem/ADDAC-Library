
/*

to do:

Glide!
Monophonic Mode
Arpeggiator for monophonic mode?
Filter envelope
Gate out

*/



#ifdef MIDIenable


void MIDI_CCread(){
  if (Serial1.available() > 0) {
    byte controlChangeValTemp;
    //delay(200);
    // read the incoming byte:
    if(byteNum==0){
      Serial.println("BYTE IN");
      byteNum++;
      incomingByte = Serial1.read();
      //Serial.println(incomingByte,DEC);
    }
    else if(byteNum==1){
      byteNum++;
      controlChange=Serial1.read();
      #ifdef DEBUGmidi
        Serial.print("CC:");
        Serial.print(controlChange,DEC);
      #endif
    }
    else if(byteNum==2){
      byteNum++;
      controlChangeValTemp=Serial1.read();
      #ifdef DEBUGmidi
        Serial.print("->");
        Serial.println(controlChangeValTemp,DEC);
      #endif
    }
    //blinkTime=map(incomingByte,176,191,0,1000);
    //interval=incomingByte*10;
    // wait for as status-byte, channel 1, note on or off
    if(byteNum==3){
      byteNum=0;
      if (incomingByte== 144){ // note on message starting starting
        action=1;
      }else if (incomingByte== 128){ // note off message starting
        action=0;
      }else if (incomingByte>= 176 && incomingByte<= 191){ // CONTROL CHANGE
        //interval=map(controlChangeVal,0,127,0,1000);
        controlChangeVal[controlChange]=controlChangeValTemp;
   
      }else{
        //nada
      }
    }
  }
}


void MIDIread(){
  
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    Serial.println("MIDI IN");
    switch(MIDI.getType()) {		// Get the type of the message we caught
      case NoteOff:
        break;
      case NoteOn:
        break;
      case ControlChange:
        break;
      case ProgramChange: 
        //BlinkLed(MIDI.getData1());	// Blink the LED a number of times 
        break;
      case PitchBend:
        break;
      case Clock:
        break;
      // See the online reference for other message types
      default:
        break;
    }
  }
  /*
  NoteOff	              = 0x80,	///< Note Off
	NoteOn                = 0x90,	///< Note On
	AfterTouchPoly        = 0xA0,	///< Polyphonic AfterTouch
	ControlChange         = 0xB0,	///< Control Change / Channel Mode
	ProgramChange         = 0xC0,	///< Program Change
	AfterTouchChannel     = 0xD0,	///< Channel (monophonic) AfterTouch
	PitchBend             = 0xE0,	///< Pitch Bend
	SystemExclusive       = 0xF0,	///< System Exclusive
	TimeCodeQuarterFrame  = 0xF1,	///< System Common - MIDI Time Code Quarter Frame
	SongPosition          = 0xF2,	///< System Common - Song Position Pointer
	SongSelect            = 0xF3,	///< System Common - Song Select
	TuneRequest           = 0xF6,	///< System Common - Tune Request
	Clock                 = 0xF8,	///< System Real Time - Timing Clock
	Start                 = 0xFA,	///< System Real Time - Start
	Continue              = 0xFB,	///< System Real Time - Continue
	Stop                  = 0xFC,	///< System Real Time - Stop
	ActiveSensing         = 0xFE,	///< System Real Time - Active Sensing
	SystemReset           = 0xFF,	///< System Real Time - System Reset
	InvalidType           = 0x00    ///< For notifying errors
*/
  
  /*if (Serial1.available() > 0) {
    byte controlChangeValTemp;
    //delay(200);
    // read the incoming byte:
    if(byteNum==0){
      Serial.println("BYTE IN");
      byteNum++;
      incomingByte = Serial1.read();
      Serial.println(incomingByte,DEC);
    }
    else if(byteNum==1){
      byteNum++;
      controlChange=Serial1.read();
      Serial.println(controlChange,DEC);
    }
    else if(byteNum==2){
      byteNum++;
      controlChangeValTemp=Serial1.read();
      Serial.println(controlChangeValTemp,DEC);
    }
    //blinkTime=map(incomingByte,176,191,0,1000);
    //interval=incomingByte*10;
    // wait for as status-byte, channel 1, note on or off
    if(byteNum==3){
      byteNum=0;
      if (incomingByte== 144){ // note on message starting starting
        action=1;
      }else if (incomingByte== 128){ // note off message starting
        action=0;
      }else if (incomingByte>= 176 && incomingByte<= 191){ // CONTROL CHANGE
        //interval=map(controlChangeVal,0,127,0,1000);
        controlChangeVal[controlChange]=controlChangeValTemp;
        
      }else{
        //nada
      }
    }
  }*/
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) { 
  // Do whatever you want when you receive a Note On.
  int noteNum = -1;
  boolean DONE = false;
  
  #ifdef DEBUGmidiNotes
    Serial.println();
  #endif
  
  // CHECK EXISTENT NOTE
  if(notesNum>0){
    for(int i=0; i<polyphonyVoices; i++){
      if(MIDInotes[i]==pitch){
        if(velocity == 0){
          #ifdef DEBUGmidiNotes
            Serial.print("  EXISTENT NOTE CANCEL");
          #endif
          MIDIvelocities[i]=0;
          MIDInoteON[i]=false;
          noteNum=i;
          //MIDIhistory[notesNum]=noteNum; // ??? ISTO ESTA MAL!!!!
          DONE=true;
          notesNum--;
          //VCC.WriteChannel(noteNum+1, 0);
          
          if(noteNum==0) ADSR1.AD_release();
          else if(noteNum==1) ADSR2.AD_release();
          else if(noteNum==2) ADSR3.AD_release();
          
          break;
        /*}else{
          Serial.println("EXISTENT NOTE ADD");
          MIDIvelocities[i]=velocity;
          MIDInoteON[i]==true;
          noteNum=i;
          MIDIhistory[notesNum]=noteNum; // ??? ISTO ESTA MAL!!!!
          DONE=true;
          break;*/
        }
      }else{
          if(velocity == 0 && i==polyphonyVoices-1){
            #ifdef DEBUGmidiNotes
              Serial.print("  UNEXISTENT NOTE CANCEL");
            #endif
            notesNum--;
            DONE=true;
          }
      }
    }
  }
  if(!DONE){
  // CHECK NEXT AVAILABLE SLOT
  for(int i=0; i<polyphonyVoices; i++){
    if(MIDInoteON[i]==false){
      #ifdef DEBUGmidiNotes
      Serial.print("  NEXT AVAILABLE SLOT:");
      Serial.print(i);
      #endif
      noteNum=i;
      break;
    //}else{
      //#ifdef DEBUGmidiNotes
        //Serial.print("  NOT AVAILABLE SLOT:");
        //Serial.print(i);
      //#endif
    }
  }
  
  // IF NO AVAILABLE SLOTS
  if(noteNum==-1){
    noteNum = notesNum%polyphonyVoices;
    Serial.print("NO AVAILABLE SLOT!  ");
    MIDInotes[noteNum]=pitch;
    MIDIvelocities[noteNum]=velocity;
    MIDInoteON[noteNum]=true;
    #ifdef DEBUGmidiNotes
      Serial.print("  STORE NOTE:");
      Serial.print(noteNum);
    #endif
    notesNum++;
    
    
    
    //VCC.WriteChannel(noteNum+1, velocity / 127.0f * addacMaxResolution);
    
  // IF AVAILABLE SLOT X
  }else{
    MIDInotes[noteNum]=pitch;
    MIDIvelocities[noteNum]=velocity;
    MIDInoteON[noteNum]=true;
    
    //MIDIhistory[notesNum]=noteNum;
    notesNum++;
    #ifdef DEBUGmidiNotes
      Serial.print("  STORE NOTE:");
      Serial.print(noteNum);
    #endif
    
  }
  
  if(noteNum==0){
      VCC.WriteChannel(noteNum+5, Quantize.Note(pitch-36, 1.14 ));
      ADSR1.AD_trigger(velocity/127.0f);
    }else if(noteNum==1){
      VCC.WriteChannel(noteNum+5, Quantize.Note(pitch-36, 1.115 ));
      ADSR2.AD_trigger(velocity/127.0f);
    }else if(noteNum==2){
      VCC.WriteChannel(noteNum+5, Quantize.Note(pitch-36, 1.115 ));
      ADSR3.AD_trigger(velocity/127.0f);
    }
    
  }
  
 #ifdef DEBUGmidiNotes
  Serial.print("MIDI NOTE:");
  Serial.print(pitch, DEC);
  Serial.print(", ");
  Serial.print(velocity, DEC);
  
  Serial.print(" | TOTAL NOTES: ");
  Serial.print(notesNum);
  
  //Serial.print(" | VCC NOTE:");
  //Serial.print(Quantize.Note( (MIDInotes[noteNum]-35) ), DEC);
  //Serial.print("  VEL:");
  //Serial.print( MIDIvelocities[noteNum]/127.0f * addacMaxResolution, DEC);
  
  //Serial.print(" | DEBUGGING NOTE:");
  //Serial.print(MIDInotes[noteNum]-35, DEC);
  //Serial.print(" /60:");
  //Serial.print( (MIDInotes[noteNum]-35) / 60.0f, DEC);
  //Serial.print(" *max:");
  //Serial.println( (MIDInotes[noteNum]-35) / 60.0f * addacMaxResolution, DEC);
  #endif
  
  
  //VCC.WriteChannel(noteNum+5, Quantize.Note( MIDInotes[noteNum]-36 ));
  //VCC.WriteChannel(noteNum+1, int( MIDIvelocities[noteNum])/127.0f * addacMaxResolution);
  // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
  // and have a bad impact on real-time performance.
}
#endif
