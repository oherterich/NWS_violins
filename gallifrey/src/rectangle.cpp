

#include "rectangle.h"

circle::circle(){
    
    c=ofColor(255);
    t=255;
    ofSetLineWidth(2);
    angle=ofRandom(TWO_PI);
    
    disp=ofRandom(-.1f, .1f);
    fSpeed=ofRandom(.75, 2);
    vel=0;
    grav=.08f;
    
}

void circle::addCircle(float r){
    rad=r;
    pRad=ofDist(pos.x, pos.y, ofGetWidth()/2, ofGetHeight()/2);
    tRad=250-rad;
    
    disp=(ofMap(rad, 100,2, .00075, .025));
    
    if(rand()%3==0){
        disp*=-1;
    }
    sDisp=disp;
}

void circle::drawCircle(){
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(10);
//    ofSetColor(c, t);
    ofCircle(pos.x, pos.y, rad);
    ofPopStyle();
}


void circle::update(){
    if(pRad>tRad){
        pRad-=2;
    }
    
    //Slow code
    if(slowToStop){
        stopped=true;
        if(abs(sDisp)>.0002){
            sDisp-=(sDisp-0)/50;
            
            if(abs(sDisp)<.0002){
                sDisp=0;
            }
        }
    }else if(!slowToStop && abs(sDisp)<abs(disp*mod)){
        sDisp+=((disp*mod)-sDisp)/150;
        if(stopped) mod+=.003;
    }
    
    
}

void circle::move(){
    if(sDisp>0){
        if(angle>TWO_PI)angle=0;
    }else if(sDisp<=0){
        if(angle<0)angle=TWO_PI;
    }
    
    angle+=sDisp;
    
    pos.x=(pRad*cos(angle))+ofGetWidth()/2;
    pos.y=(pRad*sin(angle))+ofGetHeight()/2;
    
}

void circle::rota(float a){
    ofRotate(a);
}

void circle::fall(){
    if(slowToStop){
    pos.y+=vel;
    vel+=grav;
        
        if(pos.x>=ofGetHeight()-rad){
            vel*=-.9;
        }
        
        
    }
    
}

void circle::drawLines(){
    ofNoFill();
    ofSetColor(c, t);
    //    ofCircle(pos.x, pos.y, rad);
    ofSetLineWidth(10);
    for(int i=0; i<20; i++){
        float jitter = 5.0;
            // use mesh here
        ofLine(pos.x+ofRandom(-jitter, jitter), pos.y+ofRandom(-jitter, jitter), ofRandom(-100,100), pos.x+ofRandom(-jitter, jitter)+rad, pos.y+ofRandom(-jitter, jitter), ofRandom(-100,100));
    }
}
