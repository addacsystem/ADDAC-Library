

/*

DONT NEED TO CHANGE NOTHING HERE !!

.
UNLESS YOU REALLY REALLY WANT TO



plays Steve Reich's "Clapping Music" Score through Gate Outputs


*/



void ClappingMusic(){
  //write to ADDAC005 - connected to input A
  int advance;
  int BPM=50;//onboardPot/1024.0f*200+50; // between 50 and 250 bpm
  if(dataStep<12){
    advance=VCC.WriteGatesA(gatesOutAdataArray[dataStep], BPM*2);
  }else{
    dataStep=0;
    advance=VCC.WriteGatesA(gatesOutAdataArray[dataStep], BPM*2);
  }
  if(advance) dataStep++;
  
  int gateOutNum = random(8);
  if(gateOutNum == 0){
    VCC.WriteGatesB(B10000000, BPM*2);
  }else if(gateOutNum == 1){
    VCC.WriteGatesB(B01000000, BPM*2);
  }else if(gateOutNum == 2){
    VCC.WriteGatesB(B00100000, BPM*2);
  }else if(gateOutNum == 3){
    VCC.WriteGatesB(B00010000, BPM*2);
  }else if(gateOutNum == 4){
    VCC.WriteGatesB(B00001000, BPM*2);
  }else if(gateOutNum == 5){
    VCC.WriteGatesB(B00000100, BPM*2);
  }else if(gateOutNum == 6){
    VCC.WriteGatesB(B00000010, BPM*2);
  }else if(gateOutNum == 7){
    VCC.WriteGatesB(B00000001, BPM*2);
  }else if(gateOutNum == 8){
    VCC.WriteGatesB(B10000000, BPM*2);
  }
}
