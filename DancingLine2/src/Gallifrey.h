//
//  Gallifrey.h
//  track04
//
//  Created by Joseph Moore on 11/4/13.
//
//

#pragma once

#include "ofMain.h"
#include "rectangle.h"
#include "Particle.h"

class Gallifrey {
public:
    Gallifrey();
    void update();
    void draw();
    void drawLines();
    void addParticle();
    
    void U();
    void I();
    void O();
    void P();
    
    bool storm;
    
    circle myCircle;
    
    bool snow = false;
    bool vac = false;
    
    vector<circle> cirList;
    vector<Particle> particleList;
    bool flickering;
    vector<ofVec3f> PosList, floatList, explodeList;
    ofEasyCam cam;
    ofVec3f tmp, lastpos;
    float lastChannel01_Attack;
    float lastChannel01_Amplitude;
    ofxPostProcessing post;
    ofMaterial material;
    ofLight pointLight, pointLight2, pointLight3;
    
    float w,h;
};

