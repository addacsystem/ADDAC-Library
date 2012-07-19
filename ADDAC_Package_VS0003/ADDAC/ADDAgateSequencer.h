/*
 * ADDA
 * Version 0.1 November, 2009
 * Copyright 2009 André Gonçalves
 * For details, see http://
 *
 * AD5668 programming based on
 * http://
 * Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
 */

#ifndef ADDAgateSequencer_h
#define ADDAgateSequencer_h


/*
//#include <WProgram.h>

#define CLKFUDGE 5      // fudge factor for clock interrupt overhead
#define CLK 256      // max value for clock (timer 2)
#define PRESCALE 8      // timer2 clock prescale
#define SYSCLOCK 16000000  // main Arduino clock
#define CLKSPERUSEC (SYSCLOCK/PRESCALE/1000000)   // timer clocks per microsecond

#define ERR 0
#define DECODED 1

#define BLINKLED 13

// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// clock timer reset value
#define INIT_TIMER_COUNT2 (CLK - USECPERTICK*CLKSPERUSEC + CLKFUDGE)
#define RESET_TIMER2 TCNT2 = INIT_TIMER_COUNT2

#define TOLERANCE 25  // percent tolerance in measurements
#define LTOL (1.0 - TOLERANCE/100.) 
#define UTOL (1.0 + TOLERANCE/100.) 

#define _GAP 5000 // Minimum map between transmissions
#define GAP_TICKS (_GAP/USECPERTICK)

#define TICKS_LOW(us) (int) (((us)*LTOL/USECPERTICK))
#define TICKS_HIGH(us) (int) (((us)*UTOL/USECPERTICK + 1))


// receiver states
#define STATE_IDLE     2
#define STATE_MARK     3
#define STATE_SPACE    4
#define STATE_STOP     5

// information for the interrupt handler
typedef struct {
  uint8_t recvpin;           // pin for IR data from detector
  uint8_t rcvstate;          // state machine
  uint8_t blinkflag;         // TRUE to enable blinking of pin 13 on IR processing
  unsigned int timer;     // state timer, counts 50uS ticks.
  unsigned int rawbuf[RAWBUF]; // raw data
  uint8_t rawlen;         // counter of entries in rawbuf
} 
irparams_t;

// Defined in IRremote.cpp
//extern volatile irparams_t irparams;
*/


class ADDAgateSequencer{
  public:
	int _sequenceId;
	int _channelOutput;
	int _expansionOutput;
	long oldTime;
	byte _sequence;
	int _bpm;
	int _steps;
	
	// channelOutput = 101 -> output A, channel 1 | 307 -> output C, channel 7
	ADDAgateSequencer(int _id, int expansionOutput, int channelOutput, int bpm, int steps, byte sequence){ // add more sequences!! ?? add time for notes??
		_sequenceId = _id;
		_channelOutput = channelOutput;
		_expansionOutput = expansionOutput;
		_bpm = bpm;
		_steps = steps;
		_sequence = sequence;
		oldTime = millis();
	}
	
	
	void channelUpdate(){
		oldTime=millis();
	}
	
	long Time(){
		return oldTime;
	}
};

// information for the CHANNELS
typedef struct {
	uint8_t _id;    // channel
	long timer;     // state timer
} 
channel_n;

// Defined in ADDA.cpp
extern volatile channel_n channels;

// IR detector output is active low
#define MARK  0
#define SPACE 1

#define TOPBIT 0x80000000

#define NEC_BITS 32
#define SONY_BITS 12
#define MIN_RC5_SAMPLES 11
#define MIN_RC6_SAMPLES 1

#endif

