 

#include "ADDAC_Random.h"

 
 


//-----------------------------------------------------------------------ADDAC-----------------
/*! \brief Default constructor for ADDAC_Random. */
ADDAC_Random::ADDAC_Random(){	
	CVstream = 0;
	actualCVstream=0; 
	RandomTime=0; 
	
	fMin=0;
	fMax=2000;
	fSeed=300;
	vMin=0;
	vMax=1.0f;
	
	BROWN = false;
	BROWNTIME = false;
	GateOut= false;
	ClockOut=false;
	TRIGGtime = 30;
	oldRandomTime=millis();
	StepReset = false;
}



// --------------------------------------------------------------------------- RANDOMS MODE -------------------------
//

// RANDOMS
//random voltages between 0.0f & 1.0f
//random frequencies in milliseconds


/*! \brief Standard random uptade - internal clock
 \param _randomMin min random voltage 
 \param _randomMax max random voltage 
 \param _randomFreqMin min time to randomize
 \param _randomFreqMax max time to randomize
 \param _smooth random smooth factor
 */
// Standard Update - Internal Clock
void ADDAC_Random::update(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth){ 
	smooth = _smooth;
	
	CalcRandom( _randomMin,  _randomMax,  _randomFreqMin,  _randomFreqMax,  _smooth);
}


/*! \brief Gated random uptade - external clock
 \param _gate activate random : true or false
 \param _randomMin min random voltage 
 \param _randomMax max random voltage 
 \param _randomFreqMin min time to randomize
 \param _randomFreqMax max time to randomize
 \param _smooth random smooth factor
 */

// Gated Update - External Clock
void ADDAC_Random::update(bool _gate, float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth){ 
	smooth = _smooth;
	Serial.print(" GATED RANDOM UPDATE ");
	if(!_gate){
		CalcGatedRandomUpdate(_smooth);
	}else {
		CalcGatedRandom( _randomMin,  _randomMax,  _randomFreqMin,  _randomFreqMax,  _smooth);
	}
	
}



// SET FUNCTIONS

/*! \activate Brownian Random
 \param brown set - true or false
 */

void ADDAC_Random::setBrownianRandom(bool brown){
	BROWN = brown;
}

/*! \activate Brownian Time
 \param brown set - true or false
 */

void ADDAC_Random::setBrownianTime(bool brown){
	BROWNTIME = brown;
}

/*! \Reset step
 \param _reset set - true or false
 */

void ADDAC_Random::setStepReset(bool _reset){
	StepReset = _reset;
}




	

// PRIVATE FUNCTIONS
void ADDAC_Random::CalcRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth){
	
	if(millis()>RandomDelay+RandomTime){
		//Serial.print(" . next step . ");
		RandomTime=millis();
		oldRandomTime=millis();
		
		if (_randomFreqMax > _randomFreqMin) {
			if(!BROWNTIME) RandomDelay=random(_randomFreqMin,_randomFreqMax);
			else brownianTime(_randomFreqMin,_randomFreqMax);
			//Serial.print(" RNDtime:");
			//Serial.print(RandomDelay);
		}else {
			RandomDelay=_randomFreqMin;
			//Serial.print(" FIXtime:");
			//Serial.print(RandomDelay);
		}
		
		threshold=(_randomMax+_randomMin)/2;
		if(StepReset) oldCVstream=actualCVstream;
		
		if(_randomMax > _randomMin){	
			if(!BROWN){
				//Serial.print(" . standard . ");
				float RND=random(_randomMin*1000.0f,_randomMax*1000.0f)/1000.0f;
				actualCVstream=constrain(RND,0,1);
				/*Serial.print(" RND:");
				Serial.print(RND);
				Serial.print(" Rmin:");
				Serial.print(_randomMin);
				Serial.print(" Rmax:");
				Serial.print(_randomMax);
				Serial.print(" val:");
				Serial.print(RND);
				Serial.print(" stream:");
				Serial.println(actualCVstream);
				*/
			}else if(BROWN){
				//Serial.print(" . brown . ");
				brownian(_randomMin*1000.0f,_randomMax*1000.0f);
				actualCVstream=BrownVal/1000.0f;
			}
		}else{
			//Serial.print(" . brown . ");
			actualCVstream=_randomMin;
		}
		
		// Random GATE Out
		//Serial.println();
		if(oldCVstream>threshold){
			GateOut=true;
		}else{
			GateOut=false;
		}
		
		// Random Clock Out
		if(oldRandomTime+TRIGGtime>millis()){
			//Serial.print(" HIGH!");
			ClockOut=true;
			//oldDACtimes[_channel]=DACtimes[_channel];
		}else{
			//Serial.print(" LOW!");
			ClockOut=false;
		}
		
		CVstream = oldCVstream;
		//Serial.println();
	}else{
		//Serial.print(" . not yet . ");
		oldCVstream=actualCVstream*(1-smooth)+oldCVstream*smooth;//*addacMaxResolution;
		if(oldCVstream>threshold){
			GateOut=true;
		}else{
			GateOut = false;
		}
		
		// Random Clock Out
		if(oldRandomTime+TRIGGtime>millis()){
			//Serial.print(" HIGH!");
			ClockOut=true;
			if(_randomFreqMin<=15)TRIGGtime=5;
			else TRIGGtime=30;
			//oldDACtimes[_channel]=DACtimes[_channel];
		}else{
			//Serial.print(" LOW!");
			ClockOut=false;
		}
		
		CVstream = oldCVstream;
		//Serial.print(" . not yet . ");
		//Serial.println(CVstream);
	}
	
}
	
