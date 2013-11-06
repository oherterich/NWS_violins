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
    
    circle p;
    p.addCircle(250);
    p.pos.x=ofGetWidth()/2;
    p.pos.y=ofGetHeight()/2;
    p.pRad = 0;
    cirList.push_back(p);
    flickering = false;
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<RimHighlightingPass>();
    post.createPass<VerticalTiltShifPass>();
    post.createPass<GodRaysPass>();
    //    post.createPass<ContrastPass>();
    
    post.createPass<FxaaPass>();
    //    post.createPass<BloomPass>();
    //    post.createPass<SSAOPass>();
    
    ofSetSphereResolution(24);
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight.setSpotlight(800.0, 2.0);
    pointLight2.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight2.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight2.setSpotlight(1000.0, 2.0);
    material.setShininess( 200 );
    material.setAmbientColor(ofColor((255)));
    // the light highlight of the material //
	material.setSpecularColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255));
    cam.setPosition(0,0,4000);
}

void Gallifrey::addParticle() {
    Particle tmp;
    
    double ax = ofRandom(TWO_PI);
    
    tmp.setParams(250*cos(ax)+ofGetWidth()/2, 250*sin(ax)+ofGetHeight()/2, 0, 0, 1.5);
    
    tmp.life = 75;
    
    particleList.push_back( tmp );
}

//--------------------------------------------------------------
void Gallifrey::update(){
    
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end();it++) {
        
        //  it->addNoise(ofMap(it->pos.y, ofGetHeight()+1+it->initSize/2, 0, 0, .3));
        
        
        if(storm){
            it->addClockwiseForce(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, .1);
            it->addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2,
                                   ofMap(ofDist(it->pos.x, it->pos.y, ofGetWidth()/2,ofGetHeight()/2), ofGetWidth()/2, 0, .3,.1));
            
            if(ofDist(it->pos.x, it->pos.y, ofGetWidth()/2, ofGetHeight()/2)>250){
                it->pos-=ofVec2f(ofGetWidth()/2, ofGetHeight()/2).normalized()*2*it->vel;
            }
            
            if(ofDist(it->pos.x, it->pos.y, ofGetWidth()/2,ofGetHeight()/2)<50){
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
void Gallifrey::draw(){
    post.begin();
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
	material.begin();
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
        
        cirList[i].drawCircle();
        cirList[i].update();
        cirList[i].move();
        
    }
    
    if(snow){
        //    if(ofGetElapsedTimeMillis()%3==0 ){
        addParticle();
        // }
    }
    ofPopStyle();
    post.end();
}

void Gallifrey::drawLines(){
    post.begin();
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
	material.begin();
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
    post.end();
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
    
    if(cirList.size()<=17){
        p.pos.x=x;
        p.pos.y=y;
        
        if(rand()%3>1){
            p.addCircle(ofRandom(40,100));
        } else{
            p.addCircle(ofRandom(2,30));
        }
    }
    
    if(cirList.size()>17){
        p.pos.x=x;
        p.pos.y=y;
        
        if(rand()%4>2){
            p.addCircle(ofRandom(60,100));
        } else{
            p.addCircle(ofRandom(2,40));
        }
        p.tRad=200-p.rad;
    }
    
    cirList.push_back(p);
}

void Gallifrey::I(){
    snow=!snow;
}

void Gallifrey::O(){
    storm=!storm;
}

void Gallifrey::P(){
    for(int i=0;i<cirList.size();i++){
    cirList[i].slowToStop=!cirList[i].slowToStop;
    }
 //   vac=!vac;
}