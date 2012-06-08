#include <SPI.h>
#include <Ethernet.h> // version IDE 0022

#include <Z_OSC.h>

byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte myIp[]  = { 192, 168, 0, 255 };

byte destIp[] =  { 192, 168, 0, 5 };
int  destPort = 10000;



char oscAdr[] = "/z-osc/test/123";
char oscAdr2[] = "/z-osc/test2/abc";

int      iCount  = 0;     
long int liCount = 0;      
float    fCount  = 0.0;    
char     str[]   = "abcd"; 

Z_OSCClient client;

void setup(){
  
  Serial.begin(19200);

  Ethernet.begin(myMac ,myIp);  
  
}

void loop(){
  
  sendProcess();
  
  Z_OSCMessage mes;  
  
  mes.setAddress(destIp,destPort);
  mes.setZ_OSCMessage(oscAdr2 ,"s" ,"test test");
  
  client.send(&mes);
  
  mes.flush();  
  
  delay(100);
}


void sendProcess(){
  
   
  long int tmp=(long int)iCount; 
  
  Z_OSCMessage message;  
  
  message.setAddress(destIp,destPort);
  message.setZ_OSCMessage(oscAdr ,"iifs" ,&tmp ,&liCount ,&fCount ,str);
  
  client.send(&message);


  if(iCount++  > 1000)  iCount =0;
  if(liCount++ > 1000)  liCount=0;
  fCount += 0.1;
  if(fCount  > 100.0) fCount =0.0;
  
}
