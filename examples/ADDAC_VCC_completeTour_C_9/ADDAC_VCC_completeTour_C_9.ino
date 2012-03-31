 
/*
 * ADDAC SYSTEM 2011
 *
 * Voltage Controlled Computer C++ LIBRARY
 * Version 0.2 August, AG.2011
 *
 *
* 

ADDAC SYSTEM CODE Full Example

below there's a precious pre-set debug system to help through the coding process
and a commented overview of all variables used globally

A lot have been implemented please read the 2nd Tab on the top!


*/



  /////////////////////////////////////////////////////////////////////////// START UP SETTINGS /////////////////////////////////

// DEBUG METHOD - (UN)COMMENT "#define" LINES BELOW TO PRINT INFO ON SERIAL MONITOR
/*

the principle is simple, comment - uncomment next lines to have a visual output of all input values
*/



// DEBUGGING CONSOLE
#define DEBUG 
#define DEBUGmodes // prints out MODE A+B SWITCHES POSITIONS
//#define DEBUGmidiNotes // MIDI NOTES STEP BY STEP DEBUG
//#define DEBUGcvA // prints out CV/MANUAL INPUTS VALUES
#define DEBUGanalogA // prints out MANUAL INPUTS VALUES
//#define DEBUGanalogB // prints out MANUAL INPUTS VALUES
//#define DEBUGgateINA // prints out GATE INPUTS
//#define DEBUGgateINB // prints out GATE INPUTS

// MAX MSP PROTOCOL
//#define MAXMSP // ENABLES MAX
//#define MaxModes
//#define MaxAnalogA
//#define MaxCvA
//#define MaxNchunk

// USE MIDI?
//#define MIDIenable


#ifdef MIDIenable
  #define USE_SERIAL_PORT         Serial1
  #include <MIDI.h>
  #define polyphonyVoices 3
  int notesNum=0;
  int MIDInotes[polyphonyVoices];
  int MIDIvelocities[polyphonyVoices];
  boolean MIDInoteON[polyphonyVoices];
  int MIDIhistory[polyphonyVoices];
#endif

// USE ETHERNET?
//#define ETHERNET

// USE NUNCHUCK?
//#define NCHUNK

/* 

BELOW THIS POINT THERE'S NOTHING NEEDED TO BE CHANGED !!

.
UNLESS YOU REALLY REALLY WANT TO



BUT IT'S A GOOD OVERALL VIEW OF ALL THE GLOBAL VARIABLES NAMES for all INCOMING AND OUTGOING VALUES 


*/


/////////////////////////////////////////////////////////////////////////// LOAD MAIN LIBRARY /////////////////////////////////


// INCLUDES THE MAIN ADDAC LIBRARY
#include <ADDAC.h>
// THEN INITIALIZES LIBRARY CLASS
ADDAC VCC; // From now on the class will be called "VCC"

/////////////////////////////////////////////////////////////////////////// NEW EXTENSION CLASSES - NEW FUNCTIONS /////////////////////////////////

// INCLUDES AND INITIALIZES THE QUANTIZER LIBRARY
#include <ADDAC_Quantizer.h>
ADDAC_Quantizer Quantize;
int noteNow=0; // variable used for testing only


// INCLUDES AND INITIALIZES THE ADDAC502 - LISSAJOUS CURVES - LIBRARY
#include <ADDAC_Liss.h>
// Instantiates 3 curves:
//ADDAC_Liss Liss1; 
//ADDAC_Liss Liss2;
//ADDAC_Liss Liss3;

// INCLUDES AND INITIALIZES THE ADDAC803 - QUADRIPHONIC SPATIALIZER - LIBRARY
#include <ADDAC_Quad.h>
//ADDAC_Quad Quad;

// INCLUDES AND INITIALIZES THE ADDAC503 - MARBLE PHYSICS - LIBRARY
#include <ADDAC_Physics.h>
//ADDAC_Physics Physics;

