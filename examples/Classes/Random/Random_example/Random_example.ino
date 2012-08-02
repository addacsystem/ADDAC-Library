#include <ADDAC.h>

#include <ADDAC_Random.h>
#include <ADDAC_Quantizer.h>
#include <ADDAC_Lin2Log.h>


// DEBUGGING CONSOLE
//#define DEBUG // Just comment this line if you are not using debug 

// INCLUDES THE MAIN ADDAC LIBRARY

// THEN INITIALIZES LIBRARY CLASS
ADDAC VCC; // From now on the class will be called "VCC"
ADDAC_Random Rnd, Rnd2;
ADDAC_Quantizer Quant;
ADDAC_Lin2Log L2G;

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
    }
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 1
    //if MODE == 0 and SUBMODE == 1, Read CVAinput1 and controll voltage with it to cv output1 
    else if(VCC.SUBMODE==1){ 
      Rnd.setBrownianRandom(false);
      Rnd.Random(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,L2G.calc(VCC.ReadCv(A,5)));
      Rnd2.Random(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,L2G.calc(VCC.ReadCv(A,5)));
      VCC.WriteChannel(0, VCC.ReadCv(A,0));
      VCC.WriteChannel(1, Rnd.CVstream);//(A,0)/1023.0f*addacMaxResolution);
      VCC.WriteChannel(2, Quant.quantize(Rnd.CVstream));
      VCC.WriteChannel(3, Rnd.ClockOut);
      VCC.WriteChannel(4, Rnd.GateOut);
      
      VCC.WriteChannel(6, Rnd2.CVstream);//(A,0)/1023.0f*addacMaxResolution);
      VCC.WriteChannel(7, Quant.quantize(Rnd2.CVstream));
      
      //Serial.print(Rnd.CVstream);
    }
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 1
    //if MODE == 0 and SUBMODE == 1, Read CVAinput1 and controll voltage with it to cv output1 
    else if(VCC.SUBMODE==2){ 
      Rnd.setBrownianRandom(true);
      Rnd.Random(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));
      Rnd2.Random(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));
      VCC.WriteChannel(0, VCC.ReadCv(A,0));
      VCC.WriteChannel(1, Rnd.CVstream);//(A,0)/1023.0f*addacMaxResolution);
      VCC.WriteChannel(2, Quant.quantize(Rnd.CVstream));
      VCC.WriteChannel(3, Rnd2.CVstream);//(A,0)/1023.0f*addacMaxResolution);
      VCC.WriteChannel(4, Quant.quantize(Rnd2.CVstream));
      
      //Serial.print(Rnd.CVstream);
    }
  }
  
    #ifdef DEBUG
      //Serial.println();
      delay(60);
    #endif

}





