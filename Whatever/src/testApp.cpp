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
    bRightParticleInside = false;
    
    maxParticlesLeft = 1000;
    maxParticlesRight = 500;
    
    green.loadImage("white-small.png");
    blue.loadImage("white.png");
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    moveCenter.set(300,300);
    blueRepulsionStr = 10.0;
    
    
    //-----POST PROCESSING------
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<RimHighlightingPass>();
    post.createPass<VerticalTiltShifPass>();
    post.createPass<GodRaysPass>();
    //    post.createPass<ContrastPass>();
    
    post.createPass<FxaaPass>();
    //    post.createPass<BloomPass>();
    //    post.createPass<SSAOPass>();
    
    ofSetSphereResolution(24);
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight.setSpotlight(800.0, 2.0);
    pointLight2.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight2.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight2.setSpotlight(1000.0, 0.2);
    material.setShininess( 200 );
    material.setAmbientColor(ofColor((255)));
    // the light highlight of the material //
	material.setSpecularColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255));

    
    
    //-----AUDIO--------
    receiver.setup(PORT);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //-----AUDIO---------------
    
    GetOSC();
    
    //-------------------------
    
    
    
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
                it->attractionForce(moveCenter.x, moveCenter.y, 1.9);
            }
            
            if (bSolo) {
                it->attractionForce( moveCenter.x, moveCenter.y, 1.0);
                it->addNoise(2.0);
                it->addRepulsionForce(moveCenter.x, moveCenter.y, 10, 5.0);
            }
            
            if (bForce) {
                it->burst(it->pos.x, it->pos.y, 50.0);
            }
            
            if (Channel01_Attack > 2.6) {
                it->addRepulsionForce(moveCenter.x, moveCenter.y, 100, 15.0);
            }
            
            else {
                it->attractionForce( moveCenter.x, moveCenter.y, 0.8 );
                
                it->addForce( wind );
                it->addClockwiseForce(moveCenter.x, moveCenter.y, 300, ofMap(rightParticles.size(), 0, 3000, 0, 10.0));
                it->addNoise(ofMap(rightParticles.size(), 0, 3000, 0, 20.0));
            }
        }
        it->addDamping();
        
        if (colorLerpSwitch) {
            it->lerpToColor(it->c, ofColor(255,150,130), 0.005);
        }
        else {
            it->lerpToColor(it->c, ofColor(235,150,240), 0.01);
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
        float radius;
        
        wind.set(0, -.03);
        
        if (suctionSwitch) {
            it->attractionForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 5.0);
            it->damping = .1;
            if (it->age < 275) {
                it->age += 500;
            }
        }
        else if (!bRightParticleInside){
            it->attractionForce( moveCenter.x, moveCenter.y, 0.5);
            radius = ofMap(leftParticles.size(), 0, 1000, 0, 250);
        }
        else {
            it->lerpToColor(it->c, ofColor(240,100,120), 0.02);
            blueRepulsionStr = ofRandom( 0.2f, 1.0f );
            float noise = ofNoise( it->pos.x * 0.005, it->pos.y * 0.005 ) * 15.0;
            float agePct = ( 1 - ( (float) it->age / (float)it->life ) );
            it->pos += ofVec2f(cos(noise), sin(noise)) * (1.0 - agePct * 1.5);
            it->vel *= 0.99;
            radius = 400;
            
            it->changeSizeOverTime();
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
    
        if ((Channel01_Amplitude * 100) > 2.2 && !suctionSwitch && !bSolo) {
            int rand = (int)ofRandom(0, 4);
            
            if( bMain2 ){
                float tmp = ofRandomf();
                if(tmp >= 0){
                    ltInitYPos = ofRandom(-500, 0);
                }else{
                    ltInitYPos = ofRandom(800, 1300);
                }
            }else{
                ltInitYPos = ofGetWindowHeight() / 2 + ofRandom(-10,10);
            }
            
            if (leftParticles.size() < maxParticlesLeft) {
                switch (rand) {
                    case 0:
                        addLeftParticle( ofVec2f(ofRandom(-500, 0), ltInitYPos));
                        break;
                        
                    case 1:
                        addLeftParticle( ofVec2f(ofRandom(-500, 0), ltInitYPos));
                        break;
                        
                    case 2:
                        addLeftParticle( ofVec2f(ofRandom(1300, 1800), ltInitYPos));
                        break;
                        
                    case 3:
                        addLeftParticle( ofVec2f(ofRandom(1300, 1800), ltInitYPos));
                        break;
                    
                }
            }
        }
        
        else if (Channel01_Attack > 1.0 && !suctionSwitch && bSolo && leftParticles.size() < maxParticlesLeft) {
            addLeftParticle( ofVec2f(moveCenter.x, moveCenter.y) );
        }
    
    if (rightParticleSwitch) {
        if (rightParticles.size() < maxParticlesRight && ofGetElapsedTimeMillis() % (int)rightParticleAmount == 0 && !suctionSwitch) {
            
            int rand = (int)ofRandom(0, 4);
            
            if (!bRightParticleInside) {
                rtParticleInitC0 = ofVec2f(ofRandom(-500, 0), ofRandom(-500, 0));
                rtParticleInitC1 = ofVec2f(ofRandom(-500, 0), ofRandom(800, 1300));
                rtParticleInitC2 = ofVec2f(ofRandom(1300,1800), ofRandom(-500, 0));
                rtParticleInitC3 = ofVec2f(ofRandom(1300,1800), ofRandom(800,1300));
            }
            else {
                rtParticleInitC0 = moveCenter + ofVec2f(ofRandomf(), ofRandomf());
                rtParticleInitC1 = moveCenter + ofVec2f(ofRandomf(), ofRandomf());
                rtParticleInitC2 = moveCenter + ofVec2f(ofRandomf(), ofRandomf());
                rtParticleInitC3 = moveCenter + ofVec2f(ofRandomf(), ofRandomf());
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
    AudioDebug();
    
//    post.begin(cam);
//    ofEnableLighting();
//    pointLight.enable();
//    pointLight2.enable();
//	material.begin();

    
    //Loop through vectors and draw particles
    for ( vector<Particle>::iterator it = leftParticles.begin(); it != leftParticles.end(); it++ ) {
        it->draw();
    }
    for ( vector<Particle>::iterator it = rightParticles.begin(); it != rightParticles.end(); it++ ) {
        it->draw();
    }
    
   // post.end();

    
//    ofSetColor(255, 255, 0);
//    ofCircle(moveCenter, 10);
    
//    ofSetColor(0, 255, 0);
//    ofDrawBitmapString( ofToString( leftParticles.size() ), ofPoint(20, 20) );
//    
//    ofSetColor(0, 0, 255);
//    ofDrawBitmapString( ofToString( rightParticles.size() ), ofPoint(ofGetWindowWidth() - 40, 20) );
//
//    ofSetColor(255, 255);
//    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(ofGetWindowWidth() / 2 - 10, 20));
//    
//    ofSetColor(255, 255);
//    ofDrawBitmapString(ofToString(rightParticleAmount), ofPoint(ofGetWindowWidth() / 2 - 10, 40));
}

void testApp::addLeftParticle( ofVec2f pos ) {
    ofVec2f vel;
    float offset = ofRandom( -100.0, 100.0 );
    //float attackVel = ofMap(Channel01_Attack, .75, 2.5, 5, 20);
    vel.set(ofRandom(-20.0, 20.0), ofRandom(0.0, 0.0));
    if (colorLerpSwitch) {
        Particle tmp( pos, vel, ofColor(255,200,100), 1.0, 200.0, &green);
        leftParticles.push_back( tmp );
    }
    else {
        Particle tmp( pos, vel, ofColor(230,200,100), 1.0, 200.0, &green);
        leftParticles.push_back( tmp );
    }
}

void testApp::addRightParticle( ofVec2f pos ) {
    ofVec2f vel;
    float offset = ofRandom( -100.0, 100.0 );
    vel.set(ofRandom(-2.0, 2.0), ofRandom(-10.0, 10.0));
    if (colorLerpSwitch) {
        Particle tmp( pos, vel, ofColor(240,200,120), 1.0, 240.0, &blue);
        rightParticles.push_back( tmp );
    }
    else {
        Particle tmp( pos, vel, ofColor(150,190,250), 1.0, 240.0, &blue);
        rightParticles.push_back( tmp );
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 's' || key == 'S') {
        rightParticleSwitch = !rightParticleSwitch;
    }
    
    if (key == 'd' || key == 'D') {
        colorLerpSwitch = !colorLerpSwitch;
    }
    
    if (key == 'f' || key == 'F') {
        suctionSwitch = !suctionSwitch;
        rightParticleSwitch = false;
    }
    
    if (key == 'g' || key == 'G') {
        bMain2 = !bMain2;
        suctionSwitch = false;
    }
    
    if (key == 'h' || key == 'H') {
        bSolo = !bSolo;
        bMain2 = false;
    }
    
    if (key == 'j' || key == 'J') {
        rightParticleSwitch = true;
        bRightParticleInside = !bRightParticleInside;
    }
    
    if (key == 'k' || key == 'K') {
        bForce = true;
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

//--------------------OSC STUFF---------------------------------

void testApp::GetOSC(){
    
    while(receiver.hasWaitingMessages()){
        
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        if(m.getAddress()=="/Channel01/AudioAnalysis"){
            Channel01_Pitch = m.getArgAsFloat(1);
            Channel01_Attack = m.getArgAsFloat(2);
            Channel01_Amplitude = m.getArgAsFloat(0);
        }
        
        if(m.getAddress()=="/Channel02/AudioAnalysis"){
            Channel02_Pitch = m.getArgAsFloat(1);
            Channel02_Attack = m.getArgAsFloat(2);
            Channel02_Amplitude = m.getArgAsFloat(0);
        }
        
        if(m.getAddress()=="/Channel01/FFT"){
            
            if(m.getArgAsInt32(0)!=Channel01_FFT_size){
                Channel01_FFT_size =m.getArgAsInt32(0);
                float tmp;
                for (int i = 0; i < Channel01_FFT_size; i++) {
                    Channel01_FFT.push_back(tmp);
                }
            }
            
            for (int i = 0; i < Channel01_FFT_size; i++) {
                Channel01_FFT[i] = m.getArgAsFloat(i+1);
            }
            
        }
        
        if(m.getAddress()=="/Channel02/FFT"){
            
            if(m.getArgAsInt32(0)!=Channel02_FFT_size){
                Channel02_FFT_size =m.getArgAsInt32(0);
                float tmp;
                for (int i = 0; i < Channel02_FFT_size; i++) {
                    Channel02_FFT.push_back(tmp);
                }
            }
            
            for (int i = 0; i < Channel02_FFT_size; i++) {
                Channel02_FFT[i] = m.getArgAsFloat(i+1);
            }
            
        }
        
    }
    
    
    Channel01_LinearPitch = 69 + 12*log2f(Channel01_Pitch/440);
    Channel02_LinearPitch = 69 + 12*log2f(Channel02_Pitch/440);
    
    
}

void testApp::AudioDebug(){
    
    //debug view
    ofPushStyle();
    ofPushMatrix();
    ofTranslate((ofGetWindowWidth()/2)-250, ofGetWindowHeight()-200);
    ofPushMatrix();
    ofTranslate(100, 0);
    
    ofFill();
    ofDrawBitmapString("Channel01", -90,0);
    ofSetColor(255,40);
    ofDrawBitmapString("FFT: "+ ofToString(Channel01_FFT_size) + " freq", 0,15);
    
    ofDrawBitmapString("Frequency: " + ofToString(Channel01_Pitch,0), 0,30);
    ofDrawBitmapString("Linear Pitch: " + ofToString(Channel01_LinearPitch,0), 0,45);
    ofDrawBitmapString("Amplitude: " + ofToString(Channel01_Amplitude,4), 0,60);
    ofDrawBitmapString("Attack: " + ofToString(Channel01_Attack,4), 0,75);
    
    
    for (int i = 0; i < Channel01_FFT_size; i++){
        ofSetColor(255,20);
        ofRect((i*6),0,5,-Channel01_FFT[i] * 3);
        ofSetColor(255);
        ofLine((i*6), -Channel01_FFT[i] * 3, ((i+1)*6), -Channel01_FFT[i+1] * 3);
    }
    ofSetColor(255, 255*Channel01_Amplitude);
    ofCircle(-50,50, Channel01_Attack*3);
    ofSetColor(255);
    ofNoFill();
    ofCircle(-50, 50, Channel01_Attack*3);
    
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(350, 0);
    
    ofFill();
    ofDrawBitmapString("Channel02", -90,0);
    ofSetColor(255,40);
    ofDrawBitmapString("FFT: "+ ofToString(Channel02_FFT_size) + " freq", 0,15);
    
    ofDrawBitmapString("Frequency: " + ofToString(Channel02_Pitch,0), 0,30);
    ofDrawBitmapString("Linear Pitch: " + ofToString(Channel02_LinearPitch,0), 0,45);
    ofDrawBitmapString("Amplitude: " + ofToString(Channel02_Amplitude,4), 0,60);
    ofDrawBitmapString("Attack: " + ofToString(Channel02_Attack,4), 0,75);
    
    
    for (int i = 0; i < Channel02_FFT_size; i++){
        ofSetColor(255,20);
        ofRect((i*6),0,5,-Channel02_FFT[i] * 3);
        ofSetColor(255);
        ofLine((i*6), -Channel02_FFT[i] * 3, ((i+1)*6), -Channel02_FFT[i+1] * 3);
    }
    ofSetColor(255, 255*Channel02_Amplitude);
    ofCircle(-50,50, Channel02_Attack*3);
    ofSetColor(255);
    ofNoFill();
    ofCircle(-50, 50, Channel02_Attack*3);
    ofPopMatrix();
    ofPopMatrix();
    ofPopStyle();
    
    
}
