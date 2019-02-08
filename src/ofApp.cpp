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
    xOrigin = -340.0;
    yOrigin = -600.0;
    zOrigin = 300;
}

//--------------------------------------------------------------
void ofApp::update(){

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
