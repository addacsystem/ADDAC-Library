
// NEEDS WIRE LIBRARY AND FAST I2C COMMUNICATION
#include <Wire.h>
#define TWI_FREQ 400000L


#include <ADDAC.h>
#include <ADDAC_Nchunk.h>

ADDAC VCC;
ADDAC_Nchunk Nchunk;

//#define DEBUG

void setup(){
  VCC.setup();
  
  Nchunk.setup(36,234, 34,220);
  
  #ifdef DEBUG
    Serial.begin(115200);
    Nchunk.calibrate(); // Prints X Y Joystick values for calibration purposes, Serial must be Enabled!
  #endif
}


void loop(){
  VCC.update();
   
  // NCHUNK
  Nchunk.update();
  
  // ACCESSING NCHUNK DATA FROM "Data" ARRAY
  VCC.WriteChannel(0,Nchunk.Data[0]); // JOYSTICK X
  VCC.WriteChannel(1,Nchunk.Data[1]); // JOYSTICK Y
  
  VCC.WriteChannel(2,Nchunk.Data[2]); // ACCELEROMETER X
  VCC.WriteChannel(3,Nchunk.Data[3]); // ACCELEROMETER Y
  VCC.WriteChannel(4,Nchunk.Data[4]); // ACCELEROMETER Z
  
  VCC.WriteChannel(5,Nchunk.Data[5]); // BUTTON C
  VCC.WriteChannel(6,Nchunk.Data[6]); // BUTTON Z
  
  #ifdef DEBUG
    Serial.println();
    delay(60);
  #endif
}
