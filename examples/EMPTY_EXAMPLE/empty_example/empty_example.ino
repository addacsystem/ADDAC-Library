#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC.h>
ADDAC VCC; 

// DEBUGGING CONSOLE
//#define DEBUG 

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

    }
  }

#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}


