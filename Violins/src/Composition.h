//
//  Composition.h
//  Violins
//
//  Created by Joseph Moore on 10/17/13.
//
//

#pragma once

#include "ofMain.h"
#include "DancingLine.h"
#include "Dart.h"

class Composition {
    
public:
    void setup();
    void update();
    void draw();
    
    void track1Order();
    void track1Chaos();
    void track1Join();
    
    void track2Line(float attack, float pitch);
    void track2SmallLines();
    void track2Order();
    void track2KillLine();
    void track2LineCorpseOrder();
    
    void track3Main();
    void track3Secondary();
    void track3ColorChange();
    void track3Implosion();
    void track3Main2();
    void track3Solo();
    void track3Secondary2();
    void track3Solo2();
    void track3Burst();
    void track3Implosion2();
    
    void track4Pattern1();
    void track4Pattern2();
    void track4Pattern3();
    void track4Finale();
    int track, status;
    DancingLine line1, line2;
    
    float pitch01, pitch02, attack01, attack02, amp01, amp02;
    
    double started;
    vector<Dart> darts;

};
