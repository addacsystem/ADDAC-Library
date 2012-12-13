//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include Physics class
#include <ADDAC_Physics.h>
//iclude Comparators class
#include <ADDAC_Comparator.h>

//initiate ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Physics physics1;
ADDAC_Comparator comp1;

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

      //create a marble physic and stream the x_position to channel "0" and y_position to channel 1.
      physics1.update(VCC.ReadCv(A,0),VCC.ReadCv(A,1),VCC.ReadCv(A,5),VCC.ReadCv(A,3));//float _gx, float _gy, float _material, float _speed
      VCC.WriteChannel(0, physics1.x);
      VCC.WriteChannel(1, physics1.y);
      VCC.WriteChannel(2, physics1.Velocity);


      //create a comparator to trigger the bumper
      boolean bumpTrigger= comp1.calc(RISE,VCC.ReadManual(A,0),0.5);  

      if(bumpTrigger){
        // bump the marble ball
        physics1.bump(500);
      }
    }
  }

#ifdef DEBUG
  Serial.print("x: ");
  Serial.print(physics1.x);
  Serial.print(" | y: ");
  Serial.print(physics1.y);
  Serial.print(" | Velocity: ");
  Serial.print(physics1.Velocity);
  Serial.println();
  delay(10);
#endif
}
