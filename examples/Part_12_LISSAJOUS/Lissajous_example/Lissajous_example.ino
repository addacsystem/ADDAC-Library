//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include LISSAJOUS class
#include <ADDAC_Liss.h>


//initiate ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Liss liss1;

// DEBUGGING CONSOLE
#define DEBUG 

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

    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){

      /*calculate lissajous courve with the following parameters:
      float amp, float _speedx, float _speedy, bool _mirror*/
      liss1.calc(VCC.ReadCv(A,0),0.9,0.9,true);
      
      //write the x position in channel 0
      VCC.WriteChannel(0,liss1.x);
      //write y position in channel 1
      VCC.WriteChannel(1,liss1.y);

    }

  }


#ifdef DEBUG
  Serial.print(liss1.x);
  Serial.println();
  delay(10);
#endif

}
















