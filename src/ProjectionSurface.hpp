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
    void setup(vector<ofVec2f> _projectionCoords, int _projectionId);
    
    vector<ofVec2f> projectionCoordVector;
    int id;
private:
};

#endif /* ProjectionSurface_hpp */
