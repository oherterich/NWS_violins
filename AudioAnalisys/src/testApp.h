#pragma once


#include "ofMain.h"
#include "fft.h"
#include "FFTOctaveAnalyzer.h"
#include "aubioAnalyzer.h"
#include "ofxOsc.h"

#define BUFFER_SIZE 512

#define HOST "localhost"
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
    
    void audioAnalisys();
    void SentMessages();
    
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
    
    ofSoundStream AudioIn;
    
    float Channel01_peakPitch;
    float Channel01_UsefulPitch;
    float Channel02_peakPitch;
    float Channel02_UsefulPitch;
    ofColor pitched;
    
    ofxOscSender Sender;
    
    int Channel01_FFT_size;
    int Channel02_FFT_size;

    float Channel01_Pitch;
    float Channel01_Attack;
    float Channel01_Amplitude;
    float Channel02_Pitch;
    float Channel02_Attack;
    float Channel02_Amplitude;
    float Channel01_LinearPitch;
    float Channel02_LinearPitch;
		
};

