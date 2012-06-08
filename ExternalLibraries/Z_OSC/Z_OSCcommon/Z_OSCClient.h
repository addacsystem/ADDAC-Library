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


#ifndef Z_OSCClient_h
#define Z_OSCClient_h

#include "Z_OSCcommon.h"
#include "Z_OSCMessage.h"

#define kDummyPortNumber 10000

class Z_OSCClient{
	
private:
	
	uint8_t socketNo;
	
	Z_OSCMessage *message;
	
	uint8_t *sendData;
	
	
	
	void flushSendData();

public:
	
	void sockOpen();
	void sockClose();
	
	Z_OSCClient();
	~Z_OSCClient();
	
	uint16_t setMessage( Z_OSCMessage::Z_OSCMessage *mes );
	
	uint16_t send();
	uint16_t send(Z_OSCMessage::Z_OSCMessage *mes);
			
};


#endif