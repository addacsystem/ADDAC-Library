//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


//include ADDAC class
#include <ADDAC.h>
//include ADDAC Random class
#include <ADDAC_Random.h>
//include ADDAC Quantizer class to quantize the random output
#include <ADDAC_Quantizer.h>

//Initialize and name the ADDAC class
ADDAC VCC;
//Initialize and name 2 Random classes
ADDAC_Random Rnd, Rnd2; 
//Initialize and name one Quantizer class
ADDAC_Quantizer Quant;

#define DEBUG   // Comment this line if you are not debugging

void setup(){

  VCC.setup();

#ifdef DEBUG
  Serial.begin(115200);
#endif

}

void loop(){

  VCC.update(); // UPDATE the VCC class 

  //WORKING ON MODE "O"
  if (VCC.MODE==0){
    
      // Define Random type:
      Rnd.setBrownianRandom(false);
      // Then update Random classes
      // Rnd.update(Random Minimum (0 to 1),Random maximum(0 to 1), 
      //            time minimum(millis), time maximum(millis), smooth(0 to 1));
      //
      
      // Update Random 1 - needed at all loops
      Rnd.update(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));

      // Update Random 2 - needed at all loops
      Rnd2.update(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));      

      //Write OutPuts
      VCC.WriteChannel(0, Rnd.CVstream); // Pure Random 1 Output
      VCC.WriteChannel(1, Quant.calc(Rnd.CVstream)); // Quantized Random 1 Output
      VCC.WriteChannel(2, Rnd2.CVstream); // Pure Random 2 Output
      VCC.WriteChannel(3, Quant.calc(Rnd2.CVstream)); // Quantized Random 2 Output    
  }
  
#ifdef DEBUG
  Serial.println();
  delay(20);
#endif
}


