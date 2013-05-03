/* EXAMPLE FOR TRIPLE PENDULUM 
 
 
              x
              |
              |
              v1
               \
                \
                 v2 
                / 
               v3
 
 
 *////////////////////////////    


//INCLUDE STANDARDCPLUSPLUS LIBRARY//
#include <StandardCplusplus.h>
#include <vector>       
////////////////////////////////////


#include <ADDAC.h>
ADDAC VCC; 

#include <ADDAC_Pendulum.h>
pendulums::ADDAC_Pendulum pd;




//#define DEBUG   // Comment this line if you are not debugging

void setup(){
  //setup all VCC main settings
  VCC.setup();
  pd.setup();

  //debug settings
#ifdef DEBUG
  //serial speed communication 
  Serial.begin(115200);
#endif
}


void loop(){
  VCC.update();

  //select mode | 1-"Euler Method" | 2-"Heun's Method" | 3-"Runge-Kutta Method" | DEFAULT - MODE - 1-"Euler Method"
  //Mode will influence the pendulum behavior 
  //pd.setMode(2);

  //update pendulum with simulation speed
  pd.update(VCC.ReadCv(A,0)/1000);

 if (VCC.MODE==0){
  //Use Pendulum Vertice Positions as LFO'S 
  //vertice1
  VCC.WriteChannel(0,pd.posX[0]);
  VCC.WriteChannel(1,pd.posY[0]);
  //vertice2
  VCC.WriteChannel(2,pd.posX[1]);
  VCC.WriteChannel(3,pd.posY[1]);
  //vertice3
  VCC.WriteChannel(4,pd.posX[2]);
  VCC.WriteChannel(5,pd.posY[2]);
 }
  if (VCC.MODE==1){
  //OR use the AXIS COLISIONS for tiggers -  bool triger[6] |  0,1,2 - X axis | 3,4,5 - Y axis
  // X AXIS Colision
  VCC.WriteChannel(0,pd.gate[0]);
  VCC.WriteChannel(1,pd.gate[1]);
  VCC.WriteChannel(2,pd.gate[2]);

  // Y AXIS Colision  
  VCC.WriteChannel(3,pd.gate[3]);
  VCC.WriteChannel(4,pd.gate[4]);
  VCC.WriteChannel(5,pd.gate[5]);
  }


#ifdef DEBUG
  delay(10);
#endif

}





