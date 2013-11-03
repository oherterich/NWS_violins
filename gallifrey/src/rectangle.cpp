

#include "rectangle.h"

circle::circle(){
    red=100;
    green=60;
    blue=150;
    
    ofSetLineWidth(2);
    
    
}

void circle::drawCircle(float x, float y, float r){
    ofNoFill();
    ofSetColor(200,170,0,255);
    ofCircle(x, y, r);
    
    ofRotate(angle);
    
    if(r>4){
    
       drawCircle(x+r/2,y,r/2);
       drawCircle(x,y+r/2,r/2);
        
    }
}


void circle::update(){
    angle+=.02f;
}