//
//  Particle.cpp
//  DuelingParticles
//
//  Created by Jorge Proano on 10/28/13.
//
//

#include "Particle.h"

Particle::Particle(){
    
    damping = 0;
    life = 0;
    bornTime = ofGetElapsedTimef();
    lifeNorm = 0;
    
    pos.set(0);
    vel.set(0);
    acc.set(0);
    renderSize = 0;
    
}

void Particle::applyForce(ofVec3f force){
    
    acc +=force;
    
}

void Particle::resetVel(){
    
    vel.set(0);
}


void Particle::update(){
    
    vel += acc;
    vel -= damping;
    
    pos += vel;
    
    lifeNorm = (ofGetElapsedTimef()-bornTime)/life;
    acc.set(0);
    
}

void Particle::debugDraw(){
    ofPushStyle();
    ofFill();
    ofSetColor(ofColor::magenta);
    ofCircle(pos, 0.5f);
    ofPopStyle();
    
}


bool Particle::CheckifAlive(){
    if (lifeNorm > 1) {
        return true;
    } else {
        return false;
    }
    
}

void Particle::atractToOrigin(){
    
    pos += origin*0.01;
}
    


    
