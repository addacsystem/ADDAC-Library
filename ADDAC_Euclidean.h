/*
 * ADDAC_Euclidean
 * 
 * Developer's blank page Class example
 *
 * in Arduino environment simply add at the very top:
 
 #include <ADDAC_Euclidean.h> // This loads the Class when compiling
 ADDAC_Euclidean Empty; // This Instantiates 1 Class with the name "Empty"
 
 *
 *
 * then in BEHAVIOUR() add at a position of your choice:
 
 unsigned int CV = Empty.update(random(0, 65535));
 
 or if you want to write it straight out at channel 1 for ex.:
 VCC.WriteChannel(1, Empty.update(random(0, 65535)) );
 
 *
 *
 * or to simply get the current value back use:
 
 unsigned int CV = Empty.CVstream;
 
 *
 *
 */

#ifndef ADDAC_Euclidean_h
#define ADDAC_Euclidean_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

//#include <EEPROM.h>

#define read_delay  50 // for debouncing 
#define MaxChannels 8;

/*
#define brightness 8
#define debug 0 // 0 = normal 1 =  (internal clock) 2= SerialDump
#define display_update 2000 // how long active channel display is shown 
#define sparepin 17
*/

class ADDAC_Euclidean{
public:
	ADDAC_Euclidean(int _channels);
	void update(float _pulse, float _kKnob, float _nKnob, float _channelSwitch); // Function to be called from Arduino Environment
	unsigned int euclid(int n, int k);
	int findlength(unsigned int bnry);
	unsigned int ConcatBin(unsigned int bina, unsigned int binb);
	void Sync();
	void reset();
	
	unsigned int CVstream; // Public Variables
	int length; //pulse length
	unsigned long time;
	unsigned long last_sync;
	
	int clocks[19]; // possible values for n - to make knob easier by offering presets
	int noclocks; // how many possible ns are available?
	
	int channels;
	unsigned int beat_holder[8];
	
	
	/*
	 Eeprom schema: 
	 Channel 1: n = 1 k = 2 o = 7
	 Channel 2: n = 3 k = 4 o = 8
	 Channel 3: n = 5 k = 6 o = 9 
	 */
	
	unsigned int channelbeats[8][4];
	float GateStream[8];
	
	
	int a; 
	int changes;
	boolean sleep;
	int masterclock;
	int read_head;
	unsigned int  looptracker;
	
	int old_total;//for knobs
	int old_pulses;//for knobs
	
	int pulseinput;
	int newpulse;//for trigger in
	int oldpulse;//for trigger in
	
	boolean diga_old; // for encoders 
	boolean digb_old;
	boolean pulses_active; // is active while a beat pulse is playing 
	boolean lights_active;   
	
	int kknob;
	int active_channel; // which channel is active? zero indexed 
	int nknob;
	int oknob; 
	int maxn; // maximums and minimums for n and k 
	int minn;
	int mink; 
	int nn; 
	int kk; 
	unsigned long last_read; 
	unsigned long last_changed; 

	int channel_switch;
	float reset_button; 
	float channel_switch_read;
	
	
	
};
#endif
