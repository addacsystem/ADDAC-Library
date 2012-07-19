/*
07.2011
_

WARNING!!!
Applies to Arduino019 and beyond

-

FOR ETHERNET TO WORK PROPERLY SOME CHANGES NEED TO BE DONE IN w5100.h FILE!!!!
this file can be found inside Arduino Package Contents -> -> libraries/ethernet/utilities

FIND AND CHANGE:

// ################################################################################
private:
    // addac.hack!!
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    inline static void initSS()    { DDRB  |=  _BV(4); };
    inline static void setSS()     { PORTB &= ~_BV(4); };
    inline static void resetSS()   { PORTB |=  _BV(4); };
#else
    inline static void initSS()    { DDRB  |=  _BV(2); };
    inline static void setSS()     { PORTB &= ~_BV(2); };
    inline static void resetSS()   { PORTB |=  _BV(2); };
#endif
// ################################################################################

TO THIS:

// ################################################################################
private:
    // addac.hack!!
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    inline static void initSS()    { DDRB  |=  _BV(0); }; // WAS _BV(4)
    inline static void setSS()     { PORTB &= ~_BV(0); }; // WAS _BV(4)
    inline static void resetSS()   { PORTB |=  _BV(0); }; // WAS _BV(4)
#else
    inline static void initSS()    { DDRB  |=  _BV(2); };
    inline static void setSS()     { PORTB &= ~_BV(2); };
    inline static void resetSS()   { PORTB |=  _BV(2); };
#endif

};
// ################################################################################

*/

#ifdef ETHERNET

//#define DEBUG_ETHERNET


float Vals[8];
int channel=9;

// Parse from MAX
char channel0str[40]="/addac1";
char channel1str[40]="/addac2";
char channel2str[40]="/addac3";
char channel3str[40]="/addac4";
char channel4str[40]="/addac5";
char channel5str[40]="/addac6";
char channel6str[40]="/addac7";
char channel7str[40]="/addac8";

/*
// Parse from MRMR
char hostName[]="aPhone";
char channel0str[40]="/mrmr/slider/horizontal/8/";
char channel1str[40]="/mrmr/slider/horizontal/9/";
char channel2str[40]="/mrmr/slider/horizontal/10/";
char channel3str[40]="/mrmr/slider/horizontal/11/";
char channel4str[40]="/mrmr/slider/horizontal/12/";
char channel5str[40]="/mrmr/slider/horizontal/13/";
char channel6str[40]="/mrmr/slider/horizontal/14/";
char channel7str[40]="/mrmr/slider/horizontal/15/";

void OSCinit(){
  // concatenate strings to fit host name in MRMR!!
 strcat(channel0str,hostName);
 strcat(channel1str,hostName);
 strcat(channel2str,hostName);
 strcat(channel3str,hostName);
 strcat(channel4str,hostName);
 strcat(channel5str,hostName);
 strcat(channel6str,hostName);
 strcat(channel7str,hostName);
}
*/


void EthernetRead(){
  if(server.available()){
    rcvMes=server.getMessage();
    logMessage();
  }
}

void EthernetWrite(){  
  etherTest=millis();
  Serial.print(etherTest);
  Z_OSCMessage mes;  
  mes.setAddress(destIp,destPort);
  mes.setZ_OSCMessage(oscAdr ,"i" ,&etherTest);
  client.send(&mes);
  mes.flush();  
  delay(1);
}

void logMessage(){
    uint16_t i;
    byte *ip=rcvMes->getIpAddress();
    
    long int intValue;
    float floatValue;
    char *stringValue;
    
    
   #ifdef DEBUG_ETHERNET
    Serial.print(ip[0],DEC);
    Serial.print(".");
    Serial.print(ip[1],DEC);
    Serial.print(".");
    Serial.print(ip[2],DEC);
    Serial.print(".");
    Serial.print(ip[3],DEC);
    Serial.print(":");
    
    Serial.print(channel0str);
    Serial.print(" ");
    Serial.print(rcvMes->getPortNumber());
    Serial.print(" ");
    Serial.print(rcvMes->getZ_OSCAddress());
    Serial.print(" ");
    Serial.print(rcvMes->getTypeTags());
    Serial.print("--");
    
   #endif 
   
    // PARSE CHANNELS
    // THIS SHOULD BE OPTIMIZED!!
    if(!strcmp( rcvMes->getZ_OSCAddress(),channel0str)){
      channel=0;
    }else if(!strcmp( rcvMes->getZ_OSCAddress(),channel1str)){
      channel=1;
     }else if(!strcmp( rcvMes->getZ_OSCAddress(),channel2str)){
      channel=2;
    }else if(!strcmp( rcvMes->getZ_OSCAddress(),channel3str)){
      channel=3;
    }else if(!strcmp( rcvMes->getZ_OSCAddress(),channel4str)){
      channel=4;
    }else if(!strcmp( rcvMes->getZ_OSCAddress(),channel5str)){
      channel=5;
    }else if(!strcmp( rcvMes->getZ_OSCAddress(),channel6str)){
      channel=6;
    }else if(!strcmp( rcvMes->getZ_OSCAddress(),channel7str)){
      channel=7;
    }else {
       channel=10;
    }
    
    /*Serial.print(" ");
    Serial.print(rcvMes->getTypeTags());
    Serial.print("--");
    */
    for(i=0 ; i<rcvMes->getArgsNum(); i++){
     switch( rcvMes->getTypeTag(i) ){
        case 'i':       
          intValue = rcvMes->getInteger32(i);
          if(channel<=7){
            Vals[channel]=intValue;
            ADDAC.WriteChannel(channel+1, intValue);
          }
          //Serial.print(intValue);
          //Serial.print(" int:");
         break; 
         
        case 'f':        
          floatValue = rcvMes->getFloat(i);
          if(channel<=7){
            Vals[channel]=floatValue;
            ADDAC.WriteChannel(channel+1, floatValue);
          }
          //Serial.print(" channel:");
          //Serial.print(channel);
          //Serial.print(" val:");
          //Serial.print(Vals[channel]);
         break; 
        
        
         case 's':         
          stringValue = rcvMes->getString(i);
          //Serial.print(stringValue);
          //Serial.print(" string:");
         break;
     }
    }
     Serial.println("");
}








#endif



