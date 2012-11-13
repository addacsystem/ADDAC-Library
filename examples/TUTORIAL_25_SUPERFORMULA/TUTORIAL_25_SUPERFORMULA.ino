//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
#include <ADDAC_SuperFormula.h>
#include <ADDAC_Quantizer.h>
#include <ADDAC_Smooth.h>

ADDAC VCC; 
ADDAC_SuperFormula sf;
ADDAC_Smooth sm;
ADDAC_Quantizer qt;

//#define DEBUG   // Comment this line if you are not debugging

void setup(){
  //setup all VCC main settings
  VCC.setup();
  ADDAC_SuperFormula();
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
      sf.superformula(VCC.ReadCv(A,1),VCC.ReadCv(A,3),VCC.ReadCv(A,4),VCC.ReadCv(A,5)*5000);
      //sf.superformula(500,100,100,VCC.ReadCv(A,5)*50000);
      
      sf.setPingPongMode(false);
      // sf.setLoopMin(VCC.ReadCv(A,3)*360);
      // sf.setLoopMax(VCC.ReadCv(A,4)*360);

     // VCC.WriteChannel(3,sm.calc(qt.calc(sf.getX()),0.95));
      //VCC.WriteChannel(4,sm.calc(sf.getX(),0.90));
     // VCC.WriteChannel(5,qt.calc(sf.getX()));
      VCC.WriteChannel(6,sf.getX());
      VCC.WriteChannel(7,sf.getY());
  
    }
  }

#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}



