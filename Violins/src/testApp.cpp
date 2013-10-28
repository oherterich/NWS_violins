#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    receiver.setup(PORT);
    
    ofBackground(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    l.frequency = ofRandom(1.0, 100.0);
    l.width = ofRandom(100.0, 200.0);

    gui = new ofxUICanvas(200,500);
    gui->addLabel("Line Dancing");
    gui->addSpacer();
    gui->addSlider("Position", 0, 1000, 1);
    gui->addSlider("Velocity", 0, 1000, 1);
    gui->addSlider("Acceleration", 0, 1000, 1);
    gui->addSlider("Width", 0, 1000, 1);
    gui->addSlider("Frequency", 0, 1000, 1);
    
    ofAddListener(gui->newGUIEvent, this, &testApp::onGuiEvent); // what we're listening for,
    // who's listening for it,
    // and the function to run when it happens
    gui->loadSettings("test_settings.xml");
}

//--------------------------------------------------------------
void testApp::exit(){
//    gui->saveSettings("test_settings.xml");
    delete gui;
}

void testApp::onGuiEvent(ofxUIEventArgs &e){
    if(e.getName() == "Position"){
        ofxUISlider *radiusSlider = (ofxUISlider*)e.widget;
        l.pos.x = radiusSlider->getScaledValue();
        cout<<l.vel.x<<endl;
    } if(e.getName() == "Velocity"){
        ofxUISlider *radiusSlider = (ofxUISlider*)e.widget;
        l.vel.x = radiusSlider->getScaledValue();
        cout<<l.vel.x<<endl;
    } if(e.getName() == "Acceleration"){
        ofxUISlider *numberSlider = (ofxUISlider*)e.widget;
        l.acc.x = numberSlider->getScaledValue();
    } if(e.getName() == "Width"){
        ofxUISlider *sizeSlider = (ofxUISlider*)e.widget;
         l.width = sizeSlider->getScaledValue();
    }if(e.getName() == "Frequency"){
        ofxUISlider *hueSlider = (ofxUISlider*)e.widget;
        l.frequency = hueSlider->getScaledValue();
    }
}

//--------------------------------------------------------------
void testApp::update(){
    GetOSC();
        l.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofFill();
     AudioDebug();
        l.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    // Track 1

    if(key == '1'){
        composition.track1Order();
    }
    if(key == '2'){
        composition.track1Chaos();
    }
    if(key == '3'){
        composition.track1Join();
    }
    
    // Track 2
    
    if(key == 'q'){
        composition.track2Line();
    }
    if(key == 'w'){
        composition.track2SmallLines();
    }
    if(key == 'e'){
        composition.track2Order();
    }
    if(key == 'r'){
        composition.track2KillLine();
    }
    if(key == 't'){
        composition.track2LineCorpseOrder();
    }
    
    // Track 3
    
    if(key == 'a'){
        composition.track3Main();
    }
    if(key == 's'){
        composition.track3Secondary();
    }
    if(key == 'd'){
        composition.track3ColorChange();
    }
    if(key == 'f'){
        composition.track3Implosion();
    }
    if(key == 'g'){
        composition.track3Main2();
    }
    if(key == 'h'){
        composition.track3Solo();
    }
    if(key == 'j'){
        composition.track3Secondary2();
    }
    if(key == 'k'){
        composition.track3Burst();
    }
    
    // Track 4
    
    if(key == 'z'){
        composition.track4Pattern1();
    }
    if(key == 'x'){
        composition.track4Pattern2();
    }
    if(key == 'c'){
        composition.track4Pattern3();
    }
    if(key == 'v'){
        composition.track4Finale();
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
