//
//  Wall.hpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#ifndef Wall_hpp
#define Wall_hpp

#include "ofMain.h"

// Personal includes
#include "ProjectionSurface.hpp"

class Wall {
public:
    Wall();
    void setup(vector<ofVec2f> _wallCoords, int _wallId);
    void attachProjection(vector<ofVec2f> _projectionCoords, int _projectionId);
    
    vector<ofVec2f> wallCoordVector;
    vector<ProjectionSurface> projectionVector;
    int id;
private:
};

#endif /* Wall_hpp */
