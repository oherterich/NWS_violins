//
//  billboardParticle.cpp
//  DuelingParticles
//
//  Created by Jorge Proano on 10/28/13.
//
//

#include "billboardParticle.h"

ParticleSystem::ParticleSystem(){
    
}

 void ParticleSystem::setup(signed int S, signed int max){
     renderSize = S;
     maxSize = max;
     CurrentColor = ofColor(255);
}

void ParticleSystem::addParticle(){
    
    Particle tmp;
    tmp.pos = emiter;
    tmp.life = ofRandomf();
    PartList.push_back(tmp);
}

void ParticleSystem::applyForces(ofVec3f force){
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        it->applyForce(force);
        
    }
}

void ParticleSystem::update(){
    
    // keep it at the rigth size
    
    if (PartList.size()>maxSize) {
        while (PartList.size()>maxSize) {
            PartList.erase(PartList.begin());
        }
    }
    
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        it->update();
        
    }
}

void ParticleSystem::draw(){
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        ofPushStyle();
        ofFill();
        ofSetColor(CurrentColor);
        ofCircle(it->pos, renderSize);
        ofPopStyle();

        
    }
}

void ParticleSystem::debugDraw(){
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        it->debugDraw();

        
    }
}

//-------------normalized particles-------------\\


NormParticleSystem::NormParticleSystem(){
    
    
   }

void NormParticleSystem::setup(signed int S, signed int max){
    renderSize = S;
    maxSize = max;
    CurrentColor = ofColor(255);
    resolution = 0.15;
    
}

void NormParticleSystem::addParticle(){

    
    if (PartList.size() > 2) {
        
        ofVec3f prevEmiter = PartList[PartList.size()-1].pos;
        float dist = emiter.distance(prevEmiter);
        float steps = (float)dist/(float)resolution;
        //cout << steps << endl;


        
        for (int i =0; i<steps; i++) {
            Particle tmp;
            ofVec3f step;
            
            step = emiter*(i/steps) + prevEmiter*(1-(i/steps));
            tmp.pos = step;
            PartList.push_back(tmp);
        }

        
    } else {
        ParticleSystem::addParticle();
    }
    
    
   
    
}


void NormParticleSystem::setResolution(float res){
    resolution = res;
}

//-------------billboarded particles-------------\\

BillboardParticleSystem::BillboardParticleSystem(){
    
    
}

void BillboardParticleSystem::setup(signed int S, signed int max){
    
    renderSize = S;
    maxSize = max;
    CurrentColor = ofColor(255);
    
    billboards.setUsage( GL_DYNAMIC_DRAW );
	billboards.setMode(OF_PRIMITIVE_POINTS);
    // load the bilboard shader
	// this is used to change the
	// size of the particle
	if(ofGetGLProgrammableRenderer()){
		billboardShader.load("shadersGL3/Billboard");
	}else{
		billboardShader.load("shadersGL2/Billboard");
	}
    // we need to disable ARB textures in order to use normalized texcoords
	ofDisableArbTex();

}

void BillboardParticleSystem::addParticle(){
    Particle tmp;
    tmp.pos = emiter;
    tmp.vel.set(0);
    billboards.getVertices().push_back(tmp.pos);
    billboards.getColors().push_back(CurrentColor);
    billboards.getNormals().push_back(ofVec3f(renderSize,0,0));
    
    PartList.push_back(tmp);

    
}


void BillboardParticleSystem::update(){
    
    

    if (PartList.size()>maxSize) {
        while (PartList.size()>maxSize) {
            PartList.erase(PartList.begin());
            billboards.getVertices().erase(billboards.getVertices().begin());
            billboards.getColors().erase(billboards.getColors().begin());
            billboards.getNormals().erase(billboards.getNormals().begin());
        }
    }
    
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        it->update();
        
    }

    
    // find a better way to do that. 
    
    for (int i = 0; i< PartList.size(); i++) {
        billboards.getColors()[i].set(CurrentColor);
        billboards.getVertices()[i].set(PartList[i].pos);
    }

    
}

void BillboardParticleSystem::draw(){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    billboardShader.begin();
	
	ofEnablePointSprites(); // not needed for GL3/4
	texture.getTextureReference().bind();
	billboards.draw();
	texture.getTextureReference().unbind();
	ofDisablePointSprites(); // not needed for GL3/4
	
	billboardShader.end();
    ofPopStyle();
    
}

//----------------normalized billboards hell yeah!-----------\\

NBillboardParticleSystem::NBillboardParticleSystem(){
    
}


