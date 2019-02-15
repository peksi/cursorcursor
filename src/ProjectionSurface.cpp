//
//  ProjectionSurface.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "ProjectionSurface.hpp"

ProjectionSurface::ProjectionSurface() {
    if(!projectionShader.load("projectionShader")) {
        cout << "Could not load shader correctly" << endl;
    }
}
void ProjectionSurface::setup(vector<ofVec2f> _wallCoords, vector<ofVec2f> _projectionCoords, int _projectionId) {
    
    id = _projectionId;
    projectionCoordVector = _projectionCoords;
    wallCoordVector = _wallCoords;
    wallLength = hypotf(
                              wallCoordVector[1].x - wallCoordVector[0].x, wallCoordVector[1].y - wallCoordVector[0].y
                              );
    
    // raycontact determines the color of the wall
    rayContact = false;
    
    calculateWorldCoords();
    
    float projectionWallWidth = abs(_wallCoords[1].x - _wallCoords[0].x);
    float projectionWallHeight = abs(_wallCoords[1].y - _wallCoords[0].y);
    projectionWidth = abs(_projectionCoords[1].x - _projectionCoords[0].x);
    projectionHeight = abs(_projectionCoords[1].y - _projectionCoords[0].y);
    projectionFbo.allocate(projectionWidth, projectionHeight);
    
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

float getLerpRatio(float start, float end, float lerpPoint){
    return (lerpPoint - start)/(end - start);
}

void ProjectionSurface::calculateWorldCoords() {
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

bool ProjectionSurface::raySurfaceIntersection(ofVec3f* rayOrigin, ofVec3f* ray){
    ofVec3f dirfrac = ofVec3f(0,0,0);
    ofVec3f lb = ofVec3f(surfaceStart.x, surfaceStart.y, 0);
    ofVec3f rt = ofVec3f(surfaceEnd.x, surfaceEnd.y, 200);
    // r.dir is unit direction vector of ray
    dirfrac.x = 1.0f / ray->x;
    dirfrac.y = 1.0f / ray->y;
    dirfrac.z = 1.0f / ray->z;
    // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    // r.org is origin of ray
    
    float t1 = (lb.x - rayOrigin->x)*dirfrac.x;
    float t2 = (rt.x - rayOrigin->x)*dirfrac.x;
    float t3 = (lb.y - rayOrigin->y)*dirfrac.y;
    float t4 = (rt.y - rayOrigin->y)*dirfrac.y;
    float t5 = (lb.z - rayOrigin->z)*dirfrac.z;
    float t6 = (rt.z - rayOrigin->z)*dirfrac.z;
    
    float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
    float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));
    float t;
    
    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        t = tmax;
        rayContact = false;
        return false;
    }
    
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        t = tmax;
        rayContact = false;
        return false;
    }
    
    t = tmin;
    rayContact = true;
    return true;
    
}

ofVec3f ProjectionSurface::raySurfaceIntersectionCoord(ofVec3f* rayOrigin, ofVec3f* ray){

    ofVec3f point0 = surfaceInWorldCoords[0];
    ofVec3f point1 = surfaceInWorldCoords[1];
    ofVec3f point2 = surfaceInWorldCoords[2];

    ofVec3f vec1 = point2 - point0;
    ofVec3f vec2 = point1 - point0;

    ofVec3f normal = vec1.cross(vec2).normalize();
    ofVec3f coord = point0;

    float d = normal.dot(coord); // normal x dot

    if ( normal.dot(*ray) == 0) {
        return ofVec3f(0,0,0);
    }

    // Compute the X value for the directed line ray intersecting the plane
    float x = (d - normal.dot(*rayOrigin) / normal.dot(*ray));

    // output contact point
    contactPoint = *rayOrigin + ray->normalize() * x;
    cout << contactPoint << endl;
    
    contactPointToProjectionSurfaceCoord();
    
    return contactPoint;
}

ofVec2f ProjectionSurface::contactPointToProjectionSurfaceCoord(){
    ofVec3f lb = ofVec3f(surfaceStart.x, surfaceStart.y, 0);
    ofVec3f rt = ofVec3f(surfaceEnd.x, surfaceEnd.y, 200);
    
    cout << lb << endl;
    cout << rt << endl;
    cout << contactPoint << endl;
    
    float ratioX = getLerpRatio(lb.x, rt.x, contactPoint.x);
//    float ratioY = getLerpRatio(lb.y, rt.y, contactPoint.y);
    float ratioZ = getLerpRatio(lb.z, rt.z, contactPoint.z);
    
    cout << "ratioX " << ratioX << endl;
//    cout << "ratioY " << ratioY << endl;
    cout << "ratioZ " << ratioZ << endl;
    
    ofVec2f retVect;
    retVect.x = ratioX;
    retVect.y = ratioZ;
    
    return retVect;
}


void ProjectionSurface::displayProjectionFbo() {
    if (showFbo) {
        if (projectionFbo.isAllocated()) {
            projectionFbo.draw(0,0);
        }
    }
}
void ProjectionSurface::drawProjectionFbo() {
    ofVec2f contactPointsProjection = contactPointToProjectionSurfaceCoord();
    ofClear(0);
    projectionFbo.begin();
    projectionShader.begin();
    projectionShader.setUniform2f("u_resolution", projectionWidth, projectionHeight);
    projectionShader.setUniform2f("u_contactPoint", contactPointsProjection.x,contactPointsProjection.y);
    projectionShader.setUniform2f("u_mousePosition", ofGetMouseX(), ofGetMouseY());
    projectionShader.setUniform1f("u_time",ofGetElapsedTimeMillis());
        ofPushMatrix();
        ofTranslate(abs(projectionCoordVector[1].x - projectionCoordVector[0].x)/2,
                    abs(projectionCoordVector[1].y - projectionCoordVector[0].y)/2);
        ofDrawPlane(0, 0,
                    abs(projectionCoordVector[1].x - projectionCoordVector[0].x),
                    abs(projectionCoordVector[1].y - projectionCoordVector[0].y));
        ofPopMatrix();
    projectionShader.end();
    projectionFbo.end();
}

