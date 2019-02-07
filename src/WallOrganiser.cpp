//
//  WallOrganiser.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "WallOrganiser.hpp"

WallOrganiser::WallOrganiser() {
    
}
void WallOrganiser::setup(ofxJSONElement _JSONconfig) {
    
}
void WallOrganiser::addWall(vector<ofVec2f> _wallCoords) {
    wallVector.push_back(*new Wall());
    wallVector[0].setup(_wallCoords);
}
void WallOrganiser::addWalls(vector<vector<ofVec2f>> _wallCoordsVector) {
    for (int i = 0; i < _wallCoordsVector.size(); i++) {
        wallVector.push_back(*new Wall);
        wallVector[0].setup(_wallCoordsVector[i]);
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
