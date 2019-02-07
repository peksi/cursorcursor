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
    }
    
    // PROJECTOR SETUP
    _XMLconfig.popTag(); // pop up to level: roomSetup
    _XMLconfig.pushTag("projectionSurfaces"); // Dive into level: projectionSurface
    int numProjectors = _XMLconfig.getNumTags("element");
    
    for (int i = 0; i < numProjectors; i++) {
        _XMLconfig.pushTag("element",i);
        int wallPairId = _XMLconfig.getValue("wallId", 0);
        
        for (Wall w : wallVector) {
            if (w.wallId == wallPairId) {
                float pBeginX = _XMLconfig.getValue("beginX", 0);
                float pBeginY = _XMLconfig.getValue("beginY", 0);
                float pEndX = _XMLconfig.getValue("endX", 0);
                float pEndY = _XMLconfig.getValue("endY", 0);
                int projectorId = _XMLconfig.getValue("projectorId", 0);
                
                vector<ofVec2f> projectorCoords;
                projectorCoords.push_back(ofVec2f(pBeginX,pBeginY));
                projectorCoords.push_back(ofVec2f(pEndX,pEndY));
                
                w.attachProjector(projectorCoords,projectorId);
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
    wallVector[0].setup(_wallCoords,_wallId);
    cout << "Wall added with coordinates: ";
    cout << "X ";
    cout << _wallCoords[0];
    cout << " Y ";
    cout << _wallCoords[1] << endl;
}
void WallOrganiser::addWalls(vector<vector<ofVec2f>> _wallCoordsVector, vector<int> _wallIdVector) {
    for (int i = 0; i < _wallCoordsVector.size(); i++) {
        wallVector.push_back(*new Wall);
        wallVector[0].setup(_wallCoordsVector[i],_wallIdVector[i]);
    }
}
void WallOrganiser::displayWalls() {
    for (int i = 0; i < wallVector.size(); i++) {
        ofDrawLine(wallVector[i].wallCoordVector[0].x,
                   wallVector[i].wallCoordVector[0].y,
                   wallVector[i].wallCoordVector[1].x,
                   wallVector[i].wallCoordVector[1].y);
    }
}
