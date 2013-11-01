//
//  DancingLine.cpp
//  track04
//
//  Created by Joseph Moore on 10/31/13.
//
//

#include "DancingLine.h"

DancingLine::DancingLine(){
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<VerticalTiltShifPass>();
    //post.createPass<DofPass>();
    post.createPass<GodRaysPass>();
    post.createPass<FxaaPass>();
    post.createPass<BloomPass>();
    ofSetSphereResolution(24);
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    material.setShininess( 120 );
    material.setAmbientColor(ofColor((255,0,127)));
    // the light highlight of the material //
	material.setSpecularColor(ofColor(255, 0, 255, 255));
    jitter = 5;
    separate = false;
}

void DancingLine::update(float attack, double start){
    pos.x = sin((ofGetElapsedTimef()-start)/10);
    pos.y = cos((ofGetElapsedTimef()-start)/10+1000)+(ofGetElapsedTimef()-start)/10;
//    pos.z = sin(ofGetElapsedTimef()/10-1000);
    pos.z = 0;

    pos = pos*1000;
    
    tmp = pos;
    
    //    Channel01_Attack = 0.1*Channel01_Attack + 0.9*lastChannel01_Attack;
    
    
    
    tmp.x = tmp.x + sin(ofGetElapsedTimef()-start)*100; //+ Channel01_Attack*100;
    tmp.z = tmp.z + cos(ofGetElapsedTimef()-start)*100;// + Channel01_Attack*-100;
    //tmp.y = tmp.y + Channel01_Attack*100;
    
    
    //cam.roll( ofRadToDeg(sin(ofGetElapsedTimef()/10)*TWO_PI));
    cam.lookAt(tmp);
    
    
    tmp.x = tmp.x + cos(ofGetElapsedTimef()-start)*attack*ofRandom(30,80);
    tmp.y = tmp.y + sin(ofGetElapsedTimef()-start)*attack*ofRandom(30,80);
    
    PosList.push_back(tmp);
    
    
    if (PosList.size()>500) {
        PosList.erase(PosList.begin());
    }
    
    ofVec3f xenoed = pos*0.001 + lastpos*0.999;
    
    cam.setPosition(xenoed.x+400, xenoed.y+400, xenoed.z+400);
    
    
    // cam.setPosition(xenoed+200);
    
    
    lastpos = xenoed;
    lastChannel01_Attack = attack;
    
    pointLight.setPosition(pos);
}

void DancingLine::draw(float pitch){
    post.begin(cam);
    ofEnableLighting();
    pointLight.enable();
    
    
	material.begin();
    //cam.begin();
    
    ofSetLineWidth(10);

    ofSetColor(ofClamp(pitch,0,255), ofClamp(pitch/10, 0, 255), ofClamp(30*(pitch/180), 0, 255));

        if(separate){
//            ofTranslate(sin(ofNoise(ofGetElapsedTimeMillis(), ofGetElapsedTimeMillis())), cos(ofNoise(ofGetElapsedTimeMillis(), ofGetElapsedTimeMillis())));
            float counter = 0;
            for(int i=0; i<100; i++){
                ofPolyline P;
                P.clear();
                for( vector<ofVec3f>::iterator it=floatList.begin(); it!=floatList.end(); it++ ){
                    float x = it->x+i/20*ofRandom(-jitter,jitter);
                    float y = it->y+i/20*ofRandom(-jitter,jitter);
                    float z = it->z+i/20*ofRandom(-jitter,jitter);
                    P.addVertex(x,y,z);
                    it->x = x;
                    it->y = y;
                    it->z = z;
                }
                P.draw();
            }
        } else {
            for(int i=0; i<100; i++){
                ofPolyline P;
                P.clear();
                for( vector<ofVec3f>::iterator it=PosList.begin(); it!=PosList.end(); it++ ){
                    P.addVertex( it->x+i/20*ofRandom(-jitter,jitter), it->y+i/20*ofRandom(-jitter,jitter), it->z+i/20*ofRandom(-jitter,jitter) );
                }
                P.draw();
            }

        }
    //cam.end();
    post.end();
    
    //ofDrawBitmapString(ofToString(post. ), 20,20);
}


void DancingLine::drawPiece(float x, float y){
    ofEnableLighting();
    pointLight.enable();
    pointLight.setPosition(ofVec3f(x,y,0));
	material.begin();
    //cam.begin();
    ofSetColor(255);
    ofSetLineWidth(10);
    ofPushMatrix();
    ofTranslate(x,y);
    for(int i=0; i<100; i++){
        ofPolyline P;
        P.clear();
        P.addVertex(0+i/20*ofRandom(-jitter,jitter),0+i/20*ofRandom(-jitter,jitter),0+i/20*ofRandom(-jitter,jitter));
        P.addVertex(50+i/20*ofRandom(-jitter,jitter),0+i/20*ofRandom(-jitter,jitter),0+i/20*ofRandom(-jitter,jitter));
        P.draw();

    }
    ofPopMatrix();

}