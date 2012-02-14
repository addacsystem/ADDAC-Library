 
/*
 * ADDAC SYSTEM 2011
 *
 * Voltage Controlled Computer C++ LIBRARY
 * Version 0.21 September, AG.2011
 *
 *
* 

CHANGES + REVISIONS + ADDITIONS . 09/2011


0.
----------------------------------------------------------- ADDED LIBRARIES --------------------------------------------------------------------------
ADDAC_Logic       :  Dedicated LOGIC Library
  * featuring: AND, OR, NAND, NOR, XOR, XNOR
  
ADDAC_LFO       :  Dedicated LFO Library
  * featuring: SIN, SAW, TRI, SQR

ADDAC_Clock       :  Dedicated COMPLEX CLOCK Library
  * featuring all clock divisions and multiplications


-------------------------------------------------------------------------------------------------------------------------------------


1.
----------------------------------------------------------- CHANGES --------------------------------------------------------------------------
GATES INPUT NEW BEHAVIOUR
 . Only Needs update and a call to a value, avoids double declaration of the gates array (in arduino and library)
 . Also added an inverting / non-inverting boolean parameter
  * VCC.ReadGatesA(bool inverting); // THIS MAKES VCC READS ALL GATE INPUTS in SLOT A - true:inverting, false:non-inverting
  * VCC.gateValuesA[channel2call] // THIS IS HOW TO ACCESS/CALL EACH CHANNEL INDEPENDENTLY  i.e. accessing the array value straight from the VCC Class
  
 . if Max communication is needed simply call
   *VCC.MAXsendGatesA()

note: should do this to cv and manual readings too!

-------------------------------------------------------------------------------------------------------------------------------------

FTDI USB drivers required!
get the latest version from here:
http://www.ftdichip.com/Drivers/VCP.htm





0lder Updates.
-------------------------------------------------------------------------------------------------------------------------------------

Version 0.2 August, AG.2011
CHANGES + REVISIONS + ADDITIONS . 08/2011


___
 * * *

   Believe me that it's worth it to read all this throughly!
   I definetly spent a lot of time writing it and i wouldn't if i thought it wouldn't be necessary 

   ;)

 * * *
____





0.
-------------------------------------------------------------------------------------------------------------------------------------
BEFORE ANYTHING ELSE!

There's now 3 ADDAC001 Versions, this needs to be defined in the ADDAC.h file!
The code is hardcoded to initialize in VS3, if you have an older version you need to change your ADDAC.h file:

Right at the top you'll find:
// WHICH VCC VERSION?
//#define VS1
//#define VS2
//#define VS3

just uncomment the one you're using and save!
-------------------------------------------------------------------------------------------------------------------------------------



1.
-------------------------------------------------------------------------------------------------------------------------------------
!! INSTALLATION PROCEDURE !!

I strongly recommend that you copy your Arduino.app Application and rename the copied App to something like: ADDAC_Arduino
This way you'll keep the Original Arduino App and use the new one only for the ADDAC001


Instructions:
_
Close Arduino App!
_
for OSX:
Go inside application with "show package contents"
_
for OSX:
(i have no windows computer but files should have the same name and in the same path inside the application's folders)
Replace these 2 files with the same file that goes inside the zip package:
Contents/Resources/Java/libraries/Ethernet/utility/w5100.h
Contents/Resources/Java/hardware/arduino/boards.txt

W5100.h 
This file as to do with the Ethernet Expansion, without this change it won't work at all!

boards.txt 
Creates 2 new Boards in the Arduino Software -> Tools/Board/
ADDAC001 VCC ( AtMega1280 )
ADDAC001 VCC ( AtMega2560 )
_
Drop "ADDAC" Library folder inside your Sketchbook "libraries" folder as defined in the Arduino Preferences (e.g. /Users/a/Documents/Arduino)
-------------------------------------------------------------------------------------------------------------------------------------



2.
-------------------------------------------------------------------------------------------------------------------------------------
!! EXAMPLE !!

The folder named "ADDAC_VCC_completeTour" is the Example to start with!
-------------------------------------------------------------------------------------------------------------------------------------



3.
-------------------------------------------------------------------------------------------------------------------------------------
!! LIBRARY FOLDER CHANGES !!

Library is now called ADDAC!
(Older code and library will work just as it was, for the Arduino environment this will be a Brand New Library)


Library folder has more files than before:
I've been moving functions out of the main library, making them classes instead to be used from the arduino environment


Classes already implemented in the library folder:
(These are also great new additions to the functions list!)

ADDAC_Liss       :  ADDAC502 Lissajous Curves Library
ADDAC_Physics    :  ADDAC503 Marble Physics Library
ADDAC_Quad       :  ADDAC803 Quadraphonic Spatializer Library
ADDAC_CVlooper   :  ADDAC304 CV Looper Library
ADDAC_Quantizer  :  Dedicated Quantizer Library
ADDAC_Adsr       :  Dedicated ADSR Library

If you want to check what's happening in there just open the cpp + h files from the library!
For some Classes you really have to do it like that for now, (e.g. the quantizer notes selection has to be done in the ADDAC_Quantizer.cpp file)


Still need to work on the old functions, lfos, ethernet, midi...
So, for now the old Functions are working as before!
-------------------------------------------------------------------------------------------------------------------------------------



4.
-------------------------------------------------------------------------------------------------------------------------------------
You can see examples of these Libraries in use in the BEHAVIOUR Tab:
MODE 0 / SUBMODE 4   - ADDAC005 GATES OUT Test 
MODE 0 / SUBMODE 5   - ETHERNET - Use with Max-Msp Test Patch
MODE 0 / SUBMODE 6   - QUANTIZER 
MODE 0 / SUBMODE 7   - LISSAJOUS CURVES 
MODE 0 / SUBMODE 8   - MARBLE PHYSICS 
MODE 0 / SUBMODE 9   - QUADRAPHONIC SPATIALIZER 
MODE 0 / SUBMODE 10  - EXPERIMENTAL CV LOOPER 
MODE 0 / SUBMODE 11  - ADSR's 
MODE 0 / SUBMODE 12  -  

MODE 0 / SUBMODE 14  - ADDAC006 NCHUNK Test : nunchuck remote controller connection
MODE 0 / SUBMODE 15  - IANNIX SOFTWARE CONNECTION  http://www.iannix.org
-------------------------------------------------------------------------------------------------------------------------------------



5.
-------------------------------------------------------------------------------------------------------------------------------------
!! ADDAC Class is now called VCC inside the arduino environment !!

so instead of:
ADDAC.writeChannel(1, addacMaxResolution);

please use:
VCC.writeChannel(1, addacMaxResolution);
-------------------------------------------------------------------------------------------------------------------------------------



6.
-------------------------------------------------------------------------------------------------------------------------------------
!! ADDAC_Empty Class Example !!

Creating Classes is much easier now!

added the Empty Example Class:
ADDAC_Empty.h
ADDAC_Empty.cpp

Simply add your own code and get going!
I suggest that you duplicate those files and rename them to your own Class names
e.g. "ADDAC_AG_MyBrandNewClass.h" & "ADDAC_AG_MyBrandNewClass.cpp"

if you rename the files please don't forget to "Find & Replace" all the references ADDAC_Empty to the new file name 
e.g. change "ADDAC_Empty" to "ADDAC_AG_MyBrandNewClass"
-------------------------------------------------------------------------------------------------------------------------------------



7.
-------------------------------------------------------------------------------------------------------------------------------------
!! IanniX_lib       :  IanniX software Library !!

implemented a connection to the very interesting IanniX Software:
Visit http://www.iannix.org for more information!
-------------------------------------------------------------------------------------------------------------------------------------
*/

