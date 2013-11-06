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
    
    ofPoint pos;
    float rad;
    float tRad;
    float pRad;
    float angle;
    float cirSpeed;
    float disp;
    
    
    ofColor c;
    
    int t=255;
    int fSpeed;

};