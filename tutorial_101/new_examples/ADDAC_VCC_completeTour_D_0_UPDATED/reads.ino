


/*

 DONT NEED TO CHANGE NOTHING HERE !!
 
 .
 UNLESS YOU REALLY REALLY WANT TO
 
 
 */

//
// --------------------------------------------------------------------------- READ CV INS - ADDAC002 -----------
void readCvsINA(int _nChannels){ // numbers of channels to read from 0
  for(int i=0;i<_nChannels;i++){
    cvValsA[i]=VCC.ReadCv(A,i);
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
    cvValsB[i]=VCC.ReadCv(B,i);
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
    cvValsC[i]=VCC.ReadCv(C,i);
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
    analogValsA[i]=VCC.ReadManual(A,i);
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
    analogValsB[i]=VCC.ReadManual(B,i);
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
    analogValsC[i]=VCC.ReadManual(B,i);
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



