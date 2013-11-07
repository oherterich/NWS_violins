#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	//we run at 60 fps!
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

    //create the socket and bind to port 11999
    udpConnection
	udpConnection.Create();
	udpConnection.Bind(11999);
	udpConnection.SetNonBlocking(true);

    //second connection on port 11998
    udpConnection2.Create();
	udpConnection2.Bind(11998);
	udpConnection2.SetNonBlocking(true);


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

        }

	}
    
    

    
    
}



//--------------------------------------------------------------
void testApp::draw(){

    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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
