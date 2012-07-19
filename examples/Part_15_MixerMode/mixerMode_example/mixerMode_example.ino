//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>              
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include the LFO class in our project
#include <ADDAC_LFO.h>
//include ADSR class
#include <ADDAC_Adsr.h>
//include LISSAJOUS class
#include <ADDAC_ULTRALISS.h>


//initiate ADDAC CLASS's and name them
ADDAC VCC;
//initiate the LFO class and give it a name, in this case we will use two LFO’s, so we give a name to both, LFO1 and LFO2
ADDAC_LFO LFO1, LFO2;
//initiate the ADSR class and give it a name
ADDAC_Adsr adsr1;
//initiate the Lissajous class and give it a name
ADDAC_ULTRALISS liss1;


// DEBUGGING CONSOLE
//#define DEBUG  //Comment line when not debuging

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

      //Create six LFO's ans stream them in the first six Outputs
      for(int i=0;i<6;i++){
        LFO1.sinMode(false,  VCC.ReadCv(A,i)*1000.0f, 1, VCC.ReadManual(A,i)*1000.0f, 0, 1);
        VCC.WriteChannel(i,LFO1.CVstream);

      }

      //Mix all VCC outputs and stream them in channel 7
      VCC.mixerMode();
    }
    else if(VCC.SUBMODE==1){

      //Create a LFO and stream it in channel 0
      LFO1.sinMode(false,  VCC.ReadCv(A,2)*1000.0f, 1, VCC.ReadManual(A,2)*1000.0f, 0, 1);
      VCC.WriteChannel(0,LFO1.CVstream);

      //Create a LFO and stream it in channel 1      
      LFO2.sinMode(false,  VCC.ReadCv(A,1)*1000.0f, 1, VCC.ReadManual(A,1)*1000.0f, 0, 1);
      VCC.WriteChannel(1,LFO2.CVstream);

      //create an adsr and stream it in channel 2
      adsr1.adsrMode(true,false,2000,0.25,2000,2000,2000);
      VCC.WriteChannel(2,adsr1.CVstream);

      //Mix channels 0,1,2 and stream the mix in channel 7
      VCC.mixerMode(7,0,1,2);

    }

    else if(VCC.SUBMODE==2){

      //Create a LFO and stream it in channel 0
      LFO1.sinMode(false,  VCC.ReadCv(A,0)*1000.0f, 1, VCC.ReadManual(A,2)*1000.0f, 0, 1);
      VCC.WriteChannel(0,LFO1.CVstream);

      //Create a LFO and stream it in channel 1      
      LFO2.sinMode(false,  VCC.ReadCv(A,1)*1000.0f, 1, VCC.ReadManual(A,1)*1000.0f, 0, 1);
      VCC.WriteChannel(1,LFO2.CVstream);

      //Create a LISSAJOUS and stream it in channel the X_value to channel 2 and the y_value to channel 3   
      liss1.calcs(VCC.ReadCv(A,2),0.9,0.9,true);
      VCC.WriteChannel(2,liss1.x);
      VCC.WriteChannel(3,liss1.y);

      //create an adsr and stream it in channel 4
      adsr1.adsrMode(true,false,2000,0.25,2000,2000,2000);
      VCC.WriteChannel(4,adsr1.CVstream);

      //Mix channels 0,1,2,3,4 and stream the mix in channel 7
      VCC.mixerMode(7,0,1,2,3,4);        
    }

  }


#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}




















