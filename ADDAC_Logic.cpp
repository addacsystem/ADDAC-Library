 
/*
 * ADDAC_Logic
 *
*/


#include "ADDAC_Logic.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------
/*! \brief Default construtor for ADDAC_Logic */
ADDAC_Logic::ADDAC_Logic(){	// INITIALIZE CLASS
	//Serial.println("ADDAC_Logic INITIALIZED");
}



// --------------------------------------------------------------------------- AND -------------------------
//


/*! \brief return true if input1 and input2 are both true  
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::AND(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return true;
	}else{
		return false;
	}
	
}

/*! \brief return true if input1 and input2 are both true  
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::AND(bool _val1, bool _val2){ // DO SOMETHING !
	if (_val1 && _val2) {
		return true;
	}else{
		return false;
	}
	
}

// --------------------------------------------------------------------------- OR -------------------------
//

/*! \brief return true if input1 or input2 are true  
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::OR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 0 && _val2 ==0) {
		return false;
	}else{
		return true;
	}
	
}

/*! \brief return true if input1 or input2 is true  
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::OR(bool _val1, bool _val2){ // DO SOMETHING !
	if (!_val1 && !_val2) {
		return false;
	}else{
		return true;
	}
	
}


// --------------------------------------------------------------------------- NAND -------------------------
//

/*! \brief return false if input1 and input2 are true  
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::NAND(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return false;
	}else{
		return true;
	}
	
}

/*! \brief return false if input1 and input2 are true  
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::NAND(bool _val1, bool _val2){ // DO SOMETHING !
	if (_val1 && _val2) {
		return false;
	}else{
		return true;
	}
	
}


// --------------------------------------------------------------------------- NOR -------------------------
//

/*! \brief Returns True if both input1 and input2 are False
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::NOR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 0 && _val2 ==0) {
		return true;
	}else{
		return false;
	}
	
}

/*! \brief Returns True if both input1 and input2 are False
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::NOR(bool _val1, bool _val2){ // DO SOMETHING !
	if (!_val1 && !_val2) {
		return true;
	}else{
		return false;
	}
	
}

// --------------------------------------------------------------------------- XOR -------------------------
//

/*! \brief Returns True if any of input1 or input2 is True. If both are True or both are false it returns False 
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::XOR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return false;
	}else if(_val1 ==0  && _val2 ==0){
		return false;
	}else{
		return true;
	}
	
}
/*! \brief Returns True if any of input1 or input2 is True. If both are True or both are false it returns False 
 \param _val1 input 1
 \param _val2 input 2
 */
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
/*! \brief Returns True if both of input1 or input2 are True or False.
 \param _val1 input 1
 \param _val2 input 2
 */
bool ADDAC_Logic::XNOR(int _val1, int _val2){ // DO SOMETHING !
	if (_val1 == 1 && _val2 ==1) {
		return true;
	}else if(_val1 ==0  && _val2 ==0){
		return true;
	}else{
		return false;
	}
	
}

/*! \brief Returns True if both of input1 or input2 are True or False.
 \param _val1 input 1
 \param _val2 input 2
 */
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