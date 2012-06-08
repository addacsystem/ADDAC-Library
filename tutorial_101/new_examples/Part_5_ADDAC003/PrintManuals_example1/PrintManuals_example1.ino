#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC.h>

ADDAC VCC; 

#define DEBUG       // Just comment this line if you are not debugging

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
          //Read all POTS from ADDAC 003 in socket A
         VCC.ReadManuals(A);
           //Print the POTS valls from socket A in the monitor log
     VCC.PrintManuals(A);
    }
      else if(VCC.SUBMODE==1){ 
             //program to preset in MODE “0”, SUBMODE “1”.
             //Read POT 1 from CV in socket B
          VCC.ReadManual(B,1);
            //Print POT val from socket B in the monitor log
      VCC.PrintManual(B,1);
      }
        }
 #ifdef DEBUG
    Serial.println();
    delay(10);
  #endif
}
