

#include "rectangle.h"

circle::circle(){
    
    c=ofColor(255);
    t=255;
    ofSetLineWidth(2);
    angle=ofRandom(TWO_PI);

    disp=ofRandom(-.1f, .1f);
    fSpeed=ofRandom(.75, 2);
    
}

void circle::addCircle(float r){
    rad=r;
    pRad=ofDist(pos.x, pos.y, ofGetWidth()/2, ofGetHeight()/2);
    tRad=250-rad;
    
    disp=(ofMap(rad, 100,2, .00075, .025));
    
    if(rand()%3==0){
        disp*=-1;
    }
    
}

void circle::drawCircle(){
    ofNoFill();
    ofSetLineWidth(5);
    ofSetColor(c, t);
    ofCircle(pos.x, pos.y, rad);
    
}

void circle::drawLines(){
    ofNoFill();
    ofSetColor(c, t);
    //    ofCircle(pos.x, pos.y, rad);
    ofSetLineWidth(10);
    for(int i=0; i<100; i++){
        float jitter = 5.0;
        
        ofLine(pos.x+ofRandom(-jitter, jitter), pos.y+ofRandom(-jitter, jitter), ofRandom(-100,100), pos.x+ofRandom(-jitter, jitter)+rad, pos.y+ofRandom(-jitter, jitter), ofRandom(-100,100));
    }
}


void circle::update(){
    if(pRad>tRad){
        pRad-=2;
    }

}

void circle::move(){
    if(disp>0){
        if(angle>TWO_PI)angle=0;
    }else if(disp<=0){
        if(angle<0)angle=TWO_PI;
    }
    
    angle+=disp;
    
    pos.x=(pRad*cos(angle))+ofGetWidth()/2;
    pos.y=(pRad*sin(angle))+ofGetHeight()/2;
    
}

void circle::rota(float a){
    ofRotate(a);
}