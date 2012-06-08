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

#include "Z_OSCCommon/Z_OSCClient.h"

#include "SPI.h"

#include "Ethernet.h"


#include "../../libraries/Ethernet/utility/socket.h"


extern "C" {
 

 #include "../../libraries/Ethernet/utility/socket.h"

 #include "../../libraries/Ethernet/utility/w5100.h"
 
}
 

 
#include "Z_OSCcommon/Z_OSCEncoder.h"



Z_OSCClient::Z_OSCClient(){
	
//	sockOpen();
	
}
Z_OSCClient::~Z_OSCClient(){
//	sockClose();
}



void Z_OSCClient::sockOpen(){
		
	socketNo = 0;
	socket(socketNo, SnMR::UDP, kDummyPortNumber, 0);
	DBG_LOGLN("open UDP socket");
}

void Z_OSCClient::sockClose(){
	DBG_LOGLN("close UDP socket");
	close(socketNo);
}

uint16_t Z_OSCClient::setMessage( Z_OSCMessage *mes){
	
	flushSendData();
	message=mes;
		
	sendData=(uint8_t*)calloc( message->getAllPackSize() ,1 );
		
	Z_OSCEncoder encoder;
	if( encoder.encode(message,sendData) > 0){
		DBG_LOGLN("client set message encode error");
		flushSendData();
		return 1;
	}
	return 0;	
}




uint16_t Z_OSCClient::send(){

	sockOpen();
	sendto(	socketNo ,
		   sendData ,
		   message->allPackSize,
		   message->ipAddress ,
		   message->portNumber );
	sockClose();
	return 0;
}
uint16_t Z_OSCClient::send(Z_OSCMessage *mes){
	
	setMessage(mes);
	return send();
}



void Z_OSCClient::flushSendData(){
	if(sendData!=NULL) free(sendData);
	sendData=NULL;
}
