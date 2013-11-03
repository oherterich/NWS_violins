#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetCircleResolution(1000);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    ofBackground(0);
    
    circle p;
    cirList.push_back(p);

}

void testApp::addParticle() {
    Particle tmp;
    
    double ax = ofRandom(TWO_PI);
    
    tmp.setParams(250*cos(ax)+ofGetWidth()/2, 250*sin(ax)+ofGetHeight()/2, 0, 0, 1.5);
    
    tmp.life = 75;
    
    particleList.push_back( tmp );
}

//--------------------------------------------------------------
void testApp::update(){
   // myCircle.update();
    
    myMap.update();
    
    if(vac && cirList.size()>0){
//        cirList[cirList.size()-1]-=ofVec2f(ofGetWidth()/2, ofGetHeight()/2).normalized()*
//        ofMap(ofDist(cirList[cirList.size()-1].x, cirList[cirList.size()-1].y, 0,0), 250, 50, 1, 3);
//        
//        if(ofDist(cirList[cirList.size()-1].x, cirList[cirList.size()-1].y, 0,0)<50){
        

            cirList.pop_back();
            vac=false;
        }
    
 //   }
    

    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end();it++) {
        
      //  it->addNoise(ofMap(it->pos.y, ofGetHeight()+1+it->initSize/2, 0, 0, .3));
        
        
        if(storm){
            it->addClockwiseForce(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, .1);
            it->addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2,
                                   ofMap(ofDist(it->pos.x, it->pos.y, ofGetWidth()/2,ofGetHeight()/2), ofGetWidth()/2, 0, .3,.1));
            
            if(ofDist(it->pos.x, it->pos.y, ofGetWidth()/2, ofGetHeight()/2)>250){
                it->pos-=ofVec2f(ofGetWidth()/2, ofGetHeight()/2).normalized()*2*it->vel;
            }
            
            if(ofDist(it->pos.x, it->pos.y, ofGetWidth()/2,ofGetHeight()/2)<50){
                it->consigned=true;
            }
            
        }
        it->ageVisuals(true, false);
        
        it->update();
        it->resetForces();
    }
    
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end();it++) {
        
        if (it->dead()==true) {
            particleList.erase(it);
            break;
        }
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    for (vector<Particle>::iterator it = particleList.begin(); it != particleList.end(); it++) {
        it->draw();
    }
    
    ofPushMatrix();
    ofTranslate(ofGetWindowSize()/2);
//  myCircle.drawCircle(0,0,250);
    
    ofNoFill();
    ofSetColor(255, 255, 255, 255);
    for (int i = 0; i<cirList.size(); i++) {
        myMap.Place(0,0,250);
      //  ofCircle(cirList[i].x, cirList[i].y, myMap.posList[i].z);
        cirList[i].drawCircle(myMap.posList[i].z);
        cirList[i].update();
        cirList[i].pos-=(cirList[i].pos-myMap.posList[i]).normalized();
        cirList[i].rota(.5);

    }
    
    cirList[0].pos=myMap.posList[0];
    ofPopMatrix();
    
    if(snow){
    //    if(ofGetElapsedTimeMillis()%3==0 ){
            addParticle();
       // }
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key=='c'){
    
    float x;
    float y;
    
    float temp = rand()%2;
    float temp2= rand()%2;
    
    if (temp==0)  x = ofRandom(-.75*ofGetWidth(), -.65*ofGetWidth());
    if (temp==1)  x = ofRandom(.65*ofGetWidth(), .75*ofGetWidth());
    if (temp2==0)  y = ofRandom(-.75*ofGetHeight(), -.65*ofGetHeight());
    if (temp2==1)  y = ofRandom(-.65*ofGetHeight(), -.75*ofGetHeight());
     
    circle p;
        p.pos.x=x;
        p.pos.y=y;
    cirList.push_back(p);
        
    }
    
    if(key=='s'){
        snow=!snow;
    }
    
    if(key=='t'){
        storm=!storm;
    }
    
    if(key=='v'){
        vac=!vac;
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