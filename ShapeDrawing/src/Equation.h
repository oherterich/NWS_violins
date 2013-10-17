//
//  Equation.h
//  ShapeDrawing
//
//  Created by Joseph Moore on 10/14/13.
//
//

#pragma once

#include "ofMain.h"

class Equation {
public:
    float YofX;
    void setYofX();
    void update();
    void draw();
    ofVec2f pos, vel;
};