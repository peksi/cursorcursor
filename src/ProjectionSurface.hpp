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
    
    int id;
    vector<ofVec2f> projectionCoordVector;
    vector<ofVec2f> wallCoordVector;
private:
};

#endif /* ProjectionSurface_hpp */
