//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC class
#include <ADDAC.h>

//include the LFO class in your project
#include <ADDAC_LFO.h>

//Initialize and name the ADDAC main class
ADDAC VCC;

/*
initiate the LFO class and give it a name, in this case we will use two LFO’s,
 so we give a name to both, LFO1 and LFO2
 */
ADDAC_LFO LFO1, LFO2;

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
    if(VCC.SUBMODE==0){ 
      /*program to preset in MODE “0”, SUBMODE “0”.
       we have two types of LFO’s, the sin and the cosine next we will create an LFO to each, let’s create the LFO’s
       when creating the LFO we need to pass some parameters that will define the wave.  
       bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top
       
       In this LFO we are creating an sin wave with a frequency defined by our manual “0” input,
       multiply it by “1”, with no offset and a 
       bottom of “0” and top of “1” 
       */
      LFO1.SINupdate(false,  VCC.ReadManual(A,0)*1000.0f, 1, 0, 0, 1);
      // create a cosine wave with the same parameters
      LFO2.COSINupdate(true, VCC.ReadManual(A,1)*1000.0f, 1, 0, 0, 1);

      //then just write the LFO into the desire OUTPUT by using the CVstream variable as the voltage
      //the sin wave to OUTPUT “0”
      VCC.WriteChannel(0,LFO1.CVstream);
      //the cosine wave to OUTPUT “1”
      VCC.WriteChannel(1,LFO2.CVstream);

    }
  }

#ifdef DEBUG
  Serial.print("LFO1 - ");
  Serial.print(LFO1.CVstream);
  Serial.print(" | LFO2 - ");
  Serial.print(LFO2.CVstream);
  Serial.println();
  delay(10);
#endif
}



