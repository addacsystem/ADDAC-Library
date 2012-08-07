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


// DEBUGGING CONSOLE
//#define DEBUG // Just comment this line if you are not using debug 

// INCLUDES THE MAIN ADDAC LIBRARY

// THEN INITIALIZES LIBRARY CLASS
ADDAC VCC; // From now on the class will be called "VCC"
ADDAC_Random Rnd, Rnd2;
ADDAC_Quantizer Quant;
ADDAC_Lin2Log L2G;
ADDAC_Comparator Comp,Comp2,Comp3;
ADDAC_Euclidean Euclides(4);

void setup(){
  VCC.setup();
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
}

void loop(){
  VCC.update(); // NEED TO UPDATE THE VCC!
  //VCC.ReadCvs(A);
  

  //WORKING MODE
  // ------------------------------------------------------------------------------------------------------------------------ MODE 0 
  if(VCC.MODE==0){  

    //WORKING SUBMODE-------------------------------------------------------------------------------------------------------- SUBMODE 0
    //if MODE == 0 and SUBMODE == 0, send a ramdom voltage to all cv outputs 
    if(VCC.SUBMODE==0){      
      for(int i=0;i<6;i++){
        //alterar (i-1).....................................................
        VCC.WriteChannel(i, VCC.ReadCv(A,i));
        VCC.PrintCv(A,i);

      }
    
   
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 1
    //if MODE == 0 and SUBMODE == 1, Read CVAinput1 and controll voltage with it to cv output1 
    }else if(VCC.SUBMODE==1){ 
      VCC.ReadManuals(A);
      Rnd.setBrownianRandom(false);
      
      int Pulse = Comp.Comparator(0,VCC.ReadCv(A,2),0.75f);
      
      Rnd.update(Pulse,
        VCC.manualValuesA[1],VCC.manualValuesA[0],
        VCC.manualValuesA[3]*10000,VCC.manualValuesA[2]*10000, L2G.calc(VCC.manualValuesA[4]));

      VCC.WriteChannel(0, Rnd.CVstream);
      VCC.WriteChannel(3, Rnd.ClockOut);
      
      VCC.WriteChannel(4, Quant.quantize(Rnd.CVstream));
      VCC.WriteChannel(5, Rnd.GateOut);
      
      
      Rnd2.update(Pulse, 
          VCC.manualValuesA[1],VCC.manualValuesA[0],
        VCC.manualValuesA[3]*10000,VCC.manualValuesA[2]*10000, L2G.calc(VCC.manualValuesA[4]));
      
      VCC.WriteChannel(1, Rnd2.CVstream);
      VCC.WriteChannel(6, Quant.quantize(Rnd2.CVstream));
      VCC.WriteChannel(7, Rnd2.GateOut);
      
      Serial.print(Rnd.CVstream);
      
      /*VCC.PrintManual(A,0);
      VCC.PrintManual(A,1);
      VCC.PrintManual(A,2);
      VCC.PrintManual(A,3);
      VCC.PrintManual(A,4);*/
    
  


  }else if(VCC.SUBMODE==2){ 
    
      int Pulse = Comp.Comparator(0,VCC.ReadCv(A,2),0.75f);
      
      Euclides.update(Pulse,VCC.ReadCv(A,0),VCC.ReadCv(A,1),VCC.ReadCv(A,3));
      for(int i=0; i<4; i++){
        VCC.WriteChannel(i, Euclides.GateStream[i]);
      } 
      
      VCC.ReadManuals(A);
      Rnd.update( Comp2.Comparator(0,Euclides.GateStream[0],0.5), 
        VCC.manualValuesA[1],VCC.manualValuesA[0],
        VCC.manualValuesA[3]*10000,VCC.manualValuesA[2]*10000,0);
    
      Rnd2.update( Comp3.Comparator(0,Euclides.GateStream[1],0.5), 
        VCC.manualValuesA[1],VCC.manualValuesA[0],
        VCC.manualValuesA[3]*10000,VCC.manualValuesA[2]*10000,0);
      
      VCC.WriteChannel(4, Quant.quantize(Rnd.CVstream));
      //VCC.WriteChannel(5, Rnd.GateOut);
      VCC.WriteChannel(5, Euclides.GateStream[0]);
      VCC.WriteChannel(6, Quant.quantize(Rnd2.CVstream));
      VCC.WriteChannel(7, Euclides.GateStream[1]);
    }
  }
  
    #ifdef DEBUG
      Serial.println();
      delay(60);
    #endif

}





