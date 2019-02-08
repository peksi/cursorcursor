//
//  ProjectionSurface.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "ProjectionSurface.hpp"

ProjectionSurface::ProjectionSurface() {
    
}
void ProjectionSurface::setup(vector<ofVec2f> _thisProjectionCoords, int _thisProjectionId) {
    projectionCoordVector = _thisProjectionCoords;
    id = _thisProjectionId;
}

