#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // XML
    string file = "config.xml";
    bool parsingSuccessful = XMLconfig.loadFile(file);
    if (parsingSuccessful) {
        wallOrganiser.setup(XMLconfig,&user.position,&user.normalRay);
    }
    
    // GUI
    setupGui();
    
    // Eyetracker camera
    camera.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
    camera.setPixelFormat(OF_PIXELS_NATIVE);
    camera.setDesiredFrameRate(75);
    camera.setup(640, 480, true);
    
    // Virtual camera
    virtualCamera.setTarget(ofVec3f(0, 0 ,0));
    virtualCamera.setDistance(1500);
    xOrigin = -340.0;
    yOrigin = -600.0;
    zOrigin = 0.0;
    
    // OSC
    std::cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup( PORT );
}

//--------------------------------------------------------------
void ofApp::update(){
    if (camera.isFrameNew()) {
        camera.update();
    }
    
    // Handle OSC data. You should have processing sketch running.
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage incomingMessage;
        receiver.getNextMessage(incomingMessage);
        if(incomingMessage.getAddress() == "/pozyx"){ // check pozyx messages
            if( incomingMessage.getArgType(0) == OFXOSC_TYPE_STRING){ // check that we're getting strings
                vector<string> splitMessage = ofSplitString(incomingMessage.getArgAsString(0), ",",true);
                user.updateUser(splitMessage);
            }
            else{
                cout << "unhandled argument type " + incomingMessage.getArgTypeName(0) << "\n";
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(40);
    
    // EYE-CAMERA IMAGE
    if (showCamera) {
        ofPushMatrix();
        camera.draw(0, 0);
        ofPopMatrix();
    }
    
    // 3D VISUALISATION MATRIX
    if (show3D) {
        ofEnableDepthTest();
        virtualCamera.begin();
        
        ofPushMatrix();
        ofRotateDeg(180, 1, 0, 0);
        ofTranslate(xOrigin,yOrigin,zOrigin);
        
        wallOrganiser.displayGroundplane();
        wallOrganiser.displayWalls();
        wallOrganiser.displayProjections();
        
        user.displayUser();
        
        ofPopMatrix();
        
        if (showAxis) {
           drawAxis();
        }
        
        virtualCamera.end();
        ofDisableDepthTest();
    }
    
    // EYE-CAMERA LOG
    if (showLog) {
        std::stringstream ss;
        ss << " App FPS: " << ofGetFrameRate() << std::endl;
        ss << " Cam FPS: " << camera.getGrabber<ofxPS3EyeGrabber>()->getFPS() << std::endl;
        ss << "Real FPS: " << camera.getGrabber<ofxPS3EyeGrabber>()->getActualFPS() << std::endl;
        ss << "      id: 0x" << ofToHex(camera.getGrabber<ofxPS3EyeGrabber>()->getDeviceId());
        ofPushStyle();
        ofSetColor(255);
        ofDrawBitmapString(ss.str(), ofPoint(10, ofGetHeight()-50));
        ofPopStyle();
    }
    
    viewGui.draw();
    fboGui.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
    camera.close();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            yOrigin += 10;
            break;
        case OF_KEY_DOWN:
            yOrigin -= 10;
            break;
        case OF_KEY_LEFT:
            xOrigin += 10;
            break;
        case OF_KEY_RIGHT:
            xOrigin -= 10;
            break;
        case 'x':
            zOrigin += 50;
            break;
        case 'z':
            zOrigin -= 50;
            break;
        case '1':
            showCamera = !showCamera;
            break;
        case '2':
            showLog = !showLog;
            break;
        case '3':
            show3D = !show3D;
            break;
        case '4':
            showAxis = !showAxis;
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
    ofSetLineWidth(3);
    ofDrawLine(0, 0, 0,
               250, 0, 0);
    ofPopStyle();
    
    // Y-Axis
    ofPushStyle();
    ofSetColor(0, 255, 0);
    ofSetLineWidth(3);
    ofDrawLine(0, 0, 0,
               0,250, 0);
    ofPopStyle();
    
    // Z-Axis
    ofPushStyle();
    ofSetColor(0, 0, 255);
    ofSetLineWidth(3);
    ofDrawLine(0, 0, 0,
               0, 0, 250);
    ofPopStyle();
    
    // Origin
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofDrawSphere(0, 0, 0, 5);
    ofPopStyle();
}
void ofApp::setupGui() {
    // GUI
    viewGui.setup("View GUI");
    viewGui.setPosition(10, 10);
    viewParameterGroup.setName("View controls");
    viewParameterGroup.add(showCamera.set("Show camera feed",false));
    viewParameterGroup.add(showLog.set("Show camera log",true));
    viewParameterGroup.add(show3D.set("Show 3D visualisation",true));
    viewParameterGroup.add(showAxis.set("Show 3D axis",true));
    viewGui.add(viewParameterGroup);
    
    fboGui.setup("FBO GUI");
    fboGui.setPosition(ofGetWidth()-fboGui.getWidth()-10, 10);
    fboParameterGroup.setName("FBO controls");
    for (int i = 0; i < wallOrganiser.wallVector.size(); i++) {
        for (int j = 0; j < wallOrganiser.wallVector[i].projectionVector.size(); j++) {
            fboParameterGroup.add(wallOrganiser.wallVector[i].projectionVector[j].showFbo.set("FBO ID: " + ofToString(wallOrganiser.wallVector[i].projectionVector[j].id), false));
        }
    }
    fboGui.add(fboParameterGroup);
}
