#pragma once

#include "ofMain.h"
#include "Particle.h"

#include "fft.h"
#include "FFTOctaveAnalyzer.h"

#define BUFFER_SIZE 512

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

    void addLeftParticle( ofVec2f pos );
    void addRightParticle( ofVec2f pos );

    vector<Particle> leftParticles;
    vector<Particle> rightParticles;

    bool rightParticleSwitch;
    float rightParticleAmount;

    bool colorLerpSwitch;
    bool forceSwitch;
    bool bNewMotion;
    bool bNoBlue;
    bool rtParticleFromOut, ltParticleFromOut;
    bool sizing;

    float maxParticlesLeft;
    float maxParticlesRight;

    ofImage green;
    ofImage blue;
    float pAlpha;

    ofVec2f moveCenter;
    float strength;
    int angle;

    //Audio stuff
    void audioReceived 	(float * input, int bufferSize, int nChannels);

    FFTOctaveAnalyzer FFTanalyzer;

    float left[BUFFER_SIZE];
    float right[BUFFER_SIZE];

    fft		myfft;

    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    float freq[BUFFER_SIZE/2];

    //float leftAddX1, leftAddY1, leftAddX2, leftAddY2, leftAddX3, leftAddY3, leftAddX4, leftAddY4;

    ofVec2f rtParticleInitC0, rtParticleInitC1, rtParticleInitC2, rtParticleInitC3;
    ofVec2f ltParticleInitC0, ltParticleInitC1, ltParticleInitC2, ltParticleInitC3;
};
