#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	//we run at 60 fps!
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

    //create the socket and bind to port 11999
	udpConnection.Create();
	udpConnection.Bind(11999);
	udpConnection.SetNonBlocking(true);

    //second connection on port 11998
    udpConnection2.Create();
	udpConnection2.Bind(11998);
	udpConnection2.SetNonBlocking(true);
    
	ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void testApp::update(){

	char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message=udpMessage;
	if(message!=""){
        
        //get incomming string, split string into pieces then assign pieces to x, y, z, magx, magy and magz
		vector<string> strPoints = ofSplitString(message,"[/p]");

        vector<string> point = ofSplitString(strPoints[0],"|");
			if( point.size() == 6 ){
				x=ofMap(atof(point[0].c_str()), -2000, 2000, 0, 1000);
				y=ofMap(atof(point[1].c_str()), -2000, 2000, 0, 1000);
                z=ofMap(atof(point[2].c_str()), -2000, 2000, 0, 1000);
				magx=atof(point[3].c_str());
				magy=atof(point[4].c_str());
                magz=atof(point[5].c_str());

                
                //add a point to the stroke array so we can plot it on screen
				stroke.push_back(ofPoint(x,y));
                //give each point an age so they fade away after a while
                age.push_back(ofGetElapsedTimeMillis());
			}

	}


	char udpMessage2[100000];
	udpConnection2.Receive(udpMessage2,100000);
	string message2=udpMessage2;
	if(message2!=""){

        
        //get incomming string, split string into pieces then assign pieces to x, y, z, magx, magy and magz
		vector<string> strPoints2 = ofSplitString(message2,"[/p]");

        vector<string> point2 = ofSplitString(strPoints2[0],"|");
        if( point2.size() == 6 ){
            x2=ofMap(atof(point2[0].c_str()), -2000, 2000, 0, 1000);
            y2=ofMap(atof(point2[1].c_str()), -2000, 2000, 0, 1000);
            z2=ofMap(atof(point2[2].c_str()), -2000, 2000, 0, 1000);
            magx2=atof(point2[3].c_str());
            magy2=atof(point2[4].c_str());
            magz2=atof(point2[5].c_str());

             //add a point to the stroke array so we can plot it on screen
            stroke2.push_back(ofPoint(x2,y2));
            //give each point an age so they fade away after a while
            age2.push_back(ofGetElapsedTimeMillis());
        }
		//}
	}
    
    
    
    //Print all accel data in one line
    cout << "X1: "<< x << "    Y1: "<< y << "    Z: "<< z << "   X2: " << x2 << "   Y2: "<< y2 << "    Z2: "<< z2 << " "  << endl;

    //Print all magnetometer data in one line
    cout << "magX1: "<< magx << " " <<  "magX2: "<< magx2 << " " << "magY1: "<< magy << " " <<  "magY2: "<< magy2 << " " "magZ1: "<< magz << " " <<  "magZ2: "<< magz2 << " "  << endl;
    
    
    
    
    
    //erase points if they get too old
    for(int i = 0; i < age.size(); i++){
        if(age[i] < ofGetElapsedTimeMillis() - 2000){
            age.erase(age.begin() + i);
            stroke.erase(stroke.begin() + i);
        }
    }
    for(int i = 0; i < age2.size(); i++){
        if(age2[i] < ofGetElapsedTimeMillis() - 2000){
            age2.erase(age2.begin() + i);
            stroke2.erase(stroke2.begin() + i);
        }
    }
    
    
}



//--------------------------------------------------------------
void testApp::draw(){
    ofFill();
    ofSetHexColor(0xFFFFFF);
    ofRect(0,0,200,30);
	ofSetHexColor(0x101010);
	ofDrawBitmapString("UDP Receiver Example ", 10, 20);
    ofDrawBitmapString("Points stored ", 10, 50);
    ofDrawBitmapString(ofToString(stroke.size()), 150, 50);
    
    ofSetColor(0);
    ofDrawBitmapString("time since last msg: "+ofToString(tempTimeStamp), 100, 10);
    
    ofSetColor(255, 255*0.35);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    

    //draw first violin in red
	for(int i=1;i<stroke.size();i++){
        ofSetColor(0);
        ofSetLineWidth(2);
		ofLine(stroke[i-1].x,stroke[i-1].y,stroke[i].x,stroke[i].y);
        ofCircle(stroke[i].x, stroke[i].y, 12);
        ofSetColor(255, 0, 0);
        ofCircle(stroke[i].x, stroke[i].y, 10);
    }
    
    //draw second violin in blue
	for(int i=1;i<stroke2.size();i++){
        ofSetColor(0);
        ofSetLineWidth(2);
		ofLine(stroke2[i-1].x,stroke2[i-1].y,stroke2[i].x,stroke2[i].y);
        ofCircle(stroke2[i].x, stroke2[i].y, 12);
        ofSetColor(0, 0, 255);
        ofCircle(stroke2[i].x, stroke2[i].y, 10);
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
      stroke.clear();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
