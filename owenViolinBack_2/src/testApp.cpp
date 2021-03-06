#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync( true );
    ofBackground( 0 );
    ofEnableAlphaBlending();

    rightParticleSwitch = false;
    rightParticleAmount = 15.0;

    suctionSwitch = false;
    colorLerpSwitch = false;
    bMain2 = false;
    bSolo = false;
    bSizing = false;
    bRtParticleFromOut = true;

    maxParticlesLeft = 1000;
    maxParticlesRight = 500;

    green.loadImage("white-small.png");
    blue.loadImage("white.png");

    ofEnableBlendMode(OF_BLENDMODE_ADD);

    moveCenter.set(300,300);
    blueRepulsionStr = 10.f;

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

        if (suctionSwitch) {
            it->attractionForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 5.0);
            it->damping = .1;
            if (it->age < 275) {
                it->age += 500;
            }
        }
        else {

            if (bMain2) {
                it->newMotion( *it, ofGetElapsedTimef() );
            }

            if (bSolo) {
                //it->damping = 0.05;
                it->attractionForce( moveCenter.x, moveCenter.y, 1.5);
                it->addNoise(2.0);
                it->addRepulsionForce(moveCenter.x, moveCenter.y, 10, 45.0);
            }

            if (bForce) {
                it->burst(it->pos.x, it->pos.y, 50.0);
            }

            else {
                it->attractionForce( moveCenter.x, moveCenter.y, 2.0 );

                it->addForce( wind );
                it->addClockwiseForce(moveCenter.x, moveCenter.y, 300, ofMap(rightParticles.size(), 0, 3000, 0, 10.0));
                it->addNoise(ofMap(rightParticles.size(), 0, 3000, 0, 20.0));
            }
        }
        it->addDamping();

        if (colorLerpSwitch) {
            it->lerpToColor(it->c, ofColor(255,150,130), 0.005);
        }

        it->update();
        if ( it->kill() ) {
            leftParticles.erase(it);
        }
        else {
            it++;
        }
    }

    for (vector<Particle>::iterator it = rightParticles.begin(); it != rightParticles.end(); ) {
        ofVec2f wind;
        wind.set(0, -.03);
        float radius;
        //float mappedStrength = ofMap(totalLowEnd, 0.0, 500.0, 0.0, 5.0);
        if (suctionSwitch) {
            it->attractionForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0.5);
            it->damping = .1;
            if (it->age < 275) {
                it->age += 500;
            }
        }else
        if( !bSizing ){
            it->attractionForce( moveCenter.x, moveCenter.y, 0.5 );
            radius = ofMap(leftParticles.size(), 0, 1000, 0, 250);
        }else{
            it->lerpToColor(it->c, ofColor(240,100,120), 0.02);
            blueRepulsionStr = ofRandom( 0.2f, 1.0f );
            float noise = ofNoise( it->pos.x*0.005, it->pos.y*0.005 ) * 15.0;
            float agePct = (1- ( (float)it->age / (float)it->life));
            it->pos += ofVec2f( cos(noise), sin(noise) ) * ( 1.0-agePct*1.5 );
            it->vel *= 0.99;
            radius = 400;
        }

        it->addForce( wind );
        it->addRepulsionForce(moveCenter.x, moveCenter.y, radius, blueRepulsionStr);

        it->addDamping();

        if (colorLerpSwitch) {
            it->lerpToColor(it->c, ofColor(255,200,150), 0.005);
        }

        if ( !rightParticleSwitch ) {
            it->lerpToColor(it->c, ofColor(0,0,0), 0.01f);
        }

        if( bSizing ){
            it->size = it->initSize*0.8 * it->sizePct;
        }

        it->update();

        if(it->c.getBrightness() < 10 ){
            rightParticles.erase(it);
        }
        else if (it->kill()) {
            rightParticles.erase(it);
        }
        else{
            it++;
        }
    }

    //Check two halfs of the spectrum. If loud enough, add a particle
    for (int i = 0; i < FFTanalyzer.nAverages / 2; i++ ) {
        if (FFTanalyzer.averages[i] > 8 && !suctionSwitch && !bSolo) {
            int rand = (int)ofRandom(0, 4);

            if (leftParticles.size() < maxParticlesLeft) {
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

        else if (FFTanalyzer.averages[i] > 8 && !suctionSwitch && bSolo && leftParticles.size() < maxParticlesLeft) {
            addLeftParticle( ofVec2f(moveCenter.x, moveCenter.y) );
        }
    }

    if (rightParticleSwitch) {
        if (rightParticles.size() < maxParticlesRight && ofGetElapsedTimeMillis() % (int)rightParticleAmount == 0 && !suctionSwitch) {

            int rand = (int)ofRandom(0, 4);

            if( bRtParticleFromOut ){
                rtParticleInitC0 = ofVec2f( ofRandom(-500, 0), ofRandom(-500, 0) );
                rtParticleInitC1 = ofVec2f( ofRandom(-500, 0), ofRandom(800, 1300) );
                rtParticleInitC2 = ofVec2f( ofRandom(1300, 1800), ofRandom(-500, 0) );
                rtParticleInitC3 = ofVec2f( ofRandom(1300, 1800), ofRandom(800, 1300) );
            }else{
                rtParticleInitC0 = moveCenter+ofVec2f(ofRandomf(),ofRandomf());
                rtParticleInitC1 = moveCenter+ofVec2f(ofRandomf(),ofRandomf());
                rtParticleInitC2 = moveCenter+ofVec2f(ofRandomf(),ofRandomf());
                rtParticleInitC3 = moveCenter+ofVec2f(ofRandomf(),ofRandomf());
            }

            if (rightParticles.size() < maxParticlesLeft) {
                switch (rand) {
                    case 0:
                        addRightParticle( rtParticleInitC0 );
                        break;

                    case 1:
                        addRightParticle( rtParticleInitC1 );
                        break;

                    case 2:
                        addRightParticle( rtParticleInitC2 );
                        break;

                    case 3:
                        addRightParticle( rtParticleInitC3 );
                        break;
                }
            }
        }
    }


    if (rightParticleAmount > 1.1 && rightParticleSwitch) {
        rightParticleAmount -= 0.01;
    }

    float moveCenterSpeed;

    if (bSolo) {
        moveCenterSpeed = 0.7;
    }
    else {
        moveCenterSpeed = ofMap(sin(ofGetElapsedTimef() * 0.1), -1, 1, 0.08, .2);
    }
    moveCenter.x = ofNoise(ofGetElapsedTimef() * moveCenterSpeed) * ofGetWindowWidth();
    moveCenter.y = ofNoise(ofGetElapsedTimef() * moveCenterSpeed + 1000) * ofGetWindowHeight();

    bForce = false;


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

//    ofSetColor(255, 255, 0);
//    ofCircle(moveCenter, 10);

//    ofSetColor(0, 255, 0);
//    ofDrawBitmapString( ofToString( leftParticles.size() ), ofPoint(20, 20) );
//
    ofSetColor(0, 0, 255);
    ofDrawBitmapString( ofToString( rightParticles.size() ), ofPoint(ofGetWindowWidth() - 40, 20) );
//
//    ofSetColor(255, 255);
    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), ofPoint(ofGetWindowWidth() / 2 - 10, 20));
