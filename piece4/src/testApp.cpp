#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	receiver.setup(PORT);
    
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<FxaaPass>();
    //post.createPass<VerticalTiltShifPass>();
    post.createPass<DofAltPass>()->setFStop(5);
    //post.createPass<GodRaysPass>();
    
   // post.createPass<BloomPass>();
    //post.createPass<ZoomBlurPass>();
    
    post.getPasses();
    
    
	ofBackground(0,0,20);
    ofEnableAlphaBlending();
    //ofEnableDepthTest();
    ofSetSphereResolution(24);
    
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    material.setShininess( 120 );
    material.setAmbientColor(ofColor((255)));
    // the light highlight of the material //
	material.setSpecularColor(ofColor(255, 0, 255, 255));


}

//--------------------------------------------------------------
void testApp::update(){

    GetOSC();
    
    pos.x = ofNoise(ofGetElapsedTimef()/10);
    pos.y = ofNoise(ofGetElapsedTimef()/10+1000)+ofGetElapsedTimef()/100;
    pos.z = ofNoise(ofGetElapsedTimef()/10-1000);
    pos = pos*1000;
    
    tmp = pos;
    
    Channel01_Attack = 0.1*Channel01_Attack + 0.9*lastChannel01_Attack;
    

    
    tmp.x = tmp.x + sin(ofGetElapsedTimef())*100; //+ Channel01_Attack*100;
    tmp.z = tmp.z + cos(ofGetElapsedTimef())*100;// + Channel01_Attack*-100;
    //tmp.y = tmp.y + Channel01_Attack*100;
    
    
    //cam.roll( ofRadToDeg(sin(ofGetElapsedTimef()/10)*TWO_PI));
    
    

    tmp.x = tmp.x + cos(ofGetElapsedTimef())*Channel01_Attack*50;
    tmp.y = tmp.y + sin(ofGetElapsedTimef())*Channel01_Attack*50;
    
    PosList.push_back(tmp);
   
    
    if (PosList.size()>1000) {
        PosList.erase(PosList.begin());
    }
    
    ofVec3f xenoed = pos*0.1 + lastpos*0.9;
    cam.lookAt(tmp*0.2+PosList[PosList.size()-10]*0.8);
    cam.setPosition(xenoed.x, xenoed.y, xenoed.z);
    
   
   // cam.setPosition(xenoed+200);
   
    
    lastpos = xenoed;
    lastChannel01_Attack = Channel01_Attack;
    
    pointLight.setPosition(pos);
    preview.lookAt(tmp);
}



//--------------------------------------------------------------
void testApp::draw(){
    //AudioDebug();
    
   // preview.begin();
    cam.draw();
    
    post.begin(cam);
   // ofEnableLighting();
//    pointLight.enable();
//    pointLight.setAttenuation(2000);
    
    
	//material.begin();

    
    ofSetColor(255,0,127);
    ofSetLineWidth(10);
    ofPolyline P;
    P.clear();
    
    for( vector<ofVec3f>::iterator it=PosList.begin(); it!=PosList.end(); it++ ){
        
        P.addVertex( it->x, it->y, it->z );
        
    }
    P.draw();

    post.end();
    
  //  preview.end();
    
    //ofDrawBitmapString(ofToString(post. ), 20,20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    

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