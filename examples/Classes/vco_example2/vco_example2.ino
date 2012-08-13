//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////


#include <ADDAC.h>

#include <ADDAC_Random.h>
#include <ADDAC_Quantizer.h>
#include <ADDAC_Lin2Log.h>
#include <ADDAC_Comparator.h>
#include <ADDAC_Euclidean.h>
#include <ADDAC_Ntof.h>
#include <ADDAC_VCO.h>



// INCLUDES THE MAIN ADDAC LIBRARY

// THEN INITIALIZES LIBRARY CLASS
ADDAC VCC; // From now on the class will be called "VCC"
ADDAC_Random Rnd, Rnd2;
ADDAC_Quantizer Quant;
ADDAC_Lin2Log L2G;
ADDAC_Comparator Comp,Comp2,Comp3;
ADDAC_Euclidean Euclides(4);  
ADDAC_Ntof ntof;
//ADDAC_VCO vco(0,0,0);


float tri;
float interval = 25;
float inc = 0.01f;

boolean UP=true;
unsigned long time =0;

void setup(){
  // initialize VCO 
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

      VCC.ReadCvs(A);
      //VCC.PrintCvs(A);
      
      int RndClock = Comp.calc(0,VCC.ReadCv(A,2),0.75f);
      
      Rnd.update(//RndClock,
        VCC.cvValuesA[1],VCC.cvValuesA[0],
        VCC.cvValuesA[3]*10000,VCC.cvValuesA[2]*10000, VCC.cvValuesA[4]);
      
    Serial.print("  pot:");
    Serial.print(VCC.cvValuesA[0]);
    Serial.print("  quantized:");
    Serial.print(Quant.calc(VCC.cvValuesA[0]));
    
      VCO.update(Quant.calc(Rnd.CVstream), VCC.cvValuesA[5]);
      //VCO.update(Rnd.CVstream,VCC.cvValuesA[5]);
      //VCO.update(VCC.cvValuesA[0],VCC.cvValuesA[5]);
  
  

    #ifdef DEBUG
      Serial.println();
      delay(60);
    #endif

}





