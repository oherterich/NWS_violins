//
//  Particle.h
//  particle0
//
//  Created by Keion Anthony Marefat on 10/10/13.
//
//

#include "ofMain.h"
#pragma once

class Particle {
public:
    Particle();
    
    void update();
    void draw();
    
    void setParams( float px, float py, float vx, float vy, float _size );
    void addForce( ofVec2f force );
    void addDampingForce();
    void addDampingForce(float val);
    void addRepulsionForce( float px, float py, float radius, float strength);
    void addAttractionForce( float px, float py, float radius, float strength);
    void addClockwiseForce( float px, float py, float radius, float strength);
    void addCounterClockwiseForce( float px, float py, float radius, float strength);
    void burst(float px, float py, float r, float multiplier);
    void xenoToPoint(float catchX, float catchY, float catchUpSpeed);
    void lerpToColor(ofColor start, ofColor end, float amt);
    void resize(float target, float startTime, float endTime);
    void addNoise(float vigor);
    void applyGravity(float g, float floor);
    void applyBounds();
    void resetForces();
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;
    
    ofColor c;
    float size;
    float newSize;
    
    ofVec2f damping;
    
    
};