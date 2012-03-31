/*
 * ADDAC SYSTEM 2011
 *
 * Voltage Controlled Computer C++ LIBRARY
 * Version 0.2 November, 2011
 * Copyright 2011 AndrŽ Gonalves
 * For details, see http://
 *
 * AD5668 programming based on
 * DAC V11 by Robin Price 2009
 +
 * shiftIn Example 2.1 by Carlyn Maw 
 */

#ifndef ADDAC_h
#define ADDAC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include <inttypes.h> 
#else
	#include <WProgram.h>
	// Provides ISR
	#include <avr/interrupt.h>
#endif



// The following are compile-time library options.
// If you change them, recompile the library.
// If DEBUG is defined, a lot of debugging output will be printed during decoding.
// TEST must be defined for the IRtest unittests to work.  It will make some
// methods virtual, which will be slightly slower, which is why it is optional.
// #define DEBUG
// #define TEST

// WHICH VCC VERSION?
//#define VS1
#define VS2
//#define VS3

// WHICH 004 VERSION?
//#define ADDAC004VS1
#define ADDAC004VS2

//#define MIDI

// Values for modes
#define MODE1 1
#define MODE2 2
#define MODE3 3
#define MODE4 4
#define MODE5 5
#define MODE6 6
#define MODE7 7
#define MODE8 8
#define MODE9 9
#define MODE10 10
#define MODE11 11
#define MODE12 12
#define MODE13 13
#define MODE14 14
#define MODE15 15
#define MODE16 16

#define UNKNOWN -1

#define LOW 0
#define HIGH 1


//AD5668 Command definitions
#define WRITE 0
#define UPDATE 1
#define WRITE_UPDATE_ALL 2
#define WRITE_UPDATE_N 3
#define POWER 4
#define LOAD_CC_REG 5
#define LOAD_LDAC_REG 6
#define RESET 7
#define SETUP_INTERNAL_REGISTER 8


//avoid these!!!
#define ENVELOPE 0 //Analog in on Arduino to test output of AD5668
#define DATAOUT 10 //MOSI, DIN Pin 15 on AD5668
#define SPICLK 11 //Serial Clock In, SCLK Pin 16
#define SLAVESELECT 12//SYNC Active Low Control Input, Pin 2
// 2GND #define LDAC 5//LDAC, Pin 1, Pulse this pin low to update DAC registers, can be tied permanently low.
#define CLR 13

extern volatile unsigned long timer0_millis;


//MODES SWITCHES define where your pins are
#ifdef VS3
	#define latchPin  8
	#define dataPin  6
	#define clockPin  7
#else
	#define latchPin  16
	#define dataPin  6
	#define clockPin  17
#endif

// ONBOARD ANALOG
#define onboardPotPin 0 

#define analogIn2pin 1
#define analogIn3pin 2
#define analogIn4pin 3
#define analogIn5pin 4
#define analogIn6pin 5

// CV INS A
#ifdef VS2
	#define cvInApin 10
#else
	#define cvInApin 2
#endif
#define cvInAs0 43
#define cvInAs1 42
#define cvInAs2 41
// CV INS B
#define cvInBpin 1
#define cvInBs0 5
#define cvInBs1 2
#define cvInBs2 3
// CV INS C
#define cvInCpin 3
#define cvInCs0 40
#define cvInCs1 37
#define cvInCs2 36

// MANUAL INS A
#if defined VS3
	#define analogInApin 4
#elif defined VS2
	#define analogInApin 8
#elif defined VS1
	#define analogInApin 4
#endif
#define analogInAs0 35
#define analogInAs1 34
#define analogInAs2 33
// MANUAL INS B
#if defined VS3
	#define analogInBpin 5
#elif defined VS2
	#define analogInBpin 9
#else
	#define analogInBpin 5
#endif
#define analogInBs0 32
#define analogInBs1 31
#define analogInBs2 30
// MANUAL INS C
#define analogInCpin 6
#define analogInCs0 28
#define analogInCs1 29
#define analogInCs2 39

#ifdef VS3
    // GATE INS A - not working pcb defect in VS1 & VS2?!!
    #define gateInAlatch 48 //P/S
    #define gateInAclock 47 //CLK
    #define gateInAdata 49  //Q8
    // GATE INS B
    #define gateInBlatch 39 //P/S
    #define gateInBclock 38 //CLK
    #define gateInBdata 40  //Q8
#else
    // GATE INS A - not working pcb defect in VS1 & VS2?!!
    #define gateInAlatch 19 //P/S
    #define gateInAclock 38 //CLK
    #define gateInAdata 18  //Q8
    // GATE INS B
    #define gateInBlatch 48 //P/S
    #define gateInBclock 47 //CLK
    #define gateInBdata 49  //Q8
    
#endif
    // GATE INS C
    #define gateInClatch 45 //P/S
    #define gateInCclock 46 //CLK
    #define gateInCdata 44  //Q8

// GATE OUTS A
#define gateOutAlatch 27 //P/S - ST_CP
#define gateOutAclock 25 //CLK - SH_CP
#define gateOutAdata 26  //Q8  - DS
// GATE OUTS B
#define gateOutBlatch 24 //P/S
#define gateOutBclock 22 //CLK
#define gateOutBdata 23  //Q8
// GATE OUTS C
#define gateOutClatch 9 //P/S
#define gateOutCclock 7 //CLK
#define gateOutCdata 8  //Q8



