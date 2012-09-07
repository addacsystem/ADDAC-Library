//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC class
#include <ADDAC.h>

//Initialize and name the ADDAC class
ADDAC VCC; 

#define DEBUG       // Just comment this line if you are not debugging

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
      /*Read all Gates ins from socket A. switch false to true to invert signal.
       Print all gates in Arduino monitor log.*/
      VCC.ReadGates(A,false);
      VCC.PrintGates(A); 
    }
    else if(VCC.SUBMODE==1){ 
      //program to preset in MODE “0”, SUBMODE “1”.
      //Read Gate 1 input from socket and inver the signal print it in the arduino monitor log
      VCC.ReadGate(A,1,true);
      VCC.PrintGate(A,1); 

    }
  }

#ifdef DEBUG
  Serial.println();
  delay(10);
#endif
}


