//
//  LinePiece.cpp
//  track04
//
//  Created by Joseph Moore on 11/1/13.
//
//

#include "LinePiece.h"

LinePiece::LinePiece(){
    
//    pos = ofVec3f(ofRandom(ofGetWidth(),ofGetHeight()),ofRandom(ofGetWidth(),ofGetHeight()),ofRandom(ofGetWidth(),ofGetHeight()));
    vel = ofVec3f(ofRandom(-20,20),ofRandom(-20,20),ofRandom(-20,20));
}

void LinePiece::update(){
    vel += acc;
    pos += vel;
//    vel *= 0.97;
    acc.set(0);
//
//    cam.setPosition(pos.x-400, pos.y-400, pos.z-400);
//
//    pointLight.setPosition(pos);
}

void LinePiece::draw(){
    jitter = ofRandom(-10,10);
    ofPushMatrix();
    for(int i=0; i<100; i++){
        ofLine(pos.x+i/20.0*ofRandom(-jitter,jitter),pos.y+i/20.0*ofRandom(-jitter,jitter),pos.z+i/20.0*ofRandom(-jitter,jitter), pos.x+100.0+i/20.0*ofRandom(-jitter,jitter),pos.y+i/20.0*ofRandom(-jitter,jitter),pos.z+i/20*ofRandom(-jitter,jitter));        
    }
    ofPopMatrix();
}