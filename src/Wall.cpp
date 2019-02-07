//
//  Wall.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#include "Wall.hpp"

Wall::Wall() {
    
}
void Wall::setup(vector<ofVec2f> _wallCoords) {
    wallCoordVector = _wallCoords;
}

