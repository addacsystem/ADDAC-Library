#include <ADDAC.h>
#include <ADDAC_Adsr.h>
#include <ADDAC_Env.h>

ADDAC VCC;
ADDAC_Adsr ADSR1;
ADDAC_Env ENV1, ENV2;



// DEBUGGING CONSOLE
#define DEBUG 


#define addacMaxResolution 65535  // CONSTANT FOR MAXIMUM RESOLUTION RANGE - NOT RECOMMENDED TO CHANGE - !!


boolean adsrTrigger1=false;
int inverse=1;

void setup(){
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


    ENV1.envMode(true,false,0.8,2000,0.4,2000,0.2,4000,200);
ADSR1.adsrMode(true,false,200,0.4,200,400,200);
VCC.WriteChannel(0,ENV1.CVstream*addacMaxResolution);
VCC.WriteChannel(1,ADSR1.CVstream*addacMaxResolution);

      
      
#ifdef DEBUG
Serial.print("adsr - ");
Serial.print(ENV1.CVstream);
//Serial.print("cvstream - ");
//Serial.print(LFO1.CVstream);
//Serial.print("  |  stream - ");
//Serial.print(LFO1.stream);
#endif

      // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 1 -

    }
    else if(VCC.SUBMODE==1){ 


    }




#ifdef DEBUG
    Serial.println();
    delay(10);
#endif

  }
}

