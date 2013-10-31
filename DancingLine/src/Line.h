//
//  Line.h
//  DancingLine
//
//  Created by Joseph Moore on 10/30/13.
//
//

#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "FlowField.h"

class Line {
public:
    Line();
    
    void update(FlowField F);
    void draw();
    float spacing, width, length, speed, jitter;
    vector<Particle> vertices;
};