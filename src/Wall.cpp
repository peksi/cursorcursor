//
//  Wall.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "Wall.hpp"

Wall::Wall() {
    
}
void Wall::setup(vector<ofVec2f> _wallCoords, int _wallId) {
    id = _wallId;
    wallCoordVector = _wallCoords;
    projectionAttached = false;
}
void Wall::attachProjection(vector<ofVec2f> _projectionCoords, int _projectionId) {
    ProjectionSurface tempProjectionSurface = *new ProjectionSurface;
    tempProjectionSurface.setup(wallCoordVector, _projectionCoords, _projectionId);
    projectionVector.push_back(tempProjectionSurface);
    projectionAttached = true;
}

