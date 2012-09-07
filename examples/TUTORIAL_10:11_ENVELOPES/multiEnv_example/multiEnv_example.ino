//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC Main class
#include <ADDAC.h>
//include Envelope class
#include <ADDAC_Env.h>
//include Comparator class
#include <ADDAC_Comparator.h>

//Initialize and name the ADDAC main class
ADDAC VCC;
//Initialize and name 2 Envelopes
ADDAC_Env ENV1, ENV2;
//Initialize and name 2 Comparators
ADDAC_Comparator  COMP1, COMP2;

//create 2 booleans with will store the values from the comparators
boolean envTrigger;
boolean addPointTrigger;

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

      //add point to envelope when ManualPot "0", is above 0.5
      addPointTrigger = COMP1.calc(RISE,VCC.ReadManual(A,0),0.5);

      //trigger envelope when ManualPot 1, is above 0.5
      envTrigger = COMP2.calc(RISE,VCC.ReadManual(A,1),0.5);        

      if(addPointTrigger){
        //Point Amplitude is defined by the CvPot "0", Time is CvPot "1" 
        ENV1.addPoint(VCC.ReadCv(A,0),VCC.ReadCv(A,1));
        ENV2.addPoint(VCC.ReadCv(A,0),VCC.ReadCv(A,1));
      }

      //create a multi envelope
      ENV1.MultiEnv(envTrigger,false);
      //create a multi envelope in loop
      ENV2.MultiEnvLoop(envTrigger,false);

      //Stream ENV1 to channel "0"
      VCC.WriteChannel(0,ENV1.CVstream);   
      //Stream ENV2 to channel "1"      
      VCC.WriteChannel(1,ENV2.CVstream);   
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


