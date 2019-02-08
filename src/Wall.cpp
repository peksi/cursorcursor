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
    wallCoordVector = _wallCoords;
    id = _wallId;
}
void Wall::attachProjection(vector<ofVec2f> _projectionCoords, int _projectionId) {
    projectionVector.push_back(*new ProjectionSurface);
    projectionVector[projectionVector.size()-1].setup(_projectionCoords,_projectionId);
    cout << "ProjectionSurface added to wall: ";
    cout << id << endl;
    cout << "Has ID: ";
    cout << _projectionId << endl;
    cout << "Coordinates: Begin: ";
    cout << _projectionCoords[0];
    cout << " End: ";
    cout << _projectionCoords[1] << endl;
}

