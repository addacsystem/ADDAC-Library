//include STL librarys
#include <StandardCplusplus.h>
#include <vector>

//include ADDAC class
#include <ADDAC.h>
#include <ADDAC_Random.h>
#include <ADDAC_Quantizer.h>

//Initialize and name the ADDAC class
ADDAC VCC;
ADDAC_Random Rnd, Rnd2;
ADDAC_Quantizer Quant;


// DEBUGGING CONSOLE
//#define DEBUG 

void setup(){
  VCC.setup();
#ifdef DEBUG
  Serial.begin(115200);
#endif
}

void loop(){
  VCC.update();

  if (VCC.MODE==0){

    if (VCC.SUBMODE==0){
      
       for(int i=0;i<6;i++){      
        VCC.WriteChannel(i, VCC.ReadCv(A,i));
       }        
    }
    
     else if(VCC.SUBMODE==1){ 
      Rnd.setBrownianRandom(false);
      Rnd.update(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));
      Rnd2.update(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));
      VCC.WriteChannel(0, VCC.ReadCv(A,0));
      VCC.WriteChannel(1, Rnd.CVstream);
      VCC.WriteChannel(2, Quant.quantize(Rnd.CVstream));
      VCC.WriteChannel(3, Rnd2.CVstream);
      VCC.WriteChannel(4, Quant.quantize(Rnd2.CVstream));
     }
     
      else if(VCC.SUBMODE==2){ 
      Rnd.setBrownianRandom(true);
      Rnd.update(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));
      Rnd2.update(VCC.ReadCv(A,1),VCC.ReadCv(A,0),
      VCC.ReadCv(A,4)*10000,VCC.ReadCv(A,3)*10000,VCC.ReadCv(A,5));
      VCC.WriteChannel(0, VCC.ReadCv(A,0));
      VCC.WriteChannel(1, Rnd.CVstream);
      VCC.WriteChannel(2, Quant.quantize(Rnd.CVstream));
      VCC.WriteChannel(3, Rnd2.CVstream);
      VCC.WriteChannel(4, Quant.quantize(Rnd2.CVstream));
    }
     
  }

#ifdef DEBUG
  Serial.println();
  delay(10);
#endif

}


