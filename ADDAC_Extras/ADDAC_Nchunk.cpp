/*extern "C" {
#include <Wire.h>
}*/

#include "ADDAC_Nchunk.h"

// include types & constants of Wiring core API
#include <WConstants.h>
 


//-----------------------------------------------------------------------ADDAC-----------------
/*! \brief Default construtor for ADDAC_Nchunk */
ADDAC_Nchunk::ADDAC_Nchunk(){	
	
	
	CALIBRATING = false;
	
	//Wire.begin();
}



// --------------------------------------------------------------------------- RANDOMS MODE -------------------------
//

// RANDOMS
/*! \brief Default Setup function with Defalut calibration settings
  \param _calibrationBottomX  	Joystick X min position
  \param _calibrationTopX       Joystick X max position
  \param _calibrationBottomY    Joystick Y min position
  \param _calibrationTopY        Joystick Y max position
 */
void ADDAC_Nchunk::setup(int _calibrationBottomX, int _calibrationTopX, int _calibrationBottomY, int _calibrationTopY){	
	calibrationTopX = _calibrationTopX;
	calibrationBottomX = _calibrationBottomX;
	calibrationTopY = _calibrationTopY;
	calibrationBottomY = _calibrationBottomY;
	
	nunchuck_init();
}
/*! \brief Default Setup function with Defalut calibration settings */
void ADDAC_Nchunk::setup(){	
	calibrationTopX = 245;
	calibrationBottomX = 15;
	calibrationTopY = 245;
	calibrationBottomY = 15;
	
	nunchuck_init();
}

/*! \brief Update all Nchunk atributes  */
// Standard Update
void ADDAC_Nchunk::update(){ 
	nunchuck_get_data();
    nunchuck_parse_data();
}





/*
 * NunchuckPrint
 *
 * 2007 Tod E. Kurt, http://todbot.com/blog/
 *
 * The Wii Nunchuck reading code is taken from Windmeadow Labs
 *   http://www.windmeadow.com/node/42
 
 
 !!!! WARNING !!!!
 The Arduino's twi.h header needs changes. 
 Look in lib/targets/libraries/Wire/utility. Then delete twi.o. Open up twi.h. Uncomment line:
 
 Since the nunchuck uses "Fast" I2C, we will need to change the default speed:
 #define TWI_FREQ 400000L
 
 */

//
// Nunchuck functions
//
// initialize the I2C system, join the I2C bus,
// and tell the nunchuck we're talking to it

void ADDAC_Nchunk::nunchuck_init(){ 
	Wire.begin();	                // join i2c bus as master
	Wire.beginTransmission(0x52);	// transmit to device 0x52
	Wire.write(0x40);		// sends memory address
	Wire.write(0x00);		// sends sent a zero.  
	Wire.endTransmission();	// stop transmitting
}

// Send a request for data to the nunchuck
// was "send_zero()"
void ADDAC_Nchunk::nunchuck_send_request(){
	Wire.beginTransmission(0x52);	// transmit to device 0x52
	Wire.write(0x00);		// sends one byte
	Wire.endTransmission();	// stop transmitting
}

// Receive data back from the nunchuck, 
int ADDAC_Nchunk::nunchuck_get_data(){
    int cnt=0;
    Wire.requestFrom (0x52, 6);	// request data from nunchuck
    while (Wire.available ()) {
		// receive byte as an integer
		nunchuck_buf[cnt] = nunchuk_decode_byte(Wire.read());
		cnt++;
    }
    nunchuck_send_request();  // send request for next data payload
    // If we recieved the 6 bytes, then go print them
    if (cnt >= 5) {
		return 1;   // success
    }
    return 0; //failure
}

