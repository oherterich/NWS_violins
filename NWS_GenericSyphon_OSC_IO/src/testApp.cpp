#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Syphon init
    ofSetWindowTitle("Generic IO");
    mainOutput.setName("GenericIO_Output");
    
    //render reset
    ofBackground(0);
    ofSetVerticalSync( TRUE );
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetBackgroundAuto(TRUE);
    ofSetFrameRate(60);

    //debug and beta
    counter = 0;
	ofSetCircleResolution(50);
}

//--------------------------------------------------------------
void testApp::update(){
counter = counter + 0.033f;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // Gl frame clear so we can capture it with syphon
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //----------------draw to shyphon here---------------

    
    //let's draw a circle:
	ofSetColor(255,130,0);
	float radius = 50 + 10 * sin(counter);
	ofFill();		// draw "filled shapes"
	ofCircle(ofGetWindowSize()/2,radius);
    
    
    
    mainOutput.publishScreen(); // push the frame to the server
    
    
    //----------------draw outside shyphon here---------------
    
    //debug stuff
    ofDrawBitmapString("hello debug view", 10,10);

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
