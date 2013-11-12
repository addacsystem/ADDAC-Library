//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////

#include <ADDAC.h>
#include <ADDAC_Probabilistic.h>
#include <ADDAC_Comparator.h>
#include <ADDAC_Quantizer.h>
#include <ADDAC_Timer.h>

ADDAC VCC;
ADDAC_Probabilistic prb; 
ADDAC_Comparator cp, cp1; 
ADDAC_Quantizer qt;
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
  //update VCC class
  VCC.update();
  
  //update Probabilistic class with the following parameters - (A%, B%, C%, D%, OFFSET).
  prb.update(VCC.ReadCv(A,0), VCC.ReadCv(A,1), VCC.ReadCv(A,3), VCC.ReadCv(A,4),0);

      //Switch between glideOn/glideOff with a comparator.
      // boolean glideCP = cp1.calc(RISE,VCC.ReadManual(A,0),0.5);
      // if(glideCP) prb.switchGlide();

      //Turn On Glide.
      prb.setGlide(true); //Turn Off - prb.setGlide(false); 

      //Create a timer and store his resut. 
      boolean timer = tm.set(VCC.ReadCv(A,5)*1000);      
      //If timer is true, calculate the next value.
      if(timer) prb.calc();

      //Write gate 1 on outPut 0
      VCC.WriteChannel(0, prb.out1);
      //Write gate 2 on outPut 1
      VCC.WriteChannel(1, prb.out2);
      //Write gate 3 on outPut 2
      VCC.WriteChannel(2, prb.out3);
      //Write gate 4 on outPut 3
      VCC.WriteChannel(3, prb.out4);
      //Write gate 5 on outPut 4
      VCC.WriteChannel(4, prb.out5);

      //write CVout on outPut 5
      VCC.WriteChannel(5, prb.CVstream);
       //write CVout quantized on outPut 5
      VCC.WriteChannel(6, qt.calc(prb.CVstream));


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



