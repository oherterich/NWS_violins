

#include "rectangle.h"

circle::circle(){
    
    c=ofColor(255);
    t=255;
    
    ofSetLineWidth(2);
    

    
    
}

void circle::drawCircle(float r){
    ofNoFill();
    ofSetColor(c, t);
    ofCircle(pos.x, pos.y, r);
    
//    ofRotate(angle);
    
//    if(r>4){
//    
//       drawCircle(x+r/2,y,r/2);
//       drawCircle(x,y+r/2,r/2);
//        
//    }
}


void circle::update(){
//    angle+=.5f;
}

void circle::move(float x, float y){
    
}

void circle::rota(float a){
    ofRotate(a);
}