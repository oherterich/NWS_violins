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
    
    void addLeftParticle();
    void addRightParticle();
    
    vector<Particle> leftParticles;
    vector<Particle> rightParticles;
    
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

		
};
