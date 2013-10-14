//
//  system.cpp
//  NWS_forms
//
//  Created by Tiam Taheri on 10/14/13.
//
//

#include "system.h"




void system::setup() {
    //ofBackground(255);
    counter = 0;
    startX = 0;
    lineSize=250;
    ofSetLineWidth(0);
    ofSetColor(255);
}

void system::draw() {
    
    ofLine(0, ofGetHeight()/2, lineSize, ofGetHeight()/2);
    ofTranslate(startX+lineSize, ofGetHeight()/2);
    branch(lineSize);
}


void system::branch(int ls) {
    
    if (ls>1) {
        counter++;
        ls*=0.8;
        ofPushMatrix();
        ofRotate(45);
        ofLine(startX, 0, startX+ls, 0);
        ofTranslate(startX+ls, 0);
        branch(ls);
        ofPopMatrix();
        
        ofPushMatrix();
        ofRotate(-45);
        ofLine(startX, 0, startX + ls, 0);
        ofTranslate(startX + ls, 0);
        branch(ls); 
        ofPopMatrix();
    }
}
