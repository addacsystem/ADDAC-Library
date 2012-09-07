//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC class
#include <ADDAC.h>

//Initialize and name the ADDAC class
ADDAC VCC; 

void setup(){
  //setup all VCC main settings
  VCC.setup();

}

void loop(){
  //update VCC
  VCC.update(); 

}


