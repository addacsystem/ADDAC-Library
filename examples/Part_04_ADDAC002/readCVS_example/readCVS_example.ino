#include <StandardCplusplus.h>
#include <vector>


#include <ADDAC.h>

// DEBUGGING CONSOLE
#define DEBUG // Just comment this line if you are not using debug 

// INCLUDES THE MAIN ADDAC LIBRARY
#include <ADDAC.h>
// THEN INITIALIZES LIBRARY CLASS
ADDAC VCC; // From now on the class will be called "VCC"

void setup(){
  VCC.setup();
  
  Serial.begin(115200);
}

void loop(){
  VCC.update(); // NEED TO UPDATE THE VCC!
  VCC.ReadCv(A,1);
  VCC.PrintCv(A,1);

  //WORKING MODE
  // ------------------------------------------------------------------------------------------------------------------------ MODE 0 
  if(VCC.MODE==0){  

    //WORKING SUBMODE-------------------------------------------------------------------------------------------------------- SUBMODE 0
    //if MODE == 0 and SUBMODE == 0, send a ramdom voltage to all cv outputs 
    if(VCC.SUBMODE==0){      
      for(int i=1;i<=6;i++){
        //alterar (i-1).....................................................
        VCC.WriteChannel(i, VCC.ReadCv(A,i-1)/1023.0f*addacMaxResolution);
        

      }
    }

    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 1
    //if MODE == 0 and SUBMODE == 1, Read CVAinput1 and controll voltage with it to cv output1 
    else if(VCC.SUBMODE==1){ 
      VCC.WriteChannel(1, VCC.ReadCv(A,0)/1023.0f*addacMaxResolution);
    }
  }
  
    #ifdef DEBUG
    //Put everything you want to debug here!!
    Serial.println();
    delay(10);
  #endif

}





