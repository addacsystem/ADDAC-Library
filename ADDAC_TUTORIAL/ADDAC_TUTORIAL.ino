/* Here is where you initialize and define the variables and librarys that you will use */

//include the ADDAC library to our project
#include <ADDAC.h>
//Initialize the ADDAC LIBRARY CLASS
//From now on the class will be called "VCC"
ADDAC VCC; 



#define addacMaxResolution 65535  // CONSTANT FOR MAXIMUM RESOLUTION RANGE - NOT RECOMMENDED TO CHANGE - !!



/*this is the setup function. Here is where you give values to the variables that you've initiated before and initialize the functions that we will need*/
void setup(){

  //So Lets initiate all the function from ADDAC class. 
  VCC.setup();

}

/*this is the loop function, the name of the functions speaks for it self, it's a loop that means that when the compiler reachs here it began run here over and over again without leaving it*/
void loop(){

  /*As this is a loop we need to update the VCC everytime that the compiler passes here.*/
  VCC.update(); // NEED TO UPDATE THE VCC!



  /*So We have 16 MODES and 16 SUBMODES in our VCC and we need to tell the VCC what the ones that we want to use to store our presets. 
  Let's say that we want to work with MODE "0", SUBMODE "0" and SUBMODE "1" */

  //Choose MODE "0"
  if(VCC.MODE==0){  //  

      //Choose SUBMODE "0"
    if(VCC.SUBMODE==0){     
      //Now we can start our preset for MODE "0" - SUBMODE "0" 

    }
    //Choose SUBMODE "1"
    else if(VCC.SUBMODE==1){
      //Now we can start our preset for MODE "0" - SUBMODE "1" 
    }



  }
}



