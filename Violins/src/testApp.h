#pragma once

#include "ofMain.h"
#include "Composition.h"
#include "Line.h"
#include "ofxUI.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    Composition composition;
    Line l;
    vector<Line> ls;
    
    void onGuiEvent(ofxUIEventArgs &e);
    ofxUICanvas *gui;
    
    //---- things to add----
    
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

    
};
