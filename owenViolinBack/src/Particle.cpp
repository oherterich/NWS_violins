//
//  Particle.cpp
//  violinParticleTest
//
//  Created by Owen Herterich on 10/6/13.
//
//

#include "Particle.h"

Particle::Particle( ofVec2f _pos, ofVec2f _vel, ofColor _c, float _size, float _trans, ofImage *_img) {
    pos = _pos;
    vel = _vel;
    c = _c;

    age = 0;
    life = ofRandom(200,400);

    size = _size;
    initSize = size;
    trans = _trans;
    initTrans = trans;

    damping = 0.03;

    img = _img;

    noiseOffsetA = ofRandom(0.05, 0.15);
    noiseOffsetB = ofRandom(10.0, 20.0);
}

void Particle::setParams( ofVec2f _pos, ofVec2f _vel, ofColor _c, float _size, float _trans ) {
    pos = _pos;
    vel = _vel;
    c = _c;

    age = 0;
    life = ofRandom(200,400);

    size = _size;
    initSize = size;
    trans = _trans;
    initTrans = trans;
}

void Particle::addForce( ofVec2f force ) {
    acc += force;
}

void Particle::attractionForce( float px, float py, float strength ) {
    ofVec2f loc;
    loc.set(px, py);

    ofVec2f diff;
    diff = pos - loc;

    diff.normalize();
    acc.x -= diff.x * strength;
    acc.y -= diff.y * strength;
}

void Particle::addRepulsionForce( float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px, py);

    ofVec2f diff = pos - posOfForce;

    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        acc.x += diff.x * pct * strength;
        acc.y += diff.y * pct * strength;
    }
}

void Particle::addNoise(float vigor){
    float noise = ofNoise(pos.x * 0.005, pos.y*0.005, ofGetElapsedTimef() * noiseOffsetA) * noiseOffsetB;
    pos += ofVec2f( cos(noise), sin(noise) ) * vigor;
}

void Particle::addClockwiseForce( float px, float py, float radius, float strength){
    ofVec2f posOfForce;
    posOfForce.set(px, py);

    ofVec2f diff = pos - posOfForce;

    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        acc.x -= diff.y * pct * strength;
        acc.y += diff.x * pct * strength;
    }
}

void Particle::addDamping() {
    acc.x = acc.x - vel.x * damping;
    acc.y = acc.y - vel.y * damping;
}

void Particle::burst(float px, float py, float multiplier){    //Reccomended pairing: Damping
    float circVal = ofRandom(TWO_PI);
    float vx = cos( sin(circVal) ) * ofRandom(-multiplier, multiplier);
    float vy = sin( sin(circVal) ) * ofRandom(-multiplier, multiplier);

    pos.set(px, py);
    vel.set(vx, vy);
}

void Particle::newMotion(Particle &p){
    p.c.lerp(ofColor(255,200,150),0.05f);
    p.vel.y = sin( ofGetElapsedTimef() * 1.2f );
}

void Particle::update() {
    vel += acc;
    pos += vel;

    float pct = 1 - age / life;
    //trans = initTrans * pct;

    age += 1.0;

    size = initSize * pct;

    acc.set(0.0);
}

void Particle::lerpToColor(ofColor startColor, ofColor endColor, float amt){
    c=startColor;
    c.lerp(endColor, amt);
}

void Particle::draw() {
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor( c, trans );
    ofPushMatrix();
    ofTranslate(pos);
    img->draw(0,0);
    ofPopMatrix();
    //ofRect( pos, size, size );
}

bool Particle::kill() {
    if (age >= life) {
        return true;
    }
    else return false;
}
