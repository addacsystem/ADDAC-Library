/*
 * ADDA5664
 * Version 0.1 November, 2009
 * Copyright 2009 AndrŽ Gonalves
 * For details, see http://
 *
 * AD5668 programming based on
 * DAC V11 by Robin Price 2009
 +
 * shiftIn Example 2.1 by Carlyn Maw 
 */

#ifndef ADDAC_Nchunk_h
#define ADDAC_Nchunk_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif



#include <Wire.h>



class ADDAC_Nchunk{
public:
	ADDAC_Nchunk();

	int calibrationTopX;	
	int calibrationBottomX;
	int calibrationTopY;	
	int calibrationBottomY;

	uint8_t nunchuck_buf[6];   // array to store nunchuck data,
    /*! \Nchunk data
        \param Data[0] -  Joystick X position
        \param Data[1] -  Joystick Y position
        \param Data[2] -  Accelerometer X position
        \param Data[3] -  Accelerometer Y position
        \param Data[4] -  Accelerometer Z position
        \param Data[5] -  Button C
        \param Data[6] -  Button C
     */
	float Data[7];
	float oldAccel[3];
	bool CALIBRATING;
	
	void setup(int _calibrationBottomX, int _calibrationTopX, int _calibrationBottomY, int _calibrationTopY);
	void setup();
	void update();
	
	void nunchuck_init();
	void nunchuck_send_request();
	int nunchuck_get_data();
	void nunchuck_parse_data();
	char nunchuk_decode_byte (char x);
	void NUNupdate();
	void calibrate();
	
};


#endif
