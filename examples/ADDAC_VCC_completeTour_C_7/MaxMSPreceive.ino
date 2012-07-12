




/*

DONT NEED TO CHANGE NOTHING HERE !!

.
UNLESS YOU REALLY REALLY WANT TO


*/



// Include de SimpleMessageSystem library
#include <SimpleMessageSystem.h> 



void checkMax(){
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
    switch (messageGetChar()) { // Gets the first word as a character
    case 'm': // Write pin
      writeADDAC(); // Call the writepin function
      break;
    case 'g': // Write pin
      writeGatedADDAC(); // Call the writepin function
      break;
    }
  }
}

void writeADDAC() { // Write into ADDAC001 outputs
  int pin;
  unsigned int state;
  pin = messageGetInt(); // Gets the next word as an integer
  state = messageGetInt(); // Gets the next word as an integer
  VCC.WriteChannel(pin, state);
}
void writeGatedADDAC() { // Write into ADDAC001 outputs
  int pin;
  int state;
  
  pin = messageGetInt(); // Gets the next word as an integer
  state = messageGetInt(); // Gets the next word as an integer
  Serial.print("CvA1 ");
  Serial.println(pin);
  Serial.print("CvA2 ");
  Serial.println(state);
  VCC.WriteGatesBstraight(pin, state);
}



