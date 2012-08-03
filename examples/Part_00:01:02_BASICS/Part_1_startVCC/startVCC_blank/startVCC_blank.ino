#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC.h>

ADDAC VCC; 

void setup(){
  VCC.setup();
}

void loop(){
  VCC.update(); 
}