//
//    ofSetColor(255, 255);
//    ofDrawBitmapString(ofToString(rightParticleAmount), ofPoint(ofGetWindowWidth() / 2 - 10, 40));
}

void testApp::addLeftParticle( ofVec2f pos ) {
    ofVec2f vel;
    float offset = ofRandom( -100.0, 100.0 );
    vel.set(ofRandom(-20.0, 20.0), ofRandom(-20.0, 20));
    if (colorLerpSwitch) {
        Particle tmp( pos, vel, ofColor(255,200,100), 2.0, 200.0, &green);
        leftParticles.push_back( tmp );
    }
    else {
        Particle tmp( pos, vel, ofColor(150,255,50), 2.0, 200.0, &green);
        leftParticles.push_back( tmp );
    }
}

void testApp::addRightParticle( ofVec2f pos ) {
    ofVec2f vel;
    float offset = ofRandom( -100.0, 100.0 );
    vel.set(ofRandom(-2.0, 2.0), ofRandom(-10, 10.0));
    if (colorLerpSwitch) {
        Particle tmp( pos, vel, ofColor(240,200,120), 3.0, 240.0, &blue);
        rightParticles.push_back( tmp );
    }
    else {
        Particle tmp( pos, vel, ofColor(150,190,250), 3.0, 240.0, &blue);
        rightParticles.push_back( tmp );
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'a' || key == 'A') {
        rightParticleSwitch = !rightParticleSwitch;
    }

    if (key == 's' || key == 'S') {
        colorLerpSwitch = !colorLerpSwitch;
    }

    if (key == 'd' || key == 'D') {
        suctionSwitch = !suctionSwitch;
        rightParticleSwitch = false;
    }

    if (key == 'f' || key == 'F') {
        bMain2 = !bMain2;
        suctionSwitch = false;
    }

    if (key == 'g' || key == 'G') {
        bSolo = !bSolo;
        bMain2 = false;
    }

    if (key == 'l' || key == 'L') {
        bForce = true;
    }

    if (key == 'z' || key == 'Z'){
        bRtParticleFromOut = ! bRtParticleFromOut;
        bSizing = !bSizing;
    }
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
