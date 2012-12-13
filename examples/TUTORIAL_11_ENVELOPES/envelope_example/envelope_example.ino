//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC Main class
#include <ADDAC.h>

//include ADDAC_Env class
#include <ADDAC_Env.h>

//Initialize and name the ADDAC class
ADDAC VCC;

/*Initialize and name the ADDAC_Env.
 As we'll use 2 envelopes in this example, 
 let's name them env1 and env2
 */
ADDAC_Env env1, env2;

#define DEBUG   // Just comment this line if you are not debugging

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
  //update VCC
  VCC.update();

  if(VCC.MODE==0){  

    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){
      //bool _trigger, bool _inverted, float _Atime, float _D, float _Dtime,float _Stime, float _Rtime
      //attack will be tha max, 1 and Decay amplititude is set by user.
      env1.update(true,false,0.5,2000,0.25,2000,0.1,2000,2000); 


      //log and exo mode
      env2.updateLogExpMode(true, false, 1, 2000, 0.9, 0.3, 500, 0.2, 0.2, 200, 0, 2000, 0.2); 

      //Stream the env1 envelope to Output channel 0
      VCC.WriteChannel(0,env1.CVstream);

      //Stream the env2 envelope to Output channel 1
      VCC.WriteChannel(1,env2.CVstream);
    }

  }

#ifdef DEBUG
  Serial.print("env1 | ");
  Serial.print(env1.CVstream);
  Serial.print(" | env2 | ");
  Serial.print(env2.CVstream);
  Serial.println();
  delay(10);
#endif


}


