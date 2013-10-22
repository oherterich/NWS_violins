#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetCircleResolution(200);
    
    ofBackground(0);
    ofNoFill();
    
    for (int i = 0; i<25; i++) {
        cirList[i].set(ofRandomHeight(), ofRandomWidth());
    }

}

//--------------------------------------------------------------
void testApp::update(){
    myCircle.update();
    
    myMap.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWindowSize()/2);
//  myCircle.drawCircle(0,0,250);
    
    for (int i = 0; i<25; i++) {
        myMap.Place(0,0,250);
        ofCircle(cirList[i].x, cirList[i].y, myMap.posList[i].z);
        cirList[i]-=(cirList[i]-myMap.posList[i]).normalize();
    }
    
    
    ofPopMatrix();
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