/* maxMSP patch available in this example folder or in the following link:
http://vcc.addacsystem.com/VCCMaxMsp.zip
*/

//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////

//include ADDAC class
#include <ADDAC.h>

//Initialize and name the ADDAC class
ADDAC VCC; 

#include <SimpleMessageSystem.h> 

// NUMBER OF INPUTS TO SEND
int nInputs = 6;

// SEND MODES Var
int MODESsend = 1;
int mode, submode;

// CV INPUTS Vars
int CV1, CV2, CV3, CV4, CV5, CV6;

int readTiming = 10;
unsigned long Time;

int writeTiming = 5;
unsigned long WTime;

void setup(){
  VCC.setup();
  Serial.begin(115200);
}


void loop(){
 VCC.update(); 
 
  if(Time+ readTiming < millis()){
    Time=millis();
     
    //SEND CV VALUES TO MAX
    SendCVinputs();
  }
  
  //RECEIVE MESSAGES FROM MAX/MSP -> into VCC OUTPUTS
  if(WTime+ writeTiming < millis()){
    WTime=millis();
    checkMax();
  }
}


