//
//  Dart.cpp
//  track04
//
//  Created by Joseph Moore on 11/2/13.
//
//

#include "Dart.h"

Dart::Dart() {
    mass = 1.0;
}

void Dart::applyForce(ofVec2f force){
    acc += (force / mass);
}

void Dart::update(){
    vel += acc;
    pos += vel;
    
    //    vel*= 0.97;
    
    acc.set(0);
    
//    if(pos.x<0 || pos.x>ofGetWidth()){
//        vel.x *= -1.0;
//    }
//    if(pos.y<0 || pos.y>ofGetWidth()){
//        vel.y *- -1.0;
//    }
}

void Dart::draw() {
    ofSetColor(255);
    ofCircle( pos, 10 );
}