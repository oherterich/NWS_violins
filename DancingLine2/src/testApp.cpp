#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	receiver.setup(PORT);
//	ofBackground(0,0,20);
    ofEnableAlphaBlending();
    composition.setup();
    ofSetFrameRate(60);
    mastercam.setPosition(-ofGetWidth()/2,0,-8000);
}

//--------------------------------------------------------------
void testApp::update(){

    GetOSC();
    composition.update();
}



//--------------------------------------------------------------
void testApp::draw(){
//    AudioDebug();
//    mastercam.begin();
    composition.draw();
//    mastercam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    // Track 1
    
    if(key == '1'){
        composition.camstart = composition.cam.getGlobalPosition();
        composition.track = 1;
        composition.status = 1;
        composition.g.flickering = false;
        composition.vines.clear();
        for(int i=0;i<30;i++){
            Vine v;
            composition.vines.push_back(v);
        }
    }
    if(key == '2'){
        composition.track = 1;
        composition.status = 2;
        composition.g.flickering = false;
    }
    if(key == '3'){
        composition.track = 1;
        composition.status = 3;
        composition.g.flickering = true;
    }
    if(key == '4'){
        composition.track = 1;
        composition.status = 4;
        composition.g.flickering = false;
    }
    
    // Track 2
    
    if(key == 'q'){
        composition.g.clearCircles();
        composition.track = 2;
        composition.status = 1;
        composition.line1.PosList.clear();
        composition.line2.PosList.clear();
        composition.line1.separate = false;
        composition.line2.separate = false;
        composition.line1.rage = true;
        composition.line2.rage = true;
        composition.started = ofGetElapsedTimef();
        composition.vines.clear();
        for(int i=0;i<30;i++){
            Vine v;
            composition.vines.push_back(v);
        }
    }
    if(key == 'w'){
        composition.track = 2;
        composition.status = 2;
        composition.line1.separate = false;
        composition.line2.separate = false;
        composition.line1.rage = true;
        composition.line2.rage = true;
    }
    if(key == 'e'){
        composition.track = 2;
        composition.status = 3;
        composition.started = ofGetElapsedTimef();
        composition.line1.separate = true;
        composition.line2.separate = true;
        composition.line1.rage = true;
        composition.line2.rage = true;
        composition.line1.floatList = composition.line1.PosList;
        composition.line2.floatList = composition.line2.PosList;
    }
    if(key == 'r'){
        composition.g.clearCircles();
        composition.track = 2;
        composition.status = 4;
        composition.started = ofGetElapsedTimef();
        composition.line1.explodeList.clear();
        composition.line2.explodeList.clear();
        composition.line1.separate = true;
        composition.line2.separate = true;
        composition.line1.rage = false;
        composition.line2.rage = false;
        composition.line1.explodeList = composition.line1.PosList;
        composition.line2.explodeList = composition.line2.PosList;
    }
    if(key == 'a'){
        composition.track = 2;
        composition.status = 5;
    }
    
    if(key == 's'){
        composition.track = 2;
        composition.status = 6;
    }
    
    if(key == 'd'){
        composition.g.clearCircles();
        composition.track = 2;
        composition.status = 9;
        composition.line1.explodeList.clear();
        composition.line2.explodeList.clear();
        composition.line1.separate = true;
        composition.line2.separate = true;
        composition.line1.rage = false;
        composition.line2.rage = false;
        composition.line1.explodeList = composition.line1.PosList;
        composition.line2.explodeList = composition.line2.PosList;
    }
    
    if(key == 'z'){
        composition.g.clearCircles();
        composition.track = 2;
        composition.status = 7;
        composition.g.clearCircles();

    }
    if(key == 'x'){
        composition.track = 2;
        composition.status = 8;
    }
    
    if(key == '/'){
        composition.dartson = !composition.dartson;
    }
    
    
    
    if(key == 'f'){
    }
    
    if(key == 'g'){
    }
    
    if(key == 'h'){
    }
    
    
    
    if(key == 'c'){
    }
    
    if(key == 'v'){
    }
    

    
    if(key == 'u'){
        composition.g.U();
    }
    
    if(key == 'i'){
        composition.g.I();
    }
    
    if(key=='o'){
        composition.g.O();
    }
    
    if(key=='p'){
        composition.g.P();
    }
    
    
    
    if(key=='j'){
    }
    if(key=='k'){
        composition.g.K();
    }
    if(key=='l'){
        composition.g.L();
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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
        
        composition.amp01 = Channel01_Amplitude;
        composition.amp02 = Channel02_Amplitude;
        composition.pitch01 = Channel01_Pitch;
        composition.pitch02 = Channel02_Pitch;
        composition.attack01 = Channel01_Attack;
        composition.attack02 = Channel02_Attack;
        
        
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