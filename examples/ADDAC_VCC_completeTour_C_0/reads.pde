


/*

 DONT NEED TO CHANGE NOTHING HERE !!
 
 .
 UNLESS YOU REALLY REALLY WANT TO
 
 
 */

//
// --------------------------------------------------------------------------- READ CV INS - ADDAC002 -----------
void readCvsINA(int _nChannels){ // numbers of channels to read from 0
  for(int i=0;i<_nChannels;i++){
    cvValsA[i]=VCC.ReadCvsA(i);
  }
#ifdef DEBUGcvA
  Serial.print(" | AN1:");
  Serial.print(cvValsA[0]);
  Serial.print(" | AN2:");
  Serial.print(cvValsA[1]);
  Serial.print(" | AN3:");
  Serial.print(cvValsA[2]);
  Serial.print(" | AN4:");
  Serial.print(cvValsA[3]);
  Serial.print(" | AN5:");
  Serial.print(cvValsA[4]);
  Serial.print(" | AN6:");
  Serial.print(cvValsA[5]);
#endif
#ifdef MaxCvA
  Serial.print("CvA1 ");
  Serial.println(cvValsA[0]);
  Serial.print("CvA2 ");
  Serial.println(cvValsA[1]);
  Serial.print("CvA3 ");
  Serial.println(cvValsA[2]);
  Serial.print("CvA4 ");
  Serial.println(cvValsA[3]);
  Serial.print("CvA5 ");
  Serial.println(cvValsA[4]);
  Serial.print("CvA6 ");
  Serial.println(cvValsA[5]);
#endif
}
// B
void readCvsINB(int _nChannels){ // numbers of channels to read from 0
  for(int i=0;i<_nChannels;i++){
    cvValsB[i]=VCC.ReadCvsB(i);
  }
#ifdef DEBUGcvB
  Serial.print(" | CvB1:");
  Serial.print(cvValsB[0]);
  Serial.print(" | CvB2:");
  Serial.print(cvValsB[1]);
  Serial.print(" | CvB3:");
  Serial.print(cvValsB[2]);
  Serial.print(" | CvB4:");
  Serial.print(cvValsB[3]);
  Serial.print(" | CvB5:");
  Serial.print(cvValsB[4]);
  Serial.print(" | CvB6:");
  Serial.print(cvValsB[5]);
#endif
#ifdef MaxCvB
  Serial.print("CvB1 ");
  Serial.println(cvValsB[0]);
  Serial.print("CvB2 ");
  Serial.println(cvValsB[1]);
  Serial.print("CvB3 ");
  Serial.println(cvValsB[2]);
  Serial.print("CvB4 ");
  Serial.println(cvValsB[3]);
  Serial.print("CvB5 ");
  Serial.println(cvValsB[4]);
  Serial.print("CvB6 ");
  Serial.println(cvValsB[5]);
#endif
}
// B
void readCvsINC(int _nChannels){ // numbers of channels to read from 0
  for(int i=0;i<_nChannels;i++){
    cvValsC[i]=VCC.ReadCvsC(i);
  }
#ifdef DEBUGcvC
  Serial.print(" | CvC1:");
  Serial.print(cvValsC[0]);
  Serial.print(" | CvC2:");
  Serial.print(cvValsB[1]);
  Serial.print(" | CvC3:");
  Serial.print(cvValsC[2]);
  Serial.print(" | CvC4:");
  Serial.print(cvValsC[3]);
  Serial.print(" | CvC5:");
  Serial.print(cvValsC[4]);
  Serial.print(" | CvC6:");
  Serial.print(cvValsC[5]);
#endif
#ifdef MaxCvC
  Serial.print("CvC1 ");
  Serial.println(cvValsC[0]);
  Serial.print("CvC2 ");
  Serial.println(cvValsC[1]);
  Serial.print("CvC3 ");
  Serial.println(cvValsC[2]);
  Serial.print("CvC4 ");
  Serial.println(cvValsC[3]);
  Serial.print("CvC5 ");
  Serial.println(cvValsC[4]);
  Serial.print("CvC6 ");
  Serial.println(cvValsC[5]);
#endif
}
//
// --------------------------------------------------------------------------- READ ANALOGS IN - ADDAC003 -----------
void readAnalogsINA(int _nChannels){ // numbers of channels to read from 0
  for(int i=0;i<_nChannels;i++){
    analogValsA[i]=VCC.ReadAnalogsA(i);
  }
#ifdef DEBUGanalogA
  Serial.print(" | AN1:");
  Serial.print(analogValsA[0]);
  Serial.print(" | AN2:");
  Serial.print(analogValsA[1]);
  Serial.print(" | AN3:");
  Serial.print(analogValsA[2]);
  Serial.print(" | AN4:");
  Serial.print(analogValsA[3]);
  Serial.print(" | AN5:");
  Serial.print(analogValsA[4]);
#endif
#ifdef MaxAnalogA
  Serial.print("ManualA1 ");
  Serial.println(analogValsA[0]);
  Serial.print("ManualA2 ");
  Serial.println(analogValsA[1]);
  Serial.print("ManualA3 ");
  Serial.println(analogValsA[2]);
  Serial.print("ManualA4 ");
  Serial.println(analogValsA[3]);
  Serial.print("ManualA5 ");
  Serial.println(analogValsA[4]);
#endif
}
// B
void readAnalogsINB(int _nChannels){ // numbers of channels to read from 0
  for(int i=0;i<_nChannels;i++){
    analogValsB[i]=VCC.ReadAnalogsB(i);
  }
#ifdef DEBUGanalogB
  Serial.print(" | BN1:");
  Serial.print(analogValsB[0]);
  Serial.print(" | BN2:");
  Serial.print(analogValsB[1]);
  Serial.print(" | BN3:");
  Serial.print(analogValsB[2]);
  Serial.print(" | BN4:");
  Serial.print(analogValsB[3]);
  Serial.print(" | BN5:");
  Serial.print(analogValsB[4]);
#endif
#ifdef MaxAnalogB
  Serial.print("ManualB1 ");
  Serial.println(analogValsB[0]);
  Serial.print("ManualB2 ");
  Serial.println(analogValsB[1]);
  Serial.print("ManualB3 ");
  Serial.println(analogValsB[2]);
  Serial.print("ManualB4 ");
  Serial.println(analogValsB[3]);
  Serial.print("ManualB5 ");
  Serial.println(analogValsB[4]);
#endif
}
// C
void readAnalogsINC(int _nChannels){ // numbers of channels to read from 0
  for(int i=0;i<_nChannels;i++){
    analogValsC[i]=VCC.ReadAnalogsC(i);
  }
#ifdef DEBUGanalogC
  Serial.print(" | CN1:");
  Serial.print(analogValsC[0]);
  Serial.print(" | CN2:");
  Serial.print(analogValsC[1]);
  Serial.print(" | CN3:");
  Serial.print(analogValsC[2]);
  Serial.print(" | CN4:");
  Serial.print(analogValsC[3]);
  Serial.print(" | CN5:");
  Serial.print(analogValsC[4]);
#endif
#ifdef MaxAnalogC
  Serial.print("ManualC1 ");
  Serial.println(analogValsC[0]);
  Serial.print("ManualC2 ");
  Serial.println(analogValsC[1]);
  Serial.print("ManualC3 ");
  Serial.println(analogValsC[2]);
  Serial.print("ManualC4 ");
  Serial.println(analogValsC[3]);
  Serial.print("ManualC5 ");
  Serial.println(analogValsC[4]);
#endif
}

