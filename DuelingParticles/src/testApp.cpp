#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    receiver.setup(PORT);
  //  ofBackground(0);
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    bg.loadImage("bg.png");
    debug = false;
    
    animCam.setFarClip(10000);
    duelingParticles.setName("Dueling particles");
    
    
    
    bodyA.setup(4, 400);
    bodyB.setup(4, 400);
    bodyA.texture.loadImage("circle.png");
    bodyB.texture.loadImage("circle.png");
    bodyA.CurrentColor = ofColor (0,52,92);
    bodyB.CurrentColor = ofColor (92,15,2);
    
    HeadA.setup(20, 100);
    HeadA.texture.loadImage("blurred_star.png");
    HeadA.CurrentColor = ofColor (30,52,92);
    
    HeadB.setup(20, 60);
    HeadB.texture.loadImage("blurred_star.png");
    HeadB.CurrentColor = ofColor (94,0,31);
    
    CoreA.setup(3, 100);
    CoreA.texture.loadImage("circle.png");
    CoreA.CurrentColor = ofColor (0,52,92);
    
    CoreB.setup(3, 100);
    CoreB.texture.loadImage("circle.png");
    CoreB.CurrentColor = ofColor (255,97,95);
    
    BubblesB.setup(5, 20);
    BubblesB.texture.loadImage("Blur07.png");
    BubblesB.CurrentColor = ofColor(159,94,45);
    
    BubblesA.setup(5, 20);
    BubblesA.texture.loadImage("Blur07.png");
    BubblesA.CurrentColor = ofColor(45,150,159);
    
    WispsA.setup(6, 200);
    WispsA.texture.loadImage("blurred_star.png");
    WispsA.CurrentColor = ofColor(0,173,239);
    
    WispsB.setup(6, 200);
    WispsB.texture.loadImage("blurred_star.png");
    WispsB.CurrentColor = ofColor(255,90,0);
    

    
    lineA.setup(2, 1000);
    lineA.CurrentColor = ofColor (0,132,220);
    
    lineB.setup(2, 1000);
    lineB.CurrentColor = ofColor (255,90,2);
    
    bokeh.setup(2, 50000);
    bokeh.CurrentColor = ofColor(212,0,220);
    bokeh.texture.loadImage("AquaBall.png");
    
    
    //--- this needs to be lifted to the UI-----//
    headSpeed = 0.5; // [averaged amplitude?]in revolutions Per Sec
    headSpace = 10; // [?] to be multiplied by the negative normal diffpitch
    bodyA.setResolution(0.15);
    bodyB.setResolution(0.15);
    
    HeadA.setResolution(0.15);
    HeadB.setResolution(0.15);
    
    CoreA.setResolution(0.15);
    CoreB.setResolution(0.15);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
     GetOSC();
    
    float tmpA;
    float tmpB;
    
    tmpA = Channel01_Attack;
    tmpB = Channel02_Attack;
    
    tmpA = ofClamp(Channel01_Attack, 0.1, 3);
    tmpB = ofClamp(Channel02_Attack, 0.1, 3);
    
    averagedAtk_A.push_back(tmpA);
    if (averagedAtk_A.size()>10) {
        averagedAtk_A.erase(averagedAtk_A.begin());
    }
    
    for (int i = 0; i<averagedAtk_A.size(); i++) {
        averagedA += averagedAtk_A[i];
    }
    
    
    
    averagedAtk_B.push_back(tmpB);
    if (averagedAtk_B.size()>10) {
        averagedAtk_B.erase(averagedAtk_B.begin());
    }
    
    for (int i = 0; i<averagedAtk_B.size(); i++) {
        averagedB += averagedAtk_B[i];
    }
    
    averagedB = averagedB/averagedAtk_B.size();
    averagedB = averagedB*0.4 + lastB*0.6;
    
    averagedA = averagedA/averagedAtk_A.size();
    averagedA = averagedA*0.4 + lastA*0.6;
    
    
    

    
    averagedA = ofMap(averagedA, 0.2, 3, 0.1, 0.5);
    averagedB = ofMap(averagedB, 0.2, 3, 0.1, 0.5);

    //lastB = averagedA;
    //lastA = averagedB,
    
    //cout << averagedA << endl;
    headSpeed = 0.5 + (Channel01_Amplitude/5);
    averagedAMP = headSpeed*0.03 + lastAMP*0.97;
    headSpace = 10 - (Channel01_Amplitude);
    lastAMP = averagedAMP;
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    deltaA = averagedA + ofGetElapsedTimef();
    deltaB = averagedB + ofGetElapsedTimef();
    delta = (deltaA + deltaB)/2;
    
    
    // lets create a new position based on a 3dnoise.
    
    tA = (deltaA) * 0.1f;
	neoPosA.x = ofSignedNoise(tA, 0, 0);
	neoPosA.y = ofSignedNoise(0, tA, 0);
	neoPosA.z = ofSignedNoise(0, 0, tA);
    
    tB = (deltaB) * 0.1f;
	neoPosB.x = ofSignedNoise(tB, 0, 0);
	neoPosB.y = ofSignedNoise(0, tB, 0);
	neoPosB.z = ofSignedNoise(0, 0, tB);
    
    t = (delta) * 0.1f;
	neoPos.x = ofSignedNoise(t, 0, 0);
	neoPos.y = ofSignedNoise(0, t, 0);
	neoPos.z = ofSignedNoise(0, 0, t);
    
    
	neoPosA *= 400; // scale from -1,+1 range to -400,+400
    neoPosB *= 400; // scale from -1,+1 range to -400,+400
    neoPos *= 400; // scale from -1,+1 range to -400,+400
    
    
    // calculate the diff between the neo and the last post
    // this will create a heading force.
    
    headingA = neoPosA - lastPosA;
    headingA.normalize();
    
    headingB = neoPosB - lastPosB;
    headingB.normalize();
    
    heading = neoPos - lastPos;
    heading.normalize();
    
    // something is happening here that creates a random jump in the values. :/
    
    
    //flip-flop
    lastPosA = neoPosA;
    lastPosB = neoPosB;
    lastPos = neoPos;
    
    //------------ sineHeads --------------
    
    float Sin = sin(ofGetElapsedTimef()*TWO_PI*averagedAMP);
    float Cos = cos(ofGetElapsedTimef()*TWO_PI*averagedAMP);
    
    
    
    headA = ofVec3f(Sin*headSpace,0,Cos*headSpace);
    headB = ofVec3f(Sin*headSpace*-1,0,Cos*headSpace*-1);
    
    // rotate the sineheads
    
    headB.rotate(90,heading);
    headA.rotate(90,heading);
    
    //place the heads
    
    headA+=neoPosA;
    headB+=neoPosB;
    
    //-----------sinedwisps----------------//
    
    float SinWisp ;
    float CosWisp ;
    
    SinWisp = sin(ofRandom(TWO_PI));
    CosWisp = cos(ofRandom(TWO_PI));
    
    headBWisps = ofVec3f(SinWisp,0,CosWisp);
    headBWisps.rotate(90,headingB);
    headBWisps += headB;
    
    headAWisps = ofVec3f(SinWisp,0,CosWisp);
    headAWisps.rotate(90,headingA);
    headAWisps += headA;
    
    
    // camera stuff
    
    camPos = camPos*0.7 + neoPos*0.3*0.8;
    camLook = neoPos - heading*10;
    
    
    animCam.setPosition(camPos+ofVec3f(10,15,12)); // so we are not coplanar.
    animCam.lookAt(camLook);
    
    
    // particles
    
    
    
    BubblesB.emiter = headBWisps;
    BubblesB.addParticle();
    BubblesB.update();
    
    BubblesA.emiter = headAWisps;
    BubblesA.addParticle();
    BubblesA.update();
    
    WispsA.emiter = headA;
    WispsA.addParticle();
    WispsA.applyForces();
    WispsA.update();
    
    WispsB.emiter = headB;
    WispsB.addParticle();
    WispsB.applyForces();
    WispsB.update();
    
    
    bodyA.emiter = headA;
    bodyA.addParticle();
    bodyA.update();
    
    bodyB.emiter = headB;
    bodyB.addParticle();
    bodyB.update();
    
    HeadA.emiter = headA;
    HeadA.addParticle();
    HeadA.update();
    
    HeadB.emiter = headB;
    HeadB.addParticle();
    HeadB.update();
    
    CoreA.emiter = headA;
    CoreA.addParticle();
    CoreA.update();
    
    CoreB.emiter = headB;
    CoreB.addParticle();
    CoreB.update();
    
    lineA.emiter = bodyA.PartList[180].pos;
    lineA.applyForces(
                      ofVec3f(
                              ofSignedNoise(ofGetElapsedTimef()),
                              ofSignedNoise(ofGetElapsedTimef()+1000),
                              ofSignedNoise(ofGetElapsedTimef()+TWO_PI)));
    lineA.addParticle();
    lineA.update();
    
    lineB.emiter = bodyB.PartList[180].pos;
    lineB.applyForces(
                      ofVec3f(
                              ofSignedNoise(300+ofGetElapsedTimef()),
                              ofSignedNoise(123456789+ofGetElapsedTimef()),
                              ofSignedNoise(1100000+ofGetElapsedTimef())));
    lineB.addParticle();
    lineB.update();
    
    bokeh.addParticle();
    bokeh.update();
    
    
    //reset averages
    averagedA = 0;
    averagedB = 0;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    // render norm
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ofSetColor(255);
    ofFill();
    
    // draw Bg image
    bg.draw(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    
    if (debug == true) {
        debugCam.begin();
    } else if (debug==false){
        
        animCam.begin();
    }
    
    bokeh.draw();
    
    BubblesB.draw();
    BubblesA.draw();
    bodyA.draw();
    bodyB.draw();
    HeadA.draw();
    HeadB.draw();
    CoreA.draw();
    CoreB.draw();
    
    WispsA.draw();
    WispsB.draw();
    
    lineA.draw();
    lineB.draw();
    
    if (debug == true) {
        
        // draw debug stuff
        
        
        
        
        
        //        ofCircle(headA, 2);
        //        ofCircle(headB, 2);
        
        ofLine(neoPos,neoPos+(heading*10));
        ofLine(camPos,ofVec3f(0,0,0));
        ofLine(camPos, camLook);
        
        ofLine(heading*30,ofVec3f(0,0,0));
        
        animCam.draw();
        debugCam.end();
        AudioDebug();
    } else if (debug==false){
        animCam.end();
    }
    
    duelingParticles.publishScreen();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'd') {
        debug = !debug;
    };
    
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
