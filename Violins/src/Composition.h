//
//  Composition.h
//  Violins
//
//  Created by Joseph Moore on 10/17/13.
//
//

#pragma once

#include "ofMain.h"
#include "DancingLine.h"
#include "Dart.h"
#include "Vine.h"
#include "Gallifrey.h"

class Composition {
    
public:
    void setup();
    void update();
    void draw();
    
    int track, status;
    DancingLine line1, line2;
    
    float pitch01, pitch02, attack01, attack02, amp01, amp02;
    
    double started;
    vector<Dart> darts;
    vector<Vine> vines;
    Gallifrey g;
    
    vector<ofVec3f> PosList, floatList, explodeList;
    ofEasyCam cam;
    ofVec3f pos, tmp, lastpos, camstart;
    float lastChannel01_Attack;
    float lastChannel01_Amplitude;
    
    ofxPostProcessing post;
    ofMaterial material;
    ofLight pointLight, pointLight2, pointLight3;

};
