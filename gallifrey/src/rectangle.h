#pragma once
#include "ofMain.h"

class circle{
public:
    circle();
    void drawCircle(float r);
    void move(float x, float y);
    void rota(float a);
    void update();
    ofPoint pos;
    float radius;
    float angle;
    float red,green,blue;
    
    ofColor c;
    
    int t=255;
    
};