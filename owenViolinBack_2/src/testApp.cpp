#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync( true );
    ofBackground( 0 );

    rightParticleSwitch = false;
    rightParticleAmount = 15.0;

    forceSwitch = false;
    colorLerpSwitch = false;
    rightParticleSwitch = false;
    bNewMotion = false;
    rtParticleFromOut = true;
    ltParticleFromOut = true;
    sizing = false;

    maxParticlesLeft = 1000;
    maxParticlesRight = 500;

    green.loadImage("white-small.png");
    blue.loadImage("white.png");

    ofEnableBlendMode(OF_BLENDMODE_ADD);

    moveCenter.set(300,300);
    strength = 10.0f;
    angle = 1;

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

    angle += 1;

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
        it->attractionForce( moveCenter.x, moveCenter.y, 2.0 );

        it->addForce( wind );
        it->addClockwiseForce(moveCenter.x, moveCenter.y, 300, ofMap(rightParticles.size(), 0, 3000, 0, 10.0));
        it->addNoise(ofMap(rightParticles.size(), 0, 3000, 0, 20.0));
        //it->addRepulsionForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, ofMap(rightParticles.size(), 0, 3000, 0, 50), 1.0);
        it->addDamping();

        if (colorLerpSwitch) {
            it->lerpToColor(it->c, ofColor(255,150,130), 0.01);
        }

        if (forceSwitch) {
            it->burst(it->pos.x, it->pos.y, 60.0); //owen: 50
        }

        if (bNewMotion) {
            it->newMotion( *it, angle );
            strength = 10.0f;
        }

        it->update();

        if ( it->kill() ) {
            leftParticles.erase(it);
        }
        else {
            it++;
        }
    }

    for (vector<Particle>::iterator it = rightParticles.begin(); it != rightParticles.end();) {
        ofVec2f wind;
        wind.set(0, -.03);
        float radius;
        if( !sizing ){
            it->attractionForce( moveCenter.x, moveCenter.y, 0.5 );
            strength = 10.0;
            radius = ofMap(leftParticles.size(), 0, 1000, 0, 250);
        }else{
            it->lerpToColor(it->c, ofColor(240,100,120), 0.02);
            strength = ofRandom(0.2,1.0);
            float noise = ofNoise( it->pos.x*0.005, it->pos.y*0.005 ) * 15.0;
            float agePct = (1- ( (float)it->age / (float)it->life));
            it->pos += ofVec2f( cos(noise), sin(noise) ) * ( 1.0-agePct*1.5 );
            it->vel *= 0.99;
            radius = 400;
        }

        it->addForce( wind );
        it->addRepulsionForce(moveCenter.x, moveCenter.y, radius, strength);
        it->addDamping();

        if (colorLerpSwitch) {
            it->lerpToColor(it->c, ofColor(255,200,150), 0.01);
        }

        it->update();

        if ( !rightParticleSwitch ) {
            it->lerpToColor(it->c, ofColor(0,0,0), 0.1f);
        }
        if( sizing ){
            it->size = it->initSize*0.8 * it->sizePct;
        }
        if(it->c.getBrightness() < 50 ){
            rightParticles.erase(it);
        }else{
            it++;
        }
    }


    //Check two halfs of the spectrum. If loud enough, add a particle
    for (int i = 0; i < FFTanalyzer.nAverages / 2; i++ ) {
        if (FFTanalyzer.averages[i] > 8) {
            int rand = (int)ofRandom(0, 4);

            if( ltParticleFromOut ){
                ltParticleInitC0 = ofVec2f( ofRandom(-500, 0), ofRandom(-500, 0) );
                ltParticleInitC1 = ofVec2f( ofRandom(-500, 0), ofRandom(800, 1300) );
                ltParticleInitC2 = ofVec2f( ofRandom(1300, 1800), ofRandom(-500, 0) );
                ltParticleInitC3 = ofVec2f( ofRandom(1300, 1800), ofRandom(800, 1300) );
            }else{
                ltParticleInitC0 = moveCenter * ofRandom(-10,100) ;
                ltParticleInitC1 = moveCenter * ofRandom(-10,100) ;
                ltParticleInitC2 = moveCenter * ofRandom(-10,100) ;
                ltParticleInitC3 = moveCenter * ofRandom(-10,100) ;
            }

            if (leftParticles.size() < maxParticlesLeft) {
            switch (rand) {
                case 0:
                    addLeftParticle( ltParticleInitC0 );
                    break;

                case 1:
                    addLeftParticle( ltParticleInitC1 );
                    break;

                case 2:
                    addLeftParticle( ltParticleInitC2 );
                    break;

                case 3:
                    addLeftParticle( ltParticleInitC3 );
                    break;

            }
            }
        }
    }

    if (rightParticleSwitch) {
        if (rightParticles.size() < maxParticlesRight && ofGetElapsedTimeMillis() % (int)rightParticleAmount == 0) {

            int rand = (int)ofRandom(0, 4);

            if( rtParticleFromOut ){
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

    float moveCenterSpeed = ofMap(sin(ofGetElapsedTimef() * 0.1), -1, 1, 0.05, .2);
    moveCenter.x = ofNoise(ofGetElapsedTimef() * moveCenterSpeed) * ofGetWindowWidth();
    moveCenter.y = ofNoise(ofGetElapsedTimef() * moveCenterSpeed) * ofGetWindowHeight();

    forceSwitch = false;
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

    ofSetColor(255, 255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(ofGetWindowWidth() / 2 - 10, 20));

    ofSetColor(255, 255);
    ofDrawBitmapString(ofToString(rightParticleAmount), ofPoint(ofGetWindowWidth() / 2 - 10, 40));
}

void testApp::addLeftParticle( ofVec2f pos ) {
    ofVec2f vel;
    float offset = ofRandom( -100.0, 100.0 );
    vel.set(ofRandom(-2.0, 2.0), ofRandom(-50.0, 0));
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
    vel.set(ofRandom(-2.0, 2.0), ofRandom(-10.0, 10.0));
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
        colorLerpSwitch = true;
    }

    if (key == 'd' || key == 'D') {
        forceSwitch = true;
    }

    if (key == 'f' || key == 'F') {
        bNewMotion = !bNewMotion;
    }

    if (key == 'z' || key == 'Z'){
        rtParticleFromOut = ! rtParticleFromOut;
        sizing = !sizing;
    }
    if (key == 'x' || key == 'X'){
        ltParticleFromOut = ! ltParticleFromOut;
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
