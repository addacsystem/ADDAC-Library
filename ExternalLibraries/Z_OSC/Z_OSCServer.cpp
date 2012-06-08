/*
 
 Z_OSC - OSC Library for Arduino.
 
 This library seems to work with Arduino firmware 0022.
 
 Copyright 2011, Jérôme Dupraz. All Rights Reserved
 
 Based on the ArdOSC of recotana( http://recotana.com )
 
 -------- License -----------
 
 Z_OSC
 
 The MIT License see readme.txt
 
 Copyright © 2011 Jérôme Dupraz
 
 */		



#include <stdlib.h>

#include "Z_OSCCommon/Z_OSCServer.h"

#include "SPI.h"

#include "ethernet.h"
#include "client.h"
#include "server.h"
#include "../../libraries/Ethernet/utility/socket.h"

extern "C" {
 

 #include "../../libraries/Ethernet/utility/socket.h"

 #include "../../libraries/Ethernet/utility/w5100.h"
 
}
 #include "string.h"
 



void Z_OSCServer::sockOpen(uint16_t _recievePort){
	socketNo=1;
	socket( socketNo ,SnMR::UDP ,_recievePort ,0);
	availableFlush();
	message.flush();
	
	DBG_LOGLN("server open");
	
}



void Z_OSCServer::sockClose(){
	message.flush();
	close( socketNo );
}




bool Z_OSCServer::available(){
	
	if( ( W5100.readSnIR(socketNo) && SnIR::RECV ) ) {
		
		if( W5100.getRXReceivedSize(socketNo) > 0 ){
			
			if(decodeProcess()==0)  return 1;
			
		}

	}
	
	return 0;
}




int16_t Z_OSCServer::decodeProcess(){
	
	DBG_LOGLN("decodeProcess");
	message.flush();
	
	
	
	W5100.writeSnIR(socketNo ,SnIR::RECV );
	
	message.allPackSize=recvfrom(socketNo
					 ,rcvData
					 ,1 
					 ,message.ipAddress 
					 ,&message.portNumber );
	
	
	if (message.allPackSize>kMaxRecieveData) {
		DBG_LOGLN("server decode process max rcv data err");
		return 2;
	}
	
	
	
	if(decoder.decode( &message ,rcvData ) > 0){
		
		message.flush();
		return 1;
	}

	
	return 0;
}


Z_OSCMessage::Z_OSCMessage *Z_OSCServer::getMessage(){

	return &message;
}

void Z_OSCServer::availableFlush(){
	
	while ( available() ){}

}
	
