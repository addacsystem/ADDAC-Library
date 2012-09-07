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
      //program to preset in MODE “0”, SUBMODE “0”. Generate a random voltage in channel 1 and 3
      VCC.WriteChannel(1, random(1023)/1023.0f);
      VCC.WriteChannel(3, random(1023)/1023.0f);
    }
    else if(VCC.SUBMODE==1){ 
      /*program to preset in MODE “0”, SUBMODE “1”. Generate a random voltage in all 8 VCC channels, 
       instead of use 8 times the same function we can use a for loop 
       that will repeat the function 8 for all the CV OUTPUTS*/
      for(int i=0;i<8;i++){
        //Notice that  i  start with the value 0 and in each loop we increment it until it is minor than 8.
        VCC.WriteChannel(i, random(1023)/1023.0f);
      }
    }
  }

}



