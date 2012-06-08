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
#include <string.h>

#include "Z_OSCcommon/Z_OSCcommon.h"
#include "Z_OSCcommon/Z_OSCDecoder.h"



int16_t Z_OSCDecoder::decode( Z_OSCMessage::Z_OSCMessage *mes ,const uint8_t *recData ){
	
	
//===========  BIN -> Z_OSC Address(String) Decode   ===========
	
	const uint8_t *packStartPtr=recData;
	
	mes->setZ_OSCAddress((char*)packStartPtr);
			
	packStartPtr += mes->oscAdrPacSize;
	


//===========  BIN -> TypeTag (String) Decode   ===========

	mes->setTypeTags((char*)(packStartPtr+1));

	packStartPtr += mes->typeTagPacSize;


//===========  BIN -> Auguments Decode   ===========
	
	
	if (mes->arguments!=NULL) free(mes->arguments);
	mes->arguments=(void**)calloc(mes->argsNum, sizeof(void*));
	
	mes->argsPacSize=0;
	
	uint8_t *tmpPtr;
	uint16_t tmpSize;


	
	for (uint16_t i=0; i< mes->argsNum ; i++) {

		switch (mes->typeTag[i]) {
				
			case 'i':
				
				tmpPtr=(uint8_t*)calloc(1, 4);

				*(tmpPtr+3)=*(uint8_t*)packStartPtr++;
				*(tmpPtr+2)=*(uint8_t*)packStartPtr++;
				*(tmpPtr+1)=*(uint8_t*)packStartPtr++;
				*tmpPtr=*(uint8_t*)packStartPtr++;

				mes->arguments[i]=(uint32_t*)tmpPtr;
				mes->argsPacSize += 4;
				break;

#ifdef _USE_FLOAT_	
			case 'f':
				
				tmpPtr=(uint8_t*)calloc(1, 4);
				
				*(tmpPtr+3)=*(uint8_t*)packStartPtr++;
				*(tmpPtr+2)=*(uint8_t*)packStartPtr++;
				*(tmpPtr+1)=*(uint8_t*)packStartPtr++;
				*tmpPtr=*(uint8_t*)packStartPtr++;

				mes->arguments[i]=(float*)tmpPtr;
				mes->argsPacSize += 4;
				
				break;
#endif
				
				
#ifdef _USE_STRING_
			case 's':
	
				tmpSize=strlen((char*)packStartPtr);
				
				if(tmpSize > kMaxStringCharactor){
					
					DBG_LOGLN("decode max str err");
					return 1;
				}
				
				
				tmpPtr=(uint8_t*)calloc(tmpSize+1, 1);
				strcpy((char*)tmpPtr,(char*)packStartPtr);
				
				mes->arguments[i]=tmpPtr;
	
				
				tmpSize = mes->getPackSize(tmpSize);
				packStartPtr += tmpSize;
				mes->argsPacSize += tmpSize;
								
				break;
#endif
		}
	}
	
	return 0;
}