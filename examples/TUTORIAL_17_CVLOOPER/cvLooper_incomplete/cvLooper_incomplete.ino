//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////

//include ADDAC MAIN LIBRARY
#include <ADDAC.h>
//include CV Looper class
#include <ADDAC_CVlooper.h>
//include QUANTIZER class
#include <ADDAC_Quantizer.h>



//initiate ADDAC CLASS's and name them
ADDAC VCC;
ADDAC_CVlooper looper1;
ADDAC_Quantizer quant1;

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


      //_MODE 0 == LOOP MODE
      //_MODE 1 == OVERDUB MODE
      //_MODE 2 == ERASE MODE
      int _MODE = (VCC.ReadManual(A,0)*10)/3;

      looper1.loopSize(VCC.ReadCv(A,5)*1023.0f); // IF THIS VALUE IS BIGGER THAN 1023/3 it might crash
      looper1.update(_MODE, VCC.ReadCv(A,0), VCC.ReadCv(A,1), VCC.ReadCv(A,2));  // (int _MODE, int _interval, float _wet, int _val);
      VCC.WriteChannel(0, looper1.CVstream); 

      unsigned int temp=quant1.quantize(looper1.CVstream);
      VCC.WriteChannel(1, temp);



    }

  }


#ifdef DEBUG
  Serial.print(looper1.CVstream);
  Serial.println();
  delay(10);
#endif

}






















