/*
DONT NEED TO CHANGE NOTHING HERE !!
UNLESS YOU REALLY REALLY WANT TO
*/

unsigned int MaxMspOutputMAx=65535;

void checkMax(){
  if (messageBuild() > 0) { // Checks to see if the message is complete and erases any previous messages
    for(int i = 0; i<8;i++){
      switch (messageGetChar()) { // Gets the first word as a character
      case 'm': // Write pin
        writeADDAC(); // Call the writepin function
        break;
      
      case 'c': // Set Numbers of Inputs to read
        SendNchannelsUpdate(); // Call the function
        break;
      
      case 'M': // Set Numbers of Inputs to read
        SendModesUpdate(); // Call the function
        break;
      }
    }
  }
}

void SendModesUpdate() { // Update sending Modes or not
  MODESsend = messageGetInt(); // Gets the next word as an integer
  MODESsend = constrain(MODESsend,0,1);
}

void SendNchannelsUpdate() { // Update 002 channels to read from
  nInputs = messageGetInt(); // Gets the next word as an integer
  nInputs = constrain(nInputs,0,6);
}

void writeADDAC() { // Write into ADDAC001 outputs
  int pin;
  unsigned int state;
  pin = messageGetInt(); // Gets the next word as an integer
  state = messageGetInt(); // Gets the next word as an integer
  VCC.WriteChannel(pin, float(state)/float(MaxMspOutputMAx));
}
