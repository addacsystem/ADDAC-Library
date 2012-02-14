
/*

VCC BEHAVIOUR

WHERE IT ALL GETS ROLLIN'

*/



void BEHAVIOUR(){
// MODES DEFINITION
// --------------------------------------------------------------------------------------------------------------------------- MODE 0 -----------
//
  if(VCC.MODE==0){  //  MODE 0 has several test/debug functions for the available functions and modules
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 0 -----------
    //
    if(VCC.SUBMODE==0){
      for(int i=0;i<8;i++){
          VCC.WriteChannel(i+1, random(1023)/1023.0f*addacMaxResolution);
      }
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 1 -----------
    //
    }else if(VCC.SUBMODE==1){ // MIDI CC TEST with RANDOM Function
      for(int i=0;i<3;i++){
        VCC.randomModeSmoothed(i, controlChangeVal[0]/127.0f*65535, controlChangeVal[1]/127.0f*65535, controlChangeVal[2]*5, controlChangeVal[3]*10,controlChangeVal[4]/127.0f);
      }
      for(int i=3;i<6;i++){
        VCC.randomModeSmoothed(i, controlChangeVal[8]/127.0f*65535, controlChangeVal[9]/127.0f*65535, controlChangeVal[10]*5, controlChangeVal[11]*10,controlChangeVal[12]/127.0f);
      }
      for(int i=6;i<8;i++){
        VCC.randomModeSmoothed(i, controlChangeVal[5]/127.0f*65535, controlChangeVal[6]/127.0f*65535, controlChangeVal[13]*5, controlChangeVal[14]*10,controlChangeVal[15]/127.0f);
      }
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 2 -----------
    //
    }else if(VCC.SUBMODE==2){ // ADDAC002 - CV IN TEST 
      readCvsINA(6);
      readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
      // int _channel (1-8), bool inverted (0=no - 1=yes), float freq (0-255), float mult (0-30), unsigned int offset (0-addacMaxResolution)  
    // XTRA 2 VALS: int _bottom (percentage 0-100%), int _top (percentage 0-100%)
     // VCC.WriteChannel(1, cvValsA[0]/1023.0f*addacMaxResolution);
      
      // ADDING AN LFO TO COMPARE IN/OUT...
      //LFO1.update(analogValsA[0]/1023.0f);
      //LFO1.SINupdate(); 
      //VCC.WriteChannel(1, LFO1.SIN);
      //VCC.WriteChannel(8, addacMaxResolution-LFO1.SIN); // inverted SIN - easy as pie!
       
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 3 -----------
    //
    }else if(VCC.SUBMODE==3){ //  ADDAC004 & ADDAC005 - GATES IN/OUT TEST    ->   * NEW METHOD!!    + LOGIC & CLOCK EXAMPLE!
    
       readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels

      // WRITES RANDOMLY TO GATE OUTPUTS 
      for(int i=0; i<8;i++){
        VCC.WriteGatesAstraight(i, int(random(2)));
        VCC.WriteGatesBstraight(i, int(random(2)));
      } 
      
      // READS FROM GATE INPUTS
      // "VCC.ReadGatesA(bool _invert)"  MAKES VCC READ ALL GATE INPUTS in SLOT A 
      // BOOLEAN PARAMETER IS THE INVERTING/NON-INVERTING SETTING
      // (ALSO USEFULL TO CORRECT CIRCUIT "BUG" WITH INVERTED READINGS FROM ADDAC004) 
      VCC.ReadGatesA(true); // Boolean Parameter sets inverting read setting  -> true:inverting, false:non-inverting
      for(int i=0; i<8;i++){
        #ifdef DEBUGgateINA
          Serial.print(VCC.gateValuesA[i],BIN); // THIS IS HOW TO ACCESS EACH CHANNEL INDEPENDENTLY i.e. accessing the array value straight from the VCC Class
          Serial.print(" : ");
        #endif
        // SIMPLE INPUT VISUALIZER - sends each GATE Input to a CV Output 
        if(VCC.gateValuesA[i]) VCC.WriteChannel(i+1, addacMaxResolution);
        else VCC.WriteChannel(i+1, 0);
        
        
        // THIS IS THE EASY FUNCTION TO CALL to SEND ALL CHANNELS TO MAX-MSP
        //VCC.MAXsendGatesA();
        
        /* // THIS IS THE HARDCODED VERSION TO SEND INDIVIDUAL CHANNELS TO MAX!
          Serial.print("GateA1 ");
          Serial.println(VCC.gateValuesA[0],BIN);
          Serial.print("GateA3 ");
          Serial.println(VCC.gateValuesA[2],BIN);
          Serial.print("GateA8 ");
          Serial.println(VCC.gateValuesA[7],BIN);
        */ 
        
      }
      
      
      // LOGIC EXAMPLE
       /* ALL FUCNTIONS
       Logic.AND( boolean _val1,  boolean _val2);
       Logic.OR( boolean _val1,  boolean _val2);
       Logic.NAND( boolean _val1,  boolean _val2);
       Logic.NOR( boolean _val1,  boolean _val2);
       Logic.XOR( boolean _val1,  boolean _val2);
       Logic.XNOR( boolean _val1,  boolean _val2);
       */
       
       //example:  
       /*if( Logic.AND(VCC.gateValuesA[0], VCC.gateValuesA[1]) ){ // THIS WILL BE TRUE
           VCC.WriteChannel(8, addacMaxResolution);
        }else{
          VCC.WriteChannel(8, 0);
        }
        
        if( Logic.OR(VCC.gateValuesA[0], VCC.gateValuesA[1]) ){ // THIS WILL BE TRUE
           VCC.WriteChannel(7, addacMaxResolution);
        }else{
          VCC.WriteChannel(7, 0);
        }
      
        if( Logic.NAND(VCC.gateValuesA[0], VCC.gateValuesA[1]) ){ // THIS WILL BE TRUE
           VCC.WriteChannel(6, addacMaxResolution);
        }else{
          VCC.WriteChannel(6, 0);
        }
        
        if( Logic.XNOR(VCC.gateValuesA[0], VCC.gateValuesA[1]) ){ // THIS WILL BE TRUE
           VCC.WriteChannel(5, addacMaxResolution);
        }else{
          VCC.WriteChannel(5, 0);
        }*/
        

      delay(100);
      
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 4 -----------
    //
    }else if(VCC.SUBMODE==4){ // ADDAC005 & 005W - GATES OUT TEST
      /*for(int i=0; i<8;i++){
        VCC.WriteGatesAstraight(i, int(random(2)));
        VCC.WriteGatesBstraight(i, int(random(2)));
        delay(100);
      } */
      readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
       VCC.ReadGatesA(true); // Boolean Parameter sets inverting read setting  -> true:inverting, false:non-inverting
       
      /*CLOCK1.update(VCC.gateValuesA[0], VCC.gateValuesA[1], millis(), analogValsA[3], analogValsA[4]);
       VCC.WriteGatesAstraight(0, CLOCK1.state);
      
       if(!CLOCK1.state){
           VCC.WriteGatesAstraight(1, 0);
       }else{
          if(CLOCK1.Counter%1==0) VCC.WriteGatesAstraight(1, 1);
       }
       
       VCC.WriteGatesAstraight(2, CLOCK1.OUT);
       */
      
      
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 5 -----------
    //
    }else if(VCC.SUBMODE==5){ // FOR ETHERNET TESTING
       #ifdef ETHERNET
         EthernetRead();
         EthernetWrite();
       #endif
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 6 -----------
    //
    }else if(VCC.SUBMODE==6){ // QUANTIZER TEST - For Now only TUNED FOR POSITIVE OUTPUT!!
      //read from ADDAC003 - MANUAL INPUTS
      readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
      unsigned int temp=Quantize.quantize(random(analogValsA[0]/1023.0f*addacMaxResolution));
      Serial.println(temp);
      VCC.WriteChannel(1, temp);
      delay(random(analogValsA[2])+analogValsA[1]);
      
      // PLAY ALL NOTES
      //Serial.println(Quantize.NOTES[noteNow]*1000.0f);
      //VCC.WriteChannel(1,Quantize.NOTES[noteNow]*1000.0f);
      //noteNow++;
      //if(noteNow>60)noteNow=0;
      //delay(300);
      
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 7 -----------
    //
    }else if(VCC.SUBMODE==7){ // LISSAJOUS TEST - update:(float XMAX, float YMAX, float speedX, float speedY)
        //read from ADDAC002 - CV / MANUAL INPUTS
        readCvsINA(6); // connected to input A -> (6) = reads 6 channels
        //read from ADDAC003 - MANUAL INPUTS
        readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
        
        
       /* Liss1.update(analogValsA[0], analogValsA[2], analogValsA[1],analogValsA[3]);
        Liss2.update(analogValsA[0], analogValsA[2], analogValsA[4]);
        Liss3.update(cvValsA[0],cvValsA[1],cvValsA[2],cvValsA[3]);
        
        VCC.WriteChannel(1, Liss1.x);
        VCC.WriteChannel(2, Liss1.y);
        VCC.WriteChannel(3, (Liss1.x+Liss1.y)/2);
        VCC.WriteChannel(4, (Liss2.x+Liss2.y)/2);
        VCC.WriteChannel(5, (Liss2.x+Liss2.y)/2);
        VCC.WriteChannel(6, (Liss1.x+Liss1.y+Liss3.x+Liss3.y)/4);
        VCC.WriteChannel(7, (Liss1.x+Liss1.y+Liss2.x+Liss3.x+Liss3.y)/5);
        VCC.WriteChannel(8, Liss3.y);   
      */  
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 8 -----------
    //
    }else if(VCC.SUBMODE==8){ // MARBLE PHYSICS TEST - update:(X TILT, Y TILT, ELASTICITY, SPEED) 
        //read from ADDAC003 - MANUAL INPUTS
        readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
        /*Physics.update(analogValsA[0], analogValsA[2], analogValsA[1],analogValsA[3]);
        
        VCC.WriteChannel(1, Physics.x);
        VCC.WriteChannel(2, Physics.y);
        VCC.WriteChannel(3, (Physics.x+Physics.y)/2);
        
        if(Physics.hitYWall){
        //Spring.hitWall=false;
          VCC.WriteChannel(4, 65000);
        }else{
          VCC.WriteChannel(4, 0);
        }  
        
        if(Physics.hitXWall){
        //Spring.hitWall=false;
          VCC.WriteChannel(5, 65000);
        }else{
          VCC.WriteChannel(5, 0);
        }  
        
        if(Physics.hitXWall || Physics.hitYWall){
        //Spring.hitWall=false;
          VCC.WriteChannel(6, 65000);
        }else{
          VCC.WriteChannel(6, 0);
        }  */
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 9 -----------
    //
    }else if(VCC.SUBMODE==9){
      //read from ADDAC003 - MANUAL INPUTS
     readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
     readCvsINA(6);
     
     int quadMode=0;
      // QUADRIPHONIC ALGORITHM
      if(cvValsA[0]<512)quadMode=0;
      else quadMode=1;

     /* Quad.calcs(quadMode,cvValsA[1], cvValsA[2], cvValsA[3],cvValsA[4],cvValsA[5]); // CARTESIAN / POLAR MODE (0=radius/angle; 1=x/y), RADIUS/X, ANGLE/Y, ANGLE MULTIPLIER, EXP/LOG, NA
      VCC.WriteChannel(1, (Quad.amp1)*addacMaxResolution); // CHANNEL 1
      VCC.WriteChannel(2, (Quad.amp2)*addacMaxResolution); // CHANNEL 2
      VCC.WriteChannel(3, (Quad.amp3)*addacMaxResolution); // CHANNEL 3
      VCC.WriteChannel(4, (Quad.amp4)*addacMaxResolution); // CHANNEL 4
      VCC.WriteChannel(5, Quad.xAbs); // X POS - bipolar
      VCC.WriteChannel(6, Quad.yAbs); // Y POS - bipolar
      VCC.WriteChannel(7, Quad.filterFreq*addacMaxResolution); // FILTER CV OUT
      //VCC.WriteChannel(8, (1 - Quad.filterFreq)*addacMaxResolution); // INVERTED FILTER CV OUT
      
      // int _channel (1-8), bool inverted (0=no - 1=yes), float freq (0-255), float mult (0-30), unsigned int offset (0-addacMaxResolution)  
    // XTRA 2 VALS: int _bottom (percentage 0-100%), int _top (percentage 0-100%)
    
    VCC.sinMode(8, 0, analogValsA[0]/4, analogValsA[1]/20, analogValsA[2]/1023.0f*addacMaxResolution, analogValsA[3]/1023.0f, analogValsA[4]/1023.0f);
      */
      /*
      Serial.print("  QUAD *");
      Serial.print("  Raio:");
      Serial.print(cvValsA[0]);
      Serial.print("  Theta:");
      Serial.print(cvValsA[1]);
      Serial.print("  X:");
      Serial.print(Quad.x);
      Serial.print("  Y:");
      Serial.print(Quad.y);
      Serial.print("  X1:");
      Serial.print(Quad.x1);
      Serial.print("  Y1:");
      Serial.print(Quad.y1);
      Serial.print("  Amp1:");
      Serial.print(Quad.amp1);
      Serial.print("  Amp2:");
      Serial.print(Quad.amp2);
      Serial.print("  Amp3:");
      Serial.print(Quad.amp3);
      Serial.print("  Amp4:");
      Serial.print(Quad.amp4);
      */
      
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 10 -----------
    //
    }else if(VCC.SUBMODE==10){ // CV RECORDER TEST - update:(int _MODE, int _interval, float _wet, int _val);
        //_MODE 0 == LOOP MODE
	//_MODE 1 == OVERDUB MODE
	//_MODE 2 == ERASE MODE

        // This Class can crash the VCC if the sample buffer is too long!
        // if strange behaviour happen and you're playing around with the loop size function this might be the cause!
        
        // Prints out Available Memory!
        Serial.print("Mem:");
        Serial.print( freeMemory() );
        Serial.print("  |  ");
        
        int _MODE = analogValsA[3] / 400;
        
       /* Looper1.loopSize(analogValsA[2]/2); // IF THIS VALUE IS BIGGER THAN 1023/3 it might crash
        Looper1.update(_MODE, analogValsA[0], analogValsA[1]/1023.0f, cvValsA[0]);  // (int _MODE, int _interval, float _wet, int _val);
        VCC.WriteChannel(1, Looper1.CVstream); 
        VCC.WriteChannel(2, Looper1.CVstream); 

        unsigned int temp=Quantize.quantize(Looper1.CVstream);
        VCC.WriteChannel(3, temp);*/
         
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 11 -----------
    //
    }else if(VCC.SUBMODE==11){ // ADSR's TESTS
        //read from ADDAC002 - CV / MANUAL INPUTS
        readCvsINA(6); // connected to input A -> (6) = reads 6 channels
        //read from ADDAC003 - MANUAL INPUTS
        readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
        
        // ADSR's HAVE LOTS OF PARAMETERS, IT'S HARD TO FIND A WAY TO DO THIS MORE CLEARLY, 
        // i'm keeping the variable name "CVstream" as the output variable for all Classes!
        
        //temporary trigger booleans
        if(analogValsA[4]>500) adsrTrigger1=true;
        if(analogValsA[4]>500) adsrTrigger2=true;
        if(analogValsA[4]>500) adsrTrigger3=true;
        
        // SIMPLE ADSR
        //
        //adsrMode(int DAC_channel, bool _trigger, bool inverted_ADSR, float A_peak, float A_time, float D_peak, float D_time, float S_peak, float S_time, float R_time)
        //int _channel (1-8), bool _trigger (0=no - 1=yes), bool _inverted (0=no - 1=yes) 
        //float X_peak (0.0f<->1.0f), float X_time (millis)                                                                
        /*ADSR3.adsrMode(3, adsrTrigger3, 0, analogValsA[0]/1023.0f, analogValsA[3]/1023.0f*2000, //A
                                           analogValsA[2]/1023.0f, analogValsA[3]/1023.0f*2000, //D
                                           analogValsA[1]/1023.0f, analogValsA[3]/1023.0f*2000, //S
                                                                   analogValsA[3]/1023.0f*2000);//R
          */                                                         
        // COMPLEX ADSR  with EXPONENTIAL / LINEAR / LOGARITHMIC PROGRESSIONS BETWEEN STEPS 
        //        
        //int _channel (1-8), bool _trigger (0=no - 1=yes), bool _inverted (0=no - 1=yes) 
        //float _X (0.0f<->1.0f), float _Xtime (millis), float _Xshape (0.0f<->1.0f)
        /*ADSR1.adsrLogExpMode(1, adsrTrigger1, 0, analogValsA[0]/1023.0f, analogValsA[3]/1023.0f*2000.0f, cvValsA[0]/1023.0f,   // A
                                                 analogValsA[2]/1023.0f, analogValsA[3]/1023.0f*2000.0f, cvValsA[1]/1023.0f,   // D
                                                 analogValsA[1]/1023.0f, analogValsA[3]/1023.0f*2000.0f, cvValsA[2]/1023.0f,   // S
                                                                         analogValsA[3]/1023.0f*2000.0f, cvValsA[3]/1023.0f);  // R
       */
       // DETAILED DESCRIPTION
       /*adsrLogExpMode(int _channel, bool _trigger, bool _inverted, float _A, float _Atime, float _Ashape, 
                                                                  float _D, float _Dtime, float _Dshape, 
                                                                  float _S, float _Stime, float _Sshape, 
                                                                            float _Rtime, float _Rshape){
                                                                  there's no need for an _R because it's always 0!*/

        // OLD BUG THAT DO SOME STRANGE INTERESTING THINGS (?? can't exactly remember, it's been a while since i did this, probaably better ignore it or use for what it is!)
        //
        //int _channel (1-8), bool _trigger (0=no - 1=yes), bool _inverted (0=no - 1=yes) 
        //float _X (0.0f<->1.0f), float _Xtime (millis), float _Xshape (0.0f<->1.0f)
        /*ADSR2.adsrWeirdMode(2, adsrTrigger2, 0, analogValsA[0]/1023.0f, analogValsA[3]/1023.0f*2000.0f, cvValsA[4]/1023.0f,   // A
                                                analogValsA[2]/1023.0f, analogValsA[3]/1023.0f*2000.0f, cvValsA[5]/1023.0f);  // D

       
      */
        adsrTrigger1=false;
        adsrTrigger2=false;
        adsrTrigger3=false;
        
        //Serial.println(ADSR1.CVstream);
        
        // I'm using the variable name "CVstream" as the output variable for all Classes with 1 output!
        /*VCC.WriteChannel(1, ADSR1.CVstream);
        VCC.WriteChannel(2, addacMaxResolution - ADSR1.CVstream); // INVERTED ADSR - easy as pie!
        
        VCC.WriteChannel(3, ADSR2.CVstream);
        VCC.WriteChannel(4, addacMaxResolution - ADSR2.CVstream); // INVERTED ADSR - easy as pie!
        
        VCC.WriteChannel(5, ADSR3.CVstream);
        VCC.WriteChannel(6, addacMaxResolution - ADSR3.CVstream); // INVERTED ADSR - easy as pie!
        */
        
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 12 -----------
    //
    }else if(VCC.SUBMODE==12){ // TESTS LOGIC LIBRARY
       /* ALL FUCNTIONS
       Logic.AND( boolean _val1,  boolean _val2);
       Logic.OR( boolean _val1,  boolean _val2);
       Logic.NOT( boolean _val1,  boolean _val2);
       Logic.NAND( boolean _val1,  boolean _val2);
       Logic.NOR( boolean _val1,  boolean _val2);
       Logic.XOR( boolean _val1,  boolean _val2);
       Logic.XNOR( boolean _val1,  boolean _val2);
       */
       
       //example:  
       //if( Logic.AND(1, 1) ){ // THIS WILL BE TRUE
           // DO SOMETHING HERE!!
       // }
        
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 13 -----------
    //
    }else if(VCC.SUBMODE==13){ // TESTS LFO LIBRARY
       /* ALL FUCNTIONS
       LFO1.update(float _increment) // sets LFO increment time (0.0f - 1.0f) -> "MASTER CLOCK" -> VALID FOR ALL WAVEFORMS
       
       LFO1.SINget()                 // updates and retrieve SIN
       LFO1.SINupdate()              // updates SIN 
       LFO1.SIN                      // VARIABLE TO HOLD SIN VALUE (0 - addacMaxResolution)
       */
       
       readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
       
       /*LFO1.update(analogValsA[0]/1023.0f);
       LFO1.SINupdate(); // ONLY CALLS FUNCTION NEEDED, DOESN'T WASTE CPU (?) OR CALL EVERYTHING IN UPDATE AND IT'S DONE ??
       //LFO1.TRIupdate(); // ONLY CALLS FUNCTION NEEDED, DOESN'T WASTE CPU (?)
       //LFO1.SAWupdate(); // ONLY CALLS FUNCTION NEEDED, DOESN'T WASTE CPU (?)
       VCC.WriteChannel(1, LFO1.SIN);
       VCC.WriteChannel(2, addacMaxResolution-LFO1.SIN); // inverted SIN - easy as pie!
      */
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 14 -----------
    //
    }else if(VCC.SUBMODE==14){ // TESTS ADDAC006 - NCHUNK
      #ifdef NCHUNK
        NUNwrite();
      #endif
    
    // ---------------------------------------------------------------------------------------------------------------------- SUBMODE 15 -----------
    //
    }else if(VCC.SUBMODE==15){ // IanniX Software Connection
      // For faster communication avoid "Serial.prints" !!
      
      // IANNIX messages have 4 values:
      // 0. the IanniX Object Type
      // 1. the ID
      // 2. the X position
      // 3. the Y position
      
      /*if((IanniX::hasData()) && (IanniX::count() >= 3)){
        //tone(IanniX::toInt(1), IanniX::toInt(2), IanniX::toInt(3));
        
        int _channel = IanniX::toInt(1);
        int _value   = IanniX::toFloat(3)*addacMaxResolution;
        VCC.WriteChannel(_channel, _value); // only using ID & Y position
        if(_channel==1){ // Quantize IanniX ID 1
          VCC.WriteChannel(7, Quantize.quantize(_value)); // only using ID & Y position
        }//VCC.WriteChannel(IanniX::toInt(1), IanniX::toFloat(3)*addacMaxResolution);
       // Serial.print("  IX1:");
       // Serial.print(IanniX::toInt(1));
        //Serial.print("  IX2:");
        //Serial.print(IanniX::toFloat(2));
      }
      */
    }
  
  // ------------------------------------------------------------------------------------------------------------------------------- MODE 1 -----------
  //
  }else if(VCC.MODE==1){ // SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 1
    // if MODE B SWITCH is in Position 1 -> ( LEFT BOTTOM POSITION)
    if(VCC.SUBMODE==1){ // CLEAR ALL OUTPUTS -> RESETS TO ZERO
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 0);
      }
    // if MODE B SWITCH is in Position 2 -> ( LEFT BOTTOM +1 POSITION)
    }else if(VCC.SUBMODE==2){ // SPEED CONTROL ALL OUPUTS
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, onboardPot/1023.0f*addacMaxResolution);
      }
    // if MODE B SWITCH is in Position 3 -> ( LEFT BOTTOM +2 POSITION)
    }else if(VCC.SUBMODE==3){ // ALL OUTPUTS TO 10000 
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 10000);
      }
    // if MODE A SWITCH is in Position 4...
    }else if(VCC.SUBMODE==4){ // ALL OUTPUTS TO 20000 
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 20000);
      }
    // if MODE A SWITCH is in Position 5...
    }else if(VCC.SUBMODE==5){ // ALL OUTPUTS TO 30000   = ±2.4v
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 30000);
      }
    // if MODE A SWITCH is in Position 6...
    }else if(VCC.SUBMODE==6){ // ALL OUTPUTS TO 35000 
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 35000);
      }
    // if MODE A SWITCH is in Position 7...
    }else if(VCC.SUBMODE==7){ // ALL OUTPUTS TO 40000
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 40000);
      }
    // if MODE A SWITCH is in Position 8...
    }else if(VCC.SUBMODE==8){ // ALL OUTPUTS TO 45000 
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 45000);
      }
    // if MODE A SWITCH is in Position 9...
    }else if(VCC.SUBMODE==9){ // ALL OUTPUTS TO 50000
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 50000);
      }
    // if MODE A SWITCH is in Position 10...
    }else if(VCC.SUBMODE==10){ // ALL OUTPUTS TO 55000 
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 55000);
      }
    // if MODE A SWITCH is in Position 11...
    }else if(VCC.SUBMODE==11){ // ALL OUTPUTS TO MAX 
      for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, addacMaxResolution);
      }
    }
    
    
    

  // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 2
  }else if(VCC.MODE==2){  // 
   
    
  }else if(VCC.MODE==3){  // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 3
    // int _channel (1-8), bool inverted (0=no - 1=yes), float freq (0-255), float mult (0-30), unsigned int offset (0-addacMaxResolution)  
    // XTRA 2 VALS: int _bottom (percentage 0-100%), int _top (percentage 0-100%)
    
    VCC.sinMode(1, 0, analogValsA[0]/4, analogValsA[1]/20, analogValsA[2]/1023.0f*addacMaxResolution, cvValsA[0]/1023.0f, cvValsA[1]/1023.0f);
    VCC.sinMode(2, 1, analogValsA[0]/4, analogValsA[1]/20, analogValsA[3]/1023.0f*addacMaxResolution, cvValsA[2]/1023.0f, cvValsA[3]/1023.0f);
    VCC.sinMode(3, 0, analogValsA[0]/4, analogValsA[1]/20, analogValsA[4]/1023.0f*addacMaxResolution); // DIVISION CLEARS JITTER IN FREQUENCY !!!!!!!!!!
    VCC.sinMode(4, 1, analogValsA[0]/4, analogValsA[1]/20, analogValsA[1]/1023.0f*addacMaxResolution); // DIVISION CLEARS JITTER IN FREQUENCY !!!!!!!!!!
    VCC.cosinMode(5, 0, analogValsA[0]/4, analogValsA[1]/20, analogValsA[2]/1023.0f*addacMaxResolution, cvValsA[4]/1023.0f, cvValsA[5]/1023.0f);
    VCC.cosinMode(6, 1, analogValsA[0]/4, analogValsA[1]/20, analogValsA[4]/1023.0f*addacMaxResolution, cvValsA[4]/1023.0f, cvValsA[5]/1023.0f);
    VCC.cosinMode(7, 0, analogValsA[0]/4, analogValsA[1]/20, analogValsA[2]/1023.0f*addacMaxResolution); // DIVISION CLEARS JITTER IN FREQUENCY !!!!!!!!!!
    //VCC.cosinMode(8, 1, analogValsA[0]/4, analogValsA[0]/20, (analogValsA[4])/1023.0f*addacMaxResolution); // DIVISION CLEARS JITTER IN FREQUENCY !!!!!!!!!!
    //VCC.tanMode(5, 0, analogValsA[0]/4, 0, 100);
    //VCC.tanMode(6, 1, analogValsA[0]/4, 0, 100);
    
    VCC.mixerMode(); // ALLWAYS IN CHANNEL 8 = Average MIX of all other Channels!  USE LAST IN LOOP!!
    
  }else if(VCC.MODE==4){ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 4
    VCC.randomMode(0,0); // MODE , CHANNEL    
    
  
  }else if(VCC.MODE==5){ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 5
    int rndTemp=random(0,8);
    if(rndTemp<8) VCC.randomMode(1,rndTemp); // MODE , CHANNEL
    
  
  }else if(VCC.MODE==6){ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 6
    int rndTemp=random(0,6+analogValsA[4]);
    if(rndTemp<6) VCC.lfosMode(0,rndTemp,0); // MODE, TYPE , CHANNEL
    
  
  }else if(VCC.MODE==7){ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 7
    int rndTemp=random(0,20+analogValsA[4]);
    if(rndTemp<6) VCC.lfosMode(0,rndTemp,0); // MODE, TYPE , CHANNEL
    else if (rndTemp>9 && rndTemp<18)VCC.randomMode(1,rndTemp-10); // MODE , CHANNEL
    
  }else if(VCC.MODE==8){ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 7
    VCC.lfosMode(0,VCC.SUBMODE,0); // MODE, TYPE , CHANNEL
    
  }else if(VCC.MODE==9){ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 7
    // sinMode(int _channel, bool _inverted, float _freq, float _mult, unsigned int _offset, float _bottom, float _top);
    VCC.sinMode(0,0, analogValsA[0], analogValsA[1]/1023.0f, analogValsA[2]/1023.0f*addacMaxResolution, analogValsA[3]/1023.0f, analogValsA[4]/1023.0f);
  

  }else if(VCC.MODE==14){ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 7
     readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
     readCvsINA(6);
    if(VCC.SUBMODE==0){
       
     
     int quadMode=0;
      // QUADRIPHONIC ALGORITHM
      if(cvValsA[0]<512)quadMode=0;
      else quadMode=1;

     /* Quad.calcs(quadMode,cvValsA[1], cvValsA[2], cvValsA[3],cvValsA[4],cvValsA[5]); // CARTESIAN / POLAR MODE (0=radius/angle; 1=x/y), RADIUS/X, ANGLE/Y, ANGLE MULTIPLIER, EXP/LOG, NA
      VCC.WriteChannel(1, (Quad.amp1)*addacMaxResolution); // CHANNEL 1
      VCC.WriteChannel(2, (Quad.amp2)*addacMaxResolution); // CHANNEL 2
      VCC.WriteChannel(3, (Quad.amp3)*addacMaxResolution); // CHANNEL 3
      VCC.WriteChannel(4, (Quad.amp4)*addacMaxResolution); // CHANNEL 4
      VCC.WriteChannel(5, Quad.xAbs); // X POS - bipolar
      VCC.WriteChannel(6, Quad.yAbs); // Y POS - bipolar
      VCC.WriteChannel(7, Quad.filterFreq*addacMaxResolution); // FILTER CV OUT
      //VCC.WriteChannel(8, (1 - Quad.filterFreq)*addacMaxResolution); // INVERTED FILTER CV OUT
      
      // ADDING AN LFO TO COMPARE IN/OUT...
      LFO1.update(analogValsA[0]/1023.0f);
      LFO1.SINupdate(); 
      VCC.WriteChannel(5, LFO1.SIN);
      
      LFO2.update(analogValsA[2]/1023.0f);
      LFO2.SINupdate(); 
      VCC.WriteChannel(6, LFO2.SIN);
      
      LFO3.update(analogValsA[1]/1023.0f);
      LFO3.SINupdate(); 
      VCC.WriteChannel(7, LFO3.SIN);
      
      LFO4.update(analogValsA[3]/1023.0f);
      LFO4.SINupdate(); 
      VCC.WriteChannel(8, LFO4.SIN);
      */
      
      
    }else if(VCC.SUBMODE==1){
     
     int quadMode=0;
      // QUADRIPHONIC ALGORITHM
      if(cvValsA[0]<512)quadMode=0;
      else quadMode=1;

      /*Quad.calcs(quadMode,cvValsA[1], cvValsA[2], cvValsA[3],cvValsA[4],cvValsA[5]); // CARTESIAN / POLAR MODE (0=radius/angle; 1=x/y), RADIUS/X, ANGLE/Y, ANGLE MULTIPLIER, EXP/LOG, NA
      VCC.WriteChannel(1, (Quad.amp2)*addacMaxResolution); // CHANNEL 1
      VCC.WriteChannel(2, (Quad.amp4)*addacMaxResolution); // CHANNEL 2
      VCC.WriteChannel(3, (Quad.amp1)*addacMaxResolution); // CHANNEL 3
      VCC.WriteChannel(4, (Quad.amp3)*addacMaxResolution); // CHANNEL 4
      //VCC.WriteChannel(5, Quad.xAbs); // X POS - bipolar
      //VCC.WriteChannel(6, Quad.yAbs); // Y POS - bipolar
      //VCC.WriteChannel(7, Quad.filterFreq*addacMaxResolution); // FILTER CV OUT
      //VCC.WriteChannel(8, (1 - Quad.filterFreq)*addacMaxResolution); // INVERTED FILTER CV OUT
      
      // ADDING AN LFO TO COMPARE IN/OUT...
      LFO1.update(analogValsA[0]/1023.0f);
      LFO1.SINupdate(); 
      VCC.WriteChannel(5, LFO1.SIN);
      
      LFO2.update(analogValsA[2]/1023.0f);
      LFO2.SINupdate(); 
      VCC.WriteChannel(6, LFO2.SIN);
      
      LFO3.update(analogValsA[1]/1023.0f);
      LFO3.SINupdate(); 
      VCC.WriteChannel(7, LFO3.SIN);
      
      LFO4.update(analogValsA[3]/1023.0f);
      LFO4.SINupdate(); 
      VCC.WriteChannel(8, LFO4.SIN);
      */
    }
  }else if(VCC.MODE==15){
    readCvsINA(6);
      readAnalogsINA(5); // connected to input A -> (5) = reads 5 channels
      // int _channel (1-8), bool inverted (0=no - 1=yes), float freq (0-255), float mult (0-30), unsigned int offset (0-addacMaxResolution)  
    // XTRA 2 VALS: int _bottom (percentage 0-100%), int _top (percentage 0-100%)
     // VCC.WriteChannel(1, cvValsA[0]/1023.0f*addacMaxResolution);
      
      // ADDING AN LFO TO COMPARE IN/OUT...
      /*LFO1.update(cvValsA[0]/1023.0f);
      LFO1.SINupdate(); 
      VCC.WriteChannel(1, LFO1.SIN);
      
      LFO2.update(cvValsA[1]/1023.0f);
      LFO2.SINupdate(); 
      VCC.WriteChannel(2, LFO2.SIN);
      
      LFO3.update(cvValsA[2]/1023.0f);
      LFO3.SINupdate(); 
      VCC.WriteChannel(3, LFO3.SIN);
      
      LFO4.update(cvValsA[3]/1023.0f);
      LFO4.SINupdate(); 
      VCC.WriteChannel(4, LFO4.SIN);
      
      LFO5.update(cvValsA[4]/1023.0f);
      LFO5.SINupdate(); 
      VCC.WriteChannel(5, LFO5.SIN);
      VCC.WriteChannel(6, addacMaxResolution-LFO5.SIN); // inverted SIN - easy as pie!
      
      LFO6.update(cvValsA[5]/1023.0f);
      LFO6.SINupdate(); 
      VCC.WriteChannel(7, LFO6.SIN);
      VCC.WriteChannel(8, addacMaxResolution-LFO6.SIN); // inverted SIN - easy as pie!
      */
  }else{ // NEXT SWITCH A POSITION --------------------------------------------------- if MODE A SWITCH is in Position 8 or higher
    VCC.lfosMode(0,MODE-1,0); // MODE, TYPE , CHANNEL
  }
  /*
  for(int i=0;i<8;i++){
        VCC.WriteChannel(i+1, 400000);
  }*/
}
