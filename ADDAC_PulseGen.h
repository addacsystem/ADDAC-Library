/*
 * ADDAC_PulseGen
 * whitney pulse generator - pusleGen
 *
 */

#ifndef ADDAC_PulseGen_h
#define ADDAC_PulseGen_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif


#include "ADDAC_PVector.h"
#include "ADDAC_Timer.h"
#include "ADDAC_Lin2Log.h"
#include "ADDAC_Euclidean.h"
#include "ADDAC_Comparator.h"

#define widthS 1000
#define heightS 1000

#define numB 48
#define numSlots 6


class ADDAC_Points{

public:
    
       
    ADDAC_PVector origin;
    ADDAC_PVector pos;
    ADDAC_PVector vel;
    
    bool activated;
    
    int slot;
    int position;
    int pulsePerCluster;
    int pulsePerClusterOld;
    
    unsigned int beat_holder;
    
    int slotSize;
    float inc;
    
    float factor;
    float offSet;
    float speed;
    
    ADDAC_Timer timer;
    ADDAC_Lin2Log ltl;
    


    ADDAC_Points(){}
    
    ADDAC_Points(int _position){
    
       
        
        origin.set(widthS/2, heightS/2);
        pos.set(widthS/2, heightS/2);
        vel.set(0, 0);
       
        position=(_position);
        speed=1000.0f;
        slotSize=numB/numSlots;
        pulsePerCluster=8;
        pulsePerClusterOld=0;
        
        factor = 0.01f;
        offSet=48;
        speed=0.05f;
        
        if (_position<slotSize)          slot = 6;
        else if (_position<(slotSize)*2) slot = 5;
        else if (_position<(slotSize)*3) slot = 4;
        else if (_position<(slotSize)*4) slot = 3;
        else if (_position<(slotSize)*5) slot = 2;
        else if (_position<(slotSize)*6) slot = 1;
     

        
    }
    

    void update(int _pulsePerCluster, float _speed, float _factor, float _offset){
        
        pulsePerCluster=constrain(_pulsePerCluster,1,8);
        
        
        speed=ltl.calc(_speed,0.60f)+0.001f;
       
        
        factor=_factor;
        offSet=_offset;
        
        pos.x = position*6.0f * cos(inc) + widthS/2;
        pos.y = position*6.0f * sin(inc) + heightS/2;
        
        
        float temp = ((float)(abs(offSet-position)+1.0f)/numB)/10.0f+1.0f;
        float temp2 = (temp-1.0f)*(factor)*100.0f+1.0f;
        
        //original-
        //inc+=(temp*temp2)*speed;
        
        inc+=(temp*temp2)*speed;

        
        checkAngle(pos);
        
        
        
                
        if(pulsePerCluster!=pulsePerClusterOld){
        
            beat_holder = euclid(8,pulsePerCluster);
            pulsePerClusterOld=pulsePerCluster;
            
            activated = false;
            
            

        }
        
        }
    
    
    
