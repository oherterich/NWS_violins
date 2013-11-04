#pragma once
#include "ofMain.h"

class Mapper{
public:
    Mapper();
    void Place(float x, float y, float r);
    void update();
    ofPoint pos;
    float radius;
    float angle;
    float red,green,blue;
    
        vector<ofVec3f> posList;
    
    float disp;
    
};