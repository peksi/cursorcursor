//
//  Wall.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "Wall.hpp"

Wall::Wall() {
    
}
void Wall::setup(vector<ofVec2f> _wallCoords, int _wallId) {
    wallCoordVector = _wallCoords;
    wallId = _wallId;
}
void Wall::attachProjector(vector<ofVec2f> _projectorCoords, int _projectorId) {
    
}

