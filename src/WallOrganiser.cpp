//
//  WallOrganiser.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "WallOrganiser.hpp"

WallOrganiser::WallOrganiser() {
    
}
void WallOrganiser::setup(ofxXmlSettings _XMLconfig) {
    _XMLconfig.pushTag("document");
    _XMLconfig.pushTag("roomSetup");
    _XMLconfig.pushTag("walls");
    int numWalls = _XMLconfig.getNumTags("element");
    
    for (int i = 0; i < numWalls; i++) {
        _XMLconfig.pushTag("element",i);
        
        float beginX = _XMLconfig.getValue("beginX", 0);
        float beginY = _XMLconfig.getValue("beginY", 0);
        float endX = _XMLconfig.getValue("endX", 0);
        float endY = _XMLconfig.getValue("endY", 0);
        int wallId = _XMLconfig.getValue("id",0);
        
        vector<ofVec2f> wallCoords;
        wallCoords.push_back(ofVec2f(beginX,beginY));
        wallCoords.push_back(ofVec2f(endX,endY));
        
        addWall(wallCoords,wallId);
        
        _XMLconfig.popTag();
        _XMLconfig.popTag();
        
        _XMLconfig.pushTag("projectionSurfaces");
        int numProjections = _XMLconfig.getNumTags("element");
        
        for (int j = 0; j < numProjections; j++) {
            _XMLconfig.pushTag("element",j);
            int pairId = _XMLconfig.getValue("wallId",0);
            
            if (wallId == pairId) {
                float pBeginX = _XMLconfig.getValue("beginX", 0);
                float pBeginY = _XMLconfig.getValue("beginY", 0);
                float pEndX = _XMLconfig.getValue("endX", 0);
                float pEndY = _XMLconfig.getValue("endY", 0);
                float projectionId = _XMLconfig.getValue("projectionId", 0);
                
                vector<ofVec2f> projectionCoords;
                projectionCoords.push_back(ofVec2f(pBeginX,pBeginY));
                projectionCoords.push_back(ofVec2f(pEndX,pEndY));
                
                wallVector[i].attachProjection(projectionCoords, projectionId);
            }
            
            _XMLconfig.popTag();
        }
        _XMLconfig.popTag();
        _XMLconfig.pushTag("walls"); // Reset to walls-level for next iteration on forLoop.
    }
    
    // Reset to document level of XML
    _XMLconfig.popTag();
    _XMLconfig.popTag();
    _XMLconfig.popTag();
    cout << "Current XML level: ";
    cout << _XMLconfig.getPushLevel() << endl;
}
void WallOrganiser::addWall(vector<ofVec2f> _wallCoords, int _wallId) {
    Wall tempWall =  *new Wall();
    tempWall.setup(_wallCoords, _wallId);
    wallVector.push_back(tempWall);
    
    cout << "Wall added with coordinates: ";
    cout << "Start: ";
    cout << _wallCoords[0];
    cout << " End: ";
    cout << _wallCoords[1] << endl;
}
void WallOrganiser::displayWalls() {
    for (int i = 0; i < wallVector.size(); i++) {
        ofPushStyle();
        ofSetColor(0, 0, 255);
        ofSetLineWidth(3);
        ofDrawLine(wallVector[i].wallCoordVector[0].x,
                   wallVector[i].wallCoordVector[0].y,
                   wallVector[i].wallCoordVector[1].x,
                   wallVector[i].wallCoordVector[1].y);
        ofPopStyle();
    }
}
void WallOrganiser::displayGroundplane() {
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(70);
    ofTranslate(680/2, 1400/2);
    ofDrawPlane(0, 0, 5, 680, 1400);
    ofPopStyle();
    ofPopMatrix();
}
void WallOrganiser::displayProjections() {
    for (int i = 0; i < wallVector.size(); i++) {
        if (wallVector[i].projectionAttached) {
            for (int j = 0; j < wallVector[i].projectionVector.size(); j++) {
                wallVector[i].projectionVector[j].displayProjection();
            }
        }
    }
}
