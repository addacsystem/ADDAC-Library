//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include ADDAC SMOOTH LIBRARY
#include <ADDAC_Smooth.h>

//initialize ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Smooth SM;

//variable for the smooth value
float smoothValue;

#define DEBUG   // Comment this line if you are not debugging

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
  VCC.update();

  if (VCC.MODE==0){
    //Working on MODE “0”, SUBMODE “0”.
    if (VCC.SUBMODE==0){
      //Smooth the value from CvPot "0" with a smooth factor of 0.99
      smoothValue=SM.calc(VCC.ReadCv(A,0),0.99);

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
