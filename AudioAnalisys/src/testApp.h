#pragma once


#include "ofMain.h"
#include "fft.h"
#include "FFTOctaveAnalyzer.h"
#include "aubioAnalyzer.h"
#include "ofxOsc.h"

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
    
    void audioReceived 	(float * input, int bufferSize, int nChannels);
    
    FFTOctaveAnalyzer Channel01_Analyzer;
    FFTOctaveAnalyzer Channel02_Analyzer;
    
    float Channel01[BUFFER_SIZE];
    float Channel02[BUFFER_SIZE];
    
    fft		Channel01_fft;
    fft     Channel02_fft;
    
    aubioAnalyzer Channel01_Aubio;
    aubioAnalyzer Channel02_Aubio;
    
    float avg_power;
    float peakTime, decayRate, HiGain, LowGain;
    
    float Channel01_magnitude[BUFFER_SIZE];
    float Channel01_phase[BUFFER_SIZE];
    float Channel01_power[BUFFER_SIZE];
    float Channel01_freq[BUFFER_SIZE/2];
    
    float Channel02_magnitude[BUFFER_SIZE];
    float Channel02_phase[BUFFER_SIZE];
    float Channel02_power[BUFFER_SIZE];
    float Channel02_freq[BUFFER_SIZE/2];
    
    vector <float> Channel01_holdFreq;
    vector <float> Channel01_deltaFreq;
    vector <float> Channel02_holdFreq;
    vector <float> Channel02_deltaFreq;
    
    float Channel01_att;
    float Channel02_att;
		
};