// INCLUDES AND INITIALIZES THE CV LOOPER LIBRARY
#include <ADDAC_CVlooper.h>
// Several Independent Loopers can be Instantiated, but Memory is not so big,  aprox. 8-12 seconds if recording at full sample rate
//ADDAC_CVlooper Looper1;
//ADDAC_CVlooper Looper2;

// INCLUDES AND INITIALIZES THE ADDAC303 - VC ADSR - LIBRARY
#include <ADDAC_Adsr.h>
ADDAC_Adsr ADSR1, ADSR2, ADSR3, ADSR4; // Instantiates 4 ADSR's

// INCLUDES AND INITIALIZES THE LOGIC - LIBRARY
#include <ADDAC_Logic.h>
ADDAC_Logic Logic; // Instantiates Logic for all operations

// INCLUDES AND INITIALIZES THE LFO - LIBRARY
#include <ADDAC_LFO.h>
ADDAC_LFO LFO1,LFO2,LFO3,LFO4,LFO5,LFO6,LFO7,LFO8; // Instantiates 1 LFO

// INCLUDES AND INITIALIZES THE CLOCK - LIBRARY
//#include <ADDAC_Clock.h>
//ADDAC_Clock CLOCK1(0); // Instantiates 1 CLOCK
boolean CLK1trig;

// INCLUDES IANNIX LIBRARY
//#include "iannix_lib.h"

#ifdef MAXMSP
  // Include de SimpleMessageSystem library for MAX MSP communication
  #include <SimpleMessageSystem.h> 
#endif

/////////////////////////////////////////////////////////////////////////// VARIABLES DECLARATION - (ToDo: THESE SHOULD ALL GO INTO THE MAIN LIBRARY) /////////////////////////////////



#define addacMaxResolution 65535  // CONSTANT FOR MAXIMUM RESOLUTION RANGE - NOT RECOMMENDED TO CHANGE - !!

// MODE SELECTOR GLOBAL VARIABLES 
// MODE = SWITCH A
// SUBMODE = SWITCH B
int MODE=1, SUBMODE=1;

// ONBOARD POT VALUE VARIABLE
int onboardPot; // PANEL SPEED POT VARIABLE

// ARRAY TO STORE INCOMING ANALOG VALUES
int analogValsA[5]; // MANUAL IN A in ADDAC001 BACK

// ARRAY TO STORE INCOMING CV IN VALUES
int cvValsA[6];// CV IN A in ADDAC001 BACK

// ARRAY TO STORE INCOMING GATES VALUES
int gatesValsA[8]; // GATES IN A in ADDAC001 BACK

// ARRAY TO STORE UPDATED DAC VALUES
int DACvoltages[8]; // this will host readings for each out channel actual value

// ARRAY TO STORE GATES OUT VALUES
byte gatesOutAdataArray[12];
int dataStep=0; // Clapping Music Related - 

// MIDI
byte controlChange, controlChangeVal[256];
int byteNum=0;
byte incomingByte;
byte note;
byte velocity;
int action=2; //0 =note off ; 1=note on ; 2= nada

// SOME OTHER THINGS
// ADSR
boolean adsrTrigger1=true;
boolean adsrTrigger2=true;
boolean adsrTrigger3=true;
// ARRAY TO STORE ANALOG VALUES
int analogValsB[5];
int analogValsC[5];
// ARRAY TO STORE CV IN VALUES
int cvValsB[6];
int cvValsC[6];
// ARRAY TO STORE GATES VALUES
int gatesValsB[8];
int gatesValsC[8];


#ifdef NCHUNK
// NUNCHUCK DATA
  #define TWI_FREQ 400000L
  #include <Wire.h>
  static uint8_t nunchuck_buf[6];   // array to store nunchuck data,
  int joy_x_axis = nunchuck_buf[0];
  int joy_y_axis = nunchuck_buf[1];
  int oldAccel_x_axis=0, accel_x_axis = nunchuck_buf[2]; // * 2 * 2; 
  int oldAccel_y_axis=0, accel_y_axis = nunchuck_buf[3]; // * 2 * 2;
  int oldAccel_z_axis=0, accel_z_axis = nunchuck_buf[4]; // * 2 * 2;
  int z_button = 0;
  int c_button = 0;
  boolean NUNCHUKon=false;
