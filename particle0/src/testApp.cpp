#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync( true );
    ofBackground( 0 );
    
    for ( int i = 0; i < 1000; i++ ) {
        Particle tmp;
        
        tmp.setParams(ofRandomWidth(), ofRandomHeight(), ofRandom(-5.0, 5.0), ofRandom(-5.0, 5.0), 2.0);
        
        particleList.push_back( tmp );
    }
    
    toggle = 0;
    reset = false;
}

//--------------------------------------------------------------
void testApp::update(){
    

    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); it++) {
        
        switch (toggle) {
            case 0:
                it->applyGravity(0.1, ofGetWindowHeight());
                break;
                
            case 1:
                it->addAttractionForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 1000, 0.1);
                break;
                
            case 2:
                it->addRepulsionForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 100, 1.0);
                break;
                
            case 3:
                it->addClockwiseForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 100, 0.2);
                break;
                
            case 4:
                it->addCounterClockwiseForce(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 100, 0.2);
                break;
                
            case 5:
                it->addForce( ofVec2f (1.0, 1.0) );
                break;
                
            case 6:
                it->xenoToPoint(mouseX, mouseY, 0.01);
                break;
                
            case 7:
                break;
                
            case 8:
                it->addNoise( 5.0 );
                break;
                
            case 9:
                it->lerpToColor(ofColor(255,0,0), ofColor(255,255,0), 0.1);
                break;
                
            default:
                break;
        }
        
        if (reset) {
            it->setParams(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, ofRandom(-5, 5), ofRandom(-5, 5), 2);
        }
        


        it->addDampingForce(0.01);
        it->update();
        it->resetForces();

    }
    
    reset = false;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); it++) {
        it->draw();
    }
    
    ofDrawBitmapString(" 0: Gravity    1: Attraction    2: Repulsion    3: Clockwise    4: Counter-clockwise    5: Force    6: Xeno    7: Nothing for now", ofPoint(10, 20));
    ofDrawBitmapString("8: Noise    9: Color Lerp    R: Reset    B: Burst", ofPoint(10, 40));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
            case '0':
                toggle = 0;
                break;
            
        case '1':
            toggle = 1;
            break;
            
        case '2':
            toggle = 2;
            break;
            
        case '3':
            toggle = 3;
            break;
            
        case '4':
            toggle = 4;
            break;
            
        case '5':
            toggle = 5;
            break;
            
        case '6':
            toggle = 6;
            break;
            
        case '7':
            toggle = 7;
            break;
            
        case '8':
            toggle = 8;
            break;
            
        case '9':
            toggle = 9;
            break;
    }
    
    if (key == 'r' || key == 'R') {
        reset = true;
    }
    
    if (key == 'b' || key =='B') {
        for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); it++) {
            it->burst(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 100.0);
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
