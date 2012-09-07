//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC class
#include <ADDAC.h>

//Initialize and name the ADDAC class
ADDAC VCC;

//#define DEBUG    // Just comment this line if you are not debugging

void setup(){
  //setup all VCC main settings
  VCC.setup();

  //DEBUG settings
#ifdef DEBUG
  //Serial speed communication
  Serial.begin(115200);
#endif
}

void loop(){
  //update VCC
  VCC.update(); 
 
  if (VCC.MODE==0){
  
    if (VCC.SUBMODE==0){
    
     // write randomly to all GATE OUTPUTS 
      for(int i=0; i<8;i++){
        //randomize values between 0 and <2 (0 or 1).
        VCC.WriteGatesStraight(A,i, int(random(2)));       
        //delay between writes
        delay(VCC.ReadManual(A,0)*500);
      }   
    }
  
  }
  #ifdef DEBUG
  Serial.println();
  delay(10);
  #endif
}

