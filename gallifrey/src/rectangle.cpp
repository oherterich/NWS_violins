

#include "rectangle.h"

circle::circle(){
    
    c=ofColor(255);
    t=255;
    ofSetLineWidth(2);
    angle=ofRandom(TWO_PI);
    
    disp=ofRandom(-.1f, .1f);
    fSpeed=ofRandom(.75, 2);
    vel=0;
    grav= .5f;
    
    falling=false;
    fixing=false;
    
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
    
    if(fixing){
        falling=false;
        antiFall();
    } else if(falling){
        fall();
    }else{
        pos.x=(pRad*cos(angle))+ofGetWidth()/2;
        pos.y=(pRad*sin(angle))+ofGetHeight()/2;
    }
}

void circle::rota(float a){
    ofRotate(a);
}


void circle::fall(){
    
    if(slowToStop){
    pos.y+=vel;
    vel+=grav;
        
        if(pos.y>=ofGetHeight()-rad){
            vel*=-.4;
            pos.y=ofGetHeight()-rad-1;
            touchdown=true;
        }
        
    }
    
}

void circle::antiFall(){
 //       grav= -.5f;
    
    if(touchdown){
        pos.y+=vel;
        vel+=grav;
        
        if(pos.y>=ofGetHeight()-rad){
            pos.y=ofGetHeight()-rad-1;
            vel*=-1.6;
        }
    }
    if(ofDist(pos.x, pos.y, (pRad*cos(angle))+ofGetWidth()/2,(pRad*sin(angle))+ofGetHeight()/2)<=50 ||
       pos.y<=ofGetHeight()/2){
        touchdown=false;
        pos.x = .15 * ((pRad*cos(angle))+ofGetWidth()/2) + (1-.15) * pos.x;
        pos.y = .15 * ((pRad*sin(angle))+ofGetHeight()/2) + (1-.15) * pos.y;
        if(ofDist(pos.x, pos.y, (pRad*cos(angle))+ofGetWidth()/2,(pRad*sin(angle))+ofGetHeight()/2)<=5){
            fixing=false;
            pos.x=(pRad*cos(angle))+ofGetWidth()/2;
            pos.y=(pRad*sin(angle))+ofGetHeight()/2;
            }
        }
}
void circle::drawLines(){
    ofNoFill();
//    ofSetColor(c, t);
    //    ofCircle(pos.x, pos.y, rad);
    ofSetLineWidth(10);
    for(int i=0; i<20; i++){
        float jitter = 5.0;
            // use mesh here
        ofLine(pos.x+ofRandom(-jitter, jitter)-rad, pos.y+ofRandom(-jitter, jitter), ofRandom(-100,100), pos.x+ofRandom(-jitter, jitter)+(rad), pos.y+ofRandom(-jitter, jitter), ofRandom(-100,100));
    }
}
