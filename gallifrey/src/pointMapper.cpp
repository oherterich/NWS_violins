//
//  pointMapper.cpp
//  gallifrey
//
//  Created by Keion Anthony Marefat on 10/21/13.
//
//

#include "pointMapper.h"

Mapper::Mapper(){
    ofSetLineWidth(2);
    
    
}

//void Mapper::Place(){
//    ofVec3f spot = ofVec3f(ofGetWidth()/2, ofGetHeight()/2, r);
//    radius = r;
//    posList.push_back(spot);
//    }
//}


void Mapper::update(){
    
    angle+=(radius*.00008);

    
    
    //COOL SHIT I DUNNO WHAT TO DO WITH
   //  angle+=(-disp);
}