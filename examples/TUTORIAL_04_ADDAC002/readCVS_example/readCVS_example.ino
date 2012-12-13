//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////

//include ADDAC class
#include <ADDAC.h>

//Initialize and name the ADDAC class
ADDAC VCC; 

#define DEBUG    // Just comment this line if you are not debugging

void setup(){
  //setup all VCC main settings
  VCC.setup();

//debug settings
#ifdef DEBUG
  //serial speed communication 
  Serial.begin(115200);
#endif

}

void loop(){
  //update VCC
  VCC.update(); 

  if(VCC.MODE==0){ 
    if(VCC.SUBMODE==0){ 
      //Stores preset in MODE “0”, SUBMODE “0”.
      //Read all POTS from CV in socket A
      VCC.ReadCvs(A);
    }
    else if(VCC.SUBMODE==1){ 
      //Stores preset in MODE “0”, SUBMODE “1”.
      //Read POT 1 from CV in socket B
      VCC.ReadCv(B,1);
      
    }
  }
#ifdef DEBUG
  if(VCC.SUBMODE==0){
    Serial.print("A: ");
    //Print the POTS values from socket A in the monitor log
    VCC.PrintCvs(A);
  }
  else if(VCC.SUBMODE==1){
    //Print POT value from socket B in the monitor log
    Serial.print(" | B1: ");
    VCC.PrintCv(B,1);
  }
  Serial.println();
  delay(10);
#endif

}
