 
/*
 * Some hints about what this Class does!
 *
*/


#include "ADDAC_LFO.h"

//-----------------------------------------------------------------------ADDAC EMPTY-----------------
/*! \brief Default construtor for ADDAC_ADSR */
ADDAC_LFO::ADDAC_LFO(){	// INITIALIZE CLASS
	
	position=0;
	//Serial.println("ADDAC_LFO INITIALIZED");
}



// --------------------------------------------------------------------------- UPDATE -------------------------
//

/*! \brief update LFO
 \param _freq LFO frequency value : 0.0f - 1.0f */
void ADDAC_LFO::update(float _freq){ // FREQUENCY DEFINED BY INCREMENT SIZE : 0.0f to 1.0f
	
    position += (exp(4.0f*_freq)-1.0f)/62.0f; // exponential equation to adjust speed with more control (?), need testing!
}



// --------------------------------------------------------------------------- SIN -------------------------
//


// float _freq (increment (0.0-1.0)

void ADDAC_LFO::SINupdate(){
    SINval = (sin(position)+1.0f)/2.0f;
    SIN = SINval;
}

unsigned int ADDAC_LFO::SINget(){
    SINval = (sin(position)+1.0f)/2.0f;
    SIN = SINval;
    return SINval;
}


// --------------------------------------------------------------------------- SIN MODE -------------------------
//
//int _channel (1-8), bool _inverted (0=no - 1=yes) 
//float _freq (hertz (0.0-20000.0), float _bottom (percentage 0-1), float _top (percentage 0-1)

/*! \brief update SINE WAVE
 \param _inverted invert SINE : true or false
 \param _freq SINE frequency
 \param _mult frequency multiply
 \param _offset SINE offset
 \param _bottom bottom Level
 \param _top top Level
 */
void ADDAC_LFO::SINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top){
	// EQUATION
	//y=(s*cos(freq*x+offset)+a)*addacMax; freq=100; T=0.8; B=0.2; S=T-B; I=1; Offset=0.5, invert=0; offset=Offset+invert/2*2¹; s=S/2, a=s+B

	_freq+=10;
	_mult+=1;
	float _dif = (_top - _bottom);
	_bottom = addacMaxResolution *_bottom;
	if(!_inverted){ // normal
		CVstream= (_bottom+(sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) *_dif + _offset)/addacMaxResolution;
	}else{ // inverted
		CVstream= (_bottom+(sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f)*_dif + _offset)/addacMaxResolution;
	}
    
    stream = CVstream / addacMaxResolution;
    
    if (stream>1){
        stream=1;
    }
    if(stream<0){
        stream=0;
    }
   
}

/*! \brief update SINE WAVE
 \param _inverted invert SINE : true or false
 \param _freq SINE frequency
 \param _mult frequency multiply
 \param _offset SINE offset
 */
void ADDAC_LFO::SINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset){
	_freq+=10;
	_mult+=1;
	if(!_inverted){ // normal
		CVstream= ((sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) + _offset)/addacMaxResolution;
	}else{ // inverted
		CVstream= ((sin(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f) + _offset)/addacMaxResolution;
	}
	
    stream = CVstream / addacMaxResolution;
    
    if (stream>1){
        stream=1;
    }
    if(stream<0){
        stream=0;
    }
    
    
}
// --------------------------------------------------------------------------- COSIN MODE -------------------------
//
//int _channel (1-8), bool _inverted (0=no - 1=yes) 
//float _freq (hertz (0.0-20000.0), int _bottom (percentage 0-100%), int _top (percentage 0-100%)


/*! \brief update COSINE WAVE
 \param _inverted invert COSINE : true or false
 \param _freq COSINE frequency
 \param _mult frequency multiply
 \param _offset COSINE offset
 \param _bottom bottom Level
 \param _top top Level
 */
void ADDAC_LFO::COSINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top){
	_freq+=10;
	_mult+=1;
	float _dif = _top - _bottom;
	_bottom = addacMaxResolution *_bottom;
	if(!_inverted){ // normal
		CVstream= (_bottom + (cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) * _dif + _offset)/addacMaxResolution;
	}else{ // inverted
		CVstream= (_bottom + (cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f) * _dif + _offset)/addacMaxResolution;
	}
    
    
    stream = CVstream / addacMaxResolution;
    
    if (stream>1){
        stream=1;
    }
    if(stream<0){
        stream=0;
    }

	
}

/*! \brief update COSINE WAVE
 \param _inverted invert COSINE : true or false
 \param _freq COSINE frequency
 \param _mult frequency multiply
 \param _offset COSINE offset
 */
void ADDAC_LFO::COSINupdate(bool _inverted, float _freq, float _mult, unsigned int _offset){
	_freq+=10;
	_mult+=1;
	if(!_inverted){ // normal
		CVstream= ((cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))+1.0f)*(addacMaxResolution/2.0f) + _offset)/addacMaxResolution;
	}else{ // inverted
		CVstream= ((cos(TWO_PI*(millis()%int(_freq*_mult)/(_freq*_mult)))*-1.0f+1.0f)*(addacMaxResolution/2.0f) + _offset)/addacMaxResolution;
	}
    
    stream = CVstream / addacMaxResolution;
    
    if (stream>1){
        stream=1;
    }
    if(stream<0){
        stream=0;
    }

}

