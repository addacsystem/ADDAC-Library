//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

#include <ADDAC.h>
#include <ADDAC_Env.h>
#include <ADDAC_Comparator.h>

ADDAC VCC;
ADDAC_Env ENV1, ENV2;
ADDAC_Comparator  COMP1, COMP2;

boolean envTrigger;

// DEBUGGING CONSOLE
//#define DEBUG 

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

      boolean addPointTrigger = COMP1.calc(RISE,VCC.ReadManual(A,0),0.5);
      envTrigger = COMP2.calc(RISE,VCC.ReadManual(A,1),0.5);        

      if(addPointTrigger){

        ENV1.addPoint(VCC.ReadCv(A,0),VCC.ReadCv(A,1));
        ENV2.addPoint(VCC.ReadCv(A,0),VCC.ReadCv(A,1));
      }

       ENV1.MultiEnv(envTrigger,false);
      VCC.WriteChannel(1,ENV1.CVstream);   
      ENV2.MultiEnvLoop(envTrigger,false);
      VCC.WriteChannel(1,ENV2.CVstream);   
    }

    else if(VCC.SUBMODE==1){ 

    }
  }

#ifdef DEBUG
  ENV1.PrintMultiEnv();
  Serial.print("  :");
  Serial.print(ENV1.CVstream);
  Serial.println();
  delay(10);
#endif
}
