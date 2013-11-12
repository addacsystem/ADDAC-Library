//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC main library
#include <ADDAC.h>
//include ADDAC linear to logarithimic class
#include <ADDAC_Lin2Log.h>

//initialize and name ADDAC main class
ADDAC VCC; 

//initialize and name ADDAC main class
ADDAC_Lin2Log lg; 

//variable to store the linear to logarithimic conversion
float logV;

#define DEBUG   // Comment this line if you are not debugging

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
  VCC.update();
  //Working on MODE “0”, SUBMODE “0”.
  if (VCC.MODE==0){

    if (VCC.SUBMODE==0){
      //Convert a linear CvPot to a logarithmic one witha a factor of 0.85
      logV=lg.calc(VCC.ReadCv(A,0),0.55f);      
    }
  }

#ifdef DEBUG
  Serial.print("lin: ");
  Serial.print(VCC.ReadCv(A,0));
  Serial.print(" | log: ");
  Serial.print(logV);
  Serial.println();
  delay(10);
#endif
}


