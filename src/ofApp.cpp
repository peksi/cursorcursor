#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    
    string file = "config.xml";
    bool parsingSuccessful = XMLconfig.loadFile(file);
    
    if (parsingSuccessful) {
        wallOrganiser.setup(XMLconfig);
    }
    
    virtualCamera.setTarget(ofVec3f(0, 0 ,0));
    
    xOrigin = 0.0;
    yOrigin = 0.0;
    zOrigin = -100.0;
    
    // OSC
    std::cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup( PORT );
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    // Handle OSC data. You should have processing sketch running.
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        if(m.getAddress() == "/pozyx"){ // check pozyx messages
            if( m.getArgType(0) == OFXOSC_TYPE_STRING){ // check that we're getting strings
                cout << m.getArgAsString(0) << "\n";
            }
            else{
                cout << "unhandled argument type " + m.getArgTypeName(0) << "\n";
            }
        }
    }
    
    user.updateUser(ofVec3f(30, 30, 30), ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(40);
    
    virtualCamera.begin();
    
    ofPushMatrix();
    ofRotateDeg(180, 1, 0, 0);
    ofTranslate(xOrigin,yOrigin,zOrigin);
    
    wallOrganiser.displayGroundplane();
    wallOrganiser.displayWalls();
    wallOrganiser.displayProjections();
    
    ofPopMatrix();
    
    user.displayUser();
    
    drawAxis();
    virtualCamera.end();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            yOrigin += 5;
            break;
        case OF_KEY_DOWN:
            yOrigin -= 5;
            break;
        case OF_KEY_LEFT:
            xOrigin += 5;
            break;
        case OF_KEY_RIGHT:
            xOrigin -= 5;
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::drawAxis() {
    // X-Axis
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofSetLineWidth(5);
    ofDrawLine(0, 0, 0,
               250, 0, 0);
    ofPopStyle();
    
    // Y-Axis
    ofPushStyle();
    ofSetColor(0, 255, 0);
    ofSetLineWidth(5);
    ofDrawLine(0, 0, 0,
               0,250, 0);
    ofPopStyle();
    
    // Z-Axis
    ofPushStyle();
    ofSetColor(0, 0, 255);
    ofSetLineWidth(5);
    ofDrawLine(0, 0, 0,
               0, 0, 250);
    ofPopStyle();
    
    // Origin
    ofPushStyle();
    ofSetColor(255, 0, 255);
    ofDrawSphere(0, 0, 0, 5);
    ofPopStyle();
}
