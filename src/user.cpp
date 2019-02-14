//
//  user.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 08/02/2019.
//

#include "user.hpp"

User::User() {
    rotationOffset = 45;
    
    position = ofVec3f(0,0,0);
    incomingPosition = ofVec3f(0,0,0);
}
void User::setup() {
    
}

void User::updateUser(vector<string> _incomingOSCmessage) {
    // slot [0] & [1] are reserved for 'POS' and tagID.
    incomingPosition = ofVec3f(ofToFloat(_incomingOSCmessage[3])/10,
                               ofToFloat(_incomingOSCmessage[2])/10,
                               ofToFloat(_incomingOSCmessage[4])/10
                       );
    if (flipX) {
        incomingPosition.x = -incomingPosition.x;
    }
    if (flipY) {
        incomingPosition.y = -incomingPosition.y;
    }
    if (flipZ) {
        incomingPosition.z = -incomingPosition.z;
    }
    
    rotation = ofVec3f(ofToFloat(_incomingOSCmessage[5]),
                       ofToFloat(_incomingOSCmessage[6]),
                       ofToFloat(_incomingOSCmessage[7])
                       );
}
void User::smoothPosition() {
    float smoothX = ofLerp(position.x,incomingPosition.x,0.01);
    float smoothY = ofLerp(position.y,incomingPosition.y,0.01);
    float smoothZ = ofLerp(position.z,incomingPosition.z,0.01);
    
    position = ofVec3f(smoothX+xOffset,smoothY+yOffset,smoothZ+zOffset);
}
void User::displayUser() {
    calculateRay();
    displayRay();
    
    // User head position
    userHead.set(10, 10);
    userHead.setPosition(position.x, position.y, -100);
    userHead.draw();
    
    // Floor position line
    ofDrawLine(position.x, position.y, -100, position.x,position.y,0);
}
void User::calculateRay() {
    ofVec3f tempRay = ofVec3f(1,0,0);
    tempRay.rotate(0,0,rotationOffset); // Calibration rotation
    tempRay.rotate(0, 0, rotation.x);
    
    // Calculate axis around which to rotate Z (tilt), perpendicular to x/y vector.
    ofVec2f tempRay2dVector = ofVec2f(tempRay[0],tempRay[1]);
    ofVec2f zRotationAxis = tempRay2dVector.getPerpendicular();
    
    tempRay.rotate(rotation.z, zRotationAxis);
    
    normalRay = tempRay;
    smoothRay();
    tempRay *= 1000;
    scaledRay = tempRay;
    
}
void User::smoothRay() {
    bool rayMatched = normalRay.match(smoothedRay,0.01);
    
    if (rayMatched == false) {
        normalSmoothedRay = smoothedRay.getNormalized();
        float smoothX = ofLerp(normalSmoothedRay.x,normalRay.x,0.1);
        float smoothY = ofLerp(normalSmoothedRay.y,normalRay.y,0.1);
        float smoothZ = ofLerp(normalSmoothedRay.z,normalRay.z,0.1);
        
        normalSmoothedRay = ofVec3f(smoothX,smoothY,smoothZ);
        smoothedRay = normalSmoothedRay * 1000;
    }
}
void User::displayRay() {
    // Scaled ray (realtime data)
    ofPushStyle();
    ofSetColor(200, 100, 100);
    ofSetLineWidth(3);
    ofDrawLine(position.x, position.y,-100,
               position.x + scaledRay.x,
               position.y + scaledRay.y,
               -100 + scaledRay.z);
    ofPopStyle();
    
    // Smoothed ray
    ofPushStyle();
    ofSetColor(100, 200, 100);
    ofSetLineWidth(3);
    ofDrawLine(position.x, position.y,-100,
               position.x + smoothedRay.x,
               position.y + smoothedRay.y,
               -100 + smoothedRay.z);
    ofPopStyle();
}
