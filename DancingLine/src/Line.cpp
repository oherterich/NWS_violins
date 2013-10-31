//
//  Line.cpp
//  DancingLine
//
//  Created by Joseph Moore on 10/30/13.
//
//

#include "Line.h"
Line::Line() {
    spacing = 100.0;
    width = 20.0;
    length = ofGetWidth()/2;
    speed = 1.0;
    for(int i=0; i<(length/spacing)+1;i++){
        Particle p;
        vertices.push_back(p);
    }
}


void Line::update(FlowField F){
    for(int i=0; i<vertices.size(); i++){
        vertices[i].update();
    }
    for( int i=0; i<vertices.size(); i++ ){
        vertices[i].applyForce( F.getForceAtPosition(vertices[i].pos ) * 0.005 );
        vertices[i].update();
    }
}

void Line::draw() {
    for(int i=1; i<vertices.size(); i++){
        ofSetLineWidth(width);
        ofLine(vertices[i-1].pos.x,vertices[i-1].pos.y,vertices[i].pos.x,vertices[i].pos.y);
    }
}