#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC.h>

ADDAC VCC; 

//#define DEBUG       // Just comment this line if you are not debugging

void setup(){
  VCC.setup();

#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void loop(){
  VCC.update(); 

  if(VCC.MODE==0){ 
    if(VCC.SUBMODE==0){ 
      //program to preset in MODE “0”, SUBMODE “0”.
      // If their is signal in Gate 1, generate a random voltage in  output 1
      if(VCC.ReadGate(A,1,false)==1){
        VCC.WriteChannel(2,random(1023)/1023.0f);

      }
    }

  }
#ifdef DEBUG
  Serial.println();
  delay(10);
#endif
}

