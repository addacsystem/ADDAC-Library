//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
#include <ADDAC_AD.h>
#include <ADDAC_Comparator.h>
ADDAC VCC; 
ADDAC_AD AD1;
ADDAC_Comparator CP1, CP2;

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

    if (VCC.SUBMODE==0){

      AD1.update(1000,5000);
      
      if(CP1.calc(RISE,VCC.ReadCv(A,5),0.5)){
       
        AD1.trigger();
       // AD1.AD_release();
        
      }
      
       if(CP2.calc(RISE,VCC.ReadCv(A,4),0.5)){
         AD1.release();
       }
       VCC.WriteChannel(0,AD1.CVstream);
    }
  }

#ifdef DEBUG
Serial.print(AD1.CVstream);
  Serial.println();
  delay(10);
#endif

}


