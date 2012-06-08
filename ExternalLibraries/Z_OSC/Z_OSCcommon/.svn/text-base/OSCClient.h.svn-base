/*
 
 ArdOSC - OSC Library for Arduino.
 
 -------- Lisence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2010 recotana( http://recotana.com )　All right reserved
 
 */	


#ifndef OSCClient_h
#define OSCClient_h

#include "OSCcommon.h"
#include "OSCMessage.h"

#define kDummyPortNumber 10000

class OSCClient{
	
private:
	
	uint8_t socketNo;
	
	OSCMessage *message;
	
	uint8_t *sendData;
	
	
	
	void flushSendData();

public:
	
	void sockOpen();
	void sockClose();
	
	OSCClient();
	~OSCClient();
	
	uint16_t setMessage( OSCMessage::OSCMessage *mes );
	
	uint16_t send();
	uint16_t send(OSCMessage::OSCMessage *mes);
			
};


#endif