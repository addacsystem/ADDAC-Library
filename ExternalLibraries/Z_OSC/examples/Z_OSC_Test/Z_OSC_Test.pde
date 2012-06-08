/* 
 
 Z_OSC_Test
 
 for Max/Msp & ARDUINO 0022

 
 Command via OSC messages for pwm output
 & limit switches
 
 
 Created 27/02/2011
 by Jerome Dupraz
 */

#include <SPI.h>
#include <Ethernet.h>   // version IDE 0022
#include "Z_OSC.h"    // version IDE 0022
#include <EEPROM.h>

/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/

#define  M1  5 // Pin for PWM M1  Message from MAX/MSP /pwm/1 0 (from 0 to 255)
#define  M2  6 // Pin for PWM M2  Message from MAX/MSP /pwm/2 0 (from 0 to 255)
#define  A1  3 // Pin for PWM A1  Message from MAX/MSP /pwm/3 0 (from 0 to 255)

#define  SW1  10 // limit switch low M1 stop 
#define  SW2  11 // limit switch high M1 stop 
#define  SW3  12 // limit switch low & high M2 stop 


#define  ON_M 4 // Demarrage carte MD22 X  Message to send from MAX/MSP /on/1 0 ( 0 or 1)
#define  ON_A 2 // Open airflow X  Message to send from MAX/MSP /on/2 0 ( 0 or 1)

long valSW1;
long valSW2;
long valSW3;

long oldSW1;
long oldSW2;
long oldSW3;

long valON_M;
long oldvalON_M ;
long valON_A;
long oldvalON_A ;

long int speedM1;  // motor M1 speed
long int speedM2;  // motor M2 speed
long int speedA1;  // motor A1 speed


int addressX = 0; // the current address in the EEPROM to store stateX
int stateX=0; // state of limit switch SW3 according to M2 direction


///////////////////////////
Z_OSCMessage *rcvMes;
Z_OSCClient client;
Z_OSCServer server;
Z_OSCMessage message;  

///////////////////////////////////////////////////////////////  
// SET THE RIGHT ADDRESS FOR ARDUINO 
///////////////////////////////////////////////////////////////
byte myMac[]= {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // TO SET ADDRESS MAC ARDUINO CARD
byte myIp[] = { 192, 168, 1, 11 };      // TO SET ADDRESS IP ARDUINO CARD  
int  serverPort = 10011;                // TO SET RECEIVING PORT
byte gateway[] = { 192, 168, 1, 1 };    // ROUTER
byte subnet[] = {255, 255, 255, 0 };    // SUBNET
byte destIp[] = {192, 168, 1, 10};      // TO SET ADDRESS IP COMPUTER
int  destPort = 10012;                  // TO SET SENDING PORT
///////////////////////////////////////////////////////////////  
///////////////////////////////////////////////////////////////  

void setup() {
  //Serial.begin(9600);
 
  //Ethernet.begin(serverMac ,serverIp);
  Ethernet.begin(myMac ,myIp ,gateway ,subnet);

  //setting osc receive server
  server.sockOpen(serverPort);

 
    pinMode(3, OUTPUT); // PWM PIN as output
    pinMode(5, OUTPUT); // PWM PIN as output
    pinMode(6, OUTPUT); // PWM PIN as output
  
    pinMode(2, OUTPUT);  // ON_M  as output
    pinMode(4, OUTPUT);  // ON_A  as output

  for(int i=10; i<13; ++i) { // switch pin as input
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);   // pull up resistor
  }

  analogWrite(M1, 127);  // M1 "stop"
  analogWrite(M2, 127);  // M2 "stop"
  analogWrite(A1, 0);    // A1 "stop"
  

  delay(1000); // wait 1s
  
  digitalWrite(ON_M, HIGH);   //put on M
  digitalWrite(ON_A, HIGH);   //put on A

}

///////////////////////////////////////////////////////////////  
void loop() {

  onPin();  // send ON-pin value

  if ( server.available() ) {   //check if osc arrive 
    rcvMes=server.getMessage();
    rcvMes->setPortNumber(destPort);

    pwmProcess();
    
  } 
  swProcess();   // send limit switches values
  checkStop();   // check limit switches to stop motors
  codProcess();  // send encoder values
}


