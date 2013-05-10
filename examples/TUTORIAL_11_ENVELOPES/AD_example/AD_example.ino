//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
ADDAC VCC; 

#include <ADDAC_Comparator.h>
ADDAC_Comparator cp, cp1;

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
  
  
  

  //SHAPE AD WITH GATE
  if(VCC.MODE==0){

    ad.updateLogExpMode(gate,1,700,0.7,900,0.3);
  }

  //SHAPE AD WITHOU GATE
  else if(VCC.MODE==1){

    //TRIGGER OR REALEASE GATE WITH COMPARATORS
    if(cp.calc(RISE,VCC.ReadCv(A,0),0.5))ad.trigger();
    else if(cp1.calc(RISE,VCC.ReadCv(A,1),0.5))ad.release();

    ad.updateLogExpMode(1,700,0.7,900,0.3);
  }

  //LINEAR AD WITH GATE
  else if(VCC.MODE==2){

    ad.updateLin(gate,700,700);
  }



  VCC.WriteChannel(0,ad.CVstream);



#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}






