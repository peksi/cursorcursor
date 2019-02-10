//
//  ProjectionSurface.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "ProjectionSurface.hpp"

ProjectionSurface::ProjectionSurface() {
    
}
void ProjectionSurface::setup(vector<ofVec2f> _wallCoords, vector<ofVec2f> _projectionCoords, int _projectionId) {
    id = _projectionId;
    projectionCoordVector = _projectionCoords;
    wallCoordVector = _wallCoords;
    
    calculateWorldCoords();
    
    cout << "Projection added to wall with coordinates: ";
    cout << "Start: ";
    cout << projectionCoordVector[0];
    cout << " End: ";
    cout << projectionCoordVector[1] << endl;
}
void ProjectionSurface::calculateWorldCoords() {
    ofVec2f constVector = ofVec2f(1,0);
    ofVec2f wallVector = ofVec2f((wallCoordVector[0].x + wallCoordVector[1].x),
                                 (wallCoordVector[0].y + wallCoordVector[1].y));
    wallVector.normalize();
    float wallAngle = constVector.angle(wallVector);
    cout << wallVector << endl;
    
    float xOffPlacement = cos(wallAngle) * projectionCoordVector[0].x;
    float yOffPlacement = sin(wallAngle) * projectionCoordVector[0].x;
    cout << xOffPlacement << endl;
    cout << yOffPlacement << endl;
}
void ProjectionSurface::displayProjection() {

}

