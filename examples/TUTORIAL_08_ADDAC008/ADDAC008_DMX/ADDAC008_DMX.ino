#include <StandardCplusplus.h>
#include <vector>

#include <ADDAC.h>
#include <ADDAC_DMX.h>
#include <ADDAC_Comparator.h>

ADDAC VCC; 
ADDAC_DMX dmx; 
ADDAC_Comparator cpIn, cpOut, cpStrobe;

//#define DEBUG    // Just comment this line if you are not debugging

void setup() {

  //setup VCC class
  VCC.setup();

  dmx.addChannel(1); // init DMX Channell 1
  dmx.addChannel(3); // init DMX Channell 3
  dmx.addChannel(10); // init DMX Channell 10
  dmx.addChannel(100); // init DMX Channell 100

  //setup dmx class using socket A - Default --- For socket B use dmx.setup(DMXB).
  //dmx.setup() must be after adding all the DMXChannels. 
  dmx.setup();

#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("Done Setup!");
#endif


}

void loop() {

  //Update VCC class
  VCC.update();

  //variable to store the value from fadeIn comparator
  boolean fadeInBang = cpIn.calc(FALL,VCC.ReadCv(A,0),0.5);

  if(fadeInBang){ 
    dmx.fadeIn(1,255,10000); // fade in DMXchannel 1 to maxValue of 255 during 1000milliseconds(10 seconds).
  }


  //variable to store the value from fadeOut comparator
  boolean fadeOutBang = cpOut.calc(FALL,VCC.ReadCv(A,1),0.5); // fade in DMXchannel 1 to minValue of 0 during 1000milliseconds(10 seconds).

  if(fadeOutBang) {
    dmx.fadeOut(1,0,10000);
  }

  //variable to store the value from strobe comparator  
  boolean strobeBang = cpStrobe.calc(FALL,VCC.ReadCv(A,5),0.5); 

  if(strobeBang) {
    dmx.strobe(1,50); // strobe DMXchannel 1 with a rate of 50milliseconds.
  }

  //set DMX channel 3 DMXstream to 26 (range:0-255)
  dmx.set(3,26);
  //set DMX channel 10 DMXstream to "CVInput 0" (range:0-255)
  dmx.set(10,VCC.ReadCv(A,0)*255);
  
  //update and write all DMXchannels.
  dmx.update();

  //DEBUG UTILITY
#ifdef DEBUG
  Serial.print(dmx.DMXstream(3));
  Serial.println();
  delay(10);
#endif

}



