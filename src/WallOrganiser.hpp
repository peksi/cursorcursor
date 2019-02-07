//
//  WallOrganiser.hpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 06/02/2019.
//

#ifndef WallOrganiser_hpp
#define WallOrganiser_hpp

#include "ofMain.h"

// ofxAddon includes
#include "ofxJSON.h"

// Personal includes
#include "Wall.hpp"

class WallOrganiser {
public:
    WallOrganiser();
    void setup(ofxJSONElement _JSONconfig);
    void addWall(vector<ofVec2f> _wallCoords);
    void addWalls(vector<vector<ofVec2f>> _wallCoordsVector);
    void displayWalls();
    
    vector<Wall> wallVector;
private:
};

#endif /* WallOrganiser_hpp */
