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

#ifndef Z_OSCServer_h
#define Z_OSCServer_h


#include "Z_OSCcommon.h"

#include "Z_OSCDecoder.h"
#include "Z_OSCMessage.h"


class Z_OSCServer{
	
private:
	
	uint8_t socketNo;
	
	uint8_t rcvData[kMaxRecieveData];
	
	Z_OSCMessage message;
	Z_OSCDecoder decoder;
	
	int16_t decodeProcess();

	
	void flushRcvData();
	
	
	
public:
	
	void sockOpen(uint16_t _recievePort);
	void sockClose();
	void availableFlush();
	
	bool available();
	
	
	Z_OSCMessage::Z_OSCMessage *getMessage();


};


#endif