// Print the input data we have recieved
// accel data is 10 bits long
// so we read 8 bits, then we have to add
// on the last 2 bits.  That is why I
// multiply them by 2 * 2
void ADDAC_Nchunk::nunchuck_parse_data(){ 
	Data[0]  = nunchuck_buf[0]; // joy_x_axis
	Data[1]  = nunchuck_buf[1]; // joy_y_axis
	Data[2]  = nunchuck_buf[2]; // * 2 * 2; accel_x_axis 
	Data[3]  = nunchuck_buf[3]; // * 2 * 2; accel_y_axis
	Data[4]  = nunchuck_buf[4]; // * 2 * 2; accel_z_axis
	
	Data[5] = 1; // z_button
	Data[6] = 1; // c_button
	
	if (CALIBRATING) {
		Serial.print("JoyX:");
		Serial.print(Data[0]);
		Serial.print(", JoyY:");
		Serial.print(Data[1]);
		Serial.print(" | ");
	}
	
	// byte nunchuck_buf[5] contains bits for z and c buttons
	// it also contains the least significant bits for the accelerometer data
	// so we have to check each bit of byte outbuf[5]
	if ((nunchuck_buf[5] >> 0) & 1) 
		Data[5] = 0;
	if ((nunchuck_buf[5] >> 1) & 1)
		Data[6] = 0;
	
	if ((nunchuck_buf[5] >> 2) & 1) 
		Data[2] += 2;
	if ((nunchuck_buf[5] >> 3) & 1)
		Data[2] += 1;
	
	if ((nunchuck_buf[5] >> 4) & 1)
		Data[3] += 2;
	if ((nunchuck_buf[5] >> 5) & 1)
		Data[3] += 1;
	
	if ((nunchuck_buf[5] >> 6) & 1)
		Data[4] += 2;
	if ((nunchuck_buf[5] >> 7) & 1)
		Data[4] += 1;
    
	
	
	
	Data[0] = map(Data[0],calibrationBottomX,calibrationTopX,0.0f,255.0f)/255.0f;
    Data[0]	= constrain(Data[0],0.0f,1.0f);
	
    Data[1] = map(Data[1],calibrationBottomY,calibrationTopY,0.0f,255.0f)/255.0f; 
	Data[1]	= constrain(Data[1],0.0f,1.0f);
    
    Data[2] = oldAccel[0]*0.8+Data[2]/255.0f*0.2;
    oldAccel[0]=Data[2];
    Data[2]=constrain(Data[2],0.0f,1.0f);
    
    Data[3] = oldAccel[1]*0.8+Data[3]/255.0f*0.2;
    oldAccel[1]=Data[3];
    Data[3] = constrain(Data[3],0.0f,1.0f);
    
    Data[4] = oldAccel[2]*0.4+Data[4]/255.0f*0.6;
    oldAccel[2]=Data[4];
    Data[4] = constrain(Data[4],0.0f,1.0f);
	
	
	
	
	
#ifdef DEBUGnunchuck
	Serial.print("joy:");
	Serial.print(Data[0]);
	Serial.print(",");
	Serial.print(Data[1], DEC);
	Serial.print(" | ");
	
	Serial.print("acc:");
	Serial.print(Data[2], DEC);
	Serial.print(",");
	Serial.print(Data[3], DEC);
	Serial.print(",");
	Serial.print(Data[4], DEC);
	Serial.print(" | ");
	
	Serial.print("but:");
	Serial.print(Data[5], DEC);
	Serial.print(",");
	Serial.print(Data[6], DEC);
#endif
	
#ifdef MaxNchunk
	Serial.print("NX ");
	Serial.println(Data[0], DEC);
	Serial.print("NY ");
	Serial.println(Data[1], DEC);
	
	Serial.print("N1 ");
	Serial.println(Data[2], DEC);
	Serial.print("N2 ");
	Serial.println(Data[3], DEC);
	Serial.print("N3 ");
	Serial.println(Data[4], DEC);
	
	
	Serial.print("B1 ");
	Serial.println(Data[5], DEC);
	Serial.print("B2 ");
	Serial.println(Data[6], DEC);
#endif
}

// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char ADDAC_Nchunk::nunchuk_decode_byte (char x){
	x = (x ^ 0x17) + 0x17;
	return x;
}

void ADDAC_Nchunk::calibrate(){
	CALIBRATING=!CALIBRATING;
}



// --------------------------------------------------------------------------- END ----------------------------------
//

