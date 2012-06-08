#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC.h>
ADDAC VCC; 

//#define DEBUG       // Just comment this line if you are not debugging

// CONSTANT FOR MAXIMUM RESOLUTION RANGE - NOT RECOMMENDED TO CHANGE - !!
//#define addacMaxResolution 65535 

void setup(){
  VCC.setup();
}

void loop(){
  VCC.update(); 

  if(VCC.MODE==0){ 
    if(VCC.SUBMODE==0){ 
          //program to preset in MODE “0”, SUBMODE “0”.
          // If their is signal in Gate 1, generate a random voltage in  output 2
     if(VCC.ReadGate(A,false,1)==1){
     VCC.WriteChannel(2,random(1023)/1023.0f*addacMaxResolution);

    }
     }

 #ifdef DEBUG
    Serial.println();
    delay(10);
  #endif
}
