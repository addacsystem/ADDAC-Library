/*
 * ADDAC_Ntof
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_Ntof.h> // This loads the Class when compiling
 ADDAC_Ntof Empty; // This Instantiates 1 Class with the name "Empty"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = Empty.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, Empty.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:

 
 *
 *
 */

#ifndef ADDAC_Ntof_h
#define ADDAC_Ntof_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


class ADDAC_Ntof{
public: // Functions to be called from Arduino Environment
    
	/*! \brief Default constructor for ADDAC_Ntof. */
	ADDAC_Ntof(void){};
	float calc(float _midiNote, int _offset){
		return pow(2,(_midiNote - _offset)/12) * 440;
	}; 
	
	float period(float _Notes05v, int _offset){
		float Note= (_Notes05v *5.0f)*12.0f; // entre 0 e 5 oitavas
		//Serial.print("  note:");
		//Serial.print(Note);
		Note= pow(2,(Note- _offset)/12) * 440;
		//Serial.print("  freq:");
		//Serial.print(Note);
		
		float period = 1/(Note/1000000);
		//if(period< 956.25) period= 956.25;
		//else if(period>10000) period= 10000;
		//Serial.print("  Period:");
		//Serial.print(period);
		return period;
	} 
	
	float calc(float _val, float _factor);
	float log10(float _x);
	
	float CVstream; // Public Variables
	
};
#endif
