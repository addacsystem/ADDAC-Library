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



#ifndef Z_OSCcommon_h
#define Z_OSCcommon_h

//======== user define ==============

//#define _DEBUG_

#define _USE_FLOAT_
#define _USE_STRING_



//======== user define  end  ========

#define kMaxAugument	16

#define kMaxRecieveData	100
#define kMaxZ_OSCAdrCharactor	255
#define kMaxStringCharactor	255



extern "C" {
#include <inttypes.h>
}


#ifdef _DEBUG_
#include "HardwareSerial.h"
#endif

#ifdef _DEBUG_
#define DBG_LOGLN(...)	Serial.println(__VA_ARGS__)
#define DBG_LOG(...)	Serial.print(__VA_ARGS__)

#else
#define DBG_LOGLN
#define DBG_LOG
#endif




#endif