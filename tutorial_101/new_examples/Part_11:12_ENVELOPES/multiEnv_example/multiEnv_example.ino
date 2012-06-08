#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC.h>
#include <ADDAC_Env.h>
#include <ADDAC_Comparator.h>


//using namespace std;
// <iostream> declares cout/cerr, but the application must define them
// because it's up to you what to do with them.

ADDAC VCC;
ADDAC_Env ENV1, ENV2;
ADDAC_Comparator  COMP1, COMP2;

boolean envTrigger;

// DEBUGGING CONSOLE
//#define DEBUG 


#define addacMaxResolution 65535  // CONSTANT FOR MAXIMUM RESOLUTION RANGE - NOT RECOMMENDED TO CHANGE - !!



void setup()
{
  VCC.setup();
#ifdef DEBUG
  Serial.begin(115200);
#endif

}

void loop(){
  VCC.update();


  if(VCC.MODE==0){  //  MODE 0 has several test/debug functions for the available functions and modules
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 0 -

    //
    if(VCC.SUBMODE==0){

      boolean addPointTrigger = COMP1.Comparator(VCC.ReadManual(A,0),0.5);
      envTrigger = COMP2.Comparator(VCC.ReadManual(A,1),0.5);        


      if(addPointTrigger){

        ENV1.addPoint(VCC.ReadCv(A,0),VCC.ReadCv(A,1));
        ENV2.addPoint(VCC.ReadCv(A,0),VCC.ReadCv(A,1));      

      }

      ENV1.MultiEnvLoop(envTrigger,false); 
      ENV2.MultiEnvLoop(envTrigger,false); 

      VCC.WriteChannel(1,ENV1.CVstream); 
      VCC.WriteChannel(2,ENV2.CVstream);     

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












