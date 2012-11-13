//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
#include <ADDAC_Quad.h>

ADDAC VCC;

ADDAC_Quad quad;

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
            
      quad.calc(0, VCC.ReadCv(A,0), VCC.ReadCv(A,5), VCC.ReadCv(A,3), VCC.ReadCv(A,4), VCC.ReadCv(A,1));
      
      VCC.WriteChannel(0,quad.amp1);
      VCC.WriteChannel(1,quad.amp2);
      VCC.WriteChannel(2,quad.amp3);
      VCC.WriteChannel(3,quad.amp4);

    }
  }

#ifdef DEBUG
  Serial.print("x: ");
  Serial.print(quad.x);
    Serial.print(" y: ");
  Serial.print(quad.y);
  Serial.print("     amp1: ");
  Serial.print(quad.amp1);
    Serial.print(" amp2: ");
  Serial.print(quad.amp2);
    Serial.print(" amp3: ");
  Serial.print(quad.amp3);
    Serial.print(" amp4: ");
  Serial.print(quad.amp4);
  Serial.println();
  delay(10);
#endif

}


