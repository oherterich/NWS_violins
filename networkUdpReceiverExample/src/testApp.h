#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		ofxUDPManager udpConnection;
        ofxUDPManager udpConnection2;
    
		ofTrueTypeFont  mono;
		ofTrueTypeFont  monosm;

		vector<ofPoint> stroke;
        vector<float> age;

        vector<ofPoint> stroke2;
        vector<float> age2;
    
        //first violin values
        float x,y,z,magx,magy,magz;
    
        //second violin values
        float x2,y2,z2,magx2,magy2,magz2;
        
        float messageInTime;
        float tempTimeStamp;
};

