//CODE BASED ON:
/*!
 *  @original file		DmxSimple.h
 *  Project		DmxSimple
 *	@brief		A simple interface to DMX.
 *	Version		3
 *  @author		Peter Knight 
 *	@date		2008-2009
 
 @modified		12.2012
 @author		ag
 
 modified:
 .integrated DmxSimple Library
 -> corrected Library to support ATMEGA2560
 -> Line 34 of DmxSimple.cpp needs to be corrected, add this in ifDefined statement:
 defined(__AVR_ATmega2560__) ||
 should look something like this in the end:
 #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__)
 -> Error found in this discussion:
 http://code.google.com/p/tinkerit/wiki/DmxSimple
 
 */


#ifndef ADDAC_DMX_h
#define ADDAC_DMX_h

#include <StandardCplusplus.h>
#include <vector>
using namespace std;


#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
// Provides ISR
#include <avr/interrupt.h>
#endif

#if RAMEND <= 0x4FF
#define DMX_SIZE 128
#else
#define DMX_SIZE 512
#endif

#define DMXA 48
#define DMXB 45

#include "ADDAC_dmxChannel.h"
#include "ADDAC_Timer.h"

class ADDAC_DMX
{
public:
    void maxChannel(int);
    void write(int, uint8_t);
    void usePin(uint8_t);
        
    
    //ADDAC FUNCTIONS
    float CVstream;
    float actualValue;
    
    void setup();
    void setup(int _pin);
    void addChannel(int channel);
    void update();
    
    void fadeIn(int _channel, int _maxValue, long _time);
    void fadeOut(int _channel, int _minValue, long _time);
    void strobe(int _channel, long _time);
    
    void set(int _channel, int _value);
    int DMXstream(int _channel);
    
    ADDAC_Timer delayControl;
    
    vector<ADDAC_dmxChannel> channel;
    
};
extern ADDAC_DMX DmxSimple;

#endif
