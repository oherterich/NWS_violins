//
//  billboardParticle.h
//  DuelingParticles
//
//  Created by Jorge Proano on 10/28/13.
//
//

#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "ofVbo.h"
#include "ofxTween.h"

class ParticleSystem{
public:
    ParticleSystem();
    
    void debugDraw();
    virtual void setup(signed int S, signed int max);
    virtual void addParticle();
    virtual void update();
    virtual void draw(); // ofEnableBlendMode(OF_BLENDMODE_ADD);
    virtual void applyForces(ofVec3f force);
    
    vector<Particle> PartList;
    
    ofVec3f emiter;
    signed int renderSize;
    signed int maxSize;
    ofColor CurrentColor;
    
};


class NormParticleSystem: public ParticleSystem {
public:
    NormParticleSystem();
    virtual void addParticle();
    virtual void setup(signed int S, signed int max);
    void setResolution(float res);

    float resolution;
};

class BillboardParticleSystem: public ParticleSystem {
public:
    BillboardParticleSystem();
    virtual void setup(signed int S, signed int max);
    virtual void addParticle();
    virtual void update();
    virtual void draw();
    
       ofShader billboardShader;
        ofImage texture;
        ofVboMesh billboards;
    
   
};

class NBillboardParticleSystem: public ParticleSystem {
    
public:
    NBillboardParticleSystem();
    virtual void setup(signed int S, signed int max);
    virtual void addParticle();
    virtual void update();
    virtual void draw();
    void setResolution(float res);
    ofShader billboardShader;
    ofImage texture;
    ofVboMesh billboards;
    
    float resolution;
    

	ofxEasingQuart easeQuart;
	ofxEasingQuint easeQuint;
    ofxEasingCubic easeCubic;

	
	float clamp;
	ofxTween::ofxEasingType easingType;
    
};

class BubblesParticleSytem: public BillboardParticleSystem{
public:
    BubblesParticleSytem();
    virtual void update();
    
    ofxEasingQuart easeQuart;
	ofxEasingQuint easeQuint;
    ofxEasingCubic easeCubic;
    
	
	float clamp;
	ofxTween::ofxEasingType easingType;
    
};

class WispsParticleSytem: public BillboardParticleSystem{
public:
    WispsParticleSytem();
    virtual void addParticle();
    virtual void update();
    virtual void applyForces();
    
    ofxEasingQuart easeQuart;
	ofxEasingQuint easeQuint;
    ofxEasingCubic easeCubic;
    
	
	float clamp;
	ofxTween::ofxEasingType easingType;
    
};

class Lines: public ParticleSystem{
    
public:
    Lines();
    ofPolyline P;
     virtual void draw();
    virtual void update();
    virtual void addParticle();
    virtual void applyForces(ofVec3f force);
    

    
    
    
};

class Bokeh: public BillboardParticleSystem{
public:
    Bokeh();
    virtual void setup(signed int S, signed int max);
    virtual void addParticle();
    
    
    
};
//public:
//    BillboardParticle();
//    
//    void setupRandom();
//    void update();
//    void updateLife();
//    void addParticle(ofVec3f pos);
//    void drawBillBoards();
//    void drawLine();
//    void setSize(int PartSize, int PartTrail);
//    void setLife(int life);
//    void setRenderSize(int RenderSize);
//    void setup();
//    
//    ofShader billboardShader;
//    ofImage texture;
//    ofVboMesh billboards;
//    
//
//    
//    
//    signed int Trail;
//    signed int LineWidth;
//    int boxSize;
//    
//    ofPolyline P;
//
//};

