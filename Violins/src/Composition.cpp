//
//  Composition.cpp
//  Violins
//
//  Created by Joseph Moore on 10/17/13.
//
//

#include "Composition.h"



void Composition::setup(){
    track = 0;
    status = 0;
    for(int i=0;i<30;i++){
        Dart d;
        darts.push_back(d);
        Vine v;
        vines.push_back(v);
    }
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
}

void Composition::update(){
    if(track == 1){
        pointLight.setSpotlight(800.0, 200.0);
        pointLight2.setSpotlight(1200.0, 200.0);
        pointLight.setPosition(g.myCircle.pos);
        pointLight2.setPosition(g.myCircle.pos+200);
        material.setShininess( 500 );
        cam.resetTransform();
        cam.setPosition(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2);
        cam.roll(180);
        if(status == 1){
            g.update();
        } else if (status == 2){
            g.update();
            for(int i=0; i<vines.size(); i++){
                vines[i].update();
            }
        } else if (status == 3){
            g.update();
            for(int i=0; i<vines.size(); i++){
                vines[i].update();
            }
        } else if (status == 4){
            g.update();
            for(int i=0; i<vines.size(); i++){
                vines[i].update();
                vines[i].wither();
            }
        }
    } else if (track == 2){
        g.clearCircles();
        ofPushMatrix();
        pointLight.setPosition(line1.pos);
        pointLight2.setPosition(line2.pos);
        pointLight.setSpotlight(800.0, 2.0);
        pointLight2.setSpotlight(1000.0, 0.2);
        material.setShininess( 200 );
        if(status == 1){
            line1.update(attack01*2, started);
            line2.update(attack02, started);
        } else if (status == 2){
            for(int i=0; i<darts.size(); i++){
                darts[i].state = 0;
                darts[i].pos = line1.pos;
                darts[i].update();
            }
        } else if (status == 3){
            for(int i=0; i<darts.size(); i++){
                darts[i].state = 1;
                darts[i].pos = line1.pos;
                darts[i].update();
            }
        } else if (status == 4){
            g.update();

//            line1.updatePiece();
//            line2.updatePiece();
        } else if (status == 5){
            
        }
        ofVec3f xenoed = line1.pos*0.001 + line1.lastpos*0.999;
        cam.lookAt(line1.flat);
        cam.setPosition(xenoed.x+400, xenoed.y+400, xenoed.z+400);
        ofPopMatrix();
    } else if (track == 3){
        if (status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        } else if (status == 4){
            
        }
    } else if (track == 4){
        if (status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        }
    }
}

void Composition::draw(){
    post.begin(cam);
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
	material.begin();
    if(track == 1){
        if(status == 1){
            g.draw(pitch01*2,pitch02);
        } else if (status == 2){
            g.draw(pitch01*2,pitch02);
            material.setShininess( 10 );
            for(int i=0; i<vines.size(); i++){
                vines[i].draw((pitch01+pitch02)/2);
            }
            material.setShininess( 500 );
        } else if (status == 3){
            g.draw(pitch01*2, pitch02);
            material.setShininess( 200 );
            material.setShininess( 10 );
            for(int i=0; i<vines.size(); i++){
                vines[i].draw((pitch01+pitch02)/2);
            }
            material.setShininess( 500 );
        } else if (status == 4){
            g.drawLines();
            for(int i=0; i<vines.size(); i++){
                vines[i].draw((pitch01+pitch02)/2);
            }
        }
    } else if (track == 2){
        ofPushMatrix();
        if(status == 1){
            line1.draw(pitch01*2);
            line2.draw(pitch02);
        } else if (status == 2){
            line1.draw(pitch01);
            line2.draw(pitch02);
            for(int i=0; i<darts.size(); i++){
                darts[i].draw();
            }
        } else if (status == 3){
            line1.draw(pitch01);
            line2.draw(pitch02);
            for(int i=0; i<darts.size(); i++){
                darts[i].draw();
            }
        } else if (status == 4){
            line1.draw(pitch01);
            line2.draw(pitch02);

//            line1.drawPiece();
//            line2.drawPiece();
        } else if (status == 5){
            
        }
        ofPopMatrix();
    }
    post.end();
}