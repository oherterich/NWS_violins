#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetCircleResolution(1000);
    
    ofBackground(0);
    ofNoFill();
    
    cirList.push_back(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));

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
    
    for (int i = 0; i<cirList.size(); i++) {
        myMap.Place(0,0,250);
        ofCircle(cirList[i].x, cirList[i].y, myMap.posList[i].z);
        cirList[i]-=(cirList[i]-myMap.posList[i]).normalized();
    }
    
    cirList[0]=myMap.posList[0];
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    float x;
    float y;
    
    float temp = rand()%2;
    float temp2= rand()%2;
    
    if (temp==0)  x = ofRandom(-.3*ofGetWidth(), -.1*ofGetWidth());
    if (temp==1)  x = ofRandom(1.1*ofGetWidth(), 1.3*ofGetWidth());
    if (temp2==0)  y = ofRandom(-.3*ofGetHeight(), -.1*ofGetHeight());
    if (temp2==1)  y = ofRandom(1.1*ofGetHeight(), 1.3*ofGetHeight());
        
    cirList.push_back(ofVec2f(x,y));

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