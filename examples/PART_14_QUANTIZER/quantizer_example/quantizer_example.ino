//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include QUANTIZER class
#include <ADDAC_Quantizer.h>

//initiate ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Quantizer quant1;

float quantizedNote;

// DEBUGGING CONSOLE
#define DEBUG 

void setup(){
  VCC.setup();

#ifdef DEBUG
  Serial.begin(115200);
#endif

}

void loop(){
  VCC.update();


  if(VCC.MODE==0){

    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){

      //Quantize random voltages
      quantizedNote = quant1.quantize(random(1023)/1023.0f);

      //write random quantized voltage to channel outPut1
      VCC.WriteChannel(1, quantizedNote);
      delay(VCC.ReadCv(A,0)*1000);

    }

  }


#ifdef DEBUG
  Serial.print(quantizedNote);
  Serial.println();
  delay(10);
#endif

}



















