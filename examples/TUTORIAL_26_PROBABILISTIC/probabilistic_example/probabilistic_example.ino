//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
#include <ADDAC_Probabilistic.h>
#include <ADDAC_Comparator.h>
#include <ADDAC_Timer.h>

ADDAC VCC;
ADDAC_Probabilistic prb; 
ADDAC_Comparator cp, cp1; 
ADDAC_Timer tm;

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
  prb.update(VCC.ReadCv(A,0), VCC.ReadCv(A,1), VCC.ReadCv(A,3), VCC.ReadCv(A,4),0);

  if (VCC.MODE==0){

    if (VCC.SUBMODE==0){
      
     boolean randomizeCP = cp.calc(RISE,VCC.ReadCv(A,5),0.5);
     // boolean glideCP = cp1.calc(RISE,VCC.ReadManual(A,0),0.5);
     // if(glideCP) prb.switchGlide();
     prb.setGlide(true);
         
      //if(randomizeCP) prb.calc();
      if(tm.set(VCC.ReadCv(A,5)*1000)) prb.calc();
      
      //gate 1
      VCC.WriteChannel(0, prb.out1);
      //gate 2
      VCC.WriteChannel(1, prb.out2);
      //gate 3
      VCC.WriteChannel(2, prb.out3);
      //gate 4
      VCC.WriteChannel(3, prb.out4);
      //gate 5
      VCC.WriteChannel(4, prb.out5);
      
      //write CVout
      VCC.WriteChannel(5, prb.CVstream);
      
    }
    
    
  }

#ifdef DEBUG

  Serial.print("OUT 1 - ");
  Serial.print(prb.out1);
  Serial.print("  OUT 2 - ");
  Serial.print(prb.out2);
  Serial.print("  OUT 3 - ");
  Serial.print(prb.out3);
  Serial.print("  OUT 4 - ");
  Serial.print(prb.out4);
  Serial.print("  OUT 5 - ");
  Serial.print(prb.out5);
  
  Serial.print("  CVstream - ");
  Serial.print(prb.CVstream);
  
  Serial.println();
  delay(10);
#endif

}


