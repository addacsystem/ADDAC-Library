 
/*
 * ADDAC_Logic
 *
*/


#include "ADDAC_Logic.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------

ADDAC_Logic::ADDAC_Logic(){	// INITIALIZE CLASS
	//Serial.println("ADDAC_Logic INITIALIZED");
}



// --------------------------------------------------------------------------- AND -------------------------
//


bool ADDAC_Logic::AND(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return true;
	}else{
		return false;
	}
	
}

bool ADDAC_Logic::AND(bool _val1, bool _val2){ // DO SOMETHING !
	if (_val1 && _val2) {
		return true;
	}else{
		return false;
	}
	
}

// --------------------------------------------------------------------------- OR -------------------------
//


bool ADDAC_Logic::OR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 0 && _val2 ==0) {
		return false;
	}else{
		return true;
	}
	
}

bool ADDAC_Logic::OR(bool _val1, bool _val2){ // DO SOMETHING !
	if (!_val1 && !_val2) {
		return false;
	}else{
		return true;
	}
	
}


// --------------------------------------------------------------------------- NAND -------------------------
//


bool ADDAC_Logic::NAND(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return false;
	}else{
		return true;
	}
	
}

bool ADDAC_Logic::NAND(bool _val1, bool _val2){ // DO SOMETHING !
	if (_val1 && _val2) {
		return false;
	}else{
		return true;
	}
	
}


// --------------------------------------------------------------------------- NOR -------------------------
//


bool ADDAC_Logic::NOR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 0 && _val2 ==0) {
		return true;
	}else{
		return false;
	}
	
}

bool ADDAC_Logic::NOR(bool _val1, bool _val2){ // DO SOMETHING !
	if (!_val1 && !_val2) {
		return true;
	}else{
		return false;
	}
	
}

// --------------------------------------------------------------------------- XOR -------------------------
//


bool ADDAC_Logic::XOR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return false;
	}else if(_val1 ==0  && _val2 ==0){
		return false;
	}else{
		return true;
	}
	
}

bool ADDAC_Logic::XOR(bool _val1, bool _val2){ // DO SOMETHING !
	if (_val1 && _val2){
		return false;
	}else if (!_val1 && !_val2) {
		return false;
	}else{
		return true;
	}
	
}


// --------------------------------------------------------------------------- XNOR -------------------------
//


bool ADDAC_Logic::XNOR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return true;
	}else if(_val1 ==0  && _val2 ==0){
		return true;
	}else{
		return false;
	}
	
}

bool ADDAC_Logic::XNOR(bool _val1, bool _val2){ // DO SOMETHING !
	if (_val1 && _val2){
		return true;
	}else if (!_val1 && !_val2) {
		return true;
	}else{
		return false;
	}
	
}



// --------------------------------------------------------------------------- END ----------------------------------
//