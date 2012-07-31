//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>

//initiate ADDAC CLASS and name them
ADDAC VCC;


// DEBUGGING CONSOLE
//#define DEBUG 


void setup()
{
  VCC.setup();
#ifdef DEBUG
  Serial.begin(115200);
#endif

}

void loop(){
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

