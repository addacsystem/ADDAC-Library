//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

#include <ADDAC.h>
#include <ADDAC_Adsr.h>


ADDAC VCC;
ADDAC_Adsr adsr1, adsr2, adsr3;


// DEBUGGING CONSOLE
//#define DEBUG 


void setup(){

  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  
  VCC.setup();
}

void loop(){  
  VCC.update();
  
  if(VCC.MODE==0){ 
    
    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){
      //bool _trigger, bool _inverted, float _Atime, float _D, float _Dtime,float _Stime, float _Rtime
      //attack will be tha max, 1 and Decay amplititude is set by user.
     adsr1.update(true,false,2000,VCC.ReadCv(A,0),2000,2000,2000); 
     
     //bool _trigger, bool _inverted, float _A, float _Atime, float _D, float _Dtime,float _Stime, float _Rtime
     //attack will be tha max, 1.
     adsr2.update(true,false,0.5,2000,0.25,2000,2000,200);
    
     //log and exo mode
     adsr3.updateLogExpMode(true, false, 1, 2000, 0.9, 0.3, 500, 0.2, 0.2, 200, 0, 2000, 0.2); 
     
     //Stream the env1 envelope to Output channel 0
     VCC.WriteChannel(0,adsr1.CVstream);
     
      //Stream the env2 envelope to Output channel 1
     VCC.WriteChannel(1,adsr2.CVstream);
     
     //Stream the env3 envelope to Output channel 2
     VCC.WriteChannel(2,adsr3.CVstream);
     
    }
    else if(VCC.SUBMODE==1){ 

    }
  }

#ifdef DEBUG
  Serial.print("adsr1 | ");
  Serial.print(adsr1.CVstream);
  Serial.print(" | adsr2 | ");
  Serial.print(adsr2.CVstream);
  Serial.print(" | adsr3 | ");
  Serial.print(adsr3.CVstream);
  Serial.println();
  delay(10);
#endif


}