void NBillboardParticleSystem::setup(int S, int max){
    
    renderSize = S;
    maxSize = max;
    CurrentColor = ofColor(255);
    resolution = 0.15;
    
    clamp = true;
	easingType = ofxTween::easeIn;
    
    
    billboards.setUsage( GL_DYNAMIC_DRAW );
	billboards.setMode(OF_PRIMITIVE_POINTS);
    // load the bilboard shader
	// this is used to change the
	// size of the particle
	if(ofGetGLProgrammableRenderer()){
		billboardShader.load("shadersGL3/Billboard");
	}else{
		billboardShader.load("shadersGL2/Billboard");
	}
    // we need to disable ARB textures in order to use normalized texcoords
	ofDisableArbTex();

}

void NBillboardParticleSystem::addParticle(){
    
    
    if (PartList.size() > 2) {
        
        ofVec3f prevEmiter = PartList[PartList.size()-1].pos;
        float dist = emiter.distance(prevEmiter);
        float steps = (float)dist/(float)resolution;
        //cout << steps << endl;
        
        
        
        for (int i =0; i<steps; i++) {
            Particle tmp;
            ofVec3f step;
            tmp.vel.set(0);
            step = emiter*(i/steps) + prevEmiter*(1-(i/steps));
            tmp.pos = step;
            
            billboards.getVertices().push_back(tmp.pos);
            billboards.getColors().push_back(CurrentColor);
            billboards.getNormals().push_back(ofVec3f(renderSize,0,0));
            
            PartList.push_back(tmp);
        }
        
        
    } else {
        Particle tmp;
        tmp.pos = emiter;
        tmp.vel.set(0);
        billboards.getVertices().push_back(tmp.pos);
        billboards.getColors().push_back(CurrentColor);
        billboards.getNormals().push_back(ofVec3f(renderSize,0,0));
        
        PartList.push_back(tmp);
    }
    

    
}


void NBillboardParticleSystem::update(){
    
    if (PartList.size()>maxSize) {
        while (PartList.size()>maxSize) {
            PartList.erase(PartList.begin());
            billboards.getVertices().erase(billboards.getVertices().begin());
            billboards.getColors().erase(billboards.getColors().begin());
            billboards.getNormals().erase(billboards.getNormals().begin());
        }
    }
    
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        it->update();
        
    }
    
    // find a better way to do that.
    
    for (int i = 0; i< PartList.size(); i++) {
        billboards.getColors()[i].set(CurrentColor);
        billboards.getVertices()[i].set(PartList[i].pos);
        float neoSize = ofxTween::map(i, 0, PartList.size()-1, 1, 0, clamp, easeCubic, easingType);
        neoSize = 1- neoSize;
        billboards.getNormals()[i].set(ofVec3f(renderSize*neoSize,0,0));
    }
 
    
}


void NBillboardParticleSystem::setResolution(float res){
    resolution = res;
}


void NBillboardParticleSystem::draw(){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    billboardShader.begin();
	
	ofEnablePointSprites(); // not needed for GL3/4
	texture.getTextureReference().bind();
	billboards.draw();
	texture.getTextureReference().unbind();
	ofDisablePointSprites(); // not needed for GL3/4
	
	billboardShader.end();
    ofPopStyle();
    
}


//------------bubles everywhere------------//

BubblesParticleSytem::BubblesParticleSytem(){
    
}

void BubblesParticleSytem::update(){
    
    clamp = true;
	easingType = ofxTween::easeInOut;
    
    if (PartList.size()>maxSize) {
        while (PartList.size()>maxSize) {
            PartList.erase(PartList.begin());
            billboards.getVertices().erase(billboards.getVertices().begin());
            billboards.getColors().erase(billboards.getColors().begin());
            billboards.getNormals().erase(billboards.getNormals().begin());
        }
    }
    
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        it->update();

        
    }
    
    
    // find a better way to do that.
    
    for (int i = 0; i< PartList.size(); i++) {
        

        billboards.getColors()[i].set(CurrentColor);
        billboards.getVertices()[i].set(PartList[i].pos);
        float neoSize = ofxTween::map(i, 0, PartList.size()-1, 1, 0, clamp, easeCubic, easingType);
        
        ofColor neoColor;
        neoColor.setHsb(CurrentColor.getHue(), CurrentColor.getSaturation(), CurrentColor.getBrightness(),255*(1-neoSize));
     
        
        billboards.getNormals()[i].set(ofVec3f(renderSize*(1-neoSize),0,0));
        billboards.getColors()[i].set(neoColor);
    }
    

}

//----------------tha wisps-------------------//


WispsParticleSytem::WispsParticleSytem(){
    
}

void WispsParticleSytem::addParticle(){
    
    Particle tmp;
    tmp.pos = emiter;
    //tmp.vel.set(emiter*0.1);
    tmp.origin = emiter;
    //tmp.damping = 0.01;
    billboards.getVertices().push_back(tmp.pos);
    billboards.getColors().push_back(CurrentColor);
    billboards.getNormals().push_back(ofVec3f(renderSize,0,0));
    
    PartList.push_back(tmp);
    
}

