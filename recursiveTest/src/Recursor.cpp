//
//  Recursor.cpp
//  recursiveTest
//
//  Created by Keion Anthony Marefat on 10/14/13.
//
//

#include "Recursor.h"
#include "ofMain.h"



Recursor::Recursor() {
    countz = 0;
    startX = 0;
    lineSize=100;
    ofSetColor(0);
}


void Recursor::branch(int ls) {
    
    if (ls>10) {
        countz++;
        ls*=.8;
        width*=.7;
        ofPushMatrix();
        ofRotate(45);
        ofLine(startX, 0, startX+ls, 0);
        ofTranslate(startX+ls, 0);
        branch(ls);
        ofPopMatrix();
        
        ofPushMatrix();
        ofRotate(-45);
        ofLine(startX, 0, startX+ls, 0);
        ofTranslate(startX+ls, 0);
        branch(ls); 
        ofPopMatrix();
    }
}

    void Recursor::draw() {
        ofLine(0, ofGetHeight()/2, lineSize, ofGetHeight()/2);
        ofTranslate(startX+lineSize, ofGetHeight()/2);
        branch(lineSize);
    }