// --------------------------------------------------------------------------- LFOS MODE ----------------------------
//
void ADDAC_LFO::lfosMode(int _MODE, int _type, int _channel){
	/*ReadAnalogsA();
	if(_MODE==0){ // UPDATE ALL CHANNELS
		if(_type==0){ // TRIANGLE   -   still buggy!!  passar para unsigned long??
			int inc=1.0f*(analogValuesA[0]*16.0f+1.0f);
			for(int i=0; i<8;i++){
				if(direction[i]){
					DACvolts[i]+=inc;
					if(DACvolts[i]>=analogValuesAMapped[2]){ //analogValuesA[2] = MAX
						DACvolts[i]=analogValuesAMapped[2];
						direction[i]=false;
					}
				}else{
					DACvolts[i]-=inc;
					if(DACvolts[i]<=analogValuesAMapped[1]){ //analogValuesA[1] = MIN
						DACvolts[i]=analogValuesAMapped[1];
						direction[i]=true;
					}
				}
				writeChannel(i,DACvolts[i]);
			}
		}else if(_type==1){ // BUGGY TRIANGLE   -   still buggy!!  passar para unsigned long??
            int inc=1.0f*(analogValuesA[0]*16.0f+1.0f);
            for(int i=0; i<8;i++){
                if(Direction){
                    DACvolts[i]+=inc;
                    if(DACvolts[i]>=analogValuesAMapped[2]){ //analogValuesA[2] = MAX
                        DACvolts[i]=analogValuesAMapped[2];
                        Direction=false;
                    }
                }else{
                    DACvolts[i]-=inc;
                    if(DACvolts[i]<=analogValuesAMapped[1]){ //analogValuesA[1] = MIN
                        DACvolts[i]=analogValuesAMapped[1];
                        Direction=true;
                    }
                }
                writeChannel(i,DACvolts[i]);
            }
		}else if(_type==2){ // SAW
			int inc=1.0f*(analogValuesA[0]*8.0f+1.0f);
			for(int i=0; i<8;i++){
				DACvolts[i]+=inc;
				if(DACvolts[i]+inc>=analogValuesAMapped[2] || DACvolts[i]<analogValuesAMapped[1]){ //analogValuesA[2] = MAX
					DACvolts[i]=analogValuesAMapped[1]; //analogValuesA[1] = MIN
				}
				writeChannel(i,DACvolts[i]);
			}
		}else if(_type==3){ // INVERTED SAW
			int inc=1.0f*(analogValuesA[0]*8.0f+1.0f);
			for(int i=0; i<8;i++){
				DACvolts[i]-=inc;
				if(DACvolts[i]-inc<=analogValuesAMapped[1] || DACvolts[i]-inc>analogValuesAMapped[2]){ //analogValuesA[2] = MAX
					DACvolts[i]=analogValuesAMapped[2]; //analogValuesA[1] = MIN
				}
				writeChannel(i,DACvolts[i]);
				if(i==0){
					Serial.print("inc:");
					Serial.print(inc);
					Serial.print(" Max:");
					Serial.print(analogValuesAMapped[1]);
					Serial.print(" Min:");
					Serial.print(analogValuesAMapped[2]);
					Serial.print(" DAC:");
					Serial.println(DACvolts[i]);
				}
			}
		}else if(_type==4){ // RND RAMPS
			int inc=1.0f*(analogValuesA[0]*16.0f+1.0f);
			for(int i=0; i<8;i++){
				if(DACvolts[i]==rndStep[i]){
					rndStep[i]=random(analogValuesAMapped[1],analogValuesAMapped[2]);
				}
				if(DACvolts[i]>rndStep[i]){
					direction[i]=false;
				}else{
					direction[i]=true;
				}
				if(direction[i]){
					DACvolts[i]+=inc;
					if(DACvolts[i]>=rndStep[i]){ //analogValuesA[2] = MAX
						DACvolts[i]=rndStep[i];
					}
				}else{
					DACvolts[i]-=inc;
					if(DACvolts[i]<=rndStep[i]){ //analogValuesA[1] = MIN
						DACvolts[i]=rndStep[i];
					}
				}
				writeChannel(i,DACvolts[i]);
			}
		}
	}else if(_MODE==1){ // UPDATE INDIVIDUAL CHANNELS
		DACvolts[_channel]+=1*(analogValuesA[0]+1);
		writeChannel(_channel,DACvolts[_channel]);
	}*/
	
	/*Serial.print("inc:");
     Serial.print(inc);
     Serial.print(" AN1");
     Serial.print(analogValuesAMapped[1]);
     Serial.print(" AN2");
     Serial.print(analogValuesAMapped[2]);
     Serial.print(" step:");
     Serial.print(rndStep[0]);
     Serial.print(" DAC:");
     Serial.print(DACvolts[0]);
     Serial.println();*/
}
// --------------------------------------------------------------------------- END ----------------------------------
//