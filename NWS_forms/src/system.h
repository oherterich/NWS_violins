//
//  system.h
//  NWS_forms
//
//  Created by Tiam Taheri on 10/14/13.
//
//

#pragma once
#include "ofMain.h"


class system{
    
public:
    void setup();
    void draw();
    void branch(int ls);
    
    int counter;
    float lineSize;
    float startX;
};