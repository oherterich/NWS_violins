//
//  Dart.h
//  track04
//
//  Created by Joseph Moore on 11/2/13.
//
//


#pragma once

#include "ofMain.h"

class Dart {
public:
    Dart();
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    float mass;
    
    void applyForce( ofVec2f force );
    void update();
    void draw();
    int state;
};