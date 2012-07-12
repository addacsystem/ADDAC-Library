
/*

to do:

Glide!
Monophonic Mode
Arpeggiator for monophonic mode?
Filter envelope
Gate out

*/



#ifdef MIDIenable

void ADDAC_MIDIcc(byte channel, byte number, byte value){ // NOT RESPECTING CHANNEL!!!!
   controlChangeVal[number]=value;
   #ifdef DEBUGmidi
     Serial.print("CChange:");
     Serial.print(number);
     Serial.print(" Val:");
     Serial.println(value);
   #endif
}

void ADDAC_MIDIclock(){ // MIDI CLOCK ACTIONS
   #ifdef DEBUGmidi
     Serial.print(" - Midi_ClockBang - ");
   #endif
}

void ADDAC_MIDIstart(){ // MIDI START ACTIONS
   #ifdef DEBUGmidi
     Serial.print(" - Midi_Start - ");
   #endif
}

void ADDAC_MIDIcontinue(){ // MIDI CONTINUE ACTIONS
   #ifdef DEBUGmidi
     Serial.print(" - Midi_Continue - ");
   #endif
}

void ADDAC_MIDIstop(){ // MIDI STOP ACTIONS
   #ifdef DEBUGmidi
     Serial.print(" - Midi_Stop - ");
   #endif
}

void ADDAC_MIDInoteOn(byte channel, byte pitch, byte velocity) {  // MIDI NOTE ON ACTIONS
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
