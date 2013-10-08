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
    Particle( ofVec2f _pos, ofVec2f _vel, ofColor _c );
    void update();
    void draw();
    void addForce( ofVec2f force );
    void attractionForce( float strength );
    void addDamping();
    bool kill();
    
    ofVec2f pos, vel, acc;
    ofColor c;
    float trans;
    float age, life;
    float size;
    float damping;
};
