/*
 * ADDA_CVrec buffer
 * Version 0.1 October, 2010
 * Copyright 2010 André Gonçalves
 * For details, see http://
 *
 * AD5668 programming based on
 * DAC V11 by Robin Price 2009
 +
 * shiftIn Example 2.1 by Carlyn Maw 
 */

#ifndef ADDAC_CVbuffer_h
#define ADDAC_CVbuffer_h


class ADDAC_CVbuffer{
public:
	ADDAC_CVbuffer();
	void write(int index, int val);
	int read(int index);
	
	int vals[256];
};

#endif
