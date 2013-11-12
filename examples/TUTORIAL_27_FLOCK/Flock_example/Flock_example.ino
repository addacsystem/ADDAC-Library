//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
#include <ADDAC_Flock.h>
ADDAC VCC; 
ADDAC_Flock fl;



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
  fl.update(false);
  
  fl.setCohesion(500);
  fl.setAlign(50);
  fl.setSeparation(VCC.ReadCv(A,4)*1000);
  fl.setSpeed(VCC.ReadCv(A,5));

  VCC.WriteChannel(0,fl.getBoidPositionA(0));
  VCC.WriteChannel(1,fl.getBoidPositionA(1));
  VCC.WriteChannel(2,fl.getBoidPositionA(2));
  VCC.WriteChannel(3,fl.getBoidPositionA(3));


#ifdef DEBUG

//    Serial.print("boid1: " );
//    Serial.print(fl.getBoidPositionX(0));
//    Serial.print(" | ");
//    Serial.print(fl.getBoidPositionY(0));
//  //  
//    Serial.print("   boid2: " );
//    Serial.print(fl.getBoidPositionX(1));
//    Serial.print(" | ");
//    Serial.print(fl.getBoidPositionY(1));
//  //  
//    Serial.print("  boid3: " );
//    Serial.print(fl.getBoidPositionX(2));
//    Serial.print(" | ");
//    Serial.print(fl.getBoidPositionY(2));
//  //  
//    Serial.print("   boid4: " );
//    Serial.print(fl.getBoidPositionX(3));
//    Serial.print(" | ");
//    Serial.print(fl.getBoidPositionY(3));


  Serial.print("boid1: " );
  Serial.print(fl.getBoidPositionA(0));

  Serial.print("  boid2: " );
  Serial.print(fl.getBoidPositionA(1));

  Serial.print("  boid3: " );
  Serial.print(fl.getBoidPositionA(2));

  Serial.print("  boid4: " );
  Serial.print(fl.getBoidPositionA(3));

  Serial.println();
  delay(10);
#endif

}





