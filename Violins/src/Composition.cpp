//
//  Composition.cpp
//  Violins
//
//  Created by Joseph Moore on 10/17/13.
//
//

#include "Composition.h"



void Composition::setup(){
    track = 0;
    status = 0;
}

void Composition::update(){
    if(track == 1){
        if(status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        }
    } else if (track == 2){
        if(status == 1){
            line1.update(attack01, started);
            line2.update(attack02, started);
        } else if (status == 2){
            
        } else if (status == 3){

        } else if (status == 4){
            
        } else if (status == 5){
            
        }
    } else if (track == 3){
        if (status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        } else if (status == 4){
            
        }
    } else if (track == 4){
        if (status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        }
    }
}

void Composition::draw(){
    if(track == 1){
        if(status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        }
    } else if (track == 2){
        if(status == 1){
            line1.draw(pitch01);
            line2.draw(pitch02);
        } else if (status == 2){
            line1.draw(pitch01);
            line2.draw(pitch02);
        } else if (status == 3){
            line1.draw(pitch01);
            line2.draw(pitch02);
        } else if (status == 4){
            line1.drawPiece(300,300);
            line2.drawPiece(600,600);
        } else if (status == 5){
            
        }
    } else if (track == 3){
        if (status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        } else if (status == 4){
            
        }
    } else if (track == 4){
        if (status == 1){
            
        } else if (status == 2){
            
        } else if (status == 3){
            
        }
    }
}

// Track 1

void Composition::track1Order(){

}

void Composition::track1Chaos(){
    
}

void Composition::track1Join(){
    
}

// Track 2

void Composition::track2Line(float attack, float pitch){
    // Joe

}

void Composition::track2SmallLines(){
    // Joe
}

void Composition::track2Order(){
    
}

void Composition::track2KillLine(){
    // Joe
}

void Composition::track2LineCorpseOrder(){
    
}

// Track 3

void Composition::track3Main(){
    //Owen will work on this, but I welcome help :)
}

void Composition::track3Secondary(){
    //Owen will work on this, but I welcome help :)
}

void Composition::track3ColorChange(){
    //Owen will work on this, but I welcome help :)
}

void Composition::track3Implosion(){
    //Owen will work on this, but I welcome help :)
}

void Composition::track3Main2(){
    //Owen will work on this, but I welcome help :)
}

void Composition::track3Solo(){
    //Owen will work on this, but I welcome help :)
}

void Composition::track3Secondary2(){
    //Owen will work on this, but I welcome help :)
}

void Composition::track3Burst(){
    //Owen will work on this, but I welcome help :)
}



// Track 4

void Composition::track4Pattern1(){
    
}

void Composition::track4Pattern2(){
    
}

void Composition::track4Pattern3(){
    
}

void Composition::track4Finale(){
    
}