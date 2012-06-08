/*
 
 ArdOSC - OSC Library for Arduino.
 
 -------- Lisence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2010 recotana( http://recotana.com )　All right reserved
 
 */	



#include <stdlib.h>

#include "OSCCommon/OSCServer.h"

extern "C" {
 
 #include "../../libraries/Ethernet/utility/types.h"
 #include "../../libraries/Ethernet/utility/socket.h"
 #include "../../libraries/Ethernet/utility/spi.h"
 #include "../../libraries/Ethernet/utility/w5100.h"
 
}
 
#include "../../libraries/Ethernet/Ethernet.h"
 



void OSCServer::sockOpen(uint16_t _recievePort){
	socketNo=1;
	socket( socketNo ,Sn_MR_UDP ,_recievePort ,0);
	availableFlush();
	message.flush();
	
	DBG_LOGLN("server open");
	
}



void OSCServer::sockClose(){
	message.flush();
	close( socketNo );
}




bool OSCServer::available(){
	
	if( ( getSn_IR(socketNo) && Sn_IR_RECV ) ) {
		
		if( getSn_RX_RSR(socketNo) > 0 ){
			
			if(decodeProcess()==0)  return 1;
			
		}

	}
	
	return 0;
}




int16_t OSCServer::decodeProcess(){
	
	DBG_LOGLN("decodeProcess");
	message.flush();
	
	
	
	IINCHIP_WRITE( Sn_IR(socketNo) ,Sn_IR_RECV );
	
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


OSCMessage::OSCMessage *OSCServer::getMessage(){

	return &message;
}

void OSCServer::availableFlush(){
	
	while ( available() ){}

}
	
