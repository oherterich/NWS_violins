#pragma once
#include "ofMain.h"

class circle{
public:
    circle();
    void drawCircle();
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
    float sDisp;
    float mod;
    
    
    ofColor c;
    
    int t=255;
    int fSpeed;
    
    bool slowToStop;
    bool stopped;
};