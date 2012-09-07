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

  if(VCC.MODE==0){ 
    if(VCC.SUBMODE==0){ 
      //program to preset in MODE “0”, SUBMODE “0”
      //YOUR CODE HERE
    }
    else if(VCC.SUBMODE==1){ 
      //program to preset in MODE “0”, SUBMODE “1”
      //YOUR CODE HERE
    }
  }
  else if(VCC.MODE==5){ 
    if(VCC.SUBMODE==0){ 
      //program to preset in MODE “5”, SUBMODE “0”
      //YOUR CODE HERE
    }
    else if(VCC.SUBMODE==15){ 
      //program to preset in MODE “5”, SUBMODE “15”
      //YOUR CODE HERE
    }

  }
}


