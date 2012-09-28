 

#include "ADDAC_Quantizer.h"

//-----------------------------------------------------------------------ADDAC-----------------
/*! \brief Default constructor for ADDAC_Quantizer. */
ADDAC_Quantizer::ADDAC_Quantizer(){	
	
	// NOTES ACTIVE IN CHROMATIC SCALE
	NOTESactive[0]	=1; //	C3
	NOTESactive[1]	=0; //	C#3
	NOTESactive[2]	=1;	//	D3
	NOTESactive[3]	=0; //	D#3
	NOTESactive[4]	=0; //	E3
	NOTESactive[5]	=1; //	F3
	NOTESactive[6]	=0; //	F#3
	NOTESactive[7]	=1; //	G3
	NOTESactive[8]	=0; //	G#3
	NOTESactive[9]	=1; //	A3
	NOTESactive[10]	=0; //	A#3
	NOTESactive[11]	=0; //	B3
	NOTESactive[12]	=1; //	C4
	NOTESactive[13]	=0; //	C#4
	NOTESactive[14]	=1; //	D4
	NOTESactive[15]	=0; //	D#4
	NOTESactive[16]	=0; //	E4
	NOTESactive[17]	=1; //	F4
	NOTESactive[18]	=0; //	F#4
	NOTESactive[19]	=1; //	G4
	NOTESactive[20]	=0; //	G#4
	NOTESactive[21]	=1; //	A4
	NOTESactive[22]	=0; //	A#4
	NOTESactive[23]	=0; //	B4
	NOTESactive[24]	=1; //	C5
	NOTESactive[25]	=0; //	C#5
	NOTESactive[26]	=1; //	D5
	NOTESactive[27]	=0; //	D#5
	NOTESactive[28]	=0; //	E5
	NOTESactive[29]	=1; //	F5
	NOTESactive[30]	=0; //	F#5
	NOTESactive[31]	=1; //	G5
	NOTESactive[32]	=0; //	G#5
	NOTESactive[33]	=1; //	A5
	NOTESactive[34]	=0; //	A#5
	NOTESactive[35]	=0; //	B5
	NOTESactive[36]	=1; //	C6
	NOTESactive[37]	=0; //	C#6
	NOTESactive[38]	=1; //	D6
	NOTESactive[39]	=0; //	D#6
	NOTESactive[40]	=0; //	E6
	NOTESactive[41]	=1; //	F6
	NOTESactive[42]	=0; //	F#6
	NOTESactive[43]	=1; //	G6
	NOTESactive[44]	=0; //	G#6
	NOTESactive[45]	=1; //	A6
	NOTESactive[46]	=0; //	A#6
	NOTESactive[47]	=0; //	B6
	NOTESactive[48]	=1; //	C7
	NOTESactive[49]	=0; //	C#7
	NOTESactive[50]	=1; //	D7
	NOTESactive[51]	=0; //	D#7
	NOTESactive[52]	=0; //	E7
	NOTESactive[53]	=1; //	F7
	NOTESactive[54]	=0; //	F#7
	NOTESactive[55]	=1; //	G7
	NOTESactive[56]	=0; //	G#7
	NOTESactive[57]	=1; //	A7
	NOTESactive[58]	=0; //	A#7
	NOTESactive[59]	=0; //	B7
	NOTESactive[60]	=1; //	C8
	
	//NOTES ACTIVE IN PENTATONIC SCALE
	/*
	NOTESactive[0]	=1; //	C3
	NOTESactive[1]	=0; //	C#3
	NOTESactive[2]	=1;	//	D3
	NOTESactive[3]	=0; //	D#3
	NOTESactive[4]	=0; //	E3
	NOTESactive[5]	=1; //	F3
	NOTESactive[6]	=0; //	F#3
	NOTESactive[7]	=1; //	G3
	NOTESactive[8]	=0; //	G#3
	NOTESactive[9]	=0; //	A3
	NOTESactive[10]	=1; //	A#3
	NOTESactive[11]	=0; //	B3
	NOTESactive[12]	=1; //	C4
	NOTESactive[13]	=0; //	C#4
	NOTESactive[14]	=1; //	D4
	NOTESactive[15]	=0; //	D#4
	NOTESactive[16]	=0; //	E4
	NOTESactive[17]	=1; //	F4
	NOTESactive[18]	=0; //	F#4
	NOTESactive[19]	=1; //	G4
	NOTESactive[20]	=0; //	G#4
	NOTESactive[21]	=0; //	A4
	NOTESactive[22]	=1; //	A#4
	NOTESactive[23]	=0; //	B4
	NOTESactive[24]	=1; //	C5
	NOTESactive[25]	=0; //	C#5
	NOTESactive[26]	=1; //	D5
	NOTESactive[27]	=0; //	D#5
	NOTESactive[28]	=0; //	E5
	NOTESactive[29]	=1; //	F5
	NOTESactive[30]	=0; //	F#5
	NOTESactive[31]	=1; //	G5
	NOTESactive[32]	=0; //	G#5
	NOTESactive[33]	=0; //	A5
	NOTESactive[34]	=1; //	A#5
	NOTESactive[35]	=0; //	B5
	NOTESactive[36]	=1; //	C6
	NOTESactive[37]	=0; //	C#6
	NOTESactive[38]	=1; //	D6
	NOTESactive[39]	=0; //	D#6
	NOTESactive[40]	=0; //	E6
	NOTESactive[41]	=1; //	F6
	NOTESactive[42]	=0; //	F#6
	NOTESactive[43]	=0; //	G6
	NOTESactive[44]	=0; //	G#6
	NOTESactive[45]	=0; //	A6
	NOTESactive[46]	=1; //	A#6
	NOTESactive[47]	=0; //	B6
	NOTESactive[48]	=0; //	C7
	NOTESactive[49]	=0; //	C#7
	NOTESactive[50]	=1; //	D7
	NOTESactive[51]	=0; //	D#7
	NOTESactive[52]	=0; //	E7
	NOTESactive[53]	=1; //	F7
	NOTESactive[54]	=0; //	F#7
	NOTESactive[55]	=1; //	G7
	NOTESactive[56]	=0; //	G#7
	NOTESactive[57]	=0; //	A7
	NOTESactive[58]	=1; //	A#7
	NOTESactive[59]	=0; //	B7
	NOTESactive[60]	=0; //	C8
	 */
	
    /*
	// OLD C PENTATONIC FIXED VALUES      !! / by 1000.0f !!
	NOTES[0]=1178;
	NOTES[1]=3617;
	NOTES[2]=7257;
	NOTES[3]=9673;
	NOTES[4]=12088;
	NOTES[5]=15731;
	NOTES[6]=18159;
	NOTES[7]=21786;
	NOTES[8]=24217;
	NOTES[9]=26638;
	NOTES[10]=30267;
	NOTES[11]=32688;
	NOTES[12]=36321;
	NOTES[13]=38745;
	NOTES[14]=41175;
	NOTES[15]=44808;
	NOTES[16]=47241;
	NOTES[17]=50866;
	NOTES[18]=53294;
	NOTES[19]=55711;
	NOTES[20]=59348;
	NOTES[21]=61768;
	NOTES[22]=65406;
	*/
	interval=0.016666667;//1.13;// 65535 / 58 (weird number? voltage reg deviation?)     --  //1.09225;//1.213;
	offset=0;//1.178;
	
	for( int i=0; i<128; i++){
		NOTES[i] = interval * i + offset;
	}
	Serial.println("ADDAC_Quantizer INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief quantize a voltage to the nearest note
 \param _val voltage to quantize
 */
float ADDAC_Quantizer::calc(float _val){
	for (int i=0; i<61; i++) {
		if (_val<=NOTES[i]) { // GETS CLOSEST NOTE BELOW!!
			if(NOTESactive[i]){
				if (NOTES[i-1]<0.02) {
					return 0;
				}else {
					return NOTES[i];
				}
				break;
			}
		}
	}
}


float ADDAC_Quantizer::Note(int _midiVal){
	return NOTES[_midiVal];
}

/*! \Quantization with X v/oct. For example, this is very useful to reach compatibility with Buchla 1.2v/oct standard
 \param _val voltage to quantize
 \param _partial partial value for quantization
 */
float ADDAC_Quantizer::Note(int _val, double _partial){
	for( int i=0; i<128; i++){
		NOTES[i] = _partial * i + offset;
	}
	return NOTES[_val]*1000.0f;
	
}

// --------------------------------------------------------------------------- END ----------------------------------
//