//////////////////////////////
// FONCTION
///////////////////////////////
// =============================================================================
// this fonction check the state of ON PIN
void onPin(){
     if( !strcmp( rcvMes->getZ_OSCAddress() , "/on/1" ) ){   // check ON_M send by Max/Msp 
      long int value1=rcvMes->getInteger32(0);
      if( value1 == 0 ){
        digitalWrite(ON_M, LOW);   // OSC message: /on 0    put off M
      } 
      else {
        digitalWrite(ON_M, HIGH);   // OSC message: /on 1   put on M
      } 
    }

    if( !strcmp( rcvMes->getZ_OSCAddress() , "/on/2" ) ){   // check ON_A 
      long int value2=rcvMes->getInteger32(0);
      if( value2 == 0 ){
        digitalWrite(ON_A, LOW);   // OSC message: /on 0    put off A
      } 
      else {
        digitalWrite(ON_A, HIGH);   // OSC message: /on 1   put on A
      } 
    }

  
}
  
// =============================================================================
// this fonction send the state of ON PIN
void onPin(){
  message.setAddress(destIp,destPort);
  client.send(&message);

  valON_M = digitalRead(ON_M);   
  if( oldvalON_M != valON_M ){   // check ON_M state and send "/on/1 0 or 1"
    message.setZ_OSCMessage("/on/1" , "i", &valON_M);
    client.send(&message);
  }
  oldvalON_M = valON_M;

  valON_A = digitalRead(ON_A); 
  if( oldvalON_A != valON_A ){   // check ON_A state and send "/on/2 0 or 1"
    message.setZ_OSCMessage("/on/2" , "i", &valON_A);
    client.send(&message);
  }
  oldvalON_A = valON_A;
  
}

// =============================================================================
// this fonction set the speed of motors and air flow receiving "/pwm/ 0 to 255"
void pwmProcess(){
  
  if(valON_M == HIGH ){        
     if( !strcmp( rcvMes->getZ_OSCAddress() , "/pwm/1" ) ){
      speedM1= rcvMes->getInteger32(0);
      analogWrite(M1, speedM1);  // set pwm value on PIN
    }  
     if( !strcmp( rcvMes->getZ_OSCAddress() ,  "/pwm/2" ) ){
      speedM2 = rcvMes->getInteger32(0);
      analogWrite(M2, speedM2);  // set pwm value on PIN
    }
    else {
      analogWrite(M1, 127);   // "stop" M1
      analogWrite(M2, 127);   // "stop" M2
    }
  }

  if(valON_A == HIGH ){
    if( !strcmp( rcvMes->getZ_OSCAddress() ,  "/pwm/3" )){
      speedA1 = rcvMes->getInteger32(0);
      analogWrite(A1, speedA1);  // set pwm value on PIN
    }  
  }
  else {
    analogWrite(A1, 0);  // "stop" A1
  }
 
}

// =============================================================================
// this fonction send the limit switches in OSC message "/sw/1 0 or 1"
void swProcess(){

  message.setAddress(destIp,destPort);
  client.send(&message);

  //SWTCH 1 SW1  
  valSW1 = digitalRead(SW1);
  if( oldSW1 != valSW1 ){
    message.setZ_OSCMessage("/sw/1" , "i", &valSW1);
    client.send(&message);
  }
  oldSW1 = valSW1;

  //SWTCH 2 SW2  
  valSW2 = digitalRead(SW2);
  if( oldSW2 != valSW2 ){
    message.setZ_OSCMessage("/sw/2" , "i", &valSW2);
    client.send(&message);
  }
  oldSW2 = valSW2;

  //SWTCH 3 SW3  
  valSW3 = digitalRead(SW3);
  if( oldSW3 != valSW3 ){ 
    message.setZ_OSCMessage("/sw/3" , "i", &valSW3);
    client.send(&message);
  }
  oldSW3 = valSW3;

 
  message.flush();

}

// =============================================================================
// this fonction check the limit switches to stop motors
void checkStop(void) {

  // M1
  if ((valSW1 == HIGH) && (speedM1 < 127)){
    analogWrite(M1, 127);   // stop  M1 when SW1 is pressed
  }

  if ((valSW2 == HIGH) && (speedM1 > 127)){
    analogWrite(M1, 127);  // stop  M1 when SW2 is pressed
  }

  // M2
  if (valSW3 == HIGH) {    // stop  M2 when SW3 is pressed according to stateX value
    if ((speedM2 < 127) && (stateX == 0)) {
      analogWrite(M2, 127); 
    }
    if ((speedM2 > 127) && (stateX == 1)){
      analogWrite(M2, 127); 
    }
  }

  if (valSW3 == LOW) {  // set the stateX to 0 or 1 according to the motor direction Left or Right
    if (speedM2 < 127) {
      stateX = 0; 
    }
    if (speedM2 > 127) {
      stateX = 1; 
    }
  }

  EEPROM.write(addressX, stateX);  // write the state value to the appropriate byte of the EEPROM. 
  // these values will remain there when the board is turned off.

}





