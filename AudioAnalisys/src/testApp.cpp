#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	// 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// BUFFER_SIZE samples per buffer
	// 4 num buffers (latency)
    
    ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);
	
	// 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	



    
    
    
	ofSoundStreamListDevices();

	
	AudioIn.setDeviceID(2);
    AudioIn.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);
    AudioIn.start();
    

	peakTime =15; // hold longer
    decayRate = 0.95f; // decay slower
    HiGain = 0.9f; // reduced gain at lowest frequency
    LowGain = 0.01f; // increasing gain at higher frequencies
    
    avg_power  = 0.0f;
    
	Channel01_Analyzer.setup(44100, BUFFER_SIZE/2, 2);
    Channel02_Analyzer.setup(44100, BUFFER_SIZE/2, 2);
	
	Channel01_Analyzer.peakHoldTime = peakTime;
	Channel01_Analyzer.peakDecayRate = decayRate;
	Channel01_Analyzer.linearEQIntercept = HiGain;
	Channel01_Analyzer.linearEQSlope = LowGain;
    
    Channel02_Analyzer.peakHoldTime = peakTime;
	Channel02_Analyzer.peakDecayRate = decayRate;
	Channel02_Analyzer.linearEQIntercept = HiGain;
	Channel02_Analyzer.linearEQSlope = LowGain;
	
    Channel01_Aubio.setup();
    Channel02_Aubio.setup();
    
	ofSetVerticalSync(true);
    
    for (int i = 0; i < Channel01_Analyzer.nAverages; i++){
        float tmp;
        Channel01_holdFreq.push_back(tmp);
        Channel01_deltaFreq.push_back(tmp);
	}
    
    for (int i = 0; i < Channel02_Analyzer.nAverages; i++){
        float tmp;
        Channel02_holdFreq.push_back(tmp);
        Channel02_deltaFreq.push_back(tmp);
	}
    
   }

//--------------------------------------------------------------
void testApp::update(){
    
	/* do the FFT on Channel 1	*/
	Channel01_fft.powerSpectrum(2,(int)BUFFER_SIZE/2, Channel01,BUFFER_SIZE,&Channel01_magnitude[0],&Channel01_phase[0],&Channel01_power[0],&avg_power);
    
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		Channel01_freq[i] = Channel01_magnitude[i];
	}
	
	Channel01_Analyzer.calculate(Channel01_freq);
    
    /* do the FFT on Channel 2	*/
    Channel02_fft.powerSpectrum(0,(int)BUFFER_SIZE/2, Channel02,BUFFER_SIZE,&Channel02_magnitude[0],&Channel02_phase[0],&Channel02_power[0],&avg_power);
    
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		Channel02_freq[i] = Channel02_magnitude[i];
	}
	
	Channel02_Analyzer.calculate(Channel02_freq);
    
  // init attack detection
    float tmp = 0;
    
    for (int i = 0; i < Channel02_Analyzer.nAverages; i++){
        
        if(Channel02_Analyzer.averages[i] > Channel02_holdFreq[i] ){
            Channel02_deltaFreq[i] = Channel02_Analyzer.averages[i] - Channel02_holdFreq[i];
        }
        
        Channel02_holdFreq[i] = Channel02_Analyzer.averages[i];
        
        tmp = tmp+Channel02_deltaFreq[i];
        
    }
    
    tmp = tmp/Channel02_Analyzer.nAverages;
    Channel02_att = tmp*0.5 + Channel02_att*0.5;
    
    if (peakPitch<Channel01_Aubio.pitch && Channel01_Aubio.confidence > 0.5) {
        peakPitch = Channel01_Aubio.pitch;
    }
    
    UsefulPitch = Channel01_Aubio.pitch*Channel01_Aubio.confidence + UsefulPitch*(1-Channel01_Aubio.confidence);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    
	
	
    
    //ofRect(60, 200, Channel02_att*20,10);
   // ofRect(60, 230, Channel01_Aubio.amplitude*500,10);
    
    pitched.setHsb(ofMap(UsefulPitch, 20, 3000, 200, 0), 255, 255*(0.6+Channel01_Aubio.amplitude));
    ofSetColor(pitched);
    ofCircle(512, 350, Channel02_att*40);
    
    ofSetHexColor(0xffffff);
    //ofCircle(800, 200, Channel01_Aubio.amplitude*500);
    
//	for (int i = 0; i < (int)(BUFFER_SIZE/2 - 1); i++){
//		ofRect(200+(i*1),600,1,-Channel01_freq[i]*10.0f);
//	}
	
//    for (int i = 0; i < BUFFER_SIZE; i++){
//		ofLine(i/2,100,i/2,100+Channel01[i]*200);
//	}
//    
//	for (int i = 0; i < Channel01_Analyzer.nAverages; i++){
//		ofRect(200+(i*20),600,20,-Channel01_Analyzer.averages[i] * 6);
//	}
//
//    for (int i = 0; i < Channel02_Analyzer.nAverages; i++){
//		ofRect(200+(i*20),200,20,-Channel02_Analyzer.averages[i] * 6);
//	}
    
    
    ofDrawBitmapString(ofToString(Channel01_Aubio.pitch), 100,100);
    ofDrawBitmapString(ofToString(Channel01_Aubio.amplitude), 100,120);
    ofDrawBitmapString(ofToString(Channel01_Aubio.confidence), 100,140);
    ofDrawBitmapString(ofToString(peakPitch), 100,160);
    
    
	ofSetHexColor(0xff0000);
//	for (int i = 0; i < Channel02_Analyzer.nAverages; i++){
//		ofRect(200+(i*20),600-Channel02_Analyzer.peaks[i] * 6,20,-4);
//	}
//    
}
//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		Channel01[i] = input[i*2];
		Channel02[i] = input[i*2+1];
	}
    
    Channel01_Aubio.processAudio(Channel01, BUFFER_SIZE);
    Channel02_Aubio.processAudio(Channel02, BUFFER_SIZE);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
