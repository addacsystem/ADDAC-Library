// Not the cleanest code solution but efficient !?
//
// Maybe it would be a communication improvement to have "delays" between channel printouts, 
// each independent at it's own rate, syncing at diferent milliseconds from the check Time if
// ch1 = 0millis, ch2 = 2millis, and so forth....
// limitation or impossibility may be max serial read refresh rate, i believe it's 10ms!!
// but at least i believe code would never ever stall!



//The ReadCv(slot, CVinput) function will return a float value between 0-1
//We multiply the value by 1023 to get a 0 - 1023 range.
//Convert the value to an integer to increase communication speed
void SendCVinputs(){
  
  //SEND MODES TO MAX
    if(MODESsend){
      if(mode != VCC.MODE){
        mode = VCC.MODE;
        Serial.print("M ");
        Serial.println(VCC.MODE);
      }
      if(submode != VCC.SUBMODE){
        submode = VCC.SUBMODE;
        Serial.print("S ");
        Serial.println(VCC.SUBMODE);
      }
    }
    
  // SEND CV INPUTS  
  switch(nInputs){
      case 0:
        break;
      case 1:
        if(CV1 != VCC.ReadCv(A,0)){
          Serial.print("A ");
          Serial.println(int(VCC.ReadCv(A,0)*1023));
        }
        break;
      case 2:
        if(CV1 != VCC.ReadCv(A,0)){
          Serial.print("A ");
          Serial.println(int(VCC.ReadCv(A,0)*1023));
        }
        if(CV2 != VCC.ReadCv(A,1)){
          Serial.print("B ");
          Serial.println(int(VCC.ReadCv(A,1)*1023));
        }
        break;
      case 3:
        if(CV1 != VCC.ReadCv(A,0)){
          Serial.print("A ");
          Serial.println(int(VCC.ReadCv(A,0)*1023));
        }
        if(CV2 != VCC.ReadCv(A,1)){ 
          Serial.print("B ");
          Serial.println(int(VCC.ReadCv(A,1)*1023));
        }
        if(CV3 != VCC.ReadCv(A,2)){
          Serial.print("C ");
          Serial.println(int(VCC.ReadCv(A,2)*1023));
        }
        break;
      case 4:
        if(CV1 != VCC.ReadCv(A,0)){
          Serial.print("A ");
          Serial.println(int(VCC.ReadCv(A,0)*1023));
        }
        if(CV2 != VCC.ReadCv(A,1)){ 
          Serial.print("B ");
          Serial.println(int(VCC.ReadCv(A,1)*1023));
        }
        if(CV3 != VCC.ReadCv(A,2)){
          Serial.print("C ");
          Serial.println(int(VCC.ReadCv(A,2)*1023));
        }
        if(CV4 != VCC.ReadCv(A,3)){
          Serial.print("D ");
          Serial.println(int(VCC.ReadCv(A,3)*1023));
        }
        break;
      case 5:
        if(CV1 != VCC.ReadCv(A,0)){
          Serial.print("A ");
          Serial.println(int(VCC.ReadCv(A,0)*1023));
        }
        if(CV2 != VCC.ReadCv(A,1)){ 
          Serial.print("B ");
          Serial.println(int(VCC.ReadCv(A,1)*1023));
        }
        if(CV3 != VCC.ReadCv(A,2)){
          Serial.print("C ");
          Serial.println(int(VCC.ReadCv(A,2)*1023));
        }
        if(CV4 != VCC.ReadCv(A,3)){
          Serial.print("D ");
          Serial.println(int(VCC.ReadCv(A,3)*1023));
        }
        if(CV5 != VCC.ReadCv(A,4)){
          Serial.print("E ");
          Serial.println(int(VCC.ReadCv(A,4)*1023));
        }
        break;
      case 6:
        if(CV1 != VCC.ReadCv(A,0)){
          Serial.print("A ");
          Serial.println(int(VCC.ReadCv(A,0)*1023));
        }
        if(CV2 != VCC.ReadCv(A,1)){ 
          Serial.print("B ");
          Serial.println(int(VCC.ReadCv(A,1)*1023));
        }
        if(CV3 != VCC.ReadCv(A,2)){
          Serial.print("C ");
          Serial.println(int(VCC.ReadCv(A,2)*1023));
        }
        if(CV4 != VCC.ReadCv(A,3)){
          Serial.print("D ");
          Serial.println(int(VCC.ReadCv(A,3)*1023));
        }
        if(CV5 != VCC.ReadCv(A,4)){
          Serial.print("E ");
          Serial.println(int(VCC.ReadCv(A,4)*1023));
        }
        if(CV6 != VCC.ReadCv(A,5)){
          Serial.print("F ");
          Serial.println(int(VCC.ReadCv(A,5)*1023));
        }
        break;
    }
    ReadCVinputs();
}


void ReadCVinputs(){
  CV1=VCC.ReadCv(A,0);
  CV2=VCC.ReadCv(A,1);
  CV3=VCC.ReadCv(A,2);
  CV4=VCC.ReadCv(A,3);
  CV5=VCC.ReadCv(A,4);
  CV6=VCC.ReadCv(A,5);
}
