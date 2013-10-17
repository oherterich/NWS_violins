//
//  Composition.h
//  Violins
//
//  Created by Joseph Moore on 10/17/13.
//
//

#pragma once

#include "ofMain.h"

class Composition {
    
public:
    void setup();
    void update();
    void draw();
    
    void track1Order();
    void track1Chaos();
    void track1Join();
    
    void track2Line();
    void track2SmallLines();
    void track2Order();
    void track2KillLine();
    void track2LineCorpseOrder();
    
    void track3Orbit1();
    void track3Corruption1();
    void track3Orbit2();
    void track3Corruption2();
    void track3Orbit3();
    void track3Corruption3();
    void track3FinalBattle();
    
    void track4Pattern1();
    void track4Pattern2();
    void track4Pattern3();
    void track4Finale();
    
};
