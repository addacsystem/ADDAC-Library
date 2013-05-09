//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
ADDAC VCC; 

#include <ADDAC_Comparator.h>

#include <ADDAC_AD.h>
ADDAC_AD ad; 

boolean gate;

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

  if(VCC.ReadCv(A,0)>0.5){

    gate=true;
  }
  else{

    gate =false;
  }


  ad.updateLogExpMode(gate,1,700,0.7,900,0.3);
  //ad.updateLin(gate,700,700);


  VCC.WriteChannel(0,ad.CVstream);



#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}




