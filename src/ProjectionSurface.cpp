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
    rayContact = false;
    
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
    
    surfaceInWorldCoords = {
        ofVec3f(surfaceStart.x, surfaceStart.y, -200),
        ofVec3f(surfaceEnd.x, surfaceEnd.y, -200),
        ofVec3f(surfaceEnd.x, surfaceEnd.y, 0),
        ofVec3f(surfaceStart.x, surfaceStart.y, 0)
    };
    
    // construct ofPath for 3d rendering
    projectionPath.moveTo(surfaceStart);
    projectionPath.setFilled(true);
    projectionPath.setFillColor(ofColor(0,255,60));
    
    for (int i = 0; i < surfaceInWorldCoords.size() ; i++) {
        projectionPath.lineTo(surfaceInWorldCoords[i]);
    }

}
void ProjectionSurface::displayProjection() {
    ofSetLineWidth(20);
    if(rayContact == true){
        projectionPath.setFillColor(ofColor(255,255,60));
    } else {
        projectionPath.setFillColor(ofColor(0,255,60));
    }
    
    ofDrawLine(
               surfaceStart, surfaceEnd
    );
    
    projectionPath.draw();
}

bool ProjectionSurface::raySurfaceIntersection(ofVec3f rayOrigin, ofVec3f ray){
    
    ofVec3f point0 = surfaceInWorldCoords[0];
    ofVec3f point1 = surfaceInWorldCoords[1];
    ofVec3f point2 = surfaceInWorldCoords[2];

    ofVec3f vec1 = point2 - point0;
    ofVec3f vec2 = point1 - point0;
    
    ofVec3f normal = vec1.cross(vec2);
    ofVec3f coord = point0;
    
    float d = normal.dot(coord); // normal x dot
    
    if ( normal.dot(ray) == 0) {
        rayContact = false;
        return false;
    }
    
    // Compute the X value for the directed line ray intersecting the plane
    float x = (d - normal.dot(rayOrigin) / normal.dot(ray));
    
    // output contact point
    contactPoint = rayOrigin + ray.normalize() * x;
    rayContact = true;
    return true;
}

