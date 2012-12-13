//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
ADDAC VCC; 

//#define DEBUG   // Comment this line if you are not debugging

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

    if (VCC.SUBMODE==0){

    }
  }

#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}


