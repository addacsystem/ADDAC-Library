//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include ADDAC SMOOTH LIBRARY
#include <ADDAC_Smooth.h>

//initiate ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Smooth SM;

// DEBUGGING CONSOLE
#define DEBUG 

//variable for the smooth value
float smoothValue;

void setup(){
  VCC.setup(); 
#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void loop(){
  VCC.update();

  if (VCC.MODE==0){

    if (VCC.SUBMODE==0){
      //Smooth a random value between 0-1 with a smooth factor of 0.99
      smoothValue=SM.Smooth(random(2),0.99);
      
      //Write the smoothed value in OUTPUT 0
      VCC.WriteChannel(0,smoothValue);    

    }
  }

#ifdef DEBUG
  Serial.print(smoothValue);
  Serial.println();
  delay(10);
#endif

}


