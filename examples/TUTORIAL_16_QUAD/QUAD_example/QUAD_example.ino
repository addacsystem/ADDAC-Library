//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include Physics class
#include <ADDAC_Quad.h>

//Initialize ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_Quad quad1;

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
  


  if(VCC.MODE==0){ 

    //WORKING ON MODE "O" - SUBMODE "0"
    if(VCC.SUBMODE==0){
    int quadMode=0;
    // CARTESIAN / POLAR MODE (0=radius/angle; 1=x/y), RADIUS/X, ANGLE/Y, ANGLE MULTIPLIER, EXP/LOG, NA
     quad1.calc(quadMode,VCC.ReadCv(A,0), VCC.ReadCv(A,1), VCC.ReadCv(A,2), VCC.ReadCv(A,3), VCC.ReadCv(A,4)); 
     
     VCC.WriteChannel(0, quad1.amp1); // CHANNEL 1
     VCC.WriteChannel(1, quad1.amp2); // CHANNEL 2
     VCC.WriteChannel(2, quad1.amp3); // CHANNEL 3
     VCC.WriteChannel(3, quad1.amp4); // CHANNEL 4
     
      }

    }

#ifdef DEBUG
  Serial.print("amp1: ");
  Serial.print(quad1.amp1);
  Serial.print(" | amp2: ");
  Serial.print(quad1.amp2);
  Serial.print(" | amp3: ");
  Serial.print(quad1.amp3);
  Serial.print(" | amp4: ");
  Serial.print(quad1.amp4);
  Serial.println();
  delay(10);
#endif

}
