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

#ifndef Z_OSCDecoder_h
#define Z_OSCDecoder_h

#include "Z_OSCMessage.h"

class Z_OSCDecoder{
	
private:
	
	
public:
	
	int16_t decode( Z_OSCMessage::Z_OSCMessage *mes ,const uint8_t *recData );
		
};

#endif