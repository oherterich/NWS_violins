#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	receiver.setup(PORT);
    
    
    
	ofBackground(30, 30, 130);
    ofEnableAlphaBlending();
    record = false;

}

//--------------------------------------------------------------
void testApp::update(){

    GetOSC();
    if(record==true){
    pitchOverTime.push_back(Channel01_Pitch);
    AttackOverTime.push_back(Channel01_Attack);
    LinearPitchTime.push_back(Channel01_LinearPitch);
    AmplitudeTime.push_back(Channel01_Amplitude);
    }
}



//--------------------------------------------------------------
void testApp::draw(){
    AudioDebug();
    P.clear();
    LP.clear();
    A.clear();
    V.clear();
  
    
    ofPushMatrix();
    ofTranslate(0, 100);
    for (float i = 0; i < pitchOverTime.size(); i++) {
        ofVec2f tmp = ofVec2f(10+(float)i*((float)ofGetWindowWidth()/(float)pitchOverTime.size()), -pitchOverTime[i]/60);
        P.addVertex(tmp);
        P.draw();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0, 250);
    for (float i = 0; i < pitchOverTime.size(); i++) {
        ofVec2f tmp = ofVec2f(10+(float)i*((float)ofGetWindowWidth()/(float)pitchOverTime.size()), -LinearPitchTime[i]);
        LP.addVertex(tmp);
        LP.draw();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0, 350);
    for (float i = 0; i < pitchOverTime.size(); i++) {
        ofVec2f tmp = ofVec2f(10+(float)i*((float)ofGetWindowWidth()/(float)pitchOverTime.size()), -AttackOverTime[i]*30);
        A.addVertex(tmp);
        A.draw();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0, 450);
    for (float i = 0; i < pitchOverTime.size(); i++) {
        ofVec2f tmp = ofVec2f(10+(float)i*((float)ofGetWindowWidth()/(float)pitchOverTime.size()), -AmplitudeTime[i]*300);
        V.addVertex(tmp);
        V.draw();
    }
    ofPopMatrix();
 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'r') {
        record = true;
        pitchOverTime.clear();
        AttackOverTime.clear();
        LinearPitchTime.clear();
        AmplitudeTime.clear();
    }
    
    if (key == 't'){
       record = false;
    }
    
    if (key == 'y'){
        pitchOverTime.clear();
        AttackOverTime.clear();
        LinearPitchTime.clear();
        AmplitudeTime.clear();
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