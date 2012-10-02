//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include ADDAC COMPARATOR CLASS
#include <ADDAC_Comparator.h>

//initiate all ADDAC classes and name them
ADDAC VCC;
ADDAC_Comparator comp1, comp2;


#define DEBUG    // Just comment this line if you are not debugging

void setup(){
  //setup all VCC main settings
  VCC.setup();

  //DEBUG settings
#ifdef DEBUG
  //Serial speed communication
  Serial.begin(115200);
#endif
}

void loop(){
  //update VCC
  VCC.update();


  if(VCC.MODE==0){  
    
    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){

      //create a boolean variable type that will be true if we move our Manual POT down 0.5
      boolean normalTrigger = comp1.calc(FALL,VCC.ReadCv(A,0),0.5); 

      //create a boolean variable type that will be true after 2 second if we move our Manual POT above or down 0.5
      boolean delayedTrigger = comp2.calc(CHANGE,VCC.ReadCv(A,5),0.5,2000);

      //if normalTrigger is true print a message in the Serial Monitor
      if(normalTrigger){
        
        Serial.print("NOW!");
      }

      //if delayedTrigger is true print a message in the Serial Monitor
      if(delayedTrigger){
        
        Serial.println("5 SECOND AGO!");
      }
    }
  }

#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}
