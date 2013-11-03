#pragma once
#include "ofMain.h"

class circle{
public:
    circle();
    void drawCircle(float x, float y, float r);
    void update();
    ofPoint pos;
    float radius;
    float angle;
    float red,green,blue;
    
    ofPolyline pline;
};