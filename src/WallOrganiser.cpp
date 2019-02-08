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
    // WALL SETUP
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
        _XMLconfig.popTag();
        
        vector<ofVec2f> wallCoords;
        wallCoords.push_back(ofVec2f(beginX,beginY));
        wallCoords.push_back(ofVec2f(endX,endY));
        
        addWall(wallCoords,wallId);
        
        // Make wall primitives
        float wallWidth = ofVec2f(beginX,beginY).distance(ofVec2f(endX,endY));
        
        ofVec2f constVector = ofVec2f(1.0,0.0);
        ofVec2f normVector = ofVec2f(abs(endX - beginX),abs(endY - beginY));
        float wallAngle = constVector.angle(normVector);
        wallAngleVector.push_back(wallAngle);
        
        cout << "current wall angle";
        cout << wallAngle << endl;
        wallPrimitiveVector.push_back(*new ofBoxPrimitive(wallWidth, 100, 3));
        wallPrimitiveVector[wallPrimitiveVector.size()-1].setPosition((beginX+endX)/2, (beginY+endY)/2, 50);
        wallPrimitiveVector[wallPrimitiveVector.size()-1].rotateDeg(90, ofVec3f(1,0,0)); // Rotate to stand upright in z-space
        wallPrimitiveVector[wallPrimitiveVector.size()-1].rotateDeg(wallAngle, ofVec3f(0,0,1)); // Rotate to desired angle
        
        // Color all sides for clear visualisation
        for (int i = 0; i < 6; i++) {
            wallPrimitiveVector[wallPrimitiveVector.size()-1].setSideColor(i, ofColor(ofRandom(0,125),
                                                                                      ofRandom(0,125),
                                                                                      ofRandom(0,125)));
        }
    }
    
    // PROJECTOR SETUP
    _XMLconfig.popTag(); // pop up to level: roomSetup
    _XMLconfig.pushTag("projectionSurfaces"); // Dive into level: projectionSurface
    int numProjections = _XMLconfig.getNumTags("element");
    
    for (int i = 0; i < numProjections; i++) {
        _XMLconfig.pushTag("element",i);
        int wallPairId = _XMLconfig.getValue("wallId", 0);
        
        for (int j = 0; j < wallVector.size(); j++) {
            if (wallVector[j].id == wallPairId) {
                float pBeginX = _XMLconfig.getValue("beginX", 0);
                float pBeginY = _XMLconfig.getValue("beginY", 0);
                float pEndX = _XMLconfig.getValue("endX", 0);
                float pEndY = _XMLconfig.getValue("endY", 0);
                int projectionId = _XMLconfig.getValue("projectionId", 0);
                
                vector<ofVec2f> projectionCoords;
                projectionCoords.push_back(ofVec2f(pBeginX,pBeginY));
                projectionCoords.push_back(ofVec2f(pEndX,pEndY));
                
                wallVector[j].attachProjection(projectionCoords,projectionId);
                
                // Make projection primitives
                float projectionWidth = ofVec2f(pBeginX,pBeginY).distance(ofVec2f(pEndX,pEndY));
                ofBoxPrimitive currentWallPrimitive = wallPrimitiveVector[j];
                ofVec3f currentWallPosition = currentWallPrimitive.getPosition();
                float currentWallWidth = currentWallPrimitive.getWidth();
                
                float yOffPlacement = sin(wallAngleVector[wallPairId-1])*((currentWallWidth/2)-pBeginX);
                float xOffPlacement = cos(wallAngleVector[wallPairId-1])*((currentWallWidth/2)-pBeginX);
                
                
                cout << xOffPlacement << endl;
                
                projectionPrimitiveVector.push_back(*new ofBoxPrimitive(abs(pEndX-pBeginX),abs(pEndY-pBeginY),5));
                projectionPrimitiveVector[projectionPrimitiveVector.size()-1].setPosition(currentWallPosition.x,
                                                                                          currentWallPosition.y - yOffPlacement,
                                                                                          currentWallPosition.z + (pBeginY+pEndY)/2 - 50);
                
                
                
                projectionPrimitiveVector[projectionPrimitiveVector.size()-1].rotateDeg(90, ofVec3f(1,0,0)); // Rotate to stand upright in z-space
                projectionPrimitiveVector[projectionPrimitiveVector.size()-1].rotateDeg(wallAngleVector[wallPairId-1],ofVec3f(0,0,1)); // Rotate same as parent wall
            }
        }
        _XMLconfig.popTag();
    }
    
    // Reset to document level of XML
    _XMLconfig.popTag();
    _XMLconfig.popTag();
    _XMLconfig.popTag();
    cout << "Current XML level: ";
    cout << _XMLconfig.getPushLevel() << endl;
    
}
void WallOrganiser::addWall(vector<ofVec2f> _wallCoords, int _wallId) {
    wallVector.push_back(*new Wall());
    wallVector[wallVector.size()-1].setup(_wallCoords,_wallId);
    cout << "Wall added with coordinates: ";
    cout << "Start: ";
    cout << _wallCoords[0];
    cout << " End: ";
    cout << _wallCoords[1] << endl;
}
void WallOrganiser::addWalls(vector<vector<ofVec2f>> _wallCoordsVector, vector<int> _wallIdVector) {
    for (int i = 0; i < _wallCoordsVector.size(); i++) {
        wallVector.push_back(*new Wall);
        wallVector[wallVector.size()-1].setup(_wallCoordsVector[i],_wallIdVector[i]);
    }
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
        
        wallPrimitiveVector[i].draw();
    }
}
void WallOrganiser::displayProjections() {
    /*
    for (int i = 0; i < wallVector.size(); i++) {
        for (int j = 0; j < wallVector[i].projectionVector.size(); j++) {
            ofPushStyle();
            ofSetColor(0, 0, 255);
            ofSetLineWidth(3);
            ofDrawLine(wallVector[i].projectionVector[j].projectionCoordVector[0].x,
                       wallVector[i].projectionVector[j].projectionCoordVector[0].y,
                       wallVector[i].projectionVector[j].projectionCoordVector[1].x,
                       wallVector[i].projectionVector[j].projectionCoordVector[1].y);
            ofPopStyle();
        }
    }
     */
    
    for (int j = 0; j < projectionPrimitiveVector.size(); j++) {
        projectionPrimitiveVector[j].draw();
    }
}
