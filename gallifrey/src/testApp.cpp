#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetCircleResolution(1000);
    ofEnableSmoothing();
    
    ofBackground(0);
    ofNoFill();
    
    cirList.push_back(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));

}

void testApp::addParticle() {
    Particle tmp;
    
    tmp.setParams(ofRandomWidth(), -ofRandom(-5,-200), 0, .1, 2.0);
    
    tmp.life = ofRandom(1000);
    
    particleList.push_back( tmp );
}

//--------------------------------------------------------------
void testApp::update(){
    myCircle.update();
    
    myMap.update();
    
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); ) {
        
        it->update();
        it->resetForces();
        
        if (it->dead()) {
            particleList.erase(it);
        }
        it++;

    }
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
    
    
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); it++) {
        it->draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key!='s'){
    
    float x;
    float y;
    
    float temp = rand()%2;
    float temp2= rand()%2;
    
    if (temp==0)  x = ofRandom(-.1*ofGetWidth(), -.15*ofGetWidth());
    if (temp==1)  x = ofRandom(1.1*ofGetWidth(), 1.15*ofGetWidth());
    if (temp2==0)  y = ofRandom(-.1*ofGetHeight(), -.15*ofGetHeight());
    if (temp2==1)  y = ofRandom(1.1*ofGetHeight(), 1.15*ofGetHeight());
        
    cirList.push_back(ofVec2f(x,y));
        
    }
    
    if(key=='s'){
        for ( int i = 0; i < 100; i++ ) {
            addParticle();
        }
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