    void checkAngle( ADDAC_PVector _angleToCheck) {
    
//        float angle = atan2(origin.x-_angleToCheck.x,origin.y-_angleToCheck.y);
//        
//        float tresh = 0.055f;  
//        
        unsigned int readBit = bitRead (beat_holder,position%slotSize);
  
        
//        if(angle+tresh > -PI/2 && angle-tresh < -PI/2 && (readBit==1))
//            activated = 1;
        
        
        if(inc>=2*PI){
            inc=inc-(2*PI);
            
            if((readBit==1))
            activated = true;
            
                   }
        
        else activated = false;
    }
    
    
    
    
    // Euclid calculation function 
    unsigned int euclid(int n, int k){ // inputs: n=total, k=beats, o = offset
        int pauses = n-k;
        int pulses = k;
        int per_pulse = pauses/k;
        int remainder = pauses%pulses;  
        unsigned int workbeat[n];
        unsigned int outbeat;
        unsigned int working;
        int workbeat_count=n;
        int a; 
        int b; 
        int trim_count;
        for (int a=0;a<n;a++){ // Populate workbeat with unsorted pulses and pauses 
            if (a<pulses){
                workbeat[a] = 1;
            }else {
                workbeat [a] = 0;
            }
        }
        
        if (per_pulse>0 && remainder <2){ // Handle easy cases where there is no or only one remainer  
            for (int a=0;a<pulses;a++){
                for (int b=workbeat_count-1; b>workbeat_count-per_pulse-1;b--){
                    workbeat[a]  = ConcatBin (workbeat[a], workbeat[b]);
                }
                workbeat_count = workbeat_count-per_pulse;
            }
            
            outbeat = 0; // Concatenate workbeat into outbeat - according to workbeat_count 
            for (int a=0;a < workbeat_count;a++){
                outbeat = ConcatBin(outbeat,workbeat[a]);
            }
            return outbeat;
        }else { 
            int groupa = pulses;
            int groupb = pauses; 
            int iteration=0;
            if (groupb<=1){
            }
            while(groupb>1){ //main recursive loop
                
                
                if (groupa>groupb){ // more Group A than Group B
                    int a_remainder = groupa-groupb; // what will be left of groupa once groupB is interleaved 
                    trim_count = 0;
                    for (int a=0; a<groupa-a_remainder;a++){ //count through the matching sets of A, ignoring remaindered
                        workbeat[a]  = ConcatBin (workbeat[a], workbeat[workbeat_count-1-a]);
                        trim_count++;
                    }
                    workbeat_count = workbeat_count-trim_count;
                    
                    groupa=groupb;
                    groupb=a_remainder;
                    
                }else if (groupb>groupa){ // More Group B than Group A
                    int b_remainder = groupb-groupa; // what will be left of group once group A is interleaved 
                    trim_count=0;
                    for (int a = workbeat_count-1;a>=groupa+b_remainder;a--){ //count from right back through the Bs
                        workbeat[workbeat_count-a-1] = ConcatBin (workbeat[workbeat_count-a-1], workbeat[a]);
                        
                        trim_count++;
                    }
                    workbeat_count = workbeat_count-trim_count;
                    groupb=b_remainder;
                    
                }else if (groupa == groupb){ // groupa = groupb 
                    trim_count=0;
                    for (int a=0;a<groupa;a++){
                        workbeat[a] = ConcatBin (workbeat[a],workbeat[workbeat_count-1-a]);
                        trim_count++;
                    }
                    workbeat_count = workbeat_count-trim_count;
                    groupb=0;
                    
                }else {
                    //        Serial.println("ERROR");
                }
                iteration++;
            }
            
            outbeat = 0; // Concatenate workbeat into outbeat - according to workbeat_count 
            for (int a=0;a < workbeat_count;a++){
                outbeat = ConcatBin(outbeat,workbeat[a]);
            }
            
//               Serial.println(outbeat,BIN);  
            return outbeat;
            
            
        }
    }
    
    
    
    
    // Function to find the binary length of a number by counting bitwise 
    int findlength(unsigned int bnry){
        boolean lengthfound = false;
        int length=1; // no number can have a length of zero - single 0 has a length of one, but no 1s for the sytem to count
        for (int q=32;q>=0;q--){
            int r=bitRead(bnry,q);
            if(r==1 && lengthfound == false){
                length=q+1;
                lengthfound = true;
            }
        }
        return length;
    }
    
    
    
    
    // Function to concatenate two binary numbers bitwise 
    unsigned int ConcatBin(unsigned int bina, unsigned int binb){
        int binb_len=findlength(binb);
        unsigned int sum=(bina<<binb_len);
        sum = sum | binb;
        return sum;
    }
    
    
    

};



class ADDAC_PulseGen{
public:
	ADDAC_PulseGen();
    
    
    void setup();	
    void update(int pulsePerCluster, float _speed, float _factor, float _offset);
    
    void checkSlots();
    
    void reset();
    
	
    ADDAC_Points point[numB];
    ADDAC_Timer tm;
    ADDAC_Comparator sl0;
    
    bool slot[6];
    int mute, muteOld;  //1-8
    
};
#endif
