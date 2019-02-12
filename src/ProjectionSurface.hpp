//
//  ProjectionSurface.hpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#ifndef ProjectionSurface_hpp
#define ProjectionSurface_hpp

#include "ofMain.h"

class ProjectionSurface{
public:
    ProjectionSurface();
    void setup(vector<ofVec2f> _wallCoords,vector<ofVec2f> _projectionCoords,int _projectionId);
    void calculateWorldCoords();
    void displayProjection();
    void displayProjectionFbo();
    
    int id;
    ofFbo projectionFbo;
    
    vector<ofVec2f> projectionCoordVector;
    vector<ofVec2f> wallCoordVector;
    ofVec2f surfaceStart, surfaceEnd;
    ofPath projectionPath;
    bool raySurfaceIntersection(ofVec3f* rayOrigin, ofVec3f* ray);
    ofVec3f raySurfaceIntersectionCoord(ofVec3f* rayOrigin, ofVec3f* ray);
    ofVec3f contactPoint;
    bool rayContact;
    
    vector<ofVec3f> surfaceInWorldCoords;
private:
};

#endif /* ProjectionSurface_hpp */