#endif

#ifdef ETHERNET
  #include <SPI.h>
  #include <Ethernet.h> // version IDE 0022
  #include <Z_OSC.h>
  #include <utility/w5100.h>
  
  ///////////////////////////////////////////////////////////////  
// SET THE RIGHT ADDRESS FOR ARDUINO - CHECK STICKER AT THE BACK OF ETHERNET PCB FOR "myMac" variable!!
///////////////////////////////////////////////////////////////
byte myMac[]= {0x90, 0xA2, 0xDA, 0x00, 0x4A, 0x9A }; // TO SET ADDRESS MAC ARDUINO CARD
//byte myMac[]= {0x90, 0xA2, 0xDA, 0x00, 0x44, 0x7B }; // TO SET ADDRESS MAC ARDUINO CARD
byte myIp[]   = {169, 254, 253, 11};      // TO SET ADDRESS IP ARDUINO CARD  
int  serverPort  = 10010;// TO SET ARDUINO PORT 

byte destIp[] = {169, 254, 253, 6};      // TO SET ADDRESS IP COMPUTER
int  destPort = 10000;                  // TO SET SENDING PORT
///////////////////////////////////////////////////////////////  
// OSC SETUP
///////////////////////////////////////////////////////////////  
Z_OSCServer server;
Z_OSCMessage *rcvMes;
Z_OSCClient client;
long int etherTest=0;
char oscAdr[] = "/out1";
#endif


// MEMORY DEBUG
#include <MemoryFree.h>

//
// SETUP INITIALIZES DAC SETTING ALL CHANNELS TO ZERO
void setup(){
  #if defined DEBUG || defined MAXMSP
    Serial.begin(115200); // SERIAL COMMUNICATION BAUD RATE - 115200 - RECOMMENDED!
  #endif
  
  #ifdef MIDIenable
    //Serial1.begin(31250);  
    MIDI.begin(1);
    // Connect the HandleNoteOn function to the library, so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
    MIDInoteON[0]=false;
    MIDInoteON[1]=false;
    MIDInoteON[2]=false;
    MIDInoteON[3]=false;
  #endif
  
  delay(100);
  
 #ifdef ETHERNET
  Ethernet.begin(myMac ,myIp);
  Serial.println("ETHERNET INITIALIZED");
  // ETHERNET TIMEOUT!!
  // as in: http://arduino.cc/forum/index.php?action=printpage;topic=49401.0
  W5100.setRetransmissionTime(0x07D0);
  W5100.setRetransmissionCount(2);
  // END TIMEOUT
  server.sockOpen(serverPort);
  Serial.println("SOCKET OPEN");
  pinMode(53, OUTPUT); 
  
  // OSCinit(); //concatenate strings from MRMR
  Serial.println("OSC READY");
 #endif
  
  #ifdef NCHUNK
    nunchuck_init(); // send the initilization handshake
  #endif
  delay(200);
  VCC.setup(); // INITIALIZES the VCC

  //IanniX::setup(); // INITIALIZES the IanniX Library
 
  // Clapping Music Score - Old Code... 
  gatesOutAdataArray[0] =  B11100111;
  gatesOutAdataArray[1] =  B11111011;
  gatesOutAdataArray[2] =  B11001101;
  gatesOutAdataArray[3] =  B10100110;
  gatesOutAdataArray[4] =  B11101011;
  gatesOutAdataArray[5] =  B11010101;
  gatesOutAdataArray[6] =  B10111010;
  gatesOutAdataArray[7] =  B11011101;
  gatesOutAdataArray[8] =  B10110110;
  gatesOutAdataArray[9] =  B11101011;
  gatesOutAdataArray[10] = B11011101;
  gatesOutAdataArray[11] = B10111110;
  
  
 // RESET ALL CHANNELS TO ZERO
 for(int i=0;i<8;i++){
   VCC.WriteChannel(i+1, 0); // WRITES INTO DAC CHIP
 }
 
 #ifdef DEBUG
   Serial.print( freeMemory() );
 #endif
}

