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
    cout << "Start: ";
    cout << surfaceStart;
    cout << " End: ";
    cout << surfaceEnd << endl;

}

ofVec2f lerp(ofVec2f a, ofVec2f b, float presentage){
    return (a + presentage * (b - a));
}

void ProjectionSurface::calculateWorldCoords() {
    float wallLength = hypotf(
                              wallCoordVector[1].x - wallCoordVector[0].x, wallCoordVector[1].y - wallCoordVector[0].y
                              );
    
    surfaceStart = lerp(
                        wallCoordVector[0],
                        wallCoordVector[1],
                        projectionCoordVector[0].x / wallLength
                        );
    
    surfaceEnd = lerp(
                      wallCoordVector[0],
                      wallCoordVector[1],
                      projectionCoordVector[1].x / wallLength
                      );
    
    // construct ofPath for 3d rendering
    projectionPath.moveTo(surfaceStart);
    projectionPath.setFilled(true);
    projectionPath.setFillColor(ofColor(100 + 20,100,255 -  20));
    projectionPath.lineTo(ofVec3f(surfaceStart.x, surfaceStart.y, -200));
    projectionPath.lineTo(ofVec3f(surfaceEnd.x, surfaceEnd.y, -200));
    projectionPath.lineTo(ofVec3f(surfaceEnd.x, surfaceEnd.y, 0));
    projectionPath.lineTo(ofVec3f(surfaceStart.x, surfaceStart.y, 0));
    
}
void ProjectionSurface::displayProjection() {
    ofSetLineWidth(20);
    ofDrawLine(
               surfaceStart, surfaceEnd
    );
    
    projectionPath.draw();
}

