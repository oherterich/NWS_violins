//
//  Line.h
//  Violins
//
//  Created by Joseph Moore on 10/20/13.
//
//

#pragma once

#include "ofMain.h"

class Line {
    
public:
    Line();
    void update();
    void draw();

    float width, frequency, peak, length;
    ofColor color;
    ofVec2f pos, vel, acc;
    vector<ofPoint> pts, pts2;
    
    void dance();
    void scroll();
};
