#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync( true );
    ofBackground( 14, 12, 28 );
    ofSetFrameRate(60);
    
    for (int i = 0; i < 400; i++) {
    Dancer d( ofVec2f(ofRandomWidth(), ofRandomHeight()), ofVec2f(ofRandom(1, 4), ofRandom(1, 4)), 3, 5);
        
    //Dancer d( ofVec2f(0, ofRandomHeight()), ofVec2f(ofRandom(1, 4), ofRandom(1, 4)), 3, 25);
        
        
    dancerList.push_back( d );
             }
}

//--------------------------------------------------------------
void testApp::update(){
    for ( vector<Dancer>::iterator it = dancerList.begin(); it != dancerList.end(); it++ ) {
        it->update(ofVec2f(mouseX, mouseY));
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    for ( vector<Dancer>::iterator it = dancerList.begin(); it != dancerList.end(); it++ ) {
        it->draw();
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
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
