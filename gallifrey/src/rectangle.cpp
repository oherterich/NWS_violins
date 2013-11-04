

#include "rectangle.h"

circle::circle(){
    
    c=ofColor(255);
    t=255;
    ofSetLineWidth(2);
    angle=ofRandom(TWO_PI);

    disp=ofRandom(-.1f, .1f);
    sDisp=disp;
    fSpeed=ofRandom(.75, 2);
    mod=1;
    
}

void circle::addCircle(float r){
    rad=r;
    pRad=ofDist(pos.x, pos.y, ofGetWidth()/2, ofGetHeight()/2);
    tRad=250-rad;
    
    disp=(ofMap(rad, 100,2, .00065, .025));
    sDisp=disp;
    
    if(rand()%3==0){
        disp*=-1;
        sDisp=disp;
    }
    
}

void circle::drawCircle(){
    ofNoFill();
    ofSetColor(c, t);
    ofCircle(pos.x, pos.y, rad);
    
}


void circle::update(){
//Swirl in
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