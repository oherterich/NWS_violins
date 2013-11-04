//
//  Vine.cpp
//  track04
//
//  Created by Joseph Moore on 11/3/13.
//
//

#include "Vine.h"

Vine::Vine() {
    mass = 1.0;
    float r = ofRandom(500);
    pos = ofVec3f(ofRandom(ofGetWidth()/2-250, ofGetWidth()/2+250), ofGetHeight(), 0);
    vel = ofVec3f(0,ofRandom(-1.0,-5.0));
    heightY = ofRandom(300.0, 400.0);
    color = ofColor(255,0,0);
    color.setSaturation(0);
    color.setBrightness(ofRandom(150,255));

}

void Vine::applyForce(ofVec2f force){
    acc += (force / mass);
}

void Vine::update(){
    if(ps.size()>0){
        pos.x = ps[ps.size()-1].x;
    }
    if(pos.y < heightY+50.0){
        vel *= 0.7;
    }
    
    if(pos.y > heightY+50.0){
        ps.push_back(pos+ofVec3f(ofRandom(-2.0,2.0), 0, 0));
        rs.push_back((5.0-(rs.size()*0.02)));
        if (ps.size()>500) {
            ps.erase(ps.begin());
            rs.erase(rs.begin());
        }
    }

    vel += acc;
    pos += vel;

    acc.set(0);
    
    //    if(pos.x<0 || pos.x>ofGetWidth()){
    //        vel.x *= -1.0;
    //    }
    //    if(pos.y<0 || pos.y>ofGetWidth()){
    //        vel.y *- -1.0;
    //    }

}

void Vine::draw() {
    ofPushStyle();
    ofSetCircleResolution(5);
    ofSetColor(255);
    for(int i=0; i<ps.size(); i++){
        ofSetColor(color);
        ofCircle( ps[i], ofClamp(rs[i], 0, 10.0));
    }
    ofPopStyle();
}