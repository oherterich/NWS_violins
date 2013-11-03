//
//  LinePiece.h
//  track04
//
//  Created by Joseph Moore on 11/1/13.
//
//


#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"

class LinePiece {
public:
    LinePiece();
    void update();
    void draw();
    ofVec3f pos, vel, acc;
    vector<ofVec3f> PosList, floatList;
    ofEasyCam cam;
    
    ofxPostProcessing post;
    ofMaterial material;
    ofLight pointLight;
    float jitter, length;
    bool separate;
    double started;
};