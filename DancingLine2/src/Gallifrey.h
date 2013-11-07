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
    void draw(float pitch1, float pitch2, int type=0);
    void drawLines(float pitch1, float pitch2);
    void drawCircles(float pitch1, float pitch2);
    void addParticle();
    
    void U();
    void I();
    void O();
    void P();
    void H();
    
    bool storm;
    
    circle myCircle;
    
    bool snow = false;
    bool vac = false;
    bool chainFall= false;
    bool chainFix= false;
    
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
    ofColor newc, lastc, c;
    void clearCircles();
    float state, state_motion, state_time;
 //   float startR;
};

