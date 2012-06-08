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




#ifndef Z_OSCMessage_h
#define Z_OSCMessage_h


//#include "Z_OSCcommon.h"


class Z_OSCMessage{
	
private:
	
	uint16_t	allPackSize;	//
	char	   *oscAddress;		// "/ard"
	uint16_t	oscAdrSize;		// "/ard" ->4
	uint16_t	oscAdrPacSize;	// "/ard\0\0\0\0" ->8
	
	char	   *typeTag;		// "iif"
	uint16_t	typeTagSize;	// ",iif" -> 4
	uint16_t	typeTagPacSize;	// ",iif\0\0\0\0" -> 8
	
	
	void	  **arguments;
	uint16_t	argsNum;		// "iif" -> 3
	uint16_t	argsPacSize;	// "iif" -> 4 + 4 + 4 = 12
	
	uint8_t		ipAddress[4];	//{192,168,0,10}	
	uint16_t	portNumber;		//10000
		
public:
	
	

	Z_OSCMessage();
	Z_OSCMessage(const char *_oscAddress);
	~Z_OSCMessage();

	void flush();
	
	
	uint16_t getAllPackSize();
	uint16_t getStrPackSize(const char* data);
	uint16_t getPackSize(uint16_t size);
	
	
	
	void setAddress(uint8_t *_ip , uint16_t _port);
	
	void setIpAddress( uint8_t *_ip );		
	void setIpAddress( uint8_t _ip1, uint8_t _ip2,	uint8_t _ip3, uint8_t _ip4);
	
	uint8_t *getIpAddress();
	void setPortNumber(uint16_t _port);
	uint16_t getPortNumber();
	
	int16_t setZ_OSCMessage( const char *_address ,char *types , ... );
	int16_t getArgsNum();
	
	int16_t setZ_OSCAddress(const char *_address);
	char   *getZ_OSCAddress();
	
	int16_t setTypeTags(const char *_tags);
	char   *getTypeTags();
	char	getTypeTag(uint16_t _index);	
	
			
	
	int32_t	getInteger32(uint16_t _index);
	
#ifdef _USE_FLOAT_
	float	getFloat(uint16_t _index);
#endif

#ifdef _USE_STRING_
	char   *getString(uint16_t _index);
#endif
	
	
	
	friend class Z_OSCServer;
	friend class Z_OSCClient;
	friend class Z_OSCDecoder;
	friend class Z_OSCEncoder;
	
};


#endif
