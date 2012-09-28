/*
 * ADDAC_Logic
 * ag . 08.2011
 *
 
 
 LOGIC CLASS
 
 AND | OR | NOR | XOR | ...
 
 *
 *
 */

#ifndef ADDAC_Logic_h
#define ADDAC_Logic_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif

#define addacMaxResolution 65535 


class ADDAC_Logic{
public:
	ADDAC_Logic();
	
	bool AND(int _val1, int _val2);
	bool AND(bool _val1, bool _val2);
	
	bool OR(int _val1, int _val2);
	bool OR(bool _val1, bool _val2);
//	
//	bool NOT(int _val1, int _val2);
//	bool NOT(bool _val1, bool _val2);
//	
	bool NAND(int _val1, int _val2);
	bool NAND(bool _val1, bool _val2);
	
	bool NOR(int _val1, int _val2);
	bool NOR(bool _val1, bool _val2);
	
	bool XOR(int _val1, int _val2);
	bool XOR(bool _val1, bool _val2);
	
	bool XNOR(int _val1, int _val2);
	bool XNOR(bool _val1, bool _val2);
	
	
};
#endif