#define addacMaxResolution 65535 



// Only used for testing; can remove virtual for shorter code
#ifdef TEST
#define VIRTUAL virtual
#else
#define VIRTUAL
#endif

class ADDAC{
public:
	ADDAC();
		void setup();
		void update();
	
		//onboard Modes Rotary Switches
		void readMODEswitch(); 
		int  readMODE(); 
		int  readSUBMODE(); 
		byte shiftIn(int myDataPin, int myClockPin); 
		byte shiftIn2(int myDataPin, int myClockPin); 
	
		//onboard pot
		int readOnboardPot();
		int onboardVal, onboardValMapped;
		
		//AD5668 functions
		void write(int command, int address, unsigned int data);
		void writeChannel(int _channel, unsigned int _voltage); // INTERNAL - WRITING FROM THIS CLASS - "private"
		void WriteChannel(int _channel, unsigned int _voltage); // EXTERNAL - WRITING FROM ARDUINO ENVIRONMENT
	
		// CV INS A
		unsigned int  cvInAvals[6], cvValuesA[6], cvValuesAMapped[6];
		int  ReadCvsA(int _channel);
		void ReadCvsA();
		// CV INS B
		unsigned int  cvInBvals[6], cvValuesB[6], cvValuesBMapped[6];
		int  ReadCvsB(int _channel);
		void ReadCvsB();
		// CV INS A
		unsigned int  cvInCvals[6], cvValuesC[6], cvValuesCMapped[6];
		int  ReadCvsC(int _channel);
		void ReadCvsC();
	
		// ANALOG INS A
		int  truthTableA[6],truthTableB[6],truthTableC[6];
		unsigned int  analogInAvals[6], analogValuesA[6], analogValuesAMapped[6];
		int  ReadAnalogsA(int _channel);
		void ReadAnalogsA();
		// ANALOG INS B
		int  analogInBvals[6], analogValuesB[6], analogValuesBMapped[6];
		int  ReadAnalogsB(int _channel);
		void ReadAnalogsB();
		// ANALOG INS C
		unsigned int  analogInCvals[6], analogValuesC[6], analogValuesCMapped[6];
		int  ReadAnalogsC(int _channel);
		void ReadAnalogsC();
	
		// GATE INS A
		byte  gateValuesA[8];
		byte  ReadGatesA();
        void  ReadGatesA(bool _invert);
        void  MAXsendGatesA();
		// GATE INS B
		byte  gateValuesB[8];
		byte  ReadGatesB();
		void  ReadGatesB(bool _invert);
        void  MAXsendGatesB();
        // GATE INS C
		byte  gateValuesC[8];
		byte  ReadGatesC();
		void  ReadGatesC(bool _invert);
        void  MAXsendGatesC();
    
		// GATE OUTS A
		void  shiftOutGates(int myDataPin, int myClockPin, byte myDataOut);
		void  shiftOutGates(int myDataPin, int myClockPin, int _pin, int myDataOut);
		int  WriteGatesA(byte _data, int bpm);
		void WriteGatesAstraight(int _pos, int _data);
		int  gateValuesOutA[8];
		unsigned long gatesOutMillisA, oldGatesOutMillisA;
		// GATE OUTS B
		int  WriteGatesB(byte _data, int bpm);
		void WriteGatesBstraight(int _pos, int _data);
		unsigned long gatesOutMillisB, oldGatesOutMillisB;
		// GATE OUTS C
		int  WriteGatesC(byte _data, int bpm);
		unsigned long gatesOutMillisC, oldGatesOutMillisC;
	
		// MODES
		int MODE,SUBMODE;
		long DACvolts[8];
		unsigned long DACtimes[8];
		unsigned int RNDdelays[8];
		boolean direction[8];
		boolean Direction;
		unsigned int rndStep[8];
		void lfosMode(int _MODE, int _type, int _channel);
		// RANDOM
		void randomMode(int _MODE, int _channel);
		void randomMode(int _channel, bool _inverted, float _randomMin, float _randomMax, float _randomFreqMin, float _randomFreqMax);
		void randomModeSmoothed(int _channel, float _randomMin, float _randomMax, float _randomFreqMin, float _randomFreqMax, float _smooth);
		// SIN
		void sinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top);
		void sinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset);
		unsigned long SINoldTimes[8];
		// coSIN
		void cosinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top);
		void cosinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset);
		// TAN
		void tanMode(int _channel, bool _inverted, float _freq, int _bottom, int _top);
		// MIXER MODE
		void mixerMode();
		void mixerMode(int _upToX);
		void mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E, int _F, int _G, int _H);
		void mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E, int _F, int _G);
		void mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E, int _F);
		void mixerMode(int _channel, int _A, int _B, int _C, int _D, int _E);
		void mixerMode(int _channel, int _A, int _B, int _C, int _D);
		void mixerMode(int _channel, int _A, int _B, int _C);
		void mixerMode(int _channel, int _A, int _B);
  // private:
  //void enableIROut(int khz);
  //VIRTUAL void mark(int usec);
  //VIRTUAL void space(int usec);
	long fMin,fMax,fSeed,vMin,vMax;
	long threshold;
};

#endif
