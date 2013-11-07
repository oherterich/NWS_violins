#pragma once

#include "ofMain.h"
#include "billboardParticle.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"

#define PORT 12345

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofEasyCam debugCam;
    ofEasyCam animCam;
    ofImage bg;
    ofVec3f neoPos, lastPos, heading;
    ofVec3f camPos, camLook;
    ofVec3f headA, headB;
    ofVec3f headAWisps, headBWisps;
    ofVec3f neoPosA, lastPosA, headingA;
    ofVec3f neoPosB, lastPosB, headingB;
    
    float lastHead;
    
    float headSpace;
    float headSpeed;
    
    bool debug;
    
    double t, tA, tB;
    float deltaA, deltaB, delta;
    
    
    BubblesParticleSytem BubblesA;
    BubblesParticleSytem BubblesB;
    
    
    NBillboardParticleSystem bodyA;
    NBillboardParticleSystem bodyB;
    
    NBillboardParticleSystem HeadA;
    NBillboardParticleSystem HeadB;
    
    NBillboardParticleSystem CoreA;
    NBillboardParticleSystem CoreB;
    
    WispsParticleSytem WispsA;
    WispsParticleSytem WispsB;
    
    
    Lines lineA;
    Lines lineB;
    
    Bokeh bokeh;
    
    ofxSyphonServer duelingParticles;

    //---------------------------osc
    
    void GetOSC();
    void AudioDebug();
    
    
	ofxOscReceiver receiver;
    int Channel01_FFT_size;
    int Channel02_FFT_size;
    vector<float> Channel01_FFT;
    vector<float> Channel02_FFT;
    float Channel01_Pitch;
    float Channel01_Attack;
    float Channel01_Amplitude;
    float Channel02_Pitch;
    float Channel02_Attack;
    float Channel02_Amplitude;
    float Channel01_LinearPitch;
    float Channel02_LinearPitch;
    vector<float> averagedAtk_A, averagedAtk_B;
    float averagedA, averagedB, averagedAMP;
    float lastA, lastB, lastAMP;
    
//    NormParticleSystem debugSytemA;
//    NormParticleSystem debugSytemB;
    
 };
