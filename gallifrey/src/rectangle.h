#pragma once
#include "ofMain.h"
#include "ofxPostProcessing.h"

class circle{
public:
    circle();
    void drawCircle();
    void drawLines();
    void move();
    void rota(float a);
    void update();
    void addCircle(float r);
    void fall();
    
    ofPoint pos;
    float rad;
    float tRad;
    float pRad;
    float angle;
    float cirSpeed;
    float disp;
    float sDisp;
    float mod;
    float vel;
    float grav;
    float dt;
    
    ofColor c;
    
    int t=255;
    int fSpeed;
    
    bool slowToStop;
    bool stopped;
};