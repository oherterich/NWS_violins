//
//  Dancer.h
//  DancingParticles
//
//  Created by Owen Herterich on 10/14/13.
//
//

#pragma once

#include "ofMain.h"

class Dancer {
public:
    Dancer( ofVec2f _pos, ofVec2f _vel, float _size, float trailLength );
    void update( ofVec2f _mouse );
    void draw();
    void setParams( ofVec2f _pos, ofVec2f _vel );
    ofVec2f trailXeno( float catchX, float catchY, float catchUpSpeed, ofVec2f p );
    void updateTrail();
    void drawTrail();
    void noiseMovement();
    void sinMovement( float coef );
    void lissajousMovement();
    
    ofVec2f pos, vel, frc;
    
    ofVec2f initPos;
    
    vector<ofVec2f> trail;
    
    float size;
    ofColor c;
    
    ofVec2f mouse;
    
    float offset, speed, amplitude;
};
