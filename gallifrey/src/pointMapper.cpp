//
//  pointMapper.cpp
//  gallifrey
//
//  Created by Keion Anthony Marefat on 10/21/13.
//
//

#include "pointMapper.h"

Mapper::Mapper(){
    red=100;
    green=60;
    blue=150;
    
    ofSetLineWidth(2);
    
    
}

void Mapper::Place(float x, float y, float r){
    ofVec3f spot = ofVec3f(x, y, r);
    radius = r;
    posList.push_back(spot);
    ofRotate(angle);
    
    if(r>4){
        
        Place(x+r/2,y,r/2);
        Place(x,y+r/2,r/2);
        
    }
}


void Mapper::update(){
    
    angle+=(radius*.00008);

    
    
    //COOL SHIT I DUNNO WHAT TO DO WITH
   //  angle+=(-disp);
}