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
	//#include <avr/interrupt.h>
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
//#define VS2
#define VS3

// WHICH 004 VERSION?
#define ADDAC004VS1
//#define ADDAC004VS2

// SOCKET CONSTANTS
#define A 0
#define B 1
#define C 2


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
#define ENVELOPE 0 //manual in on Arduino to test output of AD5668
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

// ONBOARD manual
#define onboardPotPin 0 

#define manualIn2pin 1
#define manualIn3pin 2
#define manualIn4pin 3
#define manualIn5pin 4
#define manualIn6pin 5

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
	#define manualInApin 4
#elif defined VS2
	#define manualInApin 8
#elif defined VS1
	#define manualInApin 4
#endif
#define manualInAs0 35
#define manualInAs1 34
#define manualInAs2 33
// MANUAL INS B
#if defined VS3
	#define manualInBpin 5
#elif defined VS2
	#define manualInBpin 9
#else
	#define manualInBpin 5
#endif
#define manualInBs0 32
#define manualInBs1 31
#define manualInBs2 30
// MANUAL INS C
#define manualInCpin 6
#define manualInCs0 28
#define manualInCs1 29
#define manualInCs2 39

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



/*! \Main class for ADDAC LIBRARY
See member descriptions to know how to use it, or check out the examples supplied with the library
 */

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
		void writeChannel(int _channel,  float _voltage); // INTERNAL - WRITING FROM THIS CLASS - "private"
		void WriteChannel(int _channel,  float _voltage); // EXTERNAL - WRITING FROM ARDUINO ENVIRONMENT
	
		// CV INS A
        float  cvInAvals[6], cvValuesA[6],cvValuesB[6],cvValuesC[6], cvValuesAMapped[6], cvValuesBMapped[6],cvValuesCMapped[6];
		float  ReadCv(int _socket, int _channel);
        void StoreCvs(int _socket, int _channel);
		void ReadCvs(int _socket);
       
    
        // CV PRINTS CONSOLE
        void PrintCvs(int _socket);
        void PrintCv(int _socket, int _channel);
    
		// manual INS A
		int  truthTableA[6],truthTableB[6],truthTableC[6];
		float  manualInAvals[6], manualValuesA[6], manualValuesAMapped[6];
        float  manualInBvals[6], manualValuesB[6], manualValuesBMapped[6];
        float  manualInCvals[6], manualValuesC[6], manualValuesCMapped[6];
		float  ReadManual(int _socket, int _channel);
        void StoreManuals(int _socket, int _channel);
		void ReadManuals(int _socket);
		         
        // manual PRINTS CONSOLE
        void PrintManuals(int _socket);
        void PrintManual(int _socket, int _channel);
	
    
		// GATE INS A		
		byte  ReadGates(int _socket);
        void  ReadGates(int _socket, bool _invert);
        boolean  ReadGate(int _socket, bool _invert, int _channel);
        byte  gateValuesA[8];
        byte  gateValuesB[8];
        byte  gateValuesC[8];
        void  MAXsendGates(int _socket);
           
    
        // manual PRINTS CONSOLE
        void PrintGates(int _socket);
        void PrintGate(int _socket, int _channel);
    
		// GATE OUTS A
		void  shiftOutGates(int myDataPin, int myClockPin, byte myDataOut);
		void  shiftOutGates(int myDataPin, int myClockPin, int _pin, int myDataOut);
    
		int  WriteGates(int _socket, byte _data, int bpm);
		void WriteGatesStraight(int _socket, int _pos, int _data);
		int  gateValuesOutA[8];
		unsigned long gatesOutMillisA, oldGatesOutMillisA;
		// GATE OUTS B
		unsigned long gatesOutMillisB, oldGatesOutMillisB;
		// GATE OUTS C
		unsigned long gatesOutMillisC, oldGatesOutMillisC;
	
		// MODES
		int MODE,SUBMODE;
		long DACvolts[8];
		unsigned long DACtimes[8];
		unsigned int RNDdelays[8];
		boolean direction[8];
		boolean Direction;
		unsigned int rndStep[8];
		
    
		
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
