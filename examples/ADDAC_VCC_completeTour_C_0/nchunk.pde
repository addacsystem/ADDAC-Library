
#ifdef NCHUNK
  
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

void nunchuck_init()
{ 
  Wire.begin();	                // join i2c bus as master
  Wire.beginTransmission(0x52);	// transmit to device 0x52
  Wire.send(0x40);		// sends memory address
  Wire.send(0x00);		// sends sent a zero.  
  Wire.endTransmission();	// stop transmitting
}

// Send a request for data to the nunchuck
// was "send_zero()"
void nunchuck_send_request()
{
  Wire.beginTransmission(0x52);	// transmit to device 0x52
  Wire.send(0x00);		// sends one byte
  Wire.endTransmission();	// stop transmitting
}

// Receive data back from the nunchuck, 
int nunchuck_get_data()
{
    int cnt=0;
    Wire.requestFrom (0x52, 6);	// request data from nunchuck
    while (Wire.available ()) {
      // receive byte as an integer
      nunchuck_buf[cnt] = nunchuk_decode_byte(Wire.receive());
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
void nunchuck_parse_data()
{ 
   joy_x_axis = nunchuck_buf[0];
  joy_y_axis = nunchuck_buf[1];
  accel_x_axis = nunchuck_buf[2]; // * 2 * 2; 
  accel_y_axis = nunchuck_buf[3]; // * 2 * 2;
  accel_z_axis = nunchuck_buf[4]; // * 2 * 2;

  z_button = 1;
  c_button = 1;

  // byte nunchuck_buf[5] contains bits for z and c buttons
  // it also contains the least significant bits for the accelerometer data
  // so we have to check each bit of byte outbuf[5]
  if ((nunchuck_buf[5] >> 0) & 1) 
    z_button = 0;
  if ((nunchuck_buf[5] >> 1) & 1)
    c_button = 0;

  if ((nunchuck_buf[5] >> 2) & 1) 
    accel_x_axis += 2;
  if ((nunchuck_buf[5] >> 3) & 1)
    accel_x_axis += 1;

  if ((nunchuck_buf[5] >> 4) & 1)
    accel_y_axis += 2;
  if ((nunchuck_buf[5] >> 5) & 1)
    accel_y_axis += 1;

  if ((nunchuck_buf[5] >> 6) & 1)
    accel_z_axis += 2;
  if ((nunchuck_buf[5] >> 7) & 1)
    accel_z_axis += 1;
    
 #ifdef DEBUGnunchuck
  Serial.print("joy:");
  Serial.print(joy_x_axis);
  Serial.print(",");
  Serial.print(joy_y_axis, DEC);
  Serial.print(" | ");

  Serial.print("acc:");
  Serial.print(accel_x_axis, DEC);
  Serial.print(",");
  Serial.print(accel_y_axis, DEC);
  Serial.print(",");
  Serial.print(accel_z_axis, DEC);
  Serial.print(" | ");

  Serial.print("but:");
  Serial.print(z_button, DEC);
  Serial.print(",");
  Serial.print(c_button, DEC);
 #endif

 #ifdef MaxNchunk
  Serial.print("NX ");
  Serial.println(joy_x_axis, DEC);
  Serial.print("NY ");
  Serial.println(joy_y_axis, DEC);

  Serial.print("N1 ");
  Serial.println(accel_x_axis, DEC);
  Serial.print("N2 ");
  Serial.println(accel_y_axis, DEC);
  Serial.print("N3 ");
  Serial.println(accel_z_axis, DEC);


  Serial.print("B1 ");
  Serial.println(z_button, DEC);
  Serial.print("B2 ");
  Serial.println(c_button, DEC);
 #endif
}

// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char nunchuk_decode_byte (char x)
{
  x = (x ^ 0x17) + 0x17;
  return x;
}





//




void NUNwrite(){

    joy_x_axis = map(joy_x_axis,30,241,0,255);
    ADDAC.WriteChannel(1, joy_x_axis/255.0f*addacMaxResolution);
    
    joy_y_axis = map(joy_y_axis,30,241,0,255);
    ADDAC.WriteChannel(2, joy_y_axis/255.0f*addacMaxResolution);
    
    
    accel_x_axis = oldAccel_x_axis*0.8+accel_x_axis*0.2;
    oldAccel_x_axis=accel_x_axis;
    accel_x_axis=constrain(accel_x_axis,0,255);
    ADDAC.WriteChannel(3, accel_x_axis/255.0f*addacMaxResolution);
    
    accel_y_axis = oldAccel_y_axis*0.8+accel_y_axis*0.2;
    oldAccel_y_axis=accel_y_axis;
    accel_y_axis = constrain(accel_y_axis,0,255);
    ADDAC.WriteChannel(4, accel_y_axis/255.0f*addacMaxResolution);
    
    accel_z_axis = oldAccel_z_axis*0.4+accel_z_axis*0.6;
    oldAccel_z_axis=accel_z_axis;
    accel_z_axis = constrain(accel_z_axis,0,255);
    ADDAC.WriteChannel(5, accel_z_axis/255.0f*addacMaxResolution);
    
    ADDAC.WriteChannel(6, c_button*addacMaxResolution);
    
    ADDAC.WriteChannel(7, z_button*addacMaxResolution);

    ADDAC.mixerMode(5);
}

#endif
