//
//  Vine.h
//  track04
//
//  Created by Joseph Moore on 11/3/13.
//
//


#pragma once

#include "ofMain.h"

class Vine {
public:
    Vine();
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    float mass, heightY;
    
    void applyForce( ofVec2f force );
    void update();
    void wither();
    void draw(float pitch);
    int state;
    vector<ofVec3f> ps;
    vector<float> rs;
    ofColor color;
};