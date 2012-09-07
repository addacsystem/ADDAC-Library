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
      //Read all POTS from ADDAC 003 in socket A
      VCC.ReadManuals(A);
      //Print the POTS valls from socket A in the monitor log
      VCC.PrintManuals(A);
    }
    else if(VCC.SUBMODE==1){ 
      //program to preset in MODE “0”, SUBMODE “1”.
      //Read POT 1 from CV in socket B
      //Print POT val from socket B in the monitor log
      VCC.PrintManual(B,1);
    }
  }
#ifdef DEBUG
  Serial.println();
  delay(10);
#endif
}


