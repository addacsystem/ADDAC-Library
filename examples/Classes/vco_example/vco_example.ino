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

//#include <TimerThree.h>
//#include <TimerFive.h>



int8_t ondestable[] = {
    127,134,141,148,155,162,169,176,183,189,195,201,207,212,
    217,222,227,231,234,238,241,244,246,248,250,251,252,253,
    253,254,253,253,252,251,250,248,246,244,242,240,238,235,
    233,230,227,225,222,219,216,214,211,208,206,203,201,199,
    196,194,192,190,189,187,185,184,183,181,180,179,178,178,
    177,176,176,175,175,174,174,174,173,173,173,173,172,172,
    172,171,171,171,170,170,169,169,168,168,167,166,166,165,
    164,163,162,161,160,159,158,157,156,155,153,152,151,150,
    148,147,146,144,143,142,140,139,137,136,135,133,132,131,
    129,128,127,125,124,122,121,120,118,117,116,114,113,111,
    110,109,107,106,105,103,102,101,100,98,97,96,95,94,93,92,
    91,90,89,88,87,87,86,85,85,84,84,83,83,82,82,82,81,81,81,
    80,80,80,80,79,79,79,78,78,77,77,76,75,75,74,73,72,70,69,
    68,66,64,63,61,59,57,54,52,50,47,45,42,39,37,34,31,28,26,
    23,20,18,15,13,11,9,7,5,3,2,1,0,0,0,0,0,1,2,3,5,7,9,12,15,
    19,22,26,31,36,41,46,52,58,64,70,77,84,91,98,105,112,119
  };
  
int8_t wav2[] = {
127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,
176,179,182,184,187,190,193,195,198,200,203,205,208,210,213,215,
217,219,221,224,226,228,229,231,233,235,236,238,239,241,242,244,
245,246,247,248,249,250,251,251,252,253,253,254,254,254,254,254,
255,254,254,254,254,254,253,253,252,251,251,250,249,248,247,246,
245,244,242,241,239,238,236,235,233,231,229,228,226,224,221,219,
217,215,213,210,208,205,203,200,198,195,193,190,187,184,182,179,
176,173,170,167,164,161,158,155,152,149,146,143,139,136,133,130,
127,124,121,118,115,111,108,105,102,99,96,93,90,87,84,81,
78,75,72,70,67,64,61,59,56,54,51,49,46,44,41,39,
37,35,33,30,28,26,25,23,21,19,18,16,15,13,12,10,
9,8,7,6,5,4,3,3,2,1,1,0,0,0,0,0,
0,0,0,0,0,0,1,1,2,3,3,4,5,6,7,8,
9,10,12,13,15,16,18,19,21,23,25,26,28,30,33,35,
37,39,41,44,46,49,51,54,56,59,61,64,67,70,72,75,
78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124};

float wav[] = {0.4,0.42,0.44,0.46,0.48,0.5,0.52,0.54,0.56,0.58,0.6,0.58,0.56,0.54,0.52,0.5,0.48,0.46,0.44,0.42};
int arr=0;


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

boolean UP=true,UP2=true;
unsigned long time =0;

void setup(){
  
  // initialize VCO 
  VCO.initialize();         // initialize timer1, and set a 1/2 second period
  //Timer5.initialize(1000); 
  VCO.startup(VCO_update);  // attaches callback() as a timer overflow interrupt
  //Timer5.attachInterrupt(timerCallback);
  
  VCC.setup();
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
}

void VCO_update(){ // DO NOT OVERLOAD THIS FUNCTION!!!
  //float vol = VCC.cvValuesA[5];
  VCC.WriteChannel(0, UP* VCC.cvValuesA[5]+ ((1- VCC.cvValuesA[5])/2.0f));
  UP=!UP;
}


void loop(){
  VCC.update(); // NEED TO UPDATE THE VCC!
 
  //WORKING MODE
  // ------------------------------------------------------------------------------------------------------------------------ MODE 0 
  if(VCC.MODE==4){  

      VCC.ReadCvs(A);
      //VCC.PrintCvs(A);
      //Rnd.setBrownianRandom(false);
      
      int RndClock = Comp.Comparator(0,VCC.ReadCv(A,2),0.75f);
      
      Rnd.update(//RndClock,
        VCC.cvValuesA[1],VCC.cvValuesA[0],
        VCC.cvValuesA[3]*10000,VCC.cvValuesA[2]*10000, VCC.cvValuesA[4]);
      
    Serial.print("  pot:");
    Serial.print(VCC.cvValuesA[0]);
    Serial.print("  quantized:");
    Serial.print(Quant.quantize(VCC.cvValuesA[0]));
    
      VCO.update(Quant.quantize(Rnd.CVstream),VCC.cvValuesA[5]);
      //VCO.update(Rnd.CVstream,VCC.cvValuesA[5]);
      //VCO.update(VCC.cvValuesA[0],VCC.cvValuesA[5]);
  
  
  }
    #ifdef DEBUG
      Serial.println();
      delay(60);
    #endif

}





