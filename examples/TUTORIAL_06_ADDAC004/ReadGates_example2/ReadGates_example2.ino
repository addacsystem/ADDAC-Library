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

  if(VCC.MODE==0){ 
    if(VCC.SUBMODE==0){ 
      //program to preset in MODE “0”, SUBMODE “0”.
      // If their is signal in Gate 1, generate a random voltage in  output 1
      if(VCC.ReadGate(A,1,false)==1){
        VCC.WriteChannel(2,random(1023)/1023.0f);

      }
    }

  }
#ifdef DEBUG
  Serial.println();
  delay(10);
#endif
}


