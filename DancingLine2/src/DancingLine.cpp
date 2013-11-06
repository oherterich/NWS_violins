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
    post.createPass<RimHighlightingPass>();
    post.createPass<VerticalTiltShifPass>();
    post.createPass<GodRaysPass>();
//    post.createPass<ContrastPass>();

    post.createPass<FxaaPass>();
//    post.createPass<BloomPass>();
//    post.createPass<SSAOPass>();

    ofSetSphereResolution(24);
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight.setSpotlight(800.0, 2.0);
    pointLight2.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight2.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    pointLight2.setSpotlight(1000.0, 0.2);
    material.setShininess( 200 );
    material.setAmbientColor(ofColor((255)));
    // the light highlight of the material //
	material.setSpecularColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255));
    jitter = 5;
    separate = false;
    rage = true;
    for(int i=0; i<500; i++){
        LinePiece l;
        pieces.push_back(l);
    }
    c = ofColor(255,0,0);
    lastc = ofColor(255,0,0);
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
    pointLight2.setPosition(pos+200);


}

void DancingLine::draw(float pitch){
    post.begin(cam);
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
	material.begin();
    //cam.begin();
    
    ofSetLineWidth(10);
    ofColor newc = ofColor(255,0,0);
    newc.setHue(ofClamp(ofMap(pitch,0,3000,0,255),0,255));
    c=lastc;
    c.lerp(newc, 50);
    lastc = newc;
// c = ofColor(ofClamp(ofMap(pitch,0,3000,0,255),0,255),ofClamp(ofMap(pitch,0,3000,0,255),0,255),ofClamp(ofMap(pitch,0,3000,0,255),0,255));
    ofSetColor(c);
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
                    if(rage){
                        it->x = x;
                        it->y = y;
                        it->z = z;
                    } else {
                        float r = ofRandom(10.0);
                        if(r>9.97){
                            it->x = 0;
                            it->y = 0;
                            it->z = 0;
                        }
                    }
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
    post.begin(cam);
    ofEnableLighting();
    pointLight.enable();
    pointLight.setPosition(ofVec3f(x,y,0));
	material.begin();
    //cam.begin();
    ofSetColor(255);
    ofSetLineWidth(10);
    ofPushMatrix();
//    ofTranslate(x,y);

    for(int i=0; i<20; i++){
        pieces[i].draw();
    }
    ofPopMatrix();
    post.end();

}

void DancingLine::updatePiece(){
    for( vector<ofVec3f>::iterator it=explodeList.begin(); it!=explodeList.end(); it++ ){
        float ind = it-explodeList.begin();
        pieces[ind].pos.set(ofVec3f(it->x,it->y,it->z));
        pieces[ind].update();
        it->x = pieces[ind].pos.x;
        it->y = pieces[ind].pos.y;
        it->z = pieces[ind].pos.z;
        cam.setPosition(500,100,1000);

    }

}