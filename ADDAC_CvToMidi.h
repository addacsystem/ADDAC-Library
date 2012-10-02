/*
 * ADDAC_CvToMidi
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_CvToMidi.h> // This loads the Class when compiling
 ADDAC_CvToMidi CvToMidi; // This Instantiates 1 Class with the name "CvToMidi"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = CvToMidi.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, CvToMidi.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:
 
 unsigned int CV = CvToMidi.CVstream;
 
 *
 *
 */

#ifndef ADDAC_CvToMidi_h
#define ADDAC_CvToMidi_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 

#include "ADDAC_Midi.h"

class ADDAC_CvToMidi : public ADDAC_Midi{
public:
	ADDAC_CvToMidi();
	void calcNote(float _cv, int _velocity, int _channel);
    void calcCC(int _CCnumber, float _cv, int _channel);
    
    
    int oldCvOut;
    int oldNoteOut;
	
};
#endif
