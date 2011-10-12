/*
 * ADDAC_CVlooper
 * Version 0.1 November, 2009
 * André Gonçalves + Pedro Moura
 *
 * in Experimental work
 * Still a lot to do!
 *
 * add sampling related to time!
 * metronome correction!
 * implement Smooth, with control!!!
 *
 */

#ifndef ADDAC_CVlooper_h
#define ADDAC_CVlooper_h

#include <WProgram.h>
#include <ADDAC_CVbuffer.h>

#define addacMaxResolution 65535 


// VC RECORDER

class ADDAC_CVlooper{
public:
	ADDAC_CVlooper();
		void update(int _MODE, int _interval, float _wet, int _val);
		void loopSize(int _val);
	
		void record(int _val);
		void clearRecord(int _val);
		void overdub(int _val);
		void play();
		
	
	// CV recorder
	int buffsNum, buffSize;
	ADDAC_CVbuffer CVbuffer[3];
	//buffer CVbufferTimes[3];
	int b_index,n_index,index, playIndex;
	
	int currentVal;
	int interval;
	unsigned long time;
	
	float wet;
	unsigned int CVstream;
};

#endif
