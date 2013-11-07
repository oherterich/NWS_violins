//
//  Gallifrey.cpp
//  track04
//
//  Created by Joseph Moore on 11/4/13.
//
//

#include "Gallifrey.h"

//--------------------------------------------------------------
Gallifrey::Gallifrey(){
    ofSetCircleResolution(1000);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofBackground(0);
    w = ofGetWidth()/2;
    h = ofGetHeight()/2;
    circle p;
    p.addCircle(250);
    p.pos.x=w;
    p.pos.y=h;
    p.pRad = 0;
    cirList.push_back(p);
    flickering = false;
//    startR=350;
}

void Gallifrey::addParticle() {
    Particle tmp;
    
    double ax = ofRandom(TWO_PI);
    
    tmp.setParams(250*cos(ax)+w, 250*sin(ax)+h, 0, 0, 1.5);
    
    tmp.life = 75;
    
    particleList.push_back( tmp );
}

//--------------------------------------------------------------
void Gallifrey::update(){

    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end();it++) {
        
        //  it->addNoise(ofMap(it->pos.y, ofGetHeight()+1+it->initSize/2, 0, 0, .3));
        
        
        if(storm){
            it->addClockwiseForce(w, h, w, .1);
            it->addAttractionForce(w, h, w,
                                   ofMap(ofDist(it->pos.x, it->pos.y, w,h), w, 0, .3,.1));
            
            if(ofDist(it->pos.x, it->pos.y, w, h)>250){
                it->pos-=ofVec2f(w, h).normalized()*2*it->vel;
            }
            
            if(ofDist(it->pos.x, it->pos.y, w,h)<50){
                it->consigned=true;
            }
            
        }
        it->ageVisuals(true, false);
        
        it->update();
        it->resetForces();
    }
    
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end();it++) {
        
        if (it->dead()==true) {
            particleList.erase(it);
            break;
        }
    }
    
}

//--------------------------------------------------------------
void Gallifrey::draw(float pitch1, float pitch2){
    ofPushStyle();
    if(flickering == true){
        ofSetCircleResolution((int)ofRandom(10));
    }
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); it++) {
        it->draw();
    }
    
    ofNoFill();
    ofSetColor(255, 255, 255, 255);
    for (int i = 0; i<cirList.size(); i++) {
        float pitch;
        if(i==0){
            pitch = pitch1;
        } else {
            pitch = pitch2;
        }
        ofColor newc = ofColor(255,0,0);
        newc.setHue(ofClamp(ofMap(pitch,0,3000,0,255),0,255));
        c=lastc;
        c.lerp(newc, 50);
        lastc = newc;
        // c = ofColor(ofClamp(ofMap(pitch,0,3000,0,255),0,255),ofClamp(ofMap(pitch,0,3000,0,255),0,255),ofClamp(ofMap(pitch,0,3000,0,255),0,255));
        ofSetColor(newc);
        cirList[i].drawCircle();
        cirList[i].update();
        cirList[i].move();
        
}
    
    if(chainFall){
        float thresh[cirList.size()];
        for(int i=1; i<cirList.size();i++){
            thresh[i]=ofRandom(ofGetHeight()/2)+ofGetHeight()/2;
        }
        
        for(int i=1; i<cirList.size();i++){
        if(i==cirList.size()) break;
        else if(cirList[i].pos.y >= thresh[i]) cirList[i+1].falling=true;
        }
    }
    if(snow){
        //    if(ofGetElapsedTimeMillis()%3==0 ){
        addParticle();
        // }
    }
    ofPopStyle();
}

void Gallifrey::drawLines(){
    ofPushStyle();
    if(flickering == true){
        ofSetCircleResolution((int)ofRandom(10));
    }
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); it++) {
        it->draw();
    }
    
    ofNoFill();
    ofSetColor(255, 255, 255, 255);
    for (int i = 0; i<cirList.size(); i++) {
        
        cirList[i].drawLines();
        cirList[i].update();
        cirList[i].move();
        
    }
    
    if(snow){
        //    if(ofGetElapsedTimeMillis()%3==0 ){
        addParticle();
        // }
    }
    ofPopStyle();
}

void Gallifrey::U(){
    float x;
    float y;
    
    float temp = rand()%2;
    float temp2= rand()%2;
    
    if (temp==0)  x = ofRandom(-.2*ofGetWidth(), -.3*ofGetWidth());
    if (temp==1)  x = ofRandom(.25*ofGetWidth(), .35*ofGetWidth());
    if (temp2==0)  y = ofRandom(-.35*ofGetHeight(), -.25*ofGetHeight());
    if (temp2==1)  y = ofRandom(-.25*ofGetHeight(), -.35*ofGetHeight());
    
    circle p;
    
    if(cirList.size()<10){
        p.pos.x=x;
        p.pos.y=y;
        
        if(rand()%3>1){
            p.addCircle(ofRandom(40,100));
        } else{
            p.addCircle(ofRandom(2,30));
        }
    }
    
    if(cirList.size()>10){
        p.pos.x=x;
        p.pos.y=y;
        
        if(rand()%3>1){
            p.addCircle(ofRandom(40,100));
        } else{
            p.addCircle(ofRandom(2,30));
        }
        p.tRad=200-p.rad;
    }
    
    cirList.push_back(p);
}

void Gallifrey::I(){
    for(int i=0;i<cirList.size();i++){
        cirList[i].slowToStop=!cirList[i].slowToStop;
    }


}

void Gallifrey::O(){
//    for(int i=1;i<cirList.size();i++){
    chainFall=!chainFall;
//    }

}

void Gallifrey::P(){
//    vac=!vac;
}


void Gallifrey::clearCircles(){
    for(int i=1;i<cirList.size();i++){
        cirList.pop_back();
    }
    cout<<cirList.size()<<endl;
}