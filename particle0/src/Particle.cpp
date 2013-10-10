//
//  Particle.cpp
//  particle0
//
//  Created by Keion Anthony Marefat on 10/10/13.
//
//

#include "Particle.h"

Particle::Particle() {
    setParams(0,0,0,0,3);
    damping = ofVec2f( 0.01f );
    
}

void Particle::setParams( float px, float py, float vx, float vy, float _size ){
    pos.set( px, py );
    vel.set( vx, vy );
    c=ofColor(255);
    size = _size;
}

//----------------------------------------------------------
//Adding Forces (Gradual gain / loss. Use of "resetForces" encouraged.)

void Particle::addAttractionForce( float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x -= diff.x * pct * strength;
        frc.y -= diff.y * pct * strength;
    }
}

void Particle::addClockwiseForce( float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x -= diff.y * pct * strength;
        frc.y += diff.x * pct * strength;
    }
}

void Particle::addCounterClockwiseForce( float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x += diff.y * pct * strength;
        frc.y -= diff.x * pct * strength;
    }
}

void Particle::addDampingForce() {
    frc = frc - vel * damping;
}


void Particle::addDampingForce(ofVec2f val) {
    damping = val;
    frc = frc - vel * damping;
}


void Particle::addForce( ofVec2f force ){
    frc += force;
}

void Particle::applyGravity(float g, float floor) {
    if(pos.y <= floor){
        vel.y += g;
    }
}
void Particle::addRepulsionForce( float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x += diff.x * pct * strength;
        frc.y += diff.y * pct * strength;
    }
}

void Particle::xenoToPoint(float catchX, float catchY, float catchUpSpeed){
    pos.x = catchUpSpeed * catchX + (1-catchUpSpeed) * pos.x;
    pos.y = catchUpSpeed * catchY + (1-catchUpSpeed) * pos.y;
}
//----------------------------------------------------------
//Visuals

void Particle::lerpToColor(ofColor start, ofColor end, float amt){
    c=start;
    c.lerp(end, amt);
}
//----------------------------------------------------------
//Animations

void Particle::burst(float px, float py, float r, float multiplier){    //Reccomended pairing: Damping
    float circVal = ofRandom(TWO_PI);
    float vx = cos( sin(circVal) ) * ofRandom(0,multiplier);
    float vy = sin( sin(circVal) ) * ofRandom(0,multiplier);
    
    pos.set(px, py);
    vel.set(vx, vy);
}

void Particle::resize(float target, float startTime, float endTime){
    ofMap(newSize, size, target, startTime, endTime);
    size=newSize;
}

void Particle::addNoise(float vigor){
    float noise = ofNoise(pos.x * 0.005, pos.y*0.005, ofGetElapsedTimef() * 0.1) * 15.0;
    pos += ofVec2f( cos(noise), sin(noise) ) * vigor;
}
//----------------------------------------------------------
//Utilities


void Particle::resetForces() {
    frc.set(0,0);
}


//----------------------------------------------------------
//Update / Draw

void Particle::update() {
    vel = vel + frc;
    pos = pos + vel;
}

void Particle::draw() {
    ofSetColor(c);
    ofCircle(pos.x, pos.y, size);
}
