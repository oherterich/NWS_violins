//
//  Particle.cpp
//  violinParticleTest
//
//  Created by Owen Herterich on 10/6/13.
//
//

#include "Particle.h"

Particle::Particle( ofVec2f _pos, ofVec2f _vel, ofColor _c ) {
    pos = _pos;
    vel = _vel;
    c = _c;
    
    age = 0;
    life = ofRandom(800,1000);
    
    size = 4;
    trans = 150;
    
    damping = 0.03;
}

void Particle::addForce( ofVec2f force ) {
    acc += force;
}

void Particle::attractionForce( float strength ) {
    ofVec2f loc;
    loc.set(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    
    ofVec2f diff;
    diff = pos - loc;
    
    diff.normalize();
    acc.x -= diff.x * strength;
    acc.y -= diff.y * strength;
}

void Particle::addDamping() {
    acc.x = acc.x - vel.x * damping;
    acc.y = acc.y - vel.y * damping;
}

void Particle::update() {
    vel += acc;
    pos += vel;
    
    float pct = 1 - age / life;
    trans = 255.0 * pct;
    
    age += 1.0;
    
    size = 4 * pct;
    
    acc.set(0.0);
}

void Particle::draw() {
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor( c, trans );
    ofRect( pos, size, size );
}

bool Particle::kill() {
    if (age >= life) {
        return true;
    }
    else return false;
}