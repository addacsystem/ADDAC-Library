//#ifdef MIDIenable

void MIDIread(){
  
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
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
  MIDInotes[0]=pitch;
  MIDIvelocities[0]=velocity;
  MIDInoteON[0]=true;
  if (velocity == 0) {
    // This acts like a NoteOff.
    MIDInotes[0]=0;
    MIDIvelocities[0]=0;
    MIDInoteON[0]=false;
  }
  Serial.print("MIDI NOTE:");
  Serial.print(pitch);
  Serial.print("VEL:");
  Serial.println(velocity);
  // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
  // and have a bad impact on real-time performance.
}
//#endif
