//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector> 
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include ADDAC COMPARATOR CLASS
#include <ADDAC_Comparator.h>
//include Gate Delay Class
#include <ADDAC_GateDelay.h>

//initialize ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Comparator compR, compF;
ADDAC_GateDelay gateDelay;


//#define DEBUG   // Comment this line if you are not debugging

void setup()
{
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

     
      if(compR.calc(RISE,VCC.ReadCv(A,0),0.5)){
        gateDelay.GateDelayRise();     
      }
      else if(compR.calc(FALL,VCC.ReadCv(A,0),0.5)){

        gateDelay.GateDelayFall();
      }
    
      if(gateDelay.update(VCC.ReadCv(A,1)*5000.0)){
        VCC.WriteGatesStraight(A, 0, gateDelay.state);
      }
    }
  }

#ifdef DEBUG
  Serial.print(gateDelay.state); 
  Serial.println();
  delay(10);
#endif

}
