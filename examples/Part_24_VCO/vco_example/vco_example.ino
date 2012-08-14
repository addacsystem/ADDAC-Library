//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>
////////////////////////////////////

// INCLUDES THE ADDAC MAIN LIBRARY
#include <ADDAC.h>
// INCLUDES THE ADDAC Random LIBRARY
#include <ADDAC_Random.h>
// INCLUDES THE ADDAC Quantizer LIBRARY
#include <ADDAC_Quantizer.h>
// INCLUDES THE ADDAC Comparator LIBRARY
#include <ADDAC_Comparator.h>
// INCLUDES THE ADDAC VCO LIBRARY
#include <ADDAC_VCO.h>

// THEN INITIALIZES AND NAME LIBRARY CLASS
ADDAC VCC; 
ADDAC_Random Rnd, Rnd2;
ADDAC_Quantizer Quant;
ADDAC_Comparator Comp,Comp2,Comp3;
//ADDAC_VCO vco(0,0,0);

//#define DEBUG  // Just comment this line if you are not debugging

float tri;
float interval = 25;
float inc = 0.01f;
boolean UP=true;
unsigned long time =0;

void setup(){
  //initialize VCO 
  VCO.initialize();         // initialize timer1, and set a 1/2 second period
  VCO.startup(VCO_update);  // attaches callback() as a timer overflow interrupt

  VCC.setup();

#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void VCO_update(){ // DO NOT OVERLOAD THIS FUNCTION!!!
  VCC.WriteChannel(0, UP* VCC.cvValuesA[5]+ ((1- VCC.cvValuesA[5])/2.0f));
  UP=!UP;
}


void loop(){
  VCC.update(); // NEED TO UPDATE THE VCC!

  if(VCC.MODE==0){

    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){
      VCC.ReadCvs(A);
      //VCC.PrintCvs(A);

      //update Random
      Rnd.update(VCC.cvValuesA[1], //Min Random value
      VCC.cvValuesA[0],            //Max Random value
      VCC.cvValuesA[3]*10000,      //Min Random frequency
      VCC.cvValuesA[2]*10000,      //Max Random frequency
      VCC.cvValuesA[4]);           //Smooth

      //update VCO: Volage, Volume
      VCO.update(Quant.calc(Rnd.CVstream), VCC.cvValuesA[5]);     

      //VCO.update(Rnd.CVstream,VCC.cvValuesA[5]);
      //VCO.update(VCC.cvValuesA[0],VCC.cvValuesA[5]);
    }
  }

#ifdef DEBUG
  Serial.println();
  delay(60);
#endif

}


