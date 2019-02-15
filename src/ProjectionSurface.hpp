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
    void drawProjectionFbo();
    void displayProjection();
    void displayProjectionFbo();
    float wallLength;
    
    int id;
    ofFbo projectionFbo;
    ofShader projectionShader;
    ofShader clearShader;
    ofParameter<bool> showFbo;
    
    vector<ofVec2f> projectionCoordVector;
    vector<ofVec2f> wallCoordVector;
    ofVec2f surfaceStart, surfaceEnd;
    ofPath projectionPath;
    
    /// \brief returns true if ray is colliding with projection surface
    bool raySurfaceIntersection(ofVec3f* rayOrigin, ofVec3f* ray);
    
    /// \brief calculate surface intersection coordinates
    ofVec3f raySurfaceIntersectionCoord(ofVec3f* rayOrigin, ofVec3f* ray);
    
    /// \brief Contact point in world coordinates where ray is colliding with projectionSurface
    ofVec3f contactPoint;
    
    /// \brief Returns the point where ray is pointing in projecting canvas coordinate space (x,y)
    ofVec2f contactPointToProjectionSurfaceCoord();
    bool rayContact;
    
    vector<ofVec3f> surfaceInWorldCoords;
    
    float projectionWidth;
    float projectionHeight;
private:
};

#endif /* ProjectionSurface_hpp */