void WispsParticleSytem::update(){
    
    clamp = true;
	easingType = ofxTween::easeIn;
    
    if (PartList.size()>maxSize) {
        while (PartList.size()>maxSize) {
            PartList.erase(PartList.begin());
            billboards.getVertices().erase(billboards.getVertices().begin());
            billboards.getColors().erase(billboards.getColors().begin());
            billboards.getNormals().erase(billboards.getNormals().begin());
        }
    }
    
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        it->update();
        it->resetVel();
        //it->atractToOrigin();
        
        
    }
    
    
    // find a better way to do that.
    
    for (int i = 0; i< PartList.size(); i++) {
        
        
        billboards.getColors()[i].set(CurrentColor);
        billboards.getVertices()[i].set(PartList[i].pos);
        float neoSize = ofxTween::map(i, 0, PartList.size()-1, 1, 0, clamp, easeQuint, easingType);
        
        ofColor neoColor;
        neoColor.setHsb(CurrentColor.getHue(), CurrentColor.getSaturation(), CurrentColor.getBrightness(),255*(1-neoSize));
        
        
        billboards.getNormals()[i].set(ofVec3f(renderSize*(neoSize),0,0));
        billboards.getColors()[i].set(neoColor);
    }
    
    
}

void WispsParticleSytem::applyForces(){
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
       ofVec3f tempforce = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
        tempforce *= 0.7;
        it->applyForce(tempforce);
        
    }
}

//------------lines forevah---------------//


Lines::Lines(){
    
}

void Lines::addParticle(){
    Particle tmp;
    tmp.pos = emiter;
    //tmp.life = ofRandom(0.9,1);
     tmp.life = 1;
    tmp.vel.set(0);
    P.getVertices().push_back(tmp.pos);
  
  
    
    PartList.push_back(tmp);
}

void Lines::update(){
    
    
    // keep it at the rigth size
    
    if (PartList.size()>maxSize) {
        while (PartList.size()>maxSize) {
            PartList.erase(PartList.begin());
            P.getVertices().erase( P.getVertices().begin());
        }
    }
    
    for( vector<Particle>::iterator it=PartList.begin(); it!= PartList.end(); ++it){
        
        it->update();
       
        
    }

    for (int i = 0; i< PartList.size(); i++) {
        P.getVertices()[i].set(PartList[i].pos);
        
    }
}

void Lines::draw(){
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    ofSetLineWidth(renderSize);
    
    ofColor neoColor;
    neoColor.setHsb(CurrentColor.getHue(), CurrentColor.getSaturation(), CurrentColor.getBrightness(),255*(0.5));
    
    ofSetColor(neoColor);

    P.draw();
    ofPopStyle();
 
}

void Lines::applyForces(ofVec3f force){
    
    
    for (int i = 0; i< PartList.size(); i++) {
        ofVec3f tempforce;
        tempforce = force* (ofMap(i, 0, PartList.size(), 1, 0));
        tempforce = tempforce*PartList[i].life;
        PartList[i].applyForce(tempforce);

    }
    
}

//-----------------the ice in the cake-------------

Bokeh::Bokeh(){
    
}

void Bokeh::setup(int S, int max){
    renderSize = S;
    maxSize = max;
    CurrentColor = ofColor(255);
    
    billboards.setUsage( GL_DYNAMIC_DRAW );
	billboards.setMode(OF_PRIMITIVE_POINTS);
    // load the bilboard shader
	// this is used to change the
	// size of the particle
	if(ofGetGLProgrammableRenderer()){
		billboardShader.load("shadersGL3/Billboard");
	}else{
		billboardShader.load("shadersGL2/Billboard");
	}
    // we need to disable ARB textures in order to use normalized texcoords
	ofDisableArbTex();
    
    for (int i = 0; i<maxSize; i++) {
        Particle tmp;
        tmp.pos.set(ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()));
        tmp.pos *= 600;
        tmp.vel.set(ofVec3f(ofRandomf(),ofRandomf(),ofRandomf())*0.2);
        billboards.getVertices().push_back(tmp.pos);
        billboards.getColors().push_back(CurrentColor);
        billboards.getNormals().push_back(ofVec3f(renderSize,0,0));
        
        PartList.push_back(tmp);
    }
    
    
    
}

void Bokeh::addParticle(){
    Particle tmp;
    tmp.pos.set(ofVec3f(ofRandomf(),ofRandomf(),ofRandomf()));
    tmp.pos *= 600;
    tmp.vel.set(ofVec3f(ofRandomf(),ofRandomf(),ofRandomf())*0.2);
    billboards.getVertices().push_back(tmp.pos);
    billboards.getColors().push_back(CurrentColor);
    billboards.getNormals().push_back(ofVec3f(renderSize,0,0));
    
    PartList.push_back(tmp);
}