// RANDOM WITH GATE IN CLOCK
void ADDAC_Random::CalcGatedRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax, float _smooth){
		RandomTime=millis();
		if(BROWNTIME) RandomDelay=random(_randomFreqMax); 
		else brownianTime(0,_randomFreqMax);
		//Serial.print(" Delayed:");
		//Serial.println(RandomDelay);
		GateDelay=true;

		threshold=(_randomMax+_randomMin)/2;
		oldCVstream=actualCVstream;
		if(_randomMax > _randomMin){	
			if(!BROWN){
				float RND=random(_randomMin*1000.0f,_randomMax*1000.0f)/1000.0f;
				actualCVstream=constrain(RND,0,1.0f);
				  Serial.print(" RND:");
					Serial.print(RND);
					Serial.print(" val:");
					Serial.print(actualCVstream);
				
			}else if(BROWN){
				brownian(_randomMin, _randomMax);
				actualCVstream=BrownVal;
			}
		}else{
			actualCVstream=_randomMin;
		}
		
	
	
	if(millis()>RandomDelay+RandomTime){
		GateDelay=false;
		if(oldCVstream>threshold){
			GateOut=true;
		}else{
			GateOut=false;
		}
		oldCVstream=actualCVstream*(1-smooth)+oldCVstream*smooth; //  - AQUI ESTA O SMOOTHHH ??????????????????????? não estava antes!!
		CVstream = oldCVstream;
	}
	Serial.print(" Gated:");
	Serial.print(CVstream);
}

// RANDOM GATE UPDATE
void ADDAC_Random::CalcGatedRandomUpdate(float _smooth){
	smooth = _smooth;
	if(GateDelay){
		/*  Serial.print("GATED -> WAITING FOR DELAY END");
			Serial.print(" millis:");
			Serial.print(millis());
			Serial.print(" to:");
			Serial.print(RandomDelay+RandomTime);
			Serial.print(" gate:");
			Serial.print(GateDelay);
		*/
		if(millis()>RandomDelay+RandomTime && GateDelay){
			GateDelay=false;
		}
	}else {
		oldCVstream=actualCVstream*(1-smooth)+oldCVstream*smooth;//*addacMaxResolution;
			/*  Serial.print("smooth:");
				Serial.print(smooth);
				Serial.print("  actualVal:");
				Serial.print(oldCVstream);
				Serial.print("  goTo:");
				Serial.print(actualCVstream);
			*/
		if(oldCVstream>threshold){
			GateOut=true;
		}else{
			GateOut=false;
		}
		CVstream = oldCVstream;
	}
	Serial.print(" Update:");
	Serial.print(CVstream);
}



// MATHS

void ADDAC_Random::CalcNormalRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax){
	if(_randomMax > _randomMin){	
		actualCVstream=constrain(random(_randomMin,_randomMax),0,1.0f);;
	}else{
		actualCVstream=_randomMin;
	}
}

void ADDAC_Random::CalcBrownianRandom(float _randomMin, float _randomMax, int _randomFreqMin, int _randomFreqMax){
		if(_randomMax > _randomMin){	
			actualCVstream=BrownVal;
		}else{
			actualCVstream=_randomMin;
		}		
}

void ADDAC_Random::brownian(float _randomMin, float _randomMax){
	// Put a new value at the end of the array
	int _range=(_randomMax-_randomMin)/6;
	int r=random(_range)-_range/2;
	if(BrownVal+r>=0){
		BrownVal += r ;
	}else{
		BrownVal = 0 ;
	}
	// Constrain all points to the screen
	//BrownVal = BrownVal;
}
void ADDAC_Random::brownianTime(float _randomMin, float _randomMax){
	// Put a new value at the end of the array
	int _range=(_randomMax-_randomMin)/6;
	int r=random(_range)-_range/2;
	if(RandomDelay+r>=0){
		RandomDelay += r ;
	}else{
		RandomDelay = 0 ;
	}
	// Constrain all points to the screen
	RandomDelay = constrain(RandomDelay, _randomMin, _randomMax);
}





// --------------------------------------------------------------------------- END ----------------------------------
//

