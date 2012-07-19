#ifdef MIDIenable

void MIDIread(){
  if (Serial1.available() > 0) {
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
        
        //      blinkTime=controlChangeVal*10;
        //delay(1000);
        /*
    }else if (incomingByte== 208){ // aftertouch message starting
         //not implemented yet
         }else if (incomingByte== 160){ // polypressure message starting
         //not implemented yet
         }else if ( (action==0)&&(note==0) ){ // if we received a "note off", we wait for which note (databyte)
         note=incomingByte;
         playNote(note, 0);
         note=0;
         velocity=0;
         action=2;
         }else if ( (action==1)&&(note==0) ){ // if we received a "note on", we wait for the note (databyte)
         note=incomingByte;
         }else if ( (action==1)&&(note!=0) ){ // ...and then the velocity
         velocity=incomingByte;
         playNote(note, velocity);
         note=0;
         velocity=0;
         action=0;*/
      }else{
        //nada
      }
    }
  }
}
#endif
