//
//  DancingLine.cpp
//  track04
//
//  Created by Joseph Moore on 10/31/13.
//
//

#include "DancingLine.h"

DancingLine::DancingLine(){
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
//    pos.z = sin((ofGetElapsedTimef()-start)/10+10000);;

    pos = pos*1000;
    
    tmp = pos;
    
    //    Channel01_Attack = 0.1*Channel01_Attack + 0.9*lastChannel01_Attack;
    
    
    
    tmp.x = tmp.x + sin(ofGetElapsedTimef()-start)*100; //+ Channel01_Attack*100;
//    tmp.z = tmp.z + cos(ofGetElapsedTimef()-start)*100;// + Channel01_Attack*-100;
    //tmp.y = tmp.y + Channel01_Attack*100;
    
    flat = tmp;
    //cam.roll( ofRadToDeg(sin(ofGetElapsedTimef()/10)*TWO_PI));
    
    tmp.x = tmp.x + cos(ofGetElapsedTimef()-start)*attack*ofRandom(30,80);
    tmp.y = tmp.y + sin(ofGetElapsedTimef()-start)*attack*ofRandom(30,80);
    
    PosList.push_back(tmp);
    
    
    if (PosList.size()>500) {
        PosList.erase(PosList.begin());
    }
    
    ofVec3f xenoed = pos*0.1 + lastpos*0.9;
    
    
    
    // cam.setPosition(xenoed+200);
    
    
    lastpos = xenoed;
    lastChannel01_Attack = attack;

}

void DancingLine::draw(float pitch){

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
            for(int i=0; i<80; i++){
                ofPolyline P;
                P.clear();
                for( vector<ofVec3f>::iterator it=floatList.begin(); it!=floatList.end(); it++ ){
                    if(floatList.end()-80<it){
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
                            it->x = -2000;
                            it->y = 0;
                            it->z = 0;
                        }
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
    
    //ofDrawBitmapString(ofToString(post. ), 20,20);
}


void DancingLine::drawPiece(float x, float y){
    ofSetColor(255);
    ofSetLineWidth(10);
    ofPushMatrix();
//    ofTranslate(x,y);

    for(int i=0; i<20; i++){
        pieces[i].draw();
    }
    ofPopMatrix();

}

void DancingLine::updatePiece(){
    for( vector<ofVec3f>::iterator it=explodeList.begin(); it!=explodeList.end(); it++ ){
        float ind = it-explodeList.begin();
        pieces[ind].pos.set(ofVec3f(it->x,it->y,it->z));
        pieces[ind].update();
        it->x = pieces[ind].pos.x;
        it->y = pieces[ind].pos.y;
        it->z = pieces[ind].pos.z;
    }

}