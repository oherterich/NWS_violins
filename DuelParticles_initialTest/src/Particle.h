//
//  Particle.h
//  violinParticleTest
//
//  Created by Owen Herterich on 10/6/13.
//
//

#pragma once

#include "ofMain.h"

class Particle {
public:
    Particle( ofVec2f _pos, ofVec2f _vel, ofColor _c, float _size, float _trans, ofImage *_img);
    void update();
    void draw();
    void setParams( ofVec2f _pos, ofVec2f _vel, ofColor _c, float _size, float _trans );
    void addForce( ofVec2f force );
    void attractionForce( float px, float py, float strength );
    void addRepulsionForce( float px, float py, float radius, float strength);
    void addClockwiseForce( float px, float py, float radius, float strength);
    void addNoise(float vigor);
    void lerpToColor(ofColor startColor, ofColor endColor, float amt);
    void burst(float px, float py, float multiplier);
    void addDamping();
    bool kill();
    
    ofVec2f pos, vel, acc;
    ofColor c;
    float trans, initTrans;
    float age, life;
    float size, initSize;
    float damping;
    float noiseOffsetA, noiseOffsetB;
    
    ofImage *img;
    
};