//
// --------------------------------------------------------------------------- READ GATES IN - ADDAC004 -----------
void readGatesINA(int _nChannels){ // numbers of channels to read from 0
  byte gatesValsAbin=VCC.ReadGatesA(8);
  for(int i=0;i<8;i++){
    gatesValsA[i] = gatesValsAbin & (1<<i);
    gatesValsA[i]=gatesValsA[i]>>i;
  }
#ifdef DEBUGgateINA
  Serial.print(" | GA1:");
  Serial.print(gatesValsA[0],BIN);
  Serial.print(" | GA2:");
  Serial.print(gatesValsA[1],BIN);
  Serial.print(" | GA3:");
  Serial.print(gatesValsA[2],BIN);
  Serial.print(" | GA4:");
  Serial.print(gatesValsA[3],BIN);
  Serial.print(" | GA5:");
  Serial.print(gatesValsA[4],BIN);
  Serial.print(" | GA6:");
  Serial.print(gatesValsA[5],BIN);
  Serial.print(" | GA7:");
  Serial.print(gatesValsA[6],BIN);
  Serial.print(" | GA8:");
  Serial.print(gatesValsA[7],BIN);
#endif
#ifdef MaxGatesA
  Serial.print("GateA1 ");
  Serial.println(gatesValsA[0],BIN);
  Serial.print("GateA2 ");
  Serial.println(gatesValsA[1],BIN);
  Serial.print("GateA3 ");
  Serial.println(gatesValsA[2],BIN);
  Serial.print("GateA4 ");
  Serial.println(gatesValsA[3],BIN);
  Serial.print("GateA5 ");
  Serial.println(gatesValsA[4],BIN);
  Serial.print("GateA6 ");
  Serial.println(gatesValsA[5],BIN);
  Serial.print("GateA7 ");
  Serial.println(gatesValsA[6],BIN);
  Serial.print("GateA8 ");
  Serial.println(gatesValsA[7],BIN);
#endif
}
void readGatesINB(int _nChannels){ // numbers of channels to read from 0
  byte gatesValsBbin=VCC.ReadGatesB(8);
  for(int i=0;i<8;i++){
    gatesValsB[i] = gatesValsBbin & (1<<i);
    gatesValsB[i]=gatesValsB[i]>>i;
  }
#ifdef DEBUGgateINB
  Serial.print(" | GB1:");
  Serial.print(gatesValsB[0],BIN);
  Serial.print(" | GB2:");
  Serial.print(gatesValsB[1],BIN);
  Serial.print(" | GB3:");
  Serial.print(gatesValsB[2],BIN);
  Serial.print(" | GB4:");
  Serial.print(gatesValsB[3],BIN);
  Serial.print(" | GB5:");
  Serial.print(gatesValsB[4],BIN);
  Serial.print(" | GB6:");
  Serial.print(gatesValsB[5],BIN);
  Serial.print(" | GB7:");
  Serial.print(gatesValsB[6],BIN);
  Serial.print(" | GB8:");
  Serial.print(gatesValsB[7],BIN);
#endif
#ifdef MaxGatesB
  Serial.print("GateB1 ");
  Serial.println(gatesValsB[0],BIN);
  Serial.print("GateB2 ");
  Serial.println(gatesValsB[1],BIN);
  Serial.print("GateB3 ");
  Serial.println(gatesValsB[2],BIN);
  Serial.print("GateB4 ");
  Serial.println(gatesValsB[3],BIN);
  Serial.print("GateB5 ");
  Serial.println(gatesValsB[4],BIN);
  Serial.print("GateB6 ");
  Serial.println(gatesValsB[5],BIN);
  Serial.print("GateB7 ");
  Serial.println(gatesValsB[6],BIN);
  Serial.print("GateB8 ");
  Serial.println(gatesValsB[7],BIN);
#endif
}
void readGatesINC(int _nChannels){ // numbers of channels to read from 0
  byte gatesValsCbin=VCC.ReadGatesC(8);
  for(int i=0;i<8;i++){
    gatesValsC[i] = gatesValsCbin & (1<<i);
    gatesValsC[i]=gatesValsC[i]>>i;
  }
#ifdef DEBUGgateINC
  Serial.print(" | GC1:");
  Serial.print(gatesValsC[0],BIN);
  Serial.print(" | GC2:");
  Serial.print(gatesValsC[1],BIN);
  Serial.print(" | GC3:");
  Serial.print(gatesValsC[2],BIN);
  Serial.print(" | GC4:");
  Serial.print(gatesValsC[3],BIN);
  Serial.print(" | GC5:");
  Serial.print(gatesValsC[4],BIN);
  Serial.print(" | GC6:");
  Serial.print(gatesValsC[5],BIN);
  Serial.print(" | GC7:");
  Serial.print(gatesValsC[6],BIN);
  Serial.print(" | GC8:");
  Serial.print(gatesValsC[7],BIN);
#endif
#ifdef MaxGatesC
  Serial.print("GateC1 ");
  Serial.println(gatesValsC[0],BIN);
  Serial.print("GateC2 ");
  Serial.println(gatesValsC[1],BIN);
  Serial.print("GateC3 ");
  Serial.println(gatesValsC[2],BIN);
  Serial.print("GateC4 ");
  Serial.println(gatesValsC[3],BIN);
  Serial.print("GateC5 ");
  Serial.println(gatesValsC[4],BIN);
  Serial.print("GateC6 ");
  Serial.println(gatesValsC[5],BIN);
  Serial.print("GateC7 ");
  Serial.println(gatesValsC[6],BIN);
  Serial.print("GateC8 ");
  Serial.println(gatesValsC[7],BIN);
#endif
}


