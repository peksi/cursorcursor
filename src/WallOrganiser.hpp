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
#include "ofxXmlSettings.h"

// Personal includes
#include "Wall.hpp"

class WallOrganiser {
public:
    WallOrganiser();
    void setup(ofxXmlSettings _XMLconfig);
    void addWall(vector<ofVec2f> _wallCoords, int _wallId);
    void addWalls(vector<vector<ofVec2f>> _wallCoordsVector, vector<int> _wallIdVector);
    void displayWalls();
    
    vector<Wall> wallVector;
private:
};

#endif /* WallOrganiser_hpp */
