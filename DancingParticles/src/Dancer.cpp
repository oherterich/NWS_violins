//
//  Dancer.cpp
//  DancingParticles
//
//  Created by Owen Herterich on 10/14/13.
//
//

#include "Dancer.h"

Dancer::Dancer( ofVec2f _pos, ofVec2f _vel, float _size, float trailLength ) {
    
    pos = _pos;
    vel = _vel;
    size = _size;
    
    initPos = pos;
    
    for (int i = 0; i < trailLength; i++ ) {
        ofVec2f p;
        p.x = pos.x;
        p.y = pos.y;
        
        trail.push_back( p );
    }
    
    c.setHsb(160 + ofRandom(-20, 20), 180, 220);
    
    offset = ofRandom(500, 5000);
    speed = ofRandom(0.1, 1.0);
    amplitude = ofRandom(25, 100);

}

ofVec2f Dancer::trailXeno(float catchX, float catchY, float catchUpSpeed, ofVec2f p) {
    ofVec2f newPoint = p;
    newPoint.x = catchUpSpeed * catchX + (1-catchUpSpeed) * newPoint.x;
    newPoint.y = catchUpSpeed * catchY + (1-catchUpSpeed) * newPoint.y;
    
    return newPoint;
}

void Dancer::updateTrail() {
    trail[0] = trailXeno(pos.x, pos.y, 0.3, trail[0]);
    
    for (int i = 1; i < trail.size(); i++) {
        trail[i] = trailXeno(trail[i-1].x, trail[i-1].y, 0.3, trail[i]);
    }
}

void Dancer::drawTrail() {
    for (int i = 0; i < trail.size(); i++) {
        float pct = 1.0 - i / (float)trail.size();
        float thisSize = size * pct;
        float thisTrans = 255 * pct;
        ofSetColor(c, thisTrans);
        ofCircle(trail[i], thisSize);
    }
}

void Dancer::noiseMovement() {
    float noise = ofNoise(pos.x * 0.005, pos.y*0.005, ofGetElapsedTimef() * 0.1) * 15.0;
    pos += ofVec2f( cos(noise), sin(noise) ) * vel;
}

void Dancer::sinMovement( float coef ) {
    pos.x += vel.x;
    pos.y += sin( coef * (ofGetElapsedTimef() * speed) * vel.y ) * amplitude;
}

void Dancer::lissajousMovement(){
    pos.x = sin(5 * ofGetElapsedTimef() * speed + offset) * amplitude + initPos.x;
    pos.y = cos(4 * ofGetElapsedTimef() * speed + offset) * amplitude + initPos.y;
}

void Dancer::update(ofVec2f _mouse) {
    
    mouse = _mouse;
    
    //pos = mouse;
    
    noiseMovement();
    //sinMovement(2.0);
    //lissajousMovement();
    updateTrail();
    
    //vel+=frc;
    //pos+=vel;
}


void Dancer::draw() {
    
    drawTrail();
    
    ofSetColor(c);
    ofCircle(pos, size);
}