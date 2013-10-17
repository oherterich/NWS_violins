#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync( true );
    ofBackground( 0 );
    
    // 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// BUFFER_SIZE samples per buffer
	// 4 num buffers (latency)
	
	ofSoundStreamSetup(0,2,this, 44100, BUFFER_SIZE, 4);
	
	//left = new float[BUFFER_SIZE];
	//right = new float[BUFFER_SIZE];
    
	ofSetHexColor(0x666666);
	
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/8, 8);
	
	FFTanalyzer.peakHoldTime = 15; // hold longer
	FFTanalyzer.peakDecayRate = 0.95f; // decay slower
	FFTanalyzer.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = 0.01f; // increasing gain at higher frequencies
}

//--------------------------------------------------------------
void testApp::update(){
    
    //Audio stuff
    float avg_power = 0.0f;
    
	/* do the FFT	*/
	myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
    
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		freq[i] = magnitude[i];
	}
	
	FFTanalyzer.calculate(freq);
    
    float totalLowEnd;
    for (int i = 0; i < FFTanalyzer.nAverages / 2; i++) {
        totalLowEnd += FFTanalyzer.averages[i];
    }
    
    float totalHighEnd;
    for (int i = FFTanalyzer.nAverages / 2; i < FFTanalyzer.nAverages; i++) {
        totalHighEnd += FFTanalyzer.averages[i];
    }
    
    
    for (vector<Particle>::iterator it = leftParticles.begin(); it != leftParticles.end(); ) {
        ofVec2f wind;
        wind.set(0, -.03);
        
        //float mappedStrength = ofMap(totalHighEnd, 0.0, 700.0, 0.0, 5.0);
        it->attractionForce( 2.0 );
        
        it->addForce( wind );
        it->addDamping();
        it->update();
        if ( it->kill() ) {
            leftParticles.erase( it );
        }
        else {
            it++;
        }
    }
    
    for (vector<Particle>::iterator it = rightParticles.begin(); it != rightParticles.end(); ) {
        ofVec2f wind;
        wind.set(0, -.03);
        
        //float mappedStrength = ofMap(totalLowEnd, 0.0, 500.0, 0.0, 5.0);
        it->attractionForce( 5.0 );
        
        it->addForce( wind );
        it->addDamping();
        it->update();
        
        if ( it->kill() ) {
            rightParticles.erase( it );
        }
        else {
            it++;
        }
    }
    
    //Check two halfs of the spectrum. If loud enough, add a particle
    for (int i = 0; i < FFTanalyzer.nAverages / 2; i++ ) {
        if (FFTanalyzer.averages[i] > 8) {
            int rand = (int)ofRandom(0, 4);
            
            switch (rand) {
                case 0:
                    addLeftParticle( ofVec2f(ofRandom(-500, 0), ofRandom(-500, 0)));
                    break;
                    
                case 1:
                    addLeftParticle( ofVec2f(ofRandom(-500, 0), ofRandom(800, 1300)));
                    break;
                    
                case 2:
                    addLeftParticle( ofVec2f(ofRandom(1300, 1800), ofRandom(-500, 0)));
                    break;
                    
                case 3:
                    addLeftParticle( ofVec2f(ofRandom(1300, 1800), ofRandom(800, 1300)));
                    break;
                    
            }




        }
    }
    
//    for (int i = FFTanalyzer.nAverages / 2; i < FFTanalyzer.nAverages; i++ ) {
//        if (FFTanalyzer.averages[i] > 20) {
//            addRightParticle();
//        }
//    }
    
    
//    addLeftParticle();
//    addRightParticle();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    //Loop through vectors and draw particles
    for ( vector<Particle>::iterator it = leftParticles.begin(); it != leftParticles.end(); it++ ) {
        it->draw();
    }
    for ( vector<Particle>::iterator it = rightParticles.begin(); it != rightParticles.end(); it++ ) {
        it->draw();
    }
    
    ofSetColor(0, 255, 0);
    ofDrawBitmapString( ofToString( leftParticles.size() ), ofPoint(20, 20) );
    
    ofSetColor(0, 0, 255);
    ofDrawBitmapString( ofToString( rightParticles.size() ), ofPoint(ofGetWindowWidth() - 40, 20) );

}

void testApp::addLeftParticle( ofVec2f pos ) {
    ofVec2f vel;
    float offset = ofRandom( -100.0, 100.0 );
    vel.set(ofRandom(-2.0, 2.0), ofRandom(-50.0, 0));
    Particle tmp( pos, vel, ofColor(180,255,0) );
    leftParticles.push_back( tmp );
}

void testApp::addRightParticle() {
    ofVec2f pos, vel;
    float offset = ofRandom( -100.0, 100.0 );
    pos.set(ofGetWindowWidth(), 0 + offset);
    vel.set(ofRandom(-2.0, 2.0), ofRandom(0.0, 50.0));
    Particle tmp( pos, vel, ofColor(0,180,255) );
    rightParticles.push_back( tmp );
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

//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
}
