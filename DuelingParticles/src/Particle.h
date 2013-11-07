//
//  Particle.h
//  DuelingParticles
//
//  Created by Jorge Proano on 10/28/13.
//
//


#pragma once
#include "ofMain.h"


class Particle{
    
public:
    Particle();
    
    void applyForce(ofVec3f force);
    void atractToOrigin();
    void update();
    void debugDraw();
    void resetVel();
    bool CheckifAlive();
    
    ofVec3f pos, vel, acc;
    ofVec3f origin;
    float damping;
    float life;
    float bornTime;
    float lifeNorm;
    float renderSize;
    
};
