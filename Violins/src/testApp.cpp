#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){
    l.update();
}

//--------------------------------------------------------------
void testApp::draw(){
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
        composition.track3Orbit1();
    }
    if(key == 's'){
        composition.track3Corruption1();
    }
    if(key == 'd'){
        composition.track3Orbit2();
    }
    if(key == 'f'){
        composition.track3Corruption2();
    }
    if(key == 'g'){
        composition.track3Orbit3();
    }
    if(key == 'h'){
        composition.track3Corruption3();
    }
    if(key == 'j'){
        composition.track3FinalBattle();
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
