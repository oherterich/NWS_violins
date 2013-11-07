//
//  DancingLine.h
//  track04
//
//  Created by Joseph Moore on 10/31/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "LinePiece.h"

class DancingLine {
public:
    DancingLine();
    void update(float attack, double start);
    void draw(float pitch);
    void updatePiece();
    
    void drawPiece(float x=0, float y=0);
    
    vector<ofVec3f> PosList, floatList, explodeList;
    ofEasyCam cam;
    ofVec3f pos, tmp, lastpos;
    float lastChannel01_Attack;
    float lastChannel01_Amplitude;
    
    ofxPostProcessing post;
    ofMaterial material;
    ofLight pointLight, pointLight2, pointLight3;
    float jitter;
    bool separate, rage;
    double started;
    vector<LinePiece> pieces;
    ofColor c, lastc;
    ofVec2f flat;
};