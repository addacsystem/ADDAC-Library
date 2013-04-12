//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
ADDAC VCC; 

#include <ADDAC_Comparator.h>
ADDAC_Comparator cp, cp1; 

#include <ADDAC_ADLogLin.h>
ADDAC_ADLogLin ad; 


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

  ad.updateLogExpMode(true,false,VCC.ReadCv(A,0),VCC.ReadCv(A,1)*5000,VCC.ReadCv(A,3),VCC.ReadCv(A,4)*5000,VCC.ReadCv(A,5));
  VCC.WriteChannel(0,ad.CVstream);

#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}



