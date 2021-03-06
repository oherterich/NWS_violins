//
//  Line.cpp
//  Violins
//
//  Created by Joseph Moore on 10/20/13.
//
//

#include "Line.h"

Line::Line(){
    peak = 20.0;
    pos.set(0, ofGetHeight()/2);
    vel.set(25,0);
    acc.set(0,0);
    length = 0.0;
    frequency = 1.0; // 2 points (one complete oscillation) per 100 pixels
    width = 100.0;
    color = ofColor(0);
}

void Line::update(){
    vel += acc;
    pos += vel;
    acc.set(0);
    if(pos.x<ofGetWidth()){
        pts.push_back(pos);
    }
}

void Line::draw(){
//    ofTranslate(0, cos(ofGetElapsedTimeMillis()/200.0)*100.0);
    for(int i=0; i<pts.size()-1; i++){
        if(pts.size()>1){
            for(int j=0; j<width; j++){
//                color = ofColor(ofRandom(100,255),ofRandom(255),ofRandom(50,255));
//                color.setSaturation(100);
//                color.setBrightness(150);
//                ofSetColor(color);
                ofLine(pts[i].x, pts[i].y+sin(ofGetElapsedTimeMillis()/frequency)*j, pts[i+1].x, pts[i+1].y+cos(ofGetElapsedTimeMillis()/frequency)*j);
            }
        }
    }


// Interesting Weirdness
    
//    if(pts.size()>1){
//        for(int i=0; i<pts.size(); i++){
//    ofPushMatrix();
//            ofTranslate(pts[i].x, pts[i].y);
//                ofLine(0, 0, pts[i+1].x, pts[i+1].y);
//                ofLine(0, peak, pts[i+1].x, pts[i+1].y+peak);
//
//    ofPopMatrix();
//        }
//    }
//    
    
// Tesselation errors
    
//    ofBeginShape(); {
//        if(pts.size()>1){
//            for(int i=0; i<pts.size(); i++){
//                ofVertex(pts[i].x, pts[i].y);
//                ofVertex(pts[i].x, pts[i].y+peak);
//                ofVertex(pts[i+1].x, pts[i+1].y);
//            }
//        }
//    } ofEndShape();
//    
//    ofBeginShape(); {
//        if(pts.size()>1){
//            for(int i=0; i<pts.size(); i++){
//                ofVertex(pts[i].x, pts[i].y+peak);
//                ofVertex(pts[i+1].x, pts[i+1].y+peak);
//                ofVertex(pts[i+1].x, pts[i+1].y);
//            }
//        }
//    } ofEndShape();

    
}