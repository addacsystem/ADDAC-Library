 

#include "ADDAC_CVbuffer.h"

//-----------------------------------------------------------------------ADDAC CV recorder buffers -----------------

ADDAC_CVbuffer::ADDAC_CVbuffer(){	
	//Serial.println("BUFFER SET!");
}

void ADDAC_CVbuffer::write(int index, int val){
	vals[index]=val;
}


int ADDAC_CVbuffer :: read(int index){
	return vals[index];
}



// --------------------------------------------------------------------------- END ----------------------------------
//

